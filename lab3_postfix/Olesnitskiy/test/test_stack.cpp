#include <gtest.h>
#include "postfix.h"

TEST(Stack , can_create_Stack_with_positive_lenght)
{
	ASSERT_NO_THROW(Stack<int> v(5));
}

TEST(Stack, can_create_Stack_from_other_stack)
{
	Stack<int> v(5);
	for (int i = 0; i < 5; i++)
		v.push(i);
	ASSERT_NO_THROW(Stack<int> w(v));
}

TEST(Stack, created_Stack_from_other_stack_are_equal)
{
	Stack<int> v(5);
	for (int i = 0; i < 5; i++)
		v.push(i);
	Stack<int> w(v);
	ASSERT_EQ(w == v, true);
}

TEST(Stack, can_push_in_Stack)
{
	Stack<int> a;
	ASSERT_NO_THROW(a.push(2));
}

TEST(Stack, push_is_true_in_Stack)
{
	Stack<int> a;
	a.push(2);
	EXPECT_EQ(a.top(), 2);
}

TEST(Stack, can_top_in_Stack)
{
	Stack<int> a;
	ASSERT_NO_THROW(a.top());
}

TEST(Stack, top_is_true_in_Stack)
{
	Stack<int> a;
	ASSERT_EQ(a.top(), 0);
}

TEST(Stack, can_pop_in_Stack)
{
	Stack<int> a;
	a.push(1);
	a.push(2);
	ASSERT_NO_THROW(a.pop());
}

TEST(Stack, pop_is_true_in_Stack)
{
	Stack<int> a;
	a.push(1);
	a.push(2);
	ASSERT_EQ(a.pop(), 2);
}

TEST(Stack, can_emptu_Stack)
{
	Stack<int> v(5);
	ASSERT_NO_THROW(v.empty());
}

TEST(Stack, emptu_is_trye_Stack)
{
	Stack<int> v(5);
	ASSERT_EQ(v.empty(), true);
}

TEST(Stack, can_compare_Stack)
{
	Stack<int> v(5);
	Stack<int> w(4);
	ASSERT_NO_THROW(v == w);
}

TEST(Stack, compare_Stack_not_equal_size_is_true)
{
	Stack<int> v(5);
	Stack<int> w(4);
	ASSERT_EQ(v == w, false);
}

TEST(Stack, compare_not_equal_Stack_equal_size_is_false)
{
	Stack<int> v(5);
	Stack<int> w(5);
	for (int i = 0; i < 5; i++)
	{
		v.push(i);
		w.push(i+1);
	}
	ASSERT_EQ(v == w, false);
}

TEST(Stack, compare_equal_Stack_is_true)
{
	Stack<int> v(5);
	Stack<int> w(5);
	for (int i = 0; i < 5; i++)
	{
		v.push(i);
		w.push(i);
	}
	ASSERT_EQ(v == w, true);
}