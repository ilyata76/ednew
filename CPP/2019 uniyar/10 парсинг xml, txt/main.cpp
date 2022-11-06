#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include "dies.h"

using namespace std;



typedef int parttype;
typedef string partname;

////////////////////////////////////////////////////////////////

class DATA
{
public: int dealtype; string dealname; string issname; double amount; dies date;
	  vector<parttype> PARTTYPE; vector<partname> PARTNAME;
	  DATA() {}; ~DATA() {};
};

////////////////////////////////////////////////////////////////

class state
{
public:
	virtual string stateinfo() = 0;
};

class entered : public state
{
public:
	string stateinfo() override { return "Введена"; }
};

class confirmed : public state
{
public:
	string stateinfo() override { return "Верифицирована"; }
};

class verified : public state
{
public:
	string stateinfo() override { return "Подтверждена"; }
};

////////////////////////////////////////////////////////////////
class FILES;

class base
{
private:
	base* next = NULL;
protected:
	DATA datik; FILES* failik;
public:
	base() {};
	base(DATA& A) { this->datik = A; }
	void add(base* n)
	{
		if (next) next->add(n); else next = n;
	}
	void nextt()
	{
		next->pass();
	}
	virtual bool pass() = 0;
};
class H1 : public base
{
public:
	H1() {};
	H1(DATA& A) { this->datik = A; };
	bool pass()
	{
		if (this->datik.dealtype == 2) { Sleep(5000); cout << "DEALTYPE == 2. ПОДТВЕРЖДЕНО\n"; base::nextt(); }
		else { cout << " dealtype != 2 " << endl; return false; }
	}
};
class H2 : public base
{
public:
	H2() {};
	H2(DATA& A) { this->datik = A; };
	bool pass()
	{
		int C1 = 0, C2 = 0;
		for (int k = 0; k < this->datik.PARTTYPE.size(); k++)
		{
			if (this->datik.PARTTYPE[k] == 1) C2++;
			if (this->datik.PARTTYPE[k] == 3) C1++;
		}
		if (C1 && C2) { Sleep(5000); cout << "PARTTYPE == 1 && 3. ПОДТВЕРЖДЕНО\n"; base::nextt(); }
		else if (C1 && !C2) { cout << "Участник с типом 1 отсутствует\n"; return false; }
		else if (C2 && !C1) { cout << "Участник с типом 3 отсутствует\n"; return false; }
		else { cout << "всё плохо\n"; return false; }
	}
};
class H3 : public base
{
public:
	H3() {};
	H3(DATA& A) { this->datik = A; };
	bool pass()
	{
		if (this->datik.amount >= 0) {
			Sleep(5000); cout << "AMOUNT > 0. ПОДТВЕРЖДЕНО\n"; return true;
		}
		else { cout << "amount < 0\n"; return false; }
	}
};

////////////////////////////////////////////////////////////////
class Memento;
class FILES
{
protected: int dealtype; string dealname; string issname; double amount; dies date;
		 vector<parttype> PARTTYPE; vector<partname> PARTNAME; state* CURRENT; DATA datas;
		 Memento* M;
public:
	FILES() {};
	virtual void OUTPUTFULL() = 0;
	string TYPE(int C) {
		if (C == 1) return "брокерская";
		else if (C == 2) return "собственная";
		else if (C == 3) return "между компаниями";
		else return "ЖОПА";
	}
	virtual void CURRENTLY(int i = 0, int j = 0) { ; }
	~FILES() {};

	class Memento
	{
		friend class FILES;
	private:
		int dealtype; string dealname; string issname; double amount; dies date;
		vector<parttype> PARTTYPE; vector<partname> PARTNAME; state* CURRENT; DATA datas;
		FILES* fil; // указатель на объект - тот же из-за указателей?????????
	public:
		Memento() {}
		void restore() {
			fil->dealtype = this->dealtype; fil->dealname = this->dealname; fil->issname = this->issname;
			fil->amount = this->amount; fil->date = this->date; fil->PARTTYPE = this->PARTTYPE; fil->PARTNAME = this->PARTNAME;
			fil->CURRENT = this->CURRENT; fil->datas = this->datas;
		}
	};

