#include <gtest.h>
#include "stack.h"

TEST(Stack , testing_the_constructor_functionality){
    EXPECT_NO_THROW(Stack<int> a);
}

TEST(Stack , testing_the_constructor_functionality_with_digit){
    EXPECT_NO_THROW(Stack<int> a(4));
}

TEST(Stack , testing_the_constructor_with_negative){
    EXPECT_ANY_THROW(Stack<int> a(-1));
}
TEST(Stack , testing_the_constructor_functionality_with_stack){
    Stack<int> a(3);
    EXPECT_NO_THROW(Stack<int> b(a));
}
TEST(Stack , testing_the_constructor_with_stack){
    Stack<int> a(1);
    a.Push(3);

    Stack<int> b(a);
    EXPECT_EQ(a.top(), b.top());
}
TEST(Stack , testing_push){
    Stack<int> a(3);
    EXPECT_NO_THROW(a.Push(12));
}
TEST(Stack , testing_push_correct){
    Stack<int> a;
    a.Push(12);
    EXPECT_EQ(12,a.top());
}

TEST(Stack , testing_pop){
    Stack<int> a(3);
    a.Push(4);
    EXPECT_EQ(a.pop(), 4);
}

TEST(Stack , testing_pop_correct){
    Stack<int> a;
    a.Push(1);
    a.Push(3);
    a.pop();
    EXPECT_EQ(a.top(), 1);
}

TEST(Stack , testing_top){
    Stack<int> a(3);
    a.Push(12);
    EXPECT_NO_THROW(a.top());
}
TEST(Stack , testing_top_correct){
    Stack<int> a(3);
    a.Push(1212);
    EXPECT_EQ(1212,a.top());
}
TEST(Stack , testing_empty){
    Stack<int> a(3);
    EXPECT_TRUE(a.empty());
}

TEST(Stack , testing_empty_correct){
    Stack<int> a(3);
    a.Push(3);
    EXPECT_FALSE(a.empty());
}
TEST(Stack , testing_size){
    Stack<int> a(3);
    EXPECT_NO_THROW(a.Size());
}
TEST(Stack , testing_size_correct){
    Stack<int> a;
    EXPECT_EQ(0, a.Size());
}

TEST(Stack , testing_eq){
    Stack<int> a;
    Stack<int> b;
    a.Push(1);
    b.Push(1);
    EXPECT_TRUE(a == b);
}
TEST(Stack , testing_ne){
    Stack<int> a;
    Stack<int> b;
    a.Push(1);
    a.Push(12);
    b.Push(1);
    EXPECT_FALSE(a == b);
}