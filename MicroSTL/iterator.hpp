// 迭代器接口: 用以定义4种迭代器类型与相关关系
#define _CRT_SECURE_NO_WARNINGS

namespace mstl_itm
{
	template <class _ValueT>
	class InputIterator
	{
	public:
		using ValueType		= _ValueT;	// 迭代器指向值的类型
		using IterType			= InputIterator;
	};

	// 单向访问迭代器类型
	template <class _ValueT>
	class ForwardIterator : public InputIterator<_ValueT>
	{
	public:
		using IterType			= ForwardIterator;
	};

	// 双向访问迭代器类型
	template <class _ValueT>
	class BidirectionalIterator : public ForwardIterator<_ValueT>
	{
	public:
		using IterType			= BidirectionalIterator;
	};

	// 随机访问迭代器类型
	template <class _ValueT>
	class RandomAcessIterator : public BidirectionalIterator<_ValueT>
	{
	public:
		using IterType			= RandomAcessIterator;
	};

	// 迭代器特性提取器
	template <class _Iter>
	class IteratorTraits
	{
	public:
		using ValueType			= typename _Iter::ValueType;	// 迭代器指向值的类型
		using IterType				= typename _Iter::IterType;	// 迭代器类型
		using DifferenceType		= size_t;	// 迭代器相距距离类型
	};

	template <class _Iter>
	class IteratorTraits<_Iter*>
	{
	public:
		using ValueType		= _Iter;
		using IterType			= RandomAcessIterator<ValueType>;
		using DifferenceType = size_t;
	};
}