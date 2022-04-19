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

class MinFunctionalTest : public ::testing::Test
{
protected:
  uint expectedMin = 1;
  char expectedMinChar = 'a';
  std::string expectedMinStr = "abc";
  VectorQueryable<uint> queryable;
  VectorQueryable<std::string> queryableStrings;

  void SetUp() override
  {
    this->queryable = BuildQueryable2(std::vector<uint>({ 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, expectedMin, 867, 12 }));
    this->queryableStrings = BuildQueryable2(std::vector<std::string>({ "nbc", "fox", "abc", "cbs", "the cw"}));
  }

  void TearDown() override {}
};

TEST_F(MinFunctionalTest, MinItemUninitialized)
{
  VectorQueryable<Person> emptyQueryable;
  Person min = emptyQueryable.MinItem<double>([](Person p) { return p.GetAge(); });
  ASSERT_DOUBLE_EQ(0.0, min.GetAge());
}

TEST_F(MinFunctionalTest, MinUninitialized)
{
  VectorQueryable<Person> emptyQueryable;
  double min = emptyQueryable.Min<double>([](Person p) { return p.GetAge(); });
  ASSERT_DOUBLE_EQ(0.0, min);
}

TEST_F(MinFunctionalTest, MinUninitializedDefault)
{
  VectorQueryable<double> emptyQueryable;
  double min = emptyQueryable.Min();
  ASSERT_DOUBLE_EQ(0.0, min);
}

TEST_F(MinFunctionalTest, MinSeededUninitialized)
{
  double seed = 9;
  VectorQueryable<Person> emptyQueryable;
  double min = emptyQueryable.Min<double>([](Person p) { return p.GetAge(); }, seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinSeededUninitializedDefault)
{
  double seed = 9;
  VectorQueryable<double> emptyQueryable;
  double min = emptyQueryable.Min(seed);
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
  DequeQueryable<uint> local = BuildQueryable2(this->queryable.ToDeque());
  uint min = local.MinItem<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinDeque)
{
  DequeQueryable<uint> local = BuildQueryable2(this->queryable.ToDeque());
  uint min = local.Min<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinDequeDefault)
{
  DequeQueryable<uint> local = BuildQueryable2(this->queryable.ToDeque());
  uint min = local.Min();
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinSeededLowerDeque)
{
  uint seed = 0;
  DequeQueryable<uint> local = BuildQueryable2(this->queryable.ToDeque());
  uint min = local.Min<uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinSeededLowerDequeDefault)
{
  uint seed = 0;
  DequeQueryable<uint> local = BuildQueryable2(this->queryable.ToDeque());
  uint min = local.Min(seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinSeededHigherDeque)
{
  uint seed = expectedMin + 1;
  DequeQueryable<uint> local = BuildQueryable2(this->queryable.ToDeque());
  uint min = local.Min<uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinSeededHigherDequeDefault)
{
  uint seed = expectedMin + 1;
  DequeQueryable<uint> local = BuildQueryable2(this->queryable.ToDeque());
  uint min = local.Min(seed);
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinItemList)
{
  ListQueryable<uint> local = BuildQueryable2(this->queryable.ToList());
  uint min = local.MinItem<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinList)
{
  ListQueryable<uint> local = BuildQueryable2(this->queryable.ToList());
  uint min = local.Min<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinListDefault)
{
  ListQueryable<uint> local = BuildQueryable2(this->queryable.ToList());
  uint min = local.Min();
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinSeededLowerList)
{
  uint seed = 0;
  ListQueryable<uint> local = BuildQueryable2(this->queryable.ToList());
  uint min = local.Min<uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinSeededLowerListDefault)
{
  uint seed = 0;
  ListQueryable<uint> local = BuildQueryable2(this->queryable.ToList());
  uint min = local.Min(seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinSeededHigherList)
{
  uint seed = expectedMin + 1;
  ListQueryable<uint> local = BuildQueryable2(this->queryable.ToList());
  uint min = local.Min<uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinSeededHigherListDefault)
{
  uint seed = expectedMin + 1;
  ListQueryable<uint> local = BuildQueryable2(this->queryable.ToList());
  uint min = local.Min(seed);
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinItemMultiSet)
{
  MultiSetQueryable<uint> local = BuildQueryable2(this->queryable.ToMultiSet());
  uint min = local.MinItem<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinMultiSet)
{
  MultiSetQueryable<uint> local = BuildQueryable2(this->queryable.ToMultiSet());
  uint min = local.Min<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinMultiSetDefault)
{
  MultiSetQueryable<uint> local = BuildQueryable2(this->queryable.ToMultiSet());
  uint min = local.Min();
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinSeededLowerMultiSet)
{
  uint seed = 0;
  MultiSetQueryable<uint> local = BuildQueryable2(this->queryable.ToMultiSet());
  uint min = local.Min<uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinSeededLowerMultiSetDefault)
{
  uint seed = 0;
  MultiSetQueryable<uint> local = BuildQueryable2(this->queryable.ToMultiSet());
  uint min = local.Min(seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinSeededHigherMultiSet)
{
  uint seed = expectedMin + 1;
  MultiSetQueryable<uint> local = BuildQueryable2(this->queryable.ToMultiSet());
  uint min = local.Min<uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinSeededHigherMultiSetDefault)
{
  uint seed = expectedMin + 1;
  MultiSetQueryable<uint> local = BuildQueryable2(this->queryable.ToMultiSet());
  uint min = local.Min(seed);
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinItemSet)
{
  SetQueryable<uint> local = BuildQueryable2(this->queryable.ToSet());
  uint min = local.MinItem<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinSet)
{
  SetQueryable<uint> local = BuildQueryable2(this->queryable.ToSet());
  uint min = local.Min<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinSetDefault)
{
  SetQueryable<uint> local = BuildQueryable2(this->queryable.ToSet());
  uint min = local.Min();
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinSeededLowerSet)
{
  uint seed = 0;
  SetQueryable<uint> local = BuildQueryable2(this->queryable.ToSet());
  uint min = local.Min<uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinSeededLowerSetDefault)
{
  uint seed = 0;
  SetQueryable<uint> local = BuildQueryable2(this->queryable.ToSet());
  uint min = local.Min(seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinSeededHigherSet)
{
  uint seed = expectedMin + 1;
  SetQueryable<uint> local = BuildQueryable2(this->queryable.ToSet());
  uint min = local.Min<uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinSeededHigherSetDefault)
{
  uint seed = expectedMin + 1;
  SetQueryable<uint> local = BuildQueryable2(this->queryable.ToSet());
  uint min = local.Min(seed);
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinWhere)
{
  uint expected = 12;
  uint min = this->queryable
    .Where([](uint value) { return value > 10; })
    .Min<uint>([](uint value) { return value; });
  ASSERT_EQ(expected, min);
}

TEST_F(MinFunctionalTest, MinWhereDefault)
{
  uint expected = 12;
  uint min = this->queryable
    .Where([](uint value) { return value > 10; })
    .Min();
  ASSERT_EQ(expected, min);
}
