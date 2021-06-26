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

class FirstFunctionalTest : public ::testing::Test
{
protected:
  uint expectedUnorderedFirst = 9;
  uint expectedOrderedFirst = 0;
  Queryable<uint, std::vector> queryable;

  void SetUp() override
  {
    this->queryable = Queryable<uint, std::vector>({ expectedUnorderedFirst, 4, 7, 4, 3, 76, 8, 45, 34, 76, 0, 867 });
  }

  void TearDown() override {}
};

TEST_F(FirstFunctionalTest, FirstVectorUninitialized)
{
  Queryable<Person, std::vector> emptyQueryable;

  try
  {
    Person p = emptyQueryable.First();
  }
  catch (std::runtime_error& ex)
  {
    ASSERT_STREQ(ex.what(), "Cannot get first element of empty collection");
  }
}

TEST_F(FirstFunctionalTest, FirstVector)
{
  uint value = this->queryable.First();
  ASSERT_EQ(this->expectedUnorderedFirst, value);
}

TEST_F(FirstFunctionalTest, FirstSet)
{
  uint value = Queryable<uint, std::set>(this->queryable.ToSet()).First();
  ASSERT_EQ(this->expectedOrderedFirst, value);
}

TEST_F(FirstFunctionalTest, FirstMultiSet)
{
  uint value = Queryable<uint, std::multiset>(this->queryable.ToMultiSet()).First();
  ASSERT_EQ(this->expectedOrderedFirst, value);
}

TEST_F(FirstFunctionalTest, FirstDeque)
{
  uint value = Queryable<uint, std::deque>(this->queryable.ToDeque()).First();
  ASSERT_EQ(this->expectedUnorderedFirst, value);
}

TEST_F(FirstFunctionalTest, FirstList)
{
  uint value = Queryable<uint, std::list>(this->queryable.ToList()).First();
  ASSERT_EQ(this->expectedUnorderedFirst, value);
}
