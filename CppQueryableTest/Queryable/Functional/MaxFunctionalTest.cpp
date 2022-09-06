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
  IQueryable<size_t> queryable;
  IQueryable<std::string> queryableStrings;

  MaxFunctionalTest() :
    queryable(BuildQueryable2(std::vector<size_t>({ 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, expectedMax, 1, 12 }))),
    queryableStrings(BuildQueryable2(std::vector<std::string>({ "nbc", "fox", "abc", "cbs", "the cw"})))
  {
  }

  void SetUp() override
  {
  }

  void TearDown() override {}
};

TEST_F(MaxFunctionalTest, MaxItemTemplateUninitialized)
{
  IQueryable<Person> emptyQueryable(BuildQueryable2(std::vector<Person>()));
  Person max = emptyQueryable
    .MaxItem<std::vector, double>([](Person p) { return p.GetAge(); });

  ASSERT_DOUBLE_EQ(0.0, max.GetAge());
}

TEST_F(MaxFunctionalTest, MaxItemAsVectorUninitialized)
{
  IQueryable<Person> emptyQueryable(BuildQueryable2(std::vector<Person>()));
  Person max = emptyQueryable
    .AsQueryableVector()
    .MaxItem<double>([](Person p) { return p.GetAge(); });

  ASSERT_DOUBLE_EQ(0.0, max.GetAge());
}

TEST_F(MaxFunctionalTest, MaxItemExtendedUninitialized)
{
  IQueryable<Person> emptyQueryable(BuildQueryable2(std::vector<Person>()));
  Person max = emptyQueryable
    .AsExtendedQueryable<std::vector>()
    .MaxItem<double>([](Person p) { return p.GetAge(); });

  ASSERT_DOUBLE_EQ(0.0, max.GetAge());
}

TEST_F(MaxFunctionalTest, MaxTemplateUninitialized)
{
  IQueryable<Person> emptyQueryable(BuildQueryable2(std::vector<Person>()));
  double max = emptyQueryable
    .Max<std::vector, double>([](Person p) { return p.GetAge(); });
  ASSERT_DOUBLE_EQ(0.0, max);
}

TEST_F(MaxFunctionalTest, MaxAsVectorUninitialized)
{
  IQueryable<Person> emptyQueryable(BuildQueryable2(std::vector<Person>()));
  double max = emptyQueryable
    .AsQueryableVector()
    .Max<double>([](Person p) { return p.GetAge(); });
  ASSERT_DOUBLE_EQ(0.0, max);
}

TEST_F(MaxFunctionalTest, MaxExtendedUninitialized)
{
  IQueryable<Person> emptyQueryable(BuildQueryable2(std::vector<Person>()));
  double max = emptyQueryable
    .AsExtendedQueryable<std::vector>()
    .Max<double>([](Person p) { return p.GetAge(); });
  ASSERT_DOUBLE_EQ(0.0, max);
}

TEST_F(MaxFunctionalTest, MaxUninitializedDefault)
{
  IQueryable<double> emptyQueryable(BuildQueryable2(std::vector<double>()));
  double max = emptyQueryable.Max();
  ASSERT_DOUBLE_EQ(0.0, max);
}

