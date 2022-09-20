#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <vector>

#include "../../../DataStructures/Person.hpp"

#include "../../../Queryable/QueryBuilder.hpp"


using namespace QueryBuilder;

class CountFunctionalTest : public ::testing::Test
{
protected:
  size_t expectedWithDuplicates = 12;
  size_t expectedWithoutDuplicates = 8;
  QueryableVector<size_t> queryable;

  CountFunctionalTest() :
    queryable(BuildQueryable2(std::vector<size_t>({ 7, 4, 7, 4, 3, 76, 8, 45, 34, 76, 8, 867 })))
  {
  }

  void SetUp() override
  {
  }

  void TearDown() override {}
};

// TEST_F(CountFunctionalTest, CountVectorUninitialized)
// {
//   IQueryable<Person> emptyQueryable;
//   ASSERT_EQ(0, emptyQueryable.Count());
// }

TEST_F(CountFunctionalTest, CountVector)
{
  ASSERT_EQ(this->expectedWithDuplicates, this->queryable.Count());
}

TEST_F(CountFunctionalTest, CountSet)
{
  int count = BuildQueryable2(this->queryable.ToSet()).Count();
  ASSERT_EQ(this->expectedWithoutDuplicates, count);
}

TEST_F(CountFunctionalTest, CountMultiSet)
{
  int count = BuildQueryable2(this->queryable.ToMultiSet()).Count();
  ASSERT_EQ(this->expectedWithDuplicates, count);
}

TEST_F(CountFunctionalTest, CountDeque)
{
  int count = BuildQueryable2(this->queryable.ToDeque()).Count();
  ASSERT_EQ(this->expectedWithDuplicates, count);
}

TEST_F(CountFunctionalTest, CountList)
{
  int count = BuildQueryable2(this->queryable.ToList()).Count();
  ASSERT_EQ(this->expectedWithDuplicates, count);
}

TEST_F(CountFunctionalTest, CountWhere)
{
  int expected = 7;
  int count = this->queryable
    .Where([](size_t value) { return value % 2 == 0; })
    .Count();

  ASSERT_EQ(expected, count);
}
