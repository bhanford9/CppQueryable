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

#include "../../../Queryable/QueryBuilder.h"
#include "../../../Queryable/QueryableVector.h"

using namespace QueryBuilder;

class AtFunctionalTest : public ::testing::Test
{
protected:
  int atIndex = 9;
  uint expectedUnorderedAt = 34;
  uint expectedOrderedAt = 45;
  uint expectedSetAt = 867;
  QueryableVector<uint> queryable;

  void SetUp() override
  {
    this->queryable = BuildQueryable(std::vector<uint>({ 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 }));
  }

  void TearDown() override {}
};

TEST_F(AtFunctionalTest, AtVectorUninitialized)
{
  QueryableVector<Person> emptyQueryable;

  try
  {
    Person p = emptyQueryable.At(this->atIndex);
  }
  catch (std::runtime_error& ex)
  {
    ASSERT_STREQ(ex.what(), "Specified index was outside the bounds of the container");
  }
}

TEST_F(AtFunctionalTest, AtVectorIndexToHigh)
{
  try
  {
    this->queryable.At(this->queryable.Count());
  }
  catch (std::runtime_error& ex)
  {
    ASSERT_STREQ(ex.what(), "Specified index was outside the bounds of the container");
  }
}

TEST_F(AtFunctionalTest, AtVectorIndexNegative)
{
  try
  {
    this->queryable.At(-1);
  }
  catch (std::runtime_error& ex)
  {
    ASSERT_STREQ(ex.what(), "Index must be greater than zero");
  }
}

TEST_F(AtFunctionalTest, AtVector)
{
  uint value = this->queryable.At(this->atIndex);
  ASSERT_EQ(this->expectedUnorderedAt, value);
}

TEST_F(AtFunctionalTest, AtSet)
{
  uint value = BuildQueryable(this->queryable.ToSet()).At(this->atIndex);
  ASSERT_EQ(this->expectedSetAt, value);
}

TEST_F(AtFunctionalTest, AtMultiSet)
{
  uint value = BuildQueryable(this->queryable.ToMultiSet()).At(this->atIndex);
  ASSERT_EQ(this->expectedOrderedAt, value);
}

TEST_F(AtFunctionalTest, AtDeque)
{
  uint value = BuildQueryable(this->queryable.ToDeque()).At(this->atIndex);
  ASSERT_EQ(this->expectedUnorderedAt, value);
}

TEST_F(AtFunctionalTest, AtList)
{
  uint value = BuildQueryable(this->queryable.ToList()).At(this->atIndex);
  ASSERT_EQ(this->expectedUnorderedAt, value);
}

TEST_F(AtFunctionalTest, AtWhere)
{
  uint expected = 8;
  uint value = this->queryable
    .Where([](uint val) { return val % 2 == 0; })
    ->At(3);

  ASSERT_EQ(expected, value);
}
