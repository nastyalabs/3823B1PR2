#ifndef STACK_H
#define STACK_H
#pragma once
#include <iostream>
using namespace std;
template <class T>
class Stack
{
	T* pMem;
	T* end;
	int size;
public:

	Stack(int i = 3) : size(i)
	{
		pMem = new T[size];
		end = pMem;
	}

	Stack(const Stack& _A) : size(_A.size)
	{
		pMem = new T [size]();
		end = _A.end;
		std::copy(_A.pMem, _A.end, pMem);
	}

	~Stack()
	{
		delete[] pMem;
	}

	bool empty()
	{
		if (end == pMem) return true;
		return false;
	}
	

	T top()
	{
		if (pMem == end)
		{
			return 0;
		}
		return *(end - 1);	
	}

	void push(T elem)
	{
		if (end == pMem + size)
		{
			T* var = new T[size * 2];
			end = var + size;
			std::copy(pMem, pMem + size, var);
			size = size * 2;
			delete[] pMem;
			pMem = var;
		}
		*end = elem;
		end++;
		size++;
	}

	T pop()
	{
		if (end == pMem)
		{
			return 0;
		}
		end--;
		size--;
		return *(end);
	}

	bool operator==(Stack<T>& a)
	{
		if (this == &a)
			if ((*this).end != a.end)		return 1;
			else return 0;
		if (size != a.size) return 0;
		for (size_t i = 0; i < size; i++)
			if (pMem[i] != a.pMem[i])
				return 0;
		return 1;
	}


	friend ostream& operator<<(ostream& out, const Stack& a) {
		for (int i = 0; i < a.end; i++)
			out << a.begin[i] << ' ';
		return out;
	}
};
#endif