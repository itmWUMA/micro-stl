#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "test.hpp"
//#include <vector>
#include "vector.hpp"

// Inner Test
int main()
{
	//Vector<int> v;
	Vector<int> v(10);


	for (auto i : { 1,2,3,4,5,6,7,8,9,10 })
		v.PushBack(i);
	for (size_t i = 0; i < 10; i++)
		cout << v[i] << endl;
	v.Size();
	v.Begin();
	v.End();
	v.IsEmpty();
	v.Capcity();
	v.PushBack(11);
	v[10];
	return 0;
}

//int main()
//{
//	Test::StartTest();
//
//	return 0;
//}