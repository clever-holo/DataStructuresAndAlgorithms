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
	IntSLList()	{
		head = tail = 0;
	}

	~IntSLList();

public:
	// ÊÇ·ñÎª¿Õ
	int isEmpty() {
		return head == 0;
	}

	// 
	void addToHead(int el);

	// 
	void addToTail(int el);

	//
	int deleteFromHead();

	//
	int deleteFromTail();

	//
	void deleteNode(int el);

	//
	bool isInList(int el) const;


private:
	IntSLLNode *head;
	IntSLLNode *tail;
};