TEST_F(MaxFunctionalTest, MaxTemplateSeededUninitialized)
{
  double seed = 9;
  IQueryable<Person> emptyQueryable(BuildQueryable2(std::vector<Person>()));
  double max = emptyQueryable
    .Max<std::vector, double>([](Person p) { return p.GetAge(); }, seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxAsVectorSeededUninitialized)
{
  double seed = 9;
  IQueryable<Person> emptyQueryable(BuildQueryable2(std::vector<Person>()));
  double max = emptyQueryable
    .AsQueryableVector()
    .Max<double>([](Person p) { return p.GetAge(); }, seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxExtendedSeededUninitialized)
{
  double seed = 9;
  IQueryable<Person> emptyQueryable(BuildQueryable2(std::vector<Person>()));
  double max = emptyQueryable
    .AsExtendedQueryable<std::vector>()
    .Max<double>([](Person p) { return p.GetAge(); }, seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxSeededUninitializedDefault)
{
  double seed = 9;
  IQueryable<double> emptyQueryable(BuildQueryable2(std::vector<double>()));
  double max = emptyQueryable.Max(seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxItemTemplateString)
{
  std::string max = this->queryableStrings
    .MaxItem<std::vector, char>([](std::string str) { return str[0]; });
  ASSERT_STREQ(expectedMaxStr.c_str(), max.c_str());
}

TEST_F(MaxFunctionalTest, MaxItemAsVectorString)
{
  std::string max = this->queryableStrings
    .AsQueryableVector()
    .MaxItem<char>([](std::string str) { return str[0]; });
  ASSERT_STREQ(expectedMaxStr.c_str(), max.c_str());
}

TEST_F(MaxFunctionalTest, MaxItemExtendedString)
{
  std::string max = this->queryableStrings
    .AsExtendedQueryable<std::vector>()
    .MaxItem<char>([](std::string str) { return str[0]; });
  ASSERT_STREQ(expectedMaxStr.c_str(), max.c_str());
}

TEST_F(MaxFunctionalTest, MaxTemplateString)
{
  char max = this->queryableStrings
    .Max<std::vector, char>([](std::string str) { return str[0]; });
  ASSERT_EQ(expectedMaxChar, max);
}

TEST_F(MaxFunctionalTest, MaxAsVectorString)
{
  char max = this->queryableStrings
    .AsQueryableVector()
    .Max<char>([](std::string str) { return str[0]; });
  ASSERT_EQ(expectedMaxChar, max);
}

TEST_F(MaxFunctionalTest, MaxExtendedString)
{
  char max = this->queryableStrings
    .AsExtendedQueryable<std::vector>()
    .Max<char>([](std::string str) { return str[0]; });
  ASSERT_EQ(expectedMaxChar, max);
}

TEST_F(MaxFunctionalTest, MaxTemplateSmallerSeedString)
{
  char seed = 'Z';
  char max = this->queryableStrings
    .Max<std::vector, char>([](std::string str) { return str[0]; }, seed);
  ASSERT_EQ(expectedMaxChar, max);
}

TEST_F(MaxFunctionalTest, MaxAsVectorSmallerSeedString)
{
  char seed = 'Z';
  char max = this->queryableStrings
    .AsQueryableVector()
    .Max<char>([](std::string str) { return str[0]; }, seed);
  ASSERT_EQ(expectedMaxChar, max);
}

TEST_F(MaxFunctionalTest, MaxExtendedSmallerSeedString)
{
  char seed = 'Z';
  char max = this->queryableStrings
    .AsExtendedQueryable<std::vector>()
    .Max<char>([](std::string str) { return str[0]; }, seed);
  ASSERT_EQ(expectedMaxChar, max);
}

TEST_F(MaxFunctionalTest, MaxTemplateLargerSeedString)
{
  char seed = 'v';
  char max = this->queryableStrings
    .Max<std::vector, char>([](std::string str) { return str[0]; }, seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxAsVectorLargerSeedString)
{
  char seed = 'v';
  char max = this->queryableStrings
    .AsQueryableVector()
    .Max<char>([](std::string str) { return str[0]; }, seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxExtendedLargerSeedString)
{
  char seed = 'v';
  char max = this->queryableStrings
    .AsExtendedQueryable<std::vector>()
    .Max<char>([](std::string str) { return str[0]; }, seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxItemTemplateDeque)
{
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToDeque());
  size_t max = local
    .MaxItem<std::deque, size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxItemAsDeque)
{
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToDeque());
  size_t max = local
    .AsQueryableDeque()
    .MaxItem<size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxItemExtendedDeque)
{
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToDeque());
  size_t max = local
    .AsExtendedQueryable<std::deque>()
    .MaxItem<size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxTemplateDeque)
{
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToDeque());
  size_t max = local
    .Max<std::deque, size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxAsDeque)
{
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToDeque());
  size_t max = local
    .AsQueryableDeque()
    .Max<size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxExtendedDeque)
{
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToDeque());
  size_t max = local
    .AsExtendedQueryable<std::deque>()
    .Max<size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxDequeDefault)
{
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToDeque());
  size_t max = local.Max();
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxTemplateSeededLowerDeque)
{
  size_t seed = this->expectedMax + 1;
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToDeque());
  size_t max = local
    .Max<std::deque, size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxAsDequeSeededLowerDeque)
{
  size_t seed = this->expectedMax + 1;
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToDeque());
  size_t max = local
    .AsQueryableDeque()
    .Max<size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxExtendedSeededLowerDeque)
{
  size_t seed = this->expectedMax + 1;
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToDeque());
  size_t max = local
    .AsExtendedQueryable<std::deque>()
    .Max<size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxSeededLowerDequeDefault)
{
  size_t seed = this->expectedMax + 1;
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToDeque());
  size_t max = local.Max(seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxTemplateSeededHigherDeque)
{
  size_t seed = this->expectedMax - 1;
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToDeque());
  size_t max = local
    .Max<std::deque, size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxAsDequeSeededHigherDeque)
{
  size_t seed = this->expectedMax - 1;
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToDeque());
  size_t max = local
    .AsQueryableDeque()
    .Max<size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxExtendedSeededHigherDeque)
{
  size_t seed = this->expectedMax - 1;
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToDeque());
  size_t max = local
    .AsExtendedQueryable<std::deque>()
    .Max<size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxSeededHigherDequeDefault)
{
  size_t seed = this->expectedMax - 1;
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToDeque());
  size_t max = local.Max(seed);
  ASSERT_EQ(this->expectedMax, max);
}


