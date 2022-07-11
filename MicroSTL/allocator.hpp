#pragma once
// 空间分配器: 用以调度内存
#define _CRT_SECURE_NO_WARNINGS
#define ALLOCATOR

#include <assert.h>
namespace mstl_itm
{
	template <class _AllocT>
	class Allocator
	{
	public:
		using AllocType = _AllocT;	// 类型
		using Pointer = _AllocT*;	// 指针
		using SizeType = size_t;	// 大小类型

	public:
		// 分配一块内存空间
		static Pointer Allocate()
		{
			return new AllocType;
		}

		// 分配连续内存空间
		static Pointer AllocateRange(SizeType size)
		{
			return new AllocType[size];
		}

		// 释放一块内存空间
		static void Deallocate(Pointer p)
		{
			assert(p != nullptr);
			delete p;
		}

		// 释放连续内存空间
		static void DeallocateRange(Pointer p)
		{
			assert(p != nullptr);
			delete[] p;
		}

		// 扩容
		static void Append(Pointer& p, SizeType oldSize, SizeType newSize)
		{
			Pointer newP = AllocateRange(newSize);
			// 拷贝原内容至扩增后空间
			Pointer newIter = newP, oldIter = p;
			for (size_t i = 0; i < oldSize; i++, newIter++, oldIter++)
				*newIter = *oldIter;
			// 销毁原空间
			DeallocateRange(p);
			p = newP;
		}
	};
}