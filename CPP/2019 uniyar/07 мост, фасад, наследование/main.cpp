#include <iostream>
#include <string>
#include <windows.h>
#include <map>
#include <iterator>

using namespace std;

typedef string LNG;


class language
{
public: LNG lng;
public:
	language() {};
	//language(string ll) { this->lng = ll; };

	virtual void info() = 0;

	virtual language* get() = 0;
	virtual char cinfo() = 0;

	virtual void iinfo() = 0;

	virtual void freefirst() = 0;
	virtual void freesecond() = 0;
	virtual void freethird() = 0;

	virtual void paymentfirst() = 0;
	virtual void paymentsecond() = 0;
	virtual void paymentthird() = 0;

	virtual void corporatefirst() = 0;
	virtual void corporatesecond() = 0;
	virtual void corporatethird() = 0;

	virtual void free() = 0;
	virtual void payment() = 0;
	virtual void corporate() = 0;

	virtual ~language() {};
};

class ENL : public language
{
public:
	ENL() { this->lng = "ENGLISH"; };

	void info() { cout << "ENGLISH "; }

	char cinfo() { return 'e'; }

	void iinfo() { this->info(); cout << "���� ����� "; }

	void freefirst() override { this->info(); cout << "1. � �� �� ��������? ������������� � ���� ��������"; }
	void freesecond() override { this->info(); cout << "2. � �� �� ��������? �� ��-��������� ���-��"; }
	void freethird() override { this->info(); cout << "3. � �� �� ��������? ����� �� �� ���������"; }

	void paymentfirst() override { this->info(); cout << "1. ��-��������� ������� ������"; }
	void paymentsecond() override { this->info(); cout << "2. ��-��������� ������� ������"; }
	void paymentthird() override { this->info(); cout << "3. ��-��������� ������� ������"; }

	void corporatefirst() override { this->info(); cout << "1. � ��� ��� ��� ��������-���������� ����������?"; }
	void corporatesecond() override { this->info(); cout << "2. � ��� ��� ��� ��������-���������� ����������?"; }
	void corporatethird() override { this->info(); cout << "3. � ��� ��� ��� ��������-���������� ����������?"; }

	void free() override { this->info(); cout << "�� ������ ������ ���������� ��� ��� ������ ���������?"; }
	void payment() override { this->info(); cout << "�� ����� ��� ��� ���������� ������������� ������ ��� ��������!"; }
	void corporate() override { this->info(); cout << "�������-�� �� � ���� ���� ����� ������ � ������ ������� �� ����� ��� ���������� ��������"; }

	language* get() { return new ENL; }
};
class RUL : public language
{
public:
	RUL() { this->lng = "RUSSIAN"; };
	void info() { cout << "RUSSIAN "; }
	char cinfo() { return 'r'; }

	void iinfo() { this->info(); cout << "���� ����� "; }

	void freefirst() override { this->info(); cout << "1. � �� �� ��������?"; }
	void freesecond() override { this->info(); cout << "2. � �� �� ��������?"; }
	void freethird() override { this->info(); cout << "3. � �� �� ��������?"; }

	void paymentfirst() override { this->info(); cout << "1. ������� ������"; }
	void paymentsecond() override { this->info(); cout << "2. ������� ������"; }
	void paymentthird() override { this->info(); cout << "3. ������� ������"; }

	void corporatefirst() override { this->info(); cout << "1. � ��� ��� ��� �������� ����������?"; }
	void corporatesecond() override { this->info(); cout << "2. � ��� ��� ��� �������� ����������?"; }
	void corporatethird() override { this->info(); cout << "3. � ��� ��� ��� �������� ����������?"; }

	void free() override { this->info(); cout << "�� ������ ������ ����������"; }
	void payment() override { this->info(); cout << "�� �����, ��� ��� ���������� ������������� ������!"; }
	void corporate() override { this->info(); cout << "�������-�� �� � ���� ���� ����� ������"; }


	language* get() { return new RUL; }
};
class FRL : public language
{
public:
	FRL() { this->lng = "FRANCE"; };
	void info() { cout << "FRANCE "; }
	char cinfo() { return 'f'; }

	void iinfo() { this->info(); cout << "���� ����� "; }

	void freefirst() override { this->info(); cout << "1. � �� �� ��������? vive la france"; }
	void freesecond() override { this->info(); cout << "2. � �� �� ��������? vive la france"; }
	void freethird() override { this->info(); cout << "3. � �� �� ��������? vive la france"; }

