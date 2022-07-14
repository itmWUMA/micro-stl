#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define DEQUE

#ifndef ITERATOR
#include "iterator.hpp"
#endif // !ITERATOR


namespace mstl_itm
{
	template <class _ValueT, size_t _BufSize = 0>
	class Deque
	{
	public:
		using ValueType = _ValueT;		// 元素类型
		using Pointer	 = _ValueT*;	// 元素类型指针
		using Reference = _ValueT&;	// 元素类型引用

	private:
		using MapPointer = Pointer*;	// 中控器指针

	private:
		MapPointer map;	// 中控器
		size_t mapSize;	// 中控器最多存放指针的个数

	private:
		// 计算缓冲区元素个数
		size_t GetBufferSize()
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

			Iterator& operator+=(size_t n)
			{
				size_t offset = n + (m_cur - m_first);
				// 目标在同一缓存区
				if (offset >= 0 && offset < GetBufferSize())
					m_cur += n;
				// 目标不在同一缓存区
				else
				{
					size_t nodeOffset = offset > 0 ? offset / GetBufferSize() :
						-((-offset - 1) / GetBufferSize()) - 1;
					// 跳到正确的缓存区
					operator>>(m_node + nodeOffset);
					// 切换至正确的元素
					m_cur = m_first + (offset - nodeOffset * GetBufferSize());
				}

				return *this;
			}

			Iterator operator+(size_t n) const
			{
				Iterator temp = *this;
				return temp += n;
			}

			Iterator& operator-=(size_t n)
			{
				return *this += -n;
			}

			Iterator operator-(size_t n) const
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
	};
}