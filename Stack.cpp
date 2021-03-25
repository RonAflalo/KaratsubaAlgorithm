#include "Stack.h"
#include<iostream>
using namespace std;
using namespace NumArr;

Stack::Stack()
{
	top = nullptr;
	done = false;
}

Stack::~Stack()
{
	MakeEmpty();
}

bool Stack::isEmpty()
{
	if (top == nullptr)
		return true;
	return false;
}

void Stack::MakeEmpty()
{
	itemNode* temp;
	while (top != nullptr)
	{
		temp = top;
		top = top->next;
		delete temp;
	}
}

void Stack::Push(ItemT _item)
{
	itemNode* newTop = new itemNode;
	newTop->item.set(_item);
	newTop->next = top;
	top = newTop;
}

ItemT Stack::Pop(void)
{
	if (isEmpty())
	{
		cout << "stack is empty";
		exit(1);
	}

	itemNode* temp = top;
	ItemT Itemp;
	Itemp.set(top->item);
	top = top->next;
	delete temp;
	return Itemp;
}

ItemT Stack::getTop()
{
	return top->item;
}

bool Stack::getDone()
{
	return done;
}

void Stack::setDone(int num)
{
	if (num == 1)
		done = true;
	else done = false;
}