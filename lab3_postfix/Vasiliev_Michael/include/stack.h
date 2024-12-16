#ifndef __STACK_H__
#define __STACK_H__
#pragma once
#include <iostream>
using namespace std;
template <class T>
class Stack
{
	T* begin;
	T* end;
	size_t size;
public:
	Stack(): size(1) {
		begin = new T[size];
		end = begin;
	}

	Stack(size_t _n): size(_n)
	{
		begin = new T[_n];
		end = begin;
	}

	Stack(const Stack& _A): size(_A.size) {
		begin = new T[size];
		int elements = _A.end - _A.begin;
		for (int i = 0; i < elements; i++) {
			begin[i] = _A.begin[i];
		}
		end = begin + elements;
	}

	~Stack()
	{
		delete[] begin;
	}

	void Push(T a) {
		if (end - begin == size) {
			T* _begin = new T[size * 2];
			copy(begin, begin + size, _begin);
			
			int elements = end - begin;
			delete[] begin;
			begin = _begin;
			end = begin + elements;
			size *= 2;
		}
		*end = a;
		end++;
	}

	T top() {
		if (empty()) {
			throw ("Stack is empty.");
		}
		return *(end - 1);
	}

	T pop() {
		if (empty()) {
			throw ("Stack is empty.");
		}
		end--;
		return *end;
	}
	
	bool empty() {
		return end == begin;
	}

	size_t Size() {
		return size;
	}

	Stack& operator=(const Stack& s)
	{
		if (this == &s) {
		return *this;
		}

		delete[] begin;
		size = s.size;
		begin = new T[size];

		int elements = s.end - s.begin;
		for (int i = 0; i < elements; i++) {
			begin[i] = s.begin[i];
		}
		end = begin + elements;

		return *this;
	}

	bool operator==(Stack<T>& a) {
	if ((end - begin) != (a.end - a.begin)) {
      return false;
	}

    for (size_t i = 0; i < (end - begin); i++) {
      if (begin[i] != a.begin[i]) {
        return false;
      }
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
