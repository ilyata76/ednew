#include <iostream>
#include <string>
#include <windows.h>
#include <cmath>
#include "LIST.h"

using namespace std;


int menu(string& ShowInstr);
int choice0to99();												// считывает символы: числа переводит в целочисленный
int file0to99(ifstream& file);									// ошибку не выбрасывает: просто игнорирует неправильно введённое значение

void ADD(Data& data, int Instr, ifstream& file);				// заглавные фунции ввода, удаления и смены пароля
void REMOVE(Data& data);
void CHANGE(Data& data);



int keystring(string& str);										// функции хэширования
int Symbols(int& number);
string HashSquareHalf(string& str);
string getSault(Data& data, string& str);

string HASHHEAD(Data& data);									// заглавные функции хэширования
string HASHSTR(Data& data, string& str);
string ClosedHash(Data& tempdata, int& Z, string& istr);
string ClosedHashSTR(Data& tempdata, string& str, string& istr);

LIST lst; int Z = 0;
int choice = -1;


int main()
{

	ifstream file1("txt.txt");
		if (!file1.is_open()) file1.open("D:\\#ЯП\\C++\\09.12.2019 Хэширование, список\\09.12.2019 Хэширование, список\\txt.txt");
	SetConsoleCP(1251); SetConsoleOutputCP(1251);
	Data data;
	int z; string ShowInstr;
	if (file1.is_open()) {
		if (!file1.eof()) z = file0to99(file1); else cout << "\nФайл оказался пуст\n";
		for (int i = 0; i < z; i++)	if (!file1.eof()) { ADD(data, 2, file1); Z++; }
		if (!lst.Empty()) cout << "\nЗагрузили " << Z << " пользователей\n";
		else cout << "\nФайл оказался пуст\n";
	}
	else { cout << "\nФайл не видно, а он есть?\n"; }

	cout << "==============================================" << endl;
	cout << "Показывать список каждый раз над меню?\n"
		<< "1 - да; любое другое значение - нет\n"; cin >> ShowInstr;
	do {
		system("cls");
		choice = menu(ShowInstr);

		switch (choice)
		{
		case 1:
			try {
				cout << "Количество вводимых пользователей: ";
				z = choice0to99(); if (z < 0) throw 1;
				for (int i = 0; i < z; i++)	ADD(data, 1, file1);

				cout << "==============================================" << endl;
				if (lst.Empty()) throw 4; lst.Show();
				cout << "==============================================" << endl;
			}
			catch (int F)
			{
				cout << "==============================================" << endl;
				if (F == 1) cout << "!!! Неправильно введённое количество пользователей !!! #" << F << endl;
				if (F == 4) cout << "!!! Список пуст !!! #" << F << endl;
				cout << "==============================================" << endl;
			}
			system("pause"); break;
		case 2:
			try {
				if (lst.Empty()) throw 4;
				cout << "Количество удаляемых пользователей: ";

				z = choice0to99(); if (z < 0) throw 1;

				for (int i = 0; i < z; i++)	REMOVE(data);

				cout << "==============================================" << endl;
				if (lst.Empty()) throw 4; lst.Show();
				cout << "==============================================" << endl;
			}
			catch (int F)
			{
				cout << "==============================================" << endl;
				if (F == 1) cout << "!!! Неправильно введённое количество пользователей !!! #" << F << endl;
				if (F == 2) cout << "!!! Такого пользователя не существует !!! #" << F << endl;
				if (F == 4) cout << "!!! Список пуст !!! #" << F << endl;
				if (F == 99) cout << "!!! Ошибка в функции !!! #" << F << endl;
				cout << "==============================================" << endl;
			}
			system("pause"); break;
		case 3:
			try {
				if (lst.Empty()) throw 4;
				CHANGE(data);

				cout << "==============================================" << endl;
				if (lst.Empty()) throw 4;  lst.Show();
				cout << "==============================================" << endl;
			}
			catch (int F)
			{
				cout << "==============================================" << endl;
				if (F == 2) cout << "!!! Такого пользователя не существует !!! #" << F << endl;
				if (F == 3) cout << "!!! Нельзя изменить пароль на существующий или подобный ему !!! #" << F << endl;
				if (F == 4) cout << "!!! Список пуст !!! #" << F << endl;
				if (F == 99) cout << "!!! Ошибка в функции !!! #" << F << endl;
				cout << "==============================================" << endl;
			}

			system("pause"); break;
		case 4:
			try {
				if (lst.Empty()) throw 4;
				lst.Show();
			}
			catch (int F)
			{
				cout << "==============================================" << endl;
				if (F == 4) cout << "!!! Список пуст !!! #" << F << endl;
				cout << "==============================================" << endl;
			}

			system("pause"); break;
		case 5:
			cout << "?: 1 - да; любое другое значение - нет\n"; cin >> ShowInstr; break;
		case 6:
			lst.~LIST(); break;
		case 0:
			cout << "Ливаем отсюда\n"; break;
		default:
			cout << "Введёный вариант не предусмотрен" << endl;
			system("pause");
		}
	} while (choice != 0);
	lst.~LIST();
	system("pause");
	return 0;
}
int menu(string& ShowInstr)
{
	char ShowInstra = ShowInstr[0]; if (ShowInstr[1]) ShowInstra = '2';
	if (ShowInstra == '1')
	{
		cout << "==============================================\n" << endl;
		lst.Show();
		cout << "==============================================" << endl;
	}
	else cout << "==============================================" << endl;
	cout << "В случае коллизии удаляется последний введённый пользователь,\n"
		<< "как и пароль - изменяется у последнего введённого\n"
		<< "K0: захэшировался стандартно; K1...: закрыто\n";
	cout << "==============================================" << endl;
	cout << "1. Ввести пользователей\n"
		<< "2. Удалить пользователей\n"
		<< "3. Сменить пароль\n"
		<< "4. Показать список (продавцов в ларьке с пивом)\n"
		<< "5. Спросить о показе списка сверху снова\n"
		<< "6. Очистить список\n"
		<< "0. Выход\n";
	cout << "==============================================" << endl;
	cout << "Ваш выбор:"; choice = choice0to99();
	cout << "==============================================" << endl;

	return choice;
}
int choice0to99()
{
	string c; int SS;
	cin >> c;
	if (c[0] == '1' || c[0] == '2' || c[0] == '3' || c[0] == '4' || c[0] == '5' || c[0] == '6' || c[0] == '7'
		|| c[0] == '8' || c[0] == '9' || c[0] == '0')
	{
		SS = c[0] - '0';
		if (c[1] == '1' || c[1] == '2' || c[1] == '3' || c[1] == '4' || c[1] == '5' || c[1] == '6' || c[1] == '7'
			|| c[1] == '8' || c[1] == '9' || c[1] == '0') {
			SS = (c[0] - '0') * 10 + (c[1] - '0');
		}
		if (c[1]) if (c[2]) SS = -1;
	}
	else { SS = -1; };
	return SS;
}
int file0to99(ifstream& file)
{
	string c; int SS;
	file >> c;
	if (c[0] == '1' || c[0] == '2' || c[0] == '3' || c[0] == '4' || c[0] == '5' || c[0] == '6' || c[0] == '7'
		|| c[0] == '8' || c[0] == '9' || c[0] == '0')
	{
		SS = c[0] - '0';
		if (c[1] == '1' || c[1] == '2' || c[1] == '3' || c[1] == '4' || c[1] == '5' || c[1] == '6' || c[1] == '7'
			|| c[1] == '8' || c[1] == '9' || c[1] == '0') {
			SS = (c[0] - '0') * 10 + (c[1] - '0');
		}
		if (c[1]) if (c[2]) SS = -1;
	}
	else { SS = -1; };
	return SS;
}


