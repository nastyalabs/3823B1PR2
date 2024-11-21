#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
  TDynamicVector<int> v(10);

  ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
  TDynamicVector<int> v1(10);
  for (int i = 0; i < 10; i++) {
    v1[i] = i;
  }
  TDynamicVector<int> v2(v1);
  EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
  TDynamicVector<int> v1(5);
  TDynamicVector<int> v2(v1);
  v1[4] = 4;
  v2[4] = -4;
  ASSERT_NE(v1[4], v2[4]);
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> v(4);
  EXPECT_EQ(4, v.GetSize());
}

//TEST(TDynamicVector, can_set_and_get_element)
//{
//  TDynamicVector<int> v(4);
//  v[0] = 4;
//
//  EXPECT_EQ(4, v[0]);
//}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
  TDynamicVector<int> v{};
  ASSERT_ANY_THROW(v[-1] = 1);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
  TDynamicVector<int> v(MAX_VECTOR_SIZE);
  ASSERT_ANY_THROW(v[MAX_VECTOR_SIZE] = 1);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
  TDynamicVector<int> v(5);
  v[1] = 1;
  v[3] = -5;
  v[4] = 99;
  TDynamicVector<int> exp(v);
  v = v;
  
  EXPECT_EQ(exp, v);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
  int size = 5;
  TDynamicVector<int> v1(size);
  TDynamicVector<int> v2(size);
  v1[0] = 1;
  v1[2] = -5;
  v1[4] = 99;
  ASSERT_NO_THROW(v2 = v1;);
  v2 = v1;
  EXPECT_EQ(v2, v1);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
  int size_1 = 5;
  int size_2 = 7;
  TDynamicVector<int> v1(size_1);
  v1[3] = 7;
  TDynamicVector<int> v2(size_2);
  v2[4] = 9;

  v1 = v2;

  EXPECT_EQ(v1, v2);
  EXPECT_EQ(size_2, v1.GetSize());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
  size_t size_1 = 5;
  size_t size_2 = 15;
  TDynamicVector<int> v1(size_1);
  v1[0] = 1;
  v1[2] = 2;
  v1[4] = 4;
  TDynamicVector<int> v2(size_2);
  v2 = v1;

  EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
  size_t size = 5;
  TDynamicVector<int> v1(size);
  v1[0] = 0;
  v1[2] = 2;
  v1[4] = 4;
  TDynamicVector<int> exp(size);
  exp[0] = 0;
  exp[2] = 2;
  exp[4] = 4;

  EXPECT_EQ(exp, v1);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
  size_t size = 5;
  TDynamicVector<int> v(size);
  v[0] = 1;
  v[2] = 2;
  v[4] = 4;
  EXPECT_EQ(true, v == v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
  size_t size_1 = 5;
  size_t size_2 = 15;
  TDynamicVector<int> v1(size_1);
  v1[0] = 1;
  v1[2] = 2;
  v1[4] = 4;
  TDynamicVector<int> v2(size_2);

  EXPECT_EQ(true, v1 != v2);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
  size_t size = 5;
  TDynamicVector<int> v(size);
  v[0] = 1;
  v[2] = 2;
  v[4] = 4;
  v = v + 5;
  TDynamicVector<int> exp(size);
  exp[0] = 6;
  exp[1] = 5;
  exp[2] = 7;
  exp[3] = 5;
  exp[4] = 9;

  EXPECT_EQ(exp, v);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
  size_t size = 5;
  TDynamicVector<int> v(size);
  v[0] = 1;
  v[2] = 2;
  v[4] = 4;
  v = v - 5;
  TDynamicVector<int> exp(size);
  exp[0] = -4;
  exp[1] = -5;
  exp[2] = -3;
  exp[3] = -5;
  exp[4] = -1;

  EXPECT_EQ(exp, v);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
  size_t size = 5;
  TDynamicVector<int> v(size);
  v[0] = 1;
  v[2] = 2;
  v[4] = 4;
  v = v * 3;
  TDynamicVector<int> exp(size);
  exp[0] = 3;
  exp[2] = 6;
  exp[4] = 12;

  EXPECT_EQ(exp, v);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
  size_t size = 5;
  TDynamicVector<int> v1(size);
  TDynamicVector<int> v2(size);
  TDynamicVector<int> result(size);
  v1[0] = 1;  v2[0] = 39;
              v2[1] = -10;
  v1[2] = 2;  v2[2] = 5;
              v2[3] = 4;
  v1[4] = 4;
  result = v1 + v2;

  TDynamicVector<int> exp(size);
  exp[0] = 40;
  exp[1] = -10;
  exp[2] = 7;
  exp[3] = 4;
  exp[4] = 4;

  EXPECT_EQ(exp, result);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
  size_t size_1 = 5;
  size_t size_2 = 10;
  TDynamicVector<int> v1(size_1);
  TDynamicVector<int> v2(size_2);
  ASSERT_ANY_THROW(v1 + v2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
  size_t size = 5;
  TDynamicVector<int> v1(size);
  TDynamicVector<int> v2(size);
  TDynamicVector<int> result(size);
  v1[0] = 1;  v2[0] = 39;
              v2[1] = -10;
  v1[2] = 2;  v2[2] = 5;
              v2[3] = 4;
  v1[4] = 4;
  result = v1 - v2;
  
  TDynamicVector<int> exp(size);
  exp[0] = -38;
  exp[1] = 10;
  exp[2] = -3;
  exp[3] = -4;
  exp[4] = 4;

  EXPECT_EQ(exp, result);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{ 
  size_t size_1 = 5;
  size_t size_2 = 10;
  TDynamicVector<int> v1(size_1);
  TDynamicVector<int> v2(size_2);
  ASSERT_ANY_THROW(v1 - v2);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
  size_t size = 5;
  TDynamicVector<int> v1(size);
  TDynamicVector<int> v2(size);
  v1[0] = 1;  v2[0] = 39;
              v2[1] = -10;
  v1[2] = 2;  v2[2] = 5;
              v2[3] = 4;
  v1[4] = 4;
  int result = v1 * v2;
  
  int exp = 49;
  EXPECT_EQ(exp, result);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
  size_t size_1 = 5;
  size_t size_2 = 10;
  TDynamicVector<int> v1(size_1);
  TDynamicVector<int> v2(size_2);
  ASSERT_ANY_THROW(v1 * v2);
}
