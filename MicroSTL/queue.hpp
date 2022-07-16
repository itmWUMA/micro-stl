#define _CRT_SECURE_NO_WARNINGS
#define QUEUE

#ifndef DEQUE
#include "deque.hpp"
#endif // !DEQUE


namespace mstl_itm
{
	template <class _ValueT>
	class Queue
	{
	public:
		using ValueType = _ValueT;		// 容器元素值
		using Reference = _ValueT&;	// 容器元素引用

	private:
		Deque<ValueType> base;	// 底层容器

	public:
		// 队列是否为空
		bool IsEmpty() { return base.IsEmpty(); }

		// 队列大小
		size_t Size() { return base.Size(); }

		// 队首元素
		Reference Top() { return base.Front(); }

		// 队尾元素
		Reference Back() { return base.Back(); }

		// 入队
		void Enqueue(const ValueType& val) { base.PushBack(val); }

		// 出队
		ValueType Dequeue() { return base.PopFront(); }
	};
}