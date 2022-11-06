#include <iostream>
#include <windows.h>

using namespace std;

void Dij(int GR[8][8], int start, int end);
void F_Y(int GR[8][8]);
int menu(); int choice;

int main()
{
	SetConsoleCP(1251); SetConsoleOutputCP(1251);
	int start, end;
	int arr[8][8] =
	{
		{0, 10, 20, 0, 0, 40, 0, 0},
		{10, 0, 10, 0, 25, 15, 0, 0},
		{20, 10, 0, 49, 20, 0, 0, 0},
		{0, 0, 49, 0, 29, 0, 0, 37},
		{0, 25, 20, 29, 0, 13, 15, 33},
		{40, 15, 0, 0, 13, 0, 44, 0},
		{0, 0, 0, 0, 15, 44, 0, 23},
		{0, 0, 0, 37, 33, 0, 23, 0},
	};
	int parr[8][8] = //0 > 10000
	{
		{0, 10, 20, 10000, 10000, 40, 10000, 10000},
		{10, 0, 10, 10000, 25, 15, 10000, 10000},
		{20, 10, 0, 49, 20, 10000, 10000, 10000},
		{10000, 10000, 49, 0, 29, 10000, 10000, 37},
		{10000, 25, 20, 29, 0, 13, 15, 33},
		{40, 15, 10000, 10000, 13, 0, 44, 10000},
		{10000, 10000, 10000, 10000, 15, 44, 0, 23},
		{10000, 10000, 10000, 37, 33, 10000, 23, 0},

	};


	do
	{
		cout << "Матрица смежности \n";
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
				cout << arr[i][j] << " ";
			cout << endl;
		}
		choice = menu();
		switch (choice)
		{
		case 1:
			try {
				cout << "\n Введите начальный узел: "; cin >> start;
				if (start < 0 || start > 7) throw 1;
				cout << "\n Введите конечный узел: "; cin >> end;
				if (end < 0 || end > 7) throw 1;
				Dij(arr, start, end);
			}
			catch (int f)
			{
				if (f == 1)
				{
					cout << " \n";
					cout << "//////////////////////////////////////////////////////////" << endl;
					cout << "\t Ошибка #" << f << ": " << endl;
					cout << "\t Введено неверное значение!" << endl;
					cout << "//////////////////////////////////////////////////////////" << endl;
				}
				system("pause"); system("cls");
			}
			break;
		case 2: F_Y(parr); break;
		case 0: cout << "Выход из программы"; system("pause"); break;
		default: cout << "1,2,0"; system("pause"); system("cls");
		}
	} while (choice != 0);
	return 0;
}


void Dij(int GR[8][8], int start, int end)
{
	int distance[8], count, index, i, u;
	bool visited[8];
	for (i = 0; i < 8; i++)
	{
		distance[i] = INT_MAX; visited[i] = false;
	}
	distance[start] = 0;
	for (count = 0; count < 8 - 1; count++)
	{
		int min = INT_MAX;
		for (i = 0; i < 8; i++)
			if (!visited[i] && distance[i] <= min)
			{
				min = distance[i]; index = i;
			}
		u = index;
		visited[u] = true;
		for (i = 0; i < 8; i++)
			if (!visited[i] && GR[u][i] && distance[u] != INT_MAX &&
				distance[u] + GR[u][i] < distance[i])
				distance[i] = distance[u] + GR[u][i];

	}
	cout << "Стоимость пути из начальной вершины до остальных:\t\n";
	if (distance[i] != INT_MAX)
		cout << start << " ==> " << end << " = " << distance[end] << endl;
	else cout << "маршрут недоступен" << endl;


	// а теперь выводим путь
	int ver[8];
	int ends = end;
	ver[0] = end; //начальный элемент массива вывода есть конечная вершина
	int k = 1;
	int weight = distance[end];

	while (ends != start)
	{
		for (int i = 0; i < 8; i++)
			if (GR[ends][i] != 0)
			{
				int temp = weight - GR[ends][i];
				if (temp == distance[i])
				{
					weight = temp;
					ends = i;
					ver[k] = i;
					k++;
				}
			}

	}
	cout << "Путь по точкам: " << endl;
	for (int i = k - 1; i >= 0; i--)
		cout << ver[i] << " ";
	cout << endl;

}

void F_Y(int GR[8][8])
{

	for (int k = 0; k < 8; k++) {

		for (int i = 0; i < 8; i++) {

			for (int j = 0; j < 8; j++) {

				GR[i][j] = min(GR[i][j], GR[i][k] + GR[k][j]);

			}

		}
	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
			cout << " " << GR[i][j];
		cout << endl;
	}
}

int menu()
{
	cout << "========\n";
	cout << "1. Поиск кратчайшего пути методом Дейкстры\n"
		<< "2. Вывод матрицы кратких путей. Алгоритм Флойда-Уоршелла\n"
		<< "0. Выход из программы\n";
	cout << "========\n";
	cout << "\t Введите значение выбора: "; cin >> choice;
	return choice;
}