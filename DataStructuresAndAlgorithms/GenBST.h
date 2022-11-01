
// GenBST.h
// genenal binary search tree
// 二叉查找树（有序二叉树）, 具有如下特性:
// 对于树中的每个节点n, 其左子树中的值小于节点n中的值, 其右子树中的值大于节点n中的值。


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

	// 搜索
	T* search(const T& e);

	// 广度优先遍历
	void breadthFirst();

	/************************************************************************/
	/*          深度优先遍历-递归                                                        
	/************************************************************************/
	void inOrder();	
	void preOrder();
	void postOrder();

	/************************************************************************/
	/*      深度优先遍历-非递归                                                               
	/************************************************************************/
	void Iterative_InOrder();
	void Iterative_PreOrder();
	void Iterative_PostOrder();
	
	/***********************************************************************
	**      深度优先遍历-非递归-统一写法      
	**  迭代遍历主要问题是访问节点和处理节点不一致。
    **	处理方法是将访问节点放入栈中，把要处理的节点也放入栈中但是要做标记。
	** 	如何标记呢，就是要处理的节点放入栈之后，紧接着放入一个空指针作为标记。 这种方法也可以叫做标记法。
	/************************************************************************/
	void Unified_Iterative_InOrder();
	void Unified_Iterative_PreOrder();
	void Unified_Iterative_PostOrder();

	// 插入
	void insert(const T& el);

	void findAndDeleteByMerge(const T& el);

protected:
	virtual void visit(BSTNode<T>* p);

	T* search(BSTNode<T>* p, const T& e) const;

	// 合并删除
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