TEST_F(MaxFunctionalTest, MaxItemTemplateList)
{
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToList());
  size_t max = local
    .MaxItem<std::list, size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxItemAsList)
{
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToList());
  size_t max = local
    .AsQueryableList()
    .MaxItem<size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxItemExtendedList)
{
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToList());
  size_t max = local
    .AsExtendedQueryable<std::list>()
    .MaxItem<size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxTemplateList)
{
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToList());
  size_t max = local
    .Max<std::list, size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxAsList)
{
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToList());
  size_t max = local
    .AsQueryableList()
    .Max<size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxExtendedList)
{
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToList());
  size_t max = local
    .AsExtendedQueryable<std::list>()
    .Max<size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxListDefault)
{
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToList());
  size_t max = local.Max();
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxTemplateSeededLowerList)
{
  size_t seed = this->expectedMax + 1;
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToList());
  size_t max = local
    .Max<std::list, size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxAsListSeededLowerList)
{
  size_t seed = this->expectedMax + 1;
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToList());
  size_t max = local
    .AsQueryableList()
    .Max<size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxExtendedSeededLowerList)
{
  size_t seed = this->expectedMax + 1;
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToList());
  size_t max = local
    .AsExtendedQueryable<std::list>()
    .Max<size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxSeededLowerListDefault)
{
  size_t seed = this->expectedMax + 1;
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToList());
  size_t max = local.Max(seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxTemplateSeededHigherList)
{
  size_t seed = this->expectedMax - 1;
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToList());
  size_t max = local
    .Max<std::list, size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxAsListSeededHigherList)
{
  size_t seed = this->expectedMax - 1;
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToList());
  size_t max = local
    .AsQueryableList()
    .Max<size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxExtendedSeededHigherList)
{
  size_t seed = this->expectedMax - 1;
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToList());
  size_t max = local
    .AsExtendedQueryable<std::list>()
    .Max<size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxSeededHigherListDefault)
{
  size_t seed = this->expectedMax - 1;
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToList());
  size_t max = local.Max(seed);
  ASSERT_EQ(this->expectedMax, max);
}


