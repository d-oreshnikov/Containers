#include <gtest/gtest.h>

#include "../my_containers.h"

TEST(my_stack, empty_constructor) {
    my::stack<int> s;
    ASSERT_EQ(0u, s.size());
    ASSERT_TRUE(s.empty());
}

TEST(my_stack, initializer_list_constructor) {
    my::stack<int> s{1, 2, 3, 4, 5};
    ASSERT_EQ(5u, s.size());
    ASSERT_FALSE(s.empty());
}

TEST(my_stack, copy_constructor) {
    my::stack<int> s1{1, 2, 3, 4, 5};
    my::stack<int> s2(s1);
    ASSERT_EQ(5u, s2.size());
    ASSERT_FALSE(s2.empty());
}

TEST(my_stack, move_constructor) {
    my::stack<int> s1{1, 2, 3, 4, 5};
    my::stack<int> s2(std::move(s1));
    ASSERT_EQ(5u, s2.size());
    ASSERT_FALSE(s2.empty());
}

TEST(my_stack, move_assignment) {
    my::stack<int> s1{1, 2, 3, 4, 5};
    my::stack<int> s2;
    s2 = std::move(s1);
    ASSERT_EQ(5u, s2.size());
    ASSERT_FALSE(s2.empty());
}

TEST(my_stack, top) {
    my::stack<int> s{1, 2, 3, 4, 5};
    ASSERT_EQ(5, s.top());
}

TEST(my_stack, empty) {
    my::stack<int> s;
    ASSERT_TRUE(s.empty());
    s.push(1);
    ASSERT_FALSE(s.empty());
}

TEST(my_stack, size) {
    my::stack<int> s;
    ASSERT_EQ(0u, s.size());
    s.push(1);
    ASSERT_EQ(1u, s.size());
}

TEST(my_stack, push) {
    my::stack<int> s;
    s.push(1);
    ASSERT_EQ(1u, s.size());
    ASSERT_EQ(1, s.top());
    s.push(2);
    ASSERT_EQ(2u, s.size());
    ASSERT_EQ(2, s.top());
}

TEST(my_stack, pop) {
    my::stack<int> s{1, 2, 3, 4, 5};
    s.pop();
    ASSERT_EQ(4u, s.size());
    ASSERT_EQ(4, s.top());
    s.pop();
    ASSERT_EQ(3u, s.size());
    ASSERT_EQ(3, s.top());
}

TEST(my_stack, swap) {
    my::stack<int> s1{1, 2, 3, 4, 5};
    my::stack<int> s2{6, 7, 8, 9, 10};
    s1.swap(s2);
    ASSERT_EQ(5u, s1.size());
    ASSERT_EQ(10, s1.top());
    ASSERT_EQ(5u, s2.size());
    ASSERT_EQ(5, s2.top());
}

TEST(my_stack, insert_many) {
  my::stack<int> stack({0, 1, 4, 9});
  stack.insert_many_front(std::move(16), std::move(25), 36);

  EXPECT_EQ(7u, stack.size());
  for (int i = 6; i >= 0; --i, stack.pop()) {
    EXPECT_EQ(i * i, stack.top());
  }
}
