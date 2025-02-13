#include <gtest/gtest.h>

#include "../my_containers.h"

TEST(my_map, empty_constructor) {
  my::map<int, std::string> m;
  ASSERT_EQ(0u, m.size());
  ASSERT_TRUE(m.empty());
}

TEST(my_map, initializer_constructor) {
  my::map<int, std::string> m = {
    {54, "Adam"},
    {93, "Eva"},
    {23, "Nastya"},
    {58, "Denis"},
    {12, "Fahruh"},
    {02, "Mila"},
    {29, "Hamich"},
    {67, "Gerald"},
    {83, "Migel"},
    {71, "Gaga"},
    {39, "Yanis"},
    {91, "Basil"},
    {47, "Lasha"},
    {13, "Masha"}
  };
  ASSERT_EQ(14u, m.size());
  ASSERT_FALSE(m.empty());
}

TEST(my_map, copy_contructor) {
  my::map<int, std::string> m1 = {
    {54, "Adam"},
    {93, "Eva"},
    {23, "Nastya"},
    {58, "Denis"},
    {12, "Fahruh"},
    {02, "Mila"},
    {29, "Hamich"},
    {67, "Gerald"},
    {83, "Migel"},
    {71, "Gaga"},
    {39, "Yanis"},
    {91, "Basil"},
    {47, "Lasha"},
    {13, "Masha"}
  };
  my::map<int, std::string> m2(m1);
  ASSERT_EQ(14u, m2.size());
  ASSERT_FALSE(m2.empty());
}

TEST(my_map, move_constructor) {
  my::map<int, std::string> m1 = {
    {54, "Adam"},
    {93, "Eva"},
    {23, "Nastya"},
    {58, "Denis"},
    {12, "Fahruh"},
    {02, "Mila"},
    {29, "Hamich"},
    {67, "Gerald"},
    {83, "Migel"},
    {71, "Gaga"},
    {39, "Yanis"},
    {91, "Basil"},
    {47, "Lasha"},
    {13, "Masha"}
  };
  my::map<int, std::string> m2(std::move(m1));
  ASSERT_EQ(14u, m2.size());
  ASSERT_FALSE(m2.empty());
}

TEST(my_map, move_assigment) {
  my::map<int, std::string> m1 = {
    {54, "Adam"},
    {93, "Eva"},
    {23, "Nastya"},
    {58, "Denis"},
    {12, "Fahruh"},
    {02, "Mila"},
    {29, "Hamich"},
    {67, "Gerald"},
    {83, "Migel"},
    {71, "Gaga"},
    {39, "Yanis"},
    {91, "Basil"},
    {47, "Lasha"},
    {13, "Masha"}
  };
  my::map<int, std::string> m2;
  m2 = std::move(m1);
  ASSERT_EQ(14u, m2.size());
  ASSERT_FALSE(m2.empty());
}

TEST(my_map, at) {
  my::map<int, std::string> m = {
    {54, "Adam"},
    {93, "Eva"},
    {23, "Nastya"},
    {58, "Denis"},
    {12, "Fahruh"},
    {02, "Mila"},
    {29, "Hamich"},
    {67, "Gerald"},
    {83, "Migel"},
    {71, "Gaga"},
    {39, "Yanis"},
    {91, "Basil"},
    {47, "Lasha"},
    {13, "Masha"}
  };
  ASSERT_EQ("Hamich", m.at(29));
  ASSERT_EQ("Fahruh", m.at(12));
  ASSERT_EQ("Basil", m.at(91));
}

TEST(my_map, operator) {
  my::map<int, std::string> m = {
    {54, "Adam"},
    {93, "Eva"},
    {23, "Nastya"},
    {58, "Denis"},
    {12, "Fahruh"},
    {02, "Mila"},
    {29, "Hamich"},
    {67, "Gerald"},
    {83, "Migel"},
    {71, "Gaga"},
    {39, "Yanis"},
    {91, "Basil"},
    {47, "Lasha"},
    {13, "Masha"}
  };
  ASSERT_EQ("Hamich", m.at(29));
  m[29] = "Givi";
  ASSERT_EQ("Givi", m.at(29));
  m[29] = "Sveta";
  ASSERT_EQ("Sveta", m.at(29));
}

