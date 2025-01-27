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
	int size;
public:
	Stack() : size(1) {
		begin = new T[size];
		end = begin;
	};
	Stack(int _n) {
		if (_n < 0) {
			throw ("Size must be positive");
		}
		size = _n;
		begin = new T[size];
		end = begin;
	};
	Stack(const Stack& _A) {
		size = _A.size;
		begin = new T[size];
		int values = _A.end - _A.begin;
        for (int i = 0; i < values; i++) {
            begin[i] = _A.begin[i];
        }
		end = begin + values;
	};
	~Stack() { delete[] begin; };
	void Push(T a) {
		if (end - begin == size) {
			T* _begin = new T[size * 2];
			int values = end - begin;
			for (size_t i = 0; i < values; i++) {
				_begin[i] = begin[i];
			}
			delete[] begin;
			begin = _begin;
			end = begin + values;
			size++;
		}
		*end = a;
		end++;
	};
	T top() {
		if (empty()) {
			throw ("empty stack");
		}
		return *(end - 1);
	};
	T pop() {
		if (empty()) {
			throw ("empty stack");
		}
		end--;
		return *end;
	};
	bool empty() { return end == begin; };
	int Size() { return size; };
	bool operator==(Stack<T>& a) {
		int length = end - begin;
		if (size < a.size) {
			length = a.end - a.begin;
		}
        for (int i = 0; i < length; i++) {
            if (begin[i] != a.begin[i]) {
                return false;
            }
        }
        return true;
	};
	friend ostream& operator<<(ostream& out, const Stack& a) {
		for (int i = 0; i < a.end - a.begin; i++)
			out << a.begin[i] << ' ';
		return out;
	}
};
#endif
