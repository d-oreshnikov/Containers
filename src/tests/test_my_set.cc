#include <gtest/gtest.h>

#include "../my_containers.h"

TEST(my_set, empty_constructor) {
  my::set<int> s;
  ASSERT_EQ(0u, s.size());
  ASSERT_TRUE(s.empty());
}

TEST(my_set, initializer_constructor) {
  my::set<int> s = {
    54, 93, 23, 58, 12, 02, 29, 67, 83, 71, 39, 91, 47, 13
  };
  ASSERT_EQ(14u, s.size());
  ASSERT_FALSE(s.empty());
}

TEST(my_set, copy_contructor) {
  my::set<int> s1 = {
    54, 93, 23, 58, 12, 02, 29, 67, 83, 71, 39, 91, 47, 13
  };
  my::set<int> s2(s1);
  ASSERT_EQ(14u, s2.size());
  ASSERT_FALSE(s2.empty());
}

TEST(my_set, move_constructor) {
  my::set<int> s1 = {
    54, 93, 23, 58, 12, 02, 29, 67, 83, 71, 39, 91, 47, 13
  };
  my::set<int> s2(std::move(s1));
  ASSERT_EQ(14u, s2.size());
  ASSERT_FALSE(s2.empty());
}

TEST(my_set, move_assigment) {
  my::set<int> s1 = {
    54, 93, 23, 58, 12, 02, 29, 67, 83, 71, 39, 91, 47, 13
  };
  my::set<int> s2;
  s2 = std::move(s1);
  ASSERT_EQ(14u, s2.size());
  ASSERT_FALSE(s2.empty());
}

TEST(my_set, iterator) {
  my::set<int> s = {
    54, 93, 23, 58, 12, 02, 29, 67, 83, 71, 39, 91, 47, 13
  };
  my::set<int>::iterator it = s.begin();
  ASSERT_EQ(02, it.cget());
  ++it;
  ASSERT_EQ(12, it.cget());
  ++it;
  ASSERT_EQ(13, it.cget());
  it.last_node();
  ASSERT_EQ(93, it.cget());
  ++it;
  ASSERT_EQ(02, it.cget());
  --it;
  ASSERT_EQ(93, it.cget());
}

TEST(my_set, clear) {
  my::set<int> s = {
    54, 93, 23, 58, 12, 02, 29, 67, 83, 71, 39, 91, 47, 13
  };
  ASSERT_EQ(14u, s.size());
  ASSERT_FALSE(s.empty());
  s.clear();
  ASSERT_TRUE(s.empty());
}

TEST(my_set, insert) {
  my::set<int> s = {
    54, 93, 23, 58, 12, 02, 29, 67, 83, 71, 39, 91, 47, 13
  };
  my::set<int>::iterator it = s.begin();
  auto res1 = s.insert(40);
  ASSERT_EQ(res1, std::make_pair(it.set(40), true));
  auto res2 = s.insert(41);
  ASSERT_EQ(res2, std::make_pair(it.set(41), true));
  auto res3 = s.insert(40);
  ASSERT_EQ(res3, std::make_pair(it.set(40), false));
  ASSERT_TRUE(s.contains(40));
}

TEST(my_set, erase) {
  my::set<int> s = {
    54, 93, 23, 58, 12, 02, 29, 67, 83, 71, 39, 91, 47, 13
  };
  my::set<int>::iterator it = s.begin();
  ++it;
  ++it;
  ++it;
  ++it;
  ++it;
  ASSERT_EQ(39, it.cget());
  ASSERT_TRUE(s.contains(39));
  my::set<int>::iterator it2 = s.erase(it);
  ASSERT_FALSE(s.contains(39));
  ASSERT_EQ(47, it2.cget());
}

TEST(my_set, merge) {
  my::set<int> s1 = {
    54, 93, 23, 58, 12, 02, 29, 67
  };
  my::set<int> s2 = {
    67, 83, 71, 39, 91, 47, 13
  };
  ASSERT_EQ(8u, s1.size());
  ASSERT_EQ(7u, s2.size());
  s1.merge(s2);
  ASSERT_EQ(14u, s1.size());
}

TEST(my_set, find) {
  my::set<int> s = {
    54, 93, 23, 58, 12, 02, 29, 67, 83, 71, 39, 91, 47, 13
  };
  my::set<int>::iterator it1 = s.find(67);
  ASSERT_EQ(it1.cget(), 67);
  my::set<int>::iterator it2 = s.find(100);
  ASSERT_EQ(it2.cget(), 93);
}

TEST(my_set, insert_many) {
  my::set<int> s = {
    54, 93, 23, 58, 12, 02, 29, 67, 83, 71, 39, 91, 47, 13
  };
  ASSERT_EQ(14u, s.size());
  my::set<int>::iterator it = s.begin();
  auto out = s.insert_many(40, 41, 12, 43, 47);
  ASSERT_EQ(out[0], std::make_pair(it.set(40), true));
  ASSERT_EQ(out[1], std::make_pair(it.set(41), true));
  ASSERT_EQ(out[2], std::make_pair(it.set(12), false));
  ASSERT_EQ(out[3], std::make_pair(it.set(43), true));
  ASSERT_EQ(out[4], std::make_pair(it.set(47), false));
}
