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

class LastFunctionalTest : public ::testing::Test
{
protected:
  uint expectedUnorderedLast = 9;
  uint expectedOrderedLast = 867;
  uint expectedUnorderedUnder40 = 9;
  uint expectedOrderedUnder40 = 34;
  uint threshold = 40;
  VectorInternalQueryable<uint> queryable;

  void SetUp() override
  {
    this->queryable = VectorInternalQueryable<uint>(std::vector<uint>({ 4, 7, 4, 3, 76, 8, 45, expectedOrderedLast, 76, 0, expectedOrderedUnder40, expectedUnorderedLast }));
  }

  void TearDown() override {}
};

TEST_F(LastFunctionalTest, LastVectorUninitialized)
{
  VectorInternalQueryable<Person> emptyQueryable;

  try
  {
    Person p = emptyQueryable.Last();
  }
  catch (std::runtime_error& ex)
  {
    ASSERT_STREQ(ex.what(), "Cannot get last item of empty collection.");
  }
}

TEST_F(LastFunctionalTest, LastVector)
{
  uint value = this->queryable.Last();
  ASSERT_EQ(this->expectedUnorderedLast, value);
}

TEST_F(LastFunctionalTest, LastSet)
{
  uint value = SetInternalQueryable<uint>(this->queryable.ToSet()).Last();
  ASSERT_EQ(this->expectedOrderedLast, value);
}

TEST_F(LastFunctionalTest, LastMultiSet)
{
  uint value = MultiSetInternalQueryable<uint>(this->queryable.ToMultiSet()).Last();
  ASSERT_EQ(this->expectedOrderedLast, value);
}

TEST_F(LastFunctionalTest, LastDeque)
{
  uint value = DequeInternalQueryable<uint>(this->queryable.ToDeque()).Last();
  ASSERT_EQ(this->expectedUnorderedLast, value);
}

TEST_F(LastFunctionalTest, LastList)
{
  uint value = ListInternalQueryable<uint>(this->queryable.ToList()).Last();
  ASSERT_EQ(this->expectedUnorderedLast, value);
}

TEST_F(LastFunctionalTest, LastWhereVectorUninitialized)
{
  VectorInternalQueryable<Person> emptyQueryable;

  try
  {
    Person p = emptyQueryable.Last([](Person p) { return true; });
  }
  catch (std::runtime_error& ex)
  {
    ASSERT_STREQ(ex.what(), "No item fitting the condition was found.");
  }
}

TEST_F(LastFunctionalTest, LastWhereConditionFails)
{
  try
  {
    this->queryable.Last([](uint value) { return false; });
  }
  catch (std::runtime_error& ex)
  {
    ASSERT_STREQ(ex.what(), "No item fitting the condition was found.");
  }
}

TEST_F(LastFunctionalTest, LastWhereVector)
{
  uint value = this->queryable.Last([&](uint value) { return value < this->threshold; });
  ASSERT_EQ(this->expectedUnorderedUnder40, value);
}

TEST_F(LastFunctionalTest, LastWhereSet)
{
  uint value = SetInternalQueryable<uint>(this->queryable.ToSet())
    .Last([&](uint value) { return value < this->threshold; });
  ASSERT_EQ(this->expectedOrderedUnder40, value);
}

TEST_F(LastFunctionalTest, LastWhereMultiSet)
{
  uint value = MultiSetInternalQueryable<uint>(this->queryable.ToMultiSet())
    .Last([&](uint value) { return value < this->threshold; });
  ASSERT_EQ(this->expectedOrderedUnder40, value);
}

TEST_F(LastFunctionalTest, LastWhereDeque)
{
  uint value = DequeInternalQueryable<uint>(this->queryable.ToDeque())
    .Last([&](uint value) { return value < this->threshold; });
  ASSERT_EQ(this->expectedUnorderedUnder40, value);
}

TEST_F(LastFunctionalTest, LastWhereList)
{
  uint value = ListInternalQueryable<uint>(this->queryable.ToList())
    .Last([&](uint value) { return value < this->threshold; });
  ASSERT_EQ(this->expectedUnorderedUnder40, value);
}

TEST_F(LastFunctionalTest, LastWhereEven)
{
  uint expected = expectedOrderedUnder40;
  uint value = this->queryable
    .Where([](uint value) { return value % 2 == 0; })
    .Last();
  ASSERT_EQ(expected, value);
}

TEST_F(LastFunctionalTest, LastWhereOdd)
{
  uint expected = expectedUnorderedLast;
  uint value = this->queryable
    .Where([](uint value) { return value % 2 == 1; })
    .Last();
  ASSERT_EQ(expected, value);
}

TEST_F(LastFunctionalTest, LastWhereWhereEven)
{
  uint expected = 76;
  uint value = this->queryable
    .Where([](uint value) { return value % 2 == 0; })
    .Last([](uint value) { return value > 40; });
  ASSERT_EQ(expected, value);
}

TEST_F(LastFunctionalTest, LastWhereWhereOdd)
{
  uint expected = expectedOrderedLast;
  uint value = this->queryable
    .Where([](uint value) { return value % 2 == 1; })
    .Last([](uint value) { return value > 40; });
  ASSERT_EQ(expected, value);
}
