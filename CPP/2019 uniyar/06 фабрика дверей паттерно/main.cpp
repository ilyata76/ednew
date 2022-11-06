#include <windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <iterator>



#ifndef INFO
#define _ cout << "  ";
#define ENDL cout <<endl;
#define INFO { dhandle[i]->info(); _ _; dhardway[i]->info(); ENDL; \
				dhingle[i]->info(); _ _; dglass[i]->info(); ENDL; \
			dmaterial[i]->info(); _ _; dshade[i]->info(); _ _; ENDL; _ _ _ dsized[i]->info(); ENDL; cout << "======\n";}
#define DEL { delete dhandle[i]; delete dhingle[i]; delete dhardway[i]; delete dglass[i]; delete dmaterial[i]; delete dshade[i]; delete dsized[i]; }
#endif // !INFO



using namespace std;

class Door; class CREATE;

class doorhandle
{
public:
	virtual void info() = 0;
	virtual ~doorhandle() {};
};
class doorhingle
{
public:
	virtual void info() = 0;
	virtual ~doorhingle() {};
};
class doorhardway
{
public:
	virtual void info() = 0;
	virtual ~doorhardway() {};
};
class doorglass
{
public:
	virtual void info() = 0;
	virtual ~doorglass() {};
};
class doormaterial
{
public:
	virtual void info() = 0;
	virtual ~doormaterial() {};
};

class doorshade
{
public:
	virtual void info() = 0;
	virtual ~doorshade() {};
};

class darkshade : public doorshade
{
public: void info() { cout << "DARK SHADE"; }
};
class lightshade : public doorshade
{
public: void info() { cout << "LIGHT SHADE"; }
};


class goldhandle : public doorhandle
{
public: void info() { cout << "GOLD HANDLE"; }
};
class silverhandle : public doorhandle
{
public: void info() { cout << "SILVER HANDLE"; }
};
class chinesehandle : public doorhandle
{
public: void info() { cout << "CHINESE HANDLE"; }
};

class goldhingle : public doorhingle
{
public: void info() { cout << "GOLD HINGLE"; }
};
class silverhingle : public doorhingle
{
public: void info() { cout << "SILVER HINGLE"; }
};
class chinesehingle : public doorhingle
{
public: void info() { cout << "CHINESE HINGLE"; }
};


class avaiabledoorhardway : public doorhardway
{
public: void info() { cout << "WHITH HARDWAY"; }
};
class nonavaiabledoorhardway : public doorhardway
{
public: void info() { cout << "WITHOUT HARDWAY"; }
};

class avaiabledoorglass : public doorglass
{
public: void info() { cout << "WHITH GLASS"; }
};
class nonavaiabledoorglass : public doorglass
{
public: void info() { cout << "WITHOUT GLASS"; }
};

class ashdoormaterial : public doormaterial
{
public: void info() { cout << "ASH(ясень) MATERIAL"; }
};
class oakdoormaterial : public doormaterial
{
public: void info() { cout << "OAK(дуб) MATERIAL"; }
};
class firdoormaterial : public doormaterial
{
public: void info() { cout << "FIR(пихта) MATERIAL"; }
};

class cherrydoormaterial : public doormaterial
{
public: void info() { cout << "CHERRY MATERIAL"; }
};

class SIZED
{
public:
	int height; int width;
	SIZED() { height = 0; width = 0; };
	SIZED(int h, int w) { height = h; width = w; }
	friend istream& operator>>(istream& in, SIZED& SD);
	void info() { cout << "height: " << height << "  width: " << width; }
};
istream& operator>>(istream& in, SIZED& SD) { cout << "height & width: "; in >> SD.height >> SD.width; return in; };


class DoorFactory
{
public:
	virtual doorhandle* createdoorhandle() = 0;
	virtual doorhingle* createdoorhingle() = 0;
	virtual doorhardway* createdoorhardway() = 0;
	virtual doorglass* createdoorglass() = 0;
	virtual doormaterial* createdoormaterial() = 0;
	virtual doorshade* createdoorshade(int instr) = 0;
	SIZED* createsize(SIZED sd) { return new SIZED(sd.height, sd.width); }
	virtual ~DoorFactory() {};

};

