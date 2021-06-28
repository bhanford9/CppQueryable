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

class CountIfFunctionalTest : public ::testing::Test
{
protected:
  int expectedEvensWithDuplicates = 7;
  int expectedEvensWithoutDuplicates = 4;
  Queryable<uint, std::vector> queryable;

  void SetUp() override
  {
    this->queryable = Queryable<uint, std::vector>({ 7, 4, 7, 4, 3, 76, 8, 45, 34, 76, 8, 867 });
  }

  static bool IsEven(uint value)
  {
    return (value % 2) == 0;
  }

  void TearDown() override {}
};

TEST_F(CountIfFunctionalTest, CountIfVectorUninitialized)
{
  Queryable<Person, std::vector> emptyQueryable;
  ASSERT_EQ(0, emptyQueryable.CountIf([](Person p) { return true; }));
}

TEST_F(CountIfFunctionalTest, CountIfVector)
{
  ASSERT_EQ(this->expectedEvensWithDuplicates, this->queryable.CountIf(this->IsEven));
}

TEST_F(CountIfFunctionalTest, CountIfSet)
{
  int count = Queryable<uint, std::set>(this->queryable.ToSet()).CountIf(this->IsEven);
  ASSERT_EQ(this->expectedEvensWithoutDuplicates, count);
}

TEST_F(CountIfFunctionalTest, CountIfMultiSet)
{
  int count = Queryable<uint, std::multiset>(this->queryable.ToMultiSet()).CountIf(this->IsEven);
  ASSERT_EQ(this->expectedEvensWithDuplicates, count);
}

TEST_F(CountIfFunctionalTest, CountIfDeque)
{
  int count = Queryable<uint, std::deque>(this->queryable.ToDeque()).CountIf(this->IsEven);
  ASSERT_EQ(this->expectedEvensWithDuplicates, count);
}

TEST_F(CountIfFunctionalTest, CountIfList)
{
  int count = Queryable<uint, std::list>(this->queryable.ToList()).CountIf(this->IsEven);
  ASSERT_EQ(this->expectedEvensWithDuplicates, count);
}
