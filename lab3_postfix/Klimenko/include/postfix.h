#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include "stack.h"
#include "vector"
#include "string.h"
#include <map>

using namespace std;

class TArithmeticExpression {
	string infix;
	string postfix;
	vector<char> lexems;
	map<char, int> priority;
	map<char, double> operands;

	void parse() {
		for (char c : infix) {
			lexems.push_back(c);
		}
	}

	void toPostfix() {
		parse();
		TDynamicStack<char> st;
		char stackItem;
		int openBrackets = 0;
		for (char item : lexems) {
			switch (item) {
			case '(':
				st.push(item);
				openBrackets++;
				break;
			case ')':
				if (openBrackets == 0) {
					throw std::runtime_error("No closing brackets found!");
				}
				stackItem = st.pop();
				while (stackItem != '(') {
					postfix += stackItem;
					stackItem = st.pop();
				}
				openBrackets--;
				break;
			case '+': case '-': case '*': case '/':
				while (!st.isEmpty()) {
					stackItem = st.pop();
					if (priority[item] <= priority[stackItem]) {
						postfix += stackItem;
					}
					else {
						st.push(stackItem);
						break;
					}
				}
				st.push(item);
				break;
			default:
				operands.insert({ item, 0.0 });
				postfix += item;
			}
		}

		if (openBrackets != 0) {
			throw std::runtime_error("No closing brackets found!");
		}

		while (!st.isEmpty()) {
			stackItem = st.pop();
			postfix += stackItem;
		}
	}

public:
	TArithmeticExpression(string infx) {
		infix = infx;
		priority = { {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2} };
		toPostfix();
	}

	string getInfix() const {
		return infix;
	}

	string getPostfix() const {
		return postfix;
	}

	vector<char> getOperands() const {
		vector<char> op;
		for (const auto& item : operands) {
			op.push_back(item.first);
		}
		return op;
	}

	double calculate(const map<char, double>& values) {
		for (auto& val : values) {
			try {
				operands[val.first] = val.second;
			}
			catch (out_of_range) {}
		}
		TDynamicStack<double> st;
		double leftOperand, rightOperand;

		for (char lexem : postfix) {
			switch (lexem) {
			case '+':
				rightOperand = st.pop();
				leftOperand = st.pop();
				st.push(leftOperand + rightOperand);
				break;
			case '-':
				rightOperand = st.pop();
				leftOperand = st.pop();
				st.push(leftOperand - rightOperand);
				break;
			case '*':
				rightOperand = st.pop();
				leftOperand = st.pop();
				st.push(leftOperand * rightOperand);
				break;
			case '/':
				rightOperand = st.pop();
				leftOperand = st.pop();
				if (rightOperand == 0) {
					throw std::invalid_argument("Division by zero");
				}
				st.push(leftOperand / rightOperand);
				break;
			default:
				st.push(operands[lexem]);
			}
		}
		if (st.size() != 1) {
			throw std::logic_error("Invalid expression");
		}
		return st.pop();
	}
};

#endif
