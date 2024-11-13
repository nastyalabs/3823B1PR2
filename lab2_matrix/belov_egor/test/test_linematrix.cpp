#include "LineMatrix.h"

#include <gtest.h>

TEST(LineMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(LineMatrix<int> m(5));
}

TEST(LineMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(LineMatrix<int> m(100000 + 1));
}

TEST(LineMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(LineMatrix<int> m(-5));
}

TEST(LineMatrix, can_create_copied_matrix)
{
  LineMatrix<int> m(5);

  ASSERT_NO_THROW(LineMatrix<int> m1(m));
}

TEST(LineMatrix, copied_matrix_is_equal_to_source_one)
{
    LineMatrix<int> a(2);
    for (size_t i = 0; i < a.size(); i++) {
        for (size_t j = 0; j < a.size(); j++) {
            a.position(i, j) = (int)(i + 1 + j) * a.size();
        }
    }
    LineMatrix<int> b(a);
    EXPECT_EQ(a, b);
}

TEST(LineMatrix, copied_matrix_has_its_own_memory)
{
    LineMatrix<int> a(2);
    std::cout << "im here" << endl;
    LineMatrix<int> b(a);
    std::cout << "im here" << endl;
    for (size_t i = 0; i < a.size(); i++) {
        for (size_t j = 0; j < a.size(); j++) {
            std::cout << "im here" << endl;
            a.position(i, j) = (int)(i + 1 + j) * a.size();
        }
    }
    
    b.position(0, 0) = a.position(0, 0) - 1;
    EXPECT_NE(b.position(0, 0), a.position(0, 0));
}

TEST(LineMatrix, can_get_size)
{
    LineMatrix<int> a(2);
    ASSERT_NO_THROW(a.size());
}

TEST(LineMatrix, can_set_and_get_element)
{
    LineMatrix<int> a(2);
    ASSERT_NO_THROW(a.position(0, 0) = 1; int b = a.position(0, 0));
}

TEST(LineMatrix, throws_when_set_element_with_negative_index)
{
    LineMatrix<int> a(2);
    ASSERT_ANY_THROW(a.position(0, -1) = 1);
}

TEST(LineMatrix, throws_when_set_element_with_too_large_index)
{
    LineMatrix<int> a(2);
    ASSERT_ANY_THROW(a.position(0, 100) = 1);
}

TEST(LineMatrix, can_assign_matrix_to_itself)
{
    LineMatrix<int> a(2);
    ASSERT_NO_THROW(a = a);
}

TEST(LineMatrix, can_assign_matrices_of_equal_size)
{
    LineMatrix<int> a(2);
    LineMatrix<int> b(2);
    ASSERT_NO_THROW(a = b);
}

TEST(LineMatrix, assign_operator_change_matrix_size)
{
    LineMatrix<int> a(2);
    LineMatrix<int> b(3);
    a = b;
    EXPECT_EQ(a.size(), b.size());
}

TEST(LineMatrix, can_assign_matrices_of_different_size)
{
    LineMatrix<int> a(2);
    LineMatrix<int> b(3);
    ASSERT_NO_THROW(a = b);
}

TEST(LineMatrix, compare_equal_matrices_return_true)
{
    LineMatrix<int> a(100);
    std::cout << "im here" << endl;
    LineMatrix<int> b(100);
    std::cout << "im here" << endl;
    ASSERT_TRUE(a == b);
    std::cout << "im here" << endl;
}

TEST(LineMatrix, compare_matrix_with_itself_return_true)
{
    LineMatrix<int> a(2);
    ASSERT_TRUE(a == a);
}

TEST(LineMatrix, matrices_with_different_size_are_not_equal)
{
    LineMatrix<int> a(2);
    LineMatrix<int> b(3);
    for (size_t i = 0; i < a.size(); i++) {
        for (size_t j = 0; j < a.size(); j++) {
            a.position(i, j) = (int)(i + 1 + j) * a.size();
        }
    }
    for (size_t i = 0; i < b.size(); i++) {
        for (size_t j = 0; j < b.size(); j++) {
            b.position(i, j) = (int)(i + 1 + j) * b.size();
        }
    }
    ASSERT_TRUE(a != b);
}

