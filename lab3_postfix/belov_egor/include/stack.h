// ННГУ, ВМК, Курс "Алгоритмы и структуры данных", С++, ООП
//
// stack.h - Copyright (c) Белов Е.А.
//
// Стэк

#ifndef __STACK_H__
#define __STACK_H__

#include <iostream>


const size_t STANDART_STACK_SIZE = 10;
const size_t MAX_STACK_SIZE = 10000000;

template <class T>
class Stack {
protected:
    size_t MemLen;  // максимальное количество элементов в стэке
    T* begin;  // указатель на первый элемент стэка
    T* end; // указатель на следующий элемент после последннего элемента стэка
public:
    Stack(size_t sz = STANDART_STACK_SIZE) : MemLen(sz) {
        if (sz == 0 || sz > MAX_STACK_SIZE) {
            throw -1;
        }
        end = begin = new T[sz];
    }
    Stack(const Stack& s) : MemLen(s.MemLen) {
        begin = new T[MemLen];
        memcpy(begin, s.begin, MemLen * sizeof(T));
        end = s.end - s.begin + begin;
    }
    Stack(Stack&& s) : MemLen(s.MemLen) {
        begin = s.begin;
        end = s.end;
        s.end = s.begin = nullptr;
    }
    
    ~Stack() { delete[] begin; }
    
    void resize(size_t sz) {
        if (sz == 0 || sz > MAX_STACK_SIZE) {
            throw -1;
        }
        if (sz == MemLen) {
            return;
        }
        
        T* temp = new T[sz];
        size_t i = 0;
        for (; i < sz && i < MemLen; i++) {
            temp[i] = begin[i];
        }
        
        MemLen = sz;
        delete[] begin;
        begin = temp;
        end = temp + i;
    }
    
    bool operator==(const Stack& s) const {
        if ((end - begin) != (s.end - s.begin)) {
            return false;
        }
        for (size_t i = 0; i < end - begin; i++) {
            if (begin[i] != s.begin[i]) {
                return false;
            }
        }
        return true;
    }
    bool operator!=(const Stack& s) const {
        if ((end - begin) != (s.end - s.begin)) {
            return true;
        }
        for (size_t i = 0; i < end - begin; i++) {
            if (begin[i] != s.begin[i]) {
                return true;
            }
        }
        return false;
    }
    
    Stack& operator=(const Stack& s) {
        if (*this == s) {
            return *this;
        }
        if (MemLen != s.MemLen) {
            T* t = new T[s.MemLen];
            delete[] begin;
            begin = t;
            MemLen = s.MemLen;
        }
        memcpy(begin, s.begin, MemLen * sizeof(T));
        end = s.end - s.begin + begin;
        return *this;
    }
    Stack& operator=(Stack&& s) {
        if (*this == s) {
            return *this;
        }
        begin = s.begin;
        end = s.end;
        MemLen = s.MemLen;
        s.end = s.begin = nullptr;
        return *this;
    }
    
    size_t size() const { return end - begin; }
    size_t maxSize() const { return MemLen; }
    bool isEmpty() const { return end == begin; }
    bool isFull() const { return end - begin == MemLen; }
    
    void push(T elem) {
        if (end - begin >= MemLen) {
            resize(MemLen + STANDART_STACK_SIZE);
        }
        *end = elem;
        end++;
    }
    void pop() {
        if (end <= begin) {
            throw -1;
        }
        end--;
    }
    T top() {
        if (end <= begin) {
            throw -1;
        }
        return *(end - 1);
    }
    void clear() {
        end = begin;
    }
};


#endif
