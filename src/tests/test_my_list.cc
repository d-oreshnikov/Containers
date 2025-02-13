#include <gtest/gtest.h>

#include "../my_containers.h"
#include <list>

TEST(my_list, default_constructor) {
  std::list<int> std_list;
  my::list<int> my_list;

  EXPECT_EQ(std_list.size(), my_list.size());
}

TEST(my_list, parameterized_constructor) {
  std::list<int> std_list(3);
  my::list<int> my_list(3);

  auto my_it = my_list.begin();
  for (auto std_it = std_list.begin(); std_it != std_list.end();
       ++std_it, ++my_it) {
    EXPECT_EQ(*std_it, *my_it);
  }

  EXPECT_EQ(std_list.size(), my_list.size());
}

TEST(my_list, list_constructor) {
  std::list<int> std_list = {1, 2, 3};
  my::list<int> my_list = {1, 2, 3};

  auto my_it = my_list.begin();
  for (auto std_it = std_list.begin(); std_it != std_list.end();
       ++std_it, ++my_it) {
    EXPECT_EQ(*std_it, *my_it);
  }

  EXPECT_EQ(std_list.size(), my_list.size());
}

TEST(my_list, copy_constructor) {
  std::list<int> std_list1 = {1, 2, 3};
  my::list<int> my_list1 = {1, 2, 3};

  std::list<int> std_list2(std_list1);
  my::list<int> my_list2(my_list1);

  auto my_it = my_list2.begin();
  for (auto std_it = std_list2.begin(); std_it != std_list2.end();
       ++std_it, ++my_it) {
    EXPECT_EQ(*std_it, *my_it);
  }

  EXPECT_EQ(std_list2.size(), my_list2.size());
}

TEST(my_list, move_constructor) {
  std::list<int> std_list1 = {1, 2, 3};
  my::list<int> my_list1 = {1, 2, 3};

  std::list<int> std_list2(std::move(std_list1));
  my::list<int> my_list2(std::move(my_list1));

  auto my_it = my_list2.begin();
  for (auto std_it = std_list2.begin(); std_it != std_list2.end();
       ++std_it, ++my_it) {
    EXPECT_EQ(*std_it, *my_it);
  }

  EXPECT_EQ(std_list2.size(), my_list2.size());
}

TEST(my_list, copy_operator) {
  std::list<int> std_list1 = {1, 2, 3};
  my::list<int> my_list1 = {1, 2, 3};

  std::list<int> std_list2 = {5, 4, 3, 2, 1};
  my::list<int> my_list2 = {5, 4, 3, 2, 1};

  std_list2 = std_list1;
  my_list2 = my_list1;

  auto my_it = my_list2.begin();
  for (auto std_it = std_list2.begin(); std_it != std_list2.end();
       ++std_it, ++my_it) {
    EXPECT_EQ(*std_it, *my_it);
  }

  EXPECT_EQ(std_list2.size(), my_list2.size());
}

TEST(my_list, move_operator) {
  std::list<int> std_list1 = {1, 2, 3};
  my::list<int> my_list1 = {1, 2, 3};

  std::list<int> std_list2 = {5, 4, 3, 2, 1};
  my::list<int> my_list2 = {5, 4, 3, 2, 1};

  std_list2 = std::move(std_list1);
  my_list2 = std::move(my_list1);

  auto my_it = my_list2.begin();
  for (auto std_it = std_list2.begin(); std_it != std_list2.end();
       ++std_it, ++my_it) {
    EXPECT_EQ(*std_it, *my_it);
  }

  EXPECT_EQ(std_list2.size(), my_list2.size());
}

TEST(my_list, front_function) {
  std::list<int> std_list1 = {1, 2, 3};
  my::list<int> my_list1 = {1, 2, 3};

  EXPECT_EQ(std_list1.front(), my_list1.front());

  std::list<int> std_list2;
  my::list<int> my_list2;

  EXPECT_EQ(std_list2.front(), my_list2.front());
}

TEST(my_list, back_function) {
  std::list<int> std_list1 = {1, 2, 3};
  my::list<int> my_list1 = {1, 2, 3};

  EXPECT_EQ(std_list1.back(), my_list1.back());

  std::list<int> std_list2;
  my::list<int> my_list2;

  EXPECT_EQ(std_list2.back(), my_list2.back());
}

