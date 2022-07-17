#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define DEQUE

#ifndef ITERATOR
#include "iterator.hpp"
#endif // !ITERATOR
#ifndef ALLOCATOR
#include "allocator.hpp"
#endif // !ALLOCATOR
#ifndef ALGORITHM
#include "algorithm.hpp"
#endif // !ALGORITHM


namespace mstl_itm
{
	template <class _ValueT, size_t _BufSize = 0>
	class Deque
	{
	public:
		using ValueType = _ValueT;		// 元素类型
		using Pointer = _ValueT*;	// 元素类型指针
		using Reference = _ValueT&;	// 元素类型引用

	private:
		using MapPointer = Pointer*;	// 中控器指针

	private:
		MapPointer map;	// 中控器
		size_t mapSize;	// 中控器最多存放指针的个数

	private:
		// 计算缓冲区元素个数
		static size_t GetBufferSize()
		{
			return _BufSize != 0 ? _BufSize :
				(sizeof(ValueType) < 512 ? (512 / sizeof(ValueType)) : 1);
		}

	private:
		// Deque迭代器
		struct DequeIterator : public RandomAcessIterator<ValueType>
		{
			typedef DequeIterator Iterator;
			typedef ValueType ValueType;

			Pointer m_cur;		// 缓存区当前指向元素
			Pointer m_first;	// 当前缓存区的头
			Pointer m_last;	// 当前缓存区的尾
			MapPointer m_node;	// 指回中控器结点

			// 由当前缓存区指向下一缓存区 JUMP
			void operator>>(MapPointer newNode)
			{
				this->m_node = newNode;
				this->m_first = *newNode;
				this->m_last = this->m_first + GetBufferSize();
			}

			Reference operator*() const { return *m_cur; }
			Pointer operator->() const { return &(operator*()); }

			size_t operator-(const Iterator& iter) const
			{
				return GetBufferSize() * (this->m_node - iter.m_node - 1) +
					(this->m_cur - this->m_first) + (iter.m_last - iter.m_cur);
			}

			Iterator& operator++()
			{
				++m_cur;
				// 超出缓存区，则跳到下一缓存区
				if (m_cur == m_last)
				{
					operator>>(m_node + 1);
					m_cur = m_first;
				}
				return *this;
			}

			Iterator operator++(int)
			{
				Iterator temp = *this;
				++(*this);
				return temp;
			}

			Iterator& operator--()
			{
				// 超出缓存区，则跳到下一缓存区
				if (m_cur == m_first)
				{
					operator>>(m_node - 1);
					m_cur = m_last;
				}
				--m_cur;
				return *this;
			}

			Iterator operator--(int)
			{
				Iterator temp = *this;
				--(*this);
				return temp;
			}

			Iterator& operator+=(int n)
			{
				int offset = n + (m_cur - m_first);
				// 目标在同一缓存区
				if (offset >= 0 && offset < (int)GetBufferSize())
					m_cur += n;
				// 目标不在同一缓存区
				else
				{
					size_t nodeOffset = offset > 0 ? offset / GetBufferSize() :
						-((-offset - 1) / (int)GetBufferSize()) - 1;
					// 跳到正确的缓存区
					operator>>(m_node + nodeOffset);
					// 切换至正确的元素
					m_cur = m_first + (offset - nodeOffset * GetBufferSize());
				}

				return *this;
			}

			Iterator operator+(int n) const
			{
				Iterator temp = *this;
				return temp += n;
			}

			Iterator& operator-=(int n)
			{
				return *this += -n;
			}

			Iterator operator-(int n) const
			{
				Iterator temp = *this;
				return temp -= n;
			}

			Reference operator[](size_t i) const { return *(*this + i); }
			bool operator==(const Iterator& iter) const { return m_cur == iter.m_cur; }
			bool operator!=(const Iterator& iter) const { return !(*this == iter); }
			bool operator<(const Iterator& iter) const
			{
				return m_node == iter.m_node ? m_cur < iter.m_cur : m_node < iter.m_node;
			}
		};

	public:
		using Iterator = DequeIterator;

	private:
		Iterator start;	// 指向第一个缓冲区的头结点
		Iterator finish;	// 指向最后一个缓冲区的尾结点

	public:
		// 起始迭代器
		Iterator Begin() { return start; }

		// 终止迭代器
		Iterator End() { return finish; }

		// 索引器
		Reference operator[](size_t i) { return start[i]; }

		// 首元素
		Reference Front() { return *start; }

		// 尾元素
		Reference Back() { return *(finish - 1); }

		// 元素个数
		size_t Size() { return finish - start; }

		// 判断是否为空
		bool IsEmpty() { return start == finish; }

