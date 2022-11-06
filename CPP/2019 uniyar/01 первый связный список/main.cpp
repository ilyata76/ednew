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
	void input(Rate& rate); // ��� �����
	Rate* Next;// �� ��������� ������� ������� 
};

void Rate::input(Rate& rate) // � ��� � ����
{
	char tchk;
	cout << "\n ������� ����� ��������: \n";
	cout << "\n ���: ";
	cin.getline(Position, 30);
	if (strlen(Position) < 5) throw 1;
	cout << "\n ���� ��������(������ ��.��.����.): ";
	if (cin >> dd >> tchk >> mm >> tchk >> yyyy)
	{
		if ((dd < 0) || (mm < 0) || (yyyy < 0) || (tchk != '.')) throw 1;
	}
	cout << "\n ����: ";
	cin >> Price;
	if (Price < 0) throw 1;
	cout << "\n ���������� ������: ";
	cin >> Count;
	if (Count < 0) throw 1;
}

class LIST
{
	Rate* Head; // �� ������ ������ ���������
public:
	LIST() :Head(NULL) {}; // ����������� �� ���������
	void Show(); // ��������
	void AddTop(Rate& rate); // �������� � ������
	void AddEnd(Rate& rate); // �������� � �����
	void Remove(Rate& rate); // �������
	void TotalPrice(Rate& rate); // ������� �������

	void Merge(double* A, int first, int last); //
	void MergeSort(double* A, int first, int last); //
	void Sort(); //

	~LIST();
	int num;

};

LIST::~LIST() // ���������� ������
{
	while (Head != NULL)
	{
		Rate* temp = Head->Next;
		/* temp �������� �������� Next (��� ������ ������ ������� Head), ����������� ����� ���������
		����� ������ Head; -> ����� ��� ����, ����� ���������� � Nexty ����� ��������� Head
		*/
		delete Head; // ������������ ������ �� ������
		Head = temp; // "�����"
	}
}

void LIST::AddTop(Rate& rate) // ��������� � ������
{
	Rate* temp = new Rate;
	temp->Next = Head; // ����� ���������� �������� (������ ����� temp) ��� ������ ������ 
	strcpy_s(temp->Position, rate.Position); // ����������� ������ �������� ������������� rate ����� �������� � temp
	temp->dd = rate.dd;
	temp->mm = rate.mm;
	temp->yyyy = rate.yyyy;
	temp->Price = rate.Price;
	temp->Count = rate.Count;
	Head = temp; // ��� ������ ������ �������� "�����"
	num++;
}

void LIST::AddEnd(Rate& rate)
{
	Rate* temp = new Rate;
	temp->Next = NULL; // ����� ���������� �������� ��������� �� �����, ������
	strcpy_s(temp->Position, rate.Position);
	temp->dd = rate.dd;
	temp->mm = rate.mm;
	temp->yyyy = rate.yyyy;
	temp->Price = rate.Price;
	temp->Count = rate.Count;

	// ������ ��� ���� ���������� �� ���� ��������� � ���������� ����
	Rate* tempback = Head;

	if (Head == NULL)
	{
		Head = temp;
	}
	else {

		while (tempback->Next != NULL)
		{
			tempback = tempback->Next; // ������� �� ���� �����
		}
		// � ����� ���� ��������� �� ��-��-��
		tempback->Next = temp; // �� ���������� ��������� �������������� ��������
	}
	num++;
}

void LIST::Show()
{
	Rate* temp = Head;
	if (temp == NULL) throw 4;
	while (temp != NULL) // ���� � ��� ���-�� ���� �� ������ temp
	{
		cout << "���: " << temp->Position << endl;
		cout << "���� ��������: " << temp->dd << '.' << temp->mm << '.' << temp->yyyy << endl;
		cout << "����: " << temp->Price << endl;
		cout << "����������: " << temp->Count << endl << endl;
		temp = temp->Next; // ������ ����� temp ������� �� Next
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
			cout << "���: " << temp->Position << endl;
			cout << "���� ��������: " << temp->dd << '.' << temp->mm << '.' << temp->yyyy << endl;
			cout << "����: " << temp->Price << endl;
			cout << "����������: " << temp->Count << endl << endl;
			cout << "�������� � ��������: " << TotalPrice;
		}
		temp = temp->Next;
	}
	cout << endl;
	cout << "?" << endl;
	if (TotalPrice == 0) cout << "���������� �����" << endl;
}

