#include <gtest.h>
#include "stack.h"

TEST(Stack, can_create_Stack_without_values)
{
	ASSERT_NO_THROW(Stack<int> s());
}

TEST(Stack, can_create_Stack_with_positive_size)
{
	ASSERT_NO_THROW(Stack<int> s(5));
}

TEST(Stack, throw_when_create_Stack_with_negative_size)
{
  ASSERT_ANY_THROW(Stack<int> s(-5));
}

TEST(Stack, can_push_and_copy_Stack)
{
    Stack<int> s(5);
    s.Push(2);

    Stack<int> s1(s);

    EXPECT_EQ(2, s1.top());
}

TEST(Stack, can_push_neg_elem_and_get_top_element)
{
    Stack<int> s(2);
    s.Push(-3);

    EXPECT_EQ(-3, s.top());
}

TEST(Stack, throw_then_get_top_element_in_empty_Stack)
{
    Stack<int> s(5);

    ASSERT_ANY_THROW(s.top());
}

TEST(Stack, push_elem_in_full_Stack) {
    Stack<int> s(5);
    for (int i = 0; i < 6; i++) {
        s.Push(8);
    }

    EXPECT_EQ(8, s.top());
    EXPECT_EQ(6, s.Size());
}

TEST(Stack, can_pop_not_empty_Stack) {
    Stack<int> s(5);
    s.Push(9);
    s.Push(-8);
    s.pop();

    EXPECT_EQ(9, s.top());
}

TEST(Stack, throw_pop_in_empty_Stack) {
    Stack<int> s(5);

    ASSERT_ANY_THROW(s.pop());
}

TEST(Stack, equal_Stacks) {
    Stack<int> s(3);
    Stack<int> s1(3);
    s.Push(-1);
    s.Push(5);
    s1.Push(-1);
    s1.Push(5);

    EXPECT_EQ(true, s == s1);
}

TEST(Stack, equal_empty_Stacks) {
    Stack<int> s(3);
    Stack<int> s1(3);

    EXPECT_EQ(true, s == s1);
}

TEST(Stack, equal_Stacks_with_different_sizes) {
    Stack<int> s(4);
    Stack<int> s1(3);
    s.Push(88);
    s1.Push(88);

    EXPECT_EQ(true, s == s1);
}

TEST(Stack, not_equal_Stacks_with_different_sizes) {
    Stack<int> s(1);
    Stack<int> s1(2);
    s.Push(88);
    s1.Push(88);
    s1.Push(99);

    EXPECT_EQ(false, s == s1);
}