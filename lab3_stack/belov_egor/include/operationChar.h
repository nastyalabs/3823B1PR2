// ННГУ, ВМК, Курс "Алгоритмы и структуры данных", С++, ООП
//
// operationChar.h - Copyright (c) Белов Е.А.
//
// Сущность операций

#ifndef __OPERATIONCHAR_H__
#define __OPERATIONCHAR_H__

#include <iostream>
#include <cmath>
using namespace std;

class OperationChar {
protected:
    char symbol;
    unsigned int priority;
public:
    OperationChar(char sym = '+') {
        symbol = sym;
        switch(sym) {
            case '(':
                priority = 0;
                break;
            case ')':
                priority = 0;
                break;
            case '+':
                priority = 1;
                break;
            case '-':
                priority = 1;
                break;
            case '*':
                priority = 2;
                break;
            case '/':
                priority = 2;
                break;
            case '^':
                priority = 3;
                break;
            case 'f':
                priority = 4;
                break;
            default: throw "UNKNOWN!";
        }
    }
    OperationChar(const OperationChar& c) : symbol(c.symbol), priority(c.priority) {}
    OperationChar operator=(const OperationChar& c) {symbol = c.symbol; priority = c.priority; return *this;}
    ~OperationChar() {}
    
    double exec(double a, double b) {
        switch(symbol) {
            case '+':
                return a + b;
            case '-':
                return a - b;
            case '*':
                return a * b;
            case '/':
                return a / b;
            case '^':
                return pow(a, b);
            default: throw "DUMB!";
        }
    }
    
    double exec(double a) {
        switch(symbol) {
            case 'f':
                return a;
            default: throw "DUMB!";
        }
    }
    
    bool operator>(const OperationChar& c) const { return priority > c.priority; }
    bool operator<(const OperationChar& c) const { return priority < c.priority; }
    bool operator<=(const OperationChar& c) const { return priority <= c.priority; }
    bool operator>=(const OperationChar& c) const { return priority >= c.priority; }
    bool operator==(const OperationChar& c) const { return priority == c.priority; }
    bool operator!=(const OperationChar& c) const { return priority != c.priority; }
    
    char get_char() const { return symbol; }
    char get_priority() const { return priority; }
};

#endif
