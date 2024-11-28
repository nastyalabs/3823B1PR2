#include "postfix.h"
#include <gtest.h>


TEST(Calc, can_create_calc)
{
	ASSERT_NO_THROW(Calc m("5"));
}

TEST(Calc, can_do_plus_calc)
{
	Calc m("1+2");
	ASSERT_NO_THROW(m.work());
}

TEST(Calc, plus_is_true_in_calc)
{
	Calc m("1+2");
	ASSERT_EQ(m.work(), 3);
}

TEST(Calc, can_do_sub_calc)
{
	Calc m("2 - 1");
	ASSERT_NO_THROW(m.work());
}

TEST(Calc, sub_is_true_in_calc)
{
	Calc m("1 - 2");
	ASSERT_EQ(m.work(), -1);
}

TEST(Calc, can_do_mult_calc)
{
	Calc m("7 * 5");
	ASSERT_NO_THROW(m.work());
}

TEST(Calc, mult_is_true_in_calc)
{
	Calc m("7 * 5");
	ASSERT_EQ(m.work(), 35);
}

TEST(Calc, can_do_div_calc)
{
	Calc m("6/3");
	ASSERT_NO_THROW(m.work());
}

TEST(Calc, div_is_true_in_calc)
{
	Calc m("6/2");
	ASSERT_EQ(m.work(), 3);
}

TEST(Calc, can_do_exponentiation_calc)
{
	Calc m("4^3");
	ASSERT_NO_THROW(m.work());
}

TEST(Calc, exponentiation_is_true_in_calc)
{
	Calc m("4^3");
	ASSERT_EQ(m.work(), 64);
}

TEST(Calc, multi_exponentiation_is_true_in_calc)
{
	Calc m("3^2^2");
	ASSERT_EQ(m.work(), 81);
}

TEST(Calc, can_do_bkt_calc)
{
	Calc m("3*(4+3)");
	ASSERT_NO_THROW(m.work());
}

TEST(Calc, bkt_is_true_in_calc)
{
	Calc m("3*(4+3)");
	ASSERT_EQ(m.work(), 21);
}

TEST(Calc, can_do_s_calc)
{
	Calc m("s(0)");
	ASSERT_NO_THROW(m.work());
}

TEST(Calc, s_is_true_in_calc)
{
	Calc m("s(0)");
	ASSERT_EQ(m.work(), 0);
}

TEST(Calc, can_do_c_calc)
{
	Calc m("c(0)");
	ASSERT_NO_THROW(m.work());
}

TEST(Calc, c_is_true_in_calc)
{
	Calc m("c(0)");
	ASSERT_EQ(m.work(), 1);
}

TEST(Calc, can_do_t_calc)
{
	Calc m("t(0)");
	ASSERT_NO_THROW(m.work());
}

TEST(Calc, t_is_true_in_calc)
{
	Calc m("t(0)");
	ASSERT_EQ(m.work(), 0);
}

TEST(Calc, can_do_l_calc)
{
	Calc m("l(1)");
	ASSERT_NO_THROW(m.work());
}

TEST(Calc, l_is_true_in_calc)
{
	Calc m("l(1)");
	ASSERT_EQ(m.work(), 0);
}
