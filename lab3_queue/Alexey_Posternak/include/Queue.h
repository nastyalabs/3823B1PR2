#ifndef __QUEUE_H__
#define __QUEUE_H__

#pragma once
#include <iostream>
using namespace std;
template <typename T>
class TQueue
{
	T* begin;
	T* end;
	size_t size;
public:

    TQueue() : begin(nullptr), size(0) { end = begin; }

    TQueue(size_t s) : size(s) {
        if (s < 0) {
            throw ("size must be positive");
        }
        begin = new T[size];
        end = begin;
    }

    ~TQueue() {
        delete[] begin;
    }

    TQueue(const TQueue& other) : size(other.size) {
        begin = new T[size];
		int el = other.end - other.begin;
		for (int i = 0; i < el; i++) {
			begin[i] = other.begin[i];
		}
		end = begin + el;
    }



    bool operator==(const TQueue& other) const {
        int length = end - begin;
		if (size < other.size) {
			length = other.end - other.begin;
		}
        for (int i = 0; i < length; i++) {
            if (begin[i] != other.begin[i]) {
                return false;
            }
        }
        return true;
    }

    bool empty() { return end == begin; };
	int Size() { return size; };	

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
			size *= 2;
		}
        for (size_t i = end - begin; i > 0; i--) {
            begin[i] = begin[i - 1];
        }
        end++;
        *begin = a;
	};
	T top() {
		if (empty()) {
            throw ("Queue is empty");
        }
        return *begin;
	};
	void pop() {
		if (empty()) {
            throw ("Queue is empty");
        }
        
        end--;
        for (size_t i = 0; i < end - begin; i++) {
            begin[i] = begin[i + 1];
        }
	};

	friend ostream& operator<<(ostream& out, const TQueue& a) {
		for (int i = 0; i < a.end - a.begin; i++)
			out << a.begin[i] << ' ';
		return out;
	}
};
#endif
