// 封装一些常用的仿函数，包括关系类仿函数和哈希函数
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define FUNCTOR

namespace mstl_itm
{
	template <class _ValueT>
	struct Less
	{
		bool operator()(const _ValueT& t1, const _ValueT& t2) const { return t1 < t2; }
	};

	template <class _ValueT>
	struct Greater
	{
		bool operator()(const _ValueT& t1, const _ValueT& t2) const { return t1 > t2; }
	};
}