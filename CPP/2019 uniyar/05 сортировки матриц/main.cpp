#include <iostream>
#include <windows.h>
#include <fstream>
#include <conio.h>

using namespace std;

void swapEL(int** ary, int i, int j); // ����� ��� Shaker
void myShakerSort(int** ary, int row, int cols); // ��������� ���������� �������
void ShellSort(int** ary, int row, int cols); // ���������� ������ �����
int** KeyMatrix(int* rows, int* cols); // ���� ������� � ����������
int** FileMatrix(int* rows, int* cols); // ���� ������� �� �����
void LookForMatrix(int** ary, int rows, int cols); // ����� ������� �������
int menu(); char choice; // ����� ���� � ����� ������� � main


int main()
{
	SetConsoleCP(1251); SetConsoleOutputCP(1251);
	int rows = 0, cols = 0;
	int** ary = NULL;
	do {
		system("cls");
		cout << "�������, � ������� ��������: " << endl;
		LookForMatrix(ary, rows, cols);
		choice = menu();
		switch (choice)
		{
		case '0': system("cls"); break;
		case 'A': try { ary = KeyMatrix(&rows, &cols); }
				catch (int f)
				{
					if (f == 1)
					{
						cout << " \n";
						cout << "//////////////////////////////////////////////////////////" << endl;
						cout << "            ������ #" << f << ": " << endl;
						cout << "            �� ����� �������� ��������" << endl;
						cout << " \n";
						cout << "            _������� ������_" << endl;
						cout << "//////////////////////////////////////////////////////////" << endl;

					}
				}
				system("pause");
				break;
		case 'B': try { ary = FileMatrix(&rows, &cols); }
				catch (int f)
				{
					if (f == 1)
					{
						cout << " \n";
						cout << "//////////////////////////////////////////////////////////" << endl;
						cout << "            ������ #" << f << ": " << endl;
						cout << "            �� ����� �������� ��������" << endl;
						cout << " \n";
						cout << "            _������� ������_" << endl;
						cout << "//////////////////////////////////////////////////////////" << endl;

					}
				}
				system("pause");
				break;
		case 'C': LookForMatrix(ary, rows, cols); break;
		case '1':
			cout << "==========================================================" << endl;
			cout << "\t ��������� ���������� ������� �������" << endl;
			cout << "==========================================================" << endl;
			try { myShakerSort(ary, rows, cols); }
			catch (int f)
			{
				if (f == 1)
				{
					cout << " \n";
					cout << "//////////////////////////////////////////////////////////" << endl;
					cout << "            ������ #" << f << ": " << endl;
					cout << "            �� ����� �������� ��������" << endl;
					cout << " \n";
					cout << "            _������� ������_" << endl;
					cout << "//////////////////////////////////////////////////////////" << endl;

				}
			}
			system("pause");
			break;
			cout << "==========================================================" << endl;
		case '2':
			cout << "==========================================================" << endl;
			cout << "\t ���������� ����� ������ �������" << endl;
			cout << "==========================================================" << endl;
			try { ShellSort(ary, rows, cols); }
			catch (int f)
			{
				if (f == 1)
				{
					cout << " \n";
					cout << "//////////////////////////////////////////////////////////" << endl;
					cout << "            ������ #" << f << ": " << endl;
					cout << "            �� ����� �������� ��������" << endl;
					cout << " \n";
					cout << "            _������� ������_" << endl;
					cout << "//////////////////////////////////////////////////////////" << endl;

				}
			}
			system("pause");
			break;
		case '3':
			cout << "==========================================================" << endl;
			cout << "����� �� ���������" << endl; break;
		default: cout << "����!" << endl;
			system("pause"); break;
		}
	} while (choice != '3');

	delete[] ary;
	for (int i = 0; i < rows; i++)
		delete[] ary[i];

	system("pause");
	return 0;
}


void swapEL(int** ary, int i, int j)
{
	int temp;
	temp = ary[i][j];
	ary[i][j] = ary[i - 1][j];
	ary[i - 1][j] = temp;
}

void myShakerSort(int** ary, int rows, int cols)
{
	cout << "���� ��������� �������" << endl;
	LookForMatrix(ary, rows, cols);
	int t;
	if (rows >= 1 || cols >= 1) {

		cout << "������� �������(���������� � �������), ������� ����� �������������: "; cin >> t;
		if ((t > cols) || (t < 1))
		{
			throw 1;
		}
		t--;
		int leftMark = 1;
		int rightMark = rows - 1;
		while (leftMark <= rightMark)
		{
			for (int i = rightMark; i >= leftMark; i--)
				if (ary[i - 1][t] < ary[i][t]) swapEL(ary, i, t);
			leftMark++;

			for (int i = leftMark; i <= rightMark; i++)
				if (ary[i - 1][t] < ary[i][t]) swapEL(ary, i, t);
			rightMark--;
		}

		rightMark = 0;
		cout << "������������� �������� �������: " << endl;
		for (int i = 0; i < rows; i++)
		{
			if (ary[i][t] > 0)
				rightMark += ary[i][t];
			cout << ary[i][t] << endl;
		}

		cout << "����� ������������� ��������� �������: " << rightMark << endl;
		cout << "==========================================================" << endl;
		cout << "\t \t ��� ������: " << endl;
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++)
				cout << ary[i][j] << '\t';
			cout << endl << endl;
		}
		cout << "==========================================================" << endl;
		system("pause");
	}
	else system("pause");
}

