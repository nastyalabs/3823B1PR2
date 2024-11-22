#include "postfix.h"
#include <gtest.h>

TEST(Calc, can_create_calc)
{
	ASSERT_NO_THROW(Calc m("5"));
}

TEST(Calc, can_add)
{
	Calc m("3+6");
	ASSERT_NO_THROW(m.execute());
}

TEST(Calc, add_is_true)
{
	Calc m("3+6");
	ASSERT_EQ(m.execute(), 9);
}

TEST(Calc, can_sub)
{
	Calc m("9-6");
	ASSERT_NO_THROW(m.execute());
}

TEST(Calc, sub_is_true_in)
{
	Calc m("9-6");
	ASSERT_EQ(m.execute(), 3);
}

TEST(Calc, can_mult)
{
	Calc m("5*3");
	ASSERT_NO_THROW(m.execute());
}

TEST(Calc, mult_is_true)
{
	Calc m("5*3");
	ASSERT_EQ(m.execute(), 15);
}

TEST(Calc, can_div)
{
	Calc m("6/3");
	ASSERT_NO_THROW(m.execute());
}

TEST(Calc, div_is_true)
{
	Calc m("6/3");
	ASSERT_EQ(m.execute(), 2);
}

TEST(Calc, can_raise_to_a_degree)
{
	Calc m("5^2");
	ASSERT_NO_THROW(m.execute());
}

TEST(Calc, exponentiation_is_true_in_calc)
{
	Calc m("5^2");
	ASSERT_EQ(m.execute(), 25);
}

TEST(Calc, can_raise_to_a_degree_like_a_profi)
{
	Calc m("3^2^3");
	ASSERT_EQ(m.execute(), 729);
}

TEST(Calc, can_execute_with_brackets)
{
	Calc m("2+(5*2-8)");
	ASSERT_NO_THROW(m.execute());
}

TEST(Calc, execute_with_brackets_is_true)
{
	Calc m("2+(5*2-8)");
	ASSERT_EQ(m.execute(), 4);
}

TEST(Calc, can_execute_with_sin)
{
	Calc m("s(0)");
	ASSERT_NO_THROW(m.execute());
}

	TEST(Calc, execute_with_sin_is_true)
{
	Calc m("s(0)");
	ASSERT_EQ(m.execute(), 0);
}

TEST(Calc, can_execute_with_cos)
{
	Calc m("c(0)");
	ASSERT_NO_THROW(m.execute());
}

TEST(Calc, execute_with_cos_is_true)
{
	Calc m("c(0)");
	ASSERT_EQ(m.execute(), 1);
}

TEST(Calc, can_execute_with_tg)
{
	Calc m("t(0)");
	ASSERT_NO_THROW(m.execute());
}

TEST(Calc, execute_with_tg_is_true)
{
	Calc m("t(0)");
	ASSERT_EQ(m.execute(), 0);
}

TEST(Calc, can_execute_with_log)
{
	Calc m("l(1)");
	ASSERT_NO_THROW(m.execute());
}

TEST(Calc, execute_with_log_is_true)
{
	Calc m("l(1)");
	ASSERT_EQ(m.execute(), 0);
}