	void paymentfirst() override { this->info(); cout << "1. ������� ������ vive la france vive la france vive la france"; }
	void paymentsecond() override { this->info(); cout << "2. ������� ������ vive la france"; }
	void paymentthird() override { this->info(); cout << "3. ������� ������ ���� �����������"; }

	void corporatefirst() override { this->info(); cout << "1. � ��� ��� ��� �������� �� ������� ����������?"; }
	void corporatesecond() override { this->info(); cout << "2. � ��� ��� ��� �������� ����������?"; }
	void corporatethird() override { this->info(); cout << "3. � ��� ��� ��� �������� ����������? ��� ������ ��� �������� ��������"; }

	void free() override { this->info(); cout << "�� ������ ������ ���������� �� �����������?"; }
	void payment() override { this->info(); cout << "�� �����, ��� ��� ���������� ������������� ������! ������ ���������"; }
	void corporate() override { this->info(); cout << "�������-�� �� � ���� ���� ����� ������ � �� �������� ���"; }


	language* get() { return new FRL; }
};
class GEL : public language
{
public:
	GEL() { this->lng = "GERMAN"; };
	void info() { cout << "GERMAN "; }
	char cinfo() { return 'g'; }

	void iinfo() { this->info(); cout << "���� ����� "; }

	void freefirst() override { this->info(); cout << "1. � �� �� ��������? *������������*"; }
	void freesecond() override { this->info(); cout << "2. � �� �� ��������? *������������*"; }
	void freethird() override { this->info(); cout << "3. � �� �� ��������? 1991"; }

	void paymentfirst() override { this->info(); cout << "1. ������� ������ �� �����"; }
	void paymentsecond() override { this->info(); cout << "2. ������� ������ �� ���"; }
	void paymentthird() override { this->info(); cout << "3. ������� ������ �� ������"; }

	void corporatefirst() override { this->info(); cout << "1. � ��� ��� ��� �������� ����������? ��������� �����-��"; }
	void corporatesecond() override { this->info(); cout << "2. � ��� ��� ��� �������� ����������? ��� �� �������� ��������?"; }
	void corporatethird() override { this->info(); cout << "3. � ��� ��� ��� �������� ����������? �� �� ����� ���"; }

	void free() override { this->info(); cout << "�� ������ ������ ����������? ������� ������ ��� ������"; }
	void payment() override { this->info(); cout << "�� �����, ��� ��� ���������� ������������� ������! ��������� ��� � ���"; }
	void corporate() override { this->info(); cout << "�������-�� �� � ���� ���� ����� ������ � �� ������ ��� ���"; }


	language* get() { return new GEL; }
};

class abobe
{
protected:
	language* lng = new ENL; // LNG lln;
public:
	abobe() {};
	//abobe(LNG lng) { this->lln = lng; cout << "���� ����� (): " << this->lln; };
	//abobe(language& s) { this->lng = s.get(); cout << "���� ����� (): "; this->lng->info(); };
	void takelng(language* s) { this->lng = s->get(); }
	virtual void info() = 0;
	virtual void cinnfo() = 0;
	virtual void freeaboba() = 0;
	virtual void paymentaboba() = 0;
	virtual void corporateaboba() = 0;

	/*
	friend void Flanguageout(abobe* S, char instr);
	friend void Planguageout(abobe* S, char instr);
	friend void Clanguageout(abobe* S, char instr);
	friend void FLA(abobe* S, char instr);
	friend void PLA(abobe* S, char instr);
	friend void CLA(abobe* S, char instr);
	friend void FI(abobe* S, char instr);
	friend void PI(abobe* S, char instr);
	friend void CI(abobe* S, char instr);
	*/

	virtual void freefirst() = 0;
	virtual void freesecond() = 0;
	virtual void freethird() = 0;
	virtual void paymentfirst() = 0;
	virtual void paymentsecond() = 0;
	virtual void paymentthird() = 0;
	virtual void corporatefirst() = 0;
	virtual void corporatesecond() = 0;
	virtual void corporatethird() = 0;
	/**/
	virtual abobe* get() = 0;
	virtual ~abobe() { delete lng; }
};

