#include <iostream>
#include <windows.h>
#include <cstdio>
#include <string>

using namespace std;
int menu(); int choice;



struct Rate
{
	char Position[30];
	int dd, mm, yyyy;
	double Price;
	int Count;
	void input(Rate& rate); // для ввода
	Rate* Next;// на следующий элемент штучька 
};

void Rate::input(Rate& rate) // а вот и ввод
{
	char tchk;
	cout << "\n Давайте введём товарчик: \n";
	cout << "\n Имя: ";
	cin.getline(Position, 30);
	if (strlen(Position) < 5) throw 1;
	cout << "\n Дата прибытия(формат дд.мм.гггг.): ";
	if (cin >> dd >> tchk >> mm >> tchk >> yyyy)
	{
		if ((dd < 0) || (mm < 0) || (yyyy < 0) || (tchk != '.')) throw 1;
	}
	cout << "\n Цена: ";
	cin >> Price;
	if (Price < 0) throw 1;
	cout << "\n Количество товара: ";
	cin >> Count;
	if (Count < 0) throw 1;
}

class LIST
{
	Rate* Head; // на начало списка указатель
public:
	LIST() :Head(NULL) {}; // конструктор по умолчанию
	void Show(); // показать
	void AddTop(Rate& rate); // добавить в начало
	void AddEnd(Rate& rate); // добавить в конец
	void Remove(Rate& rate); // удалить
	void TotalPrice(Rate& rate); // считаем наценку

	void Merge(double* A, int first, int last); //
	void MergeSort(double* A, int first, int last); //
	void Sort(); //

	~LIST();
	int num;

};

LIST::~LIST() // деструктор класса
{
	while (Head != NULL)
	{
		Rate* temp = Head->Next;
		/* temp получает значение Next (как метода класса объекта Head), полученного через обращение
		через объект Head; -> нужна для того, чтобы обратиться к Nexty через указатель Head
		*/
		delete Head; // освобождение памяти от начала
		Head = temp; // "сдвиг"
	}
}

void LIST::AddTop(Rate& rate) // добавляем в НАЧАЛО
{
	Rate* temp = new Rate;
	temp->Next = Head; // адрес следующего элемента (доступ через temp) это начало списка 
	strcpy_s(temp->Position, rate.Position); // копирование строки введённой пользователем rate через допуступ в temp
	temp->dd = rate.dd;
	temp->mm = rate.mm;
	temp->yyyy = rate.yyyy;
	temp->Price = rate.Price;
	temp->Count = rate.Count;
	Head = temp; // вот значит начало сдвинули "назад"
	num++;
}

void LIST::AddEnd(Rate& rate)
{
	Rate* temp = new Rate;
	temp->Next = NULL; // адрес следующего элемента указывает на конец, ничего
	strcpy_s(temp->Position, rate.Position);
	temp->dd = rate.dd;
	temp->mm = rate.mm;
	temp->yyyy = rate.yyyy;
	temp->Price = rate.Price;
	temp->Count = rate.Count;

	// теперь нам надо установить на него указатель в предыдущем узле
	Rate* tempback = Head;

	if (Head == NULL)
	{
		Head = temp;
	}
	else {

		while (tempback->Next != NULL)
		{
			tempback = tempback->Next; // переход на узел вперёд
		}
		// и когда узел указывает на ни-че-го
		tempback->Next = temp; // мы определяем указатель предпоследнего элемента
	}
	num++;
}

void LIST::Show()
{
	Rate* temp = Head;
	if (temp == NULL) throw 4;
	while (temp != NULL) // пока у нас что-то есть по адресу temp
	{
		cout << "Имя: " << temp->Position << endl;
		cout << "Дата прибытия: " << temp->dd << '.' << temp->mm << '.' << temp->yyyy << endl;
		cout << "Цена: " << temp->Price << endl;
		cout << "Количество: " << temp->Count << endl << endl;
		temp = temp->Next; // доступ через temp переход на Next
	}
	cout << endl;
}

