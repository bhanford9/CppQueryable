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

class SkipFunctionalTest : public ::testing::Test
{
protected:
  size_t SkipCount = 5;
  QueryableVector<size_t> queryable;

  SkipFunctionalTest() :
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
  void TestSkip(Queryable<TStoring, TIterable, TIterating, TArgs...> & localQueryable, size_t toSkip)
  {
    std::vector<TIterating> expected;
    for (size_t i = toSkip; i < localQueryable.Count(); i++)
    {
      expected.push_back(localQueryable.At(i));
    }

    Queryable<TStoring, TIterable, TIterating, TArgs...> & result = localQueryable.Skip(toSkip);

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
  void TestSkipNegative(Queryable<TStoring, TIterable, TIterating, TArgs...> & localQueryable, size_t toSkip)
  {
    std::vector<TIterating> expected;
    size_t endIndex = localQueryable.Count() + toSkip;
    for (size_t i = 0; i < endIndex; i++)
    {
      expected.push_back(localQueryable.At(i));
    }

    Queryable<TStoring, TIterable, TIterating, TArgs...> & result = localQueryable.Skip(toSkip);

    ASSERT_EQ(expected.size(), result.Count());

    for (size_t i = 0; i < result.Count(); i++)
    {
      ASSERT_EQ(expected[i], result.At(i));
    }
  }

  void TearDown() override {}
};

TEST_F(SkipFunctionalTest, SkipVectorSkipMoreThanSize)
{
  this->TestSkip(this->queryable, this->queryable.Count() + 1);
}

TEST_F(SkipFunctionalTest, SkipDeque)
{
  QueryableDeque<size_t> localQueryable = BuildQueryable(this->queryable.ToDeque());
  this->TestSkip(localQueryable, this->SkipCount);
}

TEST_F(SkipFunctionalTest, SkipList)
{
  QueryableList<size_t> localQueryable = BuildQueryable(this->queryable.ToList());
  this->TestSkip(localQueryable, this->SkipCount);
}

TEST_F(SkipFunctionalTest, SkipMap)
{
  QueryableMap<size_t, std::string> localQueryable = BuildQueryable<size_t, std::string>(
    this->queryable.ToMap<size_t, std::string>(
      [](size_t value) { return value; },
      [](size_t value) { return std::to_string(value / 2.0); }));
  this->TestSkip(localQueryable, this->SkipCount);
}

TEST_F(SkipFunctionalTest, SkipMultiSet)
{
  QueryableMultiSet<size_t> localQueryable = BuildQueryable(this->queryable.ToMultiSet());
  this->TestSkip(localQueryable, this->SkipCount);
}

TEST_F(SkipFunctionalTest, SkipSet)
{
  QueryableSet<size_t> localQueryable = BuildQueryable(this->queryable.ToSet());
  this->TestSkip(localQueryable, this->SkipCount);
}

TEST_F(SkipFunctionalTest, SkipVector)
{
  this->TestSkip(this->queryable, this->SkipCount);
}

// TEST_F(SkipFunctionalTest, SkipVectorNegative)
// {
//   this->TestSkipNegative(&this->queryable, -this->SkipCount);
// }

// TEST_F(SkipFunctionalTest, SkipSetNegative)
// {
//   IQueryable<size_t> localQueryable = BuildQueryable(this->queryable.ToSet());
//   this->TestSkipNegative(&localQueryable, -this->SkipCount);
// }

// TEST_F(SkipFunctionalTest, SkipMultiSetNegative)
// {
//   IQueryable<size_t> localQueryable = BuildQueryable(this->queryable.ToMultiSet());
//   this->TestSkipNegative(&localQueryable, -this->SkipCount);
// }

// TEST_F(SkipFunctionalTest, SkipDequeNegative)
// {
//   IQueryable<size_t> localQueryable = BuildQueryable(this->queryable.ToDeque());
//   this->TestSkipNegative(&localQueryable, -this->SkipCount);
// }

// TEST_F(SkipFunctionalTest, SkipListNegative)
// {
//   IQueryable<size_t> localQueryable = BuildQueryable(this->queryable.ToList());
//   this->TestSkipNegative(&localQueryable, -this->SkipCount);
// }

TEST_F(SkipFunctionalTest, SkipWhere)
{
  int skipCount = 3;
  size_t expectedCount = 3;
  QueryableVector<size_t> queryableVector = BuildQueryable(std::vector<size_t>({ 7, 0, 7, 2, 3, 4, 6, 45, 8, 1, 3, 10 }));
  QueryableVector<size_t> result = queryableVector
    .Where([](size_t value) { return value % 2 == 0; })
    .Skip(skipCount);

  ASSERT_EQ(expectedCount, result.Count());
  result.ForEach([&](size_t value) { ASSERT_EQ(skipCount++ * 2, value); });
}
