#include <gtest/gtest.h>

#include "../my_containers_plus.h"

TEST(my_array, empty_constructor) {
    my::array<int, 5> a;
    ASSERT_EQ(5u, a.size());
    ASSERT_FALSE(a.empty());
}

TEST(my_array, initializer_list_constructor) {
    my::array<int, 5> a{1, 2, 3, 4, 5};
    ASSERT_EQ(5u, a.size());
    ASSERT_FALSE(a.empty());
}

TEST(my_array, copy_constructor) {
    my::array<int, 5> a1{1, 2, 3, 4, 5};
    my::array<int, 5> a2(a1);
    ASSERT_EQ(5u, a2.size());
    ASSERT_FALSE(a2.empty());
}

TEST(my_array, move_constructor) {
    my::array<int, 5> a1{1, 2, 3, 4, 5};
    my::array<int, 5> a2(std::move(a1));
    ASSERT_EQ(5u, a2.size());
    ASSERT_FALSE(a2.empty());
}

TEST(my_array, move_assignment) {
    my::array<int, 5> a1{1, 2, 3, 4, 5};
    my::array<int, 5> a2;
    a2 = std::move(a1);
    ASSERT_EQ(5u, a2.size());
    ASSERT_FALSE(a2.empty());
}

TEST(my_array, front) {
    my::array<int, 5> a{1, 2, 3, 4, 5};
    ASSERT_EQ(1, a.front());
}

TEST(my_array, back) {
    my::array<int, 5> a{1, 2, 3, 4, 5};
    ASSERT_EQ(5, a.back());
}

TEST(my_array, empty) {
    my::array<int, 5> a;
    ASSERT_FALSE(a.empty());
}

TEST(my_array, size) {
    my::array<int, 5> a;
    ASSERT_EQ(5u, a.size());
}

TEST(my_array, max_size) {
    my::array<int, 5> a;
    ASSERT_EQ(5, int(a.max_size()));
}

TEST(my_array, swap) {
    my::array<int, 5> a1{1, 2, 3, 4, 5};
    my::array<int, 5> a2{5, 4, 3, 2, 1};
    a1.swap(a2);
    ASSERT_EQ(5, a1[0]);
    ASSERT_EQ(1, a2[0]);
}

TEST(my_array, fill) {
    my::array<int, 5> a;
    a.fill(42);
    for (int i = 0; i < 5; ++i) {
        ASSERT_EQ(42, a[i]);
    }
}

TEST(my_array, begin_end) {
    my::array<int, 5> a{1, 2, 3, 4, 5};
    int i = 1;
    for (auto it = a.begin(); it != a.end(); ++it) {
        ASSERT_EQ(i++, *it);
    }
}

TEST(my_array, array_at) {
    my::array<int, 5> a{1, 2, 3, 4, 5};
    ASSERT_EQ(1, a.at(0));
    ASSERT_EQ(5, a.at(4));
    ASSERT_THROW(a.at(5), std::out_of_range);
}

TEST(my_array, getData) {
    my::array<int, 5> a{1, 2, 3, 4, 5};
    int* data = a.getData();
    for (int i = 0; i < 5; ++i) {
        ASSERT_EQ(i + 1, data[i]);
    }
}
