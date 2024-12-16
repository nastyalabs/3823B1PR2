#include "list.h"

#include <gtest.h>

using namespace std;

TEST(TList, can_create_TList_without_given_length)
{
  ASSERT_NO_THROW(TList<int> l);
}

TEST(TList, can_create_copied_list)
{
  TList<int> l;

  ASSERT_NO_THROW(TList<int> l1(l));
}

TEST(TList, copied_list_is_equal_to_source_one)
{
  TList<int> l;
  TList<int> l1(l);

  EXPECT_EQ(true, l.isEmpty());
  EXPECT_EQ(true, l1.isEmpty());
  EXPECT_EQ(true, (l1 == l));
  EXPECT_ANY_THROW(l.getHead());
}

TEST(TList, copied_list_has_its_own_memory)
{
  TList<int> l;
  TList<int> l1(l);

  EXPECT_EQ(0, l.getSize());
  EXPECT_NE(&l, &l1);
}

TEST(TList, copied_list_has_is_equal_to_source)
{
  TList<int> l;
  for (size_t i = 0; i < 5; i++) {
    l.insert(i, to_string(i), i);
  }
  TList<int> l1(l);

  EXPECT_EQ(0, l1.getHead());
  EXPECT_EQ(2, l1.search(2));
}

TEST(TList, can_assign_list_to_itself)
{
  TList<int> l;
  for (size_t i = 0; i < 5; i++) {
    l.insert(i, to_string(i), i);
  }
  l = l;

  EXPECT_EQ(0, l.getHead());
  EXPECT_EQ(2, l.search(2));
}

TEST(TList, can_assign_lists_of_equal_size)
{
  TList<int> l;
  TList<int> l1;
  for (size_t i = 0; i < 5; i++) {
    l.insert(i, to_string(i), i);
    l1.insert(i, to_string(i), i+1);
  }
  l = l1;

  EXPECT_EQ(3, l.search(2));
}

TEST(TList, assign_operator_change_list_size)
{
  TList<int> l;
  TList<int> l1;
  for (size_t i = 0; i < 5; i++) {
    l.insert(i, to_string(i), i);
    l1.insert(i, to_string(i), i+1);
  }
  l1.insert(5, "111", 5);
  l = l1;

  EXPECT_EQ(6, l.getSize());
  EXPECT_EQ(5, l.search(5));
}

TEST(TList, compare_equal_lists_return_true)
{
  TList<int> l;
  TList<int> l1;
  for (size_t i = 0; i < 5; i++) {
    l.insert(i, to_string(i), i);
    l1.insert(i, to_string(i), i);
  }

  EXPECT_EQ(true, (l1 == l));
}

TEST(TList, compare_list_with_itself_return_true)
{
  TList<int> l;

  EXPECT_EQ(true, (l == l));
}

TEST(TList, can_use_iterators_to_change_list)
{
  TList<int> l;
  for (size_t i = 0; i < 5; i++) {
    l.insert(i, to_string(i), i);
  }
  int val = 10;
  for (TList<int>::Iterator i = l.begin(); i != l.end(); i++) {
    *i = val++;
  }

  EXPECT_EQ(11, l.search(1));
  EXPECT_EQ(12, l.search(2));
}

TEST(TList, insert_to_list_with_wrong_index)
{
  TList<int> l;

  EXPECT_ANY_THROW(l.insert(2, "100", 10));
}

TEST(TList, delete_to_list_with_correct_index)
{
  TList<int> l;
  for (size_t i = 0; i < 5; i++) {
    l.insert(i, to_string(i), i);
  }
  l.Delete(4);
  l.Delete(2);

  EXPECT_EQ(0, l.search(0));
  EXPECT_EQ(1, l.search(1));
  EXPECT_EQ(3, l.search(2));
}

TEST(TList, delete_to_list_with_wrong_index)
{
  TList<int> l;
  for (size_t i = 0; i < 5; i++) {
    l.insert(i, to_string(i), i);
  }

  EXPECT_ANY_THROW(l.Delete(5));
  EXPECT_ANY_THROW(l.Delete(6));
}

TEST(TList, search_to_list_with_wrong_index)
{
  TList<int> l;
  for (size_t i = 0; i < 5; i++) {
    l.insert(i, to_string(i), i);
  }

  EXPECT_ANY_THROW(l.search(5));
  EXPECT_ANY_THROW(l.search(6));
}

TEST(TList, medium_to_list_with_odd_size)
{
  TList<int> l;
  for (size_t i = 0; i < 5; i++) {
    l.insert(i, to_string(i), i);
  }

  EXPECT_EQ(2, l.medium());
}

TEST(TList, medium_to_list_with_even_size)
{
  TList<int> l;
  for (size_t i = 0; i < 6; i++) {
    l.insert(i, to_string(i), i);
  }

  EXPECT_EQ(3, l.medium());
}

TEST(TList, meadium_to_list_with_no_nodes)
{
  TList<int> l;

  EXPECT_ANY_THROW(l.medium());
}
