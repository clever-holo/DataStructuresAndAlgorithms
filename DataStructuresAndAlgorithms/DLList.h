#pragma once

/// 双向链表

template<class T>
class DLLLNode
{
public:
	DLLLNode(void)
	{
		next = prev = 0;
	}

	DLLLNode(const T& el, DLLLNode* n=0, DLLLNode* p=0)
	{
		info = el;
		next = n;
		prev = p;
	}

public:
	T info;
	DLLLNode *next, *prev;
};

template<class T>
class DoublyLinkedList
{
	DoublyLinkedList()
	{
		head = tail = 0;
	}

	/// 添加到尾部
	void addToTail(const T& el);

	/// 从尾部删除
	T deleteFromTail();



protected:
	DLLLNode<T> *head, *tail;
};

template<class T>
void DoublyLinkedList<T>::addToTail(const T& el)
{
	if(head == 0)
	{
		head = tail = new DLLLNode<T>(el);
	}
	else
	{
		tail->next = new DLLLNode<T>(el, 0, tail);
		tail = tail->next;
	}
}

template<class T>
T DoublyLinkedList<T>::deleteFromTail()
{
	if(tail == 0)
	{
		return T();
	}
	else
	{
		T rs = tail->info;

		if(head == tail)
		{	
			delete tail;
			head = tail = 0;
		}
		else
		{	
			tail = tail->prev;
			delete tail->next;
			tail->next = 0;		
		}
		return rs;
	}
}