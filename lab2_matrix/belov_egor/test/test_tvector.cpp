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
    TDynamicVector<int> v(40);
    TDynamicVector<int> b(v);
    EXPECT_EQ(v, b);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
    TDynamicVector<int> v(40);
    TDynamicVector<int> b(v);
    b[0] = 1;
    v[0] = 0;
    ASSERT_NE(b[0], 0);
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> v(4);

  EXPECT_EQ(4, v.size());
}

TEST(TDynamicVector, can_set_and_get_element)
{
  TDynamicVector<int> v(4);
  v[0] = 4;

  EXPECT_EQ(4, v[0]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
    TDynamicVector<int> v(4);

    ASSERT_ANY_THROW(v[-1] = 4);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
    TDynamicVector<int> v(4);
    ASSERT_ANY_THROW(v[4] = 0);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
    TDynamicVector<int> v(4);
    ASSERT_NO_THROW(v = v);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
    TDynamicVector<int> v(4);
    TDynamicVector<int> b(4);
    ASSERT_NO_THROW(v = b);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
    TDynamicVector<int> v(4);
    TDynamicVector<int> b(5);
    v = b;
    EXPECT_NE(v.size(), 4);
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
    TDynamicVector<int> v(4);
    TDynamicVector<int> b(5);
    ASSERT_NO_THROW(v = b);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
    TDynamicVector<int> v(2);
    TDynamicVector<int> b(2);
    v[0] = 0;
    v[1] = 0;
    
    b[0] = 0;
    b[1] = 0;
    ASSERT_TRUE(v == b);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
    TDynamicVector<int> v(2);
    ASSERT_TRUE(v == v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
    TDynamicVector<int> v(2);
    TDynamicVector<int> b(3);
    ASSERT_TRUE(v != b);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
    TDynamicVector<int> v(2);
    ASSERT_NO_THROW(v + 3);
}

TEST(TDynamicVector, scalar_to_vector_works_correctly)
{
    TDynamicVector<int> v(2);
    TDynamicVector<int> b(2);
    v[0] = 1;
    v[1] = 2;
    v = v + 100;
    b[0] = 101;
    b[1] = 102;
    ASSERT_TRUE(v == b);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
    TDynamicVector<int> v(2);
    ASSERT_NO_THROW(v - 3);
}

TEST(TDynamicVector, subtract_scalar_from_vector_works_correctly)
{
    TDynamicVector<int> v(2);
    TDynamicVector<int> b(2);
    v[0] = 100;
    v[1] = 200;
    v = v - 100;
    b[0] = 0;
    b[1] = 100;
    ASSERT_TRUE(v == b);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
    TDynamicVector<int> v(2);
    ASSERT_NO_THROW(v * 3);
}

TEST(TDynamicVector, multiply_scalar_by_vector_works_correctly)
{
    TDynamicVector<int> v(2);
    TDynamicVector<int> b(2);
    v[0] = 3;
    v[1] = 2;
    v = v * 100;
    b[0] = 300;
    b[1] = 200;
    ASSERT_TRUE(v == b);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
    TDynamicVector<int> v(2);
    TDynamicVector<int> b(2);
    ASSERT_NO_THROW(v + b);
}

TEST(TDynamicVector, add_vectors_with_equal_size_works_correctly)
{
    TDynamicVector<int> v(2);
    TDynamicVector<int> b(2);
    TDynamicVector<int> a(2);
    v[0] = 1;
    v[1] = 2;
    b[0] = 3;
    b[1] = 4;
    b = v + b;
    a[0] = 4;
    a[1] = 6;
    ASSERT_TRUE(a == b);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
    TDynamicVector<int> v(2);
    TDynamicVector<int> b(3);
    ASSERT_ANY_THROW(v + b);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
    TDynamicVector<int> v(2);
    TDynamicVector<int> b(2);
    ASSERT_NO_THROW(v - b);
}

TEST(TDynamicVector, subtract_vectors_with_equal_size_works_correctly)
{
    TDynamicVector<int> v(2);
    TDynamicVector<int> b(2);
    TDynamicVector<int> a(2);
    v[0] = 1;
    v[1] = 2;
    b[0] = 3;
    b[1] = 4;
    b = b - v;
    a[0] = 2;
    a[1] = 2;
    ASSERT_TRUE(a == b);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
    TDynamicVector<int> v(2);
    TDynamicVector<int> b(3);
    ASSERT_ANY_THROW(v - b);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
    TDynamicVector<int> v(2);
    TDynamicVector<int> b(2);
    ASSERT_NO_THROW(v * b);
}

TEST(TDynamicVector, multiply_vectors_with_equal_size_works_correctly)
{
    TDynamicVector<int> v(2);
    TDynamicVector<int> b(2);
    v[0] = 1;
    v[1] = 2;
    b[0] = 3;
    b[1] = 4;
    int a = b * v;
    int ans = 11;
    ASSERT_TRUE(a == ans);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
    TDynamicVector<int> v(2);
    TDynamicVector<int> b(3);
    ASSERT_ANY_THROW(v * b);
}

