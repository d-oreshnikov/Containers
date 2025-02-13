
#include <gtest/gtest.h>

#include <utility>

#include "../my_containers.h"

TEST(my_vector, basic_constructor) {
  my::vector<int> vec;
  EXPECT_EQ(vec.data(), nullptr);
  EXPECT_EQ(static_cast<size_t>(0), vec.size());
}

TEST(my_vector, size_constructor) {
  my::vector<double> vec(5);
  double* data = vec.data();

  EXPECT_NE(data, nullptr);
  EXPECT_EQ(static_cast<size_t>(5), vec.size());

  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_DOUBLE_EQ(0, data[i]);
  }
}

TEST(my_vector, initializer_list_constructor) {
  my::vector<char> vec({'a', 'b', 'c'});
  char* data = vec.data();

  EXPECT_NE(data, nullptr);
  EXPECT_EQ(static_cast<size_t>(3), vec.size());

  EXPECT_EQ('a', data[0]);
  EXPECT_EQ('b', data[1]);
  EXPECT_EQ('c', data[2]);
}

TEST(my_vector, copy_constructor) {
  my::vector<unsigned> origin({1, 2, 3, 4});
  my::vector vec(origin);

  unsigned* data = vec.data();
  unsigned* ordata = origin.data();

  EXPECT_NE(data, ordata);
  EXPECT_EQ(vec.size(), origin.size());

  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(data[i], ordata[i]);
  }
}

TEST(my_vector, move_constructor) {
  my::vector<unsigned> origin({1, 2, 3, 4});
  my::vector vec(std::move(origin));

  unsigned* data = vec.data();
  unsigned* ordata = origin.data();

  EXPECT_NE(data, nullptr);
  EXPECT_EQ(ordata, nullptr);

  EXPECT_EQ(static_cast<size_t>(4), vec.size());

  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(i + 1, data[i]);
  }
}

TEST(my_vector, copy_assignment) {
  my::vector<unsigned> origin({1, 2, 3, 4});
  my::vector<unsigned> originCpy({1, 2, 3, 4});
  my::vector<unsigned> vec(15);

  vec = std::move(originCpy);

  EXPECT_EQ(static_cast<size_t>(4), vec.size());
  EXPECT_EQ(static_cast<size_t>(4), origin.size());

  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(origin[i], vec[i]);
  }
}

TEST(my_vector, initializer_list_assignment) {
  my::vector<unsigned> vec(10);

  vec = {1, 2, 3, 4};

  EXPECT_EQ(static_cast<size_t>(4), vec.size());

  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(i + 1, vec[i]);
  }
}

TEST(my_vector, at_normal) {
  my::vector<int> vec({1, 2, 3});
  int* data = vec.data();

  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(data[i], vec.at(i));
  }
}

TEST(my_vector, at_out_of_range) {
  EXPECT_ANY_THROW({
    my::vector<double> vec;
    vec.at(0);
  });

  EXPECT_ANY_THROW({
    my::vector<int> vec({1, 2, 3});
    vec.at(3);
  });
}

TEST(my_vector, index_operator) {
  my::vector<char> vec({'a', 'b', 'c', 'd'});
  char* data = vec.data();

  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(data[i], vec[i]);
  }
}

TEST(my_vector, front) {
  my::vector<int> vec({'a', 'b', 'c', 'd'});
  EXPECT_EQ('a', vec.front());

  my::vector<double> vec2({2e22});
  EXPECT_DOUBLE_EQ(2e22, vec2.front());

  my::vector<void*> vec3(5);
  EXPECT_EQ(nullptr, vec3.front());
}

TEST(my_vector, back) {
  my::vector<int> vec({'a', 'b', 'c', 'd'});
  EXPECT_EQ('d', vec.back());

  my::vector<double> vec2({2e22});
  EXPECT_DOUBLE_EQ(2e22, vec2.back());

  my::vector<void*> vec3(5);
  EXPECT_EQ(nullptr, vec3.back());
}

TEST(my_vector, iterator) {
  my::vector<unsigned> vec({0, 2, 4, 6, 8, 10});
  unsigned* data = vec.data();

  for (auto iter = vec.begin(); iter != vec.end(); ++iter) {
    EXPECT_EQ(*(data++), *iter);
  }
}

