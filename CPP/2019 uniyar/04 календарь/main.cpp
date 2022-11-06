#include <iostream>
#include <windows.h>
#include <map> 
#include <iterator> 
#include <string>
#include <fstream>

using namespace std;


int startmonthVERT(int& mo, int& COUNT, int& k, int& DAYS, int& DAYSO, int& year, int& CMonth);			// вывод мес€ца с известным k
int monthVERT(int& mo, int& COUNT, int& k, int& DAYS, int& DAYSO, int& year, int& CMonth);				// вывод св€зного мес€ца
void forMVERT(int& mo, int& COUNT, int& k, int& DAYS, int& DAYSO, int& year, int& CMonth);				// цикл выводов св€зных мес€цев

int MOUNTHDETERMINE(int& CL, int& k, bool& viso, int& DAYS, int& DAYSO);				// заглавна€ функци€ поиска
int MONTHDETERMINE(int& k, int& DAYS, int& DAYSO);										// функци€ нахождени€ k св€зного мес€ца
int FORMONTHDETERMINE(int& CL, int& k, int& DAYS, int& DAYSO);							// цикл поисков k св€зных мес€цев

void FRANGE(int& month1, int& month2, int& year1, int& year2, int& Orien, int& CMonth); // Instr = 1
void FMONTH(int& month, int& year, int& Orien, int& CMonth);							// 2
void FYEAR(int& year, int& Orien, int& CMonth);											// 3

int startmonthHORIZ(int& mo, int& COUNT, int& k, int& DAYS, int& DAYSO, int& year, int& CMonth);
int monthHORIZ(int& mo, int& COUNT, int& k, int& DAYS, int& DAYSO, int& year, int& CMonth);
void forMHORIZ(int& mo, int& COUNT, int& k, int& DAYS, int& DAYSO, int& year, int& CMonth);

void swap(int& a, int& b);
char menu();
bool viso(int& year);

map <int, string> weekday = {
	{0, "ѕЌ"},
	{1, "¬“"},
	{2, "—–"},
	{3, "„“"},
	{4, "ѕ“"},
	{5, "—Ѕ"},
	{6, "¬—"}
}; map <int, string> ::iterator itWEEKDAY = weekday.begin();
map <int, string> mounth = {
	{1, "январь"},
	{2, "‘евраль"},
	{3, "ћарт"},
	{4, "јпрель"},
	{5, "ћай"},
	{6, "»юнь"},
	{7, "»юль"},
	{8, "јвгуст"},
	{9, "—ент€брь"},
	{10, "ќкт€брь"},
	{11, "Ќо€брь"},
	{12, "ƒекабрь"},
}; map <int, string> ::iterator itMOUNTH = mounth.begin();
map <string, int> Xfile = {
	{"year", 1},
	{"month", 2},
	{"range",3}
}; map <string, int> ::iterator itXFILE = Xfile.begin();
map <string, int> Yfile = {
	{"vert", 1},
	{"horiz", 2}
}; map <string, int> ::iterator itYFILE = Yfile.begin();
map <string, int> Zfile = {
	{"year_once", 1},
	{"year_for_month", 2}
}; map <string, int> ::iterator itZFILE = Zfile.begin();


char s[] = "  ";			// дл€ заполнени€ пустых множеств
char choice = 0;
int YESTART = 1800;	int kYESTART = 2;	// год от которого идЄт поиск

