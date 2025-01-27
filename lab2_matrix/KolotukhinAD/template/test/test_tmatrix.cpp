#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  size_t size = 5;
  ASSERT_NO_THROW(TDynamicMatrix<int> m(size));
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
  size_t size = 5;
  TDynamicMatrix<int> m(size);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
  size_t size = 5;
  TDynamicMatrix<int> m1(size);
  m1[0][0] = 2;
  m1[1][0] = 4; 
  m1[2][0] = 9; 
  m1[3][0] = 11;
  TDynamicMatrix<int> m2(m1);

  EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
  size_t size = 5;
  TDynamicMatrix<int> m1(size);
  TDynamicMatrix<int> m2(m1);
  m2[0][0] = 5;
  EXPECT_EQ(0, m1[0][0]);
}

TEST(TDynamicMatrix, can_get_size)
{
  size_t size = 5;
  TDynamicMatrix<int> m1(size);
  
  EXPECT_EQ(size, m1.GetSize());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
  size_t size = 5;
  TDynamicMatrix<int> m1(size);
  m1[1][4] = 99;
  int res = 99;
  EXPECT_EQ(res, m1[1][4]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
  size_t size = 5;
  TDynamicMatrix<int> m1(size);
  ASSERT_NO_THROW(m1[0][0] = 1);
  ASSERT_ANY_THROW(m1[-1][0] = 1);
  ASSERT_ANY_THROW(m1[-1][-1] = 1);
  ASSERT_ANY_THROW(m1[0][-1] = 1);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
  size_t size = 5;
  TDynamicMatrix<int> m1(size);
  ASSERT_ANY_THROW(m1[size][size] = 1);
  ASSERT_ANY_THROW(m1[1][size] = 1);
  ASSERT_ANY_THROW(m1[size][1] = 1);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
  size_t size = 5;
  TDynamicMatrix<int> m1(size);
  m1[0][0] = 5;
  m1[4][4] = 5;
  ASSERT_NO_THROW(m1 = m1);
  m1 = m1;
  EXPECT_EQ(m1, m1);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
  size_t size = 5;
  TDynamicMatrix<int> m1(size);
  TDynamicMatrix<int> m2(size);
  m1[0][0] = 5;
  m1[4][4] = 5;
  ASSERT_NO_THROW(m2 = m1);
  m2 = m1;
  EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
  size_t size = 5;
  TDynamicMatrix<int> m1(size);
  TDynamicMatrix<int> m2(size * 2);
  EXPECT_NE(m1.GetSize(), m2.GetSize());
  m2 = m1;
  EXPECT_EQ(m1.GetSize(), m2.GetSize());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
  size_t size = 5;
  TDynamicMatrix<int> m1(size);
  m1[4][4] = 5;
  TDynamicMatrix<int> m2(size * 2);
  EXPECT_NO_THROW(m2 = m1);
  m2 = m1;
  EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
  size_t size = 5;
  TDynamicMatrix<int> m1(size);
  m1[0][0] = 1;
  m1[4][4] = 5;
  TDynamicMatrix<int> m2(m1);
  EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
  size_t size = 5;
  TDynamicMatrix<int> m1(size);
  m1[4][4] = 5;
  EXPECT_EQ(m1, m1);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
  size_t size = 5;
  TDynamicMatrix<int> m1(size);
  m1[4][4] = 5;
  TDynamicMatrix<int> m2(size * 2);
  m2[4][4] = 5;
  EXPECT_NE(m1, m2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
  size_t size = 5;
  TDynamicMatrix<int> m1(size);
  TDynamicMatrix<int> m2(size);
  TDynamicMatrix<int> result(size);
  for (int i = 0; i < size; i++) {
    m1[0][i] = i + 1;         // |1|2| 3| 4| 5| +
    m2[0][i] = i + 6;         // |6|7| 8| 9|10| =
    result[0][i] = i * 2 + 7; // |7|9|11|13|15|
  }
  ASSERT_NO_THROW(m1 + m2);
  EXPECT_EQ(result, m1 + m2);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
  size_t size = 5;
  TDynamicMatrix<int> m1(size);
  m1[0][0] = m1[4][4] = 5;
  TDynamicMatrix<int> m2(size * 2);
  m2[0][0] = m2[9][9] = 10;
  ASSERT_ANY_THROW(m1 + m2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
  size_t size = 5;
  TDynamicMatrix<int> m1(size);
  TDynamicMatrix<int> m2(size);
  TDynamicMatrix<int> result(size);
  for (int i = 0; i < size; i++) {
    m1[0][i] = i + 1;  // | 1| 2| 3| 4| 5| -
    m2[0][i] = i + 6;  // | 6| 7| 8| 9|10| =
    result[0][i] = -5; // |-5|-5|-5|-5|-5|
  }
  ASSERT_NO_THROW(m1 - m2);
  EXPECT_EQ(result, m1 - m2);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
  size_t size = 5;
  TDynamicMatrix<int> m1(size);
  m1[0][0] = m1[4][4] = 5;
  TDynamicMatrix<int> m2(size * 2);
  m2[0][0] = m2[9][9] = 10;
  ASSERT_ANY_THROW(m1 - m2);
}

// TEST(TDynamicMatrix, can_multiple_matrixes_with_equal_size)
// { 
//   int size = 1000;
//   TDynamicMatrix<int> m1(size);
//   TDynamicMatrix<int> m2(size);
//   for (int i = 0; i < size; i++) {
//     for (int j = 0; j < size; j++) {
//       m1[i][j] = size * i + j + 1;
//       m2[i][j] = size * i + j + 1;
//     }
//   }
  // for (int i = 0; i < size-1; i++) {
  //   for (int j = 0; j < size-1; j++) {
  //     m2[i][j] = rand() % 1000;
  //   }
  // }
  // TDynamicMatrix<int> res(size-1);
//   srand(time(0));
//   EXPECT_NO_THROW(m1 * m2);
//   cout << "runtime = " << clock()/1000.0 << endl;
// }