TEST_F(MaxFunctionalTest, MaxItemTemplateMultiSet)
{
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToMultiSet());
  size_t max = local
    .MaxItem<std::multiset, size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxItemAsMultiSet)
{
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToMultiSet());
  size_t max = local
    .AsQueryableMultiSet()
    .MaxItem<size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxItemExtendedMultiSet)
{
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToMultiSet());
  size_t max = local
    .AsExtendedQueryable<std::multiset>()
    .MaxItem<size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxTemplateMultiSet)
{
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToMultiSet());
  size_t max = local
    .Max<std::multiset, size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxAsMultiSet)
{
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToMultiSet());
  size_t max = local
    .AsQueryableMultiSet()
    .Max<size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxExtendedMultiSet)
{
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToMultiSet());
  size_t max = local
    .AsExtendedQueryable<std::multiset>()
    .Max<size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxMultiSetDefault)
{
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToMultiSet());
  size_t max = local.Max();
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxTemplateSeededLowerMultiSet)
{
  size_t seed = this->expectedMax + 1;
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToMultiSet());
  size_t max = local
    .Max<std::multiset, size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxAsMultiSetSeededLowerMultiSet)
{
  size_t seed = this->expectedMax + 1;
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToMultiSet());
  size_t max = local
    .AsQueryableMultiSet()
    .Max<size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxExtendedSeededLowerMultiSet)
{
  size_t seed = this->expectedMax + 1;
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToMultiSet());
  size_t max = local
    .AsExtendedQueryable<std::multiset>()
    .Max<size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxSeededLowerMultiSetDefault)
{
  size_t seed = this->expectedMax + 1;
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToMultiSet());
  size_t max = local.Max(seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxTemplateSeededHigherMultiSet)
{
  size_t seed = this->expectedMax - 1;
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToMultiSet());
  size_t max = local
    .Max<std::multiset, size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxAsMultiSetSeededHigherMultiSet)
{
  size_t seed = this->expectedMax - 1;
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToMultiSet());
  size_t max = local
    .AsQueryableMultiSet()
    .Max<size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxExtendedSeededHigherMultiSet)
{
  size_t seed = this->expectedMax - 1;
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToMultiSet());
  size_t max = local
    .AsExtendedQueryable<std::multiset>()
    .Max<size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxSeededHigherMultiSetDefault)
{
  size_t seed = this->expectedMax - 1;
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToMultiSet());
  size_t max = local.Max(seed);
  ASSERT_EQ(this->expectedMax, max);
}


TEST_F(MaxFunctionalTest, MaxItemTemplateSet)
{
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToSet());
  size_t max = local
    .MaxItem<std::set, size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxItemAsSet)
{
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToSet());
  size_t max = local
    .AsQueryableSet()
    .MaxItem<size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxItemExtendedSet)
{
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToSet());
  size_t max = local
    .AsExtendedQueryable<std::set>()
    .MaxItem<size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxTemplateSet)
{
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToSet());
  size_t max = local
    .Max<std::set, size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxAsSet)
{
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToSet());
  size_t max = local
    .AsQueryableSet()
    .Max<size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxExtendedSet)
{
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToSet());
  size_t max = local
    .AsExtendedQueryable<std::set>()
    .Max<size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxSetDefault)
{
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToSet());
  size_t max = local.Max();
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxTemplateSeededLowerSet)
{
  size_t seed = this->expectedMax + 1;
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToSet());
  size_t max = local
    .Max<std::set, size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxAsSetSeededLowerSet)
{
  size_t seed = this->expectedMax + 1;
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToSet());
  size_t max = local
    .AsQueryableSet()
    .Max<size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxExtendedSeededLowerSet)
{
  size_t seed = this->expectedMax + 1;
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToSet());
  size_t max = local
    .AsExtendedQueryable<std::set>()
    .Max<size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxSeededLowerSetDefault)
{
  size_t seed = this->expectedMax + 1;
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToSet());
  size_t max = local.Max(seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxTemplateSeededHigherSet)
{
  size_t seed = this->expectedMax - 1;
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToSet());
  size_t max = local
    .Max<std::set, size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxAsSetSeededHigherSet)
{
  size_t seed = this->expectedMax - 1;
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToSet());
  size_t max = local
    .AsQueryableSet()
    .Max<size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxExtendedSeededHigherSet)
{
  size_t seed = this->expectedMax - 1;
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToSet());
  size_t max = local
    .AsExtendedQueryable<std::set>()
    .Max<size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxSeededHigherSetDefault)
{
  size_t seed = this->expectedMax - 1;
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToSet());
  size_t max = local.Max(seed);
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxTemplateWhere)
{
  size_t expected = 8;
  size_t max = this->queryable
    .Where([](size_t value) { return value < 10; })
    .Max<std::vector, size_t>([](size_t value) { return value; });
  ASSERT_EQ(expected, max);
}

TEST_F(MaxFunctionalTest, MaxAsVectorWhere)
{
  size_t expected = 8;
  size_t max = this->queryable
    .Where([](size_t value) { return value < 10; })
    .AsQueryableVector()
    .Max<size_t>([](size_t value) { return value; });
  ASSERT_EQ(expected, max);
}

TEST_F(MaxFunctionalTest, MaxExtendedWhere)
{
  size_t expected = 8;
  size_t max = this->queryable
    .Where([](size_t value) { return value < 10; })
    .AsExtendedQueryable<std::vector>()
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
