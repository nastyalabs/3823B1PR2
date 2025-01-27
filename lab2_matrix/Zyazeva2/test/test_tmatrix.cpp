#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
	ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
	ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
	ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
	TDynamicMatrix<int> m(5);

	ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
	TDynamicMatrix<int> m1(2);
	for (size_t i = 0; i < 2; i++) {
		for (size_t j = 0; j < 2; j++) {
			m1[i][j] = i;
		}

	}
	TDynamicMatrix<int> m2(m1);
	for (size_t i = 0; i < 2; ++i) {
		EXPECT_EQ(m1[i], m2[i]);
	}
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> m1(2);
	for (size_t i = 0; i < 2; i++) {
		for (size_t j = 0; j < 2; j++) {
			m1[i][j] = i;
		}
	}
	TDynamicMatrix<int> m2(m1);
	m1[0][1] = 56;
	EXPECT_NE(m1[0][1], m2[0][1]);
}

TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix<int> m(5);
	EXPECT_EQ(5, m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int> m(4);
	m[1][1] = 6;
	EXPECT_EQ(6, m[1][1]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<int> m(5);
	ASSERT_ANY_THROW(m.at(-1).at(3) = 6);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<int> m(5);
	ASSERT_ANY_THROW(m.at(65).at(3) = 6);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	const int size = 2;
	TDynamicMatrix<int> m1(size);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			m1[i][j] = 1;
		}
	}
	m1 = m1;
	EXPECT_EQ(1, m1[0][0]);
	EXPECT_EQ(1, m1[0][1]);
	EXPECT_EQ(1, m1[1][0]);
	EXPECT_EQ(1, m1[1][1]);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	const int size = 2;
	TDynamicMatrix<int> m1(size), m2(size);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			m1[i][j] = 1;
		}
	}
	m2 = m1;
	EXPECT_EQ(1, m2[0][0]);
	EXPECT_EQ(1, m2[0][1]);
	EXPECT_EQ(1, m2[1][0]);
	EXPECT_EQ(1, m2[1][1]);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> m1(2);
	TDynamicMatrix<int> m2(3);
	m1[0][0] = 1;
	m1[0][1] = 2;
	m1[1][0] = 3;
	m1[1][1] = 4;
	m2 = m1;
	EXPECT_EQ(2, m2.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> m1(2);
	TDynamicMatrix<int> m2(3);
	m1[0][0] = 1;
	m1[0][1] = 2;
	m1[1][0] = 3;
	m1[1][1] = 4;
	m2 = m1;
	EXPECT_EQ(1, m2[0][0]);
	EXPECT_EQ(2, m2[0][1]);
	EXPECT_EQ(3, m2[1][0]);
	EXPECT_EQ(4, m2[1][1]);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	const int size = 2;
	TDynamicMatrix<int> m1(size), m2(size);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			m1[i][j] = 1;
		}
	}
	m2 = m1;
	EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	const int size = 2;
	TDynamicMatrix<int> m1(size);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			m1[i][j] = 1;
		}
	}
	EXPECT_EQ(m1, m1);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> m1(3), m2(5);
	EXPECT_NE(m1, m2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	const int size = 2;
	TDynamicMatrix<int> m1(size), m2(size), res(size);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			m1[i][j] = 1;
		}
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			m2[i][j] = 1;
		}
	}
	res = m1 + m2;
	EXPECT_EQ(2, res[0][0]);
	EXPECT_EQ(2, res[0][1]);
	EXPECT_EQ(2, res[1][0]);
	EXPECT_EQ(2, res[1][1]);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	const int size = 2;
	TDynamicMatrix<int> m1(size), m2(7), res(7);
	ASSERT_ANY_THROW(res = m1 + m2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	const int size = 2;
	TDynamicMatrix<int> m1(size), m2(size), res(size);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			m1[i][j] = 2;
		}
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			m2[i][j] = 1;
		}
	}
	res = m1 - m2;
	EXPECT_EQ(1, res[0][0]);
	EXPECT_EQ(1, res[0][1]);
	EXPECT_EQ(1, res[1][0]);
	EXPECT_EQ(1, res[1][1]);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	const int size = 2;
	TDynamicMatrix<int> m1(size), m2(7), res(7);
	ASSERT_ANY_THROW(res = m1 - m2);
}

TEST(TDynamicMatrix, can_mult_matr)
{
	const int size = 2;
	TDynamicMatrix<int> m1(size), m2(size);
	m1[0][0] = 3;
	m1[1][0] = 2;
	m2 = m1;
	TDynamicMatrix<int> res(2);
	res = m1 * m2;
	EXPECT_EQ(9, res[0][0]);
	EXPECT_EQ(0, res[0][1]);
	EXPECT_EQ(6, res[1][0]);
	EXPECT_EQ(0, res[1][1]);
}
