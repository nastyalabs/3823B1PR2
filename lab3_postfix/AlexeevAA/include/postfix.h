#ifndef __POSTFIX_H__
#define __POSTFIX_H__
#include<deque>
#include <string>
#include "stack.h"
#include "vector"
#include "string.h"

using std::string;

class Calc{
private:
    string input;
    Stack<string> operators;
    std::vector<string> vcalc;
public: 
    Calc(string s):input(s){}
    string postfixed(){
        string s = "";
        for(std::string::iterator i = input.begin(); i != input.end(); i++){
            switch(*i){

                case '(':
                    operators.Push("(");
                    break;

                case ')':
                    if(s != ""){
                        vcalc.push_back(s);
                        s = "";
                    }
                    while(!operators.empty()){
                        if(operators.top() != "("){
                            vcalc.push_back(operators.pop());
                        }
                        else break;
                    }
                    if(!operators.empty()){
                        operators.pop();
                        break;
                    }
                    else throw string("error x)");

                case '+':
                    if(s != ""){
                        vcalc.push_back(s);
                        s = "";
                    }
                    while(!operators.empty()){
                        if(operators.top() == "*" || operators.top() == "/" || operators.top() == "+" || operators.top() == "-")
                            vcalc.push_back(operators.pop());
                        else break;
                    }
                    operators.Push("+");
                    break;

                case '-':
                    if(s != ""){
                        vcalc.push_back(s);
                        s = "";
                    }
                    while(!operators.empty()){
                        if(operators.top() == "*" || operators.top() == "/" || operators.top() == "+" || operators.top() == "-")
                            vcalc.push_back(operators.pop());
                        else break;
                    }
                    operators.Push("-");
                    break;
                case '*':
                    if(s != ""){
                        vcalc.push_back(s);
                        s = "";
                    }
                    while(!operators.empty()){
                        if(operators.top() == "*" || operators.top() == "/")
                            vcalc.push_back(operators.pop());
                        else break;
                    }
                    operators.Push("*");
                    break;

                case '/':
                    if(s != ""){
                        vcalc.push_back(s);
                        s = "";
                    }
                    while(!operators.empty()){
                        if(operators.top() == "*" || operators.top() == "/")
                            vcalc.push_back(operators.pop());
                        else break;
                    }
                    operators.Push("/");
                    break;
                case ' ':
                    break;
                default:
                    if(*i - '0' < 10 && *i - '0' >= 0){
                        s += *i;
                        break;
                    }
                    else throw string("error not number");
            }
        }
        if(s != "") 
            vcalc.push_back(s);
        while(!operators.empty()) vcalc.push_back(operators.pop());

        for(string i: vcalc)
            if(i == "(") throw string("error (x");

        string ans("");
        for(auto i: vcalc) ans += i + " ";
        return ans;
    }
    double calculate(){
        Stack<double>ans;

        for(auto i:vcalc){
            if(i != "+" && i != "-" && i != "*" && i != "/")
                ans.Push(std::stod(i));
            else{
                double y = ans.pop();
                double x = ans.pop();
                if(i == "+"){
                    x = x + y;
                    ans.Push(x);
                }
                if(i == "-"){
                    x = x - y;
                    ans.Push(x);
                }
                if(i == "/"){
                    x = x / y;
                    ans.Push(x);
                }
                if(i == "*"){
                    x = x * y;
                    ans.Push(x);
                }
            }
        }
        return ans.pop();
    }

};
/*
class CalcSec{
private:
    string input;
    Stack<char> operators;
    std::vector<char> vcalc;
public: 
    CalcSec(string s):input(s){}
    string postfixed(){
        for(std::string::iterator i = input.begin(); i != input.end(); i++){
            switch(*i){
                case '(':
                    operators.Push('(');
                    break;
                case ')':
                    while(operators.top() != '(') vcalc.push_back(operators.pop());
                    operators.pop();
                    break;
                case '+':
                    while(!operators.empty())
                        if(operators.top() == '*' || operators.top() == '/' || operators.top() == '+' || operators.top() == '-')
                            vcalc.push_back(operators.pop());
                        else break;
                    operators.Push('+');
                    break;
                case '-':
                    while(!operators.empty())
                        if(operators.top() == '*' || operators.top() == '/' || operators.top() == '+' || operators.top() == '-')
                            vcalc.push_back(operators.pop());
                        else break;
                        operators.Push('-');
                    break;
                case '*':
                    while(!operators.empty())
                        if(operators.top() == '*' || operators.top() == '/')
                            vcalc.push_back(operators.pop());
                        else break;
                    operators.Push('*');
                    break;
                case '/':
                    while(!operators.empty())
                        if(operators.top() == '*' || operators.top() == '/')
                            vcalc.push_back(operators.pop());
                        else break;
                    operators.Push('/');
                    break;
                case ' ':
                    break;
                default:
                    vcalc.push_back(*i);
                    break;
            }
        }
        while(!operators.empty()) vcalc.push_back(operators.pop());

        string ans("");
        for(auto i: vcalc) ans += i;
        return ans;
    }
    int calculate(){
        Stack<int>ans;

        for(auto i:vcalc){
            if(std::isdigit(i))
                ans.Push(i - '0');
            else{
                int y = ans.pop();
                int x = ans.pop();

                switch(i){
                    case '+':
                        x = x + y;
                        ans.Push(x);
                        break;
                    case '-':
                        x = x - y;
                        ans.Push(x);
                        break;
                    case '*':
                        x = x * y;
                        ans.Push(x);
                        break;
                    case '/':
                        x = x / y;
                        ans.Push(x);
                        break;
                }
            }
        }
        return ans.pop();
    }

};
*/
#endif