void LIST::Remove(Rate& rate)
{
	int n;
	cout << "������� ����� ��������� �������: "; cin >> n;
	if (n <= 0) throw 1;
	Rate* temp = Head;
	Rate* tempback = Head; // ��������� �����


	for (int i = 1; i < n - 1; i++) {

		tempback = tempback->Next;
		if (tempback == NULL) throw 3;
	} // ���������� �������������

	for (int i = 1; i < n; i++)
	{
		temp = temp->Next; // ���������� ���������-"������

	}
	if (Head->Next == NULL && n == 2)
	{
		throw 3;
	}
	if (n == 1) //������ ������ - ������ �����
	{
		Head = Head->Next;
	}

	tempback->Next = temp->Next; // �-�-�-�-�-�-� (����� ���������� �������� �� �����������)
	delete temp; //������� ���������(�� ������) �� ���������� �������� �� �����������

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
		cout << "�����:  " << temp->Position << endl;
		cout << "���� - " << temp->Price << ", ";
		cout << "����  - " << temp->dd << '.' << temp->mm << '.' << temp->yyyy << ", ";
		cout << "���������� ������ - " << temp->Count << '.' << endl << endl;
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
			cout << "�� ������� ������������ �������";
			cout << endl; system("pause");
			continue;
		}
		switch (choice)
		{
		case 1:
			try {
				cout << "������� ���������� �������� �������: "; cin >> N;
				if (N < 0) throw 1;

				cout << endl;

				for (int i = 0; i < N; i++)
				{
					cin.ignore();
					rate.input(rate); // ���� � �����
					lst.AddTop(rate); // � ��� �� ���������
				}

			}
			catch (int f)
			{
				if (f == 1)
				{
					cout << " \n";
					cout << "//////////////////////////////////////////////////////////" << endl;
					cout << "            ������ #" << f << ": " << endl;
					cout << "       �� ����� �������� ������������ ��������" << endl;
					cout << " \n";
					cout << "            _������� ������_" << endl;
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
					cout << "            ������ #" << f << ": " << endl;
					cout << "       �� ����� �������� ������������ ��������" << endl;
					cout << " \n";
					cout << "            _������� ������_" << endl;
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
					cout << "            ������ #" << f << ": " << endl;
					cout << "       �� ����� �������� ������������ ��������" << endl;
					cout << " \n";
					cout << "            _������� ������_" << endl;
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
					cout << "            ������ #" << f << ": " << endl;
					cout << "         �� ����� �������� ������������ ��������" << endl;
					cout << " \n";
					cout << "            _������� ������_" << endl;
					cout << "//////////////////////////////////////////////////////////" << endl;
				}
				if (f == 3)
				{
					cout << " \n";
					cout << "//////////////////////////////////////////////////////////" << endl;
					cout << "            ������ #" << f << ": " << endl;
					cout << "                      ������� ������" << endl;
					cout << " \n";
					cout << "            _������� ������_" << endl;
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
					cout << "            ������ #" << f << ": " << endl;
					cout << "                 ���������� ������!" << endl;
					cout << " \n";
					cout << "            _������� ������_" << endl;
					cout << "//////////////////////////////////////////////////////////" << endl;
				}
			}
			cout << endl; system("pause"); cout << endl;
			break;
		case 6:
			try {
				cout << "������� �������� ������: " << endl;
				cin >> rate.Position;
				lst.TotalPrice(rate);
			}
			catch (int f) {
				if (f == 4)
				{
					cout << " \n";
					cout << "//////////////////////////////////////////////////////////" << endl;
					cout << "            ������ #" << f << ": " << endl;
					cout << "                 ���������� ������!" << endl;
					cout << " \n";
					cout << "            _������� ������_" << endl;
					cout << "//////////////////////////////////////////////////////////" << endl;
				}
			}
			cout << endl; system("pause"); cout << endl;
			break;
		case 0: cout << "�������! " << endl; break;
		default: cout << "�� ������� ������������ �������";
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
	cout << "��������, �� �������: " << endl;
	cout << "===========================================================\n";
	cout << "0. Exit \n";
	cout << "1. ������� ������ \n"
		<< "2. �������� ������� � ������ ������ \n"
		<< "3. �������� ������� � ����� ������ \n"
		<< "4. ������� ������� � ������ \n"
		<< "5. ����� ������ �� ����� \n"
		<< "6. ������� �������� \n"
		<< "7. ���������� �������� \n";
	cout << "===========================================================\n";
	cout << "��� �����: "; cin >> choice;
	cout << "===========================================================\n";
	cout << endl;
	return choice;
}