int main()
{
	SetConsoleCP(1251); SetConsoleOutputCP(1251);
	do {
		system("cls");
		cout << endl;
		choice = menu();

		switch (choice)
		{
		case 'A':
		{
			int year = 0; int mo = 0; int k = 0; int CL = 0; int DAYS, DAYSO; bool visok; int COUNT = 0; int CMonth;
			cout << "√од ограничен: " << YESTART << " - минимальный; »— Ћё„≈Ќ»… Ќ≈“" << endl;
			while (!(year >= YESTART)) { cout << "¬ведите год: "; cin >> year; cout << " year: " << year << endl; }
			while (!(mo > 0 && mo <= 12)) { cout << "¬ведите номер мес€ца: ";   cin >> mo; cout << " mo: " << mo << endl; }
			while (!(COUNT > 0)) { cout << " оличество выводимых мес€цев на экран: "; cin >> COUNT; cout << "COUNTH: " << COUNT << endl; }
			cout << "1 - год дл€ всех; 2 - год дл€ каждого мес€ца: "; cin >> CMonth; cout << " CMonth: " << CMonth << endl;
			CL = abs(YESTART - year) * 12 + mo;
			cout << "CL = abs(YESTART - year) * 12 + mo: " << CL << endl;
			k = kYESTART;
			cout << "k начала поиска (" << YESTART << "): " << k << endl;
			k = MOUNTHDETERMINE(CL, k, visok, DAYS, DAYSO);
			cout << "k после поиска: " << k << endl;
			k = startmonthVERT(mo, COUNT, k, DAYS, DAYSO, year, CMonth);
			cout << "k после вывода: " << k << endl;
			system("pause");
		}
		break;
		case 'B':
		{
			int year = 0; int mo = 0; int k = 0; int CL = 0; int DAYS, DAYSO; bool visok; int COUNT = 0; int CMonth;
			cout << "√од ограничен: " << YESTART << " - минимальный; »— Ћё„≈Ќ»… Ќ≈“" << endl;
			while (!(year >= YESTART)) { cout << "¬ведите год: "; cin >> year; cout << " year: " << year << endl; }
			while (!(mo > 0 && mo <= 12)) { cout << "¬ведите номер мес€ца: ";   cin >> mo; cout << " mo: " << mo << endl; }
			while (!(COUNT > 0)) { cout << " оличество выводимых мес€цев на экран: "; cin >> COUNT; cout << "COUNTH: " << COUNT << endl; }
			cout << "1 - год дл€ всех; 2 - год дл€ каждого мес€ца: "; cin >> CMonth; cout << " CMonth: " << CMonth << endl;
			CL = abs(YESTART - year) * 12 + mo;
			cout << "CL = abs(YESTART - year) * 12 + mo: " << CL << endl;
			k = kYESTART;
			cout << "k начала поиска (" << YESTART << "): " << k << endl;
			k = MOUNTHDETERMINE(CL, k, visok, DAYS, DAYSO);
			cout << "k после поиска: " << k << endl;
			k = startmonthHORIZ(mo, COUNT, k, DAYS, DAYSO, year, CMonth);
			cout << "k после вывода: " << k << endl;
			system("pause");
		}
		break;
		case '1':
			try {
				ifstream file1("txt.txt");
					if (!file1.is_open()) file1.open("D:\\#яѕ\\C++\\04.12.2019  јЋ≈Ќƒј–№\\txt.txt");
				string X; int Instr = 0; char AA; string Y; int Orien = 0; string Z; int CMonth = 0;
				int year, month; int month1, month2; int year1, year2;
				if (!file1.is_open())
				{
					throw 0;
				}
				file1 >> X;
				for (itXFILE = Xfile.begin(); itXFILE != Xfile.end(); itXFILE++)
				{
					if (X == itXFILE->first) { Instr = itXFILE->second; cout << itXFILE->first; }
				}
				if (Instr) {
					if (Instr == 1)
					{
						file1 >> year;
						if (year < YESTART) throw 3;
						cout << " " << year;

					}
					else if (Instr == 2)
					{
						file1 >> month >> year;
						if (month <= 0 || month > 12) throw 4;
						if (year < YESTART) throw 3;
						cout << " " << month << " " << year;

					}
					else if (Instr == 3)
					{
						file1 >> month1 >> year1 >> month2 >> year2;
						if (year1 < YESTART || year2 < YESTART) throw 3;
						if (month1 <= 0 || month1 > 12 || month2 <= 0 || month2 > 12) throw 4;
						cout << " " << month1 << " " << year1 << " " << month2 << " " << year2;


					}
					else { throw 2; }
				}
				else throw 2;

				file1 >> AA;
				if (AA == '|') {
					file1 >> Y >> Z;
					cout << " " << AA;
				}
				else throw 1;
				for (itYFILE = Yfile.begin(); itYFILE != Yfile.end(); itYFILE++)
				{
					if (Y == itYFILE->first) { Orien = itYFILE->second; cout << " " << itYFILE->first; }
				}
				for (itZFILE = Zfile.begin(); itZFILE != Zfile.end(); itZFILE++)
				{
					if (Z == itZFILE->first) { CMonth = itZFILE->second; cout << " " << itZFILE->first; }
				}
				cout << endl;
				if (CMonth)
				{
					if (Orien)
					{
						if (Instr == 1) FYEAR(year, Orien, CMonth);
						if (Instr == 2) FMONTH(month, year, Orien, CMonth);
						if (Instr == 3) FRANGE(month1, month2, year1, year2, Orien, CMonth);
					}
					else throw 2;
				}
				else throw 2;
				file1.close();
				system("pause");
			}
			catch (int F)
			{
				if (F == 0)
				{
					cout << "####################################### \n";
					cout << "            ќшибка є " << F << endl;
					cout << " ‘айла нет.. ћожет, у теб€ получитс€ инвестировать " << endl;
					cout << " в американские акции?  стати, они *показывает вверх*" << endl;
					cout << "####################################### \n";
				}
				if (F == 1)
				{
					cout << "####################################### \n";
					cout << "            ќшибка є " << F << endl;
					cout << "   ! Ќе соблюдЄн формат в файле" << endl;
					cout << "####################################### \n";
				}
				if (F == 2)
				{
					cout << "####################################### \n";
					cout << "            ќшибка є " << F << endl;
					cout << "    ! Ќеверна€ инструкци€ вывода" << endl;
					cout << "####################################### \n";
				}
				if (F == 3)
				{
					cout << "####################################### \n";
					cout << "            ќшибка є " << F << endl;
					cout << "  ! ћинимальный поддерживаемый год: " << YESTART << endl;
					cout << "####################################### \n";
				}
				if (F == 4)
				{
					cout << "####################################### \n";
					cout << "            ќшибка є " << F << endl;
					cout << " ! Ќекорректно введено значение мес€ца(-ев)" << endl;
					cout << "####################################### \n";
				}
				system("pause");

			}
			break;
		case '0': cout << "¬ыход" << endl;  break;
		case '-': cout << "продам гараж" << endl; system("pause"); break;
		case 'Z': cout << "¬водим символ!" << endl; system("pause"); break;
		default: cout << "“акой вариант не предусмотрен." << endl; system("pause"); break;
		}
	} while (choice != '0');
	cout << "===============================================\n";
	system("pause");
	return 0;

}

