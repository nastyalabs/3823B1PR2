/* #include <string>
#include <sstream>
#include "antlr4-runtime.h"
#include "mygrammarBaseVisitor.h"
#include "mygrammarLexer.h"
#include "mygrammarParser.h"
#include "mygrammarVisitor.h"
#include "myvisitors.h"

class Antlr4_Tests {

	size_t num_of_test = 1;

public:

	void test1(std::string sent, double valid_result) {
		std::stringstream stream(sent);
		antlr4::ANTLRInputStream input(stream);
		mygrammarLexer lexer(&input);
		antlr4::CommonTokenStream tokens(&lexer);
		mygrammarParser parser(&tokens);
		MyVisitor visitor;
		visitor.visit(parser.prog());
		if (valid_result == visitor.data["result"]) {
			std::cout << "[TEST " << num_of_test++ << "]" << " SUCCEED" << std::endl;
		}
		else {
			std::cout << "[TEST " << num_of_test++ << "]" << " WRONG" << "\n\t because "<< valid_result<<" and "<<
				visitor.data["result"]<<" not equal" << std::endl;
		}
	}

	void test2(std::string sent, std::string var, double valid_res) {
		std::stringstream stream(sent);
		antlr4::ANTLRInputStream input(stream);
		mygrammarLexer lexer(&input);
		antlr4::CommonTokenStream tokens(&lexer);
		mygrammarParser parser(&tokens);
		MyVisitor visitor;
		visitor.visit(parser.prog());
		if (valid_res == visitor.data[var]) {
			std::cout << "[TEST " << num_of_test++ << "]" << " SUCCEED" << std::endl;
		}
		else {
			std::cout << "[TEST " << num_of_test++ << "]" << " WRONG" << "\n\t because " << valid_res << " and " <<
				visitor.data["result"] << " not equal" << std::endl;
		}
	}
};

int main() {
	Antlr4_Tests tst;

	tst.test1("1 + 4;", 5);
	tst.test1("2*3 + 12 + 5*2;", 28);
	tst.test1("1.2/2 + 0.4;", 1);
	tst.test1("(1+3)*0.5 - 2;", 0);
	tst.test1("1 - 1 + 1 - 1;", 0);
	tst.test1("a = 5;", 5);
	tst.test1("a = 7 * 4;", 28);
	tst.test1("a = 5*8 / 40;", 1);
	tst.test1("(1+1)-(3*4-1)+(5-5)*(80+100);", -9);
	tst.test1("1 / 1 / 1 * 10000;", 10000);

	std::cout << std::endl;

	tst.test2("a = 10;", "a", 10);
	tst.test2("a=10;b=10*a;", "a", 10);
	tst.test2("a=10;b=10*a;", "b", 100);
	tst.test2("a=10;b = 10 - a; c = 10 + b;", "c", 10);
	tst.test2("a=2;b=4;c=6;f=a+b-c;", "f", 0);
	tst.test2("a=2;b=4;c=6;f=a+b-c;<<f;", "f", 0);

	return 0;
} */