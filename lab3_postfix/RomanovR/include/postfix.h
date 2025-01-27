#ifndef POSTFIX_H 
#define POSTFIX_H 
 
#include <string> 
#include "stack.h" 
#include "string.h" 
 
using namespace std; 
 
class Calc{ 
 
    Stack <char> oper; 
    Stack <double> num; 
    string exp; 
    int brackets; 
 
    public: 
 
    Calc(string _exp) : exp(_exp), brackets(0){} 
 
    double work(){ 
        size_t i = 0; 
            while(exp[i] != '\0'){ 
                char s = exp[i]; 
                 switch(s){ 
                    case '(': oper.push(s); brackets++; break; 
                    case ')': proverka(s); brackets--; break; 
                    case '+': proverka(s); oper.push(s); break; 
                    case '-': proverka(s); oper.push(s); break; 
                    case '*': proverka(s); oper.push(s); break; 
                    case '/': proverka(s); oper.push(s); break; 
                    default : break; 
                } 
                if((s >= '0') && (s <= '9')) {num.push(s - '0');} 
                i++; 
        } 
        char s = oper.pop(); 
        while (s != '\0'){ 
            run(s); 
            s = oper.pop(); 
        } 
        return num.pop(); 
    } 
 
    void proverka(char a){ 
         
        if(a == ')'){ 
            if(brackets == 0){ 
                throw -1; 
            } 
            while(oper.top() != '('){ 
                run(oper.pop()); 
            } 
            oper.pop(); 
        } 
        else{ 
            while((oper.top() != '\0') && (oper.top() != '(')){ 
                if ((a == '-') || (a == '+')){ 
                    if((oper.top() == '*') || (oper.top() == '/') || (oper.top() == '+') || (oper.top() == '-')){ 
                        run(oper.pop()); 
                    } 
                    else break; 
                } 
                if((a == '*') || (a == '/')){ 
                    if((oper.top() == '*') || (oper.top() == '/')){ 
                        run(oper.pop()); 
                    } 
                    else break; 
                } 
            } 
        } 
 
    } 
 
    void run(char op){ 
        double a = num.pop(); 
        double b; 
        switch(op){ 
            case '+': 
                b = num.pop(); 
                num.push(b + a); 
                break; 
            case '-': 
                b = num.pop(); 
                num.push(b - a); 
                break; 
            case '*': 
                b = num.pop(); 
                num.push(b * a); 
                break; 
            case '/': 
                b = num.pop(); 
                num.push(b / a); 
                break; 
        } 
    } 
 
}; 
 
#endif