bool viso(int& year)
{
	bool viso;
	if (year % 100 == 0)
	{
		if (year % 400 == 0) viso = true;
		else viso = false;
	}
	else
	{
		if (year % 4 == 0) viso = true;
		else viso = false;
	}
	return viso;
}
void swap(int& a, int& b)
{
	int temp; temp = a; a = b; b = temp;
}
char menu()
{
	string s;
	printf("%04d", YESTART);
	cout << " : (" << kYESTART << ") " << endl;
	cout << "===============================================\n";
	cout << "A. VERT any year\n"
		<< "B. HORIZ any year\n"
		<< "\tv\n"
		<< "\t1. –јЅќ“ј — ‘ј…Ћќћ\n"
		<< "\t^\n"
		<< "0. Ћиваем нафик\n";
	cout << "===============================================\n";
	cout << "¬ыбор:"; cin >> s;
	cout << "===============================================\n";
	choice = s[0]; if (s[1]) choice = 'Z';
	return choice;
}

// «ј√Ћј¬Ќјя ‘”Ќ ÷»я вывода
// в функцию передаЄтс€ известные k, DAYS и DAYSO - известные после функции FORMONTHDETERMINE
// mo определ€ет DAYS дл€ следующего мес€ца
int startmonthVERT(int& mo, int& COUNT, int& k, int& DAYS, int& DAYSO, int& year, int& CMonth)
{
	cout << "===============================================\n\n";
	int day = 0; int n = 0; int moFor = mo; int YE = year;
	if (moFor >= ((moFor) / 12) * 13)
	{
		YE = year + ((moFor - 1) / 12);
		moFor -= 12 * ((moFor - 1) / 12);

	}
	for (itMOUNTH = mounth.begin(); itMOUNTH != mounth.end(); itMOUNTH++)
	{
		if (itMOUNTH->first == moFor) {
			if (CMonth == 1) // ne nado dop usloviy - perviy mecyac
			{
				cout << "=========================|" << YE << " " << endl;
			}
			cout << "     " << itMOUNTH->second;
			if (CMonth == 2) cout << "   " << YE;
			cout << endl;

		}
	}
	for (itWEEKDAY = weekday.begin(); itWEEKDAY != weekday.end(); itWEEKDAY++)
	{							// вывод первого(выбранного) мес€ца
		cout << itWEEKDAY->second << " ";
		if (itWEEKDAY == weekday.begin()) { n -= k; k = 0; }
		for (day = n + 1; day <= DAYS;) {
			if (day <= 0) {
				printf(" %s ", s);
				day += 7;
				k++;
			}
			else {
				printf(" %02d ", day);
				day += 7;
			}

		}
		n++;
		cout << endl;
	}
	DAYSO = DAYS;
	if (mo == 1)
	{
		if (viso(year)) DAYS = 29;
		else DAYS = 28;
	}
	if (mo == 2 || mo == 4 || mo == 6 || mo == 7 || mo == 9 || mo == 11 || mo == 12)
	{
		DAYS = 31;
	}
	else DAYS = 30;

	forMVERT(mo, COUNT, k, DAYS, DAYSO, year, CMonth);

	return k;
}

