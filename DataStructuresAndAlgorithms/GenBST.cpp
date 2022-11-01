#include "GenBST.h"

//////////////////////////////////////////////////////////////////////////
/// 
template<class T>
BST<T>::BST(void)
{
	root = nullptr;
}

template<class T>
BST<T>::~BST(void)
{

}

/// 
template<class T>
void BST<T>::clear()
{

}

/// 
template<class T>
void BST<T>::isEmpty()
{
	return root == nullptr;
}

/// 
template<class T>
T* BST<T>::search(const T& e)
{
	return search(root, e);
}

/// 
template<class T>
T* BST<T>::search(BSTNode<T>* p, const T& e) const
{
	while(p)
	{
		if(p->el == p)
			return &p->el;
		else if(p->el > p)
			p = p->left;
		else
			p = p->right;
	}
	return nullptr;
}

/// 
template<class T>
void BST<T>::breadthFirst()
{
	Queue<BSTNode<T>*> _queue;
	if (root)
		_queue.enqueue(p);

	while (!_queue.empty())
	{
		BSTNode<T>* p = _queue.dequeue();
		visit(p);
		if(p->left)
			_queue.enqueue(p->left);
		if(p->right)
			_queue.enqueue(p->right);
	}
}

///
template<class T>
void BST<T>::inOrder()
{
	inOrder(root);
}

///
template<class T>
void BST<T>::preOrder()
{
	preOrder(root);
}

///
template<class T>
void BST<T>::postOrder()
{
	postOrder(root);
}

///
template<class T>
void BST<T>::inOrder(BSTNode<T>* p)
{
	if (p != nullptr)
	{
		inOrder(p->left);
		visit(p);
		inOrder(p->right);
	}
}

///
template<class T>
void BST<T>::preOrder(BSTNode<T>* p)
{
	if (p != nullptr)
	{
		visit(p);
		preOrder(p->left);
		preOrder(p->right);
	}	
}

///
template<class T>
void BST<T>::postOrder(BSTNode<T>* p)
{
	if (p != nullptr)
	{
		postOrder(p->left);
		postOrder(p->right);
		visit(p);
	}
}

/// 
template<class T>
void BST<T>::visit(BSTNode<T>* p)
{
	std::cout << p->el << " ";
}

/// 
template<class T>
void BST<T>::Iterative_PostOrder()
{
	std::stack<BSTNode<T>*> s;
	BSTNode<T>* cur = 0;                 // 当前结点 
	BSTNode<T>* pre = 0;                 // 前一次访问的结点 
	s.push(root);
	while(!s.empty())
	{
		cur=s.top();
		if( (cur->left == 0 && cur->right == 0) ||
			(pre != 0 && ( pre == cur->left || pre==cur->right)))
		{
			visit(cur);  // 如果当前结点没有孩子结点或者孩子节点都已被访问过 
			s.pop();
			pre = cur; 
		}
		else
		{
			if(cur->right)
				s.push(cur->right);
			if(cur->left)    
				s.push(cur->left);
		}
	}    

}

///
template<class T>
void BST<T>::Iterative_InOrder()
{
	std::stack<BSTNode<T>*> s;
	BSTNode<T>* p = root;                 
	while(p || !s.empty())
	{
		while (p)
		{
			s.push(p);
			p = p->left;
		}

		if (!s.empty())
		{
			p = s.top();
			s.pop();
			visit(p);
			p = p->right;
		}
	}
}

/// 
template<class T>
void BST<T>::Iterative_PreOrder()
{
	if (root != nullptr)
	{
		std::stack<BSTNode<T>*> _stack;
		_stack.push(root);

		while(!_stack.empty())
		{
			BSTNode<T>* p = _stack.top();
			_stack.pop();

			visit(p);
			if(p->right != nullptr)
				_stack.push(p->right);
			if(p->left != nullptr)
				_stack.push(p->left);
		}
	}
}


template<class T>
void BST<T>::Unified_Iterative_InOrder()
{
	std::stack<BSTNode<T>*> _stack;
	if (root)
		_stack.push(root);
	
	while(!_stack.empty())
	{
		BSTNode<T>* cur = _stack.top();
		_stack.pop();

		if (cur)
		{
			if(cur->right)
				_stack.push(cur->right);

			_stack.push(cur);
			_stack.push(NULL);

			if (cur->left)
				_stack.push(cur->left);
		}
		else
		{
			cur = _stack.top();
			visit(cur);
		}
	}	
}


template<class T>
void BST<T>::Unified_Iterative_PostOrder()
{
	std::stack<BSTNode<T>*> _stack;
	if (root)
		_stack.push(root);

	while(!_stack.empty())
	{
		BSTNode<T>* cur = _stack.top();
		_stack.pop();

		if (cur)
		{
			_stack.push(cur);
			_stack.push(NULL);

			if(cur->right)
				_stack.push(cur->right);
			
			if (cur->left)
				_stack.push(cur->left);
		}
		else
		{
			cur = _stack.top();
			visit(cur);
		}
	}	
}

template<class T>
void BST<T>::Unified_Iterative_PreOrder()
{
	std::stack<BSTNode<T>*> _stack;
	if (root)
		_stack.push(root);

	while(!_stack.empty())
	{
		BSTNode<T>* cur = _stack.top();
		_stack.pop();

		if (cur)
		{
			if(cur->right)
				_stack.push(cur->right);			

			if (cur->left)
				_stack.push(cur->left);

			_stack.push(cur);
			_stack.push(NULL);
		}
		else
		{
			cur = _stack.top();
			visit(cur);
		}
	}	
}

template<class T>
void BST<T>::insert(const T& el)
{
	if (!root)
	{
		root = new BSTNode<T>(el);
	}
	else
	{
		BSTNode<T>* cur = root;
		BSTNode<T>* pre = 0;
		while(cur)
		{			
			if(el == cur->el)
				return;
			else if(el < cur->el)
				cur = cur->left;
			else
				cur = cur->right;

			pre = cur;
		}

		if (el < pre->el)
		{
			pre->left = new BSTNode<T>(el);
		}
		else
		{
			pre->right = new BSTNode<T>(el);
		}
	}
}

/// 合并删除
template<class T>
void BST<T>::DeleteByMerge(BSTNode<T>*& p)
{
	if(!p)
		return;

	BSTNode<T>* tmp = p;

	if(p->left == nullptr)
	{
		p = p->right;
	}
	else if (p->right == nullptr)
	{
		p = p->left;
	}
	else
	{
		BSTNode<T>* r_node = p->left;
		while (r_node->right)
			r_node = r_node->right; 
		r_node->right = p->right;
		p = p->left;
	}

	delete tmp;
	tmp = nullptr;
}