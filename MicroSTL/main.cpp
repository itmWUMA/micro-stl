#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "test.hpp"
#include "vector.hpp"
#include "list.hpp"
//#include <vector>

 //Inner Test
int main()
{
	List<int> l;
	l.Size();
	l.IsEmpty();
	l.Begin();
	l.End();

	return 0;
}

//int main()
//{
//	Test::StartTest();
//
//	return 0;
//}