// внос€тс€ k прошлого мес€ца, DAYS нынешнего и DAYSO прошлого
// используетс€ дл€ вывода и FOR
int monthVERT(int& mo, int& COUNT, int& k, int& DAYS, int& DAYSO, int& year, int& CMonth) // дл€ вывода св€зного мес€ца
{
	int day = 0; int n = 0; int moFor = mo; int YE = year;

	if (moFor >= ((moFor) / 12) * 12)
	{
		YE = year + ((moFor - 1) / 12);
		moFor -= 12 * ((moFor - 1) / 12);
	}
	for (itMOUNTH = mounth.begin(); itMOUNTH != mounth.end(); itMOUNTH++)
	{
		if (itMOUNTH->first == moFor)
		{
			if (CMonth == 1 && moFor == 1)
			{
				cout << "=========================|" << YE << " " << endl;
			}
			cout << "     " << itMOUNTH->second;
			if (CMonth == 2) cout << "   " << YE;
			cout << endl;
		}
	}
	for (itWEEKDAY = weekday.begin(); itWEEKDAY != weekday.end(); itWEEKDAY++)
	{
		cout << itWEEKDAY->second << " ";
		if (itWEEKDAY == weekday.begin() && DAYSO == 31) {		// услови€
			n = -k - 3; k = 0;									// дл€
		}														// сдвига
		if (itWEEKDAY == weekday.begin() && DAYSO == 30) {		// от предыдущего
			n = -k - 2; k = 0;									// мес€ца
		}
		if (itWEEKDAY == weekday.begin() && DAYSO == 29) {
			n = -k - 1; k = 0;
		}
		if (itWEEKDAY == weekday.begin() && DAYSO == 28) {
			n = -k - 0; k = 0;
		}
		if (n <= -7) n = n + 7;
		// если количество "отступов" в нынешнем мес€це превышает
		// количество дней в неделе в силу форумлы - сдвигаемс€ на эту неделю
		// оправдано тем, что если оступов больше 4х, происходит сдвиг в предыдущем мес€це
		// и выход 1-2 дней на новый столбец
		// по алгоритму: предпоследний столбец должен оставить за собой полосу пустых клеток
		for (day = n + 1; day <= DAYS;)
		{

			if (day <= 0)
			{
				printf(" %s ", s);
				day += 7;
				k++;
			}
			else if (day > 0 && day <= DAYS) {
				printf(" %02d ", day);
				day += 7;
			}

		}
		cout << endl;
		n++;

	}
	cout << "\n";
	return k;
}