TEST(my_vector, reserve) {
  my::vector<unsigned> vec;
  auto cap = vec.capacity();

  vec.reserve(15);
  cap = 15;
  EXPECT_EQ(cap, vec.capacity());

  vec.reserve(200);
  cap = 200;
  EXPECT_EQ(cap, vec.capacity());

  vec.reserve(100);
  EXPECT_EQ(cap, vec.capacity());

  EXPECT_EQ(static_cast<size_t>(0), vec.size());
}

TEST(my_vector, shrink_to_fit) {
  my::vector<int> vec(25);

  vec.reserve(1000);
  vec.shrink_to_fit();
  EXPECT_EQ(vec.capacity(), vec.size());

  vec.reserve(100000);
  vec.shrink_to_fit();
  EXPECT_EQ(vec.capacity(), vec.size());

  vec.reserve(22);
  vec.shrink_to_fit();
  EXPECT_EQ(vec.capacity(), vec.size());
}

TEST(my_vector, clear) {
  my::vector<int> vec;
  vec.clear();
  EXPECT_EQ(static_cast<size_t>(0), vec.size());

  my::vector<char> vec2({'a', 'b', 'c'});
  vec2.clear();
  EXPECT_EQ(static_cast<size_t>(0), vec2.size());
}

TEST(my_vector, insert) {
  my::vector<char> vec{'a'};

  auto pos = vec.insert(vec.begin(), 'b');
  EXPECT_EQ('b', *pos);

  pos = vec.begin();
  pos = vec.insert(++pos, 'c');
  EXPECT_EQ('c', *pos);

  EXPECT_EQ(static_cast<size_t>(3), vec.size());
  EXPECT_EQ('b', vec[0]);
  EXPECT_EQ('c', vec[1]);
  EXPECT_EQ('a', vec[2]);

  vec.insert(vec.begin(), 'd');
  pos = vec.begin();
  ++pos;
  ++pos;
  vec.insert(pos, 'e');

  EXPECT_EQ(static_cast<size_t>(5), vec.size());
  EXPECT_EQ('d', vec[0]);
  EXPECT_EQ('b', vec[1]);
  EXPECT_EQ('e', vec[2]);
  EXPECT_EQ('c', vec[3]);
  EXPECT_EQ('a', vec[4]);
}

TEST(my_vector, insert_end) {
  my::vector<char> vec{'a'};

  auto pos = vec.insert(vec.end(), 'b');
  EXPECT_EQ('b', *pos);

  pos = vec.insert(vec.end(), 'c');
  EXPECT_EQ('c', *pos);

  EXPECT_EQ(static_cast<size_t>(3), vec.size());
  EXPECT_EQ('a', vec[0]);
  EXPECT_EQ('b', vec[1]);
  EXPECT_EQ('c', vec[2]);
}

TEST(my_vector, insert_empty) {
  my::vector<int> vec;

  auto pos = vec.insert(vec.begin(), 11);
  EXPECT_EQ(11, *pos);

  EXPECT_EQ(static_cast<size_t>(1), vec.size());
  EXPECT_EQ(11, vec[0]);

  my::vector<double> vec2;

  auto pos2 = vec2.insert(vec2.end(), 2.33);
  EXPECT_DOUBLE_EQ(2.33, *pos2);

  EXPECT_EQ(static_cast<size_t>(1), vec2.size());
  EXPECT_DOUBLE_EQ(2.33, vec2[0]);
}

TEST(my_vector, erase) {
  my::vector<int> vec({1, 2, 3, 4, 5});

  auto pos = vec.begin();
  ++pos;
  ++pos;

  vec.erase(pos);

  EXPECT_EQ(static_cast<size_t>(4), vec.size());
  EXPECT_EQ(1, vec[0]);
  EXPECT_EQ(2, vec[1]);
  EXPECT_EQ(4, vec[2]);
  EXPECT_EQ(5, vec[3]);

  pos = vec.end();
  --pos;

  vec.erase(pos);

  EXPECT_EQ(static_cast<size_t>(3), vec.size());
  EXPECT_EQ(1, vec[0]);
  EXPECT_EQ(2, vec[1]);
  EXPECT_EQ(4, vec[2]);

  vec.erase(vec.begin());

  EXPECT_EQ(static_cast<size_t>(2), vec.size());
  EXPECT_EQ(2, vec[0]);
  EXPECT_EQ(4, vec[1]);
}