	virtual Memento* getMemento() {
		Memento* m = new Memento;
		m->fil = this; m->dealtype = this->dealtype; m->dealname = this->dealname; m->issname = this->issname;
		m->amount = this->amount; m->date = this->date; m->PARTTYPE = this->PARTTYPE; m->PARTNAME = this->PARTNAME;
		m->CURRENT = this->CURRENT; m->datas = this->datas;
		return m;
	}

	virtual bool ALL() { return false; }
	virtual bool restor() { return false; }
	virtual void out() { ; }
};

class FILETXT : public FILES
{
public:
	Memento* m1; Memento* m2; Memento* m3;
public:
	FILETXT() {};
	FILETXT(DATA& X) {
		dealtype = X.dealtype; dealname = X.dealname; issname = X.issname; amount = X.amount; date = X.date; PARTTYPE = X.PARTTYPE; PARTNAME = X.PARTNAME; datas = X; this->CURRENT = new entered;
	};
	//FILEXML(FILEXML* A) {};
	//FILEXML(FILEXML* A, DATA& X) {};
	void OUTPUTFULL() override {
		cout << "\n==========//ИНФОРМАЦИЯ//============\n";
		cout << "НАЗВАНИЕ СДЕЛКИ: " << this->dealname << " ТИП СДЕЛКИ: " << this->TYPE(this->dealtype) << " НАЗВАНИЕ ЦЕННОЙ БУМАГИ: " << this->issname << endl <<
			" СТОИМОСТЬ: " << this->amount << " ДАТА: " << this->date << endl << "___" << endl;
		for (int i = 0; i < PARTTYPE.size(); i++)
			cout << "[" << i << "]" << "  PARTTYPE: " << PARTTYPE[i] << " PARTNAME: " << PARTNAME[i] << endl; cout << "CURRENT: " << this->CURRENT->stateinfo() << endl;
	}

	void CURRENTLY(int i = 0, int j = 0) override
	{
		cout << "\n==========//ОБРАБОТКА//============\n";
		cout << " ! " << this->CURRENT->stateinfo() << " ! \n";
		cout << "Делаем снимок" << endl; this->m1 = this->getMemento();
		H1 one(this->datas); H2 two(this->datas); H3 three(this->datas); one.add(&two); one.add(&three);
		if (one.pass()) {
			this->CURRENT = new confirmed; cout << " ! " << this->CURRENT->stateinfo() << " ! \n";
			cout << "Делаем снимок" << endl; this->m2 = this->getMemento(); Sleep(5000);
			this->CURRENT = new verified; cout << " ! " << this->CURRENT->stateinfo() << " ! \n";
			cout << "Делаем снимок" << endl; this->m3 = this->getMemento(); Sleep(5000);
		}
	}

	bool ALL() override
	{
		this->OUTPUTFULL(); this->CURRENTLY(); cout << "CURRENT: " << this->CURRENT->stateinfo() << endl;

		if (this->CURRENT->stateinfo() == "Верифицирована" || this->CURRENT->stateinfo() == "Подтверждена") {
			return true;
		}
		else return false;
	}

	bool restor() override
	{
		if (this->CURRENT->stateinfo() == "Верифицирована" || this->CURRENT->stateinfo() == "Подтверждена") {
			cout << " Восстанавливаем через снимок" << endl; Sleep(3000);
			cout << "CURRENT: " << this->CURRENT->stateinfo(); m2->restore();
			cout << "\n||||СНИМОК||||\n"; OUTPUTFULL(); cout << "\n||||\n";
			m1->restore(); Sleep(2000);
			cout << "\n||||СНИМОК||||\n"; OUTPUTFULL(); cout << "\n||||\n";
			return true;
		}
		else cout << "Нечего откатывать\n"; return false;
	}

	void out() override
	{
		cout << "НАЗВАНИЕ СДЕЛКИ: " << this->dealname << " CUR: " << this->CURRENT->stateinfo() << " ТИП СДЕЛКИ: " << this->TYPE(this->dealtype) << " НАЗВАНИЕ ЦЕННОЙ БУМАГИ: " << this->issname << endl;
	}
};

