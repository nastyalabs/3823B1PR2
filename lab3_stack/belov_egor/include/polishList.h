// ННГУ, ВМК, Курс "Алгоритмы и структуры данных", С++, ООП
//
// polishList.h - Copyright (c) Белов Е.А.
//
// Связный список для хранения польской записи арифметических выражений

#ifndef __POLISHLIST_H__
#define __POLISHLIST_H__

#include "operationChar.h"

enum type {null, num, operation, function};

struct PolishCell {
    PolishCell* left;
    PolishCell* right;
    type info;
    void* value;
    PolishCell() : value(nullptr), info(null), left(nullptr), right(nullptr) {
        std::cout << "Hello" << std::endl;
    }
    PolishCell(const OperationChar& val) : left(nullptr), right(nullptr) {
        info = operation;
        value = (void*)(new OperationChar(val));
    }
    PolishCell(const double& val) : left(nullptr), right(nullptr) {
        info = num;
        value = (void*)(new double(val));
    }
    ~PolishCell() {
        if (info == num) {
            delete (double*)value;
        }
        else if (info == operation) {
            delete (OperationChar*)value;
        }
    }
};

class PolishList { // ЭТОТ КЛАСС РАЗРЕШЕНО ИСПОЛЬЗОВАТЬ ТОЛЬКО В КЛАССЕ prefixModule
protected:
    PolishCell* pointer;
public:
    PolishList() : pointer(nullptr) {}
    ~PolishList();
    
    
    void push(const double& val);
    void push(const OperationChar& val);
    
    void pop();
    
    type getInfo() { return pointer->info; }
    void* get() { return pointer->value; }
    
    void setNeedle(PolishCell* need) { pointer = need; }
    
    void left();
    void right();
    
    void toCalculate();
    void toNextOp();
    
    bool isNextNull() { return pointer->right == nullptr; }
    bool isPrevNull() { return pointer->left == nullptr; }
};


#endif
