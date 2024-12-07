#ifndef POSTFIX_H
#define POSTFIX_H

#include <string>
#include "stack.h"
#include <vector>

using namespace std;

class Calculator {
    Stack<char> op;
    Stack<double> num;
    string exp;
    int cnt = 0;

public:
    Calculator(string expr) : exp(expr), cnt(0) {
        
    }

    void run(char s) {
        double a = num.Pop();
        double a1;
        int res = 1;
        switch (s) {
        case '+':
            a1 = num.Pop();
            num.Push(a + a1);
            break;
        case '-':
            a1 = num.Pop();
            num.Push(a1 - a);
            break;
        case '*':
            a1 = num.Pop();
            num.Push(a * a1);
            break;
        case '/':
            a1 = num.Pop();
            if (a == 0) throw ("Division by zero");
            num.Push(a1 / a);
            break;
        case '^':
            a1 = num.Pop();
            for (int i = 0; i < a; i++) res = res * a1;
            num.Push(res);
            break;
        }
    }

    bool brackets() {
        int i1 = 0;
        int cnt1 = 0;
        Stack<char> br;
        while (i1 < exp.length()) {
            if (exp[i1] == '(') {
                br.Push('(');
            }
            else if (exp[i1] == ')') {
                if (br.empty()){
                    cout << "fix closing brackets";
                    return false;
                }
                br.Pop();
            }
            i1++;
        }
        if (!br.empty()) cout << "fix opening brackets";
        return br.empty();
    }

    void rev_polish_not() {
        int i = 0;
        
        if (!brackets()) {
            throw("fix your brackets");
        }
        else {
            while (i < exp.length()) {
                char s = exp[i];
                if (s == '+' || s == '-' || s == '*' || s == '/') {
                    check_priority(s);
                    op.Push(s);
                }
                else if (s >= '0' && s <= '9') {
                    num.Push(s - '0');
                }
                else if (s == '^') {
                    op.Push(s);
                }
                else if (s == '(') {
                    op.Push(s);
                    cnt++;
                }
                else if (s == ')') {
                    check_priority(s);
                    cnt--;
                }
                else {
                    throw "error";
                }
                i++;
            }
        }
    }

    double exec() {
        rev_polish_not();
        while (!op.empty()) {
            char my = op.Pop();
            run(my);
        }
        return num.Pop();
    }

    
	void check_priority(char s) {
        
		if (s == ')') {
            if (cnt == 0) {
                throw ("No opening bracket");
            }
			while (op.Top() != '(') run(op.Pop());
			op.Pop();//no more skobka (
		}
        else {
            while ((op.Top() != '(') || (op.Top() != '\0')) {
                if ((op.Top() == '*') || (op.Top() == '/') || (op.Top() == '^')) run(op.Pop());
                else break;  
            }
        }
	}
};

#endif 

