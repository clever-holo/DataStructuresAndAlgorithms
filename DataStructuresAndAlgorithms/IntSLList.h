/// *********************  IntSLList.h  *******************
// singly-linked list class to store integers

#pragma once



class IntSLLNode
{
public:
	IntSLLNode()
	{
		next = 0;
	}
	IntSLLNode(int el, IntSLLNode *ptr = 0)
	{
		info = el;
		next = ptr;
	}

public:
	int info;
	IntSLLNode *next;
};




class IntSLList
{
public:
	IntSLList()
	{
		head = tail = 0;
	}
	~IntSLList();

public:
	int isEmpty()
	{
		return head == 0;
	}




private:
	IntSLLNode *head;
	IntSLLNode *tail;
};

