#include "postfix.h"
#include <gtest.h>

TEST(TArithmeticExpression, cant_calculate_an_expression_without_the_second_value) {
	string exprStr = "A*";
	TArithmeticExpression expr(exprStr);
	vector<char> operands = expr.getOperands();
	map<char, double> values;
	for (const auto& op : operands) {
		values[0] = 1;
	}
	ASSERT_ANY_THROW(expr.calculate(values));
}

TEST(TArithmeticExpression, cant_calculate_the_empty_expression) {
	string exprStr = "";
	TArithmeticExpression expr(exprStr);
	vector<char> operands = expr.getOperands();
	map<char, double> values;
	for (const auto& op : operands) {
		values[0] = 1;
		values[1] = 0;
	}
	ASSERT_ANY_THROW(expr.calculate(values));
}

TEST(TArithmeticExpression, can_convert_to_postfix_form)
{
	string exprStr;
	TArithmeticExpression expr(exprStr);
	ASSERT_NO_THROW(expr.getPostfix());
}

TEST(TArithmeticExpression, can_create_arithmetic_expression)
{
	string exprStr = "A+F*E*E/P";
	ASSERT_NO_THROW(TArithmeticExpression expr(exprStr));
}

TEST(TArithmeticExpression, cant_divide_to_zero) {
	string exprStr = "D/O";
	TArithmeticExpression expr(exprStr);
	vector<char> operands = expr.getOperands();
	map<char, double> values;
	for (const auto& op : operands) {
		values[0] = 1;
		values[1] = 0;
	}
	ASSERT_ANY_THROW(expr.calculate(values));
}

TEST(TArithmeticExpression, cant_define_the_expression_without_the_closing_bracket) {
	string exprStr = "(P+U)-S/H)";
	ASSERT_ANY_THROW(TArithmeticExpression expr(exprStr));
}

TEST(TArithmeticExpression, cant_define_the_expression_with_an_extra_bracket) {
	string exprStr = "(C*O-M)*M/I+T(";
	ASSERT_ANY_THROW(TArithmeticExpression expr(exprStr));
}

TEST(TArithmeticExpression, operands_are_not_defined) {
	string exprStr = "*";
	TArithmeticExpression expr(exprStr);
	vector<char> operands = expr.getOperands();
	map<char, double> values;
	
	ASSERT_ANY_THROW(expr.calculate(values));
}

TEST(TArithmeticExpression, postfix_form_is_equal_to_expected_result)
{
	string exprStr = "A*(B+C-D)/E";
	TArithmeticExpression expr(exprStr);
	ASSERT_EQ(expr.getPostfix(), "ABC+D-*E/");
}

TEST(TArithmeticExpression, postfix_form_is_not_equal_to_expected_result)
{
	string exprStr = "(F/E/T/C/H)*P/O/P";
	TArithmeticExpression expr(exprStr);
	ASSERT_NE(expr.getPostfix(), "FE/T/C/H/P*O/P//");
}