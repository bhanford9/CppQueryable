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
  IQueryable<uint> queryable;
  IQueryable<std::string> queryableStrings;

  MinFunctionalTest() :
    queryable(BuildQueryable2(std::vector<uint>({ 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, expectedMin, 867, 12 }))),
    queryableStrings(BuildQueryable2(std::vector<std::string>({ "nbc", "fox", "abc", "cbs", "the cw"})))
  {
  }

  void SetUp() override
  {
  }

  void TearDown() override {}
};

TEST_F(MinFunctionalTest, MinItemTemplateUninitialized)
{
  IQueryable<Person> emptyQueryable(BuildQueryable2(std::vector<Person>()));
  Person min = emptyQueryable
    .MinItem<std::vector, double>([](Person p) { return p.GetAge(); });
  ASSERT_DOUBLE_EQ(0.0, min.GetAge());
}

TEST_F(MinFunctionalTest, MinItemAsVectorUninitialized)
{
  IQueryable<Person> emptyQueryable(BuildQueryable2(std::vector<Person>()));
  Person min = emptyQueryable
    .AsQueryableVector()
    .MinItem<double>([](Person p) { return p.GetAge(); });
  ASSERT_DOUBLE_EQ(0.0, min.GetAge());
}

TEST_F(MinFunctionalTest, MinItemExtendedUninitialized)
{
  IQueryable<Person> emptyQueryable(BuildQueryable2(std::vector<Person>()));
  Person min = emptyQueryable
    .AsExtendedQueryable<std::vector>()
    .MinItem<double>([](Person p) { return p.GetAge(); });
  ASSERT_DOUBLE_EQ(0.0, min.GetAge());
}

TEST_F(MinFunctionalTest, MinTemplateUninitialized)
{
  IQueryable<Person> emptyQueryable(BuildQueryable2(std::vector<Person>()));
  double min = emptyQueryable
    .Min<std::vector, double>([](Person p) { return p.GetAge(); });
  ASSERT_DOUBLE_EQ(0.0, min);
}

TEST_F(MinFunctionalTest, MinAsVectorUninitialized)
{
  IQueryable<Person> emptyQueryable(BuildQueryable2(std::vector<Person>()));
  double min = emptyQueryable
    .AsQueryableVector()
    .Min<double>([](Person p) { return p.GetAge(); });
  ASSERT_DOUBLE_EQ(0.0, min);
}

TEST_F(MinFunctionalTest, MinExtendedUninitialized)
{
  IQueryable<Person> emptyQueryable(BuildQueryable2(std::vector<Person>()));
  double min = emptyQueryable
    .AsExtendedQueryable<std::vector>()
    .Min<double>([](Person p) { return p.GetAge(); });
  ASSERT_DOUBLE_EQ(0.0, min);
}

TEST_F(MinFunctionalTest, MinUninitializedDefault)
{
  IQueryable<double> emptyQueryable(BuildQueryable2(std::vector<double>()));
  double min = emptyQueryable.Min();
  ASSERT_DOUBLE_EQ(0.0, min);
}

