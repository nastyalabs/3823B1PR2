#ifndef __ALGEXP_H__
#define __ALGEXP_H__
#pragma once
#include "stack.h"
#include "string"
class algexp {
    private:
        string expression; // постфиксная форма записи
    public:
        algexp();
        algexp(string expr);
        algexp(const algexp& _other);
        string getExpr();
        double solveIt() const;
        algexp operator=(const algexp& _other);
        bool operator==(const algexp& _other) const;
        friend ostream& operator<<(ostream& ostr, const algexp& _algexp);
};
#endif
