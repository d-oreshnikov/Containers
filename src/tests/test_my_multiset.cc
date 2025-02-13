#include <gtest/gtest.h>

#include "../my_containers_plus.h"

TEST(my_multiset, empty_constructor) {
  my::multiset<int> s;
  ASSERT_EQ(0u, s.size());
  ASSERT_TRUE(s.empty());
}

TEST(my_multiset, initializer_constructor) {
  my::multiset<int> ms = {
    54, 93, 23, 23, 23, 02, 29, 67, 83, 83, 83, 83, 83, 13
  };
  ASSERT_EQ(14u, ms.size());
  ASSERT_FALSE(ms.empty());
}

TEST(my_multiset, copy_contructor) {
  my::multiset<int> ms1 = {
    54, 93, 23, 23, 23, 02, 29, 67, 83, 83, 83, 83, 83, 13
  };
  my::multiset<int> ms2(ms1);
  ASSERT_EQ(14u, ms2.size());
  ASSERT_FALSE(ms2.empty());
}

TEST(my_multiset, move_constructor) {
  my::multiset<int> ms1 = {
    54, 93, 23, 23, 23, 02, 29, 67, 83, 83, 83, 83, 83, 13
  };
  my::multiset<int> ms2(std::move(ms1));
  ASSERT_EQ(14u, ms2.size());
  ASSERT_FALSE(ms2.empty());
}

TEST(my_multiset, move_assigment) {
  my::multiset<int> ms1 = {
    54, 93, 23, 23, 23, 02, 29, 67, 83, 83, 83, 83, 83, 13
  };
  my::multiset<int> ms2;
  ms2 = std::move(ms1);
  ASSERT_EQ(14u, ms2.size());
  ASSERT_FALSE(ms2.empty());
}

TEST(my_multiset, iterator) {
  my::multiset<int> ms = {
    54, 93, 23, 23, 23, 02, 29, 67, 83, 83, 83, 83, 83, 13
  };
  my::multiset<int>::iterator it = ms.begin();
  ASSERT_EQ(02, it.cget());
  ++it;
  ASSERT_EQ(13, it.cget());
  ++it;
  ASSERT_EQ(23, it.cget());
  ++it;
  ASSERT_EQ(23, it.cget());
  it.last_node();
  ASSERT_EQ(93, it.cget());
  ++it;
  ASSERT_EQ(02, it.cget());
  --it;
  ASSERT_EQ(93, it.cget());
  --it;
  ASSERT_EQ(83, it.cget());
  --it;
  ASSERT_EQ(83, it.cget());
}

TEST(my_multiset, clear) {
  my::multiset<int> ms = {
    54, 93, 23, 23, 23, 02, 29, 67, 83, 83, 83, 83, 83, 13
  };
  ASSERT_EQ(14u, ms.size());
  ASSERT_FALSE(ms.empty());
  ms.clear();
  ASSERT_TRUE(ms.empty());
}

TEST(my_multiset, insert) {
  my::multiset<int> ms = {
    54, 93, 23, 23, 23, 02, 29, 67, 83, 83, 83, 83, 83, 13
  };
  my::multiset<int>::iterator it = ms.begin();
  auto res1 = ms.insert(40);
  ASSERT_EQ(res1, it.set(40));
  auto res2 = ms.insert(41);
  ASSERT_EQ(res2, it.set(41));
  auto res3 = ms.insert(40);
  ASSERT_EQ(res3, it.set(40));
  ASSERT_TRUE(ms.contains(40));
}

TEST(my_multiset, erase) {
  my::multiset<int> ms = {
    54, 93, 23, 23, 23, 02, 29, 67, 83, 83, 83, 83, 83, 13
  };
  my::multiset<int>::iterator it = ms.begin();
  ++it;
  ++it;
  ++it;
  ++it;
  ASSERT_EQ(23, it.cget());
  ASSERT_TRUE(ms.contains(23));
  my::multiset<int>::iterator it2 = ms.erase(it);
  ASSERT_EQ(29, it2.cget());
}

TEST(my_multiset, merge) {
  my::multiset<int> ms1 = {
    67, 83, 83, 83, 83, 83, 13
  };
  my::multiset<int> ms2 = {
    54, 93, 23, 23, 23, 02, 29, 67
  };
  ASSERT_EQ(7u, ms1.size());
  ASSERT_EQ(8u, ms2.size());
  ms1.merge(ms2);
  ASSERT_EQ(15u, ms1.size());
}

TEST(my_multiset, find) {
  my::multiset<int> ms = {
    54, 93, 23, 23, 23, 02, 29, 67, 83, 83, 83, 83, 83, 13
  };
  my::multiset<int>::iterator it1 = ms.find(67);
  ASSERT_EQ(it1.cget(), 67);
  my::multiset<int>::iterator it2 = ms.find(100);
  ASSERT_EQ(it2.cget(), 93);
}

TEST(my_multiset, count) {
  my::multiset<int> ms = {
    54, 93, 23, 23, 23, 02, 29, 67, 83, 83, 83, 83, 83, 13
  };
  auto count = ms.count(83);
  ASSERT_EQ(5u, count);
}

TEST(my_multiset, equal_range) {
  my::multiset<int> ms = {
    54, 93, 23, 23, 23, 02, 29, 67, 83, 83, 83, 83, 83, 13
  };
  auto pos = ms.equal_range(83);
  ASSERT_EQ(pos.first.cget(), 83);
  ASSERT_EQ(pos.second.cget(), 93);
}

TEST(my_multiset, bounds) {
  my::multiset<int> ms = {
    54, 93, 23, 23, 23, 02, 29, 67, 83, 83, 83, 83, 83, 13
  };
  my::multiset<int>::iterator it1 = ms.lower_bound(23);
  my::multiset<int>::iterator it2 = ms.upper_bound(23);
  ASSERT_EQ(29, it1.cget());
  ASSERT_EQ(23, it2.cget());
}

TEST(my_multiset, insert_many) {
  my::multiset<int> ms = {
    54, 93, 23, 23, 23, 02, 29, 67, 83, 83, 83, 83, 83, 13
  };
  auto out = ms.insert_many(23, 23, 45, 45, 83);
  ASSERT_EQ(out[0].second, true);
  ASSERT_EQ(out[1].second, true);
  ASSERT_EQ(out[2].second, true);
  ASSERT_EQ(out[3].second, true);
  ASSERT_EQ(out[4].second, true);
}