TEST(my_map, iterator) {
  my::map<int, std::string> m = {
    {54, "Adam"},
    {93, "Eva"},
    {23, "Nastya"},
    {58, "Denis"},
    {12, "Fahruh"},
    {02, "Mila"},
    {29, "Hamich"},
    {67, "Gerald"},
    {83, "Migel"},
    {71, "Gaga"},
    {39, "Yanis"},
    {91, "Basil"},
    {47, "Lasha"},
    {13, "Masha"}
  };
  my::map<int, std::string>::iterator it = m.begin();
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

TEST(my_map, clear) {
  my::map<int, std::string> m = {
    {54, "Adam"},
    {93, "Eva"},
    {23, "Nastya"},
    {58, "Denis"},
    {12, "Fahruh"},
    {02, "Mila"},
    {29, "Hamich"},
    {67, "Gerald"},
    {83, "Migel"},
    {71, "Gaga"},
    {39, "Yanis"},
    {91, "Basil"},
    {47, "Lasha"},
    {13, "Masha"}
  };
  ASSERT_EQ(14u, m.size());
  ASSERT_FALSE(m.empty());
  m.clear();
  ASSERT_TRUE(m.empty());
}

TEST(my_map, insert) {
  my::map<int, std::string> m = {
    {54, "Adam"},
    {93, "Eva"},
    {23, "Nastya"},
    {58, "Denis"},
    {12, "Fahruh"},
    {02, "Mila"},
    {29, "Hamich"},
    {67, "Gerald"},
    {83, "Migel"},
    {71, "Gaga"},
    {39, "Yanis"},
    {91, "Basil"},
    {47, "Lasha"},
    {13, "Masha"}
  };
  my::map<int, std::string>::iterator it = m.begin();
  auto res1 = m.insert(std::make_pair(40, "Valentina"));
  ASSERT_EQ(res1, std::make_pair(it.set(40), true));
  auto res2 = m.insert(41, "Stas");
  ASSERT_EQ(res2, std::make_pair(it.set(41), true));
  auto res3 = m.insert(std::make_pair(40, "Valya"));
  ASSERT_EQ(res3, std::make_pair(it.set(40), false));
  ASSERT_EQ(m.at(40), "Valentina");
  auto res4 = m.insert_or_assign(42, "Olga");
  ASSERT_EQ(res4, std::make_pair(it.set(42), true));
  auto res5 = m.insert_or_assign(40, "Valya");
  ASSERT_EQ(res5, std::make_pair(it.set(40), false));
  ASSERT_EQ(m.at(40), "Valya");
}

TEST(my_map, erase) {
  my::map<int, std::string> m = {
    {54, "Adam"},
    {93, "Eva"},
    {23, "Nastya"},
    {58, "Denis"},
    {12, "Fahruh"},
    {02, "Mila"},
    {29, "Hamich"},
    {67, "Gerald"},
    {83, "Migel"},
    {71, "Gaga"},
    {39, "Yanis"},
    {91, "Basil"},
    {47, "Lasha"},
    {13, "Masha"}
  };
  my::map<int, std::string>::iterator it = m.begin();
  ++it;
  ++it;
  ++it;
  ++it;
  ++it;
  ASSERT_EQ(39, it.cget());
  ASSERT_TRUE(m.contains(39));
  m.erase(it);
  ASSERT_FALSE(m.contains(39));
}

TEST(my_map, merge) {
  my::map<int, std::string> m1 = {
    {54, "Adam"},
    {93, "Eva"},
    {23, "Nastya"},
    {58, "Denis"},
    {12, "Fahruh"},
    {02, "Mila"},
    {29, "Hamich"},
    {67, "Gerald"},
  };
  my::map<int, std::string> m2 = {
    {67, "Gerald"},
    {83, "Migel"},
    {71, "Gaga"},
    {39, "Yanis"},
    {91, "Basil"},
    {47, "Lasha"},
    {13, "Masha"}
  };
  ASSERT_EQ(8u, m1.size());
  ASSERT_EQ(7u, m2.size());
  m1.merge(m2);
  ASSERT_EQ(14u, m1.size());
}

TEST(my_map, insert_many) {
  my::map<int, std::string> m = {
    {54, "Adam"},
    {93, "Eva"},
    {23, "Nastya"},
    {58, "Denis"},
    {12, "Fahruh"},
    {02, "Mila"},
    {29, "Hamich"},
    {67, "Gerald"},
    {83, "Migel"},
    {71, "Gaga"},
    {39, "Yanis"},
    {91, "Basil"},
    {47, "Lasha"},
    {13, "Masha"}
  };
  auto out = m.insert_many(
    std::make_pair(14, "Misha"), 
    std::make_pair(59, "Mars"), 
    std::make_pair(91, "Nataly"), 
    std::make_pair(71, "Jimmy"));
  my::map<int, std::string>::iterator it = m.begin();
  ASSERT_EQ(out[0], std::make_pair(it.set(14), true));
  ASSERT_EQ(out[1], std::make_pair(it.set(59), true));
  ASSERT_EQ(out[2], std::make_pair(it.set(91), false));
  ASSERT_EQ(out[3], std::make_pair(it.set(71), false));
}
