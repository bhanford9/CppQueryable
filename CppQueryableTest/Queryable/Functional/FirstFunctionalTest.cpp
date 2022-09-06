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

class FirstFunctionalTest : public ::testing::Test
{
protected:
  size_t expectedUnorderedFirst = 9;
  size_t expectedOrderedFirst = 0;
  size_t expectedUnorderedOver40 = 76;
  size_t expectedOrderedOver40 = 45;
  size_t threshold = 40;
  IQueryable<size_t> queryable;

  FirstFunctionalTest() :
    queryable(BuildQueryable2(std::vector<size_t>({ expectedUnorderedFirst, 4, 7, 4, 3, 76, 8, 45, 34, 76, 0, 867 })))
  {
  }

  void SetUp() override
  {
  }

  void TearDown() override {}
};

TEST_F(FirstFunctionalTest, FirstVectorUninitialized)
{
  IQueryable<Person> emptyQueryable(BuildQueryable2(std::vector<Person>()));

  try
  {
    Person p = emptyQueryable.First();
  }
  catch (std::runtime_error& ex)
  {
    ASSERT_STREQ(ex.what(), "Cannot get first item of empty collection.");
  }
}

TEST_F(FirstFunctionalTest, FirstVector)
{
  size_t value = this->queryable.First();
  ASSERT_EQ(this->expectedUnorderedFirst, value);
}

TEST_F(FirstFunctionalTest, FirstSet)
{
  size_t value = ISortedQueryable<size_t>(BuildQueryable2(this->queryable.ToSet())).First();
  ASSERT_EQ(this->expectedOrderedFirst, value);
}

TEST_F(FirstFunctionalTest, FirstMultiSet)
{
  size_t value = ISortedQueryable<size_t>(BuildQueryable2(this->queryable.ToMultiSet())).First();
  ASSERT_EQ(this->expectedOrderedFirst, value);
}

TEST_F(FirstFunctionalTest, FirstDeque)
{
  size_t value = IQueryable<size_t>(BuildQueryable2(this->queryable.ToDeque())).First();
  ASSERT_EQ(this->expectedUnorderedFirst, value);
}

TEST_F(FirstFunctionalTest, FirstList)
{
  size_t value = IQueryable<size_t>(BuildQueryable2(this->queryable.ToList())).First();
  ASSERT_EQ(this->expectedUnorderedFirst, value);
}

TEST_F(FirstFunctionalTest, FirstWhereVectorUninitialized)
{
  IQueryable<Person> emptyQueryable(BuildQueryable2(std::vector<Person>()));

  try
  {
    Person p = emptyQueryable.First([](Person p) { return true; });
  }
  catch (std::runtime_error& ex)
  {
    ASSERT_STREQ(ex.what(), "No item fitting the condition was found.");
  }
}

TEST_F(FirstFunctionalTest, FirstWhereConditionFails)
{
  try
  {
    this->queryable.First([](size_t value) { return false; });
  }
  catch (std::runtime_error& ex)
  {
    ASSERT_STREQ(ex.what(), "No item fitting the condition was found.");
  }
}

TEST_F(FirstFunctionalTest, FirstWhereVector)
{
  size_t value = this->queryable.First([&](size_t value) { return value > this->threshold; });
  ASSERT_EQ(this->expectedUnorderedOver40, value);
}

TEST_F(FirstFunctionalTest, FirstWhereSet)
{
  size_t value = ISortedQueryable<size_t>(BuildQueryable2(this->queryable.ToSet()))
    .First([&](size_t value) { return value > this->threshold; });
  ASSERT_EQ(this->expectedOrderedOver40, value);
}

TEST_F(FirstFunctionalTest, FirstWhereMultiSet)
{
  size_t value = ISortedQueryable<size_t>(BuildQueryable2(this->queryable.ToMultiSet()))
    .First([&](size_t value) { return value > this->threshold; });
  ASSERT_EQ(this->expectedOrderedOver40, value);
}

TEST_F(FirstFunctionalTest, FirstWhereDeque)
{
  size_t value = IQueryable<size_t>(BuildQueryable2(this->queryable.ToDeque()))
    .First([&](size_t value) { return value > this->threshold; });
  ASSERT_EQ(this->expectedUnorderedOver40, value);
}

TEST_F(FirstFunctionalTest, FirstWhereList)
{
  size_t value = IQueryable<size_t>(BuildQueryable2(this->queryable.ToList()))
    .First([&](size_t value) { return value > this->threshold; });
  ASSERT_EQ(this->expectedUnorderedOver40, value);
}

TEST_F(FirstFunctionalTest, FirstWhereEven)
{
  size_t expected = 4;
  size_t value = this->queryable
    .Where([](size_t value) { return value % 2 == 0; })
    .First();
  ASSERT_EQ(expected, value);
}

TEST_F(FirstFunctionalTest, FirstWhereOdd)
{
  size_t expected = expectedUnorderedFirst;
  size_t value = this->queryable
    .Where([](size_t value) { return value % 2 == 1; })
    .First();
  ASSERT_EQ(expected, value);
}

TEST_F(FirstFunctionalTest, FirstWhereWhereEven)
{
  size_t expected = 76;
  size_t value = this->queryable
    .Where([](size_t value) { return value % 2 == 0; })
    .First([](size_t value) { return value > 10; });
  ASSERT_EQ(expected, value);
}

TEST_F(FirstFunctionalTest, FirstWhereWhereOdd)
{
  size_t expected = 45;
  size_t value = this->queryable
    .Where([](size_t value) { return value % 2 == 1; })
    .First([](size_t value) { return value > 10; });
  ASSERT_EQ(expected, value);
}
