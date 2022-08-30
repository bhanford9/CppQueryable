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

class TakeFunctionalTest : public ::testing::Test
{
protected:
  int takeCount = 5;
  IQueryable<uint> queryable;

  TakeFunctionalTest() :
    queryable(BuildQueryable2(std::vector<uint>({ 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 })))
  {
  }

  void SetUp() override
  {
  }

  template<typename TObj>
  void TestTake(IQueryable<TObj> localQueryable, int toTake)
  {
    std::vector<uint> expected;
    const size_t copyToTake = static_cast<size_t>(toTake);

    for (size_t i = 0; i < copyToTake; i++)
    {
      if (i >= localQueryable.Count())
      {
        break;
      }

      expected.push_back(localQueryable.At(i));
    }

    IQueryable<uint> result = localQueryable.Take(toTake);

    ASSERT_EQ(expected.size(), result.Count());

    expected.push_back(9999);

    int i = 0;
    for (const uint & val : result.ToList())
    {
      ASSERT_EQ(expected[i++], val);
    }

    for (size_t i = 0; i < result.Count(); i++)
    {
      ASSERT_EQ(expected[i], result.At(i));
    }
  }

  template<typename TObj>
  void TestTakeNegative(IQueryable<TObj> localQueryable, int toTake)
  {
    std::vector<uint> expected;
    int startIndex = localQueryable.Count() + toTake;
    for (size_t i = startIndex; i < localQueryable.Count(); i++)
    {
      expected.push_back(localQueryable.At(i));
    }

    IQueryable<uint> result = localQueryable.Take(toTake);

    ASSERT_EQ(-toTake, result.Count());
    ASSERT_EQ(expected.size(), result.Count());

    for (size_t i = 0; i < result.Count(); i++)
    {
      ASSERT_EQ(expected[i], result.At(i));
    }
  }

  void TearDown() override {}
};

// TEST_F(TakeFunctionalTest, TakeVectorUninitialized)
// {
//   IQueryable<Person> emptyQueryable;
//   IQueryable<Person> result = emptyQueryable.Take(this->takeCount);

//   ASSERT_EQ(0, result.Count());
// }

// TEST_F(TakeFunctionalTest, TakeVectorTakeMoreThanSize)
// {
//   IQueryable<uint> localQueryable = BuildQueryable2(this->queryable.ToVector());
//   this->TestTake(localQueryable, this->queryable.Count() + 1);
// }

TEST_F(TakeFunctionalTest, TakeVector)
{
  IQueryable<uint> localQueryable = BuildQueryable2(this->queryable.ToVector());
  this->TestTake(localQueryable, this->takeCount);
}

TEST_F(TakeFunctionalTest, TakeVector2)
{
  IQueryable<uint> localQueryable = BuildQueryable2(this->queryable.ToVector());
  this->TestTake(localQueryable, this->takeCount);
}

// TEST_F(TakeFunctionalTest, TakeSet)
// {
//   IQueryable<uint> localQueryable(this->queryable.ToSet());
//   this->TestTake(&localQueryable, this->takeCount);
// }

// TEST_F(TakeFunctionalTest, TakeMultiSet)
// {
//   IQueryable<uint> localQueryable(this->queryable.ToMultiSet());
//   this->TestTake(&localQueryable, this->takeCount);
// }

TEST_F(TakeFunctionalTest, TakeDeque)
{
  IQueryable<uint> localQueryable(BuildQueryable2(this->queryable.ToDeque()));
  this->TestTake(localQueryable, this->takeCount);
}

TEST_F(TakeFunctionalTest, TakeList)
{
  IQueryable<uint> localQueryable(BuildQueryable2(this->queryable.ToList()));
  this->TestTake(localQueryable, this->takeCount);
}

// TEST_F(TakeFunctionalTest, TakeVectorNegative)
// {
//   this->TestTakeNegative(&this->queryable, -this->takeCount);
// }

// TEST_F(TakeFunctionalTest, TakeSetNegative)
// {
//   IQueryable<uint> localQueryable(this->queryable.ToSet());
//   this->TestTakeNegative(&localQueryable, -this->takeCount);
// }

// TEST_F(TakeFunctionalTest, TakeMultiSetNegative)
// {
//   IQueryable<uint> localQueryable(this->queryable.ToMultiSet());
//   this->TestTakeNegative(&localQueryable, -this->takeCount);
// }

// TEST_F(TakeFunctionalTest, TakeDequeNegative)
// {
//   IQueryable<uint> localQueryable(this->queryable.ToDeque());
//   this->TestTakeNegative(&localQueryable, -this->takeCount);
// }

// TEST_F(TakeFunctionalTest, TakeListNegative)
// {
//   IQueryable<uint> localQueryable(this->queryable.ToList());
//   this->TestTakeNegative(&localQueryable, -this->takeCount);
// }

TEST_F(TakeFunctionalTest, TakeWhere)
{
  int takeCount = 3;
  int expectedCount = 3;
  IQueryable<uint> queryableVector = BuildQueryable2(std::vector<uint>({ 7, 0, 7, 2, 3, 4, 6, 45, 8, 1, 3, 10 }));
  IQueryable<uint>  result = queryableVector
    .Where([](uint value) { return value % 2 == 0; })
    .Take(takeCount);

  ASSERT_EQ(expectedCount, result.Count());

  takeCount = 0;
  result.ForEach([&](uint value) { ASSERT_EQ(takeCount++ * 2, value); });
}
