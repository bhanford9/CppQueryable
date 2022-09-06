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
  IQueryable<size_t> queryable;
  IQueryable<std::string> queryableStrings;

  MinFunctionalTest() :
    queryable(BuildQueryable2(std::vector<size_t>({ 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, expectedMin, 867, 12 }))),
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
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToDeque());
  size_t min = local
    .MinItem<std::deque, size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinItemAsVectorDeque)
{
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToDeque());
  size_t min = local
    .AsQueryableDeque()
    .MinItem<size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinItemExtendedDeque)
{
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToDeque());
  size_t min = local
    .AsExtendedQueryable<std::deque>()
    .MinItem<size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinTemplateDeque)
{
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToDeque());
  size_t min = local
    .Min<std::deque, size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinAsVectorDeque)
{
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToDeque());
  size_t min = local
    .AsQueryableDeque()
    .Min<size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinExtendedDeque)
{
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToDeque());
  size_t min = local
    .AsExtendedQueryable<std::deque>()
    .Min<size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinDequeDefault)
{
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToDeque());
  size_t min = local.Min();
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinTemplateSeededLowerDeque)
{
  size_t seed = 0;
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToDeque());
  size_t min = local
    .Min<std::deque, size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinAsDequeSeededLowerDeque)
{
  size_t seed = 0;
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToDeque());
  size_t min = local
    .AsQueryableDeque()
    .Min<size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinExtendedSeededLowerDeque)
{
  size_t seed = 0;
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToDeque());
  size_t min = local
    .AsExtendedQueryable<std::deque>()
    .Min<size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinSeededLowerDequeDefault)
{
  size_t seed = 0;
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToDeque());
  size_t min = local.Min(seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinTemplateSeededHigherDeque)
{
  size_t seed = expectedMin + 1;
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToDeque());
  size_t min = local
    .Min<std::deque, size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinAsDequeSeededHigherDeque)
{
  size_t seed = expectedMin + 1;
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToDeque());
  size_t min = local
    .AsQueryableDeque()
    .Min<size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinExtendedSeededHigherDeque)
{
  size_t seed = expectedMin + 1;
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToDeque());
  size_t min = local
    .AsExtendedQueryable<std::deque>()
    .Min<size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinSeededHigherDequeDefault)
{
  size_t seed = expectedMin + 1;
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToDeque());
  size_t min = local.Min(seed);
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinItemTemplateList)
{
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToList());
  size_t min = local
    .MinItem<std::list, size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinItemAsList)
{
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToList());
  size_t min = local
    .AsQueryableList()
    .MinItem<size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinItemExtendedList)
{
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToList());
  size_t min = local
    .AsExtendedQueryable<std::list>()
    .MinItem<size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinTemplateList)
{
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToList());
  size_t min = local
    .Min<std::list, size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinAsList)
{
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToList());
  size_t min = local
    .AsQueryableList()
    .Min<size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinExtendedList)
{
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToList());
  size_t min = local
    .AsExtendedQueryable<std::list>()
    .Min<size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinListDefault)
{
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToList());
  size_t min = local.Min();
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinTemplateSeededLowerList)
{
  size_t seed = 0;
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToList());
  size_t min = local
    .Min<std::list, size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinAsListSeededLowerList)
{
  size_t seed = 0;
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToList());
  size_t min = local
    .AsQueryableList()
    .Min<size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinExtendedSeededLowerList)
{
  size_t seed = 0;
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToList());
  size_t min = local
    .AsExtendedQueryable<std::list>()
    .Min<size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinSeededLowerListDefault)
{
  size_t seed = 0;
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToList());
  size_t min = local.Min(seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinTemplateSeededHigherList)
{
  size_t seed = expectedMin + 1;
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToList());
  size_t min = local
    .Min<std::list, size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinAsListSeededHigherList)
{
  size_t seed = expectedMin + 1;
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToList());
  size_t min = local
    .AsQueryableList()
    .Min<size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinExtendedSeededHigherList)
{
  size_t seed = expectedMin + 1;
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToList());
  size_t min = local
    .AsExtendedQueryable<std::list>()
    .Min<size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinSeededHigherListDefault)
{
  size_t seed = expectedMin + 1;
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToList());
  size_t min = local.Min(seed);
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinItemTemplateMultiSet)
{
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToMultiSet());
  size_t min = local
    .MinItem<std::multiset, size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinItemAsMultiSet)
{
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToMultiSet());
  size_t min = local
    .AsQueryableMultiSet()
    .MinItem<size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinItemExtendedMultiSet)
{
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToMultiSet());
  size_t min = local
    .AsExtendedQueryable<std::multiset>()
    .MinItem<size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinTemplateMultiSet)
{
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToMultiSet());
  size_t min = local
    .Min<std::multiset, size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinAsMultiSet)
{
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToMultiSet());
  size_t min = local
    .AsQueryableMultiSet()
    .Min<size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinExtendedMultiSet)
{
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToMultiSet());
  size_t min = local
    .AsExtendedQueryable<std::multiset>()
    .Min<size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinMultiSetDefault)
{
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToMultiSet());
  size_t min = local.Min();
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinTemplateSeededLowerMultiSet)
{
  size_t seed = 0;
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToMultiSet());
  size_t min = local
    .Min<std::multiset, size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinAsMultiSetSeededLowerMultiSet)
{
  size_t seed = 0;
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToMultiSet());
  size_t min = local
    .AsQueryableMultiSet()
    .Min<size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinExtendedSeededLowerMultiSet)
{
  size_t seed = 0;
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToMultiSet());
  size_t min = local
    .AsExtendedQueryable<std::multiset>()
    .Min<size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinSeededLowerMultiSetDefault)
{
  size_t seed = 0;
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToMultiSet());
  size_t min = local.Min(seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinTemplateSeededHigherMultiSet)
{
  size_t seed = expectedMin + 1;
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToMultiSet());
  size_t min = local
    .Min<std::multiset, size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinAsMultiSetSeededHigherMultiSet)
{
  size_t seed = expectedMin + 1;
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToMultiSet());
  size_t min = local
    .AsQueryableMultiSet()
    .Min<size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinExtendedSeededHigherMultiSet)
{
  size_t seed = expectedMin + 1;
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToMultiSet());
  size_t min = local
    .AsExtendedQueryable<std::multiset>()
    .Min<size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinSeededHigherMultiSetDefault)
{
  size_t seed = expectedMin + 1;
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToMultiSet());
  size_t min = local.Min(seed);
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinItemTemplateSet)
{
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToSet());
  size_t min = local
    .MinItem<std::set, size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinItemAsSet)
{
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToSet());
  size_t min = local
    .AsQueryableSet()
    .MinItem<size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinItemExtendedSet)
{
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToSet());
  size_t min = local
    .AsExtendedQueryable<std::set>()
    .MinItem<size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinTemplateSet)
{
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToSet());
  size_t min = local
    .Min<std::set, size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinAsSet)
{
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToSet());
  size_t min = local
    .AsQueryableSet()
    .Min<size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinExtendedSet)
{
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToSet());
  size_t min = local
    .AsExtendedQueryable<std::set>()
    .Min<size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinSetDefault)
{
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToSet());
  size_t min = local.Min();
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinTemplateSeededLowerSet)
{
  size_t seed = 0;
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToSet());
  size_t min = local
    .Min<std::set, size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinAsSetSeededLowerSet)
{
  size_t seed = 0;
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToSet());
  size_t min = local
    .AsQueryableSet()
    .Min<size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinExtendedSeededLowerSet)
{
  size_t seed = 0;
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToSet());
  size_t min = local
    .AsExtendedQueryable<std::set>()
    .Min<size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinSeededLowerSetDefault)
{
  size_t seed = 0;
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToSet());
  size_t min = local.Min(seed);
  ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinTemplateSeededHigherSet)
{
  size_t seed = expectedMin + 1;
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToSet());
  size_t min = local
    .Min<std::set, size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinAsSetSeededHigherSet)
{
  size_t seed = expectedMin + 1;
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToSet());
  size_t min = local
    .AsQueryableSet()
    .Min<size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinExtendedSeededHigherSet)
{
  size_t seed = expectedMin + 1;
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToSet());
  size_t min = local
    .AsExtendedQueryable<std::set>()
    .Min<size_t>([](size_t value) { return value; }, seed);
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinSeededHigherSetDefault)
{
  size_t seed = expectedMin + 1;
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToSet());
  size_t min = local.Min(seed);
  ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinTemplateWhere)
{
  size_t expected = 12;
  size_t min = this->queryable
    .Where([](size_t value) { return value > 10; })
    .Min<std::vector, size_t>([](size_t value) { return value; });
  ASSERT_EQ(expected, min);
}

TEST_F(MinFunctionalTest, MinAsVectorWhere)
{
  size_t expected = 12;
  size_t min = this->queryable
    .Where([](size_t value) { return value > 10; })
    .AsQueryableVector()
    .Min<size_t>([](size_t value) { return value; });
  ASSERT_EQ(expected, min);
}

TEST_F(MinFunctionalTest, MinExtendedWhere)
{
  size_t expected = 12;
  size_t min = this->queryable
    .Where([](size_t value) { return value > 10; })
    .AsExtendedQueryable<std::vector>()
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
