#include <gtest/gtest.h>

#include <array>
#include <deque>
#include <exception>
#include <iostream>
#include <list>
#include <set>
#include <string>
#include <vector>

#include "../../../DataStructures/Gender.hpp"
#include "../../../DataStructures/Person.hpp"
#include "../../../DataStructures/PersonLibrary.hpp"

#include "../../../Queryable/QueryBuilder.hpp"


using namespace QueryBuilder;

class MaxFunctionalTest : public ::testing::Test
{
protected:
  uint expectedMax = 867;
  char expectedMaxChar = 't';
  std::string expectedMaxStr = "the cw";
  VectorQueryable<uint> queryable;
  VectorQueryable<std::string> queryableStrings;

  void SetUp() override
  {
    this->queryable = BuildQueryable2(std::vector<uint>({ 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, expectedMax, 1, 12 }));
    this->queryableStrings = BuildQueryable2(std::vector<std::string>({ "nbc", "fox", "abc", "cbs", "the cw"}));
  }

  void TearDown() override {}
};

TEST_F(MaxFunctionalTest, MaxItemUninitialized)
{
  VectorQueryable<Person> emptyQueryable;
  Person max = emptyQueryable.MaxItem<double>([](Person p) { return p.GetAge(); });
  ASSERT_DOUBLE_EQ(0.0, max.GetAge());
}

TEST_F(MaxFunctionalTest, MaxUninitialized)
{
  VectorQueryable<Person> emptyQueryable;
  double max = emptyQueryable.Max<double>([](Person p) { return p.GetAge(); });
  ASSERT_DOUBLE_EQ(0.0, max);
}

TEST_F(MaxFunctionalTest, MaxUninitializedDefault)
{
  VectorQueryable<double> emptyQueryable;
  double max = emptyQueryable.Max();
  ASSERT_DOUBLE_EQ(0.0, max);
}

