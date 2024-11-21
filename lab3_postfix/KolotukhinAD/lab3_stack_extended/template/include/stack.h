#ifndef __STACK_H__
#define __STACK_H__
#pragma once
#include <iostream>
#include <iomanip>
using namespace std;
template<typename T>
class stack {
private:
    size_t size; // макс кол-во эл-тов в стеке
    T* begin;
    T* end;
public:
    stack(size_t _size = 1) : size(_size) {
        if (size < 1) {
            throw invalid_argument("[STACK] size less than 1");
        }
        begin = new T[size]();
        end = begin;
    }

    stack(const stack<T>& _other) : size(_other.size) {
        begin = new T[size]();
        std::copy(_other.begin, _other.begin + _other.getSize(), begin);
        end = begin + _other.getSize();
    }

    ~stack() {
        delete[] begin;
    }

    T& top() const {
        if (isEmpty()) {
            throw out_of_range("[TOP] stack is empty");
        }
        return *(end - 1);
    }
    
    void pop() {
        if (isEmpty()) {
            throw out_of_range("[POP] stack is empty");
        }
        end--;
    }

    void print() const {
        if (isEmpty()) {
            cout << "empty" << endl;
        } else {
            T* ptr = begin;
            while (ptr != end) {
                cout << *ptr++ << "  ";
            }
            cout << endl;
        }
    }

    void addMem() {
        T* tmp = new T[size]();
        std::copy(begin, begin + size, tmp);
        delete[] begin;
        begin = new T[size * 2]();
        end = begin + size;
        std::copy(tmp, tmp + size, begin);
        size *= 2;
        delete[] tmp;
    }

    void push(const T& elem) {
        if (this->getSize() == this->getMaxSize()) {
            this->addMem(); // throw out_of_range("[PUSH] stack is full");
        }
        *end++ = elem;
    }

    bool isEmpty() const {
        return begin == end;
    }

    int getSize() const { // текущее кол-во эл-тов в стеке
        return end - begin;
    }

    int getMaxSize() const { // MAX кол-во эл-тов в стеке
        return size;
    }

    bool operator==(const stack<T>& _other) const {
        if (this->getSize() != _other.getSize()) {
            return false;
        }
        for (size_t i = 0; i < _other.getSize(); i++) {
            if (begin[i] != _other.begin[i]) {
                return false;
            }
        }
        return true;
    }

    stack& operator=(const stack<T>& _other) {
        if (!(*this == _other)) {
            if (this->getMaxSize() < _other.getSize()) {
                delete[] this->begin;
                this->size = _other.size;
                this->begin = new T[size]();
            }
            std::copy(_other.begin, _other.begin + _other.getSize(), begin);
            end = begin + _other.getSize();
        }
        return *this;
    }

    friend ostream& operator<<(ostream& ostr, const stack<T>& a) {
		for (int i = 0; i < a.getSize(); i++)
			ostr << a.begin[i] << "  ";
		return ostr;
	}
};
#endif
// (a + b * c) * (c / d - e) -> abc*+cd/e-*