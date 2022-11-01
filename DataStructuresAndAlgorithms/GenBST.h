
// GenBST.h
// genenal binary search tree
// ����������������������, ������������:
// �������е�ÿ���ڵ�n, ���������е�ֵС�ڽڵ�n�е�ֵ, ���������е�ֵ���ڽڵ�n�е�ֵ��


#ifndef _GENBST_H
#define _GENBST_H

#include <stack>
#include <queue>

//////////////////////////////////////////////////////////////////////////
// Stack
template<class T>
class Stack : public std::stack<T> 
{  
};

//////////////////////////////////////////////////////////////////////////
/// Queue
template<class T>
class Queue : public std::queue<T>
{
public:
	T dequeue()
	{
		T temp = this->front();
		this->pop();
		return temp;
	}

	void enqueue(const T& el)
	{
		this->push(el);
	}
};

//////////////////////////////////////////////////////////////////////////
/// BSTNode
template<class T>
class BSTNode
{
public:
	BSTNode()
	{
		left = right = 0;
	}

	BSTNode(const T& e, BSTNode<T>* l=0, BSTNode<T>* r=0)
	{
		el = e;
		left = l;
		right = r;
	}

	T el;
	BSTNode<T>* left, *right;
};

//////////////////////////////////////////////////////////////////////////
/// BST
template<class T>
class BST
{
public:
	BST(void);
	~BST(void);

	
	void clear();

	void isEmpty();

	// ����
	T* search(const T& e);

	// ������ȱ���
	void breadthFirst();

	/************************************************************************/
	/*          ������ȱ���-�ݹ�                                                        
	/************************************************************************/
	void inOrder();	
	void preOrder();
	void postOrder();

	/************************************************************************/
	/*      ������ȱ���-�ǵݹ�                                                               
	/************************************************************************/
	void Iterative_InOrder();
	void Iterative_PreOrder();
	void Iterative_PostOrder();
	
	/***********************************************************************
	**      ������ȱ���-�ǵݹ�-ͳһд��      
	**  ����������Ҫ�����Ƿ��ʽڵ�ʹ���ڵ㲻һ�¡�
    **	�������ǽ����ʽڵ����ջ�У���Ҫ����Ľڵ�Ҳ����ջ�е���Ҫ����ǡ�
	** 	��α���أ�����Ҫ����Ľڵ����ջ֮�󣬽����ŷ���һ����ָ����Ϊ��ǡ� ���ַ���Ҳ���Խ�����Ƿ���
	/************************************************************************/
	void Unified_Iterative_InOrder();
	void Unified_Iterative_PreOrder();
	void Unified_Iterative_PostOrder();

	// ����
	void insert(const T& el);

	void findAndDeleteByMerge(const T& el);

protected:
	virtual void visit(BSTNode<T>* p);

	T* search(BSTNode<T>* p, const T& e) const;

	// �ϲ�ɾ��
	void DeleteByMerge(BSTNode<T>*& p);

	void inOrder(BSTNode<T>* p);
	void preOrder(BSTNode<T>* p);
	void postOrder(BSTNode<T>* p);

protected:
	BSTNode<T>* root;
};

template<class T>
void BST<T>::findAndDeleteByMerge(const T& el)
{
	BSTNode<T>* node = root, *prev = nullptr;
	while(node != 0)
	{
		if(node->el == el)
			break;

		prev = node;
		if(node->el > el)
			node = node->left;
		else
			node = node->right;
	}

	if (node != nullptr)
	{
		if (node == root)
			DeleteByMerge(root);
		else if(prev->left == node)
			DeleteByMerge(prev->left);
		else
			DeleteByMerge(prev->right);			
	}

}








#endif // _GENBST_H



