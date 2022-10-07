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
  size_t expectedMax = 867;
  char expectedMaxChar = 't';
  std::string expectedMaxStr = "the cw";
  QueryableVector<size_t> queryable;
  QueryableVector<std::string> queryableStrings;

  MaxFunctionalTest() :
    queryable(BuildQueryable(std::vector<size_t>({ 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, expectedMax, 1, 12 }))),
    queryableStrings(BuildQueryable(std::vector<std::string>({ "nbc", "fox", "abc", "cbs", "the cw"})))
  {
  }

  void SetUp() override
  {
  }

  void TearDown() override {}
};

TEST_F(MaxFunctionalTest, MaxItemUninitialized)
{
  QueryableVector<Person> emptyQueryable(BuildQueryable(std::vector<Person>()));
  Person max = emptyQueryable
    .MaxItem<double>([](Person p) { return p.GetAge(); });

  ASSERT_DOUBLE_EQ(0.0, max.GetAge());
}

TEST_F(MaxFunctionalTest, MaxUninitialized)
{
  QueryableVector<Person> emptyQueryable(BuildQueryable(std::vector<Person>()));
  double max = emptyQueryable
    .Max<double>([](Person p) { return p.GetAge(); });
  ASSERT_DOUBLE_EQ(0.0, max);
}

TEST_F(MaxFunctionalTest, MaxUninitializedDefault)
{
  QueryableVector<double> emptyQueryable(BuildQueryable(std::vector<double>()));
  double max = emptyQueryable.Max();
  ASSERT_DOUBLE_EQ(0.0, max);
}

