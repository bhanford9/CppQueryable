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

class SkipWhileFunctionalTest : public ::testing::Test
{
protected:
  uint threshold = 10;
  int expectedCountUnordered = 8;
  int expectedCountOrdered = 6;
  int expectedCountOrderedSet = 5;
  Queryable<uint, std::vector> queryable;

  void SetUp() override
  {
    this->queryable = Queryable<uint, std::vector>({ 4, 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 9, 867, 12 });
  }

  void TearDown() override {}
};

TEST_F(SkipWhileFunctionalTest, SkipWhileVectorUninitialized)
{
  Queryable<Person, std::vector> emptyQueryable;
  Queryable<Person, std::vector> result = emptyQueryable.SkipWhile([](Person p) { return true; });

  ASSERT_EQ(0, result.Count());
}

TEST_F(SkipWhileFunctionalTest, SkipWhileVectorAlwaysTrue)
{
  Queryable<uint, std::vector> result = this->queryable.SkipWhile([](uint value) { return true; });

  ASSERT_EQ(this->queryable.Count(), result.Count());

  for (int i = 0; i < this->queryable.Count(); i++)
  {
    ASSERT_EQ(this->queryable.At(i), result.At(i));
  }
}

TEST_F(SkipWhileFunctionalTest, SkipWhileVector)
{
  Queryable<uint, std::vector> result = this->queryable
    .SkipWhile([&](uint value) { return value < this->threshold; });

  ASSERT_EQ(this->expectedCountUnordered, result.Count());

  for (int i = 0; i < result.Count(); i++)
  {
    ASSERT_TRUE(result.At(i) > 7);
  }
}

TEST_F(SkipWhileFunctionalTest, SkipWhileSet)
{
  Queryable<uint, std::set> result = Queryable<uint, std::set>(this->queryable.ToSet())
    .SkipWhile([&](uint value) { return value < this->threshold; });

  ASSERT_EQ(this->expectedCountOrderedSet, result.Count());

  for (int i = 0; i < result.Count(); i++)
  {
    ASSERT_TRUE((result.At(i) / 10) > 0);
  }
}

TEST_F(SkipWhileFunctionalTest, SkipWhileMultiSet)
{
  Queryable<uint, std::multiset> result = Queryable<uint, std::multiset>(this->queryable.ToMultiSet())
    .SkipWhile([&](uint value) { return value < this->threshold; });

  ASSERT_EQ(this->expectedCountOrdered, result.Count());

  for (int i = 0; i < result.Count(); i++)
  {
    ASSERT_TRUE((result.At(i) / 10) > 0);
  }
}

TEST_F(SkipWhileFunctionalTest, SkipWhileDeque)
{
  Queryable<uint, std::deque> result = Queryable<uint, std::deque>(this->queryable.ToDeque())
    .SkipWhile([&](uint value) { return value < this->threshold; });

  ASSERT_EQ(this->expectedCountUnordered, result.Count());

  for (int i = 0; i < result.Count(); i++)
  {
    ASSERT_TRUE(result.At(i) > 7);
  }
}

TEST_F(SkipWhileFunctionalTest, SkipWhileList)
{
  Queryable<uint, std::list> result = Queryable<uint, std::list>(this->queryable.ToList())
    .SkipWhile([&](uint value) { return value < this->threshold; });

  ASSERT_EQ(this->expectedCountUnordered, result.Count());

  for (int i = 0; i < result.Count(); i++)
  {
    ASSERT_TRUE(result.At(i) > 7);
  }
}
