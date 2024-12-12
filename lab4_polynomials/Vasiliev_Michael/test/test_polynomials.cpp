#include "polynomials.h"
#include <gtest.h>

TEST(Polynomial, can_add_various_terms)
{
  Polynomial p1;
  Polynomial p2;
  p1.add_term(2, "100");
  p1.add_term(-2, "203");
  p2.add_term(0, "023");
  p2.add_term(4, "321");
  p2.add_term(2, "000");
  p2.add_term(3, "001");  // // (2x - 2x^2z^3) + (4x^3y^2z + 2 + 3z);

  EXPECT_EQ(0, p1.evaluate(1, 1, 1));
  EXPECT_EQ(9, p2.evaluate(1, 1, 1));
}

TEST(Polynomial, can_sum_with_various_terms)
{
  Polynomial p1;
  Polynomial p2;
  p1.add_term(2, "100");
  p1.add_term(-2, "203");
  p2.add_term(0, "023");
  p2.add_term(4, "321");
  p2.add_term(2, "000");
  p2.add_term(3, "001");  // (2x - 2x^2z^3) + (4x^3y^2z + 2 + 3z);

  Polynomial sum = p1 + p2;  // 2 - 2 + 4 + 2 + 3 = 9;

  EXPECT_EQ(9, sum.evaluate(1, 1, 1));
}

TEST(Polynomial, can_sum_with_various_terms_with_other_cords)
{
  Polynomial p1;
  Polynomial p2;
  p1.add_term(2, "100");
  p1.add_term(-2, "203");
  p2.add_term(0, "023");
  p2.add_term(4, "321");
  p2.add_term(2, "000");
  p2.add_term(3, "001");  // (2x - 2x^2z^3) + (4x^3y^2z + 2 + 3z);

  Polynomial sum = p1 + p2;  // 0 - 0 + 0 + 2 + 9 = 11;

  EXPECT_EQ(11, sum.evaluate(0, 2, 3));
}

TEST(Polynomial, can_sum_empty_polynomials)
{
  Polynomial p1;
  Polynomial p2;

  Polynomial sum = p1 + p2;

  EXPECT_EQ(0, sum.evaluate(1, 1, 1));
}

TEST(Polynomial, can_sub_with_various_terms)
{
  Polynomial p1;
  Polynomial p2;
  p1.add_term(2, "100");
  p1.add_term(-2, "203");
  p2.add_term(0, "023");
  p2.add_term(4, "321");
  p2.add_term(2, "000");
  p2.add_term(3, "001");  // (2x - 2x^2z^3) - (4x^3y^2z + 2 + 3z);

  Polynomial sub = p1 - p2;  // 2 - 2 - 4 - 2 - 3 = -9;

  EXPECT_EQ(-9, sub.evaluate(1, 1, 1));
}

TEST(Polynomial, can_sub_with_various_terms_with_other_cords)
{
  Polynomial p1;
  Polynomial p2;
  p1.add_term(2, "100");
  p1.add_term(-2, "203");
  p2.add_term(0, "023");
  p2.add_term(4, "321");
  p2.add_term(2, "000");
  p2.add_term(3, "001");  // (2x - 2x^2z^3) - (4x^3y^2z + 2 + 3z);

  Polynomial sub = p1 - p2;  // 0 - 0 - 0 - 2 - 9 = -11;

  EXPECT_EQ(-11, sub.evaluate(0, 2, 3));
}

TEST(Polynomial, can_sub_empty_polynomials)
{
  Polynomial p1;
  Polynomial p2;

  Polynomial sub = p1 - p2;

  EXPECT_EQ(0, sub.evaluate(1, 1, 1));
}

TEST(Polynomial, can_mult_with_various_terms)
{
  Polynomial p1;
  Polynomial p2;
  p1.add_term(2, "100");
  p1.add_term(-2, "203");
  p2.add_term(0, "023");
  p2.add_term(4, "321");
  p2.add_term(2, "000");
  p2.add_term(3, "001");  // (2x - 2x^2z^3) * (4x^3y^2z + 2 + 3z) = 8x^4y^2z + 4x + 6xz - 8x^5z^4 - 4x^2z^3 - 6x^2z^4;

  Polynomial mult = p1 * p2;  // 8 + 4 + 6 - 8 - 4 - 6 = 0;

  EXPECT_EQ(0, mult.evaluate(1, 1, 1));
}

TEST(Polynomial, can_mult_with_various_terms_with_other_cords)
{
  Polynomial p1;
  Polynomial p2;
  p1.add_term(2, "100");
  p1.add_term(-2, "203");
  p2.add_term(0, "023");
  p2.add_term(4, "321");
  p2.add_term(2, "000");
  p2.add_term(3, "001");  // (2x - 2x^2z^3) * (4x^3y^2z + 2 + 3z) = 8x^4y^2z + 4x + 6xz - 8x^5z^4 - 4x^2z^3 - 6x^2z^4;

  Polynomial mult = p1 * p2;  // 0 + 0 + 0 - 0 - 0 - 0 = 0;

  EXPECT_EQ(0, mult.evaluate(0, 2, 3));
}

TEST(Polynomial, can_mult_empty_polynomials)
{
  Polynomial p1;
  Polynomial p2;

  Polynomial mult = p1 * p2;

  EXPECT_EQ(0, mult.evaluate(1, 1, 1));
}
