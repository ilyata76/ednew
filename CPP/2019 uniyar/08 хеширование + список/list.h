#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Data
{
	string name; string surname;
	string password;
	void Input(Data& data);
	void InputFile(Data& data, ifstream& file);
	Data* NEXT;
	int Z;
};

class LIST
{
	Data* HEAD; // na nachalo
public:
	LIST() :HEAD(NULL) {};
	~LIST();
	void AddUser(Data& data); // dobavlyaem
	void DelUser(Data& dAta); // udalyaem
	void Show(); // чекнуть заполнение списка
	void ChangePassword(Data& data, string& new_pass);
	bool CheckUser(Data& data, int& u); // для смены проверка и для коллизий подойдёт
	bool CheckCol(Data& data, int& u);
	bool Empty();
};