class FILEXML : public FILES
{
public:
	Memento* m1; Memento* m2; Memento* m3;
public:
	FILEXML() {};
	FILEXML(DATA& X) {
		dealtype = X.dealtype; dealname = X.dealname; issname = X.issname; amount = X.amount; date = X.date; PARTTYPE = X.PARTTYPE; PARTNAME = X.PARTNAME; datas = X; this->CURRENT = new entered;
	};
	//FILEXML(FILEXML* A) {};
	//FILEXML(FILEXML* A, DATA& X) {};
	void OUTPUTFULL() override {
		cout << "\n==========//ИНФОРМАЦИЯ//============\n";
		cout << "НАЗВАНИЕ СДЕЛКИ: " << this->dealname << " ТИП СДЕЛКИ: " << this->TYPE(this->dealtype) << " НАЗВАНИЕ ЦЕННОЙ БУМАГИ: " << this->issname << endl <<
			" СТОИМОСТЬ: " << this->amount << " ДАТА: " << this->date << endl << "___" << endl;
		for (int i = 0; i < PARTTYPE.size(); i++)
			cout << "[" << i << "]" << "  PARTTYPE: " << PARTTYPE[i] << " PARTNAME: " << PARTNAME[i] << endl; cout << "CURRENT: " << this->CURRENT->stateinfo() << endl;
	}

	void CURRENTLY(int i = 0, int j = 0) override
	{
		cout << "\n==========//ОБРАБОТКА//============\n";
		cout << " ! " << this->CURRENT->stateinfo() << " ! \n";
		cout << "Делаем снимок" << endl; this->m1 = this->getMemento();
		H1 one(this->datas); H2 two(this->datas); H3 three(this->datas); one.add(&two); one.add(&three);
		if (one.pass()) {
			this->CURRENT = new confirmed; cout << " ! " << this->CURRENT->stateinfo() << " ! \n";
			cout << "Делаем снимок" << endl; this->m2 = this->getMemento(); Sleep(5000);
			this->CURRENT = new verified; cout << " ! " << this->CURRENT->stateinfo() << " ! \n";
			cout << "Делаем снимок" << endl; this->m3 = this->getMemento(); Sleep(5000);
		}
	}

	bool ALL() override
	{
		this->OUTPUTFULL(); this->CURRENTLY(); cout << "CURRENT: " << this->CURRENT->stateinfo() << endl;

		if (this->CURRENT->stateinfo() == "Верифицирована" || this->CURRENT->stateinfo() == "Подтверждена") {
			return true;
		}
		else return false;
	}

	bool restor() override
	{
		if (this->CURRENT->stateinfo() == "Верифицирована" || this->CURRENT->stateinfo() == "Подтверждена") {
			cout << " Восстанавливаем через снимок" << endl; Sleep(3000);
			cout << "CURRENT: " << this->CURRENT->stateinfo(); m2->restore();
			cout << "\n||||СНИМОК||||\n"; OUTPUTFULL(); cout << "\n||||\n";
			m1->restore(); Sleep(2000);
			cout << "\n||||СНИМОК||||\n"; OUTPUTFULL(); cout << "\n||||\n";
			return true;
		}
		else cout << "Нечего откатывать\n"; return false;
	}

	void out() override
	{
		cout << "НАЗВАНИЕ СДЕЛКИ: " << this->dealname << " CUR: " << this->CURRENT->stateinfo() << " ТИП СДЕЛКИ: " << this->TYPE(this->dealtype) << " НАЗВАНИЕ ЦЕННОЙ БУМАГИ: " << this->issname << endl;
	}
};

//////////////////////////////////////////

string firstcode(ifstream& file)
{
	string A; char B;
	if (file.is_open())
		if (!file.eof())
			do { file >> B; A.push_back(B); } while (B != '>');
	return A;
}

bool comm(string A) { if (A[0] == '<' && A[1] == '!') return true; else return false; }

