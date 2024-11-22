#ifndef __STACK_H__
#define __STACK_H__
#pragma once
#include <iostream>

using namespace std;

template <class T>
class Stack {
	T* begin;
	T* end;
	int size;
public:

	Stack() : size(5) {
		begin = new T[size];
		end = begin;
	}

	Stack(int _n) : size(_n) {
		begin = new T[size];
		end = begin;
	}

	Stack(const Stack& _A) : size(_A.size) {
		begin = new T[size];
		for (int i = 0; i < size; ++i) {
			begin[i] = _A.begin[i];
		}
		end = begin + size;
	}

	//~Stack() { delete[] begin; }

	void Push(T a) {
		if (end == begin + size)
		{
			int newsize = size * 2;
			T* newst = new T[newsize];
			for (int i = 0; i < size; ++i) {
				newst[i] = begin[i];
			}			
			end = newst + (end - begin);
			delete[] begin;
			begin = newst;
			size = newsize;
		}
		*end = a;
		end++;
	}

	T top()	{
		if (begin == end)
			return T();
		return *(end - 1);
	}

	T pop()	{
		if (end == begin)
			return T();
		end--;
		return *(end);
	}

	bool empty() { return end == begin; }

	int Size() { return end - begin; }

	bool operator==(Stack<T>& a) {
		if (Size() != a.Size()) 
			return false;
		for (int i = 0; i < Size(); ++i) {
			if (begin[i] != a.begin[i]) 
				return false;
		}
		return true;
	}

	friend ostream& operator<<(ostream& out, const Stack& a) {
		for (int i = 0; i < a.end - a.begin; i++)
			out << a.begin[i] << ' ';
		return out;
	}

};
#endif