TEST(my_vector, push_back) {
  my::vector<int> vec;

  for (int i = 0; i < 100; ++i) {
    vec.push_back(i);
  }

  EXPECT_EQ(static_cast<size_t>(100), vec.size());

  vec.shrink_to_fit();

  for (int i = 100; i < 1000; ++i) {
    vec.push_back(i);
  }

  EXPECT_EQ(static_cast<size_t>(1000), vec.size());

  for (int i = 0; i < 1000; ++i) {
    EXPECT_EQ(i, vec[i]);
  }
}

TEST(my_vector, pop_back) {
  my::vector<int> vec;

  for (int i = 0; i < 2000; ++i) {
    vec.push_back(i);
  }

  for (int i = 0; i < 500; ++i) {
    vec.pop_back();
  }

  EXPECT_EQ(static_cast<size_t>(1500), vec.size());

  for (int i = 0; i < 1500; ++i) {
    EXPECT_EQ(i, vec.at(i));
  }

  for (int i = 0; i < 1500; ++i) {
    vec.pop_back();
  }

  EXPECT_EQ(static_cast<size_t>(0), vec.size());
}

TEST(my_vector, swap) {
  my::vector<int> vec({1, 2, 3, 4});
  my::vector copied_vec(vec);
  auto size = vec.size();
  auto capacity = vec.capacity();
  auto data = vec.data();

  my::vector<int> other_vec({5, 6, 7, 8, 9, 10});
  my::vector copied_other_vec(other_vec);
  auto other_size = other_vec.size();
  auto other_capacity = other_vec.capacity();
  auto other_data = other_vec.data();

  vec.swap(other_vec);

  EXPECT_EQ(vec.size(), other_size);
  EXPECT_EQ(other_vec.size(), size);

  EXPECT_EQ(copied_other_vec.size(), vec.size());
  EXPECT_EQ(copied_vec.size(), other_vec.size());

  EXPECT_EQ(vec.capacity(), other_capacity);
  EXPECT_EQ(other_vec.capacity(), capacity);

  EXPECT_EQ(vec.data(), other_data);
  EXPECT_EQ(other_vec.data(), data);

  for (size_t i = 0; i < copied_vec.size(); ++i) {
    EXPECT_EQ(copied_vec[i], other_vec[i]);
  }

  for (size_t i = 0; i < copied_other_vec.size(); ++i) {
    EXPECT_EQ(copied_other_vec[i], vec[i]);
  }
}

TEST(my_vector, self_swap) {
  my::vector<int> vec({1, 2, 3, 4});
  my::vector copied_vec(vec);

  vec.swap(vec);

  EXPECT_EQ(copied_vec.size(), vec.size());
  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(copied_vec[i], vec[i]);
  }
}

TEST(my_vector, insert_many_once) {
  my::vector<int> vec{1, 2, 3};

  auto pos = vec.begin();
  ++pos;
  pos = vec.insert_many(pos, 4);

  EXPECT_EQ(*pos, 4);

  EXPECT_EQ(static_cast<size_t>(4), vec.size());
  EXPECT_EQ(1, vec[0]);
  EXPECT_EQ(4, vec[1]);
  EXPECT_EQ(2, vec[2]);
  EXPECT_EQ(3, vec[3]);
}

