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

#include "../../../Queryable/Queryable.h"

class TakeFunctionalTest : public ::testing::Test
{
protected:
  int takeCount = 5;
  Queryable<uint, std::vector> queryable;

  void SetUp() override
  {
    this->queryable = Queryable<uint, std::vector>({ 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 });
  }

  template<typename TObj, template<typename...> typename TIterable>
  void TestTake(Queryable<TObj, TIterable> localQueryable, int toTake)
  {
    std::vector<uint> expected;
    for (int i = 0; i < toTake; i++)
    {
      if (i >= localQueryable.Count())
      {
        break;
      }

      expected.push_back(localQueryable.At(i));
    }

    Queryable<uint, TIterable> result = localQueryable.Take(toTake);

    ASSERT_EQ(toTake > result.Count() ? result.Count() : toTake, result.Count());
    ASSERT_EQ(expected.size(), result.Count());

    for (int i = 0; i < result.Count(); i++)
    {
      ASSERT_EQ(expected[i], result.At(i));
    }
  }

  template<typename TObj, template<typename...> typename TIterable>
  void TestTakeNegative(Queryable<TObj, TIterable> localQueryable, int toTake)
  {
    std::vector<uint> expected;
    int startIndex = localQueryable.Count() + toTake;
    for (int i = startIndex; i < localQueryable.Count(); i++)
    {
      expected.push_back(localQueryable.At(i));
    }

    Queryable<uint, TIterable> result = localQueryable.Take(toTake);

    ASSERT_EQ(-toTake, result.Count());
    ASSERT_EQ(expected.size(), result.Count());

    for (int i = 0; i < result.Count(); i++)
    {
      ASSERT_EQ(expected[i], result.At(i));
    }
  }

  void TearDown() override {}
};

TEST_F(TakeFunctionalTest, TakeVectorUninitialized)
{
  Queryable<Person, std::vector> emptyQueryable;
  Queryable<Person, std::vector> result = emptyQueryable.Take(this->takeCount);

  ASSERT_EQ(0, result.Count());
}

TEST_F(TakeFunctionalTest, TakeVectorTakeMoreThanSize)
{
  this->TestTake(this->queryable, this->queryable.Count() + 1);
}

TEST_F(TakeFunctionalTest, TakeVector)
{
  this->TestTake(this->queryable, this->takeCount);
}

TEST_F(TakeFunctionalTest, TakeSet)
{
  this->TestTake(Queryable<uint, std::set>(this->queryable.ToSet()), this->takeCount);
}

TEST_F(TakeFunctionalTest, TakeMultiSet)
{
  this->TestTake(Queryable<uint, std::multiset>(this->queryable.ToMultiSet()), this->takeCount);
}

TEST_F(TakeFunctionalTest, TakeDeque)
{
  this->TestTake(Queryable<uint, std::deque>(this->queryable.ToDeque()), this->takeCount);
}

TEST_F(TakeFunctionalTest, TakeList)
{
  this->TestTake(Queryable<uint, std::list>(this->queryable.ToList()), this->takeCount);
}

TEST_F(TakeFunctionalTest, TakeVectorNegative)
{
  this->TestTakeNegative(this->queryable, -this->takeCount);
}

TEST_F(TakeFunctionalTest, TakeSetNegative)
{
  this->TestTakeNegative(Queryable<uint, std::set>(this->queryable.ToSet()), -this->takeCount);
}

TEST_F(TakeFunctionalTest, TakeMultiSetNegative)
{
  this->TestTakeNegative(Queryable<uint, std::multiset>(this->queryable.ToMultiSet()), -this->takeCount);
}

TEST_F(TakeFunctionalTest, TakeDequeNegative)
{
  this->TestTakeNegative(Queryable<uint, std::deque>(this->queryable.ToDeque()), -this->takeCount);
}

TEST_F(TakeFunctionalTest, TakeListNegative)
{
  this->TestTakeNegative(Queryable<uint, std::list>(this->queryable.ToList()), -this->takeCount);
}