// а не проще ли запретить вбивать одинаковые логины?

// инструментарий
void ADD(Data& data, int Instr, ifstream& file)
{
	int u = -1;
	if (Instr == 1)
	{
		cout << "==============================================" << endl;
		cout << "Введите данные:" << endl;
		data.Input(data);
	}
	if (Instr == 2) data.InputFile(data, file); string istr;

	Data tempdata = data; Data Ttempdata = data;

	istr = to_string(1);
	HASHHEAD(data); ClosedHash(tempdata, Z, istr);			// обычный хэш для data, закрытый хэш для tempdata
	bool check = lst.CheckUser(data, u);
	bool checkCol = lst.CheckCol(tempdata, u);
	if (!check && !checkCol)
	{
		lst.AddUser(data); cout << "K0 ";
		cout << "  " << data.name << " " << data.surname << " " << data.password << endl;
		if (Instr == 1) cout << "\nПользователь добавлен" << endl;
	}
	else if (check && checkCol)						// если он существует, а коллизия имеет место,
	{
		checkCol = lst.CheckCol(tempdata, u);
		cout << "К";
		tempdata = Ttempdata; int i = 1;
		while (checkCol)
		{

			Ttempdata = tempdata;
			istr = to_string(i);
			ClosedHash(tempdata, Z, istr);
			checkCol = lst.CheckCol(tempdata, u);
			if (checkCol) { tempdata = Ttempdata; i++; }
			if (!checkCol) { ClosedHash(Ttempdata, Z, istr); tempdata = Ttempdata; cout << i << " "; break; }
		}

		lst.AddUser(tempdata);	i = 1;
		cout << "  " << tempdata.name << " " << tempdata.surname << " " << tempdata.password << endl; // как только коллизия исчезла,
		if (Instr == 1)	cout << "\nПользователь добавлен" << endl;	// мы добавляем этого пользователя
	}
	else if (!check && checkCol)					// если его не существует, а коллизия имеет место
	{												// (2 и 3, допустим, одинаковые пользователи),
													// мы добавляем его обычным хэшированием

		lst.AddUser(data);
		cout << "  " << data.name << " " << data.surname << " " << data.password << endl;
		if (Instr == 1)	cout << "\nПользователь добавлен" << endl;

	}
	else if (check && !checkCol)
	{
		cout << "K1 ";
		cout << "  " << tempdata.name << " " << tempdata.surname << " " << tempdata.password << endl;
		lst.AddUser(tempdata);
		if (Instr == 1)cout << "\nПользователь добавлен" << endl;

	}
	else throw 99;
}
void REMOVE(Data& data)
{
	int u = -1;
	cout << "\n\nВведите данные пользователя для удаления:" << endl;
	data.Input(data);

	Data tempdata = data; Data Ttempdata = tempdata; string istr;

	istr = to_string(1);
	HASHHEAD(data); ClosedHash(tempdata, Z, istr);
	// обычный хэш для data, закрытый хэш для tempdata
	bool check = lst.CheckUser(data, u);
	bool checkCol = lst.CheckCol(tempdata, u);

	if (check && !checkCol)											// если он существует, а коллизии нет,
	{																// удаляем его
		cout << "  " << data.name << " " << data.surname << " " << data.password << endl;
		lst.DelUser(data);
		cout << "\nПользователь удалён" << endl;
	}
	else if (!check && !checkCol)									// если ни его, ни коллизийных остальных нет
	{																// то их вообще нет
		throw 2;
	}
	else if ((!check && checkCol) || (check && checkCol))			// если его не существует, а коллизийные остались
	{																// или если и существует, и колизийные есть		
		tempdata = Ttempdata; int i = 1; int c = 0;
		while (checkCol)
		{
			Ttempdata = tempdata;
			istr = to_string(i);
			ClosedHash(tempdata, Z, istr);
			checkCol = lst.CheckCol(tempdata, u);
			if (checkCol) { tempdata = Ttempdata; c = i; i++; }			// прохешировали на троечке - совпадения не нашли
			if (!checkCol) { tempdata = Ttempdata; i--; break; }		// вернулись на единичку назад
		}

		istr = to_string(i);
		ClosedHash(tempdata, Z, istr);
		cout << "  " << tempdata.name << " " << tempdata.surname << " " << tempdata.password << endl;
		lst.DelUser(tempdata);
		cout << "\nПользователь удалён" << endl;
	}
	else throw 99;
}
void CHANGE(Data& data)
{

	int u = -1; string new_pass;
	cout << "\n\nВведите данные пользователя для смены пароля: \n";
	data.Input(data);
	string istr; Data tempdata = data; Data Ttempdata = data;

	istr = to_string(1);
	HASHHEAD(data); ClosedHash(tempdata, Z, istr);

	bool check = lst.CheckUser(data, u);
	bool checkCol = lst.CheckCol(tempdata, u);

	if (check && !checkCol)
	{
		cout << "\nВведите новый пароль: "; cin >> new_pass;
		HASHSTR(data, new_pass);
		cout << "\n<<==   " << data.name << " " << data.surname << " " << data.password << endl;
		cout << "==>>  " << data.name << " " << data.surname << " " << new_pass << endl;
		if (new_pass == data.password) throw 3;
		lst.ChangePassword(data, new_pass);

	}
	else if (!check && !checkCol)
	{
		throw 2;
	}
	else if ((check && checkCol) || (!check && checkCol))
	{
		string new_pass;
		cout << "\nВведите новый пароль: "; cin >> new_pass;
		tempdata = Ttempdata; int i = 1; int c = 0;
		while (checkCol)
		{
			Ttempdata = tempdata;
			istr = to_string(i);
			ClosedHash(tempdata, Z, istr);
			checkCol = lst.CheckCol(tempdata, u);
			if (checkCol) { tempdata = Ttempdata; c = i; i++; }
			if (!checkCol) { tempdata = Ttempdata; i--; break; }
		}
		istr = to_string(i);
		ClosedHash(tempdata, Z, istr);
		HASHSTR(tempdata, new_pass);

		cout << "\n<<==   " << tempdata.name << " " << tempdata.surname << " " << tempdata.password << endl;
		cout << "==>>  " << tempdata.name << " " << tempdata.surname << " " << new_pass << endl;

		if (new_pass == data.password || new_pass == tempdata.password) throw 3;
		lst.ChangePassword(tempdata, new_pass);
		cout << "\nПароль изменён" << endl;
	}
	else throw 99;
}


