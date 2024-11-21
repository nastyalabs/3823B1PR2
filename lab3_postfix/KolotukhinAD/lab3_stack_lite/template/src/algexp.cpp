#include "algexp.h"
#include <stdlib.h>

algexp::algexp() {}

unsigned char getPriority(char _lexeme) {
    if (_lexeme == '+' || _lexeme == '-') {
        return 1;
    } else if (_lexeme == '*' || _lexeme == '/'){
        return 2;
    }
    return 0;
}

algexp::algexp(string expr) {
    stack<char> save(expr.length());
    for (char lexeme : expr) {
        if (isdigit(lexeme)) {
            expression += lexeme;
        } else if (lexeme == '(') {
            save.push(lexeme);
        } else if (lexeme == ')') {
            while (save.top() != '(') {
                expression += save.top();
                save.pop();
            }
            save.pop();
        } else if (lexeme == '+' || lexeme == '-' || lexeme == '*' || lexeme == '/') {
            while (!save.isEmpty() && getPriority(lexeme) <= getPriority(save.top())) {
                expression += save.top();
                save.pop();
            }
            save.push(lexeme);
        }
    }
    while (!save.isEmpty()) {
        expression += save.top();
        save.pop();
    }
}

algexp::algexp(const algexp& _other) {
    expression = _other.expression;
}

string algexp::getExpr() {
    return expression;
}

bool isCorrect(string expression) {
    int countOperations = 0;
    int countOperands = 0;
    for (char lexeme : expression) {
        if (isdigit(lexeme)) {
            countOperands++;
        } else {
            countOperations++;
        }
    }
    if (countOperands - countOperations == 1) {
        return true;
    }
    return false;
}

int algexp::solveIt() const {
    if (!isCorrect(expression)) {
        throw invalid_argument("[INCORRECT EXPR] not enough operands");
    }
    stack<char> save(expression.length());
    for (char lexeme : expression) {
        if (isdigit(lexeme)) {
            save.push(lexeme - '0');
        } else {
            int res;
            int second_arg = save.top(); save.pop();
            int first_arg = save.top(); save.pop();
            switch(lexeme) {
                case '+':
                    res = first_arg + second_arg;
                    break;
                case '-':
                    res = first_arg - second_arg;
                    break;
                case '*':
                    res = first_arg * second_arg;
                    break;
                case '/':
                    if (second_arg == 0) {
                        throw invalid_argument("[INCORRECT ARG] division by zero");
                    }
                    res = first_arg / second_arg;
                    break;
            }
            save.push(res);
        }
    }
    return save.top();
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