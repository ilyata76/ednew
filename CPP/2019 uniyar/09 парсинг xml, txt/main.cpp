#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include "dies.h"


using namespace std;


// ПОРОЖДАЮЩИЙ

class securite
{
public:
	securite() {};
	virtual string info() = 0;
	virtual void INFO() = 0;
	friend ostream& operator<< (ostream& out, securite* A);
	~securite() {};
};

ostream& operator<< (ostream& out, securite* A) { out << A->info(); return out; };

class bond : public securite
{
public:
	bond() {};
	string info() override { return "Облигацию"; }
	void INFO() override { cout << "ОБЛИГАЦИЯ"; }
};

class stonk : public securite
{
public:
	stonk() {};
	string info() override { return "Акцию"; }
	void INFO() override { cout << "АКЦИЯ"; }
};

class certificate : public securite
{
public:
	certificate() {};
	string info() override { return "Сертификат"; }
	void INFO() override { cout << "СЕРТИФИКАТ"; }
};

// END ПОРОЖДАЮЩИЙ

/////////////////////////////////////
class DATA
{
public: int type; string name; double nominal; dies date; double price;
	  DATA() {}; ~DATA() {};
};
/////////////////////////////////////
//////////////////////////////////////////////////
class FILES
{
public:
	FILES() {};
	virtual void OUTPUT() = 0;
	virtual securite* createSecurite(DATA X) = 0;
	~FILES() {};
};

class FILETXT : public FILE
{
public:
	securite* type; string name; double nominal; dies date; double price;
public:
	FILETXT() {};
	FILETXT(DATA& X) {};
	FILETXT(FILETXT* A) {};
	FILETXT(FILETXT* A, DATA& X) {};
	virtual void OUTPUT() = 0;
	virtual securite* createSecurite(DATA X) {
		if (X.type == 1) return new stonk; else if (X.type == 2) return new bond;
		else if (X.type == 3) return new certificate; else return new stonk;
	}
};
class FILEXML : public FILE
{
public:
	securite* type; string name; double nominal; dies date; double price;
public:
	FILEXML() {};
	FILEXML(DATA& X) {};
	FILEXML(FILEXML* A) {};
	FILEXML(FILEXML* A, DATA& X) {};
	virtual void OUTPUT() = 0;
	virtual securite* createSecurite(DATA X) {
		if (X.type == 1) return new stonk; else if (X.type == 2) return new bond;
		else if (X.type == 3) return new certificate; else return new stonk;
	}
};
//////////////////////////////////////////////////
class TXT_1 : public FILETXT
{
public:
	FILETXT* FILE;
public:
	TXT_1() {}
	TXT_1(DATA& X) { type = createSecurite(X); name = X.name; nominal = X.nominal; date = X.date; price = X.price; };

	bool fiz(TXT_1* f)
	{
		if ((f->nominal * f->price <= 50000.0) && (f->nominal * f->price > 0.0)) return true;
		else if ((f->nominal * f->price >= 50000.0) && (f->nominal * f->price > 0.0)) return false; else return true;
	}
	void OUTPUT() override {
		if (fiz(this)) cout << " Физическое лицо" << " купило ";
		else cout << " Юричидеское лицо" << " купило ";
	}
};

class TXT_2 : public FILETXT
{
public:
	FILETXT* FILE;
public:
	TXT_2(FILETXT* f) { FILE = f; }
	void OUTPUT() override {
		this->FILE->OUTPUT(); cout << " " << this->FILE->type->info() << " компании " << this->FILE->name <<
			" номиналом " << this->FILE->nominal << " в дату " << this->FILE->date;
	}
};
//////////////////////////////////////////////////
class XML_1 : public FILEXML
{
public:
	FILEXML* FILE;
public:
	XML_1() {}
	XML_1(DATA& X) { type = createSecurite(X); name = X.name; nominal = X.nominal; date = X.date; price = X.price; };
	bool fiz(XML_1* f)
	{
		if ((f->nominal * f->price <= 50000.0) && (f->nominal * f->price > 0.0)) return true;
		else if ((f->nominal * f->price >= 50000.0) && (f->nominal * f->price > 0.0)) return false; else return true;
	}
	void OUTPUT() override {
		if (fiz(this)) cout << " Физическое лицо" << " купило ";
		else cout << " Юричидеское лицо" << " купило ";
	}
};

class XML_2 : public FILEXML
{
public:
	FILEXML* FILE;
public:
	XML_2() {}
	XML_2(FILEXML* f) { FILE = f; }
	void OUTPUT() override {
		this->FILE->OUTPUT(); cout << " " << this->FILE->type->info() << " компании " << this->FILE->name <<
			" номиналом " << this->FILE->nominal << " в дату " << this->FILE->date;
	}
};
//////////////////////////////////////////////////
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
	if (!comm(A))
		if (file.is_open())
			if (!file.eof())
				while (B != '>') { file.read(&B, 1); A.push_back(B); }
			else {}
		else {}
	else { return A = { '<', '!' }; }
	return A;
}

