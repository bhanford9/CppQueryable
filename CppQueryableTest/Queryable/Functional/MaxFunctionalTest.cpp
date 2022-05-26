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
  IQueryable<uint> queryable;
  IQueryable<std::string> queryableStrings;

  MaxFunctionalTest() :
    queryable(BuildQueryable2(std::vector<uint>({ 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, expectedMax, 1, 12 }))),
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
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToDeque());
  uint max = local
    .MaxItem<std::deque, uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxItemAsDeque)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToDeque());
  uint max = local
    .AsQueryableDeque()
    .MaxItem<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxItemExtendedDeque)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToDeque());
  uint max = local
    .AsExtendedQueryable<std::deque>()
    .MaxItem<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxTemplateDeque)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToDeque());
  uint max = local
    .Max<std::deque, uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxAsDeque)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToDeque());
  uint max = local
    .AsQueryableDeque()
    .Max<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxExtendedDeque)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToDeque());
  uint max = local
    .AsExtendedQueryable<std::deque>()
    .Max<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxDequeDefault)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToDeque());
  uint max = local.Max();
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxTemplateSeededLowerDeque)
{
  uint seed = this->expectedMax + 1;
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToDeque());
  uint max = local
    .Max<std::deque, uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxAsDequeSeededLowerDeque)
{
  uint seed = this->expectedMax + 1;
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToDeque());
  uint max = local
    .AsQueryableDeque()
    .Max<uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxExtendedSeededLowerDeque)
{
  uint seed = this->expectedMax + 1;
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToDeque());
  uint max = local
    .AsExtendedQueryable<std::deque>()
    .Max<uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxSeededLowerDequeDefault)
{
  uint seed = this->expectedMax + 1;
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToDeque());
  uint max = local.Max(seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxTemplateSeededHigherDeque)
{
  uint seed = this->expectedMax - 1;
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToDeque());
  uint max = local
    .Max<std::deque, uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxAsDequeSeededHigherDeque)
{
  uint seed = this->expectedMax - 1;
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToDeque());
  uint max = local
    .AsQueryableDeque()
    .Max<uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxExtendedSeededHigherDeque)
{
  uint seed = this->expectedMax - 1;
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToDeque());
  uint max = local
    .AsExtendedQueryable<std::deque>()
    .Max<uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxSeededHigherDequeDefault)
{
  uint seed = this->expectedMax - 1;
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToDeque());
  uint max = local.Max(seed);
  ASSERT_EQ(this->expectedMax, max);
}


TEST_F(MaxFunctionalTest, MaxItemTemplateList)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToList());
  uint max = local
    .MaxItem<std::list, uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxItemAsList)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToList());
  uint max = local
    .AsQueryableList()
    .MaxItem<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxItemExtendedList)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToList());
  uint max = local
    .AsExtendedQueryable<std::list>()
    .MaxItem<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxTemplateList)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToList());
  uint max = local
    .Max<std::list, uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxAsList)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToList());
  uint max = local
    .AsQueryableList()
    .Max<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxExtendedList)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToList());
  uint max = local
    .AsExtendedQueryable<std::list>()
    .Max<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxListDefault)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToList());
  uint max = local.Max();
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxTemplateSeededLowerList)
{
  uint seed = this->expectedMax + 1;
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToList());
  uint max = local
    .Max<std::list, uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxAsListSeededLowerList)
{
  uint seed = this->expectedMax + 1;
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToList());
  uint max = local
    .AsQueryableList()
    .Max<uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxExtendedSeededLowerList)
{
  uint seed = this->expectedMax + 1;
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToList());
  uint max = local
    .AsExtendedQueryable<std::list>()
    .Max<uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxSeededLowerListDefault)
{
  uint seed = this->expectedMax + 1;
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToList());
  uint max = local.Max(seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxTemplateSeededHigherList)
{
  uint seed = this->expectedMax - 1;
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToList());
  uint max = local
    .Max<std::list, uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxAsListSeededHigherList)
{
  uint seed = this->expectedMax - 1;
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToList());
  uint max = local
    .AsQueryableList()
    .Max<uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxExtendedSeededHigherList)
{
  uint seed = this->expectedMax - 1;
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToList());
  uint max = local
    .AsExtendedQueryable<std::list>()
    .Max<uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxSeededHigherListDefault)
{
  uint seed = this->expectedMax - 1;
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToList());
  uint max = local.Max(seed);
  ASSERT_EQ(this->expectedMax, max);
}


