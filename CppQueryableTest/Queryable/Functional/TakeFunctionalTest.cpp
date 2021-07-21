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

class TakeFunctionalTest : public ::testing::Test
{
protected:
  int takeCount = 5;
  QueryableVector<uint> queryable;

  void SetUp() override
  {
    this->queryable = QueryableVector<uint>({ 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 });
  }

  template<typename TObj>
  void TestTake(Queryable<TObj> * localQueryable, int toTake)
  {
    std::vector<uint> expected;
    for (int i = 0; i < toTake; i++)
    {
      if (i >= localQueryable->Count())
      {
        break;
      }

      expected.push_back(localQueryable->At(i));
    }

    Queryable<uint> * result = localQueryable->Take(toTake);

    ASSERT_EQ(toTake > result->Count() ? result->Count() : toTake, result->Count());
    ASSERT_EQ(expected.size(), result->Count());

    for (int i = 0; i < result->Count(); i++)
    {
      ASSERT_EQ(expected[i], result->At(i));
    }
  }

  template<typename TObj>
  void TestTakeNegative(Queryable<TObj> * localQueryable, int toTake)
  {
    std::vector<uint> expected;
    int startIndex = localQueryable->Count() + toTake;
    for (int i = startIndex; i < localQueryable->Count(); i++)
    {
      expected.push_back(localQueryable->At(i));
    }

    Queryable<uint>* result = localQueryable->Take(toTake);

    ASSERT_EQ(-toTake, result->Count());
    ASSERT_EQ(expected.size(), result->Count());

    for (int i = 0; i < result->Count(); i++)
    {
      ASSERT_EQ(expected[i], result->At(i));
    }
  }

  void TearDown() override {}
};

TEST_F(TakeFunctionalTest, TakeVectorUninitialized)
{
  QueryableVector<Person> emptyQueryable;
  Queryable<Person> * result = emptyQueryable.Take(this->takeCount);

  ASSERT_EQ(0, result->Count());
}

TEST_F(TakeFunctionalTest, TakeVectorTakeMoreThanSize)
{
  this->TestTake(&this->queryable, this->queryable.Count() + 1);
}

TEST_F(TakeFunctionalTest, TakeVector)
{
  this->TestTake(&this->queryable, this->takeCount);
}

TEST_F(TakeFunctionalTest, TakeSet)
{
  QueryableSet<uint> localQueryable(this->queryable.ToSet());
  this->TestTake(&localQueryable, this->takeCount);
}

TEST_F(TakeFunctionalTest, TakeMultiSet)
{
  QueryableMultiSet<uint> localQueryable(this->queryable.ToMultiSet());
  this->TestTake(&localQueryable, this->takeCount);
}

TEST_F(TakeFunctionalTest, TakeDeque)
{
  QueryableDeque<uint> localQueryable(this->queryable.ToDeque());
  this->TestTake(&localQueryable, this->takeCount);
}

TEST_F(TakeFunctionalTest, TakeList)
{
  QueryableList<uint> localQueryable(this->queryable.ToList());
  this->TestTake(&localQueryable, this->takeCount);
}

TEST_F(TakeFunctionalTest, TakeVectorNegative)
{
  this->TestTakeNegative(&this->queryable, -this->takeCount);
}

TEST_F(TakeFunctionalTest, TakeSetNegative)
{
  QueryableSet<uint> localQueryable(this->queryable.ToSet());
  this->TestTakeNegative(&localQueryable, -this->takeCount);
}

TEST_F(TakeFunctionalTest, TakeMultiSetNegative)
{
  QueryableMultiSet<uint> localQueryable(this->queryable.ToMultiSet());
  this->TestTakeNegative(&localQueryable, -this->takeCount);
}

TEST_F(TakeFunctionalTest, TakeDequeNegative)
{
  QueryableDeque<uint> localQueryable(this->queryable.ToDeque());
  this->TestTakeNegative(&localQueryable, -this->takeCount);
}

TEST_F(TakeFunctionalTest, TakeListNegative)
{
  QueryableList<uint> localQueryable(this->queryable.ToList());
  this->TestTakeNegative(&localQueryable, -this->takeCount);
}

TEST_F(TakeFunctionalTest, TakeWhere)
{
  int takeCount = 3;
  int expectedCount = 3;
  QueryableVector<uint> queryableVector = BuildQueryable(std::vector<uint>({ 7, 0, 7, 2, 3, 4, 6, 45, 8, 1, 3, 10 }));
  Queryable<uint> * result = queryableVector
    .Where([](uint value) { return value % 2 == 0; })
    ->Take(takeCount);

  ASSERT_EQ(expectedCount, result->Count());

  takeCount = 0;
  result->ForEach([&](uint value) { ASSERT_EQ(takeCount++ * 2, value); });
}