	private:
		// 建立结点和中控器
		void CreateMapAndNodes(size_t elemCount)
		{
			// 所需缓存区个数
			size_t nodeCount = elemCount / GetBufferSize() + 1;
			// 中控器大小
			mapSize = nodeCount > 8 ? nodeCount + 2 : 8;	// 中控器最小要存放8个缓存区
			// 申请中控器的空间
			map = Allocator<Pointer>::AllocateRange(mapSize);

			// 将中控器区域移至map的中间
			MapPointer nstart = map + ((mapSize - nodeCount) >> 1);
			MapPointer nfinish = nstart + nodeCount - 1;
			MapPointer cur;
			// 申请缓存区的空间
			for (cur = nstart; cur <= nfinish; cur++)
				*cur = Allocator<ValueType>::AllocateRange(GetBufferSize());

			// 更新当前成员
			start >> nstart;
			finish >> nfinish;
			start.m_cur = start.m_first;
			finish.m_cur = finish.m_first + elemCount % GetBufferSize();
		}

		// 尾部扩容中控器
		void AppendMap(size_t addNodeCount = 1, bool isAddFront = true)
		{
			// 新中控器大小计算
			size_t newMapSize = mapSize + Algorithm::Max(mapSize, addNodeCount) + 2;
			size_t oldNumNodes = finish.m_node - start.m_node + 1;
			size_t newNumNodes = oldNumNodes + addNodeCount;

			// 申请新中控器的空间
			MapPointer newMap = Allocator<Pointer>::AllocateRange(newMapSize);
			MapPointer newNstrart = newMap + ((newMapSize - newNumNodes) >> 1) +
				(isAddFront ? addNodeCount : 0);
			
			// 拷贝原map内容
			for (MapPointer i = start.m_node, j = finish.m_node, k = newNstrart;
				i < j + 1; i++, k++) 
			{
				*k = *i;
			}

			// 释放原map
			Allocator<Pointer>::DeallocateRange(map);

			// 更新成员数据
			map = newMap;
			mapSize = newMapSize;
			start >> newNstrart;
			finish >> (newNstrart + oldNumNodes - 1);
		}

	public:
		// 默认构造
		Deque() { CreateMapAndNodes(0); }

		// 填充构造
		Deque(int elemCount, const ValueType& val) 
		{ 
			// 生成结构
			CreateMapAndNodes(elemCount); 
			
			// 填充
			for (Iterator iter = start; iter != finish; iter++)
				*(iter.m_cur) = val;
		}

		// TODO: 拷贝构造

		// TODO: 赋值拷贝

		// 析构
		~Deque()
		{
			// 释放缓存区
			for (MapPointer p = start.m_node; p < finish.m_node + 1; p++)
				Allocator<ValueType>::DeallocateRange(*p);

			// 释放中控器
			Allocator<Pointer>::DeallocateRange(map);
			map = nullptr;
		}

		// 尾插
		void PushBack(const ValueType& val)
		{
			// 最后缓冲区有两个及以上的备用缓冲区空间
			if (finish.m_cur != finish.m_last - 1)
			{
				*(finish.m_cur) = val;
				++(finish.m_cur);
			}
			// 仅剩余一个备用缓冲区空间
			else
			{
				// 中控器空间不足
				if (finish.m_node - map == mapSize - 1)
				{
					// 扩容map
					AppendMap(1, false);
				}

				// 构建新的缓冲区
				*(finish.m_node + 1) = Allocator<ValueType>::AllocateRange(GetBufferSize());
				*(finish.m_cur) = val;
				// 更新迭代器
				finish >> (finish.m_node + 1);
				finish.m_cur = finish.m_first;
			}
		}

		// 头插
		void PushFront(const ValueType& val)
		{
			// 第一缓冲区有备用缓冲区空间
			if (start.m_cur != start.m_first)
			{
				*(start.m_cur - 1) = val;
				start.m_cur--;
			}
			// 第一缓冲区无备用缓冲区空间
			else
			{
				// 中控器空间不足
				if (start.m_node == map)
				{
					// 扩容map
					AppendMap();
				}

				*(start.m_node - 1) = Allocator<ValueType>::AllocateRange(GetBufferSize());
				start >> (start.m_node - 1);
				start.m_cur = start.m_last - 1;
				*(start.m_cur) = val;
			}
		}

		// 尾删元素
		ValueType PopBack()
		{
			// 缓冲区有1个以上的元素
			if (finish.m_cur != finish.m_first)
			{
				--finish.m_cur;
				ValueType res = *finish;
				return res;
			}
			// 最后缓冲区无任何元素
			else
			{
				// 释放缓冲区
				Allocator<ValueType>::DeallocateRange(finish.m_cur);
				finish >> (finish.m_node - 1);
				finish.m_cur = finish.m_last - 1;
				ValueType res = *finish;
				return res;
			}
		}

		// 头删元素
		ValueType PopFront()
		{
			// 第一缓冲区有两个以上元素
			if (start.m_cur != start.m_last - 1)
			{
				ValueType res = *start;
				++start.m_cur;
				return res;
			}
			// 第一缓冲区仅含一个元素
			else
			{
				ValueType res = *start;
				Allocator<ValueType>::DeallocateRange(start.m_first);
				start >> (start.m_node + 1);
				start.m_cur = start.m_first;
				return res;
			}
		}

		// TODO: Insert | Erase
	};
}