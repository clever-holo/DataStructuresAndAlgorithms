#include <iostream>

template <class T>
class DLList
{
	struct Node
	{
		T data;
		Node* next;
		Node* prev;
		Node(T val): data(val), next(nullptr), prev(nullptr){}
	};

public:
	DLList(): head(nullptr), tail(nullptr){}

	~DLList()
	{
		Node *tmp = nullptr;
		while(head)
		{
			tmp = head;
			head = head->next;
			delete tmp;
		}
		head = nullptr;
	}

public:
	
	// �Ƿ�Ϊ��
	bool isEmpty()
	{
		return head == nullptr;
	}

	// �Ƿ����ֵ
	bool isExist(T val)
	{
		return findVal(val) != nullptr;
	}

	// ��ͷ����
	void insertFront(T val)
	{
		Node *node = new Node(val);
		if(head == nullptr)
		{
			head = node;
			tail = node;
		}
		else
		{
			node->next = head;
			head->prev = node;
			head = node;
		}
	}

	// ��β����
	void insertBack(T val)
	{
		Node *node = new Node(val);
		if(head == nullptr)
		{
			head = node;
			tail = node;
		}
		else
		{
			node->prev = tail;
			tail->next = node;
			tail = node;
		}
	}

	// ɾ��
	void deleteVal(T val)
	{
		Node* node = findVal(val);
		if(node)
		{
			// ͷ�ڵ�
			if(node->prev == nullptr)
			{
				// ͷ�ڵ�ָ����
				head = node->next;
			}
			else
			{
				// ǰһ���ڵ�ָ����
				node->prev->next = node->next;
			}

			// β�ڵ�
			if (node->next == nullptr)
			{
				// β�ڵ�ָ��ǰ��
				tail = node->prev;
			}
			else
			{
				// ��һ���ڵ�ָ��ǰ��
				node->next->prev = node->prev;
			}
		}
	}

	friend std::ostream& operator << (std::ostream& out, DLList<T>& dll)
	{
		out << "asc: ";
		for (Node* temp = dll.head; temp != nullptr; temp = temp->next)
		{
			out << temp->data << " ";
		}
		out << std::endl;

		out << "desc: ";
		for (Node* temp = dll.tail; temp != nullptr; temp = temp->prev)
		{
			out << temp->data << " ";
		}
		out << std::endl;
		return out;
	};

private:
	// ���ҽڵ�
	Node* findVal(T val)
	{
		for (Node* temp = head; temp != nullptr; temp = temp->next)
		{
			if(temp->data == val)
				return temp;
		}
		return nullptr;
	}

private:
	Node *head;
	Node *tail;

};