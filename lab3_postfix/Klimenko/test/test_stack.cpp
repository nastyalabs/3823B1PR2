#include <gtest.h>
#include "stack.h"

TEST(TDynamicStack, can_clear_the_stack) {
	TDynamicStack<int> stack(25);
	stack.clear();
	ASSERT_NE(stack.isFull(), true);
}

TEST(TDynamicStack, can_create_the_empty_stack) {
	TDynamicStack<int> stack(5000);
	ASSERT_TRUE(stack.isEmpty());
}

TEST(TDynamicStack, can_create_the_stack_of_integers)
{
	ASSERT_NO_THROW(TDynamicStack<int> stack);
}

TEST(TDynamicStack, can_create_the_stack_of_doubles)
{
	ASSERT_NO_THROW(TDynamicStack<double> stack);
}

TEST(TDynamicStack, can_create_the_stack_with_a_positive_length)
{
	ASSERT_NO_THROW(TDynamicStack<int> stack(1000));
}

TEST(TDynamicStack, cant_create_the_stack_with_a_negative_length)
{
	ASSERT_ANY_THROW(TDynamicStack<int> stack(-1000));
}

TEST(TDynamicStack, can_create_the_stack_with_the_other_stack_as_an_argument)
{
	TDynamicStack<int> stack;
	ASSERT_NO_THROW(TDynamicStack<int> one_more_stack(stack));
}

TEST(TDynamicStack, can_expand_the_memory_when_the_stack_is_full) {
	TDynamicStack<int> stack(2000);
	for (int i = 0; i < 2005; i++) {
		stack.push(i);
	}
	EXPECT_EQ(4000, stack.getMemSize());
}

TEST(TDynamicStack, can_fill_the_stack)
{
	TDynamicStack<int> stack(100);
	for (int i = 1; i <= stack.getMemSize(); i++) {
		stack.push(i);
	}
	ASSERT_EQ(stack.isFull(), true);
}

TEST(TDynamicStack, cant_fill_the_stack)
{
	TDynamicStack<int> stack(100);
	for (int i = 1; i < stack.getMemSize(); i++) {
		stack.push(i);
	}
	ASSERT_NE(stack.isFull(), true);
}

TEST(TDynamicStack, can_get_the_memory_size_of_the_stack) {
	TDynamicStack<int> stack(4321);
	ASSERT_EQ(4321, stack.getMemSize());
}

TEST(TDynamicStack, can_get_the_top_value_of_the_stack) {
	TDynamicStack<int> stack(4000);
	stack.push(1);
	ASSERT_EQ(1, stack.getTopValue());
}

TEST(TDynamicStack, cant_pop_elements_from_the_empty_stack) {
	TDynamicStack<int> stack(12);
	int elem;
	ASSERT_ANY_THROW(elem == stack.pop());
}

TEST(TDynamicStack, can_pop_elements_from_the_stack) {
	TDynamicStack<int> stack(999);
	int elem = 55;
	stack.push(elem);
	ASSERT_EQ(55, stack.pop());
}

TEST(TDynamicStack, can_push_elements_to_the_stack) {
	TDynamicStack<int> stack(999);
	int elem = 10;
	ASSERT_NO_THROW(stack.push(elem));
}