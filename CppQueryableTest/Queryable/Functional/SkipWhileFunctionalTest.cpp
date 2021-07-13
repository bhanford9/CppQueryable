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

class SkipWhileFunctionalTest : public ::testing::Test
{
protected:
  uint threshold = 10;
  int expectedCountUnordered = 8;
  int expectedCountOrdered = 6;
  int expectedCountOrderedSet = 5;
  QueryableVector<uint> queryable;

  void SetUp() override
  {
    this->queryable = QueryableVector<uint>({ 4, 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 9, 867, 12 });
  }

  void TearDown() override {}
};

TEST_F(SkipWhileFunctionalTest, SkipWhileVectorUninitialized)
{
  QueryableVector<Person> emptyQueryable;
  Queryable<Person> * result = emptyQueryable.SkipWhile([](Person p) { return true; });

  ASSERT_EQ(0, result->Count());
}

TEST_F(SkipWhileFunctionalTest, SkipWhileVectorAlwaysTrue)
{
  Queryable<uint>* result = this->queryable.SkipWhile([](uint value) { return true; });

  ASSERT_EQ(this->queryable.Count(), result->Count());

  for (int i = 0; i < this->queryable.Count(); i++)
  {
    ASSERT_EQ(this->queryable.At(i), result->At(i));
  }
}

TEST_F(SkipWhileFunctionalTest, SkipWhileVector)
{
  Queryable<uint>* result = this->queryable
    .SkipWhile([&](uint value) { return value < this->threshold; });

  ASSERT_EQ(this->expectedCountUnordered, result->Count());

  for (int i = 0; i < result->Count(); i++)
  {
    ASSERT_TRUE(result->At(i) > 7);
  }
}

TEST_F(SkipWhileFunctionalTest, SkipWhileSet)
{
  QueryableSet<uint> queryableSet = BuildQueryable(this->queryable.ToSet());
  Queryable<uint>* result = queryableSet
    .SkipWhile([&](uint value) { return value < this->threshold; });

  ASSERT_EQ(this->expectedCountOrderedSet, result->Count());

  for (int i = 0; i < result->Count(); i++)
  {
    ASSERT_TRUE((result->At(i) / 10) > 0);
  }
}

TEST_F(SkipWhileFunctionalTest, SkipWhileMultiSet)
{
  QueryableMultiSet<uint> queryableSet = BuildQueryable(this->queryable.ToMultiSet());
  Queryable<uint>* result = queryableSet
    .SkipWhile([&](uint value) { return value < this->threshold; });

  ASSERT_EQ(this->expectedCountOrdered, result->Count());

  for (int i = 0; i < result->Count(); i++)
  {
    ASSERT_TRUE((result->At(i) / 10) > 0);
  }
}

TEST_F(SkipWhileFunctionalTest, SkipWhileDeque)
{
  QueryableDeque<uint> queryableSet = BuildQueryable(this->queryable.ToDeque());
  Queryable<uint>* result = queryableSet
    .SkipWhile([&](uint value) { return value < this->threshold; });

  ASSERT_EQ(this->expectedCountUnordered, result->Count());

  for (int i = 0; i < result->Count(); i++)
  {
    ASSERT_TRUE(result->At(i) > 7);
  }
}

TEST_F(SkipWhileFunctionalTest, SkipWhileList)
{
  QueryableList<uint> queryableSet = BuildQueryable(this->queryable.ToList());
  Queryable<uint>* result = queryableSet
    .SkipWhile([&](uint value) { return value < this->threshold; });

  ASSERT_EQ(this->expectedCountUnordered, result->Count());

  for (int i = 0; i < result->Count(); i++)
  {
    ASSERT_TRUE(result->At(i) > 7);
  }
}
