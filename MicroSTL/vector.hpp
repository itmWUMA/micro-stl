#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define VECTOER

#include "allocator.hpp"
#include "iterator.hpp"

namespace mstl_itm
{
	template <class _ValueT>
	class Vector
	{
	public:
		using ValueType = _ValueT;		// 元素类型
		using Pointer = _ValueT*;		// 元素类型指针
		using Reference = _ValueT&;
		using DifferenceType = size_t;		// 指针距离类型
		using Iterator = Pointer;		// Vector迭代器

	private:
		Iterator m_start;				// 目前使用空间的头部
		Iterator m_finish;			// 目前使用空间的尾部
		Iterator m_endOfStorage;	// 目前可用空间的尾部

	public:
		// 默认构造
		Vector()
		{
			Pointer p = Allocator<ValueType>::AllocateRange(1);
			m_start = p;
			m_finish = p;
			m_endOfStorage = p + 1;
		}

		// 指定容量构造
		Vector(int capcity)
		{
			Pointer p = Allocator<ValueType>::AllocateRange(capcity);
			m_start = p;
			m_finish = p;
			m_endOfStorage = p + capcity;
		}

		// 区间构造
		Vector(InputIterator<ValueType> first, InputIterator<ValueType> last)
		{
			DifferenceType cap = last - first;
			Pointer p = Allocator<ValueType>::AllocateRange(cap);
			m_start = p;
			m_finish = p;
			m_endOfStorage = p + cap;

			for (auto iter = first; iter != last; iter++, m_finish++)
				*m_finish = *iter;
		}

		// 拷贝构造
		Vector(const Vector& v)
		{
			DifferenceType cap = v.m_endOfStorage - v.m_start;
			Pointer p = Allocator<ValueType>::AllocateRange(cap);
			m_start = p;
			m_finish = p;
			m_endOfStorage = p + cap;

			for (auto iter = v.m_start; iter != v.m_finish; iter++, m_finish++)
				*m_finish = *iter;
		}

		// 析构
		~Vector()
		{
			Allocator<ValueType>::DeallocateRange(m_start);
			m_start = nullptr;
			m_endOfStorage = nullptr;
			m_finish = nullptr;
		}

		// 获取起始迭代器
		Iterator Begin() { return m_start; }

		// 获取结束迭代器
		Iterator End() { return m_finish; }

		// 获取数组大小
		size_t Size() { return m_finish - m_start; }

		// 获取数组容量
		size_t Capcity() { return m_endOfStorage - m_start; }

		// 判断数组是否为空
		bool IsEmpty() { return (m_start == m_finish); }

		// 获取首元素
		ValueType Front() { return *m_start; }

		// 获取末元素
		ValueType Back() { return *(m_finish - 1); }

		// 索引器
		Reference operator[](size_t index) { return *(m_start + index); }

	private:
		// vector扩容机制
		void _Append()
		{
			size_t cap = Capcity();
			Allocator<ValueType>::Append(m_start, cap, 2 * cap);
			// 更新3根指针
			m_finish = m_start + cap;
			m_endOfStorage = m_start + 2 * cap;
		}

	public:
		// 添加元素
		void PushBack(const ValueType& elem)
		{
			// 数组满员
			if (Size() == Capcity())
			{
				// 扩容
				_Append();
			}
			*m_finish = elem;
			m_finish++;
		}

		// 插入元素
		void Insert(int pos, const ValueType& elem)
		{
			if (pos < 0 || pos > (int)this->Size()) throw;
			// 数组满员
			if (Size() == Capcity())
			{
				// 扩容
				_Append();
			}

			// 向后搬运
			Iterator iter = m_finish;
			for (int i = this->Size(); i > pos; i--, iter--)
				*iter = *(iter - 1);
			// 插入元素
			*(m_start + pos) = elem;
			// 更新指针
			m_finish++;
		}

		// 删除尾部元素
		ValueType PopBack()
		{
			if (IsEmpty())	throw;
			return *--m_finish;
		}

		// 删除元素
		ValueType Erase(int pos)
		{
			if (pos < 0 || pos > (int)this->Size() || IsEmpty()) throw;
			ValueType res = *(m_start + pos);
			// 向前搬运
			for (auto iter = m_start + pos; iter != m_finish - 1; iter++)
				*iter = *(iter + 1);
			// 更新指针
			m_finish--;
			
			return res;
		}
	};
}