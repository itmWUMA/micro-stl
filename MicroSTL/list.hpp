#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define LIST

#include "allocator.hpp"
#include "iterator.hpp"

namespace mstl_itm
{
	template <class _ValueT>
	class List
	{
	public:
		using ValueType = _ValueT;		// 元素类型
		using Reference = _ValueT&;	// 元素引用类型
		using Pointer	 = _ValueT*;	// 元素指针类型

	private:
		// 链表结点
		struct ListNode
		{
			using NodePtr = ListNode*;	// 结点指针类型

			NodePtr next;		// 后指针
			NodePtr prior;		// 前指针
			ValueType data;	// 元素值
		};

		// 链表迭代器
		struct ListIterator : public BidirectionalIterator<ValueType>
		{
			using ValueType = ValueType;
			using NodePtr = ListNode*;

			NodePtr node;	// 迭代器内存在一个指针，指向链表结点

			ListIterator(NodePtr node) : node(node) {}
			ListIterator() : node(nullptr) {}
			ListIterator(const ListIterator& iter) : node(iter.node) {}

			bool operator==(const ListIterator& iter) const { return node == iter.node; }
			bool operator!=(const ListIterator& iter) const { return !(*this == iter); }

			// *iterator => 拿到结点的data
			Reference operator*() const { return (*node).data; }
			Pointer operator->() const { return &(operator*()); }

			// 前置++
			ListIterator& operator++()
			{
				node = node->next;
				return *this;
			}
			// 后置++
			ListIterator operator++(int)
			{
				ListIterator temp = *this;
				node = node->next;
				return temp;
			}
			// 前置--
			ListIterator& operator--()
			{
				node = node->prior;
				return *this;
			}
			// 后置--
			ListIterator operator--(int)
			{
				ListIterator temp = *this;
				node = node->prior;
				return temp;
			}
		};

	public:
		using NodePtr = ListNode*;		// 结点指针类型
		using Iterator = ListIterator;	// 迭代器
	};
}