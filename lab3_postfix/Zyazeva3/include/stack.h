#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <stdexcept> 
#include <algorithm> 

template <class T>
class Stack {
    size_t size; //максимальный размер стека
    int top; //индекс "верхнего" элемента
    T* pMem; 

public:
    Stack() : size(1), pMem(new T[size]), top(-1) {}
    Stack(size_t _n) : size(_n), pMem(new T[size]), top(-1) {}

    Stack(const Stack& _A) { 
        size = _A.size;
        top = _A.top;
        pMem = new T[size];
        for (int i = 0; i <= top; i++) { 
            pMem[i] = _A.pMem[i];
        }
    }

    ~Stack() { 
        delete[] pMem;
    }

    void Push(T a) { 
        if (top == size - 1) {
            T* tmpMem = new T[size * 2];
            std::copy(pMem, pMem + size, tmpMem);
            size *= 2;
            delete[] pMem;
            pMem = tmpMem;
        }
        pMem[++top] = a;
    }

    T Top() { 
        if (top == -1) {
            return 0;
        }
        return pMem[top];
    }

    T Pop() {
        if (top == -1){
            throw ("The stack is empty");
        }
        return pMem[top--];
    }

    bool empty() const { 
        return top == -1;
    }

    int Size() const {
        return size;
    }

    void clear() {
        top = -1;
    }

    friend std::ostream& operator<<(std::ostream& out, const Stack& a) {
        for (int i = 0; i <= a.top; i++) //
            out << a.pMem[i] << ' ';
        return out;
    }
};

#endif