string get(ifstream& file)
{
	char B = 0; string A; string BB;
	A += firstcode(file);
	if (!comm(A) && A != "</SecurityDeal>")
		if (file.is_open())
			if (!file.eof())
				while (B != '>') { file.read(&B, 1); A.push_back(B); }
			else {}
		else {}
	else if (A == "</SecurityDeal>") return A;
	else { return A = { '<', '!' }; }
	return A;
}
string getstr(string& A, int i); int getpart(ifstream& file, string& X, string& Y);
string getblock(ifstream& file, string& B, string& C, string& D, string& E, string& F, string& G, string& K,
	vector<parttype>& PARTTYPE, vector<partname>& PARTNAME)
{
	string A; string X; string Y;
	// A = firstcode(file); // <securlist
	A = B = firstcode(file); // <secur
	if (A == "</SecurityDealList>") { return A; }

Cget: if (!comm(A)) C = get(file); //name
else { A = B = firstcode(file); goto Cget; }

Dget: if (!comm(C)) D = get(file); //type
else { C = get(file); goto Dget; }

Eget: if (!comm(D)) E = get(file); // имя бумаги
else { D = get(file); goto Eget; }

Fget: if (!comm(E)) F = get(file); // сумма
else { E = get(file); goto Fget; }

Gget: if (!comm(F)) G = get(file); // дата
else { F = get(file); goto Gget; }

PARTTYPE.clear(); PARTNAME.clear();
int Z = 0;
Zget: Z = getpart(file, X, Y);
if (Z == 1) {
	PARTTYPE.push_back(X[10] - '0');
	PARTNAME.push_back(getstr(Y, 10));
	// cout << "вперёд на goto\n"; cout << Y;
	goto Zget;
}
else if (Z == 0) K = X;

return B + C + D + E + F + G + K;
}

int getpart(ifstream& file, string& X, string& Y)
{
Xget: X = get(file);	//parttype
	if (comm(X)) goto Xget;
	if (X == "</SecurityDeal>") { return 0; }
	else {
	Yget: if (!comm(X)) Y = get(file);	//partname
	else { X = get(file); goto Yget; }
	return 1;
	}
}

dies getdate(string A, string AA)
{
	string B, C, D; int Bi, Ci, Di;
	if (AA == "XML") {
		for (int i = 14; i < 18; i++) B.push_back(A[i]);
		for (int i = 19; i < 21; i++) C.push_back(A[i]);
		for (int i = 22; i < 24; i++) D.push_back(A[i]);
		Bi = stoi(B); Ci = stoi(C); Di = stoi(D); return { Di,Ci,Bi };
	}
	else if (AA == "TXT")
	{
		for (int i = 0; i < 4; i++) B.push_back(A[i]);
		for (int i = 5; i < 7; i++) C.push_back(A[i]);
		for (int i = 8; i < 10; i++) D.push_back(A[i]);
		Bi = stoi(B); Ci = stoi(C); Di = stoi(D); return { Bi,Ci,Di };
	}
	else cout << "што-то не так";
}
//////
vector <DATA> DVXML; vector <DATA> DVTXT;
/////
string getstr(string& A, int i) { string B; for (int j = i; A[j] != '<'; j++) B.push_back(A[j]); return B; }

string XML(ifstream& file)
{
	string B, C, D, E, F, G, K; vector<parttype> PARTTYPE; vector<partname> PARTNAME;
	DATA XX; string str, A, X;  do { str = firstcode(file); } while (comm(str)); X += str;
	for (int i = 1; A != "</SecurityDealList>"; i++)
	{
		A = getblock(file, B, C, D, E, F, G, K, PARTTYPE, PARTNAME);
		if (A != "</SecurityDealList>") {
			XX.dealname = getstr(C, 10); XX.dealtype = D[10] - '0';
			XX.issname = getstr(E, 12); XX.amount = stod(getstr(F, 8)); XX.date = getdate(G, "XML");
			XX.PARTNAME = PARTNAME; XX.PARTTYPE = PARTTYPE; DVXML.push_back(XX); X += A;
		}
		else { X += A; }
	}										// i-тый блок
	return X;
}


