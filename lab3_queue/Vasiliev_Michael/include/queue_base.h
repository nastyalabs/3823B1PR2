#ifndef __QUEUE_BASE_H__
#define __QUEUE_BASE_H__

#pragma once
#include <iostream>
using namespace std;
template <typename T>
class TQueue
{
	T* begin;
	T* _el;  // ptr to first element (that would be popped)
	T* end;
	size_t size;
public:
	TQueue(size_t sz = 10): size(sz) {
		begin = new T[size];
		_el = begin;
		end = begin;
	}

	TQueue(const TQueue& _A): size(_A.size) {
		begin = new T[size];
		int elements = _A.end - _A.begin;
		for (int i = 0; i < elements; i++) {
			begin[i] = _A.begin[i];
		}
		_el = begin;
		end = begin + elements;
	}

	~TQueue()
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
			_el = begin;
			end = begin + elements;
			size *= 2;
		}
		*end = a;
		end++;
	}

	T top() {
		if (isEmpty()) {
			throw ("Queue is empty.");
		}
		return *(_el);
	}

	T pop() {
		if (isEmpty()) {
			throw ("Queue is empty.");
		}

		T val = *_el;
		_el++;
		return val;
	}
	
	bool isEmpty() {
		return end == begin;
	}

	size_t Size() {
		return size;
	}

	TQueue& operator=(const TQueue& q)
	{
		if (this == &q) {
		return *this;
		}

		delete[] begin;
		size = q.size;
		begin = new T[size];

		int elements = q.end - q.begin;
		for (int i = 0; i < elements; i++) {
			begin[i] = q.begin[i];
		}
		_el = begin;
		end = begin + elements;

		return *this;
	}

	bool operator==(TQueue<T>& a) {
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

	friend ostream& operator<<(ostream& out, const TQueue& a) {
		for (int i = 0; i < a.end - a.begin; i++)
			out << a.begin[i] << ' ';
		return out;
	}
};
#endif
