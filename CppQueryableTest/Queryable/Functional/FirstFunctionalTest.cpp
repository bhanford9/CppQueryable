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


using namespace QueryBuilder;

class FirstFunctionalTest : public ::testing::Test
{
protected:
  uint expectedUnorderedFirst = 9;
  uint expectedOrderedFirst = 0;
  uint expectedUnorderedOver40 = 76;
  uint expectedOrderedOver40 = 45;
  uint threshold = 40;
  Queryable<uint> queryable;

  void SetUp() override
  {
    this->queryable = BuildQueryable(std::vector<uint>({ expectedUnorderedFirst, 4, 7, 4, 3, 76, 8, 45, 34, 76, 0, 867 }));
  }

  void TearDown() override {}
};

TEST_F(FirstFunctionalTest, FirstVectorUninitialized)
{
  Queryable<Person> emptyQueryable;

  try
  {
    Person p = emptyQueryable.First();
  }
  catch (std::runtime_error& ex)
  {
    ASSERT_STREQ(ex.what(), "Cannot get first item of empty collection.");
  }
}

TEST_F(FirstFunctionalTest, FirstVector)
{
  uint value = this->queryable.First();
  ASSERT_EQ(this->expectedUnorderedFirst, value);
}

TEST_F(FirstFunctionalTest, FirstSet)
{
  uint value = Queryable<uint>(this->queryable.ToSet()).First();
  ASSERT_EQ(this->expectedOrderedFirst, value);
}

TEST_F(FirstFunctionalTest, FirstMultiSet)
{
  uint value = Queryable<uint>(this->queryable.ToMultiSet()).First();
  ASSERT_EQ(this->expectedOrderedFirst, value);
}

TEST_F(FirstFunctionalTest, FirstDeque)
{
  uint value = Queryable<uint>(this->queryable.ToDeque()).First();
  ASSERT_EQ(this->expectedUnorderedFirst, value);
}

TEST_F(FirstFunctionalTest, FirstList)
{
  uint value = Queryable<uint>(this->queryable.ToList()).First();
  ASSERT_EQ(this->expectedUnorderedFirst, value);
}

TEST_F(FirstFunctionalTest, FirstWhereVectorUninitialized)
{
  Queryable<Person> emptyQueryable;

  try
  {
    Person p = emptyQueryable.First([](Person p) { return true; });
  }
  catch (std::runtime_error& ex)
  {
    ASSERT_STREQ(ex.what(), "No item fitting the condition was found.");
  }
}

TEST_F(FirstFunctionalTest, FirstWhereConditionFails)
{
  try
  {
    this->queryable.First([](uint value) { return false; });
  }
  catch (std::runtime_error& ex)
  {
    ASSERT_STREQ(ex.what(), "No item fitting the condition was found.");
  }
}

TEST_F(FirstFunctionalTest, FirstWhereVector)
{
  uint value = this->queryable.First([&](uint value) { return value > this->threshold; });
  ASSERT_EQ(this->expectedUnorderedOver40, value);
}

TEST_F(FirstFunctionalTest, FirstWhereSet)
{
  uint value = Queryable<uint>(this->queryable.ToSet())
    .First([&](uint value) { return value > this->threshold; });
  ASSERT_EQ(this->expectedOrderedOver40, value);
}

TEST_F(FirstFunctionalTest, FirstWhereMultiSet)
{
  uint value = Queryable<uint>(this->queryable.ToMultiSet())
    .First([&](uint value) { return value > this->threshold; });
  ASSERT_EQ(this->expectedOrderedOver40, value);
}

TEST_F(FirstFunctionalTest, FirstWhereDeque)
{
  uint value = Queryable<uint>(this->queryable.ToDeque())
    .First([&](uint value) { return value > this->threshold; });
  ASSERT_EQ(this->expectedUnorderedOver40, value);
}

TEST_F(FirstFunctionalTest, FirstWhereList)
{
  uint value = Queryable<uint>(this->queryable.ToList())
    .First([&](uint value) { return value > this->threshold; });
  ASSERT_EQ(this->expectedUnorderedOver40, value);
}

TEST_F(FirstFunctionalTest, FirstWhereEven)
{
  uint expected = 4;
  uint value = this->queryable
    .Where([](uint value) { return value % 2 == 0; })
    .First();
  ASSERT_EQ(expected, value);
}

TEST_F(FirstFunctionalTest, FirstWhereOdd)
{
  uint expected = expectedUnorderedFirst;
  uint value = this->queryable
    .Where([](uint value) { return value % 2 == 1; })
    .First();
  ASSERT_EQ(expected, value);
}

TEST_F(FirstFunctionalTest, FirstWhereWhereEven)
{
  uint expected = 76;
  uint value = this->queryable
    .Where([](uint value) { return value % 2 == 0; })
    .First([](uint value) { return value > 10; });
  ASSERT_EQ(expected, value);
}

TEST_F(FirstFunctionalTest, FirstWhereWhereOdd)
{
  uint expected = 45;
  uint value = this->queryable
    .Where([](uint value) { return value % 2 == 1; })
    .First([](uint value) { return value > 10; });
  ASSERT_EQ(expected, value);
}
