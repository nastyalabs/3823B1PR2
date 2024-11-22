#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main()
{
	Calc vyr1("((1+5-3)*2)/6+5^2");
	cout << vyr1.execute() << endl;   // = 26

	Calc vyr2("l(1)");
	cout << vyr2.execute() << endl;   // = 0

	Calc vyr3("((1+5*t(0)-3)*2+sin(0))/6+5^2-cos(0)");
	cout << vyr3.execute() << endl;   // ~23.3
	
}