// семейство хэш-функций и их подсосов
int keystring(string& str)
{ // конвертация введённых символов в int
	int sum = 0;
	int n = 0;
	{
		n = (str).size();
		for (int i = 0; i < n; i++)
		{
			sum += ((int)(str)[i]) * (i + 1);		// поможет избавиться от коллизий 123 321	
		}
	}
	return sum;
}
int Symbols(int& number)
{
	int temp = number; int symbols = 0;
	for (int i = 1; i < 10; i++)
	{
		if ((int)(temp / pow(10, i - 1)) > 0)
		{
			symbols = i;
		}
		else break;
	}
	return symbols;
}
string HashSquareHalf(string& str)
{
	int key = 0;
	key = keystring(str);

	key *= key;

	int symbols = Symbols(key);				// узнаем кол-во символов

	int k, k1, k2;
	// просчитываем символы "центра"
	if (symbols % 2 == 0)
	{
		k = symbols / 2;
		if (k % 2 == 0)
		{
			k = k / 2;
			k1 = k; k2 = symbols - k1 - 1;
		}
		else
		{
			k = int(k / 2);
			k1 = k; k2 = symbols - k1 - 1;
		}

	}
	else
	{
		k = (int)(symbols / 2);
		if (k % 2 == 0)
		{
			k = k / 2;
			k1 = k; k2 = symbols - k1 - 1;
		}
		else
		{
			k = int(k / 2) + 1;
			k1 = k; k2 = symbols - k1 - 1;
		}
	}


	string num;
	num = to_string(key);
	char* z = new char;						// от известных k1 k2 заполняем массив этими числами

	int SS = 0;
	for (int i = k1; i <= k2; i++, SS++)
	{
		z[SS] = num[i];
	}
	z[SS] = '\0';
	string HASH = string(z);
	// HASH = atoi(z);							// функция перевода из char в int
												// !!!! 0056 = 56



	return HASH;
}
string getSault(Data& data, string& str)
{
	string Sault21(1, data.name[0]);
	string Sault22 = data.surname;
	string Sault2 = Sault21 + Sault22;
	// cout << " sol "  << Sault2 << endl;
	return Sault2;
}

