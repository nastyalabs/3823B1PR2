#include <gtest.h>
#include "postfix.h"

TEST(Stack, can_create_stack_with_positive_lenght)
{
	ASSERT_NO_THROW(Stack<int> v(5));
}

TEST(Stack, can_copy)
{
	Stack<int> v(5);
	v.push(7);
	ASSERT_NO_THROW(Stack<int> v1(v));
}

TEST(Stack, can_copy_correctly)
{
	Stack<int> v(5);
	v.push(7);
	Stack<int> v1(v);
	EXPECT_EQ(v1.top(), 7);
}

TEST(Stack, can_push)
{
	Stack<int> s;
	ASSERT_NO_THROW(s.push(6));
}

TEST(Stack, can_push_correctly)
{
	Stack<int> s;
	s.push(6);
	EXPECT_EQ(s.top(), 6);
}


TEST(Stack, can_pop)
{
	Stack<int> s;
	s.push(6);
	ASSERT_NO_THROW(s.pop());
}

TEST(Stack, can_pop_correctly)
{
	Stack<int> s;
	s.push(6);
	s.push(5);
	s.pop();
	EXPECT_EQ(s.top(), 6);
}

TEST(Stack, can_get_top)
{
	Stack<int> s;
	s.push(6);
	s.push(5);
	EXPECT_EQ(s.top(), 5);
}

TEST(Stack, can_see_if_empty)
{
	Stack<int> s;
	s.push(6);
	s.push(5);
	Stack<int> s1;

	EXPECT_EQ(s.empty(), false);
	EXPECT_EQ(s1.empty(), true);
}

