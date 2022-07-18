// 封装一些常用的仿函数，包括关系类仿函数和哈希函数
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define FUNCTOR

#include <functional>

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

	// 哈希函数
	template <typename T>
	void CombineHash(size_t& seed, const T& t)
	{
		seed ^= std::hash<T>()(t) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	}

	template <typename T>
	void GetHash(size_t& seed, const T& t)
	{
		CombineHash(seed, t);
	}

	template <typename T, typename... _Types>
	void GetHash(size_t& seed, const T& t, const _Types&... types)
	{
		CombineHash(seed, t);
		GetHash(seed, types...);
	}

	template <typename... _Types>
	size_t GetHash(const _Types&... types)
	{
		size_t seed = 0;
		GetHash(seed, types...);
		return seed;
	}
}