TEST(my_list, begin_function) {
  std::list<int> std_list1 = {1, 2, 3};
  my::list<int> my_list1 = {1, 2, 3};

  EXPECT_EQ(*std_list1.begin(), *my_list1.begin());

  std::list<int> std_list2;
  my::list<int> my_list2;

  EXPECT_EQ(*std_list2.begin(), *my_list2.begin());
}

TEST(my_list, cbegin_function) {
  std::list<int> std_list1 = {1, 2, 3};
  my::list<int> my_list1 = {1, 2, 3};

  EXPECT_EQ(*std_list1.cbegin(), *my_list1.cbegin());

  std::list<int> std_list2;
  my::list<int> my_list2;

  EXPECT_EQ(*std_list2.cbegin(), *my_list2.cbegin());
}

TEST(my_list, end_function) {
  std::list<int> std_list1 = {1, 2, 3};
  my::list<int> my_list1 = {1, 2, 3};

  EXPECT_EQ(*(--std_list1.end()), *(--my_list1.end()));

  std::list<int> std_list2;
  my::list<int> my_list2;

  EXPECT_EQ(*std_list2.end(), *my_list2.end());
}

TEST(my_list, cend_function) {
  std::list<int> std_list1 = {1, 2, 3};
  my::list<int> my_list1 = {1, 2, 3};

  EXPECT_EQ(*(--std_list1.cend()), *(--my_list1.cend()));

  std::list<int> std_list2;
  my::list<int> my_list2;

  EXPECT_EQ(*std_list2.cend(), *my_list2.cend());
}

TEST(my_list, empty_function) {
  std::list<int> std_list1 = {1, 2, 3};
  my::list<int> my_list1 = {1, 2, 3};

  EXPECT_EQ(std_list1.empty(), my_list1.empty());

  std::list<int> std_list2;
  my::list<int> my_list2;

  EXPECT_EQ(std_list2.empty(), my_list2.empty());
}

TEST(my_list, size_function) {
  std::list<int> std_list1 = {1, 2, 3};
  my::list<int> my_list1 = {1, 2, 3};

  EXPECT_EQ(std_list1.size(), my_list1.size());

  std::list<int> std_list2;
  my::list<int> my_list2;

  EXPECT_EQ(std_list2.size(), my_list2.size());
}

TEST(my_list, max_size_function) {
  std::list<int> std_list1 = {1, 2, 3};
  my::list<int> my_list1 = {1, 2, 3};

  EXPECT_EQ(std_list1.max_size(), my_list1.max_size());

  std::list<int> std_list2;
  my::list<int> my_list2;

  EXPECT_EQ(std_list2.max_size(), my_list2.max_size());
}

TEST(my_list, clear_function) {
  std::list<int> std_list1 = {1, 2, 3};
  my::list<int> my_list1 = {1, 2, 3};

  EXPECT_EQ(std_list1.size(), my_list1.size());

  std_list1.clear();
  my_list1.clear();

  EXPECT_EQ(std_list1.size(), my_list1.size());
}

TEST(my_list, insert_function) {
  std::list<int> std_list1 = {1, 2, 3};
  my::list<int> my_list1 = {1, 2, 3};

  EXPECT_EQ(std_list1.size(), my_list1.size());

  auto std_pos = std_list1.insert(std_list1.begin(), 0);
  auto my_pos = my_list1.insert(my_list1.begin(), 0);

  EXPECT_EQ(std_list1.size(), my_list1.size());
  EXPECT_EQ(*std_pos, *my_pos);

  auto my_it = my_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++my_it) {
    EXPECT_EQ(*std_it, *my_it);
  }

  std_pos = std_list1.insert(--std_list1.end(), 0);
  my_pos = my_list1.insert(--my_list1.end(), 0);

  EXPECT_EQ(std_list1.size(), my_list1.size());
  EXPECT_EQ(*std_pos, *my_pos);

  my_it = my_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++my_it) {
    EXPECT_EQ(*std_it, *my_it);
  }
}

TEST(my_list, erase_function) {
  std::list<int> std_list1 = {1, 2, 3, 4, 5};
  my::list<int> my_list1 = {1, 2, 3, 4, 5};

  EXPECT_EQ(std_list1.size(), my_list1.size());

  std_list1.erase(std_list1.begin());
  my_list1.erase(my_list1.begin());

  EXPECT_EQ(std_list1.size(), my_list1.size());

  auto my_it = my_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++my_it) {
    EXPECT_EQ(*std_it, *my_it);
  }

  std_list1.erase(--std_list1.end());
  my_list1.erase(--my_list1.end());

  EXPECT_EQ(std_list1.size(), my_list1.size());

  my_it = my_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++my_it) {
    EXPECT_EQ(*std_it, *my_it);
  }
}