TEST_F(MaxFunctionalTest, MaxSeededUninitialized)
{
  double seed = 9;
  VectorQueryable<Person> emptyQueryable;
  double max = emptyQueryable.Max<double>([](Person p) { return p.GetAge(); }, seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxSeededUninitializedDefault)
{
  double seed = 9;
  VectorQueryable<double> emptyQueryable;
  double max = emptyQueryable.Max(seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxItemString)
{
  std::string max = this->queryableStrings.MaxItem<char>([](std::string str) { return str[0]; });
  ASSERT_STREQ(expectedMaxStr.c_str(), max.c_str());
}

TEST_F(MaxFunctionalTest, MaxString)
{
  char max = this->queryableStrings.Max<char>([](std::string str) { return str[0]; });
  ASSERT_EQ(expectedMaxChar, max);
}

TEST_F(MaxFunctionalTest, MaxSmallerSeedString)
{
  char seed = 'Z';
  char max = this->queryableStrings.Max<char>([](std::string str) { return str[0]; }, seed);
  ASSERT_EQ(expectedMaxChar, max);
}

TEST_F(MaxFunctionalTest, MaxLargerSeedString)
{
  char seed = 'v';
  char max = this->queryableStrings.Max<char>([](std::string str) { return str[0]; }, seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxItemDeque)
{
  DequeQueryable<uint> local = BuildQueryable2(this->queryable.ToDeque());
  uint max = local.MaxItem<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxDeque)
{
  DequeQueryable<uint> local = BuildQueryable2(this->queryable.ToDeque());
  uint max = local.Max<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxDequeDefault)
{
  DequeQueryable<uint> local = BuildQueryable2(this->queryable.ToDeque());
  uint max = local.Max();
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxSeededLowerDeque)
{
  uint seed = this->expectedMax + 1;
  DequeQueryable<uint> local = BuildQueryable2(this->queryable.ToDeque());
  uint max = local.Max<uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxSeededLowerDequeDefault)
{
  uint seed = this->expectedMax + 1;
  DequeQueryable<uint> local = BuildQueryable2(this->queryable.ToDeque());
  uint max = local.Max(seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxSeededHigherDeque)
{
  uint seed = this->expectedMax - 1;
  DequeQueryable<uint> local = BuildQueryable2(this->queryable.ToDeque());
  uint max = local.Max<uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxSeededHigherDequeDefault)
{
  uint seed = this->expectedMax - 1;
  DequeQueryable<uint> local = BuildQueryable2(this->queryable.ToDeque());
  uint max = local.Max(seed);
  ASSERT_EQ(this->expectedMax, max);
}


TEST_F(MaxFunctionalTest, MaxItemList)
{
  ListQueryable<uint> local = BuildQueryable2(this->queryable.ToList());
  uint max = local.MaxItem<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxList)
{
  ListQueryable<uint> local = BuildQueryable2(this->queryable.ToList());
  uint max = local.Max<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxListDefault)
{
  ListQueryable<uint> local = BuildQueryable2(this->queryable.ToList());
  uint max = local.Max();
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxSeededLowerList)
{
  uint seed = this->expectedMax + 1;
  ListQueryable<uint> local = BuildQueryable2(this->queryable.ToList());
  uint max = local.Max<uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxSeededLowerListDefault)
{
  uint seed = this->expectedMax + 1;
  ListQueryable<uint> local = BuildQueryable2(this->queryable.ToList());
  uint max = local.Max(seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxSeededHigherList)
{
  uint seed = this->expectedMax - 1;
  ListQueryable<uint> local = BuildQueryable2(this->queryable.ToList());
  uint max = local.Max<uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxSeededHigherListDefault)
{
  uint seed = this->expectedMax - 1;
  ListQueryable<uint> local = BuildQueryable2(this->queryable.ToList());
  uint max = local.Max(seed);
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxItemMultiSet)
{
  MultiSetQueryable<uint> local = BuildQueryable2(this->queryable.ToMultiSet());
  uint max = local.MaxItem<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxMultiSet)
{
  MultiSetQueryable<uint> local = BuildQueryable2(this->queryable.ToMultiSet());
  uint max = local.Max<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxMultiSetDefault)
{
  MultiSetQueryable<uint> local = BuildQueryable2(this->queryable.ToMultiSet());
  uint max = local.Max();
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxSeededLowerMultiSet)
{
  uint seed = this->expectedMax + 1;
  MultiSetQueryable<uint> local = BuildQueryable2(this->queryable.ToMultiSet());
  uint max = local.Max<uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxSeededLowerMultiSetDefault)
{
  uint seed = this->expectedMax + 1;
  MultiSetQueryable<uint> local = BuildQueryable2(this->queryable.ToMultiSet());
  uint max = local.Max(seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxSeededHigherMultiSet)
{
  uint seed = this->expectedMax - 1;
  MultiSetQueryable<uint> local = BuildQueryable2(this->queryable.ToMultiSet());
  uint max = local.Max<uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxSeededHigherMultiSetDefault)
{
  uint seed = this->expectedMax - 1;
  MultiSetQueryable<uint> local = BuildQueryable2(this->queryable.ToMultiSet());
  uint max = local.Max(seed);
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxItemSet)
{
  SetQueryable<uint> local = BuildQueryable2(this->queryable.ToSet());
  uint max = local.MaxItem<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxSet)
{
  SetQueryable<uint> local = BuildQueryable2(this->queryable.ToSet());
  uint max = local.Max<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxSetDefault)
{
  SetQueryable<uint> local = BuildQueryable2(this->queryable.ToSet());
  uint max = local.Max();
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxSeededLowerSet)
{
  uint seed = this->expectedMax + 1;
  SetQueryable<uint> local = BuildQueryable2(this->queryable.ToSet());
  uint max = local.Max<uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxSeededLowerSetDefault)
{
  uint seed = this->expectedMax + 1;
  SetQueryable<uint> local = BuildQueryable2(this->queryable.ToSet());
  uint max = local.Max(seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxSeededHigherSet)
{
  uint seed = this->expectedMax - 1;
  SetQueryable<uint> local = BuildQueryable2(this->queryable.ToSet());
  uint max = local.Max<uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxSeededHigherSetDefault)
{
  uint seed = this->expectedMax - 1;
  SetQueryable<uint> local = BuildQueryable2(this->queryable.ToSet());
  uint max = local.Max(seed);
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxWhere)
{
  uint expected = 8;
  uint max = this->queryable
    .Where([](uint value) { return value < 10; })
    .Max<uint>([](uint value) { return value; });
  ASSERT_EQ(expected, max);
}

TEST_F(MaxFunctionalTest, MaxWhereDefault)
{
  uint expected = 8;
  uint max = this->queryable
    .Where([](uint value) { return value < 10; })
    .Max();
  ASSERT_EQ(expected, max);
}