class EconomDoorFactory : public DoorFactory
{
public:
	doorhandle* createdoorhandle() { return new chinesehandle; }
	doorhingle* createdoorhingle() { return new chinesehingle; }
	doorhardway* createdoorhardway() { return new nonavaiabledoorhardway; }
	doorglass* createdoorglass() { return new nonavaiabledoorglass; }
	doormaterial* createdoormaterial() { return new ashdoormaterial; }
	doorshade* createdoorshade(int instr) { if (instr == 1) return new lightshade; else return new darkshade; }
};
class ComfortDoorFactory : public DoorFactory
{
public:
	doorhandle* createdoorhandle() { return new silverhandle; }
	doorhingle* createdoorhingle() { return new silverhingle; }
	doorhardway* createdoorhardway() { return new nonavaiabledoorhardway; }
	doorglass* createdoorglass() { return new avaiabledoorglass; }
	doormaterial* createdoormaterial() { return new firdoormaterial; }
	doorshade* createdoorshade(int instr) { if (instr == 1) return new lightshade; else return new darkshade; }
};
class LuksDoorFactory : public DoorFactory
{
public:
	doorhandle* createdoorhandle() { return new goldhandle; }
	doorhingle* createdoorhingle() { return new goldhingle; }
	doorhardway* createdoorhardway() { return new avaiabledoorhardway; }
	doorglass* createdoorglass() { return new avaiabledoorglass; }
	doormaterial* createdoormaterial() { return new firdoormaterial; }
	doorshade* createdoorshade(int instr) { if (instr == 1) return new lightshade; else return new darkshade; }
};

int determine(int INSTRA)
{
	map<string, int> HH{ {"gold",1},{"silver",2},{"chinese",3} }; map<string, int> ::iterator itHH = HH.begin();
	map<char, int> HW{ {'+', 1},{'-', 2} }; map<char, int> ::iterator itHW = HW.begin();
	map<string, int> MM{ {"ash",1},{"oak",2},{"fir",3},{"cherry",4} }; map<string, int> ::iterator itMM = MM.begin();
	if (INSTRA == 1) {
		string A; cout << "Ручки HANDLE: gold, silver, chinese : "; cin >> A; cout << A; for (itHH = HH.begin(); itHH != HH.end(); itHH++) {
			if (A == itHH->first) return itHH->second;
		} return 0;
	}
	if (INSTRA == 2) {
		string A; cout << "Петки HINGLE: gold, silver, chinese : "; cin >> A; for (itHH = HH.begin(); itHH != HH.end(); itHH++)
			if (A == itHH->first) { return itHH->second; } return 0;
	}
	if (INSTRA == 3) {
		char A; cout << "Фурнитур HARDWAY: +, - : "; cin >> A; for (itHW = HW.begin(); itHW != HW.end(); itHW++)
			if (A == itHW->first) { return itHW->second; } return 0;
	}
	if (INSTRA == 4) {
		char A; cout << "Стекло GLASS : +, - : "; cin >> A; for (itHW = HW.begin(); itHW != HW.end(); itHW++)
			if (A == itHW->first) { return itHW->second; }  return 0;
	}
	if (INSTRA == 5) {
		string A; cout << "Материал MATERIAL: ash, oak, fir, cherry : "; cin >> A; for (itMM = MM.begin(); itMM != MM.end(); itMM++)
			if (A == itMM->first) { return itMM->second; } return 0;
	}
	return 0;
}
class MyDoorFactory : public DoorFactory
{
public:
	doorhandle* createdoorhandle() {
		int c = determine(1);
		if (c == 1) return new goldhandle; else if (c == 2) return new silverhandle; else if (c == 3) return new chinesehandle; else return new chinesehandle;
	}
	doorhingle* createdoorhingle() {
		int c = determine(2);
		if (c == 1) return new goldhingle; else if (c == 2) return new silverhingle; else if (c == 3) return new chinesehingle; else return new chinesehingle;
	}
	doorhardway* createdoorhardway() {
		int c = determine(3);
		if (c == 1) return new avaiabledoorhardway; else if (c == 2) return new nonavaiabledoorhardway; else return new nonavaiabledoorhardway;
	}
	doorglass* createdoorglass() {
		int c = determine(4);
		if (c == 1) return new avaiabledoorglass; else if (c == 2) return new nonavaiabledoorglass; else return new nonavaiabledoorglass;
	}
	doormaterial* createdoormaterial() {
		int c = determine(5);
		if (c == 1) return new ashdoormaterial; else if (c == 2) return new oakdoormaterial; else if (c == 3) return new firdoormaterial;
		else if (c == 4) return new cherrydoormaterial; else return new ashdoormaterial;
	}
	doorshade* createdoorshade(int instr) { if (instr == 1) return new lightshade; else return new darkshade; }
};


