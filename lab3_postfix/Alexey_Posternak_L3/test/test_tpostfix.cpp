//#include "postfix.h"
#include <gtest.h>
#include "Alexey_Posternak_L3/include/postfix.h"

TEST(TArithmeticExpression, go_to_postfix_and_calculate_1) {
    string infix = "1+2";
    TArithmeticExpression p(infix);

    EXPECT_EQ("12+", p.getPostfix());
    EXPECT_EQ(3, p.Calculate());
}

TEST(TArithmeticExpression, go_to_postfix_and_calculate_2) {
    string infix = "1+2*(3-2)-4";
    TArithmeticExpression p(infix);

    EXPECT_EQ("1232-*+4-", p.getPostfix());
    EXPECT_EQ(-1, p.Calculate());
}

TEST(TArithmeticExpression, go_to_postfix_and_calculate_3) {
    string infix = "(2+9*7)*(7/5-3)";
    TArithmeticExpression p(infix);

    EXPECT_EQ("297*+75/3-*", p.getPostfix());
    EXPECT_EQ(-104, p.Calculate());
}

TEST(TArithmeticExpression, end_paranthesis_is_not_found) {
  string f = "(((1+2)*1-2)+5)*2-(7";

  EXPECT_ANY_THROW(TArithmeticExpression p(f));
}

TEST(TArithmeticExpression, begin_paranthesis_is_not_found) {
  string f = "(2+3)*8-1)/2";

  EXPECT_ANY_THROW(TArithmeticExpression p(f));
}