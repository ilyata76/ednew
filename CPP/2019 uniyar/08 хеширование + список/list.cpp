#include "LIST.h"

int num;							// кол-во элементов в списке

void Data::Input(Data& data)
{

	cout << "==============================================\n" << endl;
	cout << "Name: "; cin >> name;
	cout << "Surname: "; cin >> surname;
	cout << "Password: "; cin >> password;
	cout << "==============================================\n" << endl;
}

void Data::InputFile(Data& data, ifstream& file)
{
	if (file.is_open())
	{
		file >> name >> surname >> password;
	}
}


void LIST::AddUser(Data& data)
{

	Data* temp = new Data;
	temp->name = data.name;
	temp->surname = data.surname;
	temp->password = data.password;

	temp->NEXT = HEAD; HEAD = temp;
	num++;
}

void LIST::DelUser(Data& data)
{
	Data* temp = HEAD;
	Data* tempback = HEAD;
	int u = -1;
	bool check = CheckUser(data, u);
	if (check) {
		if (u == 1)
		{
			HEAD = HEAD->NEXT;
		}
		else {
			for (int i = 1; i < u - 1; i++)
			{
				tempback = tempback->NEXT;
			}

			for (int i = 1; i < u; i++)
			{
				temp = temp->NEXT;
			}
			tempback->NEXT = temp->NEXT;
		}
		delete temp; num--;
	}
	else cout << "LIST :: no check" << endl;

}

void LIST::Show()
{
	Data* temp = new Data;
	temp = HEAD;

	while (temp != NULL)
	{
		cout << temp->name << " " << temp->surname << " " << temp->password << endl;
		temp = temp->NEXT;

	}
	cout << endl;
}

void LIST::ChangePassword(Data& data, string& new_pass)
{
	Data* temp = HEAD;
	int u = -1;
	bool check = CheckUser(data, u);
	if (check) {
		for (int i = 1; i < u; i++)
		{
			temp = temp->NEXT;
		}
		if (temp->password != new_pass) {
			temp->password = new_pass; cout << "LIST :: succses\n";
		}
		else cout << "LIST :: need different pass";
	}
	else cout << "LIST :: no check" << endl;
}

bool LIST::CheckUser(Data& data, int& u)
{
	Data* temp = HEAD;
	u = -1;
	for (int i = 1; i <= num; i++)
	{
		if (data.name == temp->name)
		{
			if (data.surname == temp->surname)
			{
				if (data.password == temp->password) u = i;
			}
		}
		temp = temp->NEXT;
	}
	temp = HEAD;
	if (u >= 0) { return true; }
	else { return false; }
}

bool LIST::CheckCol(Data& data, int& u)
{
	Data* temp = HEAD;
	bool check = CheckUser(data, u);
	temp = HEAD;
	if (check)
	{
		for (int i = 1; i <= num; i++)
		{
			if (data.name == temp->name)
			{
				if (data.surname == temp->surname)
				{
					if (data.password == temp->password) { u = i; break; }
				}
			}
			temp = temp->NEXT;
		}
	}
	else return false;

	if (u >= 0) {
		return true;
	}
	else return false;
}

bool LIST::Empty()
{
	Data* temp = HEAD;
	if (temp == NULL || num <= 0) return true;
	else return false;
}

LIST::~LIST()
{
	Data* temp = HEAD;
	while (HEAD)
	{
		temp = HEAD->NEXT;
		delete HEAD;
		HEAD = temp;
		num--;
	}
}
