// 算法: 用以实现对容器操作的各类算法
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define ALGORITHM

#ifndef ITERATOR
#include "iterator.hpp"
#endif // !ITERATOR

namespace mstl_itm
{
	class Algorithm
	{
	public:
		// 获取迭代器间距离
		template <typename _InputIter>
		static typename IteratorTraits<_InputIter>::DifferenceType
			Distance(_InputIter first, _InputIter last)
		{
			typename IteratorTraits<_InputIter>::DifferenceType count = 0;
			// 逐一累计距离
			while (first != last)
			{
				first++;
				count++;
			}
			return count;
		}
	};
}