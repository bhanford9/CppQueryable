#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <vector>

#include "../../../DataStructures/Gender.h"
#include "../../../DataStructures/Person.h"
#include "../../../DataStructures/PersonLibrary.h"

#include "../../../Queryable/QueryBuilder.h"


using namespace QueryBuilder;

class CountFunctionalTest : public ::testing::Test
{
protected:
  uint expectedWithDuplicates = 12;
  uint expectedWithoutDuplicates = 8;
  Queryable<uint> queryable;

  void SetUp() override
  {
    this->queryable = BuildQueryable(std::vector<uint>({ 7, 4, 7, 4, 3, 76, 8, 45, 34, 76, 8, 867 }));
  }

  void TearDown() override {}
};

TEST_F(CountFunctionalTest, CountVectorUninitialized)
{
  // Queryable<Person> emptyQueryable;
  // ASSERT_EQ(0, emptyQueryable.Count());
}

TEST_F(CountFunctionalTest, CountVector)
{
  ASSERT_EQ(this->expectedWithDuplicates, this->queryable.Count());
}

TEST_F(CountFunctionalTest, CountSet)
{
  int count = BuildQueryable(this->queryable.ToSet()).Count();
  ASSERT_EQ(this->expectedWithoutDuplicates, count);
}

TEST_F(CountFunctionalTest, CountMultiSet)
{
  int count = BuildQueryable(this->queryable.ToMultiSet()).Count();
  ASSERT_EQ(this->expectedWithDuplicates, count);
}

TEST_F(CountFunctionalTest, CountDeque)
{
  int count = BuildQueryable(this->queryable.ToDeque()).Count();
  ASSERT_EQ(this->expectedWithDuplicates, count);
}

TEST_F(CountFunctionalTest, CountList)
{
  int count = BuildQueryable(this->queryable.ToList()).Count();
  ASSERT_EQ(this->expectedWithDuplicates, count);
}

TEST_F(CountFunctionalTest, CountWhere)
{
  int expected = 7;
  int count = this->queryable
    .Where([](uint value) { return value % 2 == 0; })
    .Count();

  ASSERT_EQ(expected, count);
}