TEST(my_list, push_back_function) {
  std::list<int> std_list1 = {1, 2, 3, 4, 5};
  my::list<int> my_list1 = {1, 2, 3, 4, 5};

  EXPECT_EQ(std_list1.size(), my_list1.size());

  std_list1.push_back(6);
  my_list1.push_back(6);

  EXPECT_EQ(std_list1.size(), my_list1.size());

  auto my_it = my_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++my_it) {
    EXPECT_EQ(*std_it, *my_it);
  }
}

TEST(my_list, pop_back_function) {
  std::list<int> std_list1 = {1, 2, 3, 4, 5};
  my::list<int> my_list1 = {1, 2, 3, 4, 5};

  EXPECT_EQ(std_list1.size(), my_list1.size());

  std_list1.pop_back();
  my_list1.pop_back();

  EXPECT_EQ(std_list1.size(), my_list1.size());

  auto my_it = my_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++my_it) {
    EXPECT_EQ(*std_it, *my_it);
  }
}

TEST(my_list, push_front_function) {
  std::list<int> std_list1 = {1, 2, 3, 4, 5};
  my::list<int> my_list1 = {1, 2, 3, 4, 5};

  EXPECT_EQ(std_list1.size(), my_list1.size());

  std_list1.push_front(6);
  my_list1.push_front(6);

  EXPECT_EQ(std_list1.size(), my_list1.size());

  auto my_it = my_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++my_it) {
    EXPECT_EQ(*std_it, *my_it);
  }
}

TEST(my_list, pop_front_function) {
  std::list<int> std_list1 = {1, 2, 3, 4, 5};
  my::list<int> my_list1 = {1, 2, 3, 4, 5};

  EXPECT_EQ(std_list1.size(), my_list1.size());

  std_list1.pop_front();
  my_list1.pop_front();

  EXPECT_EQ(std_list1.size(), my_list1.size());

  auto my_it = my_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++my_it) {
    EXPECT_EQ(*std_it, *my_it);
  }
}

TEST(my_list, swap_function) {
  std::list<int> std_list1 = {1, 2, 3, 4, 5};
  my::list<int> my_list1 = {1, 2, 3, 4, 5};

  std::list<int> std_list2 = {5, 4, 3, 2, 1};
  my::list<int> my_list2 = {5, 4, 3, 2, 1};

  std_list1.swap(std_list2);
  my_list1.swap(my_list2);

  EXPECT_EQ(std_list1.size(), my_list1.size());
  EXPECT_EQ(std_list2.size(), my_list2.size());

  EXPECT_EQ(*std_list1.begin(), *my_list1.begin());
  EXPECT_EQ(*std_list2.begin(), *my_list2.begin());
}

TEST(my_list, merge_function) {
  std::list<int> std_list1 = {1, 2, 3, 4, 5};
  my::list<int> my_list1 = {1, 2, 3, 4, 5};

  std::list<int> std_list2 = {9, 8, 7};
  my::list<int> my_list2 = {9, 8, 7};

  std_list1.merge(std_list2);
  my_list1.merge(my_list2);

  EXPECT_EQ(std_list1.size(), my_list1.size());

  auto my_it = my_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++my_it) {
    EXPECT_EQ(*std_it, *my_it);
  }

  std_list1 = {9, 8, 7};
  my_list1 = {9, 8, 7};

  std_list2 = {1, 2, 3, 4, 5};
  my_list2 = {1, 2, 3, 4, 5};

  std_list1.merge(std_list2);
  my_list1.merge(my_list2);

  EXPECT_EQ(std_list1.size(), my_list1.size());

  my_it = my_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++my_it) {
    EXPECT_EQ(*std_it, *my_it);
  }

  std_list1 = {1, 2, 3, 4, 5};
  my_list1 = {1, 2, 3, 4, 5};

  std_list2 = {1, 2, 3, 4, 5};
  my_list2 = {1, 2, 3, 4, 5};

  std_list1.merge(std_list2);
  my_list1.merge(my_list2);

  EXPECT_EQ(std_list1.size(), my_list1.size());

  my_it = my_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++my_it) {
    EXPECT_EQ(*std_it, *my_it);
  }
}

