#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include "stack.h"
#include "vector"
#include "string.h"
#include <map>
#include <cmath>

using namespace std;

class TArithmeticExpression
{
private:
    string infix;
    string postfix;
    vector<char> lexems;
    map<char, int> priority;
public:
    TArithmeticExpression(string infx) : infix(infx) {
        priority = { {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'%', 2}, {'(', 3}, {')', 3}};
        toPostfix();
    }

    void Parse() {
        for (char c : infix) {
            lexems.push_back(c);
        }
        if (lexems.size() > 1) { // exception for /* ** -+ etc. and 4(...)
            for (int i = 0; i < lexems.size()-1; i++) {
                if (((lexems[i] == '+' || lexems[i] == '-' || lexems[i] == '*' || lexems[i] == '/' || lexems[i] == '%' || lexems[i] == '(')&& 
                (lexems[i+1] == '+' || lexems[i+1] == '-' || lexems[i+1] == '*' || lexems[i+1] == '/' || lexems[i+1] == '%')) 
                || (isdigit(lexems[i]) && lexems[i+1] == '(')) {
                    throw "Multiple operators in the row";
                }
            }
        }
    }

    void toPostfix() {
        Parse();
        Stack<char> st;
        char stackItem;
        for (char item : lexems) {
            switch (item) {
                case '(':
                    st.Push(item);
                    break;
                case ')':
                    stackItem = st.pop();
                    while (stackItem != '(') {
                        postfix += stackItem;
                        if (!st.empty()) {
                            stackItem = st.pop();
                        } else {
                            throw "No opening paranthesis in expression";
                        }
                    }
                    break;
                case '+': case '-': case '*': case '/': case '%':
                    while (!st.empty() && priority[item] <= priority[st.top()] && st.top() != '(') {
                        stackItem = st.pop();
                        postfix += stackItem;
                    }
                    st.Push(item);
                    break;
                default:
                    postfix += item;
            }
        }
        while (!st.empty()) {
            stackItem = st.pop();
            if (stackItem == '(') {
                throw "No end paranthesis in expression";
            }
            postfix += stackItem;
        }
    }

    string GetInfix() const {
        return infix;
    }

    string GetPostfix() const {
        return postfix;
    }

    double Calculate() {
        Stack<double> st;
        double leftOper, rightOper;
        for (char lexem : postfix) {
            if (isdigit(lexem)) {
                st.Push(lexem - '0');
            } else {
            switch (lexem) {
                case '+':
                    rightOper = st.pop();
                    leftOper = st.pop();
                    st.Push(leftOper + rightOper);
                    break;
                case '-':
                    rightOper = st.pop();
                    leftOper = st.pop();
                    st.Push(leftOper - rightOper);
                    break;
                case '*':
                    rightOper = st.pop();
                    leftOper = st.pop();
                    st.Push(leftOper * rightOper);
                    break;
                case '/':
                    rightOper = st.pop();
                    leftOper = st.pop();
                    if (rightOper == 0) {
                        throw "Division by zero";
                    }
                    st.Push(leftOper / rightOper);
                    break;
                case '%':
                    rightOper = st.pop();
                    leftOper = st.pop();
                    st.Push(fmod(leftOper, rightOper));
                    break;
            }
            }
        }
        return st.pop();
    }
};

#endif
