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
  size_t expectedMin = 1;
  char expectedMinChar = 'a';
  std::string expectedMinStr = "abc";
  QueryableVector<size_t> queryable;
  QueryableVector<std::string> queryableStrings;

  MinFunctionalTest() :
    queryable(BuildQueryable(std::vector<size_t>({ 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, expectedMin, 867, 12 }))),
    queryableStrings(BuildQueryable(std::vector<std::string>({ "nbc", "fox", "abc", "cbs", "the cw"})))
  {
  }

  void SetUp() override
  {
  }

  void TearDown() override {}
};

TEST_F(MinFunctionalTest, MinItemUninitialized)
{
  QueryableVector<Person> emptyQueryable(BuildQueryable(std::vector<Person>()));
  Person min = emptyQueryable
    .MinItem<double>([](Person p) { return p.GetAge(); });
  ASSERT_DOUBLE_EQ(0.0, min.GetAge());
}

TEST_F(MinFunctionalTest, MinUninitialized)
{
  QueryableVector<Person> emptyQueryable(BuildQueryable(std::vector<Person>()));
  double min = emptyQueryable
    .Min<double>([](Person p) { return p.GetAge(); });
  ASSERT_DOUBLE_EQ(0.0, min);
}

// TEST_F(MinFunctionalTest, MinUninitializedDefault)
// {
//   QueryableVector<double> emptyQueryable(BuildQueryable(std::vector<double>()));
//   double min = emptyQueryable.Min();
//   ASSERT_DOUBLE_EQ(0.0, min);
// }