// в функцию передаютс€: необходимый мес€ц mo дл€ начала отсчЄта; количество выводимых мес€цев COUNT;
// k от заглавного мес€ца, DAYS, DAYSO дл€ следующего (определ€етс€ в заглавной ф.);
// year дл€ возможного "перепрыга" на другой год
void forMVERT(int& mo, int& COUNT, int& k, int& DAYS, int& DAYSO, int& year, int& CMonth)
{												// функци€ вывода нескольких следующих друг за другом мес€цев
	bool visok; int moF;
	cout << endl;
	for (int i = mo + 1; i < COUNT + mo; i++)	// mo+1 т.к. учтЄн предыдущий мес€ц
	{
		if ((i - 2) % 12 == 0)				// если февраль
		{
			int YE = year + (i - 1) / 12;
			visok = viso(YE);				// високосного года?
			if (visok) DAYS = 29;
			else DAYS = 28;
		}
		if ((i - 13) % 12 == 0)
		{										// "13" мес€ц - следующий €нварь
			DAYS = 31; DAYSO = 31;				// его прошлым был декабрь с 31 днЄм
		}
		if ((i - 8) % 12 == 0)
		{
			DAYS = 31; DAYSO = 31;				 // июль-август
		}
		if (DAYS == 28)
		{
			moF = i;
			k = monthVERT(moF, COUNT, k, DAYS, DAYSO, year, CMonth);
			DAYSO = 28; DAYS = 31;
		}
		else if (DAYS == 29)
		{
			moF = i;
			k = monthVERT(moF, COUNT, k, DAYS, DAYSO, year, CMonth);
			DAYSO = 29; DAYS = 31;
		}
		else if (DAYS == 30)
		{
			moF = i;
			k = monthVERT(moF, COUNT, k, DAYS, DAYSO, year, CMonth);
			DAYSO = 30; DAYS = 31;
		}
		else if (DAYS == 31)
		{
			moF = i;
			k = monthVERT(moF, COUNT, k, DAYS, DAYSO, year, CMonth);
			DAYSO = 31; DAYS = 30;
		}
	}
}




int MOUNTHDETERMINE(int& CL, int& k, bool& visok, int& DAYS, int& DAYSO)
{
	if (CL > 5000) cout << "\n считаем...\n";
	k = kYESTART; // €нварь года YESTART
	int day = 0; int n = 0;
	DAYS = 31;
	for (itWEEKDAY = weekday.begin(); itWEEKDAY != weekday.end(); itWEEKDAY++)
	{
		if (itWEEKDAY == weekday.begin()) { n -= k; k = 0; }
		for (day = n + 1; day <= DAYS;) {
			if (day <= 0) {
				// здесь €кобы пропуск
				day += 7;
				k++;
			}
			else {
				// здесь €кобы пишем
				day += 7;


			}

		}
		n++;
	}
	DAYSO = DAYS;
	int YE = YESTART;
	visok = viso(YE);
	if (visok) DAYS = 29;
	else DAYS = 28;
	FORMONTHDETERMINE(CL, k, DAYS, DAYSO);
	swap(DAYS, DAYSO); // они свапаютс€ в функци€х FOR, надо возвращать
	return k;
}

int MONTHDETERMINE(int& k, int& DAYS, int& DAYSO) {
	int day = 0;  int n = 0;
	for (itWEEKDAY = weekday.begin(); itWEEKDAY != weekday.end(); itWEEKDAY++)
	{
		if (itWEEKDAY == weekday.begin() && DAYSO == 31) {
			n = -k - 3; k = 0;
		}
		if (itWEEKDAY == weekday.begin() && DAYSO == 30) {
			n = -k - 2; k = 0;
		}
		if (itWEEKDAY == weekday.begin() && DAYSO == 29) {
			n = -k - 1; k = 0;
		}
		if (itWEEKDAY == weekday.begin() && DAYSO == 28) {
			n = -k - 0; k = 0;
		}
		if (n <= -7) n = n + 7;
		for (day = n + 1; day <= DAYS;) {
			if (day <= 0) {
				day += 7;
				k++;
			}
			else if (day > 0 && day <= DAYS) {
				day += 7;
			}

		}
		n++;
	}
	return k;
}

int FORMONTHDETERMINE(int& CL, int& k, int& DAYS, int& DAYSO)
{
	bool visok;
	for (int i = 2; i <= CL; i++)
	{
		if (CL > 5000 && i == CL / 2) cout << "...половину посчитали\n";
		if ((i - 2) % 12 == 0)
		{
			int YE = YESTART + (i - 1) / 12;
			visok = viso(YE);
			if (visok) DAYS = 29;
			else DAYS = 28;
			DAYSO = 31;
		}
		if ((i - 13) % 12 == 0)
		{
			DAYS = 31; DAYSO = 31;
		}
		if ((i - 8) % 12 == 0)
		{
			DAYS = 31; DAYSO = 31;
		}

		if (DAYS == 28)
		{
			k = MONTHDETERMINE(k, DAYS, DAYSO);
			DAYSO = 28; DAYS = 31;
		}
		else if (DAYS == 29)
		{
			k = MONTHDETERMINE(k, DAYS, DAYSO);
			DAYSO = 29; DAYS = 31;
		}
		else if (DAYS == 30)
		{
			k = MONTHDETERMINE(k, DAYS, DAYSO);
			DAYSO = 30; DAYS = 31;
		}
		else if (DAYS == 31)
		{
			k = MONTHDETERMINE(k, DAYS, DAYSO);
			DAYSO = 31; DAYS = 30;
		}
	}
	return k;
}



