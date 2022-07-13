#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define LIST

#ifndef ALLOCATOR
#include "allocator.hpp"
#endif // !ALLOCATOR
#ifndef ITERATOR
#include "iterator.hpp"
#endif // !ITERATOR
#ifndef ALGORITHM
#include "algorithm.hpp"
#endif // !ALGORITHM

namespace mstl_itm
{
	template <class _ValueT>
	class List
	{
	public:
		using ValueType = _ValueT;		// 元素类型
		using Reference = _ValueT&;	// 元素引用类型
		using Pointer = _ValueT*;	// 元素指针类型

	private:
		// 链表结点
		struct ListNode
		{
			using NodePtr = ListNode*;	// 结点指针类型

			NodePtr next;		// 后指针
			NodePtr prior;		// 前指针
			ValueType data;	// 元素值

			ListNode() : next(nullptr), prior(nullptr), data(ValueType()) {}
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

	private:
		NodePtr dummyHead;	// 链表的头结点

	public:
		// 获取起始迭代器
		Iterator Begin() { return Iterator(dummyHead->next); }

		// 获取终止迭代器
		Iterator End() { return Iterator(dummyHead); }

		// 判断是否为空
		bool IsEmpty() { return dummyHead->next == dummyHead; }

		// 获取链表元素个数
		size_t Size() { return Algorithm::Distance(Begin(), End()); }

		// 首元素
		Reference Front() { return *Begin(); }

		// 尾元素
		Reference Back() { return *(--End()); }

	private:
		// 申请一个结点
		NodePtr CreateNode() { return Allocator<ListNode>::Allocate(); }
		NodePtr CreateNode(const ValueType& elem)
		{
			NodePtr p = CreateNode();
			p->data = elem;
			return p;
		}

		// 释放一个结点
		void DeleteNode(NodePtr p) { Allocator<ListNode>::Deallocate(p); }

	public:
		// 默认构造
		List()
		{
			dummyHead = CreateNode();
			dummyHead->next = dummyHead;
			dummyHead->prior = dummyHead;
		}

		// 清空链表
		void Clear()
		{
			NodePtr curNode = dummyHead->next, nextNode;
			// 依次释放后续结点
			while (curNode != dummyHead)
			{
				nextNode = curNode->next;
				DeleteNode(curNode);
				curNode = nextNode;
			}
			dummyHead->next = dummyHead;
			dummyHead->prior = dummyHead;
		}

		// 析构
		~List()
		{
			// 清空
			Clear();
			// 释放dummyHead
			DeleteNode(dummyHead);
			dummyHead = nullptr;
		}

		// 插入结点
		Iterator Insert(Iterator pos, const ValueType& val)
		{
			// 创建结点
			NodePtr newNode = CreateNode(val);
			// 调整指针
			newNode->next = pos.node;
			newNode->prior = (pos.node)->prior;
			newNode->prior->next = newNode;
			(pos.node)->prior = newNode;
			return Iterator(newNode);
		}

		// 尾插结点
		void PushBack(const ValueType& val) { Insert(End(), val); }

		// 头插结点
		void PushFront(const ValueType& val) { Insert(Begin(), val); }

		// 擦除结点
		Iterator Erase(Iterator pos)
		{
			NodePtr priorNode = (pos.node)->prior;
			NodePtr nextNode = (pos.node)->next;
			priorNode->next = nextNode;
			nextNode->prior = priorNode;
			DeleteNode(pos.node);
			return Iterator(nextNode);
		}

		// 尾删
		ValueType PopBack()
		{
			Iterator temp = End();
			ValueType res = (--temp).node->data;
			Erase(temp);
			return res;
		}

		// 头删
		ValueType PopFront()
		{
			Iterator temp = Begin();
			ValueType res = temp.node->data;
			Erase(temp);
			return res;
		}

		// 移除指定元素
		void Remove(const ValueType& elem)
		{
			for (auto iter = Begin(); iter != End();)
			{
				if ((iter.node)->data == elem)
					iter = Erase(iter);
				else
					iter++;
			}
		}
	};
}