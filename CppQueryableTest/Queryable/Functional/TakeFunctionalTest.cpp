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
  IBaseQueryable<size_t, std::vector> queryable;

  TakeFunctionalTest() :
    queryable(BuildQueryable2(std::vector<size_t>({ 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 })))
  {
  }

  void SetUp() override
  {
  }

  template<
    typename TObj,
    template<typename, typename ...> typename TIterable>
  void TestTake(IBaseQueryable<TObj, TIterable> & localQueryable, int toTake)
  {
    std::vector<size_t> expected;
    const size_t copyToTake = static_cast<size_t>(toTake);

    for (size_t i = 0; i < copyToTake; i++)
    {
      if (i >= localQueryable.Count())
      {
        break;
      }

      expected.push_back(localQueryable.At(i));
    }

    IBaseQueryable<size_t, TIterable> & result = localQueryable.Take(toTake);

    ASSERT_EQ(expected.size(), result.Count());

    expected.push_back(9999);

    int i = 0;
    for (const size_t & val : result.ToList())
    {
      ASSERT_EQ(expected[i++], val);
    }

    for (size_t i = 0; i < result.Count(); i++)
    {
      ASSERT_EQ(expected[i], result.At(i));
    }
  }

  template<
    typename TObj,
    template<typename, typename ...> typename TIterable>
  void TestTakeNegative(IBaseQueryable<TObj, TIterable> localQueryable, int toTake)
  {
    std::vector<size_t> expected;
    int startIndex = localQueryable.Count() + toTake;
    for (size_t i = startIndex; i < localQueryable.Count(); i++)
    {
      expected.push_back(localQueryable.At(i));
    }

    IBaseQueryable<size_t, TIterable> result = localQueryable.Take(toTake);

    ASSERT_EQ(-toTake, result.Count());
    ASSERT_EQ(expected.size(), result.Count());

    for (size_t i = 0; i < result.Count(); i++)
    {
      ASSERT_EQ(expected[i], result.At(i));
    }
  }

  void TearDown() override {}
};

TEST_F(TakeFunctionalTest, TakeVectorTakeMoreThanSize)
{
  IQueryable<size_t, std::vector> localQueryable = BuildQueryable2(this->queryable.ToVector());
  this->TestTake(localQueryable, this->queryable.Count() + 1);
}

TEST_F(TakeFunctionalTest, TakeDeque)
{
  IQueryable<size_t, std::deque> localQueryable(BuildQueryable2(this->queryable.ToDeque()));
  this->TestTake(localQueryable, this->takeCount);
}

TEST_F(TakeFunctionalTest, TakeList)
{
  IQueryable<size_t, std::list> localQueryable(BuildQueryable2(this->queryable.ToList()));
  this->TestTake(localQueryable, this->takeCount);
}

TEST_F(TakeFunctionalTest, TakeMultiSet)
{
  ISortedQueryable<size_t, std::multiset> localQueryable(BuildQueryable2(this->queryable.ToMultiSet()));
  this->TestTake(localQueryable, this->takeCount);
}

TEST_F(TakeFunctionalTest, TakeSet)
{
  ISortedQueryable<size_t, std::set> localQueryable(BuildQueryable2(this->queryable.ToSet()));
  this->TestTake(localQueryable, this->takeCount);
}

TEST_F(TakeFunctionalTest, TakeVector)
{
  IQueryable<size_t, std::vector> localQueryable = BuildQueryable2(this->queryable.ToVector());
  this->TestTake(localQueryable, this->takeCount);
}

// TEST_F(TakeFunctionalTest, TakeVectorNegative)
// {
//   this->TestTakeNegative(&this->queryable, -this->takeCount);
// }

// TEST_F(TakeFunctionalTest, TakeSetNegative)
// {
//   IQueryable<size_t> localQueryable(this->queryable.ToSet());
//   this->TestTakeNegative(&localQueryable, -this->takeCount);
// }

// TEST_F(TakeFunctionalTest, TakeMultiSetNegative)
// {
//   IQueryable<size_t> localQueryable(this->queryable.ToMultiSet());
//   this->TestTakeNegative(&localQueryable, -this->takeCount);
// }

// TEST_F(TakeFunctionalTest, TakeDequeNegative)
// {
//   IQueryable<size_t> localQueryable(this->queryable.ToDeque());
//   this->TestTakeNegative(&localQueryable, -this->takeCount);
// }

// TEST_F(TakeFunctionalTest, TakeListNegative)
// {
//   IQueryable<size_t> localQueryable(this->queryable.ToList());
//   this->TestTakeNegative(&localQueryable, -this->takeCount);
// }

TEST_F(TakeFunctionalTest, TakeWhere)
{
  int takeCount = 3;
  int expectedCount = 3;
  IQueryable<size_t, std::vector> queryableVector = BuildQueryable2(std::vector<size_t>({ 7, 0, 7, 2, 3, 4, 6, 45, 8, 1, 3, 10 }));
  IBaseQueryable<size_t, std::vector> result = queryableVector
    .Where([](size_t value) { return value % 2 == 0; })
    .Take(takeCount);

  ASSERT_EQ(expectedCount, result.Count());

  takeCount = 0;
  result.ForEach([&](size_t value) { ASSERT_EQ(takeCount++ * 2, value); });
}