int startmonthHORIZ(int& mo, int& COUNT, int& k, int& DAYS, int& DAYSO, int& year, int& CMonth)
{
	cout << "===============================================\n\n";
	int day = 0; int n = 0; int moFor = mo; int YE = year;
	if (moFor >= ((moFor) / 12) * 13)
	{
		YE = year + ((moFor - 1) / 12);
		moFor -= 12 * ((moFor - 1) / 12);

	}
	for (itMOUNTH = mounth.begin(); itMOUNTH != mounth.end(); itMOUNTH++)
	{
		if (itMOUNTH->first == moFor) {
			if (CMonth == 1) // ne nado dop usloviy - perviy mecyac
			{
				cout << "=========================|" << YE << " " << endl;
			}
			cout << "     " << itMOUNTH->second;
			if (CMonth == 2) cout << "   " << YE;
			cout << endl;

		}
	}

	for (itWEEKDAY = weekday.begin(); itWEEKDAY != weekday.end(); itWEEKDAY++)
	{
		cout << " " << itWEEKDAY->second << " ";
	}
	cout << endl;
	n -= k; k = 0;
	for (day = n + 1; day <= DAYS;)
	{
		for (int z = 0; z < 7; z++)
		{
			if (day <= 0)
			{
				printf(" %s ", s);
				day += 1; k++;
			}
			else if (day > 0 && day <= DAYS)
			{
				printf(" %02d ", day);
				day += 1;
			}
		}
		cout << endl;
	}

	DAYSO = DAYS;
	if (mo == 1)
	{
		if (viso(year)) DAYS = 29;
		else DAYS = 28;
	}
	if (mo == 2 || mo == 4 || mo == 6 || mo == 7 || mo == 9 || mo == 11 || mo == 12)
	{
		DAYS = 31;
	}
	else DAYS = 30;

	forMHORIZ(mo, COUNT, k, DAYS, DAYSO, year, CMonth);

	return k;

}

int monthHORIZ(int& mo, int& COUNT, int& k, int& DAYS, int& DAYSO, int& year, int& CMonth)
{
	int day = 0; int n = 0; int moFor = mo; int YE = year;

	if (moFor >= ((moFor) / 12) * 12)
	{
		YE = year + ((moFor - 1) / 12);
		moFor -= 12 * ((moFor - 1) / 12);
	}
	for (itMOUNTH = mounth.begin(); itMOUNTH != mounth.end(); itMOUNTH++)
	{
		if (itMOUNTH->first == moFor)
		{
			if (CMonth == 1 && moFor == 1)
			{
				cout << "=========================|" << YE << " " << endl;
			}
			cout << "     " << itMOUNTH->second;
			if (CMonth == 2) cout << "   " << YE;
			cout << endl;
		}
	}
	for (itWEEKDAY = weekday.begin(); itWEEKDAY != weekday.end(); itWEEKDAY++)
	{
		cout << " " << itWEEKDAY->second << " ";
		if (itWEEKDAY == weekday.begin() && DAYSO == 31) {
			n = -k - 3; k = 0;
		}
		if (itWEEKDAY == weekday.begin() && DAYSO == 30) {
			n = -k - 2; k = 0;
		}
		if (itWEEKDAY == weekday.begin() && DAYSO == 29) {
			n = -k - 1; k = 0;
		}
		if (itWEEKDAY == weekday.begin() && DAYSO == 28) {
			n = -k - 0; k = 0;
		}
		if (n <= -7) n = n + 7;

	}
	cout << endl;
	for (day = n + 1; day <= DAYS;)
	{
		for (int z = 0; z < 7; z++)
		{
			if (day <= 0)
			{
				printf(" %s ", s);
				day += 1; k++;
			}
			else if (day > 0 && day <= DAYS)
			{
				printf(" %02d ", day);
				day += 1;
			}
		}
		cout << endl;
	}

	cout << "\n";
	return k;
}

