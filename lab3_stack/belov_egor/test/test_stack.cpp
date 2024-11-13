#include "stack.h"

#include <gtest.h>

TEST(Stack, can_create_stack_with_positive_length) {
    ASSERT_NO_THROW(Stack<int> s(10));
}

TEST(Stack, can_create_default_stack) {
    ASSERT_NO_THROW(Stack<int> a);
}

TEST(Stack, default_stacks_are_empty) {
    Stack<int> a;
    Stack<int> b;
    ASSERT_EQ(a, b);
}

TEST(Stack, cant_create_too_long_stack) {
    ASSERT_ANY_THROW(Stack<int> s(MAX_STACK_SIZE + 1));
}

TEST(Stack, cant_create_empty_and_negative_long_stack) {
    ASSERT_ANY_THROW(Stack<int> s(0));
    ASSERT_ANY_THROW(Stack<int> s(-1));
}

TEST(Stack, can_copy_stacks) {
    Stack<int> a(10);
    ASSERT_NO_THROW(Stack<int> b(a));
}

TEST(Stack, copied_stacks_are_equal) {
    Stack<int> a(5);
    a.push(1);
    a.push(2);
    a.push(3);
    Stack<int> b(a);
    EXPECT_EQ(a, b);
}

TEST(Stack, resize_works) {
    Stack<int> a(2);
    ASSERT_NO_THROW(a.resize(4));
    ASSERT_NO_THROW(a.resize(1));
}

TEST(Stack, resize_works_correctly) {
    int check = 10;
    Stack<int> a(2);
    a.push(check - 10);
    a.push(check);
    a.resize(10);
    EXPECT_EQ(a.top(), check);
    a.resize(1);
    EXPECT_EQ(a.top(), check - 10);
}

TEST(Stack, equal_operator_works) {
    Stack<int> a;
    Stack<int> b;
    ASSERT_NO_THROW(a == b);
}

TEST(Stack, equal_operator_works_correctly) {
    Stack<int> a(5);
    a.push(1);
    a.push(2);
    a.push(3);
    
    Stack<int> b(10);
    b.push(1);
    b.push(2);
    b.push(3);
    
    EXPECT_EQ(a, b);
}


TEST(Stack, not_equal_works) {
    Stack<int> a;
    Stack<int> b;
    ASSERT_NO_THROW(a != b);
}

TEST(Stack, not_equal_operator_works_correctly) {
    Stack<int> a(5);
    a.push(1);
    a.push(2);
    a.push(3);
    
    Stack<int> b(10);
    b.push(1);
    b.push(2);
    b.push(5);
    
    EXPECT_NE(a, b);
}

TEST(Stack, to_operator_works) {
    Stack<int> a(3);
    Stack<int> b;
    ASSERT_NO_THROW(b = a);
}

TEST(Stack, to_operator_works_correctly) {
    Stack<int> a;
    a.push(1);
    a.push(2);
    a.push(3);
    
    Stack<int> b(100);
    b = a;
    EXPECT_EQ(b, a);
    EXPECT_EQ(b.maxSize(), a.maxSize());
}

TEST(Stack, size_works) {
    Stack<int> a;
    ASSERT_NO_THROW(a.size());
}

TEST(Stack, size_works_correctly) {
    Stack<int> a;
    a.push(1);
    a.push(2);
    a.push(3);
    EXPECT_EQ(a.size(), 3);
}

TEST(Stack, max_size_works) {
    Stack<int> a;
    ASSERT_NO_THROW(a.maxSize());
}

TEST(Stack, max_size_works_correctly) {
    Stack<int> a;
    a.push(1);
    a.push(2);
    a.push(3);
    EXPECT_EQ(a.maxSize(), STANDART_STACK_SIZE);
}

TEST(Stack, is_empty_works) {
    Stack<int> a;
    ASSERT_NO_THROW(a.isEmpty());
}

TEST(Stack, is_empty_works_correctly) {
    Stack<int> a;
    EXPECT_TRUE(a.isEmpty());
}

TEST(Stack, is_full_works) {
    Stack<int> a;
    ASSERT_NO_THROW(a.isFull());
}

TEST(Stack, is_full_works_correctly) {
    Stack<int> a(2);
    a.push(1);
    a.push(2);
    EXPECT_TRUE(a.isFull());
}

TEST(Stack, push_works) {
    Stack<int> a(1);
    ASSERT_NO_THROW(a.push(1));
}

TEST(Stack, push_works_correctly) {
    Stack<int> a;
    int check = 10;
    a.push(check);
    EXPECT_EQ(check, a.top());
}

TEST(Stack, push_changes_size) {
    Stack<int> a;
    int check = a.size();
    a.push(10);
    EXPECT_EQ(check + 1, a.size());
}

TEST(Stack, push_resizes_overloaded_stack) {
    Stack<int> a(1);
    a.push(1);
    a.push(2);
    EXPECT_TRUE(a.maxSize() >= 2);
}

TEST(Stack, pop_works) {
    Stack<int> a(1);
    a.push(1);
    ASSERT_NO_THROW(a.pop());
}

TEST(Stack, pop_works_correctly) {
    Stack<int> a;
    int check = 10;
    a.push(check);
    a.push(check + 10);
    a.pop();
    EXPECT_EQ(check, a.top());
}

TEST(Stack, pop_changes_size) {
    Stack<int> a;
    a.push(10);
    a.push(12);
    int check = a.size();
    a.pop();
    EXPECT_EQ(check - 1, a.size());
}

TEST(Stack, pop_throws_when_empty) {
    Stack<int> a;
    ASSERT_ANY_THROW(a.pop());
}

TEST(Stack, pop_doesnt_resize) {
    Stack<int> a(1);
    a.push(1);
    a.push(2);
    a.push(3);
    int check = a.maxSize();
    a.pop();
    EXPECT_EQ(check, a.maxSize());
}

TEST(Stack, top_works) {
    Stack<int> a;
    a.push(10);
    ASSERT_NO_THROW(a.top());
}

TEST(Stack, top_works_correctly) {
    Stack<int> a;
    int check = 10;
    a.push(check);
    EXPECT_EQ(check, a.top());
}

TEST(Stack, top_throws_when_empty) {
    Stack<int> a;
    ASSERT_ANY_THROW(a.top());
}

TEST(Stack, clear_works) {
    Stack<int> a;
    a.push(1);
    a.push(2);
    a.push(3);
    
    ASSERT_NO_THROW(a.clear());
}

TEST(Stack, clear_works_correctly) {
    Stack<int> a;
    a.push(1);
    a.push(2);
    a.push(3);
    a.clear();
    EXPECT_TRUE(a.isEmpty());
}

TEST(Stack, clear_doesnt_resize) {
    Stack<int> a(1);
    a.push(1);
    a.push(2);
    a.push(3);
    int check = a.maxSize();
    a.clear();
    EXPECT_EQ(check, a.maxSize());
}
