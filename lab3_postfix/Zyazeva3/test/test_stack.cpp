#include <gtest.h>
#include "postfix.h"

TEST(Stack, can_create_stack_with_positive_lenght)
{
	ASSERT_NO_THROW(Stack<int> v(5));
}

TEST(Stack, cant_create_stack_with_negative_lenght)
{
	ASSERT_ANY_THROW(Stack<int> v(-5));
}

TEST(Stack, can_copy)
{
	Stack<int> v(5);
	v.Push(7);
	ASSERT_NO_THROW(Stack<int> v1(v));
}

TEST(Stack, can_copy_correctly)
{
	Stack<int> v(5);
	v.Push(7);
	Stack<int> v1(v);
	EXPECT_EQ(v1.Top(), 7);
}

TEST(Stack, can_push)
{
	Stack<int> s;
	ASSERT_NO_THROW(s.Push(6));
}

TEST(Stack, can_push_correctly)
{
	Stack<int> s;
	s.Push(6);
	EXPECT_EQ(s.Top(), 6);
}


TEST(Stack, can_expand_stack)
{
	Stack<int> s(2);
	s.Push(6);
	s.Push(6);
	s.Push(5);
	s.Push(5);
	EXPECT_EQ(s.Size(), 4);
}

TEST(Stack, can_pop)
{
	Stack<int> s;
	s.Push(6);
	ASSERT_NO_THROW(s.Pop());
}

TEST(Stack, can_pop_correctly)
{
	Stack<int> s;
	s.Push(6);
	s.Push(5);
	s.Pop();
	EXPECT_EQ(s.Top(), 6);
}

TEST(Stack, can_get_top)
{
	Stack<int> s;
	s.Push(6);
	s.Push(5);
	EXPECT_EQ(s.Top(), 5);
}

TEST(Stack, can_see_if_empty)
{
	Stack<int> s;
	s.Push(6);
	s.Push(5);
	Stack<int> s1;

	EXPECT_EQ(s.empty(), false);
	EXPECT_EQ(s1.empty(), true);
}

TEST(Stack, can_see_size)
{
	Stack<int> s;
	s.Push(6);
	s.Push(5);

	EXPECT_EQ(s.Size(), 2);
}

TEST(Stack, can_clear_stack)
{
	Stack<int> s;
	s.Push(6);
	s.Push(5);
	ASSERT_NO_THROW(s.clear());
}

TEST(Stack, can_clear_stack_correctly)
{
	Stack<int> s;
	s.Push(6);
	s.Push(5);
	s.clear();
	EXPECT_EQ(s.empty(), true);
}