void forMHORIZ(int& mo, int& COUNT, int& k, int& DAYS, int& DAYSO, int& year, int& CMonth)
{												// функци€ вывода нескольких следующих друг за другом мес€цев
	bool visok; int moF;
	cout << endl;
	for (int i = mo + 1; i < COUNT + mo; i++)	// mo+1 т.к. учтЄн предыдущий мес€ц
	{
		if ((i - 2) % 12 == 0)				// если февраль
		{
			int YE = year + (i - 1) / 12;
			visok = viso(YE);				// високосного года?
			if (visok) DAYS = 29;
			else DAYS = 28;
		}
		if ((i - 13) % 12 == 0)
		{										// "13" мес€ц - следующий €нварь
			DAYS = 31; DAYSO = 31;				// его прошлым был декабрь с 31 днЄм
		}
		if ((i - 8) % 12 == 0)
		{
			DAYS = 31; DAYSO = 31;				 // июль-август
		}
		if (DAYS == 28)
		{
			moF = i;
			k = monthHORIZ(moF, COUNT, k, DAYS, DAYSO, year, CMonth);
			DAYSO = 28; DAYS = 31;
		}
		else if (DAYS == 29)
		{
			moF = i;
			k = monthHORIZ(moF, COUNT, k, DAYS, DAYSO, year, CMonth);
			DAYSO = 29; DAYS = 31;
		}
		else if (DAYS == 30)
		{
			moF = i;
			k = monthHORIZ(moF, COUNT, k, DAYS, DAYSO, year, CMonth);
			DAYSO = 30; DAYS = 31;
		}
		else if (DAYS == 31)
		{
			moF = i;
			k = monthHORIZ(moF, COUNT, k, DAYS, DAYSO, year, CMonth);
			DAYSO = 31; DAYS = 30;
		}
	}
}





void FMONTH(int& month, int& year, int& Orien, int& CMonth)
{
	int k;  int CL; bool visok; int DAYS = 0, DAYSO = 0;
	CL = abs(YESTART - year) * 12 + month;
	k = MOUNTHDETERMINE(CL, k, visok, DAYS, DAYSO);

	int COUNT = 1;


	if (Orien == 1) k = startmonthVERT(month, COUNT, k, DAYS, DAYSO, year, CMonth);
	if (Orien == 2) k = startmonthHORIZ(month, COUNT, k, DAYS, DAYSO, year, CMonth);
}

void FRANGE(int& month1, int& month2, int& year1, int& year2, int& Orien, int& CMonth)
{
	int DAYS = 0, DAYSO = 0; int k = 0; bool visok; int CL, COUNT;
	if (year2 < year1)
	{
		swap(month1, month2);
		swap(year1, year2);
	}
	CL = abs(YESTART - year1) * 12 + month1;
	k = MOUNTHDETERMINE(CL, k, visok, DAYS, DAYSO);

	if (year2 > year1)							// -1, т.к. первый год заполн€етс€ отдельно
												// +1 отсутствует, т.к. второй год заполн€етс€ отдельно 
	{
		COUNT = (12 - month1 + 1) + (month2)+abs(year2 - year1 - 1) * 12;
	}
	else if (year2 < year1)
	{
		swap(year2, year1);
		COUNT = (12 - month1 + 1) + (month2)+abs(year2 - year1 - 1) * 12;
	}
	else if (year2 == year1)
	{
		COUNT = month2 - month1 + 1;
	}

	if (Orien == 1) k = startmonthVERT(month1, COUNT, k, DAYS, DAYSO, year1, CMonth);
	if (Orien == 2) k = startmonthHORIZ(month1, COUNT, k, DAYS, DAYSO, year1, CMonth);
}

void FYEAR(int& year, int& Orien, int& CMonth)
{
	int k;  int CL; bool visok; int DAYS = 0, DAYSO = 0;
	int month = 1;
	CL = abs(YESTART - year) * 12 + month;
	k = MOUNTHDETERMINE(CL, k, visok, DAYS, DAYSO);
	int COUNT = 12;

	if (Orien == 1) k = startmonthVERT(month, COUNT, k, DAYS, DAYSO, year, CMonth);
	if (Orien == 2) k = startmonthHORIZ(month, COUNT, k, DAYS, DAYSO, year, CMonth);
}