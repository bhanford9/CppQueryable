#include <gtest/gtest.h>

#include <array>
#include <deque>
#include <vector>

#include "../../../Queryable/QueryBuilder.hpp"


using namespace QueryBuilder;

class TakeFunctionalTest : public ::testing::Test
{
protected:
  int takeCount = 5;
  QueryableVector<size_t> queryable;

  TakeFunctionalTest() :
    queryable(BuildQueryable(std::vector<size_t>({ 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 })))
  {
  }

  void SetUp() override
  {
  }

  template<
    typename TStoring,
    template<typename, typename ...> typename TIterable,
    typename TIterating,
    typename ...TArgs>
  void TestTake(Queryable<TStoring, TIterable, TIterating, TArgs...> & localQueryable, int toTake)
  {
    std::vector<TIterating> expected;
    const size_t copyToTake = static_cast<size_t>(toTake);

    for (size_t i = 0; i < copyToTake; i++)
    {
      if (i >= localQueryable.Count())
      {
        break;
      }

      expected.push_back(localQueryable.At(i));
    }

    Queryable<TStoring, TIterable, TIterating, TArgs...> & result = localQueryable.Take(toTake);

    ASSERT_EQ(expected.size(), result.Count());
    
    size_t i = 0;
    result.ForEach([&](TIterating value)
    {
      ASSERT_EQ(expected[i++], value);
    });

    for (size_t i = 0; i < result.Count(); i++)
    {
      ASSERT_EQ(expected[i], result.At(i));
    }
  }

  template<
    typename TStoring,
    template<typename, typename ...> typename TIterable,
    typename TIterating,
    typename ...TArgs>
  void TestTakeNegative(Queryable<TStoring, TIterable, TIterating, TArgs...> & localQueryable, int toTake)
  {
    std::vector<TIterating> expected;
    const int startIndex = localQueryable.Count() + toTake;
    for (size_t i = startIndex; i < localQueryable.Count(); i++)
    {
      expected.push_back(localQueryable.At(i));
    }

    Queryable<TStoring, TIterable, TIterating, TArgs...> & result = localQueryable.Take(toTake);

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
  QueryableVector<size_t> localQueryable = BuildQueryable(this->queryable.ToVector());
  this->TestTake(localQueryable, this->queryable.Count() + 1);
}

TEST_F(TakeFunctionalTest, TakeDeque)
{
  QueryableDeque<size_t> localQueryable(BuildQueryable(this->queryable.ToDeque()));
  this->TestTake(localQueryable, this->takeCount);
}

TEST_F(TakeFunctionalTest, TakeList)
{
  QueryableList<size_t> localQueryable(BuildQueryable(this->queryable.ToList()));
  this->TestTake(localQueryable, this->takeCount);
}

//TEST_F(TakeFunctionalTest, TakeMap)
//{
//  QueryableMap<size_t, std::string> localQueryable(BuildQueryable<size_t, std::string>(
//    this->queryable.ToMap<size_t, std::string>(
//      [](size_t value) { return value; },
//      [](size_t value) { return std::to_string(value / 2.0); })));
//  this->TestTake(localQueryable, this->takeCount);
//}

TEST_F(TakeFunctionalTest, TakeMultiSet)
{
  QueryableMultiSet<size_t> localQueryable(BuildQueryable(this->queryable.ToMultiSet()));
  this->TestTake(localQueryable, this->takeCount);
}

TEST_F(TakeFunctionalTest, TakeSet)
{
  QueryableSet<size_t> localQueryable(BuildQueryable(this->queryable.ToSet()));
  this->TestTake(localQueryable, this->takeCount);
}

TEST_F(TakeFunctionalTest, TakeVector)
{
  QueryableVector<size_t> localQueryable = BuildQueryable(this->queryable.ToVector());
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
  const int expectedCount = 3;
  QueryableVector<size_t> queryableVector = BuildQueryable(std::vector<size_t>({ 7, 0, 7, 2, 3, 4, 6, 45, 8, 1, 3, 10 }));
  QueryableVector<size_t> result = queryableVector
    .Where([](size_t value) { return value % 2 == 0; })
    .Take(takeCount);

  ASSERT_EQ(expectedCount, result.Count());

  takeCount = 0;
  result.ForEach([&](size_t value) { ASSERT_EQ(takeCount++ * 2, value); });
}
