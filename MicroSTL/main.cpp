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
	v.Size();
	v.Begin();
	v.End();
	v.IsEmpty();
	v.Capcity();
	return 0;
}

//int main()
//{
//	Test::StartTest();
//
//	return 0;
//}