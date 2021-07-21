#include <gtest/gtest.h>

#include <array>
#include <deque>
#include <exception>
#include <iostream>
#include <list>
#include <set>
#include <string>
#include <vector>

#include "../../../DataStructures/Gender.h"
#include "../../../DataStructures/Person.h"
#include "../../../DataStructures/PersonLibrary.h"

#include "../../../Queryable/QueryBuilder.h"
#include "../../../Queryable/QueryableVector.h"

using namespace QueryBuilder;

class TakeWhileFunctionalTest : public ::testing::Test
{
protected:
  uint threshold = 10;
  int expectedCountUnordered = 6;
  int expectedCountOrdered = 8;
  int expectedCountOrderedSet = 5;
  QueryableVector<uint> queryable;

  void SetUp() override
  {
    this->queryable = QueryableVector<uint>({ 4, 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 });
  }

  void TearDown() override {}
};

TEST_F(TakeWhileFunctionalTest, TakeWhileVectorUninitialized)
{
  QueryableVector<Person> emptyQueryable;
  Queryable<Person> * result = emptyQueryable.TakeWhile([](Person p) { return true; });

  ASSERT_EQ(0, result->Count());
}

TEST_F(TakeWhileFunctionalTest, TakeWhileVectorAlwaysTrue)
{
  Queryable<uint> * result = this->queryable.TakeWhile([](uint value) { return true; });

  ASSERT_EQ(this->queryable.Count(), result->Count());

  for (int i = 0; i < this->queryable.Count(); i++)
  {
    ASSERT_EQ(this->queryable.At(i), result->At(i));
  }
}

TEST_F(TakeWhileFunctionalTest, TakeWhileVector)
{
  Queryable<uint> * result = this->queryable
    .TakeWhile([&](uint value) { return value < this->threshold; });

  ASSERT_EQ(this->expectedCountUnordered, result->Count());

  for (int i = 0; i < result->Count(); i++)
  {
    ASSERT_EQ(0, result->At(i) / 10);
  }
}

TEST_F(TakeWhileFunctionalTest, TakeWhileSet)
{
  QueryableSet<uint> queryableSet = BuildQueryable(this->queryable.ToSet());
  Queryable<uint>* result = queryableSet
    .TakeWhile([&](uint value) { return value < this->threshold; });

  ASSERT_EQ(this->expectedCountOrderedSet, result->Count());

  for (int i = 0; i < result->Count(); i++)
  {
    ASSERT_EQ(0, result->At(i) / 10);
  }
}

TEST_F(TakeWhileFunctionalTest, TakeWhileMultiSet)
{
  QueryableMultiSet<uint> queryableSet = BuildQueryable(this->queryable.ToMultiSet());
  Queryable<uint>* result = queryableSet
    .TakeWhile([&](uint value) { return value < this->threshold; });

  ASSERT_EQ(this->expectedCountOrdered, result->Count());

  for (int i = 0; i < result->Count(); i++)
  {
    ASSERT_EQ(0, result->At(i) / 10);
  }
}

TEST_F(TakeWhileFunctionalTest, TakeWhileDeque)
{
  QueryableDeque<uint> queryableSet = BuildQueryable(this->queryable.ToDeque());
  Queryable<uint>* result = queryableSet
    .TakeWhile([&](uint value) { return value < this->threshold; });

  ASSERT_EQ(this->expectedCountUnordered, result->Count());

  for (int i = 0; i < result->Count(); i++)
  {
    ASSERT_EQ(0, result->At(i) / 10);
  }
}

TEST_F(TakeWhileFunctionalTest, TakeWhileList)
{
  QueryableList<uint> queryableSet = BuildQueryable(this->queryable.ToList());
  Queryable<uint>* result = queryableSet
    .TakeWhile([&](uint value) { return value < this->threshold; });

  ASSERT_EQ(this->expectedCountUnordered, result->Count());

  for (int i = 0; i < result->Count(); i++)
  {
    ASSERT_EQ(0, result->At(i) / 10);
  }
}

TEST_F(TakeWhileFunctionalTest, TakeWhileWhere)
{
  int takeCount = 0;
  int expectedCount = 4;
  QueryableVector<uint> queryableVector = BuildQueryable(std::vector<uint>({ 7, 0, 7, 2, 3, 4, 6, 45, 8, 1, 3, 10 }));
  Queryable<uint> * result = queryableVector
    .Where([](uint value) { return value % 2 == 0; })
    ->TakeWhile([](uint value) { return value < 8; });

  ASSERT_EQ(expectedCount, result->Count());
  result->ForEach([&](uint value) { ASSERT_EQ(takeCount++ * 2, value); });
}
