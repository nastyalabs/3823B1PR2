#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main()
{
	string exprStr;
	cout << "Вставьте выражение: ";
	cin >> exprStr;
	try {
		TArithmeticExpression expr(exprStr);
		cout << expr.GetInfix() << " - infix" << endl;
		cout << expr.GetPostfix() << " - postfix" << endl;
		cout << endl << expr.Calculate() << endl;
	}
	catch (const char* err) {
		cout << "Exception: " << err << endl;
	}
}