TEST_F(MinFunctionalTest, MinTemplateSeededUninitialized)
{
  double seed = 9;
  IQueryable<Person> emptyQueryable(BuildQueryable2(std::vector<Person>()));
  double min = emptyQueryable
    .Min<std::vector, double>([](Person p) { return p.GetAge(); }, seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinAsVectorSeededUninitialized)
{
  double seed = 9;
  IQueryable<Person> emptyQueryable(BuildQueryable2(std::vector<Person>()));
  double min = emptyQueryable
    .AsQueryableVector()
    .Min<double>([](Person p) { return p.GetAge(); }, seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinExtendedSeededUninitialized)
{
  double seed = 9;
  IQueryable<Person> emptyQueryable(BuildQueryable2(std::vector<Person>()));
  double min = emptyQueryable
    .AsExtendedQueryable<std::vector>()
    .Min<double>([](Person p) { return p.GetAge(); }, seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinSeededUninitializedDefault)
{
  double seed = 9;
  IQueryable<double> emptyQueryable(BuildQueryable2(std::vector<double>()));
  double min = emptyQueryable.Min(seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinItemTemplateString)
{
  std::string min = this->queryableStrings
    .MinItem<std::vector, char>([](std::string str) { return str[0]; });
  ASSERT_STREQ(expectedMinStr.c_str(), min.c_str());
}

TEST_F(MinFunctionalTest, MinItemAsVectorString)
{
  std::string min = this->queryableStrings
    .AsQueryableVector()
    .MinItem<char>([](std::string str) { return str[0]; });
  ASSERT_STREQ(expectedMinStr.c_str(), min.c_str());
}

TEST_F(MinFunctionalTest, MinItemExtendedString)
{
  std::string min = this->queryableStrings
    .AsExtendedQueryable<std::vector>()
    .MinItem<char>([](std::string str) { return str[0]; });
  ASSERT_STREQ(expectedMinStr.c_str(), min.c_str());
}

TEST_F(MinFunctionalTest, MinTemplateString)
{
  char min = this->queryableStrings
    .Min<std::vector, char>([](std::string str) { return str[0]; });
  ASSERT_EQ(expectedMinChar, min);
}

TEST_F(MinFunctionalTest, MinAsVectorString)
{
  char min = this->queryableStrings
    .AsQueryableVector()
    .Min<char>([](std::string str) { return str[0]; });
  ASSERT_EQ(expectedMinChar, min);
}

TEST_F(MinFunctionalTest, MinExtendedString)
{
  char min = this->queryableStrings
    .AsExtendedQueryable<std::vector>()
    .Min<char>([](std::string str) { return str[0]; });
  ASSERT_EQ(expectedMinChar, min);
}

TEST_F(MinFunctionalTest, MinTemplateSmallerSeedString)
{
  char seed = 'Z';
  char min = this->queryableStrings
    .Min<std::vector, char>([](std::string str) { return str[0]; }, seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinAsVectorSmallerSeedString)
{
  char seed = 'Z';
  char min = this->queryableStrings
    .AsQueryableVector()
    .Min<char>([](std::string str) { return str[0]; }, seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinExtendedSmallerSeedString)
{
  char seed = 'Z';
  char min = this->queryableStrings
    .AsExtendedQueryable<std::vector>()
    .Min<char>([](std::string str) { return str[0]; }, seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinTemplateLargerSeedString)
{
  char seed = 'c';
  char min = this->queryableStrings
    .Min<std::vector, char>([](std::string str) { return str[0]; }, seed);
  ASSERT_EQ(expectedMinChar, min);
}

TEST_F(MinFunctionalTest, MinAsVectorLargerSeedString)
{
  char seed = 'c';
  char min = this->queryableStrings
    .AsQueryableVector()
    .Min<char>([](std::string str) { return str[0]; }, seed);
  ASSERT_EQ(expectedMinChar, min);
}

TEST_F(MinFunctionalTest, MinExtendedLargerSeedString)
{
  char seed = 'c';
  char min = this->queryableStrings
    .AsExtendedQueryable<std::vector>()
    .Min<char>([](std::string str) { return str[0]; }, seed);
  ASSERT_EQ(expectedMinChar, min);
}

TEST_F(MinFunctionalTest, MinItemTemplateDeque)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToDeque());
  uint min = local
    .MinItem<std::deque, uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinItemAsVectorDeque)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToDeque());
  uint min = local
    .AsQueryableDeque()
    .MinItem<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinItemExtendedDeque)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToDeque());
  uint min = local
    .AsExtendedQueryable<std::deque>()
    .MinItem<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinTemplateDeque)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToDeque());
  uint min = local
    .Min<std::deque, uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinAsVectorDeque)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToDeque());
  uint min = local
    .AsQueryableDeque()
    .Min<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinExtendedDeque)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToDeque());
  uint min = local
    .AsExtendedQueryable<std::deque>()
    .Min<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinDequeDefault)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToDeque());
  uint min = local.Min();
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinTemplateSeededLowerDeque)
{
  uint seed = 0;
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToDeque());
  uint min = local
    .Min<std::deque, uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinAsDequeSeededLowerDeque)
{
  uint seed = 0;
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToDeque());
  uint min = local
    .AsQueryableDeque()
    .Min<uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinExtendedSeededLowerDeque)
{
  uint seed = 0;
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToDeque());
  uint min = local
    .AsExtendedQueryable<std::deque>()
    .Min<uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinSeededLowerDequeDefault)
{
  uint seed = 0;
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToDeque());
  uint min = local.Min(seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinTemplateSeededHigherDeque)
{
  uint seed = expectedMin + 1;
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToDeque());
  uint min = local
    .Min<std::deque, uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinAsDequeSeededHigherDeque)
{
  uint seed = expectedMin + 1;
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToDeque());
  uint min = local
    .AsQueryableDeque()
    .Min<uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinExtendedSeededHigherDeque)
{
  uint seed = expectedMin + 1;
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToDeque());
  uint min = local
    .AsExtendedQueryable<std::deque>()
    .Min<uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinSeededHigherDequeDefault)
{
  uint seed = expectedMin + 1;
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToDeque());
  uint min = local.Min(seed);
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinItemTemplateList)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToList());
  uint min = local
    .MinItem<std::list, uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinItemAsList)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToList());
  uint min = local
    .AsQueryableList()
    .MinItem<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinItemExtendedList)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToList());
  uint min = local
    .AsExtendedQueryable<std::list>()
    .MinItem<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinTemplateList)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToList());
  uint min = local
    .Min<std::list, uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinAsList)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToList());
  uint min = local
    .AsQueryableList()
    .Min<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinExtendedList)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToList());
  uint min = local
    .AsExtendedQueryable<std::list>()
    .Min<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinListDefault)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToList());
  uint min = local.Min();
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinTemplateSeededLowerList)
{
  uint seed = 0;
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToList());
  uint min = local
    .Min<std::list, uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinAsListSeededLowerList)
{
  uint seed = 0;
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToList());
  uint min = local
    .AsQueryableList()
    .Min<uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinExtendedSeededLowerList)
{
  uint seed = 0;
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToList());
  uint min = local
    .AsExtendedQueryable<std::list>()
    .Min<uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinSeededLowerListDefault)
{
  uint seed = 0;
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToList());
  uint min = local.Min(seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinTemplateSeededHigherList)
{
  uint seed = expectedMin + 1;
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToList());
  uint min = local
    .Min<std::list, uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinAsListSeededHigherList)
{
  uint seed = expectedMin + 1;
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToList());
  uint min = local
    .AsQueryableList()
    .Min<uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinExtendedSeededHigherList)
{
  uint seed = expectedMin + 1;
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToList());
  uint min = local
    .AsExtendedQueryable<std::list>()
    .Min<uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinSeededHigherListDefault)
{
  uint seed = expectedMin + 1;
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToList());
  uint min = local.Min(seed);
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinItemTemplateMultiSet)
{
  ISortedQueryable<uint> local = BuildQueryable2(this->queryable.ToMultiSet());
  uint min = local
    .MinItem<std::multiset, uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinItemAsMultiSet)
{
  ISortedQueryable<uint> local = BuildQueryable2(this->queryable.ToMultiSet());
  uint min = local
    .AsQueryableMultiSet()
    .MinItem<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinItemExtendedMultiSet)
{
  ISortedQueryable<uint> local = BuildQueryable2(this->queryable.ToMultiSet());
  uint min = local
    .AsExtendedQueryable<std::multiset>()
    .MinItem<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinTemplateMultiSet)
{
  ISortedQueryable<uint> local = BuildQueryable2(this->queryable.ToMultiSet());
  uint min = local
    .Min<std::multiset, uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinAsMultiSet)
{
  ISortedQueryable<uint> local = BuildQueryable2(this->queryable.ToMultiSet());
  uint min = local
    .AsQueryableMultiSet()
    .Min<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinExtendedMultiSet)
{
  ISortedQueryable<uint> local = BuildQueryable2(this->queryable.ToMultiSet());
  uint min = local
    .AsExtendedQueryable<std::multiset>()
    .Min<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinMultiSetDefault)
{
  ISortedQueryable<uint> local = BuildQueryable2(this->queryable.ToMultiSet());
  uint min = local.Min();
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinTemplateSeededLowerMultiSet)
{
  uint seed = 0;
  ISortedQueryable<uint> local = BuildQueryable2(this->queryable.ToMultiSet());
  uint min = local
    .Min<std::multiset, uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinAsMultiSetSeededLowerMultiSet)
{
  uint seed = 0;
  ISortedQueryable<uint> local = BuildQueryable2(this->queryable.ToMultiSet());
  uint min = local
    .AsQueryableMultiSet()
    .Min<uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinExtendedSeededLowerMultiSet)
{
  uint seed = 0;
  ISortedQueryable<uint> local = BuildQueryable2(this->queryable.ToMultiSet());
  uint min = local
    .AsExtendedQueryable<std::multiset>()
    .Min<uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinSeededLowerMultiSetDefault)
{
  uint seed = 0;
  ISortedQueryable<uint> local = BuildQueryable2(this->queryable.ToMultiSet());
  uint min = local.Min(seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinTemplateSeededHigherMultiSet)
{
  uint seed = expectedMin + 1;
  ISortedQueryable<uint> local = BuildQueryable2(this->queryable.ToMultiSet());
  uint min = local
    .Min<std::multiset, uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinAsMultiSetSeededHigherMultiSet)
{
  uint seed = expectedMin + 1;
  ISortedQueryable<uint> local = BuildQueryable2(this->queryable.ToMultiSet());
  uint min = local
    .AsQueryableMultiSet()
    .Min<uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinExtendedSeededHigherMultiSet)
{
  uint seed = expectedMin + 1;
  ISortedQueryable<uint> local = BuildQueryable2(this->queryable.ToMultiSet());
  uint min = local
    .AsExtendedQueryable<std::multiset>()
    .Min<uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinSeededHigherMultiSetDefault)
{
  uint seed = expectedMin + 1;
  ISortedQueryable<uint> local = BuildQueryable2(this->queryable.ToMultiSet());
  uint min = local.Min(seed);
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinItemTemplateSet)
{
  ISortedQueryable<uint> local = BuildQueryable2(this->queryable.ToSet());
  uint min = local
    .MinItem<std::set, uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinItemAsSet)
{
  ISortedQueryable<uint> local = BuildQueryable2(this->queryable.ToSet());
  uint min = local
    .AsQueryableSet()
    .MinItem<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinItemExtendedSet)
{
  ISortedQueryable<uint> local = BuildQueryable2(this->queryable.ToSet());
  uint min = local
    .AsExtendedQueryable<std::set>()
    .MinItem<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinTemplateSet)
{
  ISortedQueryable<uint> local = BuildQueryable2(this->queryable.ToSet());
  uint min = local
    .Min<std::set, uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinAsSet)
{
  ISortedQueryable<uint> local = BuildQueryable2(this->queryable.ToSet());
  uint min = local
    .AsQueryableSet()
    .Min<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinExtendedSet)
{
  ISortedQueryable<uint> local = BuildQueryable2(this->queryable.ToSet());
  uint min = local
    .AsExtendedQueryable<std::set>()
    .Min<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinSetDefault)
{
  ISortedQueryable<uint> local = BuildQueryable2(this->queryable.ToSet());
  uint min = local.Min();
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinTemplateSeededLowerSet)
{
  uint seed = 0;
  ISortedQueryable<uint> local = BuildQueryable2(this->queryable.ToSet());
  uint min = local
    .Min<std::set, uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinAsSetSeededLowerSet)
{
  uint seed = 0;
  ISortedQueryable<uint> local = BuildQueryable2(this->queryable.ToSet());
  uint min = local
    .AsQueryableSet()
    .Min<uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinExtendedSeededLowerSet)
{
  uint seed = 0;
  ISortedQueryable<uint> local = BuildQueryable2(this->queryable.ToSet());
  uint min = local
    .AsExtendedQueryable<std::set>()
    .Min<uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinSeededLowerSetDefault)
{
  uint seed = 0;
  ISortedQueryable<uint> local = BuildQueryable2(this->queryable.ToSet());
  uint min = local.Min(seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinTemplateSeededHigherSet)
{
  uint seed = expectedMin + 1;
  ISortedQueryable<uint> local = BuildQueryable2(this->queryable.ToSet());
  uint min = local
    .Min<std::set, uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinAsSetSeededHigherSet)
{
  uint seed = expectedMin + 1;
  ISortedQueryable<uint> local = BuildQueryable2(this->queryable.ToSet());
  uint min = local
    .AsQueryableSet()
    .Min<uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinExtendedSeededHigherSet)
{
  uint seed = expectedMin + 1;
  ISortedQueryable<uint> local = BuildQueryable2(this->queryable.ToSet());
  uint min = local
    .AsExtendedQueryable<std::set>()
    .Min<uint>([](uint value) { return value; }, seed);
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinSeededHigherSetDefault)
{
  uint seed = expectedMin + 1;
  ISortedQueryable<uint> local = BuildQueryable2(this->queryable.ToSet());
  uint min = local.Min(seed);
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinTemplateWhere)
{
  uint expected = 12;
  uint min = this->queryable
    .Where([](uint value) { return value > 10; })
    .Min<std::vector, uint>([](uint value) { return value; });
  ASSERT_EQ(expected, min);
}

TEST_F(MinFunctionalTest, MinAsVectorWhere)
{
  uint expected = 12;
  uint min = this->queryable
    .Where([](uint value) { return value > 10; })
    .AsQueryableVector()
    .Min<uint>([](uint value) { return value; });
  ASSERT_EQ(expected, min);
}

TEST_F(MinFunctionalTest, MinExtendedWhere)
{
  uint expected = 12;
  uint min = this->queryable
    .Where([](uint value) { return value > 10; })
    .AsExtendedQueryable<std::vector>()
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
