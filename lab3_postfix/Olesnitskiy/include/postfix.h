#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include "stack.h"
#include "vector"
#include "string.h"

using namespace std;

class Calc
{
	Stack <char> oper;
	Stack <double> number;
	string example;
	int counter;
public:

	Calc(string ex) :counter(0)
	{
		oper = Stack <char>{};
		number = Stack <double>{};
		example = ex;
	}

	double work()
	{
		size_t i = 0;
		while (example[i] != '\0')
		{
			char s = example[i];
			if (s == '(')
			{
				oper.push(s);
				counter++;
			}
			if (s == ')')
			{
				proverka(s);
				counter--;
			}

			if (s == '^' || (s == 's') || (s == 'c') || (s == 't') || (s == 'l'))
			{
				oper.push(s);
			}

			if ((s == '+') || (s == '-') || (s == '*') || (s == '/'))
			{
				proverka(s);
				oper.push(s);
			}

			if ((s >= '0') && (s <= '9'))
			{
				number.push(s - '0');
			}
			i++;
		}
		char s = oper.pop();
		while (s != '\0')
		{
			doing(s);
			s = oper.pop();
		}
		return number.pop();
	}

	void proverka(char a)
	{
		if (a == ')')
		{
			if (counter = 0) cout << "Error.";
			while (oper.top() != '(')
				doing(oper.pop());
			oper.pop();							//стёрли '('
			if (oper.top() == 's' || oper.top() == 'c' || oper.top() == 't' || oper.top() == 'l')
				doing(oper.pop());

		}
		else
		{
			while ((oper.top() != '\0') || (oper.top() != '('))
			{
				if ((a == '+') || (a == '-') || (a == 's') || (a == 'c') || (a == 't') || (a == 'l'))
				{
					if ((oper.top() == '*') || (oper.top() == '/') || (oper.top() == '+') || (oper.top() == '-') || (oper.top() == '^')) doing(oper.pop());
					else break;
				}
				if ((a == '*') || (a == '/'))
				{
					if ((oper.top() == '*') || (oper.top() == '/') || (oper.top() == '^')) doing(oper.pop());
					else break;
				}
			}
		}

	}

	void doing(char simbol)
	{
		double a = number.pop();
		double b;
		double my = 1;
		switch (simbol)
		{
		case '+':	b = number.pop(); number.push(b + a); break;
		case '-':	b = number.pop(); number.push(b - a); break;
		case '/':	b = number.pop(); number.push(b / a); break;
		case '*':	b = number.pop(); number.push(a * b); break;
		case '^':	b = number.pop(); for (int i = 0; i < a; i++) my = my * b; number.push(my); break;
		case 's':	number.push(sin(a)); break;
		case 'c':	number.push(cos(a)); break;
		case 't':	number.push(tan(a)); break;
		case 'l':	number.push(log(a)); break;
		}

	}
};
#endif