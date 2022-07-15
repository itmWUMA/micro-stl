#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define TEST

#ifndef ALLOCATOR
#include "allocator.hpp"
#endif // !ALLOCATOR
#ifndef VECTOR
#include "vector.hpp"
#endif // !VECTOR
#ifndef LIST
#include "list.hpp"
#endif // !LIST
#ifndef DEQUE
#include "deque.hpp"
#endif // !DEQUE


#include <iostream>
#include <string>
#include <random>
#include <Windows.h>
using namespace std;
using namespace mstl_itm;

class Test
{

private:
	// 打字机效果
	static void DelayPrintLine(const string& str, DWORD delayTime = 80)
	{
		for (auto ch : str)
		{
			cout << ch;
			Sleep(delayTime);
		}
		cout << endl;
	}

	// 清空并暂停
	static void CleanAndPause()
	{
		system("pause");
		system("cls");
	}

	// 打印主界面
	static void PrintMainInterface()
	{
		cout << "================= MicroSTL =================" << endl;
		Sleep(200);
		cout << "         [1] vector" << '\t' << "[2] list" << endl;
		Sleep(200);
		cout << "         [3] deque" << '\t' << "[4] stack" << endl;
		Sleep(200);
		cout << "         [5] queue" << '\t' << "[6] sortedset" << endl;
		Sleep(200);
		cout << "         [7] sortedmap" << '\t' << "[8] hashset" << endl;
		Sleep(200);
		cout << "         [9] hashmap" << '\t' << "[0] exit" << endl;
		Sleep(200);
		cout << "               " << "\t\t" << "Designed by itmWuma" << endl;
		Sleep(200);
		cout << "=============================================" << endl;
	}

	// 打印界面
	static void PrintHello()
	{
		DelayPrintLine("Welcome to MicroSTL");
		Sleep(1000);
		DelayPrintLine("This is a test program, which you can test all functions in the project");
		Sleep(1000);
		DelayPrintLine("Choose test items according to following options: ");
		Sleep(1000);
		PrintMainInterface();
	}

	// 随机字符串
	static string GetRandStr(int len)
	{
		string buffer;
		for (int i = 0; i < len; i++)
			buffer += (char)(rand() % 26 + 65);
		return buffer;
	}

	// 测试用自定义类型
	class TestType
	{
	public:
		int i;
		double d;
		string str;

		TestType() : i(0), d(0), str("") {}
		TestType(int i, double d, string str) : i(i), d(d), str(str) {}

		bool operator<(const TestType& tt) const
		{
			if (this->i != tt.i)
				return this->i < tt.i;
			else if (this->d != tt.d)
				return this->d < tt.d;
			else
				return this->str < tt.str;
		}

		bool operator>(const TestType& tt) const
		{
			return !(*this < tt);
		}

		bool operator==(const TestType& tt) const
		{
			return (i == tt.i && d == tt.d && str == tt.str);
		}

		bool operator!=(const TestType& tt) const
		{
			return !(*this == tt);
		}

		// 生成随机值
		static TestType GenerateRand()
		{
			int ir = rand() % 101;
			double dr = (double)(rand() % 101);
			return TestType(ir, dr, GetRandStr(5));
		}
	};

	friend ostream& operator<<(ostream&, const Test::TestType&);

	static void TestVector()
	{
		system("cls");

		Vector<TestType> v;

		// 生成随机值并打印
		cout << "Push 10 random elements : " << endl;
		for (int i = 0; i < 10; i++)
		{
			Sleep(100);
			TestType randTT = TestType::GenerateRand();
			cout << randTT << endl;
			v.PushBack(randTT);
		}

		// 插入元素
		Sleep(1000);
		cout << "Insert one element at [1]..." << endl;
		v.Insert(1, TestType(1, 1.5, "INSERT_ELEMENT"));

		// 打印vector
		Sleep(1000);
		cout << "vector: \n[ " << endl;
		for (auto iter = v.Begin(); iter != v.End(); iter++)
			cout << *iter << "," << endl;
		cout << " ]\n";

		// 显示vector属性
		Sleep(1000);
		cout << endl;
		cout << "size = " << v.Size() << endl;
		cout << "capcity = " << v.Capcity() << endl;
		cout << "isEmpty = " << (v.IsEmpty() ? "TRUE" : "FALSE") << endl;
		cout << "front = " << v.Front() << endl;
		cout << "back = " << v.Back() << endl;

		// 删除元素
		cout << endl;
		Sleep(1000);
		cout << "Now let's pop back..." << endl;
		for (int i = 0; i < 3; i++)
		{
			Sleep(500);
			cout << "pop back elem : " << v.PopBack() << endl;
		}
		Sleep(1000);
		cout << "Now let's erase elem at [1]..." << endl;
		for (int i = 0; i < 3; i++)
		{
			Sleep(100);
			cout << "earse elem : " << v.Erase(1) << endl;
		}
		Sleep(1000);
		cout << endl;
		cout << "current vector: \n[ " << endl;
		for (auto iter = v.Begin(); iter != v.End(); iter++)
			cout << *iter << "," << endl;
		cout << " ]\n";

		// 清空元素
		cout << endl;
		Sleep(1000);
		cout << "Clear all elements : " << endl;
		v.Clear();
		Sleep(1000);
		cout << "Then resize vector : " << endl;
		v.Resize(50);
		for (auto iter = v.Begin(); iter != v.End(); iter++)
			cout << *iter << "," << endl;
		cout << " ]\n";


		system("pause");
		system("cls");
	}

