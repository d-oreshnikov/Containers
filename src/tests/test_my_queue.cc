#include <gtest/gtest.h>

#include "../my_containers.h"

TEST(my_queue, empty_constructor) {
    my::queue<int> q;
    ASSERT_EQ(0u, q.size());
    ASSERT_TRUE(q.empty());
}

TEST(my_queue, initializer_list_constructor) {
    my::queue<int> q{1, 2, 3, 4, 5};
    ASSERT_EQ(5u, q.size());
    ASSERT_FALSE(q.empty());
}

TEST(my_queue, copy_constructor) {
    my::queue<int> q1{1, 2, 3, 4, 5};
    my::queue<int> q2(q1);
    ASSERT_EQ(5u, q2.size());
    ASSERT_FALSE(q2.empty());
}

TEST(my_queue, move_constructor) {
    my::queue<int> q1{1, 2, 3, 4, 5};
    my::queue<int> q2(std::move(q1));
    ASSERT_EQ(5u, q2.size());
    ASSERT_FALSE(q2.empty());
}

TEST(my_queue, move_assignment) {
    my::queue<int> q1{1, 2, 3, 4, 5};
    my::queue<int> q2;
    q2 = std::move(q1);
    ASSERT_EQ(5, int(q2.size()));
    ASSERT_FALSE(q2.empty());
}

TEST(my_queue, front) {
    my::queue<int> q{1, 2, 3, 4, 5};
    ASSERT_EQ(1, q.front());
}

TEST(my_queue, back) {
    my::queue<int> q{1, 2, 3, 4, 5};
    ASSERT_EQ(5, q.back());
}

TEST(my_queue, empty) {
    my::queue<int> q;
    ASSERT_TRUE(q.empty());
    q.push(1);
    ASSERT_FALSE(q.empty());
}

TEST(my_queue, size) {
    my::queue<int> q;
    ASSERT_EQ(0u, q.size());
    q.push(1);
    ASSERT_EQ(1u, q.size());
}

TEST(my_queue, push) {
    my::queue<int> q;
    q.push(1);
    ASSERT_EQ(1u, q.size());
    ASSERT_EQ(1, q.front());
    ASSERT_EQ(1, q.back());
    q.push(2);
    ASSERT_EQ(2u, q.size());
    ASSERT_EQ(1, q.front());
    ASSERT_EQ(2, q.back());
}

TEST(my_queue, pop) {
    my::queue<int> q{1, 2, 3, 4, 5};
    q.pop();
    ASSERT_EQ(4u, q.size());
    ASSERT_EQ(2, q.front());
    ASSERT_EQ(5, q.back());
}

TEST(my_queue, swap) {
    my::queue<int> q1{1, 2, 3, 4, 5};
    my::queue<int> q2{6, 7, 8, 9, 10};
    q1.swap(q2);
    ASSERT_EQ(5u, q1.size());
    ASSERT_EQ(5u, q2.size());
    ASSERT_EQ(6, q1.front());
    ASSERT_EQ(5, q2.back());
}

TEST(my_queue, insert_many) {
  my::queue<int> queue({0, 1, 4, 9});
  queue.insert_many_back(std::move(16), std::move(25), 36);

  EXPECT_EQ(7u, queue.size());

  for (int i = 0; i < 7; ++i, queue.pop()) {
    EXPECT_EQ(i * i, queue.front());
  }
}
