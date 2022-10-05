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

class TakeWhileFunctionalTest : public ::testing::Test
{
protected:
  size_t threshold = 10;
  int expectedCountUnordered = 5;
  int expectedCountOrdered = 7;
  int expectedCountOrderedSet = 5;
  QueryableVector<size_t> queryable;

  TakeWhileFunctionalTest() :
    queryable(BuildQueryable2(std::vector<size_t>({ 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 })))
  {
  }

  void SetUp() override
  {
  }

  void TearDown() override {}
};

// TEST_F(TakeWhileFunctionalTest, TakeWhileVectorUninitialized)
// {
//   IQueryable<Person> emptyQueryable;
//   IQueryable<Person> result = emptyQueryable.TakeWhile([](Person p) { return true; });

//   ASSERT_EQ(0, result.Count());
// }

TEST_F(TakeWhileFunctionalTest, TakeWhileVectorAlwaysTrue)
{
  QueryableVector<size_t> result = this->queryable.TakeWhile([](size_t value) { return true; });

  ASSERT_EQ(this->queryable.Count(), result.Count());

  for (size_t i = 0; i < this->queryable.Count(); i++)
  {
    ASSERT_EQ(this->queryable.At(i), result.At(i));
  }
}

TEST_F(TakeWhileFunctionalTest, TakeWhileDeque)
{
  QueryableDeque<size_t> queryableDeque(BuildQueryable2(this->queryable.ToDeque()));
  QueryableDeque<size_t> & result = queryableDeque
    .TakeWhile([&](size_t value) { return value < this->threshold; });

  ASSERT_EQ(this->expectedCountUnordered, result.Count());

  for (size_t i = 0; i < result.Count(); i++)
  {
    ASSERT_EQ(0, result.At(i) / 10);
  }
}

TEST_F(TakeWhileFunctionalTest, TakeWhileList)
{
  // somethings not right with Take While. It seems to iterate over the collection several times
  QueryableList<size_t> queryableList = BuildQueryable2(this->queryable.ToList());
  QueryableList<size_t> result = queryableList
    .TakeWhile([&](size_t value) { return value < this->threshold; });

  ASSERT_EQ(this->expectedCountUnordered, result.Count());

  for (size_t i = 0; i < result.Count(); i++)
  {
    ASSERT_EQ(0, result.At(i) / 10);
  }
}

TEST_F(TakeWhileFunctionalTest, TakeWhileMap)
{
  QueryableMap<size_t, std::string> queryableMap = BuildQueryable2<size_t, std::string>(
    this->queryable.ToMap<size_t, std::string>(
      [](size_t value) { return value; },
      [](size_t value) { return std::to_string(value / 2.0); }));
  QueryableMap<size_t, std::string> result = queryableMap
    .TakeWhile([&](std::pair<const size_t, std::string> kvp) { return kvp.first < this->threshold; });

  ASSERT_EQ(this->expectedCountOrderedSet, result.Count());

  for (size_t i = 0; i < result.Count(); i++)
  {
    ASSERT_EQ(0, result.At(i).first / 10);
  }
}

TEST_F(TakeWhileFunctionalTest, TakeWhileMultiSet)
{
  QueryableMultiSet<size_t> queryableSet = BuildQueryable2(this->queryable.ToMultiSet());
  QueryableMultiSet<size_t> result = queryableSet
    .TakeWhile([&](size_t value) { return value < this->threshold; });

  ASSERT_EQ(this->expectedCountOrdered, result.Count());

  for (size_t i = 0; i < result.Count(); i++)
  {
    ASSERT_EQ(0, result.At(i) / 10);
  }
}

TEST_F(TakeWhileFunctionalTest, TakeWhileSet)
{
  QueryableSet<size_t> queryableSet = BuildQueryable2(this->queryable.ToSet());
  QueryableSet<size_t> result = queryableSet
    .TakeWhile([&](size_t value) { return value < this->threshold; });

  ASSERT_EQ(this->expectedCountOrderedSet, result.Count());

  for (size_t i = 0; i < result.Count(); i++)
  {
    ASSERT_EQ(0, result.At(i) / 10);
  }
}

TEST_F(TakeWhileFunctionalTest, TakeWhileVector)
{
  QueryableVector<size_t> result = this->queryable
    .TakeWhile([&](size_t value) { return value < this->threshold; });

  ASSERT_EQ(this->expectedCountUnordered, result.Count());

  for (size_t i = 0; i < result.Count(); i++)
  {
    ASSERT_EQ(0, result.At(i) / 10);
  }
}

TEST_F(TakeWhileFunctionalTest, TakeWhileWhere)
{
  int takeCount = 0;
  int expectedCount = 4;
  QueryableVector<size_t> queryableVector = BuildQueryable2(std::vector<size_t>({ 7, 0, 7, 2, 3, 4, 6, 45, 8, 1, 3, 10 }));
  QueryableVector<size_t> result = queryableVector
    .Where([](size_t value) { return value % 2 == 0; })
    .TakeWhile([](size_t value) { return value < 8; });


  ASSERT_EQ(expectedCount, result.Count());
  result.ForEach([&](size_t value) { ASSERT_EQ(takeCount++ * 2, value); });
}
