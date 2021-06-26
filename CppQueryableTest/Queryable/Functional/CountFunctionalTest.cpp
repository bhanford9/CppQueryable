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

class CountFunctionalTest : public ::testing::Test
{
protected:
  uint expectedWithDuplicates = 12;
  uint expectedWithoutDuplicates = 8;
  Queryable<uint, std::vector> queryable;

  void SetUp() override
  {
    this->queryable = Queryable<uint, std::vector>({ 7, 4, 7, 4, 3, 76, 8, 45, 34, 76, 8, 867 });
  }

  void TearDown() override {}
};

TEST_F(CountFunctionalTest, CountVectorUninitialized)
{
  Queryable<Person, std::vector> emptyQueryable;
  ASSERT_EQ(0, emptyQueryable.Count());
}

TEST_F(CountFunctionalTest, CountVector)
{
  ASSERT_EQ(this->expectedWithDuplicates, this->queryable.Count());
}

TEST_F(CountFunctionalTest, CountSet)
{
  int count = Queryable<uint, std::set>(this->queryable.ToSet()).Count();
  ASSERT_EQ(this->expectedWithoutDuplicates, count);
}

TEST_F(CountFunctionalTest, CountMultiSet)
{
  int count = Queryable<uint, std::multiset>(this->queryable.ToMultiSet()).Count();
  ASSERT_EQ(this->expectedWithDuplicates, count);
}

TEST_F(CountFunctionalTest, CountDeque)
{
  int count = Queryable<uint, std::deque>(this->queryable.ToDeque()).Count();
  ASSERT_EQ(this->expectedWithDuplicates, count);
}

TEST_F(CountFunctionalTest, CountList)
{
  int count = Queryable<uint, std::list>(this->queryable.ToList()).Count();
  ASSERT_EQ(this->expectedWithDuplicates, count);
}
