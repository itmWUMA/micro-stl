// 内部实现：堆结构
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define HEAP

#ifndef VECTOR
#include "vector.hpp"
#endif // !VECTOR
#ifndef FUNCTOR
#include "functor.hpp"
#endif // !FUNCTOR
#ifndef ALGORITHM
#include "algorithm.hpp"
#endif // !ALGORITHM

#include <stdexcept>

namespace mstl_itm
{
	template <class _ValueT, class _Cmp = Less<_ValueT>>
	class Heap
	{
	public:
		using ValueType = _ValueT;		// 元素值
		using Reference = _ValueT&;	// 元素引用
		using Comparator = _Cmp;		// 比较器

	private:
		Vector<ValueType> base;		// 底层结构由vector支持

	public:
		// 堆大小
		size_t Size() { return base.Size(); }

		// 是否为空
		bool IsEmpty() { return base.IsEmpty(); }

		// 拿到堆顶元素
		Reference Top() { return base[0]; }

	private:
		// 堆化
		void Heapify(size_t pos)
		{
			size_t left = 2 * pos + 1, right = left + 1;
			size_t heapSize = Size();

			while (left < heapSize)
			{
				// 左右子树PK
				size_t winIndex = (right < heapSize && (Comparator()(base[left], base[right]))) ?
					right : left;
				// 胜者与当前数据PK
				winIndex = (Comparator()(base[pos], base[winIndex])) ? winIndex : pos;
				if (winIndex == pos)
					return;
				// 当前元素下潜
				Algorithm::Swap(base[pos], base[winIndex]);
				pos = winIndex;
				left = pos * 2 + 1;
				right = left + 1;
			}
		}

		// 插入堆
		void InsertHeap(const ValueType& val)
		{
			base.PushBack(val);
			size_t heapSize = Size();
			int cur = heapSize - 1,
				parent = (cur - 1) / 2;
			while (parent != cur)
			{
				if (Comparator()(base[cur], base[parent]))
					return;
				Algorithm::Swap(base[parent], base[cur]);
				cur = parent;
				parent = (cur - 1) / 2;
			}
		}

	public:
		// 入堆
		void Push(const ValueType& val) { InsertHeap(val); }

		// 出堆
		ValueType Pop()
		{
			if (IsEmpty())
				throw runtime_error("Heap is empty!");

			ValueType res = Top();
			Algorithm::Swap(base[0], base[Size() - 1]);
			base.PopBack();
			// 重新堆化
			Heapify(0);

			return res;
		}
	};
}
