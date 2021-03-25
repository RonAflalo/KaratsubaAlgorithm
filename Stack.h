#pragma once
#include "ItemT.h"

namespace NumArr
{
	class ItemT;
	class Stack
	{
	private:
		struct itemNode
		{
			ItemT item;
			itemNode* next;
		};
		itemNode* top;
		bool done;

	public:
		Stack();
		~Stack();
		bool isEmpty();
		void MakeEmpty();
		void Push(ItemT item);
		ItemT Pop(void);
		ItemT getTop();
		bool getDone();
		void setDone(int num);

	};


}