class free_a : public abobe
{
public:
	free_a() {};
	//free_a(LNG lng) : abobe(lng) { cout << " FREE\n"; };
	//free_a(language& s) : abobe(s) { cout << " FREE\n"; };
	void info() override { this->lng->iinfo(); this->cinnfo(); cout << endl; }
	void cinnfo() override { cout << "FREE "; }
	void freeaboba() override { cout << "(+) "; this->cinnfo(); this->lng->free(); cout << endl; }
	void paymentaboba() override { cout << "(-) "; this->cinnfo(); this->lng->payment(); cout << endl; }
	void corporateaboba() override { cout << "(-) "; this->cinnfo(); this->lng->corporate(); cout << endl; }
	/**/
	void freefirst() override { cout << "(+) "; this->cinnfo(); this->lng->freefirst();  cout << " \n"; }
	void freesecond() override { cout << "(+) "; this->cinnfo(); this->lng->freesecond(); cout << " \n"; }
	void freethird() override { cout << "(+) "; this->cinnfo(); this->lng->freethird(); cout << " \n"; }
	void paymentfirst() override { cout << "(-) "; this->cinnfo(); this->lng->paymentfirst(); cout << " \n"; }
	void paymentsecond() override { cout << "(-) "; this->cinnfo(); this->lng->paymentsecond(); cout << " \n"; }
	void paymentthird() override { cout << "(-) "; this->cinnfo(); this->lng->paymentthird(); cout << " \n"; }
	void corporatefirst() override { cout << "(-) "; this->cinnfo(); this->lng->corporatefirst(); cout << " \n"; }
	void corporatesecond() override { cout << "(-) "; this->cinnfo(); this->lng->corporatesecond(); cout << " \n"; }
	void corporatethird() override { cout << "(-) "; this->cinnfo(); this->lng->corporatethird(); cout << " \n"; }
	/**/
	abobe* get() { return new free_a; }
};

class payment_a : public abobe
{
public:
	payment_a() {};
	//payment_a(LNG lng) : abobe(lng) { cout << " PAYMENT\n"; };
	//payment_a(language& s) : abobe(s) { cout << " PAYMENT\n"; };
	void info() override { this->lng->iinfo(); this->cinnfo(); cout << endl; }
	void cinnfo() override { cout << "PAYMENT "; }
	void freeaboba() override { cout << "(+) "; this->cinnfo(); this->lng->free(); cout << endl; }
	void paymentaboba() override { cout << "(+) "; this->cinnfo(); this->lng->payment(); cout << endl; }
	void corporateaboba() override { cout << "(-) "; this->cinnfo(); this->lng->corporate(); cout << endl; }
	/**/
	void freefirst() override { cout << "(+) "; this->cinnfo(); this->lng->freefirst();  cout << " \n"; }
	void freesecond() override { cout << "(+) "; this->cinnfo(); this->lng->freesecond(); cout << " \n"; }
	void freethird() override { cout << "(+) "; this->cinnfo(); this->lng->freethird(); cout << " \n"; }
	void paymentfirst() override { cout << "(+) "; this->cinnfo(); this->lng->paymentfirst(); cout << " \n"; }
	void paymentsecond() override { cout << "(+) "; this->cinnfo(); this->lng->paymentsecond(); cout << " \n"; }
	void paymentthird() override { cout << "(+) "; this->cinnfo(); this->lng->paymentthird(); cout << " \n"; }
	void corporatefirst() override { cout << "(-) "; this->cinnfo(); this->lng->corporatefirst(); cout << " \n"; }
	void corporatesecond() override { cout << "(-) "; this->cinnfo(); this->lng->corporatesecond(); cout << " \n"; }
	void corporatethird() override { cout << "(-) "; this->cinnfo(); this->lng->corporatethird(); cout << " \n"; }
	/**/
	abobe* get() { return new payment_a; }
};

class corporate_a : public abobe
{
public:
	corporate_a() {};
	//corporate_a(LNG lng) : abobe(lng) { cout << " CORPORATE\n"; };
	//corporate_a(language& s) : abobe(s) { cout << " CORPORATE\n"; };

	void info() override { this->lng->iinfo(); this->cinnfo(); cout << endl; }
	void cinnfo() override { cout << "CORPORATE "; }
	void freeaboba() override { cout << "(+) "; this->cinnfo(); this->lng->free(); cout << endl; }
	void paymentaboba() override { cout << "(+) "; this->cinnfo(); this->lng->payment(); cout << endl; }
	void corporateaboba() override { cout << "(+) "; this->cinnfo(); this->lng->corporate(); cout << endl; }

