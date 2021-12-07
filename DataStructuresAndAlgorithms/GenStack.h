#pragma once
//////////////////////////////////////////////////////////////////////////
/// 栈的向量实现

#include <vector>

template<class T, int capacity = 30>
class Stack
{
public:
	Stack()
	{
		pool.reserve(capacity);
	}

	~Stack(void)
	{

	}

	void clear()
	{
		pool.clear();
	}

	bool isEmpty()
	{
		return pool.empty();
	}

	T topEl()
	{
		return pool.back();
	}

	void push(const T& el)
	{
		pool.push_back(el);
	}

	T pop()
	{
		T el = pool.back();
		pool.pop_back();
		return el;	
	}

private:
	std::vector<T> pool;
};

