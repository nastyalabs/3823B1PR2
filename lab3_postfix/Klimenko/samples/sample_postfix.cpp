#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main()
{
	string exprStr;
	cout << "Enter expression: ";
	cin >> exprStr;

	TArithmeticExpression expr(exprStr);
	cout << expr.getInfix() << endl;
	cout << expr.getPostfix() << endl;
	vector<char> operands = expr.getOperands();

	map<char, double> values;

	for (const auto& op : operands) {
		if (isdigit(op)) {
			double val = op - '0'; 
			values[op] = val;
		}
		else {
			cout << "Enter value of " << op << ": ";
			double val;
			cin >> val;
			values[op] = val;
		}
	}
	cout << expr.calculate(values) << endl;
}