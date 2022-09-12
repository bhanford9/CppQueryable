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

class SkipWhileFunctionalTest : public ::testing::Test
{
protected:
  size_t threshold = 10;
  int expectedCountUnordered = 8;
  int expectedCountOrdered = 6;
  int expectedCountOrderedSet = 5;
  IQueryable<size_t> queryable;

  SkipWhileFunctionalTest() :
    queryable(BuildQueryable2(std::vector<size_t>({ 4, 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 9, 867, 12 })))
  {
  }

  void SetUp() override
  {
  }

  void TearDown() override {}
};

TEST_F(SkipWhileFunctionalTest, SkipWhileVectorAlwaysTrue)
{
  IBaseQueryable<size_t> result = this->queryable.SkipWhile([](size_t value) { return true; });

  ASSERT_EQ(this->queryable.Count(), result.Count());

  for (size_t i = 0; i < this->queryable.Count(); i++)
  {
    ASSERT_EQ(this->queryable.At(i), result.At(i));
  }
}

TEST_F(SkipWhileFunctionalTest, SkipWhileVector)
{
  IBaseQueryable<size_t> result = this->queryable
    .SkipWhile([&](size_t value) { return value < this->threshold; });

  ASSERT_EQ(this->expectedCountUnordered, result.Count());

  for (size_t i = 0; i < result.Count(); i++)
  {
    ASSERT_TRUE(result.At(i) > 7);
  }
}

TEST_F(SkipWhileFunctionalTest, SkipWhileSet)
{
  ISortedQueryable<size_t> localQueryable = BuildQueryable2(this->queryable.ToSet());
  IBaseQueryable<size_t> result = localQueryable
    .SkipWhile([&](size_t value) { return value < this->threshold; });

  ASSERT_EQ(this->expectedCountOrderedSet, result.Count());

  for (size_t i = 0; i < result.Count(); i++)
  {
    ASSERT_TRUE((result.At(i) / 10) > 0);
  }
}

TEST_F(SkipWhileFunctionalTest, SkipWhileMultiSet)
{
  ISortedQueryable<size_t> localQueryable = BuildQueryable2(this->queryable.ToMultiSet());
  IBaseQueryable<size_t> result = localQueryable
    .SkipWhile([&](size_t value) { return value < this->threshold; });

  ASSERT_EQ(this->expectedCountOrdered, result.Count());

  for (size_t i = 0; i < result.Count(); i++)
  {
    ASSERT_TRUE((result.At(i) / 10) > 0);
  }
}

TEST_F(SkipWhileFunctionalTest, SkipWhileDeque)
{
  IQueryable<size_t> localQueryable = BuildQueryable2(this->queryable.ToDeque());
  IBaseQueryable<size_t> result = localQueryable
    .SkipWhile([&](size_t value) { return value < this->threshold; });

  ASSERT_EQ(this->expectedCountUnordered, result.Count());

  for (size_t i = 0; i < result.Count(); i++)
  {
    ASSERT_TRUE(result.At(i) > 7);
  }
}

TEST_F(SkipWhileFunctionalTest, SkipWhileList)
{
  IQueryable<size_t> localQueryable = BuildQueryable2(this->queryable.ToList());
  IBaseQueryable<size_t> result = localQueryable
    .SkipWhile([&](size_t value) { return value < this->threshold; });

  ASSERT_EQ(this->expectedCountUnordered, result.Count());

  for (size_t i = 0; i < result.Count(); i++)
  {
    ASSERT_TRUE(result.At(i) > 7);
  }
}

TEST_F(SkipWhileFunctionalTest, SkipWhileWhere)
{
  int skipCount = 4;
  int expectedCount = 2;
  IQueryable<size_t> localQueryable = BuildQueryable2(std::vector<size_t>({ 7, 0, 7, 2, 3, 4, 6, 45, 8, 1, 3, 10 }));
  IBaseQueryable<size_t> result = localQueryable
    .Where([](size_t value) { return value % 2 == 0; })
    .SkipWhile([](size_t value) { return value < 8; });

  ASSERT_EQ(expectedCount, result.Count());
  result.ForEach([&](size_t value) { ASSERT_EQ(skipCount++ * 2, value); });
}