// главные за расчёт
string HASHHEAD(Data& data)
{
	string str;
	string Sault = getSault(data, str);
	string HashPass = HashSquareHalf(data.password);
	string ByHash = HashPass + Sault;
	string BEHash = HashSquareHalf(ByHash);
	data.password = BEHash;
	return BEHash;
}
string HASHSTR(Data& data, string& str)
{
	string Sault = getSault(data, str);
	string HashPass = HashSquareHalf(str);
	string ByHash = HashPass + Sault;
	string BEHash = HashSquareHalf(ByHash);
	str = BEHash;
	return BEHash;
}
string ClosedHash(Data& tempdata, int& Z, string& istr)
{
	string str;
	string Sault = getSault(tempdata, str);
	//tempdata.password = tempdata.password + istr;
	string HashPass = HashSquareHalf(tempdata.password);
	HashPass = HashPass + istr;
	// нашли хэш-позицию для парол
	//string newhash = tempdata.password + istr;					
	//string newHashPass = HashSquareHalf(newhash);				
	string ByHash = HashPass + Sault;
	string BEHash = HashSquareHalf(ByHash);
	tempdata.password = BEHash;
	return BEHash;
}
string ClosedHashSTR(Data& tempdata, string& str, string& istr)
{
	string Sault = getSault(tempdata, str);
	string HashPass = HashSquareHalf(str);
	string newhash = str + istr;
	//string newHashPass = HashSquareHalf(newhash);				
	string ByHash = newhash + Sault;
	string BEHash = HashSquareHalf(ByHash);
	str = BEHash;
	return BEHash;
}