#include "MyStack.h"

MyStack::~MyStack()
{
	while (Head != NULL)
	{
		Zh* temp = Head->Next;
		delete Head;
		Head = temp;
	}
}

void MyStack::push(int N)
{
	Zh* temp = new Zh;
	temp->Next = Head;
	temp->V = N;
	Head = temp;
}

void MyStack::pop()
{
	Zh* temp = Head->Next;
	delete Head;
	Head = temp;
}

int MyStack::size()
{
	int Count = 0;
	Zh* temp = Head;
	while (temp != NULL)
	{
		Count++;
		temp = temp->Next;
	}
	return Count;
}

int MyStack::top()
{
	int top = (Head->V);
	return top;
}

bool MyStack::empty()
{
	bool EMPTY;
	if (Head != NULL)
		EMPTY = false;
	else
		EMPTY = true;

	return EMPTY;

}