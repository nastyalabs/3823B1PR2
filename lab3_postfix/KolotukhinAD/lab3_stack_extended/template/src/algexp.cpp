#include "algexp.h"
#include <stdlib.h>
#include <sstream>
#include <math.h>

#define PI 3.14159265

algexp::algexp() : expression("0") {}

size_t getPriority(string _lexeme) {
    if (_lexeme == "+" || _lexeme == "-") return 1;
    if (_lexeme == "*" || _lexeme == "/") return 2;
    if (_lexeme == "sin" || _lexeme == "cos" || _lexeme == "tan" || _lexeme == "sqrt") return 3;
    return 0;
}

bool isOperator(string c) {
    return c == "+" || c == "-" || c == "*" || c == "/";
}

bool isfunction(string c) {
    return c == "sin" || c == "cos" || c == "tan" || c == "sqrt";
}

algexp::algexp(string expr) {
    stack<string> operators(expr.length());
    istringstream lexemes(expr); // ∫ 4 5 f(x)dx
    string lexeme;
    while (lexemes >> lexeme) {
        if (isdigit(lexeme[0])) {
            expression += (lexeme + " ");
        } else if (isOperator(lexeme) || isfunction(lexeme)) {
            while (!operators.isEmpty() && getPriority(operators.top()) >= getPriority(lexeme)) {
                expression += (operators.top() + " ");
                operators.pop();
            }
            operators.push(lexeme);
        } else if (lexeme == "(") {
            operators.push(lexeme);
        } else if (lexeme == ")") {
            while (!operators.isEmpty() && operators.top() != "(") {
                expression += (operators.top() + " ");
                operators.pop();
            }
            operators.pop();
        }
    }

    while (!operators.isEmpty()) {
        expression += (operators.top() + " ");
        operators.pop();
    }
}

algexp::algexp(const algexp& _other) {
    expression = _other.expression;
}

string algexp::getExpr() {
    return expression;
}

bool isCorrect(string expression) {
    istringstream lexemes(expression);
    string lexeme;
    int countOperations = 0;
    int countOperands = 0;
    while (lexemes >> lexeme) {
        if (isdigit(lexeme[0])) {
            countOperands++;
        } else if (isOperator(lexeme)) {
            countOperations++;
        }
    }
    if (countOperands - countOperations == 1) {
        return true;
    }
    return false;
}

double algexp::solveIt() const {
    if (!isCorrect(expression)) {
        throw invalid_argument("[INCORRECT EXPR] not enough operands");
    }
    istringstream lexemes(expression);
    string lexeme;
    stack<string> save(expression.length());
    while (lexemes >> lexeme) {
        if (isdigit(lexeme[0])) {
            save.push(lexeme);
        } else {
            double res;
            double second_arg;
            double first_arg  = stod(save.top()); save.pop();
                if (lexeme == "+") {
                    second_arg = stod(save.top()); save.pop();
                    res = first_arg + second_arg;
            } else if (lexeme == "-") {
                    second_arg = stod(save.top()); save.pop();
                    res = second_arg - first_arg;
            } else if (lexeme == "*") {
                    second_arg = stod(save.top()); save.pop();
                    res = first_arg * second_arg;
            } else if (lexeme == "/") {
                    second_arg = stod(save.top()); save.pop();
                    if (first_arg == 0) {
                        throw invalid_argument("[INCORRECT ARG] division by zero");
                    }
                    res = second_arg / first_arg;
            } else if (lexeme == "sin") {
                    res = sin(first_arg * PI / 180);
            } else if (lexeme == "cos") {
                    res = cos(first_arg * PI / 180);
            } else if (lexeme == "tan") {
                    res = tan(first_arg * PI / 180);
            } else if (lexeme == "sqrt") {
                    res = sqrt(first_arg);
            }
            save.push(to_string(res));
        }
    }
    return stod(save.top());
}

algexp algexp::operator=(const algexp& _other) {
    algexp res(_other);
    return res;
}

ostream& operator<<(ostream& ostr, const algexp& _algexp) {
    ostr << _algexp.expression;
    return ostr;
}

bool algexp::operator==(const algexp& _other) const {
    if (isCorrect(this->expression) && isCorrect(_other.expression)) {
        return this->solveIt() == _other.solveIt();
    }
    return false;
}