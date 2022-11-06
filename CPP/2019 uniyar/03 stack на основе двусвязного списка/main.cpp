#include <fstream>
#include <stack>
#include <windows.h>
#include <string>
#include "MyStack.h"


using namespace std;

char menu(); char choice = 0;
void FileCheck(ifstream& file);
void inputStack(ifstream& file, MyStack& MyStack, stack <int>& Stack, int& Instruction, int& Count, int& ZeroCount,
	int& NegCount, int& Value, int& N);
void Sort(ifstream& file, MyStack& MyStack, stack <int>& Stack, int& Instruction, int& Count, int& ZeroCount,
	int& NegCount, int& Value, int& N);
int MinS(int* val);
int MaxS(int* val);
int MaxSS(int* val);




int main()
{
	SetConsoleCP(1251); SetConsoleOutputCP(1251);
	int Instruction = 0; int Count = 0; int ZeroCount = 0; int NegCount = 0; int Value = 0; int N = 0;
	do
	{
		system("cls");

		stack <int> Stack;
		MyStack MyStack;
		ifstream file1("C:\\Users\\ilyat\\Desktop\\Zapov\\VS\\Project4.2\\Project4.2\\txt.txt");
		ifstream file2("C:\\Users\\ilyat\\Desktop\\Zapov\\VS\\Project4.2\\Project4.2\\txt.txt");
		cout << endl;
		choice = menu();
		switch (choice)
		{
		case '1':

			FileCheck(file1);
			Instruction = 1;

			inputStack(file2, MyStack, Stack, Instruction, Count, ZeroCount, NegCount, Value, N);
			if (ZeroCount == Count) { cout << "Все числа есть нули\n"; system("pause"); }
			else
			{
				Sort(file2, MyStack, Stack, Instruction, Count, ZeroCount, NegCount, Value, N);
			}
			system("pause");
			break;

		case '2':
			FileCheck(file1);
			Instruction = 2;
			inputStack(file2, MyStack, Stack, Instruction, Count, ZeroCount, NegCount, Value, N);
			if (ZeroCount == Count) { cout << "Все числа есть нули\n"; system("pause"); }
			else
			{
				Sort(file2, MyStack, Stack, Instruction, Count, ZeroCount, NegCount, Value, N);
			}
			system("pause");
			break;
		case '0': cout << "Выход"; break;
		default: cout << "Что-то не то введено";
		}


	} while (choice != '0');

	system("pause"); return 0;


}

char menu()
{
	string s;
	cout << "===============================================\n";
	cout << "1. Стеk библиотечный\n"
		<< "2. Стеk самописный\n"
		<< "0. Ливаем нафик\n";
	cout << "===============================================\n";
	cout << "Выбор:"; cin >> s;
	cout << "===============================================\n";
	choice = s[0]; if (s[1]) choice = 'Z';
	return choice;
}

void FileCheck(ifstream& file)
{ // проверка символов на числа
	if (!file.is_open())
	{
		throw 0;
	}
	int Minus = 0;
	for (char Symbol = 0; !file.eof();)
	{
		file >> Symbol;
		if (Symbol == '-')
			Minus++;
		else
			Minus = 0;

		if (Symbol != '0' && Symbol != '1' && Symbol != '2' && Symbol != '3' && Symbol != '4' && Symbol != '5' &&
			Symbol != '6' && Symbol != '7' && Symbol != '8' && Symbol != '9' && Symbol != '-' || Minus == 2)
		{
			throw 1;
		}
	}
	file.close();
}

void inputStack(ifstream& file, MyStack& MyStack, stack <int>& Stack, int& Instruction, int& Count, int& ZeroCount,
	int& NegCount, int& Value, int& N)
{
	file >> N;

	while (!file.eof())
	{
		file >> Value;
		if (Value < 0) NegCount++;
		if (Value == 0) ZeroCount++;
		if (Instruction == 1) Stack.push(Value);
		if (Instruction == 2) MyStack.push(Value);
		Count++;
	}

	if (Stack.size() != N && MyStack.size() != N)
		throw 1;
	if (N < 3)
		throw 2;
}

void Sort(ifstream& file, MyStack& MyStack, stack <int>& Stack, int& Instruction, int& Count, int& ZeroCount,
	int& NegCount, int& Value, int& N)
{
	int MAXPositive, MAXNegative;
	int val[5];
	for (int z = 0; z < 5; z++)
		val[z] = 0;
	if (NegCount != N)
	{
		if (Instruction == 1) {
			while (!Stack.empty())
			{
				cout << Stack.top() << " ";
				if (Stack.top() > val[MinS(val)] && Stack.top() > 0)
					val[MinS(val)] = Stack.top();
				if (Stack.top() < val[MaxS(val)] && Stack.top() < 0)
					val[MaxS(val)] = Stack.top();
				Stack.pop();
			}
		}
		if (Instruction == 2) {
			while (!MyStack.empty())
			{
				cout << MyStack.top() << " ";
				if (MyStack.top() > val[MinS(val)] && MyStack.top() > 0)
					val[MinS(val)] = MyStack.top();
				if (MyStack.top() < val[MaxS(val)] && MyStack.top() < 0)
					val[MaxS(val)] = MyStack.top();
				MyStack.pop();
			}
		}
		cout << endl;
		for (int z = 0; z < 5; z++)
			cout << " " << val[z];
		cout << endl;
		MAXPositive = val[0] * val[1] * val[2];
		MAXNegative = val[3] * val[4] * val[MaxSS(val)];
		if (MAXPositive >= MAXNegative)
		{
			if (MAXPositive > MAXNegative)
				cout << "Максимальное произведение: " << MAXPositive << " " << "Числа: " << val[0] << " " << val[1] << " " << val[2] << " " << endl;
			if (MAXPositive = MAXNegative)
			{
				cout << "Максимальное произведение: " << MAXPositive << " " << "Числа: " << val[0] << " " << val[1] << " "
					<< val[2] << " И " << "Числа: " << val[3] << " " << val[4] << " " << val[MaxSS(val)] << endl;
			}
		}
		else
			cout << "Максимальное произведение: " << MAXNegative << " " << "Числа: " << val[3] << " " << val[4] << " " << val[MaxSS(val)] << " " << endl;
	}
	else
	{
		for (int z = 0; z < 5; z++)
			val[z] = -INT_MAX;
		if (Instruction == 1) {
			while (!Stack.empty())
			{
				cout << Stack.top();
				if (Stack.top() > val[0] || Stack.top() > val[1] || Stack.top() > val[2])
					val[MinS(val)] = Stack.top();
				Stack.pop();
			}
		}
		if (Instruction == 2) {
			while (!MyStack.empty())
			{
				cout << MyStack.top();
				if (MyStack.top() > val[0] || MyStack.top() > val[1] || MyStack.top() > val[2])
					val[MinS(val)] = MyStack.top();
				MyStack.pop();
			}
		}
		cout << endl;
		MAXPositive = val[0] * val[1] * val[2];
		cout << "Максимальное произведение: " << MAXPositive << " " << "Числа: " << val[0] << " " << val[1] << " " <<
			" " << val[2] << " " << endl;
	}
}

int MinS(int* val)
{
	int im = 0;
	for (int i = 0; i < 3; i++)
		if (val[i] < val[im])
			im = i;
	return im;
}
int MaxS(int* val)
{
	int im = 0;
	for (int j = 0; j < 3; j++)
		if (val[j] > val[im])
			im = j;
	return im;
}
int MaxSS(int* val)
{
	int im = 3;
	for (int j = 0; j < 3; j++)
		if (val[j] < val[im])
			im = j;
	return im;
}