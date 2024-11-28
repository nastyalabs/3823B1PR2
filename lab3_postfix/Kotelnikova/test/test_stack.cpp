#include "postfix.h"
#include <gtest.h>

TEST(Stack, can_create_stack_with_positive_length)
{
	ASSERT_NO_THROW(Stack<int> v(5));
}

TEST(Stack, can_create_too_large_stack)
{
	ASSERT_NO_THROW(Stack<int> v(100));
}

TEST(Stack, cant_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(Stack<int> v(-5));
}

TEST(Stack, can_create_copied_stack)
{
	Stack<int> v(10);
	ASSERT_NO_THROW(Stack<int> v1(v));
}

TEST(Stack, copied_stack_is_equal_to_source_one)
{
	Stack<int> v1(10);
	for (int i = 0; i < 10; i++) {
		v1.Push(i);
	}
	Stack<int> v2(v1);
	EXPECT_EQ(v1.Size(), v2.Size());
	while (!v1.empty() && !v2.empty()) {
		EXPECT_TRUE(v1.pop() == v2.pop());
	}
}

TEST(Stack, copied_stack_has_its_own_memory)
{
	Stack<int> v1(10);
	for (int i = 0; i < 10; i++) {
		v1.Push(i);
	}
	Stack<int> v2(v1);
	v1.Push(100);
	EXPECT_EQ(v2.Size(), 10);
	bool isDifferent = false;
	for (int i = 0; i < 5; i++) {
		int v1Top = v1.pop();
		int v2Top = v2.pop();
		if (v1Top != v2Top) {
			isDifferent = true;
		}
	}
	EXPECT_TRUE(isDifferent);
}

TEST(Stack, can_get_size)
{
	Stack<int> v1(10);
	EXPECT_EQ(v1.Size(), 0);

	Stack<int> v2(10);
	for (int i = 0; i < 5; i++) {
		v2.Push(i);
	}
	EXPECT_EQ(v2.Size(), 5);
}

TEST(Stack, change_stack_size) {
	Stack<int> v1(5);
	Stack<int> v2(10);
	for (int i = 0; i < 10; ++i) {
		v2.Push(i);
	}
	v1 = v2;
	EXPECT_EQ(v1.Size(), v2.Size());
}

TEST(Stack, can_assign_stack_of_different_size)
{
	Stack<int> v1(5);
	Stack<int> v2(10);
	for (int i = 0; i < 5; i++) {
		v1.Push(i * 1);
	}
	for (int i = 0; i < 10; ++i) {
		v2.Push(i * 2);
	}
	ASSERT_NO_THROW(v1 = v2);
	EXPECT_EQ(v1.Size(), v2.Size());
	while (!v1.empty() && !v2.empty()) {
		EXPECT_EQ(v1.pop(), v2.pop());
	}
}

TEST(Stack, compare_equal_stack_return_true)
{
	Stack<int> v1(5);
	Stack<int> v2(5);
	for (size_t i = 0; i < 5; i++) {
		v1.Push(i);
		v2.Push(i);
	}
	EXPECT_TRUE(v1 == v2);
}

TEST(Stack, compare_stack_with_itself_return_true)
{
	Stack<int> v(5);
	for (int i = 0; i < 5; i++) {
		v.Push(i);
	}
	EXPECT_TRUE(v == v);
}

TEST(Stack, stack_with_different_size_are_not_equal)
{
	Stack<int> v1(5);
	Stack<int> v2(10);
	for (int i = 0; i < 5; i++) {
		v1.Push(i);
	}
	for (int i = 0; i < 10; i++) {
		v2.Push(i);
	}
	EXPECT_FALSE(v1 == v2);
}

TEST(Stack, can_Push)
{
	Stack<int> v;
	ASSERT_NO_THROW(v.Push(5));
}

TEST(Stack, Push_is_true)
{
	Stack<int> v;
	v.Push(5);
	EXPECT_EQ(v.top(), 5);
}

TEST(Stack, can_top)
{
	Stack<int> v;
	ASSERT_NO_THROW(v.top());
}

TEST(Stack, top_is_true)
{
	Stack<int> v;
	ASSERT_EQ(v.top(), 0);
}

TEST(Stack, can_pop)
{
	Stack<int> v;
	v.Push(3);
	v.Push(6);
	ASSERT_NO_THROW(v.pop());
}

TEST(Stack, pop_is_true)
{
	Stack<int> v;
	v.Push(3);
	v.Push(6);
	ASSERT_EQ(v.pop(), 6);
}

TEST(Stack, can_create_empty_stack)
{
	Stack<int> v(5);
	ASSERT_NO_THROW(v.empty());
}

TEST(Stack, empty_is_true)
{
	Stack<int> v(5);
	ASSERT_EQ(v.empty(), true);
}