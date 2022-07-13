#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "test.hpp"
#include "vector.hpp"
#include "list.hpp"
//#include <vector>

 //Inner Test
void Test()
{
	List<int> l;
	l.PushBack(10);
	l.Size();
	l.IsEmpty();
	l.Begin();
	l.End();
	l.Front();
}

int main()
{
	Test();

	return 0;
}

//int main()
//{
//	Test::StartTest();
//
//	return 0;
//}