void LIST::TotalPrice(Rate& rate)
{
	if (num == 0) throw 4;
	double TotalPrice = 0;
	Rate* temp = Head;
	for (int i = 0; i < num; i++)
	{
		if (!strcmp(temp->Position, rate.Position))
		{
			TotalPrice = temp->Price * temp->Count * 1.18;
			cout << "Имя: " << temp->Position << endl;
			cout << "Дата прибытия: " << temp->dd << '.' << temp->mm << '.' << temp->yyyy << endl;
			cout << "Цена: " << temp->Price << endl;
			cout << "Количество: " << temp->Count << endl << endl;
			cout << "Доставка с наценкой: " << TotalPrice;
		}
		temp = temp->Next;
	}
	cout << endl;
	cout << "?" << endl;
	if (TotalPrice == 0) cout << "Попробуйте снова" << endl;
}

void LIST::Remove(Rate& rate)
{
	int n;
	cout << "Введите номер удяляемой позиции: "; cin >> n;
	if (n <= 0) throw 1;
	Rate* temp = Head;
	Rate* tempback = Head; // определим потом


	for (int i = 1; i < n - 1; i++) {

		tempback = tempback->Next;
		if (tempback == NULL) throw 3;
	} // определили предпоследний

	for (int i = 1; i < n; i++)
	{
		temp = temp->Next; // определили последний-"нужный

	}
	if (Head->Next == NULL && n == 2)
	{
		throw 3;
	}
	if (n == 1) //особый случай - просто сдвиг
	{
		Head = Head->Next;
	}

	tempback->Next = temp->Next; // п-о-д-м-е-н-а (чтобы предыдущий указывал на последующий)
	delete temp; //удаляем указатель(оч память) со следующего элемента на последующий

}

void LIST::Merge(double* A, int first, int last)
{
	int middle, start, final, j;
	double* mas = new double[100];
	middle = (first + last) / 2;
	start = first;
	final = middle + 1;
	for (j = first; j <= last; j++)
		if ((start <= middle) && ((final > last) || (A[start] < A[final])))
		{
			mas[j] = A[start];
			start++;
		}
		else
		{
			mas[j] = A[final];
			final++;
		}

	for (j = first; j <= last; j++) A[j] = mas[j];
	delete[]mas;
}

void LIST::MergeSort(double* A, int first, int last)
{
	{
		if (first < last)
		{
			MergeSort(A, first, (first + last) / 2);
			MergeSort(A, (first + last) / 2 + 1, last);
			Merge(A, first, last);
		}
	}
}

void LIST::Sort()
{
	int b; int i = 0;
	Rate* temp = Head;
	double A[100];
	while (temp != NULL)
	{
		A[i] = temp->Price;
		i++;
		temp = temp->Next;
		b = i;
	}

	MergeSort(A, 0, b - 1);

	temp = Head;


	for (i = 0; i < b; i++)
	{

		while (temp->Price != A[i])
		{
			temp = temp->Next;
		}
		cout << "Товар:  " << temp->Position << endl;
		cout << "Цена - " << temp->Price << ", ";
		cout << "Дата  - " << temp->dd << '.' << temp->mm << '.' << temp->yyyy << ", ";
		cout << "Количество товара - " << temp->Count << '.' << endl << endl;
		temp = Head;
	}
}