void ShellSort(int** ary, int rows, int cols)
{
	cout << "�������, � ������� ��������:" << endl;
	LookForMatrix(ary, rows, cols);
	int i, j, step, st;
	int tmp;

	if (rows >= 1 || cols >= 1) {
		cout << "������� ������(���������� �� �������), ������� ����� �������������: ";
		cin >> st;
		if (st > rows || st < 1)
		{
			throw 1;
		}
		st--;
		for (step = cols / 2; step > 0; step /= 2)
			for (i = step; i < cols; i++)
			{
				tmp = ary[st][i];
				for (j = i; j >= step; j -= step)
				{
					if (tmp < ary[st][j - step])
						ary[st][j] = ary[st][j - step];
					else
						break;
				}
				ary[st][j] = tmp;
			}
		cout << "==========================================================" << endl;
		cout << "����������� �������� = " << ary[st][0] << endl;
		cout << "������������ �������� = " << ary[st][cols - 1] << endl;
		cout << "���� ��������������� ������: " << endl;
		for (i = 0; i < cols; i++)
			cout << ary[st][i] << '\t';

		cout << endl;
		cout << "==========================================================" << endl;
		cout << "���������� ������:" << endl;
		cout << "==========================================================" << endl;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++) {
				cout << ary[i][j] << "\t";
			}
			cout << endl;
			cout << endl;
		}
		cout << "==========================================================" << endl;
		system("pause");

	}
	else system("pause");
}

int** KeyMatrix(int* rows, int* cols)
{
	int** ary;
	cout << "\t\t ������� ������� ������� \n";
	cout << "������� ����� �����: "; cin >> *rows;
	if (*rows < 0)
	{
		cout << "��� ���?: "; cin >> *rows;
		if (*rows < 0) throw 1;
	}
	cout << "������� ����� ��������: "; cin >> *cols;

	if (*cols < 0)
	{
		cout << "��� ���?: "; cin >> *cols;
		if (*cols < 0) throw 1;
	}

	ary = new int* [*rows];
	for (int i = 0; i < *rows; i++)
		ary[i] = new int[*cols];
	cout << endl;

	// ������ ������

	cout << "��������� ������ \n" << endl;
	for (int i = 0; i < *rows; i++) {
		for (int j = 0; j < *cols; j++) {
			cout << "������� ������� [" << i << "][" << j << "]: ";
			cin >> ary[i][j];
		}
	}


	cout << "\n ��������� ���� ������� \n";
	for (int i = 0; i < *rows; i++) {
		for (int j = 0; j < *cols; j++)
			cout << ary[i][j] << "\t";
		cout << endl;
		cout << endl;
	}

	return ary;

}

int** FileMatrix(int* rows, int* cols)
{
	int** ary;
	ifstream file("ary.txt");
		if (!file.is_open()) file.open("D:\\#��\\C++\\09.10.2019 ���������� ������\\09.10.2019 ���������� ������\\ary.txt");
	cout << "==========================================================" << endl;
	cout << "����� ������� �� �����" << endl;
	cout << "������� ����������� ������� � ������������ � ������������ � �����!" << endl;
	cout << "==========================================================" << endl;
	cout << "������� ����� �����: "; cin >> *rows;
	if (*rows < 0)
	{
		cout << "��� ���?: "; cin >> *rows;
		if (*rows < 0) throw 1;
	}
	cout << "������� ����� ��������: "; cin >> *cols;

	if (*cols < 0)
	{
		cout << "��� ���?: "; cin >> *cols;
		if (*cols < 0) throw 1;
	}
	cout << "�������������� � ���, ��� � ����� ���� ������� ����������� �����������" << endl;
	system("pause");

	ary = new int* [*rows];
	for (int i = 0; i < *rows; i++)
		ary[i] = new int[*cols];

	for (int i = 0; i < *rows; i++)
		for (int j = 0; j < *cols; j++)
			file >> ary[i][j];
	cout << "==========================================================" << endl;
	cout << "\n ��������� ������� \n";
	cout << "==========================================================" << endl;
	for (int i = 0; i < *rows; i++)
	{
		for (int j = 0; j < *cols; j++)
			cout << ary[i][j] << ' ';
		cout << endl;
		cout << endl;
	}
	cout << "==========================================================" << endl;
	system("pause");
	return ary;

}

void LookForMatrix(int** ary, int rows, int cols)
{
	cout << "==========================================================" << endl;
	if ((rows != 0) && (cols != 0))
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				cout << ary[i][j] << " \t ";
			}
			cout << endl;
			cout << endl;
		}
	}
	else
	{
		cout << "� ��� �������?" << endl;
	}
	cout << "==========================================================" << endl;
}

int menu()
{
	cout << "**********************************************************" << endl;
	cout << "�������� �����" << endl;
	cout << "A. ������� ������� � ����������\n";
	cout << "B. ����� ������� �� ����� \n";
	cout << "1. ��������� ���������� ������� \n"
		<< "2. ���������� ����� ������ \n"
		<< "3. ����� �� ��������� \n";
	cout << "**********************************************************" << endl;
	cout << "��� �����: "; cin >> choice;
	return choice;
}