#include "queue_base.h"

#include <gtest.h>

TEST(TQueue, can_create_queue_without_given_length)
{
  ASSERT_NO_THROW(TQueue<int> q());
}

TEST(TQueue, can_create_queue_with_positive_length)
{
  ASSERT_NO_THROW(TQueue<int> q(5));
}

TEST(TQueue, throws_when_create_queue_with_negative_length)
{
  ASSERT_ANY_THROW(TQueue<int> q(-5));
}

TEST(TQueue, can_create_copied_queue)
{
  TQueue<int> q(10);

  ASSERT_NO_THROW(TQueue<int> q1(q));
}

TEST(TQueue, copied_queue_is_equal_to_source_one)
{
  TQueue<int> q(10);
  TQueue<int> q1(q);

  EXPECT_EQ(true, (q1 == q));
}

TEST(TQueue, copied_queue_has_its_own_memory)
{
  TQueue<int> q(10);
  TQueue<int> q1(q);

  EXPECT_NE(&q, &q1);
}

TEST(TQueue, can_assign_queue_to_itself)
{
  TQueue<int> q(5);
  for (size_t i = 0; i < 10; i++) {  // additional test for incresing allocated memory
    q.Push(i);
  }
  q = q;

  EXPECT_EQ(0, q.top());
}

TEST(TQueue, can_assign_queues_of_equal_size)
{
  size_t size_st = 10;
  TQueue<int> q(size_st);
  TQueue<int> q1(size_st);
  for (size_t i = 0; i < q1.Size(); i++) {
    q1.Push(i);
  }
  q = q1;

  EXPECT_EQ(0, q.top());
}

TEST(TQueue, assign_operator_change_queue_size)
{
  TQueue<int> q(10);
  TQueue<int> q1(12);
  for (size_t i = 0; i < q1.Size(); i++) {
    q1.Push(i);
  }
  q = q1;

  EXPECT_EQ(12, q.Size());
}

TEST(TQueue, can_assign_queues_of_different_size)
{
  TQueue<int> q(10);
  TQueue<int> q1(12);
  for (size_t i = 0; i < q1.Size(); i++) {
    q1.Push(i+1);
  }
  q = q1;

  EXPECT_EQ(1, q.top());
}

TEST(TQueue, can_get_size)
{
  TQueue<int> q(4);

  EXPECT_EQ(4, q.Size());
}

TEST(TQueue, compare_equal_queues_return_true)
{
  size_t size_st = 10;
  TQueue<int> q(size_st);
  TQueue<int> q1(size_st);
  for (size_t i = 0; i < q1.Size(); i++) {
    q.Push(i);
    q1.Push(i);
  }

  EXPECT_EQ(true, (q1 == q));
}

TEST(TQueue, compare_queue_with_itself_return_true)
{
  TQueue<int> q(10);

  EXPECT_EQ(true, (q == q));
}

TEST(TQueue, queues_with_different_size_are_equal)
{
  TQueue<int> q(10);
  TQueue<int> q1(12);

  EXPECT_EQ(true, (q == q1));
}

TEST(TQueue, push_to_queue_that_has_enough_memory)
{
  TQueue<int> q(10);
  q.Push(2);
  q.Push(4);

  EXPECT_EQ(2, q.top());
}

TEST(TQueue, push_to_queue_that_has_not_enough_memory)
{
  TQueue<int> q(10);
  for (size_t i = 0; i < q.Size(); i++) {
    q.Push(i);
  }
  q.Push(4);

  EXPECT_EQ(0, q.top());
  EXPECT_EQ(20, q.Size());
}

TEST(TQueue, top_to_queue_that_have_no_elements)
{
  TQueue<int> q(10);

  EXPECT_ANY_THROW(q.top());
}

TEST(TQueue, pop_to_queue_that_has_elements)
{
  TQueue<int> q(10);
  for (size_t i = 0; i < q.Size(); i++) {
    q.Push(i);
  }
  int val = q.pop();

  EXPECT_EQ(0, val);
  EXPECT_EQ(1, q.top());
  EXPECT_EQ(10, q.Size());
}

TEST(TQueue, pop_to_queue_that_has_no_elements)
{
  TQueue<int> q(10);

  EXPECT_ANY_THROW(q.pop());
}
