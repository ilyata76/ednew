#include <iostream>
#include <windows.h>
#include <fstream>
#include <conio.h>

using namespace std;

void swapEL(int** ary, int i, int j); // смена для Shaker
void myShakerSort(int** ary, int row, int cols); // шейкерная сортировка столбца
void ShellSort(int** ary, int row, int cols); // сортировка строки Шелла
int** KeyMatrix(int* rows, int* cols); // ввод матрицы с клавиатуры
int** FileMatrix(int* rows, int* cols); // ввод матрицы из файла
void LookForMatrix(int** ary, int rows, int cols); // вывод рабочей матрицы
int menu(); char choice; // вывод меню и выбор позиции в main


int main()
{
	SetConsoleCP(1251); SetConsoleOutputCP(1251);
	int rows = 0, cols = 0;
	int** ary = NULL;
	do {
		system("cls");
		cout << "Матрица, с которой работаем: " << endl;
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
						cout << "            Ошибка #" << f << ": " << endl;
						cout << "            Вы ввели неверное значение" << endl;
						cout << " \n";
						cout << "            _Начните заново_" << endl;
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
						cout << "            Ошибка #" << f << ": " << endl;
						cout << "            Вы ввели неверное значение" << endl;
						cout << " \n";
						cout << "            _Начните заново_" << endl;
						cout << "//////////////////////////////////////////////////////////" << endl;

					}
				}
				system("pause");
				break;
		case 'C': LookForMatrix(ary, rows, cols); break;
		case '1':
			cout << "==========================================================" << endl;
			cout << "\t ШЕЙКЕРНАЯ СОРТИРОВКА СТОЛБЦА МАТРИЦЫ" << endl;
			cout << "==========================================================" << endl;
			try { myShakerSort(ary, rows, cols); }
			catch (int f)
			{
				if (f == 1)
				{
					cout << " \n";
					cout << "//////////////////////////////////////////////////////////" << endl;
					cout << "            Ошибка #" << f << ": " << endl;
					cout << "            Вы ввели неверное значение" << endl;
					cout << " \n";
					cout << "            _Начните заново_" << endl;
					cout << "//////////////////////////////////////////////////////////" << endl;

				}
			}
			system("pause");
			break;
			cout << "==========================================================" << endl;
		case '2':
			cout << "==========================================================" << endl;
			cout << "\t СОРТИРОВКА ШЕЛЛА СТРОКИ МАТРИЦЫ" << endl;
			cout << "==========================================================" << endl;
			try { ShellSort(ary, rows, cols); }
			catch (int f)
			{
				if (f == 1)
				{
					cout << " \n";
					cout << "//////////////////////////////////////////////////////////" << endl;
					cout << "            Ошибка #" << f << ": " << endl;
					cout << "            Вы ввели неверное значение" << endl;
					cout << " \n";
					cout << "            _Начните заново_" << endl;
					cout << "//////////////////////////////////////////////////////////" << endl;

				}
			}
			system("pause");
			break;
		case '3':
			cout << "==========================================================" << endl;
			cout << "Выход из программы" << endl; break;
		default: cout << "Мимо!" << endl;
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
	cout << "Наша начальная матрица" << endl;
	LookForMatrix(ary, rows, cols);
	int t;
	if (rows >= 1 || cols >= 1) {

		cout << "Введите столбец(отсчитывая с единицы), который нужно отсортировать: "; cin >> t;
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
		cout << "Положительные элементы массива: " << endl;
		for (int i = 0; i < rows; i++)
		{
			if (ary[i][t] > 0)
				rightMark += ary[i][t];
			cout << ary[i][t] << endl;
		}

		cout << "Сумма положительных элементов массива: " << rightMark << endl;
		cout << "==========================================================" << endl;
		cout << "\t \t Ваш массив: " << endl;
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
	cout << "Матрица, с которой работаем:" << endl;
	LookForMatrix(ary, rows, cols);
	int i, j, step, st;
	int tmp;

	if (rows >= 1 || cols >= 1) {
		cout << "Введите строку(отсчитывая от единицы), которую нужно отсортировать: ";
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
		cout << "Минимальное значение = " << ary[st][0] << endl;
		cout << "Максимальное значение = " << ary[st][cols - 1] << endl;
		cout << "Наша отсортированная строка: " << endl;
		for (i = 0; i < cols; i++)
			cout << ary[st][i] << '\t';

		cout << endl;
		cout << "==========================================================" << endl;
		cout << "Измененный массив:" << endl;
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
	cout << "\t\t Введите размеры массива \n";
	cout << "Введите число строк: "; cin >> *rows;
	if (*rows < 0)
	{
		cout << "Ещё раз?: "; cin >> *rows;
		if (*rows < 0) throw 1;
	}
	cout << "Введите число столбцов: "; cin >> *cols;

	if (*cols < 0)
	{
		cout << "Ещё раз?: "; cin >> *cols;
		if (*cols < 0) throw 1;
	}

	ary = new int* [*rows];
	for (int i = 0; i < *rows; i++)
		ary[i] = new int[*cols];
	cout << endl;

	// вводим массив

	cout << "Заполняем массив \n" << endl;
	for (int i = 0; i < *rows; i++) {
		for (int j = 0; j < *cols; j++) {
			cout << "Введите элемент [" << i << "][" << j << "]: ";
			cin >> ary[i][j];
		}
	}


	cout << "\n Проверьте вашу матрицу \n";
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
		if (!file.is_open()) file.open("D:\\#ЯП\\C++\\09.10.2019 Сортировки матриц\\09.10.2019 Сортировки матриц\\ary.txt");
	cout << "==========================================================" << endl;
	cout << "Вывод матрицы из файла" << endl;
	cout << "Введите размерность матрицы в соответствии с размерностью в файле!" << endl;
	cout << "==========================================================" << endl;
	cout << "Введите число строк: "; cin >> *rows;
	if (*rows < 0)
	{
		cout << "Ещё раз?: "; cin >> *rows;
		if (*rows < 0) throw 1;
	}
	cout << "Введите число столбцов: "; cin >> *cols;

	if (*cols < 0)
	{
		cout << "Ещё раз?: "; cin >> *cols;
		if (*cols < 0) throw 1;
	}
	cout << "Удостоверьтесь в том, что в файле есть матрица необходимой размерности" << endl;
	system("pause");

	ary = new int* [*rows];
	for (int i = 0; i < *rows; i++)
		ary[i] = new int[*cols];

	for (int i = 0; i < *rows; i++)
		for (int j = 0; j < *cols; j++)
			file >> ary[i][j];
	cout << "==========================================================" << endl;
	cout << "\n Проверьте матрицу \n";
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
		cout << "А где матрица?" << endl;
	}
	cout << "==========================================================" << endl;
}

int menu()
{
	cout << "**********************************************************" << endl;
	cout << "Сделайте выбор" << endl;
	cout << "A. Набрать матрицу с клавиатуры\n";
	cout << "B. Взять матрицу из файла \n";
	cout << "1. Шейкерная сортировка столбца \n"
		<< "2. Сортировка Шелла строки \n"
		<< "3. Выход из программы \n";
	cout << "**********************************************************" << endl;
	cout << "Ваш выбор: "; cin >> choice;
	return choice;
}