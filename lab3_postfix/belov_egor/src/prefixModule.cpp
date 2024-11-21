// ННГУ, ВМК, Курс "Алгоритмы и структуры данных", С++, ООП
//
// prefixModule.h - Copyright (c) Белов Е.А.
//
// Модуль работы с арифметическими операциями

#include "prefixModule.h"

PrefixModule::PrefixModule(normalArith str) {
    Stack<OperationChar> operators = Stack<OperationChar>();
    OperationChar temp;
    nArith = str;
    pArith = "";
    char current;
    for (size_t i = 0; i < str.length(); i++) {
        current = str[i];
        if (current == ' ') { continue; }
        if (current >= '0' && current <= '9') {
            pArith += current;
            
            calculator.push((double)(current - '0'));
        }
        else {
            temp = OperationChar(current);
            if (temp.get_priority() != 0) {
                while (!operators.isEmpty() && operators.top() > temp) {
                    pArith += operators.top().get_char();
                    calculator.push(operators.top());
                    operators.pop();
                }
                operators.push(temp);
            }
            else {
                if (current == '(') {
                    operators.push(temp);
                }
                else {
                    while (operators.top() != temp) {
                        pArith += operators.top().get_char();
                        calculator.push(operators.top());
                        operators.pop();
                    }
                    operators.pop();
                }
            }
        }
    }
    while (!operators.isEmpty()) {
        pArith += operators.top().get_char();
        calculator.push(operators.top());
        operators.pop();
    }
    
    calculator.toCalculate();
}


double PrefixModule::step_push() {
    if (calculator.getInfo() == num) { return *((double*)calculator.get()); }
    
    double res;
    
    OperationChar temp = *((OperationChar*)calculator.get());
    if (calculator.getInfo() == operation) {
        calculator.pop();
        double num1 = *((double*)calculator.get());
        calculator.pop();
        res = *(double*)calculator.get() = temp.exec(*(double*)calculator.get(), num1);
    }
    else if (calculator.getInfo() == function) {
        calculator.pop();
        res = *(double*)calculator.get() = temp.exec(*(double*)calculator.get());
    }
    else {
        throw "lol";
    }
    
    calculator.toNextOp();
    return res;
}

double PrefixModule::calculate() {
    while (calculator.getInfo() != num) {
        step_push();
    }
    return step_push();
}
