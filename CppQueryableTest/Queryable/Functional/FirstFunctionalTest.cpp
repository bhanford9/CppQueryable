#include <gtest/gtest.h>

#include <array>
#include <deque>
#include <exception>
#include <forward_list>
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
  Queryable<Person, std::vector> queryable;

  void SetUp() override
  {
    this->queryable = Queryable<Person, std::vector>(PersonLibrary().GetPeople());
  }

  void TearDown() override {}
};

TEST_F(FirstFunctionalTest, FirstVectorUninitializedTest)
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
  Person p = this->queryable.First();
}

TEST_F(FirstFunctionalTest, FirstSet)
{
  Person p = Queryable<Person, std::set>(this->queryable.ToSet()).First();
}

TEST_F(FirstFunctionalTest, FirstMultiSet)
{
  Person p = Queryable<Person, std::multiset>(this->queryable.ToMultiSet()).First();
}

TEST_F(FirstFunctionalTest, FirstDeque)
{
  Person p = Queryable<Person, std::deque>(this->queryable.ToDeque()).First();
}

TEST_F(FirstFunctionalTest, FirstForwardList)
{
  Person p = Queryable<Person, std::forward_list>(this->queryable.ToForwardList()).First();
}

TEST_F(FirstFunctionalTest, FirstList)
{
  Person p = Queryable<Person, std::list>(this->queryable.ToList()).First();
}
