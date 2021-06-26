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

class AtFunctionalTest : public ::testing::Test
{
protected:
  int atIndex = 9;
  uint expectedUnorderedAt = 34;
  uint expectedOrderedAt = 45;
  uint expectedSetAt = 867;
  Queryable<uint, std::vector> queryable;

  void SetUp() override
  {
    this->queryable = Queryable<uint, std::vector>({ 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 });
  }

  void TearDown() override {}
};

TEST_F(AtFunctionalTest, AtVectorUninitialized)
{
  Queryable<Person, std::vector> emptyQueryable;

  try
  {
    Person p = emptyQueryable.At(atIndex);
  }
  catch (std::runtime_error& ex)
  {
    ASSERT_STREQ(ex.what(), "Specified index was greater than the size of the collection");
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
    ASSERT_STREQ(ex.what(), "Specified index was greater than the size of the collection");
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
  uint value = this->queryable.At(atIndex);
  ASSERT_EQ(this->expectedUnorderedAt, value);
}

TEST_F(AtFunctionalTest, AtSet)
{
  uint value = Queryable<uint, std::set>(this->queryable.ToSet()).At(atIndex);
  ASSERT_EQ(this->expectedSetAt, value);
}

TEST_F(AtFunctionalTest, AtMultiSet)
{
  uint value = Queryable<uint, std::multiset>(this->queryable.ToMultiSet()).At(atIndex);
  ASSERT_EQ(this->expectedOrderedAt, value);
}

TEST_F(AtFunctionalTest, AtDeque)
{
  uint value = Queryable<uint, std::deque>(this->queryable.ToDeque()).At(atIndex);
  ASSERT_EQ(this->expectedUnorderedAt, value);
}

TEST_F(AtFunctionalTest, AtList)
{
  uint value = Queryable<uint, std::list>(this->queryable.ToList()).At(atIndex);
  ASSERT_EQ(this->expectedUnorderedAt, value);
}
