#include "Stack_Queue.h"

#include <gtest.h>

TEST(TStackQueue, can_create_queue_without_values)
{
	ASSERT_NO_THROW(TStackQueue<int> q);
}

TEST(TStackQueue, can_get_queue_size) {
    TStackQueue<int> q;
    q.Push(2);
    EXPECT_EQ(1, q.size());
}

TEST(TStackQueue, can_push) {
    TStackQueue<int> q;
    q.Push(2);
    EXPECT_EQ(2, q.top());
}

TEST(TStackQueue, can_top) {
    TStackQueue<int> q;
    q.Push(2);
    q.Push(5);
    EXPECT_EQ(2, q.top());
}

TEST(TStackQueue, top_in_empty_queue) {
    TStackQueue<int> q;
    ASSERT_ANY_THROW(q.top());
}

TEST(TStackQueue, can_pop) {
    TStackQueue<int> q;
    q.Push(2);
    q.Push(5);
    q.Push(4);
    q.pop();
    EXPECT_EQ(5, q.top());
}

TEST(TStackQueue, pop_in_empty_queue) {
    TStackQueue<int> q;
    ASSERT_ANY_THROW(q.pop());
}

TEST(TStackQueue, can_get_max_value) {
    TStackQueue<int> q;
    q.Push(500);
    q.Push(-2);
    q.Push(200);
    q.Push(5);
    q.pop();
    EXPECT_EQ(200, q.getMax());
}

TEST(TStackQueue, getMax_in_empty_queue) {
    TStackQueue<int> q;
    ASSERT_ANY_THROW(q.getMax());
}

TEST(TStackQueue, can_get_min_value) {
    TStackQueue<int> q;
    q.Push(-500);
    q.Push(-2);
    q.Push(200);
    q.Push(5);
    q.pop();
    EXPECT_EQ(-2, q.getMin());
}

TEST(TStackQueue, getMin_in_empty_queue) {
    TStackQueue<int> q;
    ASSERT_ANY_THROW(q.getMin());
}