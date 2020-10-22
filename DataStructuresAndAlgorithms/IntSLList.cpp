#include "IntSLList.h"


IntSLList::~IntSLList()
{
	for(IntSLLNode* p; !isEmpty();){
		p = head->next;
		delete head;
		head = p;
	}
}

void IntSLList::addToHead(int el)
{
	if(head == 0){
		head = tail = new IntSLLNode(el);
	}
	else{
		head = new IntSLLNode(el, head);
	}
	return;
}

void IntSLList::addToTail(int el)
{
	if(head == 0){
		head = tail = new IntSLLNode(el);
	}
	else {
		tail->next = new IntSLLNode(el);
		tail = tail->next;
	}
	return;
}

int IntSLList::deleteFromHead()
{
	if(head == 0)
		return 0;

	int rs = head->info;
	IntSLLNode* p = head;

	if(head == tail){
		head = tail = 0;
	}
	else{
		head = head->next;
	}
	
	delete p;
	return rs;
}

int IntSLList::deleteFromTail()
{
	if(head == 0)
		return 0;

	int rs = tail->info;
	IntSLLNode* p = tail;

	if(head == tail){
		head = tail = 0;
	}
	else{
		IntSLLNode* pp = head;
		while(pp->next != tail)
			pp = pp->next;
		tail = pp;
	}

	delete p;
	return rs;
}

void IntSLList::deleteNode(int el)
{
	if(head == 0)
		return;

	
	IntSLLNode* ppre = 0;
	IntSLLNode* p = head;
	while (1)
	{
		// 查找值等于el的节点
		while(p != 0 && p->info !=el )
			p = p->next;
		
		// 未找到
		if(p == 0)
			break;

		// head 的值为el
		if(ppre = 0)
		{
			p = p->next;
			deleteFromHead();
		}
		else
		{
			ppre->next = p->next;
			delete p;
			p = ppre->next;
		}
	}
	return;
}

bool IntSLList::isInList(int el) const
{
	IntSLLNode* p = head;

	// 查找值等于el的节点
	while(p != 0 && p->info !=el )
			p = p->next;

	return el == 0;
}