	void freefirst() override { cout << "(+) "; this->cinnfo(); this->lng->freefirst();  cout << " \n"; }
	void freesecond() override { cout << "(+) "; this->cinnfo(); this->lng->freesecond(); cout << " \n"; }
	void freethird() override { cout << "(+) "; this->cinnfo(); this->lng->freethird(); cout << " \n"; }
	void paymentfirst() override { cout << "(+) "; this->cinnfo(); this->lng->paymentfirst(); cout << " \n"; }
	void paymentsecond() override { cout << "(+) "; this->cinnfo(); this->lng->paymentsecond(); cout << " \n"; }
	void paymentthird() override { cout << "(+) "; this->cinnfo(); this->lng->paymentthird(); cout << " \n"; }
	void corporatefirst() override { cout << "(+) "; this->cinnfo(); this->lng->corporatefirst(); cout << " \n"; }
	void corporatesecond() override { cout << "(+) "; this->cinnfo(); this->lng->corporatesecond(); cout << " \n"; }
	void corporatethird() override { cout << "(+) "; this->cinnfo(); this->lng->corporatethird(); cout << " \n"; }

	abobe* get() { return new corporate_a; }
};



class babobe // ������ ����������!
{
private:
	abobe* S;
public:
	babobe() { this->S = new free_a; this->S->takelng(new ENL); };
	babobe(language& ll, abobe& ss) { this->S = ss.get(); this->S->takelng(ll.get()); /*S->takelng(L);*/ }
	void info() { S->info(); }
	void changelanguage() {
		LNG ll; cout << "german, france, russian, english\n"; cin >> ll;
		if (ll == "german") { cout << "������ �� GER\n"; this->S->takelng(new GEL); }
		else if (ll == "france") { cout << "������ �� FRA\n"; this->S->takelng(new FRL); }
		else if (ll == "russian") { cout << "������ �� RUS\n"; this->S->takelng(new RUL); }
		else if (ll == "english") { cout << "������ �� ENG\n"; this->S->takelng(new ENL); }
		else { cout << "������ �� ENG\n"; this->S->takelng(new ENL); }
	}
	/**/
	void freeaboba() { S->freeaboba(); S->freefirst(); S->freesecond(); S->freethird(); }
	void paymentaboba() { S->paymentaboba(); S->paymentfirst(); S->paymentsecond(); S->paymentthird(); }
	void corporateaboba() { S->corporateaboba(); S->corporatefirst(); S->corporatesecond(); S->corporatethird(); }
	/**/
	void freefirst() { S->freefirst(); } void freesecond() { S->freesecond(); } void freethird() { S->freethird(); }
	void paymentfirst() { S->paymentfirst(); } void paymentsecond() { S->paymentsecond(); } void paymentthird() { S->paymentthird(); }
	void corporatefirst() { S->corporatefirst(); } void corporatesecond() { S->corporatesecond(); } void corporatethird() { S->corporatethird(); }
	void box() { S->freefirst(); S->paymentfirst(); S->paymentthird(); S->freesecond(); S->freefirst(); }
	/**/

	~babobe() { cout << "destr: ����� ������\n"; delete S; }
};


