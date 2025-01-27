#include "stack.h"

#include <gtest.h>
TEST(stack, can_create_stack_with_positive_size)
{
	ASSERT_NO_THROW(stack<int> st(5));
}

TEST(stack, throws_when_create_stack_with_negative_size)
{
	ASSERT_ANY_THROW(stack<int> st(-5));
}

TEST(stack, can_create_copied_stack)
{
  	stack<int> st(10);
  	ASSERT_NO_THROW(stack<int> st1(st));
}

TEST(stack, copied_stack_is_equal_to_source_one)
{
  	stack<int> st1(10);
  	for (int i = 0; i < 10; i++) {
    	st1.push(i);
  	}
  	stack<int> st2(st1);
  	EXPECT_EQ(st1, st2);
}

TEST(stack, copied_stack_has_its_own_memory)
{
  	stack<int> st1(5);
  	stack<int> st2(st1);
  	st1.push(4);
  	st2.push(-4);
  	ASSERT_NE(st2.top(), st1.top());
}

TEST(stack, can_get_size)
{
  	stack<int> st(4);
  	EXPECT_EQ(4, st.getMaxSize());
}

TEST(stack, can_push_and_getTop_element)
{
	size_t size = 4;
	stack<int> st(size);
	EXPECT_EQ(0, st.getSize());
	st.push(4);
	EXPECT_EQ(1, st.getSize());
	EXPECT_EQ(size, st.getMaxSize());
	EXPECT_EQ(4, st.top());
}

TEST(stack, can_pop_element)
{
	size_t size = 4;
	stack<int> st(size);
	st.push(4);
	st.push(90);
	st.push(-12);
	EXPECT_EQ(3, st.getSize());
 	st.pop();
	EXPECT_EQ(size, st.getMaxSize());
	EXPECT_EQ(2, st.getSize());
	EXPECT_EQ(90, st.top());
}

TEST(stack, throws_when_stack_is_empty)
{
	stack<int> st{};
	ASSERT_ANY_THROW(st.top());
}

TEST(stack, can_assign_stack_to_itself)
{
	size_t size = 5;
	stack<int> st(size);
	st.push(1);
	st.push(4);
	st.push(7);
	stack<int> exp(st);
	st = st;
	EXPECT_EQ(exp, st);
}

TEST(stack, can_assign_stacks_of_equal_size)
{
	int size = 5;
	stack<int> st1(size);
	stack<int> st2(size);
	st1.push(1);
	st1.push(3);
	st1.push(5);
	ASSERT_NO_THROW(st2 = st1;);
	st2 = st1;
	EXPECT_EQ(st2, st1);
}

TEST(stack, assign_operator_change_stack_size)
{
	int size_1 = 5;
	stack<int> st1(size_1);
	for (size_t i = 0; i < size_1; i++) {
		st1.push(i);
	}

	EXPECT_EQ(size_1, st1.getSize());
	EXPECT_EQ(size_1, st1.getMaxSize());


	int size_2 = size_1 * 2;
	stack<int> st2(size_2);
	for (size_t i = 0; i < size_2; i++){
		st2.push(i);
	}
	EXPECT_EQ(size_2, st2.getSize());
	EXPECT_EQ(size_2, st2.getMaxSize());


  	st1 = st2;
	EXPECT_EQ(st1, st2);
	EXPECT_EQ(size_2, st1.getSize());
	EXPECT_EQ(size_2, st1.getMaxSize());
}

TEST(stack, can_assign_stacks_of_different_size)
{
	size_t size_1 = 5;
	size_t size_2 = 10;
	stack<int> st1(size_1);
	st1.push(1);
	st1.push(2);
	st1.push(3);
	stack<int> st2(size_2);
	st2 = st1;
	EXPECT_EQ(st1, st2);
	EXPECT_EQ(size_2, st2.getMaxSize());
	EXPECT_EQ(3, st2.getSize());

	size_t size_3 = 10;
	size_t size_4 = 5;
	stack<int> st3(size_3);
	stack<int> st4(size_4);
	st3.push(1);
	st3.push(2);
	st3.push(3);
	st3.push(4);
	st3.push(5);
	st3.push(6);
	st4 = st3;
	EXPECT_EQ(st4, st3);
	EXPECT_EQ(size_4 * 2, st4.getMaxSize());
	EXPECT_EQ(6, st4.getSize());
}

TEST(stack, compare_equal_stacks_return_true)
{
	size_t size = 5;
  	stack<int> st1(size);
	st1.push(0);
	st1.push(2);
	st1.push(4);
  	stack<int> exp(size);
	exp.push(0);
	exp.push(2);
	exp.push(4);

  EXPECT_EQ(true, exp == st1);
}

TEST(stack, compare_stack_with_itself_return_true)
{
 	size_t size = 5;
  	stack<int> st1(size);
 	st1.push(0);
  	st1.push(2);
  	st1.push(4);
  	EXPECT_EQ(true, st1 == st1);
}

TEST(stack, stacks_with_different_element_count_are_not_equal) {
	size_t size_1 = 5;
	size_t size_2 = 5;
	stack<int> st1(size_1);
	st1.push(1);
	st1.push(2);
	st1.push(3);
	stack<int> st2(size_2);
	EXPECT_NE(true, st1 == st2);
}

TEST(stack, push_new_element_to_full_stack_change_it_size) {
	size_t maxSize = 3;
	stack<int> full(maxSize);
	full.push(0);
	full.push(1);
	full.push(2);
	
	full.push(4);
	EXPECT_EQ(4, full.getSize());
	EXPECT_EQ(maxSize * 2, full.getMaxSize());
	EXPECT_EQ(4, full.top());
}