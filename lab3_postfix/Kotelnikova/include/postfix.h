#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include "stack.h"
#include "vector"
#include "string.h"

using namespace std;

class Calc {
	Stack<char> operators;
	Stack<double> chisla;
	string vyrazenie;
	
public:
	Calc(string vyr) {
		operators = Stack<char>{};
		chisla = Stack<double>{};
		vyrazenie = vyr;
	}

    bool isdigit(char ch) { return ch >= '0' && ch <= '9'; }
    bool isopera(char ch) { return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^'; }
    bool isfunct(char ch) { return ch == 's' || ch == 'c' || ch == 't' || ch == 'l'; }

    int prio(char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/' || op == '^') return 2;
        return 0;
    }

    double execute() {
        int i = 0;
        while (i < vyrazenie.size()) {
            char now = vyrazenie[i];

            if (isdigit(now)) {
                chisla.Push(now - '0');
            }
            else if (isopera(now)) {
                processprio(now);
                operators.Push(now);
            }
            else if (isfunct(now)) {
                operators.Push(now);
            }
            else if (now == '(') {
                operators.Push(now);
            }
            else if (now == ')') {
                scobki();
            }

            i++;
        }

        while (!operators.empty()) {
            operationsrealization(operators.pop());
        }

        return chisla.pop();
    }

    void processprio(char op) {
        while (!operators.empty() && prio(operators.top()) >= prio(op)) {
            operationsrealization(operators.pop());
        }
    }

    void scobki() {
        while (!operators.empty() && operators.top() != '(') {
            operationsrealization(operators.pop());
        }

        if (!operators.empty())
            operators.pop();

        if (!operators.empty() && isfunct(operators.top()))
            operationsrealization(operators.pop());
    }

    void operationsrealization(char op) {
        double a = chisla.pop();
        double b;

        switch (op) {
        case '+':
            b = chisla.pop();
            chisla.Push(b + a);
            break;
        case '-':
            b = chisla.pop();
            chisla.Push(b - a);
            break;
        case '*':
            b = chisla.pop();
            chisla.Push(b * a);
            break;
        case '/':
            b = chisla.pop();
            chisla.Push(b / a);
            break;
        case '^':
            b = chisla.pop();
            chisla.Push(pow(b, a));
            break;
        case 's':
            chisla.Push(sin(a));
            break;
        case 'c':
            chisla.Push(cos(a));
            break;
        case 't':
            chisla.Push(tan(a));
            break;
        case 'l':
            chisla.Push(log(a));
            break;
        default:
            break;
        }
    }
	
};
#endif
