#include <iostream>

struct Zh
{
	int V;
	Zh* Next;
};

class MyStack
{
	Zh* Head;
public:
	MyStack() :Head(NULL) {};
	void push(int N);
	int size();
	void pop();
	int top();
	bool empty();
	~MyStack();
};