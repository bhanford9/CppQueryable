#include <gtest/gtest.h>

#include <array>
#include <deque>
#include <exception>
#include <iostream>
#include <list>
#include <set>
#include <string>
#include <vector>

#include "../../../DataStructures/Gender.h"
#include "../../../DataStructures/Person.h"
#include "../../../DataStructures/PersonLibrary.h"

#include "../../../Queryable/QueryBuilder.h"
#include "../../../Queryable/QueryableVector.h"

using namespace QueryBuilder;

class MinFunctionalTest : public ::testing::Test
{
protected:
  uint expectedMin = 1;
  char expectedMinChar = 'a';
  std::string expectedMinStr = "abc";
  QueryableVector<uint> queryable;
  QueryableVector<std::string> queryableStrings;

  void SetUp() override
  {
    this->queryable = BuildQueryable(std::vector<uint>({ 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, expectedMin, 867, 12 }));
    this->queryableStrings = BuildQueryable(std::vector<std::string>({ "nbc", "fox", "abc", "cbs", "the cw"}));
  }

  void TearDown() override {}
};

TEST_F(MinFunctionalTest, MinItemUninitialized)
{
  QueryableVector<Person> emptyQueryable;

  try
  {
    emptyQueryable.MinItem<double>([](Person p) { return p.GetAge(); });
  }
  catch (std::runtime_error& ex)
  {
    ASSERT_STREQ(ex.what(), "Cannot find minimum item of an empty colleciton.");
  }
}

TEST_F(MinFunctionalTest, MinUninitialized)
{
  QueryableVector<Person> emptyQueryable;

  try
  {
    emptyQueryable.Min<double>([](Person p) { return p.GetAge(); });
  }
  catch (std::runtime_error& ex)
  {
    ASSERT_STREQ(ex.what(), "Cannot find minimum item of an empty colleciton.");
  }
}

TEST_F(MinFunctionalTest, MinSeededUninitialized)
{
  double seed = 9;
  QueryableVector<Person> emptyQueryable;
  double min = emptyQueryable.Min<double>([](Person p) { return p.GetAge(); }, seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinItemString)
{
  std::string min = this->queryableStrings.MinItem<char>([](std::string str) { return str[0]; });
  ASSERT_STREQ(expectedMinStr.c_str(), min.c_str());
}

TEST_F(MinFunctionalTest, MinString)
{
  char min = this->queryableStrings.Min<char>([](std::string str) { return str[0]; });
  ASSERT_EQ(expectedMinChar, min);
}

TEST_F(MinFunctionalTest, MinSmallerSeedString)
{
  char seed = 'Z';
  char min = this->queryableStrings.Min<char>([](std::string str) { return str[0]; }, seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinLargerSeedString)
{
  char seed = 'c';
  char min = this->queryableStrings.Min<char>([](std::string str) { return str[0]; }, seed);
  ASSERT_EQ(expectedMinChar, min);
}

TEST_F(MinFunctionalTest, MinItemDeque)
{
  QueryableDeque<uint> local = BuildQueryable(this->queryable.ToDeque());
  uint min = local.MinItem<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinDeque)
{
  QueryableDeque<uint> local = BuildQueryable(this->queryable.ToDeque());
  uint min = local.Min<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinSeededLowerDeque)
{
  uint seed = 0;
  QueryableDeque<uint> local = BuildQueryable(this->queryable.ToDeque());
  uint min = local.Min<uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinSeededHigherDeque)
{
  uint seed = expectedMin + 1;
  QueryableDeque<uint> local = BuildQueryable(this->queryable.ToDeque());
  uint min = local.Min<uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinItemList)
{
  QueryableList<uint> local = BuildQueryable(this->queryable.ToList());
  uint min = local.MinItem<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinList)
{
  QueryableList<uint> local = BuildQueryable(this->queryable.ToList());
  uint min = local.Min<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinSeededLowerList)
{
  uint seed = 0;
  QueryableList<uint> local = BuildQueryable(this->queryable.ToList());
  uint min = local.Min<uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinSeededHigherList)
{
  uint seed = expectedMin + 1;
  QueryableList<uint> local = BuildQueryable(this->queryable.ToList());
  uint min = local.Min<uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinItemMultiSet)
{
  QueryableMultiSet<uint> local = BuildQueryable(this->queryable.ToMultiSet());
  uint min = local.MinItem<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinMultiSet)
{
  QueryableMultiSet<uint> local = BuildQueryable(this->queryable.ToMultiSet());
  uint min = local.Min<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinSeededLowerMultiSet)
{
  uint seed = 0;
  QueryableMultiSet<uint> local = BuildQueryable(this->queryable.ToMultiSet());
  uint min = local.Min<uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinSeededHigherMultiSet)
{
  uint seed = expectedMin + 1;
  QueryableMultiSet<uint> local = BuildQueryable(this->queryable.ToMultiSet());
  uint min = local.Min<uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinItemSet)
{
  QueryableSet<uint> local = BuildQueryable(this->queryable.ToSet());
  uint min = local.MinItem<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinSet)
{
  QueryableSet<uint> local = BuildQueryable(this->queryable.ToSet());
  uint min = local.Min<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinSeededLowerSet)
{
  uint seed = 0;
  QueryableSet<uint> local = BuildQueryable(this->queryable.ToSet());
  uint min = local.Min<uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinSeededHigherSet)
{
  uint seed = expectedMin + 1;
  QueryableSet<uint> local = BuildQueryable(this->queryable.ToSet());
  uint min = local.Min<uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinWhere)
{
  uint expected = 12;
  uint min = this->queryable
    .Where([](uint value) { return value > 10; })
    ->Min<uint>([](uint value) { return value; });
  ASSERT_EQ(expected, min);
}
