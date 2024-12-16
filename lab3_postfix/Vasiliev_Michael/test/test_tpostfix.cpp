#include "postfix.h"
#include <gtest.h>

TEST(TArithmeticExpression, can_solve_simple_expression)
{
  string arithm = "4*3+2";
  TArithmeticExpression expr(arithm);

  EXPECT_EQ("4*3+2", expr.GetInfix());
  EXPECT_EQ("43*2+", expr.GetPostfix());
  EXPECT_EQ(14, expr.Calculate());
}

TEST(TArithmeticExpression, can_solve_simple_expression_with_diff_priority)
{
  string arithm = "4+3*2";
  TArithmeticExpression expr(arithm);

  EXPECT_EQ("4+3*2", expr.GetInfix());
  EXPECT_EQ("432*+", expr.GetPostfix());
  EXPECT_EQ(10, expr.Calculate());
}

TEST(TArithmeticExpression, can_solve_simple_expression_with_diff_priority_and_mod_operator)
{
  string arithm = "4+6/2%3";
  TArithmeticExpression expr(arithm);

  EXPECT_EQ("4+6/2%3", expr.GetInfix());
  EXPECT_EQ("462/3%+", expr.GetPostfix());
  EXPECT_EQ(4, expr.Calculate());
}

TEST(TArithmeticExpression, can_solve_difficult_expression_with_diff_priority)
{
  string arithm = "4+3/2-3+1*2";
  TArithmeticExpression expr(arithm);

  EXPECT_EQ("4+3/2-3+1*2", expr.GetInfix());
  EXPECT_EQ("432/+3-12*+", expr.GetPostfix());
  EXPECT_EQ(4.5, expr.Calculate());
}

TEST(TArithmeticExpression, can_solve_simple_expression_with_parantheses)
{
  string arithm = "3+2*(9*3)";
  TArithmeticExpression expr(arithm);

  EXPECT_EQ("3+2*(9*3)", expr.GetInfix());
  EXPECT_EQ("3293**+", expr.GetPostfix());
  EXPECT_EQ(57, expr.Calculate());
}

TEST(TArithmeticExpression, can_solve_simple_expression_with_double_parantheses)
{
  string arithm = "3+(9*3+(4-2))";
  TArithmeticExpression expr(arithm);

  EXPECT_EQ("3+(9*3+(4-2))", expr.GetInfix());
  EXPECT_EQ("393*42-++", expr.GetPostfix());
  EXPECT_EQ(32, expr.Calculate());
}

TEST(TArithmeticExpression, can_solve_simple_expression_with_diff_priority_and_parantheses)
{
  string arithm = "3*2+(4+3)";
  TArithmeticExpression expr(arithm);

  EXPECT_EQ("3*2+(4+3)", expr.GetInfix());
  EXPECT_EQ("32*43++", expr.GetPostfix());
  EXPECT_EQ(13, expr.Calculate());
}

TEST(TArithmeticExpression, can_solve_difficult_expression_with_diff_priority_and_parantheses)
{
  string arithm = "(9+3*2)*(8/5-4)";
  TArithmeticExpression expr(arithm);

  EXPECT_EQ("(9+3*2)*(8/5-4)", expr.GetInfix());
  EXPECT_EQ("932*+85/4-*", expr.GetPostfix());
  EXPECT_EQ(-36, expr.Calculate());
}

TEST(TArithmeticExpression, cannot_solve_expression_without_end_paranthesis)
{
  string arithm = "4+3*(5+2";

  EXPECT_ANY_THROW(TArithmeticExpression expr(arithm));
}

TEST(TArithmeticExpression, cannot_solve_expression_without_begin_paranthesis)
{
  string arithm = "4+3*)5+2";

  EXPECT_ANY_THROW(TArithmeticExpression expr(arithm));
}

TEST(TArithmeticExpression, cannot_solve_expression_without_operator_before_parantheses)
{
  string arithm = "4+3(3-2)";

  EXPECT_ANY_THROW(TArithmeticExpression expr(arithm));
}

TEST(TArithmeticExpression, cannot_solve_expression_with_multiple_operators_in_the_row)
{
  string arithm = "4*/3";

  EXPECT_ANY_THROW(TArithmeticExpression expr(arithm));
}

TEST(TArithmeticExpression, cannot_div_by_zero)
{
  string arithm = "4+5/0";
  TArithmeticExpression expr(arithm);

  EXPECT_ANY_THROW(expr.Calculate());
}
