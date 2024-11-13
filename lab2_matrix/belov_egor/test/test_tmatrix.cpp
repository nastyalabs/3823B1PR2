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
    TDynamicMatrix<int> a(2);
    for (size_t i = 0; i < a.size(); i++) {
        for (size_t j = 0; j < a.size(); j++) {
            a[i][j] = i + 1 + j * a.size();
        }
    }
    TDynamicMatrix<int> b(a);
    EXPECT_EQ(a, b);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
    TDynamicMatrix<int> a(2);
    for (size_t i = 0; i < a.size(); i++) {
        for (size_t j = 0; j < a.size(); j++) {
            a[i][j] = i + 1 + j * a.size();
        }
    }
    TDynamicMatrix<int> b(a);
    b[0] = a[0] - 1;
    EXPECT_NE(b[0], a[0]);
}

TEST(TDynamicMatrix, can_get_size)
{
    TDynamicMatrix<int> a(2);
    ASSERT_NO_THROW(a.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
    TDynamicMatrix<int> a(2);
    ASSERT_NO_THROW(a[0][0] = 1; int b = a[0][0]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
    TDynamicMatrix<int> a(2);
    ASSERT_ANY_THROW(a[0][-1] = 1);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
    TDynamicMatrix<int> a(2);
    ASSERT_ANY_THROW(a[0][100] = 1);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
    TDynamicMatrix<int> a(2);
    ASSERT_NO_THROW(a = a);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
    TDynamicMatrix<int> a(2);
    TDynamicMatrix<int> b(2);
    ASSERT_NO_THROW(a = b);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
    TDynamicMatrix<int> a(2);
    TDynamicMatrix<int> b(3);
    a = b;
    EXPECT_EQ(a.size(), b.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
    TDynamicMatrix<int> a(2);
    TDynamicMatrix<int> b(3);
    ASSERT_NO_THROW(a = b);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
    TDynamicMatrix<int> a(2);
    TDynamicMatrix<int> b(2);
    for (size_t i = 0; i < a.size(); i++) {
        for (size_t j = 0; j < a.size(); j++) {
            a[i][j] = i + 1 + j * a.size();
        }
    }
    for (size_t i = 0; i < b.size(); i++) {
        for (size_t j = 0; j < b.size(); j++) {
            b[i][j] = i + 1 + j * b.size();
        }
    }
    ASSERT_TRUE(a == b);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
    TDynamicMatrix<int> a(2);
    ASSERT_TRUE(a == a);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
    TDynamicMatrix<int> a(2);
    TDynamicMatrix<int> b(3);
    for (size_t i = 0; i < a.size(); i++) {
        for (size_t j = 0; j < a.size(); j++) {
            a[i][j] = i + 1 + j * a.size();
        }
    }
    for (size_t i = 0; i < b.size(); i++) {
        for (size_t j = 0; j < b.size(); j++) {
            b[i][j] = i + 1 + j * b.size();
        }
    }
    ASSERT_TRUE(a != b);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
    TDynamicMatrix<int> a(2);
    TDynamicMatrix<int> b(2);
    for (size_t i = 0; i < a.size(); i++) {
        for (size_t j = 0; j < a.size(); j++) {
            a[i][j] = i + 1 + j * a.size();
        }
    }
    for (size_t i = 0; i < b.size(); i++) {
        for (size_t j = 0; j < b.size(); j++) {
            b[i][j] = i + 1 + j * b.size();
        }
    }
    ASSERT_NO_THROW(a + b);
}

TEST(TDynamicMatrix, add_matrices_with_equal_size_works_correctly)
{
    TDynamicMatrix<int> a(2);
    TDynamicMatrix<int> b(2);
    TDynamicMatrix<int> c(2);
    
    a[0][0] = 1;
    a[0][1] = 2;
    a[1][0] = 3;
    a[1][1] = 4;
    
    b[0][0] = 10;
    b[0][1] = 20;
    b[1][0] = 30;
    b[1][1] = 40;
    
    c[0][0] = 11;
    c[0][1] = 22;
    c[1][0] = 33;
    c[1][1] = 44;
    
    b = a + b;
    ASSERT_TRUE(b == c);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
    TDynamicMatrix<int> a(2);
    TDynamicMatrix<int> b(3);
    for (size_t i = 0; i < a.size(); i++) {
        for (size_t j = 0; j < a.size(); j++) {
            a[i][j] = i + 1 + j * a.size();
        }
    }
    for (size_t i = 0; i < b.size(); i++) {
        for (size_t j = 0; j < b.size(); j++) {
            b[i][j] = i + 1 + j * b.size();
        }
    }
    ASSERT_ANY_THROW(a + b);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
    TDynamicMatrix<int> a(2);
    TDynamicMatrix<int> b(2);
    for (size_t i = 0; i < a.size(); i++) {
        for (size_t j = 0; j < a.size(); j++) {
            a[i][j] = i + 1 + j * a.size();
        }
    }
    for (size_t i = 0; i < b.size(); i++) {
        for (size_t j = 0; j < b.size(); j++) {
            b[i][j] = i + 1 + j * b.size();
        }
    }
    ASSERT_NO_THROW(a - b);
}

TEST(TDynamicMatrix, subtract_matrices_with_equal_size_works_correctly)
{
    TDynamicMatrix<int> a(2);
    TDynamicMatrix<int> b(2);
    TDynamicMatrix<int> c(2);
    
    a[0][0] = 1;
    a[0][1] = 2;
    a[1][0] = 3;
    a[1][1] = 4;
    
    b[0][0] = 10;
    b[0][1] = 20;
    b[1][0] = 30;
    b[1][1] = 40;
    
    c[0][0] = 9;
    c[0][1] = 18;
    c[1][0] = 27;
    c[1][1] = 36;
    
    b = b - a;
    ASSERT_TRUE(b == c);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
    TDynamicMatrix<int> a(2);
    TDynamicMatrix<int> b(3);
    for (size_t i = 0; i < a.size(); i++) {
        for (size_t j = 0; j < a.size(); j++) {
            a[i][j] = i + 1 + j * a.size();
        }
    }
    for (size_t i = 0; i < b.size(); i++) {
        for (size_t j = 0; j < b.size(); j++) {
            b[i][j] = i + 1 + j * b.size();
        }
    }
    ASSERT_ANY_THROW(a - b);
}

TEST(TDynamicMatrix, can_multiply_matrices_with_vector_equal_size)
{
    TDynamicMatrix<int> a(2);
    TDynamicVector<int> b(2);
    for (size_t i = 0; i < a.size(); i++) {
        for (size_t j = 0; j < a.size(); j++) {
            a[i][j] = i + 1 + j * a.size();
        }
    }
    b[0] = 1;
    b[1] = 2;
    ASSERT_NO_THROW(a * b);
}

TEST(TDynamicMatrix, multiply_matrices_with_vector_equal_size_works_correctly)
{
    TDynamicMatrix<int> a(2);
    TDynamicVector<int> b(2);
    TDynamicVector<int> c(2);
    
    a[0][0] = 1;
    a[0][1] = 2;
    a[1][0] = 4;
    a[1][1] = 3;
    
    b[0] = 3;
    b[1] = 6;
    
    c[0] = 15;
    c[1] = 30;
    
    b = a * b;
    ASSERT_TRUE(b == c);
}

TEST(TDynamicMatrix, cant_multiply_matrices_with_vector_not_equal_size)
{
    TDynamicMatrix<int> a(2);
    TDynamicVector<int> b(3);
    for (size_t i = 0; i < a.size(); i++) {
        for (size_t j = 0; j < a.size(); j++) {
            a[i][j] = i + 1 + j * a.size();
        }
    }
    b[0] = 1;
    b[1] = 2;
    b[2] = 3;
    ASSERT_ANY_THROW(a * b);
}

TEST(TDynamicMatrix, can_multiply_matrices_with_equal_size_works_correctly)
{
    TDynamicMatrix<int> a(2);
    TDynamicMatrix<int> b(2);
    TDynamicMatrix<int> c(2);
    a[0][0] = 1;
    a[0][1] = 2;
    a[1][0] = 4;
    a[1][1] = 3;
    
    b[0][0] = 3;
    b[0][1] = 2;
    b[1][0] = 6;
    b[1][1] = 1;
    b = a * b;
    
    c[0][0] = 15;
    c[0][1] = 4;
    c[1][0] = 30;
    c[1][1] = 11;
    ASSERT_TRUE(b == c);
}
