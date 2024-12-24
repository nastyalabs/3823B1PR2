#include "tmatrix.h"

#include <gtest.h>

/*
	ASSERT_NO_THROW();
	ASSERT_ANY_THROW();
	ASSERT_EQ();
	EXPECT_EQ();
*/
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
  TDynamicVector<int> v(10);
  TDynamicVector<int> _v(v);
  EXPECT_EQ(v, _v);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
  TDynamicVector<int> v(10);
  TDynamicVector<int> _v(v);
  _v[0] = 1;
  EXPECT_NE(v[0], _v[0]);
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
	TDynamicVector<int> v(10);
	ASSERT_ANY_THROW(v[-1]);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	TDynamicVector<int> v(10);
	ASSERT_ANY_THROW(v[MAX_VECTOR_SIZE + 1]);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	TDynamicVector<int> v(10);
	ASSERT_NO_THROW(v = v);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	TDynamicVector<int> v(10), _v(10);
	ASSERT_NO_THROW(v = _v);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	TDynamicVector<int> v(10);
	TDynamicVector<int> _v(9);
	v = _v;
	EXPECT_EQ(v, _v);
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	TDynamicVector<int> v(10), _v(9);
	v[0] = 1;
	v = _v;
	EXPECT_EQ(v[0], _v[0]);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	TDynamicVector<int> v(10), _v(10);
	EXPECT_EQ(v, _v);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	TDynamicVector<int> v(10);
	EXPECT_EQ(v, v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	TDynamicVector<int> v(10), _v(9);
	EXPECT_NE(v, _v);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	TDynamicVector<int> v(10);
	v[0] = 1;
	v = v + 1;
	EXPECT_EQ(v[0], 2);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	TDynamicVector<int> v(10);
	v[0] = 1;
	v = v - 1;
	EXPECT_EQ(v[0], 0);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	TDynamicVector<int> v(10);
	v[0] = 1;
	v = v * 5;
	EXPECT_EQ(v[0], 5);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	TDynamicVector<int> v(10), _v(10), __v(10);
	_v[0] = 1;
	__v[0] = 1;
	v = _v + __v;
	EXPECT_EQ(v[0], 2);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	TDynamicVector<int> v(10), _v(9);
	EXPECT_NE(v, _v);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	TDynamicVector<int> v(10), _v(10), __v(10);
	_v[0] = 1;
	__v[0] = 1;
	v = _v - __v;
	EXPECT_EQ(v[0], 0);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	TDynamicVector<int> v(10), _v(10), __v(9);
	EXPECT_NE(_v, __v);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	TDynamicVector<int> v(10), _v(10);
	v[0] = 1;
	_v[0] = 10;
	EXPECT_EQ(10, v*_v);
}


TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	TDynamicVector<int> v(10), _v(10), __v(9);
	EXPECT_NE(_v, __v);
}