	static void TestList()
	{
		system("cls");

		List<TestType> l;

		// 生成随机值并打印
		cout << "Push 10 random elements : " << endl;
		for (int i = 0; i < 10; i++)
		{
			Sleep(100);
			TestType randTT = TestType::GenerateRand();
			cout << randTT << endl;
			l.PushBack(randTT);
		}

		// 插入元素
		Sleep(1000);
		cout << "Insert one element at [1]..." << endl;
		l.Insert(++(l.Begin()), TestType(1, 1.5, "INSERT_ELEMENT"));
		Sleep(500);
		cout << "Push front one element..." << endl;
		l.PushFront(TestType(-5, 3.14, "PUSH_FRONT_ELEMENT"));
		l.PushFront(TestType(-5, 3.14, "PUSH_FRONT_ELEMENT"));
		l.PushFront(TestType(-5, 3.14, "PUSH_FRONT_ELEMENT"));

		// 打印list
		Sleep(1000);
		cout << "list: \n[ " << endl;
		for (auto iter = l.Begin(); iter != l.End(); iter++)
			cout << *iter << "->" << endl;
		cout << " ]\n";

		// 显示list属性
		Sleep(1000);
		cout << endl;
		cout << "size = " << l.Size() << endl;
		cout << "isEmpty = " << (l.IsEmpty() ? "TRUE" : "FALSE") << endl;
		cout << "front = " << l.Front() << endl;
		cout << "back = " << l.Back() << endl;

		// 删除元素
		cout << endl;
		Sleep(1000);
		cout << "Now let's erase element at [1]..." << endl;
		l.Erase(++(l.Begin()));
		Sleep(500);
		cout << "Then let's pop front element..." << endl;;
		TestType res = l.PopFront();
		cout << "pop front element = " << res << endl;
		Sleep(500);
		cout << "And then let's pop back element..." << endl;
		res = l.PopBack();
		cout << "pop back element = " << res << endl;
		Sleep(500);
		cout << "Remove elements..." << endl;
		l.Remove(TestType(-5, 3.14, "PUSH_FRONT_ELEMENT"));
		cout << endl;
		cout << "current vector: \n[ " << endl;
		for (auto iter = l.Begin(); iter != l.End(); iter++)
			cout << *iter << "->" << endl;
		cout << " ]\n";

		system("pause");
		system("cls");
	}

	static void TestDeque()
	{
		system("cls");

		Deque<TestType> dq;

		// 生成随机值并打印
		cout << "Push 10 random elements : " << endl;
		for (int i = 0; i < 10; i++)
		{
			Sleep(100);
			TestType randTT = TestType::GenerateRand();
			cout << randTT << endl;
			dq.PushBack(randTT);
		}

		// 插入元素
		Sleep(1000);
		cout << "Insert one element at front..." << endl;
		dq.PushFront(TestType(23, 33.3, "PUSH_FRONT"));

		// 打印deque
		Sleep(1000);
		cout << "deque: \n[ " << endl;
		for (auto iter = dq.Begin(); iter != dq.End(); iter++)
			cout << *iter << "," << endl;
		cout << " ]\n";

		// 显示deque属性
		Sleep(1000);
		cout << endl;
		cout << "size = " << dq.Size() << endl;
		cout << "isEmpty = " << (dq.IsEmpty() ? "TRUE" : "FALSE") << endl;
		cout << "front = " << dq.Front() << endl;
		cout << "back = " << dq.Back() << endl;
		cout << "dq[5] = " << dq[5] << endl;

		// 删除元素
		cout << endl;
		Sleep(1000);
		cout << "Now let's pop back elements..." << endl;
		TestType res = dq.PopBack();
		cout << "pop back element = " << res << endl;
		Sleep(500);
		cout << "Now let's pop front elements..." << endl;
		res = dq.PopFront();
		cout << "pop front element = " << res << endl;

		system("pause");
		system("cls");
	}

	static void TestStack()
	{

	}

	static void Queue()
	{

	}

	static void TestSortedset()
	{

	}

	static void TestSortedmap()
	{

	}

	static void TestHashset()
	{

	}

	static void TestHashmap()
	{

	}

public:
	// 测试启动接口
	static void StartTest()
	{
		srand((unsigned int)time(NULL));

		//PrintHello();
		int ipt = 0;
		do
		{
			cout << "> ";
			cin >> ipt;
			switch (ipt)
			{
			case 1:	// vector
				TestVector();
				PrintMainInterface();
				break;
			case 2:	// list
				TestList();
				PrintMainInterface();
				break;
			case 3:	// deque
				TestDeque();
				PrintMainInterface();
				break;
			case 4:	// stack

				break;
			case 5:	// queue

				break;
			case 6:	// sortedset

				break;
			case 7:	// sortedmap

				break;
			case 8:	// hashset

				break;
			case 9:	// hashmap

				break;
			case 0:	// exit
				system("cls");
				cout << "GOODBYE~~" << endl;
				break;
			default:	// ERROR
				cout << "the number is wrong, please try again" << endl;
				break;
			}
		} while (ipt);

		system("pause");
	}
};

::ostream& operator<<(::ostream& cout, const Test::TestType& tt)
{
	cout << "{" << tt.i << ", " << tt.d << ", " << tt.str << "}";
	return cout;
}