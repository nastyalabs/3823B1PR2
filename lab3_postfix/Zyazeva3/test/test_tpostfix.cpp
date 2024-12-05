#include "postfix.h"
#include <gtest.h>

TEST(Calculator, can_create_calculator)
{
	ASSERT_NO_THROW(Calculator myexp("(1+(5*4))/3"););
}

TEST(Calculator, can_calculate_nothrow)
{
	Calculator myexp("(1+(5*4))/3");
	ASSERT_NO_THROW(myexp.exec());
}

TEST(Calculator, can_calculate)
{
	Calculator myexp("(1+(5*4))/3");
	EXPECT_EQ(myexp.exec(), 7);
}

TEST(Calculator, can_add)
{
	Calculator myexp("1+1");
	EXPECT_EQ(myexp.exec(), 2);
}

TEST(Calculator, can_add_nothrow)
{
	Calculator myexp("1+1");
	ASSERT_NO_THROW(myexp.exec());
}

TEST(Calculator, can_sub)
{
	Calculator myexp("1-1");
	EXPECT_EQ(myexp.exec(), 0);
}

TEST(Calculator, can_mul)
{
	Calculator myexp("2*3");
	EXPECT_EQ(myexp.exec(), 6);
}

TEST(Calculator, can_div)
{
	Calculator myexp("6/2");
	EXPECT_EQ(myexp.exec(), 3);
}

TEST(Calculator, can_div_zero)
{
	Calculator myexp("6/0");
	ASSERT_ANY_THROW(myexp.exec());
}

TEST(Calculator, can_calculate_with_brackets)
{
	Calculator myexp("(1+3)*2");
	EXPECT_EQ(myexp.exec(), 8);
}

TEST(Calculator, cant_calculate_with_wrong_brackets)
{
	Calculator myexp("(1+3)(*2");
	ASSERT_ANY_THROW(myexp.exec());
}

TEST(Calculator, cant_calculate_with_wrong_brackets_2)
{
	Calculator myexp("(1+3)())*2");
	ASSERT_ANY_THROW(myexp.exec());
}

TEST(Calculator, can_exp)
{
	Calculator myexp("2^3");
	EXPECT_EQ(myexp.exec(), 8);
}