int choice = -1; babobe* MAIN();
bool isdigit(char c) { if (c == '1' || c == '2' || c == '3' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9' || c == '0') return true; else return false; }

int menu()
{
	cout << "=======================\\\\\\\n"
		<< "||\t1. freeaboba - ��� ������� ����������\n"
		<< "||\t2/3 paymentaboba/corporateaboba \n"
		<< "||\t4. ������� ���� ���������\n"
		<< "||\t5. �������� ���������� � ������\n"
		<< "||\t6. �������� ������ ���������\n"
		<< "||\t7. ��������� ��� ������� ������\n"
		<< "||\t8/9/10. free/1/2/3\n"
		<< "||\t11/12/13. payment/1/2/3\n"
		<< "||\t14/15/16. corporate/1/2/3\n"
		<< "||\t17. Payment+: ���������� ��� � ������� (����� �������)\n"
		<< "||\t0. VIHOD\n";

	string c; cin >> c;
	//if (c[0] && !c[1] && isdigit(c[0])) { choice = c[0] - '0'; }
	//else if (c[0] && c[1] && isdigit(c[0]) && isdigit(c[1]) && !c[2]) { choice = (c[0] - '0') * 10 + (c[1] - '0'); }
	//else choice = -1;
	choice = 0; for (unsigned int i = 0; i < c.size(); i++) {
		if (c[i] && isdigit(c[i])) { choice += int((c[i] - '0') * pow(10.0, c.size() - (i + 1))); }
		else if (c[i] && !isdigit(c[i])) { choice = -1; return choice; }
	}
	return int(choice);
}

int main()
{
	SetConsoleCP(1251); SetConsoleOutputCP(1251);
	babobe* ADOBE = MAIN();
	do {
		cout << "=======================\\\\\\\n"; ADOBE->info();
		choice = menu();
		cout << "�����: " << choice << endl;
		switch (choice)
		{
		case 1: ADOBE->freeaboba(); break;
		case 2: ADOBE->paymentaboba(); break;
		case 3: ADOBE->corporateaboba(); break;
		case 4: ADOBE->changelanguage(); break;
		case 5: ADOBE->info(); break;
		case 6: ADOBE = MAIN(); break;
		case 7: ADOBE->freeaboba(); ADOBE->paymentaboba(); ADOBE->corporateaboba(); cout << "=======\n"; ADOBE->info(); cout << "======\n"; break;
		case 8: ADOBE->freefirst(); break;
		case 9: ADOBE->freesecond(); break;
		case 10: ADOBE->freethird(); break;
		case 11: ADOBE->paymentfirst(); break;
		case 12: ADOBE->paymentsecond(); break;
		case 13: ADOBE->paymentthird(); break;
		case 14: ADOBE->corporatefirst(); break;
		case 15: ADOBE->corporatesecond(); break;
		case 16: ADOBE->corporatethird(); break;
		case 17: ADOBE->box(); break;
		case 0: cout << "liga sliv\n"; system("pause"); break;
		default: cout << "mimo\n";
		}
	} while (choice != 0);
	ADOBE->~babobe();
	return 0;
}


babobe* MAIN() // ����� ��������� ������ - �������� � �������
{
	map<LNG, int> LNGS{ {"russian",1},{"english",2},{"france",3},{"german",4} }; map<LNG, int>::iterator itLNGS = LNGS.begin();
	map<string, int> ABO{ {"free",1},{"payment",2},{"corporate",3} }; map<string, int>::iterator itABO = ABO.begin();
	RUL rl; ENL el; FRL fl; GEL gl; /**/ free_a fa; payment_a pa; corporate_a ca;

GOTOversion: string A; cout << "������� ������� ������:"; for (itABO = ABO.begin(); itABO != ABO.end(); itABO++) cout << " " << itABO->first << ";"; cout << endl; cin >> A;
	for (itABO = ABO.begin(); itABO != ABO.end(); itABO++) if (itABO->first == A) break;
	if (itABO == ABO.end() || itLNGS == LNGS.end()) { cout << "���-�� �� ���, �������� �������\n"; goto GOTOversion; }

GOTOlanguage: LNG B; cout << "������� ����. ���� ���������:"; for (itLNGS = LNGS.begin(); itLNGS != LNGS.end(); itLNGS++) cout << " " << itLNGS->first << ";"; cout << endl; cin >> B;
	for (itLNGS = LNGS.begin(); itLNGS != LNGS.end(); itLNGS++) if (itLNGS->first == B) break;
	if (itABO == ABO.end() || itLNGS == LNGS.end()) { cout << "���-�� �� ���, �������� �������\n"; goto GOTOlanguage; }

	if (itABO->second == 1)
	{
		if (itLNGS->second == 1) return new babobe(rl, fa);
		else if (itLNGS->second == 2) return new babobe(el, fa);
		else if (itLNGS->second == 3) return new babobe(fl, fa);
		else if (itLNGS->second == 4) return new babobe(gl, fa);
		else { cout << "���-�� �� ���, �������� �������\n"; return MAIN(); }
	}

	else if (itABO->second == 2)
	{
		if (itLNGS->second == 1) return new babobe(rl, pa);
		else if (itLNGS->second == 2) return new babobe(el, pa);
		else if (itLNGS->second == 3) return new babobe(fl, pa);
		else if (itLNGS->second == 4) return new babobe(gl, pa);
		else { cout << "���-�� �� ���, �������� �������\n"; return MAIN(); }
	}

	else if (itABO->second == 3)
	{
		if (itLNGS->second == 1) return new babobe(rl, ca);
		else if (itLNGS->second == 2) return new babobe(el, ca);
		else if (itLNGS->second == 3) return new babobe(fl, ca);
		else if (itLNGS->second == 4) return new babobe(gl, ca);
		else { cout << "���-�� �� ���, �������� �������\n"; return MAIN(); }
	}

	else { cout << "���-�� �� ���, �������� �������\n"; return MAIN(); }

}