class Door {
public:
	Door() {};
	vector<doorhandle*> dhandle;
	vector<doorhingle*> dhingle;
	vector<doorhardway*> dhardway;
	vector<doorglass*> dglass;
	vector<doormaterial*> dmaterial;
	vector<doorshade*> dshade;
	vector<SIZED*> dsized;
	void info() { for (unsigned int i = 0; i < dhandle.size(); ++i) INFO; }
	~Door() { for (unsigned int i = 0; i < dhandle.size(); ++i) DEL; }
};

class CREATE {
public:
	CREATE() {};
	Door* createDoorka(DoorFactory& factoria, int instr, SIZED sd) {
		Door* p = new Door;
		p->dhandle.push_back(factoria.createdoorhandle());
		p->dhingle.push_back(factoria.createdoorhingle());
		p->dhardway.push_back(factoria.createdoorhardway());
		p->dglass.push_back(factoria.createdoorglass());
		p->dmaterial.push_back(factoria.createdoormaterial());
		p->dshade.push_back(factoria.createdoorshade(instr));
		p->dsized.push_back(factoria.createsize(sd));
		return p;
	}
};

int choice = 0; int menu();
vector<Door*> ADD(CREATE, EconomDoorFactory&, ComfortDoorFactory&, LuksDoorFactory&, SIZED&, int, vector<Door*> FD, int, MyDoorFactory&);
void SHOW(vector<Door*> FD) { for (unsigned int i = 0; i < FD.size(); ++i) { cout << "===================\\\n"; FD[i]->info(); } }

int main()
{
	SetConsoleCP(1251); SetConsoleOutputCP(1251);
	CREATE doorka; int instr = 0; SIZED sd; EconomDoorFactory Economka; ComfortDoorFactory Comforka; LuksDoorFactory Lusksa; vector<Door*> FD; MyDoorFactory moyadoorka;
	do {
		choice = menu();
		switch (choice)
		{
		case 1: FD = ADD(doorka, Economka, Comforka, Lusksa, sd, 1, FD, 0, moyadoorka); system("cls"); break;
		case 2: FD = ADD(doorka, Economka, Comforka, Lusksa, sd, 2, FD, 0, moyadoorka); system("cls"); break;
		case 3: FD = ADD(doorka, Economka, Comforka, Lusksa, sd, 3, FD, 0, moyadoorka); system("cls"); break;
		case 4: FD = ADD(doorka, Economka, Comforka, Lusksa, sd, 0, FD, 1, moyadoorka); break;
		case 5: SHOW(FD); break;
		case 0: cout << "LIGA SLIV\n"; break;
		default: cout << "miss\n";
		}
	} while (choice != 0);
	system("pause");
	return 0;
}

vector<Door*> ADD(CREATE doorka, EconomDoorFactory& Economka, ComfortDoorFactory& Comforka, LuksDoorFactory& Lusksa, SIZED& sd, int instruction, vector<Door*> FD, int ISTRA, MyDoorFactory& moyadoorka)
{
	Door* Temp; int instr;
	if (instruction == 1)
	{
		cin >> sd; cout << "1 - light; other integer - dark shade : "; cin >> instr;
		Temp = doorka.createDoorka(Economka, instr, sd);
		FD.push_back(Temp);
		return FD;
	}
	else if (instruction == 2)
	{
		cin >> sd; cout << "1 - light; other integer - dark shade : "; cin >> instr;
		Temp = doorka.createDoorka(Comforka, instr, sd);
		FD.push_back(Temp);
		return FD;
	}
	else if (instruction == 3)
	{
		cin >> sd; cout << "1 - light; other integer - dark shade : "; cin >> instr;
		Temp = doorka.createDoorka(Lusksa, instr, sd);
		FD.push_back(Temp);
		return FD;
	}
	else {}
	if (instruction == 0 && ISTRA != 0)
	{

		cin >> sd; cout << "1 - light; other integer - dark shade : "; cin >> instr;
		Temp = doorka.createDoorka(moyadoorka, instr, sd);
		FD.push_back(Temp);
		return FD;
	}
	return FD;
}

int menu()
{
	cout << "Формируем \"DOORKA\"\n";
	cout << "1. ЭКОНОМ для испанских графов\n"
		<< "2. КОМФОРТ для сербских королей\n"
		<< "3. ЛЮКС для императоров французских\n"
		<< "4. Вы уникальны? Вам уникальная дурка\n"
		<< "5. Показать\n"
		<< "0. Vihod\n";
	cout << "??? : "; cin >> choice; return choice;
}