TEST(LineMatrix, can_add_matrices_with_equal_size)
{
    LineMatrix<int> a(2);
    std::cout << "im here" << endl;
    LineMatrix<int> b(2);
    std::cout << "im here" << endl;
    for (size_t i = 0; i < a.size(); i++) {
        for (size_t j = 0; j < a.size(); j++) {
            std::cout << "im here" << endl;
            a.position(i, j) = (int)(i + 1 + j) * a.size();
        }
    }
    for (size_t i = 0; i < b.size(); i++) {
        for (size_t j = 0; j < b.size(); j++) {
            std::cout << "im here" << endl;
            b.position(i, j) = (int)(i + 1 + j) * b.size();
        }
    }
    std::cout << "im here" << endl;
    ASSERT_NO_THROW(a + b);
    std::cout << "im here" << endl;
}

TEST(LineMatrix, add_matrices_with_equal_size_works_correctly)
{
    LineMatrix<int> a(2);
    LineMatrix<int> b(2);
    LineMatrix<int> c(2);
    
    a.position(0, 0) = 1;
    a.position(0, 1) = 2;
    a.position(1, 0) = 3;
    a.position(1, 1) = 4;
    
    b.position(0, 0) = 10;
    b.position(0, 1) = 20;
    b.position(1, 0) = 30;
    b.position(1, 1) = 40;
    
    c.position(0, 0) = 11;
    c.position(0, 1) = 22;
    c.position(1, 0) = 33;
    c.position(1, 1) = 44;
    
    b = a + b;
    ASSERT_TRUE(b == c);
}

TEST(LineMatrix, cant_add_matrices_with_not_equal_size)
{
    LineMatrix<int> a(2);
    LineMatrix<int> b(3);
    for (size_t i = 0; i < a.size(); i++) {
        for (size_t j = 0; j < a.size(); j++) {
            a.position(i, j) = (int)(i + 1 + j) * a.size();
        }
    }
    for (size_t i = 0; i < b.size(); i++) {
        for (size_t j = 0; j < b.size(); j++) {
            b.position(i, j) = (int)(i + 1 + j) * b.size();
        }
    }
    ASSERT_ANY_THROW(a + b);
}

TEST(LineMatrix, can_subtract_matrices_with_equal_size)
{
    LineMatrix<int> a(2);
    LineMatrix<int> b(2);
    for (size_t i = 0; i < a.size(); i++) {
        for (size_t j = 0; j < a.size(); j++) {
            a.position(i, j) = (int)(i + 1 + j) * a.size();
        }
    }
    for (size_t i = 0; i < b.size(); i++) {
        for (size_t j = 0; j < b.size(); j++) {
            b.position(i, j) = (int)(i + 1 + j) * b.size();
        }
    }
    ASSERT_NO_THROW(a - b);
}

TEST(LineMatrix, subtract_matrices_with_equal_size_works_correctly)
{
    LineMatrix<int> a(2);
    LineMatrix<int> b(2);
    LineMatrix<int> c(2);
    
    a.position(0, 0) = 1;
    a.position(0, 1) = 2;
    a.position(1, 0) = 3;
    a.position(1, 1) = 4;
    
    b.position(0, 0) = 10;
    b.position(0, 1) = 20;
    b.position(1, 0) = 30;
    b.position(1, 1) = 40;
    
    c.position(0, 0) = 9;
    c.position(0, 1) = 18;
    c.position(1, 0) = 27;
    c.position(1, 1) = 36;
    
    b = b - a;
    ASSERT_TRUE(b == c);
}

TEST(LineMatrix, cant_subtract_matrixes_with_not_equal_size)
{
    LineMatrix<int> a(2);
    LineMatrix<int> b(3);
    for (size_t i = 0; i < a.size(); i++) {
        for (size_t j = 0; j < a.size(); j++) {
            a.position(i, j) = (int)(i + 1 + j) * a.size();
        }
    }
    for (size_t i = 0; i < b.size(); i++) {
        for (size_t j = 0; j < b.size(); j++) {
            b.position(i, j) = (int)(i + 1 + j) * b.size();
        }
    }
    ASSERT_ANY_THROW(a - b);
}

TEST(LineMatrix, can_multiply_matrices_with_equal_size_works_correctly)
{
    LineMatrix<int> a(2);
    LineMatrix<int> b(2);
    LineMatrix<int> c(2);
    a.position(0, 0) = 1;
    a.position(0, 1) = 2;
    a.position(1, 0) = 4;
    a.position(1, 1) = 3;
    
    b.position(0, 0) = 3;
    b.position(0, 1) = 2;
    b.position(1, 0) = 6;
    b.position(1, 1) = 1;
    b = a * b;
    
    c.position(0, 0) = 15;
    c.position(0, 1) = 4;
    c.position(1, 0) = 30;
    c.position(1, 1) = 11;
    ASSERT_TRUE(b == c);
}
