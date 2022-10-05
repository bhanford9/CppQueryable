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
  QueryableVector<size_t> queryable;

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
  QueryableVector<size_t> result = this->queryable.SkipWhile([](size_t value) { return true; });

  ASSERT_EQ(this->queryable.Count(), result.Count());

  for (size_t i = 0; i < this->queryable.Count(); i++)
  {
    ASSERT_EQ(this->queryable.At(i), result.At(i));
  }
}

TEST_F(SkipWhileFunctionalTest, SkipWhileDeque)
{
  QueryableDeque<size_t> localQueryable = BuildQueryable2(this->queryable.ToDeque());
  QueryableDeque<size_t> result = localQueryable
    .SkipWhile([&](size_t value) { return value < this->threshold; });

  ASSERT_EQ(this->expectedCountUnordered, result.Count());

  for (size_t i = 0; i < result.Count(); i++)
  {
    ASSERT_TRUE(result.At(i) > 7);
  }
}

TEST_F(SkipWhileFunctionalTest, SkipWhileList)
{
  // somethings not right with Skip While. It seems to iterate over the collection several times
  QueryableList<size_t> localQueryable = BuildQueryable2(this->queryable.ToList());
  QueryableList<size_t> result = localQueryable
    .SkipWhile([&](size_t value) { std::cout << "value: " << value << std::endl; return value < this->threshold; });

  ASSERT_EQ(this->expectedCountUnordered, result.Count());

  for (size_t i = 0; i < result.Count(); i++)
  {
    ASSERT_TRUE(result.At(i) > 7);
  }
}

TEST_F(SkipWhileFunctionalTest, SkipWhileMap)
{
  QueryableMap<size_t, std::string> localQueryable = BuildQueryable2<size_t, std::string>(
    this->queryable.ToMap<size_t, std::string>(
      [](size_t value) { return value; },
      [](size_t value) { return std::to_string(value / 2.0); }));
  QueryableMap<size_t, std::string> result = localQueryable
    .SkipWhile([&](std::pair<const size_t, std::string> kvp) { return kvp.first < this->threshold; });

  ASSERT_EQ(this->expectedCountOrderedSet, result.Count());

  for (size_t i = 0; i < result.Count(); i++)
  {
    ASSERT_TRUE((result.At(i).first / 10.0) > 1.0);
  }
}

TEST_F(SkipWhileFunctionalTest, SkipWhileMultiSet)
{
  QueryableMultiSet<size_t> localQueryable = BuildQueryable2(this->queryable.ToMultiSet());
  QueryableMultiSet<size_t> result = localQueryable
    .SkipWhile([&](size_t value) { return value < this->threshold; });

  ASSERT_EQ(this->expectedCountOrdered, result.Count());

  for (size_t i = 0; i < result.Count(); i++)
  {
    ASSERT_TRUE((result.At(i) / 10.0) > 1.0);
  }
}

TEST_F(SkipWhileFunctionalTest, SkipWhileSet)
{
  QueryableSet<size_t> localQueryable = BuildQueryable2(this->queryable.ToSet());
  QueryableSet<size_t> result = localQueryable
    .SkipWhile([&](size_t value) { return value < this->threshold; });

  ASSERT_EQ(this->expectedCountOrderedSet, result.Count());

  for (size_t i = 0; i < result.Count(); i++)
  {
    ASSERT_TRUE((result.At(i) / 10.0) > 1.0);
  }
}

TEST_F(SkipWhileFunctionalTest, SkipWhileVector)
{
  QueryableVector<size_t> result = this->queryable
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
  QueryableVector<size_t> localQueryable = BuildQueryable2(std::vector<size_t>({ 7, 0, 7, 2, 3, 4, 6, 45, 8, 1, 3, 10 }));
  QueryableVector<size_t> result = localQueryable
    .Where([](size_t value) { return value % 2 == 0; })
    .SkipWhile([](size_t value) { return value < 8; });

  ASSERT_EQ(expectedCount, result.Count());
  result.ForEach([&](size_t value) { ASSERT_EQ(skipCount++ * 2, value); });
}
