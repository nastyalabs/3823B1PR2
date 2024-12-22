#include "Queue.h"

#include <gtest.h>

TEST(TQueue, can_create_queue_without_values)
{
	ASSERT_NO_THROW(TQueue<int> q());
}

TEST(TQueue, can_create_queue_with_positive_size)
{
	ASSERT_NO_THROW(TQueue<int> s(5));
}

TEST(TQueue, throw_when_create_queue_with_negative_size)
{
  ASSERT_ANY_THROW(TQueue<int> s(-5));
}

TEST(TQueue, can_push_and_copy_queue)
{
    TQueue<int> s(5);
    s.Push(2);

    TQueue<int> s1(s);

    EXPECT_EQ(2, s1.top());
}

TEST(TQueue, can_push_neg_elem_and_get_top_element)
{
    TQueue<int> s(2);
    s.Push(-3);

    EXPECT_EQ(-3, s.top());
}

TEST(TQueue, throw_then_get_top_element_in_empty_queue)
{
    TQueue<int> s(5);

    ASSERT_ANY_THROW(s.top());
}

TEST(TQueue, push_elem_in_full_queue) {
    TQueue<int> s(5);
    for (int i = 0; i < 6; i++) {
        s.Push(8);
    }

    EXPECT_EQ(8, s.top());
    EXPECT_EQ(10, s.Size());
}

TEST(TQueue, can_pop_not_empty_queue) {
    TQueue<int> s(5);
    s.Push(9);
    s.Push(-8);
    s.pop();

    EXPECT_EQ(9, s.top());
}

TEST(TQueue, throw_pop_in_empty_queue) {
    TQueue<int> s(5);

    ASSERT_ANY_THROW(s.pop());
}

TEST(TQueue, equal_queue) {
    TQueue<int> s(3);
    TQueue<int> s1(3);
    s.Push(-1);
    s.Push(5);
    s1.Push(-1);
    s1.Push(5);

    EXPECT_EQ(true, s == s1);
}

TEST(TQueue, equal_empty_queues) {
    TQueue<int> s(3);
    TQueue<int> s1(3);

    EXPECT_EQ(true, s == s1);
}

TEST(TQueue, equal_queues_with_different_queues) {
    TQueue<int> s(4);
    TQueue<int> s1(3);
    s.Push(88);
    s1.Push(88);

    EXPECT_EQ(true, s == s1);
}

TEST(TQueue, not_equal_queues_with_different_sizes) {
    TQueue<int> s(1);
    TQueue<int> s1(2);
    s.Push(88);
    s1.Push(88);
    s1.Push(99);

    EXPECT_EQ(false, s == s1);
}
