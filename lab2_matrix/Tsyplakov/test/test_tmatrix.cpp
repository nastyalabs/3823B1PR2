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
    TDynamicMatrix<int> matrix1(3);
    matrix1[0][0] = 1;
    matrix1[1][1] = 2;
    matrix1[2][2] = 3;
    TDynamicMatrix<int> matrix2 = matrix1;
    ASSERT_EQ(matrix1, matrix2);
  
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
    TDynamicMatrix<int> matrix1(3);
    matrix1[0][0] = 1;
    TDynamicMatrix<int> matrix2 = matrix1;
    matrix2[0][0] = 2;
    ASSERT_NE(matrix1[0][0], matrix2[0][0]);
}

TEST(TDynamicMatrix, can_get_size)
{
    TDynamicMatrix<int> m(5); // Создаём матрицу 5x5
    ASSERT_EQ(m.size(), 5); // Проверяем, что размер равен 5
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
    TDynamicMatrix<int> matrix(3);
    matrix[1][1] = 42;
    ASSERT_EQ(matrix[1][1], 42);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
    TDynamicMatrix<int> m(5);
    ASSERT_ANY_THROW(m[-10][-10] = 10);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
    TDynamicMatrix<int> y(6);
    ASSERT_ANY_THROW(y[8][8] = 14);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
    TDynamicMatrix<int> matrix(3);
    matrix[1][1] = 5;
    matrix = matrix;
    ASSERT_EQ(matrix[1][1], 5);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
    TDynamicMatrix<int> matrix1(3), matrix2(3);
    matrix1[1][1] = 7;
    matrix2 = matrix1;
    ASSERT_EQ(matrix2[1][1], 7);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
    TDynamicMatrix<int> m1(2); // Создаём матрицу 2x2
    TDynamicMatrix<int> m2(3); // Создаём матрицу 3x3
    m1 = m2; // Присваиваем
    ASSERT_EQ(m1.size(), 3); // Проверяем, что размер m1 изменился на 3
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
    TDynamicMatrix<int> m1(2); // Создаём матрицу 2x2
    TDynamicMatrix<int> m2(3); // Создаём матрицу 3x3
    m1 = m2; // Присваиваем
    ASSERT_EQ(m1.size(), 3); // Проверяем, что размер m1 изменился на 3
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
    TDynamicMatrix<int> matrix1(3), matrix2(3);
    matrix1[0][0] = 5;
    matrix2[0][0] = 5;
    ASSERT_TRUE(matrix1 == matrix2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
    TDynamicMatrix<int> matrix(3);
    ASSERT_TRUE(matrix == matrix);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
    TDynamicMatrix<int> matrix1(3), matrix2(4);
    ASSERT_FALSE(matrix1 == matrix2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
    TDynamicMatrix<int> matrix1(2), matrix2(2);
    matrix1[0][0] = 1; 
    matrix2[0][0] = 2;
    TDynamicMatrix<int> result = matrix1 + matrix2;
    ASSERT_EQ(result[0][0], 3);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
    TDynamicMatrix<int> m1(2); // Создаём матрицу 2x2
    TDynamicMatrix<int> m2(3); // Создаём матрицу 3x3
    ASSERT_ANY_THROW(m1 + m2); // Проверяем, что при сложении выбрасывается исключение
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
    TDynamicMatrix<int> matrix1(2), matrix2(2);
    matrix1[0][0] = 5; 
    matrix2[0][0] = 3;
    TDynamicMatrix<int> result = matrix1 - matrix2;
    ASSERT_EQ(result[0][0], 2);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
    TDynamicMatrix<int> m1(2); // Создаём матрицу 2x2
    TDynamicMatrix<int> m2(3); // Создаём матрицу 3x3
    ASSERT_ANY_THROW(m1 - m2); // Проверяем, что при вычитании выбрасывается исключение

}

