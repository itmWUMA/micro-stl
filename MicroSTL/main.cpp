#define _CRT_SECURE_NO_WARNINGS
#include "test.hpp"
#include <vector>
#include "iterator.hpp"

// Inner Test
int main()
{
	cout << typeid(IteratorTraits<RandomAcessIterator<double>>::IterType).name()
		<< endl;

	return 0;
}

//int main()
//{
//	Test::StartTest();
//
//	return 0;
//}