string getblock(ifstream& file, string& B, string& C, string& D, string& E, string& F, string& G, string& K)
{
	string A;
	// A = firstcode(file); // <securlist

	A = B = firstcode(file); // <secur
	if (A == "</SecurityList>") { return A; }

Cget: if (!comm(A)) C = get(file); //type
else { A = B = firstcode(file); goto Cget; }

Dget: if (!comm(C)) D = get(file); //name
else { C = get(file); goto Dget; }

Eget: if (!comm(D)) E = get(file); //nominal
else { D = get(file); goto Eget; }

Fget: if (!comm(E)) F = get(file); //date
else { E = get(file); goto Fget; }

Gget: if (!comm(F)) G = get(file); //price
else { F = get(file); goto Gget; }

Kget: if (!comm(G)) K = firstcode(file);
else { G = get(file); goto Kget; }

return B + C + D + E + F + G + K;
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
		for (int i = 0; i < 2; i++) B.push_back(A[i]);
		for (int i = 4; i < 6; i++) C.push_back(A[i]);
		for (int i = 6; i < 11; i++) D.push_back(A[i]);
		Bi = stoi(B); Ci = stoi(C); Di = stoi(D); return { Bi,Ci,Di };
	}
	else cout << "што-то не так";
}

vector <DATA> DVXML;
vector <DATA> DVTXT;
string getstr(string& A, int i) { string B; for (int j = i; A[j] != '<'; j++) B.push_back(A[j]); return B; } // name 12, nominal 9, price 7

string XML(ifstream& file)
{
	string B, C, D, E, F, G, K;
	DATA XX; string str, A, X;  do { str = firstcode(file); } while (comm(str)); X += str;
	for (int i = 1; A != "</SecurityList>"; i++)
	{
		A = getblock(file, B, C, D, E, F, G, K);
		if (A != "</SecurityList>") {
			for (int i = 14; i < 15; i++) XX.type = C[i] - '0';
			XX.name = getstr(D, 12); XX.nominal = stod(getstr(E, 9));
			XX.date = getdate(F, "XML"); XX.price = stod(getstr(G, 7));
			DVXML.push_back(XX); X += A;
		}
		else { X += A; }
	}										// i-тый блок
	return X;
}
//////////////////////////////////////////////////
string gettxtblock(ifstream& file)
{
	string A; char XX; DATA PP; string B, C, D, F, E; int i;
	if (file.is_open()) while (!file.eof())
	{
		getline(file, A);
		if (A[0] == '!') break; i = 0;
		for (i = 0; A[i] != '-'; i++) B.push_back(A[i]); // название
		i++; for (; A[i] != ';'; i++) C.push_back(A[i]); // тип бумаги
		i++; i++; for (; A[i] != ';'; i++) { if (A[i] == ';') continue; D.push_back(A[i]); } // номинал
		i++; i++; for (; A[i] != ';'; i++) { if (A[i] == ';') continue; E.push_back(A[i]); }// дата
		i++; i++; for (; A[i] != '\0'; i++) { if (A[i] == ';') continue; F.push_back(A[i]); }// цена
		PP.name = B; PP.type = C[1] - '0';
		PP.nominal = stod(D); PP.date = getdate(E, "TXT");
		PP.price = stod(F); D = F = C = B = E = "";

		DVXML.push_back(PP);
	}
	return B + C + D + E + F;
}
string TXT(ifstream& file) { string A; char X; string B, C, D, E, F; getline(file, A); A.clear(); gettxtblock(file); return A; }
//////////////////////////////////////////////////
vector <FILEXML*> XMLS;
vector <FILETXT*> TXTS;

int main()
{
	SetConsoleCP(1251); SetConsoleOutputCP(1251);

	ifstream file_xml("xml.xml");
		if (!file_xml.is_open()) file_xml.open("D:\\#ЯП\\C++\\28.04.2020 Парсинг XML и TXT файлов ранний паттерно\\28.04.2020 Парсинг XML и TXT файлов ранний паттерно\\xml.xml");
	ifstream file_txt("txt.txt");
		if (!file_txt.is_open()) file_txt.open("D:\\#ЯП\\C++\\28.04.2020 Парсинг XML и TXT файлов ранний паттерно\\28.04.2020 Парсинг XML и TXT файлов ранний паттерно\\txt.txt");
	

	XML(file_xml);
	TXT(file_txt);
	for (unsigned int i = 0, j = 0; j < DVXML.size(); j++, i++)
	{
		XMLS.push_back(new XML_2(new XML_1(DVXML[i])));
	}
	for (unsigned int i = 0, j = 0; j < DVTXT.size(); j++, i++)
	{
		TXTS.push_back(new TXT_2(new TXT_1(DVTXT[i])));
	}
	for (unsigned int i = 0, j = 0; j < DVXML.size(); j++, i++)
	{
		cout << endl; XMLS[i]->OUTPUT(); cout << endl;
	}
	for (unsigned int i = 0, j = 0; j < DVTXT.size(); j++, i++)
	{
		cout << endl; TXTS[i]->OUTPUT(); cout << endl;
	}
	system("pause");
	return 0;
}