TEST_F(MaxFunctionalTest, MaxSeededUninitialized)
{
  double seed = 9;
  QueryableVector<Person> emptyQueryable(BuildQueryable(std::vector<Person>()));
  double max = emptyQueryable
    .Max<double>([](Person p) { return p.GetAge(); }, seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxSeededUninitializedDefault)
{
  double seed = 9;
  QueryableVector<double> emptyQueryable(BuildQueryable(std::vector<double>()));
  double max = emptyQueryable.Max(seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxItemString)
{
  std::string max = this->queryableStrings
    .MaxItem<char>([](std::string str) { return str[0]; });
  ASSERT_STREQ(expectedMaxStr.c_str(), max.c_str());
}

TEST_F(MaxFunctionalTest, MaxString)
{
  char max = this->queryableStrings
    .Max<char>([](std::string str) { return str[0]; });
  ASSERT_EQ(expectedMaxChar, max);
}

TEST_F(MaxFunctionalTest, MaxSmallerSeedString)
{
  char seed = 'Z';
  char max = this->queryableStrings
    .Max<char>([](std::string str) { return str[0]; }, seed);
  ASSERT_EQ(expectedMaxChar, max);
}

TEST_F(MaxFunctionalTest, MaxLargerSeedString)
{
  char seed = 'v';
  char max = this->queryableStrings
    .Max<char>([](std::string str) { return str[0]; }, seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxItemDeque)
{
  QueryableDeque<size_t> local = BuildQueryable(this->queryable.ToDeque());
  size_t max = local
    .MaxItem<size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxDeque)
{
  QueryableDeque<size_t> local = BuildQueryable(this->queryable.ToDeque());
  size_t max = local
    .Max<size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxDequeDefault)
{
  QueryableDeque<size_t> local = BuildQueryable(this->queryable.ToDeque());
  size_t max = local.Max();
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxSeededLowerDeque)
{
  size_t seed = this->expectedMax + 1;
  QueryableDeque<size_t> local = BuildQueryable(this->queryable.ToDeque());
  size_t max = local
    .Max<size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxSeededLowerDequeDefault)
{
  size_t seed = this->expectedMax + 1;
  QueryableDeque<size_t> local = BuildQueryable(this->queryable.ToDeque());
  size_t max = local.Max(seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxSeededHigherDeque)
{
  size_t seed = this->expectedMax - 1;
  QueryableDeque<size_t> local = BuildQueryable(this->queryable.ToDeque());
  size_t max = local
    .Max<size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxSeededHigherDequeDefault)
{
  size_t seed = this->expectedMax - 1;
  QueryableDeque<size_t> local = BuildQueryable(this->queryable.ToDeque());
  size_t max = local.Max(seed);
  ASSERT_EQ(this->expectedMax, max);
}


TEST_F(MaxFunctionalTest, MaxItemList)
{
  QueryableList<size_t> local = BuildQueryable(this->queryable.ToList());
  size_t max = local
    .Max<size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxList)
{
  QueryableList<size_t> local = BuildQueryable(this->queryable.ToList());
  size_t max = local
    .Max<size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxListDefault)
{
  QueryableList<size_t> local = BuildQueryable(this->queryable.ToList());
  size_t max = local.Max();
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxSeededLowerList)
{
  size_t seed = this->expectedMax + 1;
  QueryableList<size_t> local = BuildQueryable(this->queryable.ToList());
  size_t max = local
    .Max<size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxSeededLowerListDefault)
{
  size_t seed = this->expectedMax + 1;
  QueryableList<size_t> local = BuildQueryable(this->queryable.ToList());
  size_t max = local.Max(seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxSeededHigherList)
{
  size_t seed = this->expectedMax - 1;
  QueryableList<size_t> local = BuildQueryable(this->queryable.ToList());
  size_t max = local
    .Max<size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxSeededHigherListDefault)
{
  size_t seed = this->expectedMax - 1;
  QueryableList<size_t> local = BuildQueryable(this->queryable.ToList());
  size_t max = local.Max(seed);
  ASSERT_EQ(this->expectedMax, max);
}


TEST_F(MaxFunctionalTest, MaxItemMultiSet)
{
  QueryableMultiSet<size_t> local = BuildQueryable(this->queryable.ToMultiSet());
  size_t max = local
    .Max<size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxMultiSet)
{
  QueryableMultiSet<size_t> local = BuildQueryable(this->queryable.ToMultiSet());
  size_t max = local
    .Max<size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxMultiSetDefault)
{
  QueryableMultiSet<size_t> local = BuildQueryable(this->queryable.ToMultiSet());
  size_t max = local.Max();
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxSeededLowerMultiSet)
{
  size_t seed = this->expectedMax + 1;
  QueryableMultiSet<size_t> local = BuildQueryable(this->queryable.ToMultiSet());
  size_t max = local
    .Max<size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxSeededLowerMultiSetDefault)
{
  size_t seed = this->expectedMax + 1;
  QueryableMultiSet<size_t> local = BuildQueryable(this->queryable.ToMultiSet());
  size_t max = local.Max(seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxSeededHigherMultiSet)
{
  size_t seed = this->expectedMax - 1;
  QueryableMultiSet<size_t> local = BuildQueryable(this->queryable.ToMultiSet());
  size_t max = local
    .Max<size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxSeededHigherMultiSetDefault)
{
  size_t seed = this->expectedMax - 1;
  QueryableMultiSet<size_t> local = BuildQueryable(this->queryable.ToMultiSet());
  size_t max = local.Max(seed);
  ASSERT_EQ(this->expectedMax, max);
}


TEST_F(MaxFunctionalTest, MaxItemSet)
{
  QueryableSet<size_t> local = BuildQueryable(this->queryable.ToSet());
  size_t max = local
    .MaxItem<size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxSet)
{
  QueryableSet<size_t> local = BuildQueryable(this->queryable.ToSet());
  size_t max = local
    .Max<size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxSetDefault)
{
  QueryableSet<size_t> local = BuildQueryable(this->queryable.ToSet());
  size_t max = local.Max();
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxSeededLowerSet)
{
  size_t seed = this->expectedMax + 1;
  QueryableSet<size_t> local = BuildQueryable(this->queryable.ToSet());
  size_t max = local
    .Max<size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxSeededLowerSetDefault)
{
  size_t seed = this->expectedMax + 1;
  QueryableSet<size_t> local = BuildQueryable(this->queryable.ToSet());
  size_t max = local.Max(seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxSeededHigherSet)
{
  size_t seed = this->expectedMax - 1;
  QueryableSet<size_t> local = BuildQueryable(this->queryable.ToSet());
  size_t max = local
    .Max<size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(this->expectedMax, max);
}


TEST_F(MaxFunctionalTest, MaxSeededHigherSetDefault)
{
  size_t seed = this->expectedMax - 1;
  QueryableSet<size_t> local = BuildQueryable(this->queryable.ToSet());
  size_t max = local.Max(seed);
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxWhere)
{
  size_t expected = 8;
  size_t max = this->queryable
    .Where([](size_t value) { return value < 10; })
    .Max<size_t>([](size_t value) { return value; });
  ASSERT_EQ(expected, max);
}

TEST_F(MaxFunctionalTest, MaxWhereDefault)
{
  size_t expected = 8;
  size_t max = this->queryable
    .Where([](size_t value) { return value < 10; })
    .Max();
  ASSERT_EQ(expected, max);
}