TEST_F(MinFunctionalTest, MinSeededUninitialized)
{
  double seed = 9;
  QueryableVector<Person> emptyQueryable(BuildQueryable(std::vector<Person>()));
  double min = emptyQueryable
    .Min<double>([](Person p) { return p.GetAge(); }, seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinSeededUninitializedDefault)
{
  double seed = 9;
  QueryableVector<double> emptyQueryable(BuildQueryable(std::vector<double>()));
  double min = emptyQueryable.Min(seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinItemString)
{
  std::string min = this->queryableStrings
    .MinItem<char>([](std::string str) { return str[0]; });
  ASSERT_STREQ(expectedMinStr.c_str(), min.c_str());
}

TEST_F(MinFunctionalTest, MinString)
{
  char min = this->queryableStrings
    .Min<char>([](std::string str) { return str[0]; });
  ASSERT_EQ(expectedMinChar, min);
}

TEST_F(MinFunctionalTest, MinSmallerSeedString)
{
  char seed = 'Z';
  char min = this->queryableStrings
    .Min<char>([](std::string str) { return str[0]; }, seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinLargerSeedString)
{
  char seed = 'c';
  char min = this->queryableStrings
    .Min<char>([](std::string str) { return str[0]; }, seed);
  ASSERT_EQ(expectedMinChar, min);
}

TEST_F(MinFunctionalTest, MinItemDeque)
{
  QueryableDeque<size_t> local = BuildQueryable(this->queryable.ToDeque());
  size_t min = local
    .MinItem<size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinDeque)
{
  QueryableDeque<size_t> local = BuildQueryable(this->queryable.ToDeque());
  size_t min = local
    .Min<size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinDequeDefault)
{
  QueryableDeque<size_t> local = BuildQueryable(this->queryable.ToDeque());
  size_t min = local.Min();
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinSeededLowerDeque)
{
  size_t seed = 0;
  QueryableDeque<size_t> local = BuildQueryable(this->queryable.ToDeque());
  size_t min = local
    .Min<size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinSeededLowerDequeDefault)
{
  size_t seed = 0;
  QueryableDeque<size_t> local = BuildQueryable(this->queryable.ToDeque());
  size_t min = local.Min(seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinSeededHigherDeque)
{
  size_t seed = expectedMin + 1;
  QueryableDeque<size_t> local = BuildQueryable(this->queryable.ToDeque());
  size_t min = local
    .Min<size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinSeededHigherDequeDefault)
{
  size_t seed = expectedMin + 1;
  QueryableDeque<size_t> local = BuildQueryable(this->queryable.ToDeque());
  size_t min = local.Min(seed);
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinItemList)
{
  QueryableList<size_t> local = BuildQueryable(this->queryable.ToList());
  size_t min = local
    .MinItem<size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinList)
{
  QueryableList<size_t> local = BuildQueryable(this->queryable.ToList());
  size_t min = local
    .Min<size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinListDefault)
{
  QueryableList<size_t> local = BuildQueryable(this->queryable.ToList());
  size_t min = local.Min();
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinSeededLowerList)
{
  size_t seed = 0;
  QueryableList<size_t> local = BuildQueryable(this->queryable.ToList());
  size_t min = local
    .Min<size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinSeededLowerListDefault)
{
  size_t seed = 0;
  QueryableList<size_t> local = BuildQueryable(this->queryable.ToList());
  size_t min = local.Min(seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinSeededHigherList)
{
  size_t seed = expectedMin + 1;
  QueryableList<size_t> local = BuildQueryable(this->queryable.ToList());
  size_t min = local
    .Min<size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinSeededHigherListDefault)
{
  size_t seed = expectedMin + 1;
  QueryableList<size_t> local = BuildQueryable(this->queryable.ToList());
  size_t min = local.Min(seed);
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinItemMultiSet)
{
  QueryableMultiSet<size_t> local = BuildQueryable(this->queryable.ToMultiSet());
  size_t min = local
    .MinItem<size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinMultiSet)
{
  QueryableMultiSet<size_t> local = BuildQueryable(this->queryable.ToMultiSet());
  size_t min = local
    .Min<size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinMultiSetDefault)
{
  QueryableMultiSet<size_t> local = BuildQueryable(this->queryable.ToMultiSet());
  size_t min = local.Min();
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinSeededLowerMultiSet)
{
  size_t seed = 0;
  QueryableMultiSet<size_t> local = BuildQueryable(this->queryable.ToMultiSet());
  size_t min = local
    .Min<size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinSeededLowerMultiSetDefault)
{
  size_t seed = 0;
  QueryableMultiSet<size_t> local = BuildQueryable(this->queryable.ToMultiSet());
  size_t min = local.Min(seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinSeededHigherMultiSet)
{
  size_t seed = expectedMin + 1;
  QueryableMultiSet<size_t> local = BuildQueryable(this->queryable.ToMultiSet());
  size_t min = local
    .Min<size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinSeededHigherMultiSetDefault)
{
  size_t seed = expectedMin + 1;
  QueryableMultiSet<size_t> local = BuildQueryable(this->queryable.ToMultiSet());
  size_t min = local.Min(seed);
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinItemSet)
{
  QueryableSet<size_t> local = BuildQueryable(this->queryable.ToSet());
  size_t min = local
    .MinItem<size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinSet)
{
  QueryableSet<size_t> local = BuildQueryable(this->queryable.ToSet());
  size_t min = local
    .Min<size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinSetDefault)
{
  QueryableSet<size_t> local = BuildQueryable(this->queryable.ToSet());
  size_t min = local.Min();
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinSeededLowerSet)
{
  size_t seed = 0;
  QueryableSet<size_t> local = BuildQueryable(this->queryable.ToSet());
  size_t min = local
    .Min<size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinSeededLowerSetDefault)
{
  size_t seed = 0;
  QueryableSet<size_t> local = BuildQueryable(this->queryable.ToSet());
  size_t min = local.Min(seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinSeededHigherSet)
{
  size_t seed = expectedMin + 1;
  QueryableSet<size_t> local = BuildQueryable(this->queryable.ToSet());
  size_t min = local
    .Min<size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinSeededHigherSetDefault)
{
  size_t seed = expectedMin + 1;
  QueryableSet<size_t> local = BuildQueryable(this->queryable.ToSet());
  size_t min = local.Min(seed);
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinWhere)
{
  size_t expected = 12;
  size_t min = this->queryable
    .Where([](size_t value) { return value > 10; })
    .Min<size_t>([](size_t value) { return value; });
  ASSERT_EQ(expected, min);
}

TEST_F(MinFunctionalTest, MinWhereDefault)
{
  size_t expected = 12;
  size_t min = this->queryable
    .Where([](size_t value) { return value > 10; })
    .Min();
  ASSERT_EQ(expected, min);
}
