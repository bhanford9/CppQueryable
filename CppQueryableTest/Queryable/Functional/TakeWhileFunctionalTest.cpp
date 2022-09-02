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
  uint threshold = 10;
  int expectedCountUnordered = 5;
  int expectedCountOrdered = 7;
  int expectedCountOrderedSet = 5;
  IQueryable<uint> queryable;

  TakeWhileFunctionalTest() :
    queryable(BuildQueryable2(std::vector<uint>({ 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 })))
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
  IBaseQueryable<uint> result = this->queryable.TakeWhile([](uint value) { return true; });

  ASSERT_EQ(this->queryable.Count(), result.Count());

  for (size_t i = 0; i < this->queryable.Count(); i++)
  {
    ASSERT_EQ(this->queryable.At(i), result.At(i));
  }
}

TEST_F(TakeWhileFunctionalTest, TakeWhileDeque)
{
  IQueryable<uint> queryableDeque(BuildQueryable2(this->queryable.ToDeque()));
  IBaseQueryable<uint> & result = queryableDeque
    .TakeWhile([&](uint value) { return value < this->threshold; });

  ASSERT_EQ(this->expectedCountUnordered, result.Count());

  for (size_t i = 0; i < result.Count(); i++)
  {
    ASSERT_EQ(0, result.At(i) / 10);
  }
}

TEST_F(TakeWhileFunctionalTest, TakeWhileList)
{
  IQueryable<uint> queryableList = BuildQueryable2(this->queryable.ToList());
  IBaseQueryable<uint> result = queryableList
    .TakeWhile([&](uint value) { return value < this->threshold; });

  ASSERT_EQ(this->expectedCountUnordered, result.Count());

  for (size_t i = 0; i < result.Count(); i++)
  {
    ASSERT_EQ(0, result.At(i) / 10);
  }
}

TEST_F(TakeWhileFunctionalTest, TakeWhileMultiSet)
{
  ISortedQueryable<uint> queryableSet = BuildQueryable2(this->queryable.ToMultiSet());
  IBaseQueryable<uint> result = queryableSet
    .TakeWhile([&](uint value) { return value < this->threshold; });

  ASSERT_EQ(this->expectedCountOrdered, result.Count());

  for (size_t i = 0; i < result.Count(); i++)
  {
    ASSERT_EQ(0, result.At(i) / 10);
  }
}

TEST_F(TakeWhileFunctionalTest, TakeWhileSet)
{
  ISortedQueryable<uint> queryableSet = BuildQueryable2(this->queryable.ToSet());
  IBaseQueryable<uint> result = queryableSet
    .TakeWhile([&](uint value) { return value < this->threshold; });

  ASSERT_EQ(this->expectedCountOrderedSet, result.Count());

  for (size_t i = 0; i < result.Count(); i++)
  {
    ASSERT_EQ(0, result.At(i) / 10);
  }
}

TEST_F(TakeWhileFunctionalTest, TakeWhileVector)
{
  IBaseQueryable<uint> result = this->queryable
    .TakeWhile([&](uint value) { return value < this->threshold; });

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
  IQueryable<uint> queryableVector = BuildQueryable2(std::vector<uint>({ 7, 0, 7, 2, 3, 4, 6, 45, 8, 1, 3, 10 }));
  IBaseQueryable<uint> result = queryableVector
    .Where([](uint value) { return value % 2 == 0; })
    .TakeWhile([](uint value) { return value < 8; });


  ASSERT_EQ(expectedCount, result.Count());
  result.ForEach([&](uint value) { ASSERT_EQ(takeCount++ * 2, value); });
}
