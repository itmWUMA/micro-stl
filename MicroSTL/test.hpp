#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;

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

	// 打印界面
	static void PrintHello()
	{
		DelayPrintLine("Welcome to MicroSTL");
		Sleep(1000);
		DelayPrintLine("This is a test program, which you can test all functions in the project");
		Sleep(1000);
		DelayPrintLine("Choose test items according to following options: ");
		Sleep(1000);
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

public:
	// 测试启动接口
	static void StartTest()
	{
		PrintHello();
		int ipt = 0;
		do
		{
			cout << "> ";
			cin >> ipt;
			switch (ipt)
			{
			case 1:	// vector
				break;
			case 2:	// list
				break;
			case 3:	// deque
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