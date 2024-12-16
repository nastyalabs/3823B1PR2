#include <iostream>
#include <string>
#include "list.h"
#include "polynomials.h"

using namespace std;

int main()
{
	Polynomial p1;
	Polynomial p2;
	try {
		p1.add_term(2, "101");  // 2xz
		p1.add_term(-4, "200");  // -4x^2
		p1.add_term(5, "000");  // 5

		p2.add_term(6, "101");  // 6xz
		p2.add_term(1, "201");  // x^2z
		p2.add_term(-3, "030");  // -3y^3

		Polynomial sum = p1 + p2;
		cout << "Sum: " << sum;

		Polynomial mult = p1 * p2;
		cout << "Mult: " << mult;

		Polynomial sub = p1 - p2;
		cout << "Sub: " << sub;
		
		cout << "Значение выражения mult в точке (3, 0, 2): " << mult.evaluate(3, 0, 2) << endl;
	}
	catch (const char* err) {
		cout << "Exception: " << err << endl;
	}
}
