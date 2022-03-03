#include <gtest/gtest.h>

#include <array>
#include <deque>
#include <iostream>
#include <list>
#include <set>
#include <string>
#include <vector>


#include "../../../Queryable/QueryableType.hpp"
#include "../../../Queryable/Utilities/Group.hpp"

class GroupTest : public ::testing::Test
{
 protected:
   int wUniques = 4;
   std::vector<std::string> strings = {
     "hello", "world", "how", "are", "you" "doing"
     "today", "we", "need", "enough", "variety", "in",
     "words", "that", "we", "have", "many", "words",
     "that", "start" "with", "different", "letters",
     "but", "also", "some", "that", "start", "with",
     "similar", "letters"
   };
  void SetUp() override
  {
  }

  void TearDown() override {}
};

TEST_F(GroupTest, GroupDefaultDequeTest)
{
  std::deque<std::string> wStrings;
  for (std::string str : this->strings)
  {
    if (str[0] == 'w')
    {
      wStrings.push_back(str);
    }
  }

  Group<char, std::string, std::deque> wGroup('w', QueryableType::Deque);
  wGroup.AddMany(wStrings);

  ASSERT_TRUE(wGroup.GetKey() == 'w');
  ASSERT_TRUE(wGroup.Count() > 0);
  ASSERT_EQ(wStrings.size(), wGroup.Count());

  auto it = wGroup.begin();
  for (std::string str : wStrings)
  {
    ASSERT_TRUE(str == *it);
    std::advance(it, 1);
  }
}

TEST_F(GroupTest, GroupDefaultListTest)
{
  std::list<std::string> wStrings;
  for (std::string str : this->strings)
  {
    if (str[0] == 'w')
    {
      wStrings.push_back(str);
    }
  }

  Group<char, std::string, std::list> wGroup('w', QueryableType::Deque);
  wGroup.AddMany(wStrings);

  ASSERT_TRUE(wGroup.GetKey() == 'w');
  ASSERT_TRUE(wGroup.Count() > 0);
  ASSERT_EQ(wStrings.size(), wGroup.Count());

  auto it = wGroup.begin();
  for (std::string str : wStrings)
  {
    ASSERT_TRUE(str == *it);
    std::advance(it, 1);
  }
}

TEST_F(GroupTest, GroupDefaultMultiSetTest)
{
  std::multiset<std::string> wStrings;
  for (std::string str : this->strings)
  {
    if (str[0] == 'w')
    {
      wStrings.insert(str);
    }
  }

  Group<char, std::string, std::multiset> wGroup('w', QueryableType::MultiSet);
  wGroup.AddMany(wStrings);

  ASSERT_TRUE(wGroup.GetKey() == 'w');
  ASSERT_TRUE(wGroup.Count() > 0);
  ASSERT_EQ(wStrings.size(), wGroup.Count());

  auto it = wGroup.begin();
  for (std::string str : wStrings)
  {
    ASSERT_TRUE(str == *it);
    std::advance(it, 1);
  }
}

TEST_F(GroupTest, GroupDefaultSetTest)
{
  std::set<std::string> wStrings;
  for (std::string str : this->strings)
  {
    if (str[0] == 'w')
    {
      wStrings.insert(str);
    }
  }

  Group<char, std::string, std::set> wGroup('w', QueryableType::Set);
  wGroup.AddMany(wStrings);

  ASSERT_TRUE(wGroup.GetKey() == 'w');
  ASSERT_EQ(wUniques, wGroup.Count());
  ASSERT_EQ(wStrings.size(), wGroup.Count());

  auto it = wGroup.begin();
  for (std::string str : wStrings)
  {
    ASSERT_TRUE(str == *it);
    std::advance(it, 1);
  }
}

TEST_F(GroupTest, GroupDefaultVectorTest)
{
  std::vector<std::string> wStrings;
  for (std::string str : this->strings)
  {
    if (str[0] == 'w')
    {
      wStrings.push_back(str);
    }
  }

  Group<char, std::string> wGroup('w', QueryableType::Vector);
  wGroup.AddMany(wStrings);

  ASSERT_TRUE(wGroup.GetKey() == 'w');
  ASSERT_TRUE(wGroup.Count() > 0);
  ASSERT_EQ(wStrings.size(), wGroup.Count());

  auto it = wGroup.begin();
  for (std::string str : wStrings)
  {
    ASSERT_TRUE(str == *it);
    std::advance(it, 1);
  }
}

TEST_F(GroupTest, GroupDefaultLessThanTest)
{
  std::vector<std::string> wStrings;
  for (std::string str : this->strings)
  {
    if (str[0] == 'w')
    {
      wStrings.push_back(str);
    }
  }

  std::vector<std::string> tStrings;
  for (std::string str : this->strings)
  {
    if (str[0] == 't')
    {
      tStrings.push_back(str);
    }
  }

  std::vector<std::string> hStrings;
  for (std::string str : this->strings)
  {
    if (str[0] == 'h')
    {
      hStrings.push_back(str);
    }
  }

  Group<char, std::string> wGroup('w', QueryableType::Vector);
  wGroup.AddMany(wStrings);
  Group<char, std::string> tGroup('t', QueryableType::Vector);
  tGroup.AddMany(tStrings);
  Group<char, std::string> hGroup('h', QueryableType::Vector);
  hGroup.AddMany(hStrings);

  ASSERT_TRUE(hGroup < tGroup);
  ASSERT_TRUE(tGroup < wGroup);
  ASSERT_FALSE(wGroup < hGroup);
}

TEST_F(GroupTest, GroupCustomLessThanTest)
{
  std::vector<std::string> wStrings;
  for (std::string str : this->strings)
  {
    if (str[0] == 'w')
    {
      wStrings.push_back(str);
    }
  }

  std::vector<std::string> tStrings;
  for (std::string str : this->strings)
  {
    if (str[0] == 't')
    {
      tStrings.push_back(str);
    }
  }

  std::vector<std::string> hStrings;
  for (std::string str : this->strings)
  {
    if (str[0] == 'h')
    {
      hStrings.push_back(str);
    }
  }

  std::function<bool(char,char)> backwardCompare =
    [](char a, char b) -> bool { return b < a; };
  typedef decltype(backwardCompare) TComparison;

  Group<char, std::string, std::vector, TComparison> wGroup('w', QueryableType::Vector, backwardCompare);
  wGroup.AddMany(wStrings);
  Group<char, std::string, std::vector, TComparison> tGroup('t', QueryableType::Vector, backwardCompare);
  tGroup.AddMany(tStrings);
  Group<char, std::string, std::vector, TComparison> hGroup('h', QueryableType::Vector, backwardCompare);
  hGroup.AddMany(hStrings);

  ASSERT_TRUE(wGroup < tGroup);
  ASSERT_TRUE(tGroup < hGroup);
  ASSERT_FALSE(hGroup < wGroup);
}
