#include "stack.h"

#include <gtest.h>

TEST(Stack, can_create_stack_without_given_length)
{
  ASSERT_NO_THROW(Stack<int> s());
}

TEST(Stack, can_create_stack_with_positive_length)
{
  ASSERT_NO_THROW(Stack<int> s(5));
}

TEST(Stack, throws_when_create_stack_with_negative_length)
{
  ASSERT_ANY_THROW(Stack<int> s(-5));
}

TEST(Stack, can_create_copied_stack)
{
  Stack<int> s(10);

  ASSERT_NO_THROW(Stack<int> s1(s));
}

TEST(Stack, copied_stack_is_equal_to_source_one)
{
  Stack<int> s(10);
  Stack<int> s1(s);

  EXPECT_EQ(true, (s1 == s));
}

TEST(Stack, copied_stack_has_its_own_memory)
{
  Stack<int> s(10);
  Stack<int> s1(s);

  EXPECT_NE(&s, &s1);
}

TEST(Stack, can_assign_stack_to_itself)
{
  Stack<int> s(10);
  for (size_t i = 0; i < s.Size(); i++) {
    s.Push(i);
  }
  s = s;

  EXPECT_EQ(9, s.top());
}

TEST(Stack, can_assign_stacks_of_equal_size)
{
  size_t size_st = 10;
  Stack<int> s(size_st);
  Stack<int> s1(size_st);
  for (size_t i = 0; i < s1.Size(); i++) {
    s1.Push(i);
  }
  s = s1;

  EXPECT_EQ(9, s.top());
}

TEST(Stack, assign_operator_change_stack_size)
{
  Stack<int> s(10);
  Stack<int> s1(12);
  for (size_t i = 0; i < s1.Size(); i++) {
    s1.Push(i);
  }
  s = s1;

  EXPECT_EQ(12, s.Size());
}

TEST(Stack, can_assign_stacks_of_different_size)
{
  Stack<int> s(10);
  Stack<int> s1(12);
  for (size_t i = 0; i < s1.Size(); i++) {
    s1.Push(i);
  }
  s = s1;

  EXPECT_EQ(11, s.top());
}

TEST(Stack, can_get_size)
{
  Stack<int> s(4);

  EXPECT_EQ(4, s.Size());
}

TEST(Stack, compare_equal_stacks_return_true)
{
  size_t size_st = 10;
  Stack<int> s(size_st);
  Stack<int> s1(size_st);
  for (size_t i = 0; i < s1.Size(); i++) {
    s.Push(i);
    s1.Push(i);
  }

  EXPECT_EQ(true, (s1 == s));
}

TEST(Stack, compare_stack_with_itself_return_true)
{
  Stack<int> s(10);

  EXPECT_EQ(true, (s == s));
}

TEST(Stack, stacks_with_different_size_are_equal)
{
  Stack<int> s(10);
  Stack<int> s1(12);

  EXPECT_EQ(true, (s == s1));
}

TEST(Stack, push_to_stack_that_has_enough_memory)
{
  Stack<int> s(10);
  s.Push(2);
  s.Push(4);

  EXPECT_EQ(4, s.top());
}

TEST(Stack, push_to_stack_that_has_not_enough_memory)
{
  Stack<int> s(10);
  for (size_t i = 0; i < s.Size(); i++) {
    s.Push(i);
  }
  s.Push(4);

  EXPECT_EQ(4, s.top());
  EXPECT_EQ(20, s.Size());
}

TEST(Stack, top_to_stack_that_have_no_elements)
{
  Stack<int> s(10);

  EXPECT_ANY_THROW(s.top());
}

TEST(Stack, pop_to_stack_that_has_elements)
{
  Stack<int> s(10);
  for (size_t i = 0; i < s.Size(); i++) {
    s.Push(i);
  }
  s.pop();

  EXPECT_EQ(8, s.top());
  EXPECT_EQ(10, s.Size());
}

TEST(Stack, pop_to_stack_that_has_no_elements)
{
  Stack<int> s(10);

  EXPECT_ANY_THROW(s.pop());
}

TEST(Stack, empty_stack_function)
{
  Stack<int> s(3);

  EXPECT_ANY_THROW(s.pop());
}
