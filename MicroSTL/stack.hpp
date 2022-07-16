#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define STACK

#ifndef DEQUE
#include "deque.hpp"
#endif // !DEQUE


namespace mstl_itm
{
	template <class _ValueT>
	class Stack
	{
	public:
		using ValueType = _ValueT;		// 容器元素值
		using Reference = _ValueT&;	// 容器元素引用

	private:
		Deque<ValueType> base;	// 底层容器

	public:
		// 栈是否为空
		bool IsEmpty() { return base.IsEmpty(); }
		
		// 栈大小
		size_t Size() { return base.Size(); }

		// 栈顶元素
		Reference Top() { return base.Back(); }

		// 压栈
		void Push(const ValueType& val) { base.PushBack(val); }

		// 弹栈
		ValueType Pop() { return base.PopBack(); }
	};
}