TEST_F(MaxFunctionalTest, MaxItemTemplateMultiSet)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToMultiSet());
  uint max = local
    .MaxItem<std::multiset, uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxItemAsMultiSet)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToMultiSet());
  uint max = local
    .AsQueryableMultiSet()
    .MaxItem<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxItemExtendedMultiSet)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToMultiSet());
  uint max = local
    .AsExtendedQueryable<std::multiset>()
    .MaxItem<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxTemplateMultiSet)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToMultiSet());
  uint max = local
    .Max<std::multiset, uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxAsMultiSet)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToMultiSet());
  uint max = local
    .AsQueryableMultiSet()
    .Max<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxExtendedMultiSet)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToMultiSet());
  uint max = local
    .AsExtendedQueryable<std::multiset>()
    .Max<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxMultiSetDefault)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToMultiSet());
  uint max = local.Max();
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxTemplateSeededLowerMultiSet)
{
  uint seed = this->expectedMax + 1;
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToMultiSet());
  uint max = local
    .Max<std::multiset, uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxAsMultiSetSeededLowerMultiSet)
{
  uint seed = this->expectedMax + 1;
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToMultiSet());
  uint max = local
    .AsQueryableMultiSet()
    .Max<uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxExtendedSeededLowerMultiSet)
{
  uint seed = this->expectedMax + 1;
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToMultiSet());
  uint max = local
    .AsExtendedQueryable<std::multiset>()
    .Max<uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxSeededLowerMultiSetDefault)
{
  uint seed = this->expectedMax + 1;
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToMultiSet());
  uint max = local.Max(seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxTemplateSeededHigherMultiSet)
{
  uint seed = this->expectedMax - 1;
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToMultiSet());
  uint max = local
    .Max<std::multiset, uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxAsMultiSetSeededHigherMultiSet)
{
  uint seed = this->expectedMax - 1;
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToMultiSet());
  uint max = local
    .AsQueryableMultiSet()
    .Max<uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxExtendedSeededHigherMultiSet)
{
  uint seed = this->expectedMax - 1;
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToMultiSet());
  uint max = local
    .AsExtendedQueryable<std::multiset>()
    .Max<uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxSeededHigherMultiSetDefault)
{
  uint seed = this->expectedMax - 1;
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToMultiSet());
  uint max = local.Max(seed);
  ASSERT_EQ(this->expectedMax, max);
}


TEST_F(MaxFunctionalTest, MaxItemTemplateSet)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToSet());
  uint max = local
    .MaxItem<std::set, uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxItemAsSet)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToSet());
  uint max = local
    .AsQueryableSet()
    .MaxItem<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxItemExtendedSet)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToSet());
  uint max = local
    .AsExtendedQueryable<std::set>()
    .MaxItem<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxTemplateSet)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToSet());
  uint max = local
    .Max<std::set, uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxAsSet)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToSet());
  uint max = local
    .AsQueryableSet()
    .Max<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxExtendedSet)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToSet());
  uint max = local
    .AsExtendedQueryable<std::set>()
    .Max<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxSetDefault)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToSet());
  uint max = local.Max();
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxTemplateSeededLowerSet)
{
  uint seed = this->expectedMax + 1;
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToSet());
  uint max = local
    .Max<std::set, uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxAsSetSeededLowerSet)
{
  uint seed = this->expectedMax + 1;
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToSet());
  uint max = local
    .AsQueryableSet()
    .Max<uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxExtendedSeededLowerSet)
{
  uint seed = this->expectedMax + 1;
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToSet());
  uint max = local
    .AsExtendedQueryable<std::set>()
    .Max<uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxSeededLowerSetDefault)
{
  uint seed = this->expectedMax + 1;
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToSet());
  uint max = local.Max(seed);
  ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxTemplateSeededHigherSet)
{
  uint seed = this->expectedMax - 1;
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToSet());
  uint max = local
    .Max<std::set, uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxAsSetSeededHigherSet)
{
  uint seed = this->expectedMax - 1;
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToSet());
  uint max = local
    .AsQueryableSet()
    .Max<uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxExtendedSeededHigherSet)
{
  uint seed = this->expectedMax - 1;
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToSet());
  uint max = local
    .AsExtendedQueryable<std::set>()
    .Max<uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxSeededHigherSetDefault)
{
  uint seed = this->expectedMax - 1;
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToSet());
  uint max = local.Max(seed);
  ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxTemplateWhere)
{
  uint expected = 8;
  uint max = this->queryable
    .Where([](uint value) { return value < 10; })
    .Max<std::vector, uint>([](uint value) { return value; });
  ASSERT_EQ(expected, max);
}

TEST_F(MaxFunctionalTest, MaxAsVectorWhere)
{
  uint expected = 8;
  uint max = this->queryable
    .Where([](uint value) { return value < 10; })
    .AsQueryableVector()
    .Max<uint>([](uint value) { return value; });
  ASSERT_EQ(expected, max);
}

TEST_F(MaxFunctionalTest, MaxExtendedWhere)
{
  uint expected = 8;
  uint max = this->queryable
    .Where([](uint value) { return value < 10; })
    .AsExtendedQueryable<std::vector>()
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
