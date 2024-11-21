#include "algexp.h"

#include <gtest.h>
TEST(algexp, can_create_algexp)
{
    ASSERT_NO_THROW(algexp a());
}

TEST(algexp, can_create_algexp_with_correct_expression)
{
    ASSERT_NO_THROW(algexp a("1.5 + 2 * 3"));
}

TEST(algexp, can_create_algexp_with_incorrect_expression)
{
    ASSERT_NO_THROW(algexp a("1 + 2 *"));
}

TEST(algexp, cant_create_algexp_with_empty_string_arg)
{
    ASSERT_ANY_THROW(algexp a(""));
}

TEST(algexp, copied_algexp_is_equal_to_source_one)
{
    algexp exp1("1 + 2 * 3");
    algexp exp2(exp1);
  	EXPECT_EQ(exp1, exp2);
}

TEST(algexp, can_get_correct_postfix_expression)
{
    algexp exp1("1 + 2 * 3");
    EXPECT_EQ("1 2 3 * + ", exp1.getExpr());
}

TEST(algexp, can_get_incorrect_postfix_expression)
{
    algexp exp1("1 + 2 *");
    EXPECT_EQ("1 2 * + ", exp1.getExpr());
}

TEST(algexp, can_solve_correct_postfix_expression)
{
    algexp exp1("( ( 1 + 2 ) * 3 ) / 9");
    EXPECT_EQ(1, exp1.solveIt());
}

TEST(algexp, cant_solve_incorrect_postfix_expression)
{
    algexp exp1("( ( 1 + 2) * 3 ) /");
    ASSERT_ANY_THROW(exp1.solveIt());
}

TEST(algexp, cant_solve_division_by_zero)
{
    algexp exp1("( ( 1 + 2 ) * 3 ) / ( 4 - 4 )");
    ASSERT_ANY_THROW(exp1.solveIt());
}

TEST(algexp, can_assign_algexp_to_itself)
{
    algexp exp1("( 1 + 2 ) * 3");
    ASSERT_NO_THROW(exp1 = exp1);
}

TEST(algexp, can_assign_algexps)
{
    algexp exp1("( 1 + 2 ) * 3");
    algexp exp2 = exp1;
    EXPECT_EQ("1 2 + 3 * ", exp2.getExpr());
}

TEST(algexp, can_solve_trigonometric_functions)
{
    algexp exp1("1 + sin ( 30 )");
    algexp exp2("34 * cos ( 90 * 2 )");
    algexp exp3("3 * 7 - 4 + tan ( 15 * 6 - 45 )");
    EXPECT_EQ(1.5, exp1.solveIt());
    EXPECT_EQ(-34, exp2.solveIt());
    EXPECT_EQ(18,  exp3.solveIt());
}

TEST(algexp, hard_function)
{
    algexp exp1("1 + sin ( 27.7 * tan ( 12 * 4  + cos ( 4 / 19 ) ) ) * 39");
    ASSERT_NEAR(21.588, exp1.solveIt(), 0.001);
}