TEST(my_list, splice_function) {
  std::list<int> std_list1 = {1, 2, 3, 4};
  my::list<int> my_list1 = {1, 2, 3, 4};

  std::list<int> std_list2 = {9, 8, 7};
  my::list<int> my_list2 = {9, 8, 7};

  std_list1.splice(std_list1.end(), std_list2);
  my_list1.splice(my_list1.cend(), my_list2);

  EXPECT_EQ(std_list1.size(), my_list1.size());
  EXPECT_EQ(std_list2.size(), my_list2.size());

  auto my_it = my_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++my_it) {
    EXPECT_EQ(*std_it, *my_it);
  }

  std_list2.splice(std_list2.begin(), std_list1);
  my_list2.splice(my_list2.cbegin(), my_list1);

  EXPECT_EQ(std_list1.size(), my_list1.size());
  EXPECT_EQ(std_list2.size(), my_list2.size());

  my_it = my_list2.begin();
  for (auto std_it = std_list2.begin(); std_it != std_list2.end();
       ++std_it, ++my_it) {
    EXPECT_EQ(*std_it, *my_it);
  }
}

TEST(my_list, reverse_function) {
  std::list<int> std_list1 = {1, 2, 3, 4, 5};
  my::list<int> my_list1 = {1, 2, 3, 4, 5};

  std_list1.reverse();
  my_list1.reverse();

  EXPECT_EQ(std_list1.size(), my_list1.size());

  auto my_it = my_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++my_it) {
    EXPECT_EQ(*std_it, *my_it);
  }
}

TEST(my_list, unique_function) {
  std::list<int> std_list1 = {1, 2, 2, 3, 4, 5, 5, 5, 2};
  my::list<int> my_list1 = {1, 2, 2, 3, 4, 5, 5, 5, 2};

  std_list1.unique();
  my_list1.unique();

  EXPECT_EQ(std_list1.size(), my_list1.size());

  auto my_it = my_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++my_it) {
    EXPECT_EQ(*std_it, *my_it);
  }
}

TEST(my_list, sort_function) {
  std::list<int> std_list1 = {2, 7, 1, 3, 8, 5};
  my::list<int> my_list1 = {2, 7, 1, 3, 8, 5};

  std_list1.sort();
  my_list1.sort();

  EXPECT_EQ(std_list1.size(), my_list1.size());

  auto my_it = my_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++my_it) {
    EXPECT_EQ(*std_it, *my_it);
  }

  std_list1 = {9, 8, 7, 6, 5};
  my_list1 = {9, 8, 7, 6, 5};

  std_list1.sort();
  my_list1.sort();

  EXPECT_EQ(std_list1.size(), my_list1.size());

  my_it = my_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++my_it) {
    EXPECT_EQ(*std_it, *my_it);
  }
}

TEST(my_list, insert_many_function) {
  std::list<int> std_list1 = {1, 6, 7, 8, 2, 3, 4, 5};
  my::list<int> my_list1 = {1, 2, 3, 4, 5};

  auto pos = my_list1.insert_many(++my_list1.cbegin(), 6, 7, 8);

  EXPECT_EQ(8u, my_list1.size());
  EXPECT_EQ(6, *pos);

  auto my_it = my_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++my_it) {
    EXPECT_EQ(*std_it, *my_it);
  }

  std_list1 = {1, 6, 7, 8, 2, 3, 4, 0, 0, 0, 5};

  pos = my_list1.insert_many(--my_list1.cend(), 0, 0, 0);

  EXPECT_EQ(11u, my_list1.size());
  EXPECT_EQ(0, *pos);

  my_it = my_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++my_it) {
    EXPECT_EQ(*std_it, *my_it);
  }
}

TEST(my_list, insert_many_back_function) {
  std::list<int> std_list1 = {1, 2, 3, 4, 5, 6, 7, 8};
  my::list<int> my_list1 = {1, 2, 3, 4, 5};

  my_list1.insert_many_back(6, 7, 8);

  EXPECT_EQ(8u, my_list1.size());

  auto my_it = my_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++my_it) {
    EXPECT_EQ(*std_it, *my_it);
  }
}

TEST(my_list, insert_many_front_function) {
  std::list<int> std_list1 = {6, 7, 8, 1, 2, 3, 4, 5};
  my::list<int> my_list1 = {1, 2, 3, 4, 5};

  my_list1.insert_many_front(6, 7, 8);

  EXPECT_EQ(8u, my_list1.size());

  auto my_it = my_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++my_it) {
    EXPECT_EQ(*std_it, *my_it);
  }
}