int main()
{
	SetConsoleCP(1251); SetConsoleOutputCP(1251);

	Rate rate;
	int N;
	LIST lst;

	do {
		system("cls");
		choice = menu();
		if (choice < 0)
		{
			cout << "Вы выбрали недопустимый вариант";
			cout << endl; system("pause");
			continue;
		}
		switch (choice)
		{
		case 1:
			try {
				cout << "Введите количество вводимых позиций: "; cin >> N;
				if (N < 0) throw 1;

				cout << endl;

				for (int i = 0; i < N; i++)
				{
					cin.ignore();
					rate.input(rate); // ввод с клавы
					lst.AddTop(rate); // и это же добавляем
				}

			}
			catch (int f)
			{
				if (f == 1)
				{
					cout << " \n";
					cout << "//////////////////////////////////////////////////////////" << endl;
					cout << "            Ошибка #" << f << ": " << endl;
					cout << "       Вы ввели неверное определяющее значение" << endl;
					cout << " \n";
					cout << "            _Начните заново_" << endl;
					cout << "//////////////////////////////////////////////////////////" << endl;

				}
			}
			cout << endl; system("pause"); cout << endl;
			break;
		case 2:
			try {
				cin.ignore();
				rate.input(rate);
				lst.AddTop(rate);
			}
			catch (int f)
			{
				if (f == 1)
				{
					cout << " \n";
					cout << "//////////////////////////////////////////////////////////" << endl;
					cout << "            Ошибка #" << f << ": " << endl;
					cout << "       Вы ввели неверное определяющее значение" << endl;
					cout << " \n";
					cout << "            _Начните заново_" << endl;
					cout << "//////////////////////////////////////////////////////////" << endl;

				}
			}
			cout << endl; system("pause"); cout << endl;
			break;
		case 3:
			try {
				cin.ignore();
				rate.input(rate);
				lst.AddEnd(rate);
			}
			catch (int f)
			{
				if (f == 1)
				{
					cout << " \n";
					cout << "//////////////////////////////////////////////////////////" << endl;
					cout << "            Ошибка #" << f << ": " << endl;
					cout << "       Вы ввели неверное определяющее значение" << endl;
					cout << " \n";
					cout << "            _Начните заново_" << endl;
					cout << "//////////////////////////////////////////////////////////" << endl;

				}
			}
			cout << endl; system("pause"); cout << endl;
			break;
		case 4:
			try {
				cin.ignore();
				lst.Remove(rate);
			}
			catch (int f) {
				if (f == 1)
				{
					cout << " \n";
					cout << "//////////////////////////////////////////////////////////" << endl;
					cout << "            Ошибка #" << f << ": " << endl;
					cout << "         Вы ввели неверное определяющее значение" << endl;
					cout << " \n";
					cout << "            _Начните заново_" << endl;
					cout << "//////////////////////////////////////////////////////////" << endl;
				}
				if (f == 3)
				{
					cout << " \n";
					cout << "//////////////////////////////////////////////////////////" << endl;
					cout << "            Ошибка #" << f << ": " << endl;
					cout << "                      Удалять нечего" << endl;
					cout << " \n";
					cout << "            _Начните заново_" << endl;
					cout << "//////////////////////////////////////////////////////////" << endl;

				}
			}
			cout << endl; system("pause"); cout << endl;
			break;
		case 5:
			try {
				system("cls");
				cin.ignore();
				lst.Show();

			}
			catch (int f) {
				if (f == 4)
				{
					cout << " \n";
					cout << "//////////////////////////////////////////////////////////" << endl;
					cout << "            Ошибка #" << f << ": " << endl;
					cout << "                 Показывать нечего!" << endl;
					cout << " \n";
					cout << "            _Начните заново_" << endl;
					cout << "//////////////////////////////////////////////////////////" << endl;
				}
			}
			cout << endl; system("pause"); cout << endl;
			break;
		case 6:
			try {
				cout << "Введите название товара: " << endl;
				cin >> rate.Position;
				lst.TotalPrice(rate);
			}
			catch (int f) {
				if (f == 4)
				{
					cout << " \n";
					cout << "//////////////////////////////////////////////////////////" << endl;
					cout << "            Ошибка #" << f << ": " << endl;
					cout << "                 Показывать нечего!" << endl;
					cout << " \n";
					cout << "            _Начните заново_" << endl;
					cout << "//////////////////////////////////////////////////////////" << endl;
				}
			}
			cout << endl; system("pause"); cout << endl;
			break;
		case 0: cout << "Выходим! " << endl; break;
		default: cout << "Вы выбрали недопустимый вариант";
			cout << endl; system("pause"); cout << endl; system("cls");
		}


	} while (choice != 0);


	cout << endl; system("pause"); cout << endl;
	lst.~LIST();
	return 0;
}

int menu()
{
	cout << "===========================================================\n";
	cout << "Выберите, шо сделать: " << endl;
	cout << "===========================================================\n";
	cout << "0. Exit \n";
	cout << "1. Создать список \n"
		<< "2. Добавить позицию в начало списка \n"
		<< "3. Добавить позицию в конец списка \n"
		<< "4. Удалить позицию в списке \n"
		<< "5. Вывод списка на экран \n"
		<< "6. Наценка доставки \n"
		<< "7. Сортировка слиянием \n";
	cout << "===========================================================\n";
	cout << "Ваш выбор: "; cin >> choice;
	cout << "===========================================================\n";
	cout << endl;
	return choice;
}