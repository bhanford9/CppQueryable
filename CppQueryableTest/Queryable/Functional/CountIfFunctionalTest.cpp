#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <vector>

#include "../../../DataStructures/Person.hpp"

#include "../../../Queryable/QueryBuilder.hpp"


using namespace QueryBuilder;

class CountIfFunctionalTest : public ::testing::Test
{
protected:
  int expectedEvensWithDuplicates = 7;
  int expectedEvensWithoutDuplicates = 4;
  QueryableVector<uint> queryable;

  CountIfFunctionalTest() :
    queryable(BuildQueryable2(std::vector<uint>({ 7, 4, 7, 4, 3, 76, 8, 45, 34, 76, 8, 867 })))
  {
  }

  void SetUp() override
  {
  }

  static bool IsEven(uint value)
  {
    return (value % 2) == 0;
  }

  void TearDown() override {}
};

// TEST_F(CountIfFunctionalTest, CountIfVectorUninitialized)
// {
//   QueryableVector<Person> emptyQueryable;
//   ASSERT_EQ(0, emptyQueryable.CountIf([](Person p) { return true; }));
// }

TEST_F(CountIfFunctionalTest, CountIfVector)
{
  ASSERT_EQ(this->expectedEvensWithDuplicates, this->queryable.CountIf(this->IsEven));
}

TEST_F(CountIfFunctionalTest, CountIfSet)
{
  int count = BuildQueryable2(this->queryable.ToSet()).CountIf(this->IsEven);
  ASSERT_EQ(this->expectedEvensWithoutDuplicates, count);
}

TEST_F(CountIfFunctionalTest, CountIfMultiSet)
{
  int count = BuildQueryable2(this->queryable.ToMultiSet()).CountIf(this->IsEven);
  ASSERT_EQ(this->expectedEvensWithDuplicates, count);
}

TEST_F(CountIfFunctionalTest, CountIfDeque)
{
  int count = BuildQueryable2(this->queryable.ToDeque()).CountIf(this->IsEven);
  ASSERT_EQ(this->expectedEvensWithDuplicates, count);
}

TEST_F(CountIfFunctionalTest, CountIfList)
{
  int count = BuildQueryable2(this->queryable.ToList()).CountIf(this->IsEven);
  ASSERT_EQ(this->expectedEvensWithDuplicates, count);
}

TEST_F(CountIfFunctionalTest, CountIfWhere)
{
  int count = this->queryable
    .Where([](uint value) { return value % 2 == 0; })
    .CountIf([] (uint value) { return true; });

  ASSERT_EQ(expectedEvensWithDuplicates, count);
}
