#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main()
{
	// *
	// /
	// +
	// -
	// s() - sin
	// c() - cos
	// t() - tg
	// l() - lg
	// ^ - возведение в степень
	// (    ) - скобки
	// числа вводится могут однозначные
	// 
	// вова
	//  
	//Calc a("1+2*3-1*8/2+1-1");
	//Calc a("4*4*(4-4+(8^3/7*3*(6*2)^2))");
	//Calc a("(8/7)^(1+1)");
	//Calc a("l(l(3))");
	Calc a("6+9*5/(5/2)");
	//Calc a("2*s(0)");
	cout << a.work();
	return 0;
}