#include <iostream>
#include <string>
#include "postfix.h"
#include "stack.h"
using namespace std;

int main()
{
	Calculator myexp("(1+(5*4))/3");
	Calculator myexp2("3*2+)(4/7)+2^2");

	cout << myexp.exec() << "  " << myexp2.exec();
	return 0;
}