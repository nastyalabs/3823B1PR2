#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include "stack.h"
#include "vector"
#include "string.h"
#include <map>
#include<cmath>

using namespace std;

// class TArithmeticExpression {
//     string infix;
//     string postfix;

//     int Priority(char op) {
//         if (op == '+' || op == '-') {
//             return 1;
//         }
//         if (op == '*' || op == '/') {
//             return 2;
//         }
//         return -1; // некорректный оператор
//     }

//     bool isOperation(char sym) {
//         return sym == '+' || sym == '-' || sym == '*' || sym == '/';
//     }

//     // double Calculate() {

//     // }

// public:
//     TArithmeticExpression (string _infix) : infix(_infix) { }

//     void ToPostfix() {
//         Stack<char> opS;

//         for (size_t i = 0; i < infix.length(); i++) {
//             char sym = infix[i];

//             if (isspace(sym)) {
//                 continue;
//             }

//             if(isdigit(sym)) {
//                 postfix += sym;
//             } else if (sym == '(') {
//                 opS.Push(sym);
//             } else if(isOperation(sym)) {
//                 while (Priority(sym) <= Priority(opS.top()) && !opS.empty()) {
//                     postfix += opS.pop();
//                 }
//                 opS.Push(sym);
//             } else if(sym == ')') {
//                 while (opS.top() != '(') {
//                     postfix += opS.pop();
//                 }
//                 opS.pop();
//             }
//         }

//         while (!opS.empty()) {
//             postfix += opS.pop();
//         }
//     }

//     string getPostfix() const {
//         return postfix;
//     }

//     string getInfix() const {
//         return infix;
//     }
// };


class TArithmeticExpression {
    string infix;
    string postfix;
    vector<char> lexems;
    map<char, int> priority;

    void Parse() {
        for (char c : infix) {
            lexems.push_back(c);
        }
    }

    void ToPostfix() {
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
                            throw ("Opening paranthesis is not found");
                        }
                    }
                    break;
                case '+': case '-': case '*': case '/':
                    while (!st.empty()) {
                        stackItem = st.pop();
                        if (priority[item] <= priority[stackItem]) {
                            postfix += stackItem;
                        } else {
                            st.Push(stackItem);
                            break;
                        }
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
                throw ("')' is not found");
            }
            postfix += stackItem;
        }
    };

public:
    TArithmeticExpression(string _infix) : infix(_infix) {
        priority = { {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}};
        ToPostfix();
    }

    string getPostfix() const {
        return postfix;
    }

    string getInfix() const {
        return infix;
    }

    // vector<char> GetOperands() const {
    //     vector<char> op;
    //     for (const auto& item : operands) {
    //         op.push_back(item.first);
    //     }
    //     return op;
    // }

    double Calculate() {
        Stack<double> st;
        double leftOperand, rightOperand;
        for (char lexem : postfix) {
            if (isdigit(lexem)) {
                st.Push(lexem - '0');
            } else {
                switch (lexem) {
                    case '+':
                        rightOperand = st.pop();
                        leftOperand = st.pop();
                        st.Push(leftOperand + rightOperand);
                        break;
                    case '-':
                        rightOperand = st.pop();
                        leftOperand = st.pop();
                        st.Push(leftOperand - rightOperand);
                        break;
                    case '*':
                        rightOperand = st.pop();
                        leftOperand = st.pop();
                        st.Push(leftOperand * rightOperand);
                        break;
                    case '/':
                        rightOperand = st.pop();
                        if (rightOperand == 0) {
                            throw ("Div on zero");
                        }
                        leftOperand = st.pop();
                        st.Push(leftOperand / rightOperand);
                        break;
                }
            }
        }
        return st.pop();
    }
};

#endif
