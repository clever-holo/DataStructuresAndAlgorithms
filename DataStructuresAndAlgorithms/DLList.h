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
	
	// 是否为空
	bool isEmpty()
	{
		return head == nullptr;
	}

	// 是否存在值
	bool isExist(T val)
	{
		return findVal(val) != nullptr;
	}

	// 从头插入
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

	// 从尾插入
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

	// 删除
	void deleteVal(T val)
	{
		Node* node = findVal(val);
		if(node)
		{
			// 头节点
			if(node->prev == nullptr)
			{
				// 头节点指向后边
				head = node->next;
			}
			else
			{
				// 前一个节点指向后边
				node->prev->next = node->next;
			}

			// 尾节点
			if (node->next == nullptr)
			{
				// 尾节点指向前边
				tail = node->prev;
			}
			else
			{
				// 后一个节点指向前边
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
	// 查找节点
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