#include "queue_stack.h"

#include <gtest.h>

TEST(TStackQueue, can_create_queue_without_given_length)
{
  ASSERT_NO_THROW(TStackQueue<int> q);
}

TEST(TStackQueue, can_get_size)
{
  TStackQueue<int> q;
  q.Push(5);
  q.Push(3);

  EXPECT_EQ(2, q.Size());
}

TEST(TStackQueue, top_to_queue_that_have_no_elements)
{
  TStackQueue<int> q;

  EXPECT_ANY_THROW(q.top());
}

TEST(TStackQueue, pop_to_queue_that_has_elements)
{
  TStackQueue<int> q;
  for (int i = 0; i < 4; i++) {
    q.Push(i);
  }
  int val = q.pop();

  EXPECT_EQ(0, val);
  EXPECT_EQ(1, q.top());
  EXPECT_EQ(3, q.Size());
}

TEST(TStackQueue, pop_to_queue_that_has_no_elements)
{
  TStackQueue<int> q;

  EXPECT_ANY_THROW(q.pop());
}

TEST(TStackQueue, can_getmin_of_queue_that_has_elements)
{
  TStackQueue<int> q;
  for (int i = 0; i < 6; i++) {
    q.Push(i);
  }

  EXPECT_EQ(0, q.getMin());
}

TEST(TStackQueue, can_not_getmin_of_queue_that_has_no_elements)
{
  TStackQueue<int> q;
  
  EXPECT_EQ(1, q.isEmpty());
  EXPECT_ANY_THROW(q.getMin());
}

TEST(TStackQueue, can_getmax_of_queue_that_has_elements)
{
  TStackQueue<int> q;
  for (int i = 0; i < 6; i++) {
    q.Push(i);
  }

  EXPECT_EQ(5, q.getMax());
}

TEST(TStackQueue, can_not_getmax_of_queue_that_has_no_elements)
{
  TStackQueue<int> q;

  EXPECT_EQ(1, q.isEmpty());
  EXPECT_ANY_THROW(q.getMax());
}