string gettxtblock(ifstream& file)
{
	string A; char XX; DATA PP; string B, C, D, F, E; int i;
	string p1, pn1, p3, pn3, p2, pn2; string X;
	if (file.is_open()) while (!file.eof())
	{
		getline(file, A);
		if (A[0] == '!') break; i = 0; i = 0;
		for (; A[i] != '-'; i++) B.push_back(A[i]);
		for (int j = 0; j < B.size() - 1; j++) X.push_back(B[j]); B = X;

		i++; i++; for (; A[i] != ';'; i++) C.push_back(A[i]);
		i++; i++; for (; A[i] != ';'; i++) D.push_back(A[i]);
		i++; i++; for (; A[i] != ';'; i++) F.push_back(A[i]);
		i++; i++; for (; A[i] != ';'; i++) E.push_back(A[i]);

		i++; i++; for (; A[i] != '-'; i++) p1.push_back(A[i]);
		i++; for (; A[i] != '_'; i++) pn1.push_back(A[i]);
		i++; for (; A[i] != '-'; i++) p3.push_back(A[i]);
		i++; for (; A[i] != '_'; i++) pn3.push_back(A[i]);
		i++; for (; A[i] != '-'; i++) p2.push_back(A[i]);
		i++; for (; A[i] != '.'; i++) pn2.push_back(A[i]);

		PP.dealname = B;
		PP.dealtype = stoi(C);
		PP.issname = D;
		PP.amount = stod(F);
		PP.date = getdate(E, "TXT");
		PP.PARTTYPE.push_back(stoi(p1));
		PP.PARTTYPE.push_back(stoi(p2));
		PP.PARTTYPE.push_back(stoi(p3));

		PP.PARTNAME.push_back(pn1);
		PP.PARTNAME.push_back(pn2);
		PP.PARTNAME.push_back(pn3);

		B.clear(); X.clear(); C.clear(); D.clear(); F.clear(); E.clear(); p1.clear(); pn1.clear();
		p2.clear(); p3.clear(); pn2.clear(); pn3.clear();

		DVTXT.push_back(PP);
		PP.PARTTYPE.clear(); PP.PARTNAME.clear();
	}
	return B + C + D + E + F;
}
string TXT(ifstream& file) { string A; char X; string B, C, D, E, F; getline(file, A); A.clear(); gettxtblock(file); return A; }

//class DATA
//{
//public: int dealtype; string dealname; string issname; double amount; dies date;
//	  vector<parttype> PARTTYPE; vector<partname> PARTNAME;
//	  DATA() {}; ~DATA() {};
//};



vector <FILES*> ALL;

int choice = 0;

int menu()
{
	for (int i = 0; i < ALL.size(); i++) {
		cout << "[" << i << "]";   ALL[i]->out();
	}
	cout
		<< "---------\n"
		<< "| 1. Парсировать всё\n"
		<< "| 2. Показать\n"
		<< "| 3. Загрузка\n"
		<< "| 4. Откатить n-ный элемент\n"
		<< "| 0. Vihod\n"
		<< "---------\n";
	cout << "Ваш выбор: "; cin >> choice; return choice;
}

void PAR()
{
	for (int i = 0; i < DVXML.size(); i++)
		ALL.push_back(new FILEXML(DVXML[i]));
	for (int i = 0; i < DVTXT.size(); i++)
		ALL.push_back(new FILETXT(DVTXT[i]));
}

void SHOW()
{
	for (int i = 0; i < ALL.size(); i++)
		ALL[i]->OUTPUTFULL();
}

void ALLS()
{
	for (int i = 0; i < ALL.size(); i++)
		ALL[i]->ALL();

}

void RESTORELEMENT()
{
	int n; cout << "Введите номер элемента: "; cin >> n;
	ALL[n]->out();
	ALL[n]->restor();

}

int main()
{
	ifstream file_xml("xml.xml");
		if (!file_xml.is_open()) file_xml.open("D:\\#ЯП\\C++\\29.04.2020 Парсинг XML и TXT файлов паттерно\\29.04.2020 Парсинг XML и TXT файлов паттерно\\xml.xml");
	ifstream file_txt("txt.txt");
		if (!file_txt.is_open()) file_txt.open("D:\\#ЯП\\C++\\29.04.2020 Парсинг XML и TXT файлов паттерно\\29.04.2020 Парсинг XML и TXT файлов паттерно\\txt.txt");
	SetConsoleCP(1251); SetConsoleOutputCP(1251);
	XML(file_xml); TXT(file_txt);

	do {
		choice = menu();
		switch (choice)
		{
		case 1: PAR(); break;
		case 2: SHOW(); break;
		case 3: ALLS(); break;
		case 4: RESTORELEMENT(); break;
		case 0: system("pause"); break;
		default: "mimo";
		}
	} while (choice != 0);
	return 0;
}