TEST(my_vector, insert_many_multiple) {
  my::vector<char> vec{'a', 'b', 'c'};

  auto pos = vec.begin();
  ++pos;
  ++pos;
  pos = vec.insert_many(pos, 'd', 'e', 'f');

  EXPECT_EQ(*pos, 'd');

  EXPECT_EQ(static_cast<size_t>(6), vec.size());
  EXPECT_EQ('a', vec[0]);
  EXPECT_EQ('b', vec[1]);
  EXPECT_EQ('d', vec[2]);
  EXPECT_EQ('e', vec[3]);
  EXPECT_EQ('f', vec[4]);
  EXPECT_EQ('c', vec[5]);

  pos = vec.insert_many(vec.begin(), 'a', 'b', std::move('o'), 'b', 'a');

  EXPECT_EQ(*pos, 'a');

  EXPECT_EQ(static_cast<size_t>(11), vec.size());
  EXPECT_EQ('a', vec[0]);
  EXPECT_EQ('b', vec[1]);
  EXPECT_EQ('o', vec[2]);
  EXPECT_EQ('b', vec[3]);
  EXPECT_EQ('a', vec[4]);
  EXPECT_EQ('a', vec[5]);
  EXPECT_EQ('b', vec[6]);
  EXPECT_EQ('d', vec[7]);
  EXPECT_EQ('e', vec[8]);
  EXPECT_EQ('f', vec[9]);
  EXPECT_EQ('c', vec[10]);
}

TEST(my_vector, insert_many_nothing) {
  my::vector<double> vec({1.1, 2.2, 3.3});
  auto pos = vec.insert_many(vec.begin());

  EXPECT_DOUBLE_EQ(*pos, 1.1);

  EXPECT_EQ(static_cast<size_t>(3), vec.size());
  EXPECT_DOUBLE_EQ(1.1, vec[0]);
  EXPECT_DOUBLE_EQ(2.2, vec[1]);
  EXPECT_DOUBLE_EQ(3.3, vec[2]);
}

TEST(my_vector, insert_many_to_end) {
  my::vector<char> vec({'a', 'b', 'o'});
  auto pos = vec.insert_many(vec.end(), 'b', 'u', 's');
  EXPECT_EQ(*pos, 'b');

  EXPECT_EQ(static_cast<size_t>(6), vec.size());
  EXPECT_EQ('a', vec[0]);
  EXPECT_EQ('b', vec[1]);
  EXPECT_EQ('o', vec[2]);
  EXPECT_EQ('b', vec[3]);
  EXPECT_EQ('u', vec[4]);
  EXPECT_EQ('s', vec[5]);
}

TEST(my_vector, insert_many_to_empty) {
  my::vector<int> vec;
  auto pos = vec.insert_many(vec.begin(), 1, 2, 3);

  EXPECT_EQ(*pos, 1);

  EXPECT_EQ(static_cast<size_t>(3), vec.size());
  EXPECT_EQ(1, vec[0]);
  EXPECT_EQ(2, vec[1]);
  EXPECT_EQ(3, vec[2]);
}

TEST(my_vector, insert_many_back_once) {
  my::vector<int> vec{0, 2, 4, 6};
  vec.insert_many_back(8);

  EXPECT_EQ(static_cast<size_t>(5), vec.size());
  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(2 * i, static_cast<size_t>(vec[i]));
  }
}

TEST(my_vector, insert_many_back_multiple) {
  my::vector<int> vec{0, 1, 4, 9};
  vec.insert_many_back(std::move(16), std::move(25), 36);

  EXPECT_EQ(static_cast<size_t>(7), vec.size());
  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(i * i, static_cast<size_t>(vec[i]));
  }
}

TEST(my_vector, insert_many_back_nothing) {
  my::vector<char> vec{'c', 'o', 'o', 'l'};
  vec.insert_many_back();

  EXPECT_EQ(static_cast<size_t>(4), vec.size());
  EXPECT_EQ('c', vec[0]);
  EXPECT_EQ('o', vec[1]);
  EXPECT_EQ('o', vec[2]);
  EXPECT_EQ('l', vec[3]);
}

TEST(my_vector, insert_many_back_empty) {
  my::vector<char> vec;
  vec.insert_many_back('c', 'o', 'o', 'l');

  EXPECT_EQ(static_cast<size_t>(4), vec.size());
  EXPECT_EQ('c', vec[0]);
  EXPECT_EQ('o', vec[1]);
  EXPECT_EQ('o', vec[2]);
  EXPECT_EQ('l', vec[3]);
}
