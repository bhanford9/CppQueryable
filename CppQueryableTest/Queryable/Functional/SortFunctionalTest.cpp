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
#include "../../../DataStructures/Point.hpp"

#include "../../../Queryable/QueryBuilder.hpp"

using namespace QueryBuilder;

class SortFunctionalTest : public ::testing::Test
{
protected:
  IQueryable<size_t> queryable;
  PersonLibrary personLibrary;
  IQueryable<Person> people;

  SortFunctionalTest() :
    queryable(BuildQueryable2(std::vector<size_t>({ 1, 2, 3, 7, 45, 8, 23, 9 }))), //7, 3, 7, 4, 4, 76, 8, 45, 76, 34, 867, 1, 12 }))),
    personLibrary(),
    people(BuildQueryable2(this->personLibrary.GetPeople()))
  {
  }

  void SetUp() override
  {
  }

  void TearDown() override {}
};

// TEST_F(SortFunctionalTest, SortUninitialized)
// {
//   IQueryable<Person> emptyQueryable;
//   IQueryable<Person> & result = emptyQueryable.Sort();
//   result.ToList();
// }

TEST_F(SortFunctionalTest, DequeDefault)
{
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToDeque());
  local = local.Sort<std::deque>();

  ASSERT_EQ(this->queryable.Count(), local.Count());

  size_t previous = 0;
  local.ForEach([&](size_t value)
  {
    ASSERT_TRUE(previous <= value);
    previous = value;
  });
}

TEST_F(SortFunctionalTest, ListDefault)
{
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToList());
  local.Sort<std::list>();

  ASSERT_EQ(this->queryable.Count(), local.Count());

  size_t previous = 0;
  local.ForEach([&](size_t value)
  {
    ASSERT_TRUE(previous <= value);
    previous = value;
  });
}

TEST_F(SortFunctionalTest, MultiSetDefault)
{
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToMultiSet());
  local.Sort<std::multiset>();

  ASSERT_EQ(this->queryable.Count(), local.Count());

  size_t previous = 0;
  local.ForEach([&](size_t value)
  {
    ASSERT_TRUE(previous <= value);
    previous = value;
  });
}

TEST_F(SortFunctionalTest, SetDefault)
{
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToSet());
  local.Sort<std::set>();

  ASSERT_EQ(this->queryable.Count(), local.Count());

  size_t previous = 0;
  local.ForEach([&](size_t value)
  {
    ASSERT_TRUE(previous <= value);
    previous = value;
  });
}

TEST_F(SortFunctionalTest, VectorDefault)
{
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToVector());
  local = local.Sort<std::vector>();

  ASSERT_EQ(this->queryable.Count(), local.Count());

  size_t previous = 0;
  local.ForEach([&](size_t value)
  {
    ASSERT_TRUE(previous <= value);
    previous = value;
  });
}

TEST_F(SortFunctionalTest, DequeClass)
{
  IQueryable<Person> local = BuildQueryable2(this->people.ToDeque());
  local.Sort<std::deque>();

  ASSERT_EQ(this->people.Count(), local.Count());

  Person previous;
  previous.SetName("\0");
  local.ForEach([&](Person person)
  {
    ASSERT_TRUE(previous.GetName() <= person.GetName());
    previous = person;
  });

  local.Sort<std::deque>([](Person p1, Person p2) { return p1.GetAge() < p2.GetAge(); });

  previous = Person();
  previous.SetAge(-1);
  local.ForEach([&](Person person)
  {
    ASSERT_TRUE(previous.GetAge() <= person.GetAge());
    previous = person;
  });
}

TEST_F(SortFunctionalTest, ListClass)
{
  IQueryable<Person> local = BuildQueryable2(this->people.ToList());
  local.Sort<std::list>();

  ASSERT_EQ(this->people.Count(), local.Count());

  Person previous;
  previous.SetName("\0");
  local.ForEach([&](Person person)
  {
    ASSERT_TRUE(previous.GetName() <= person.GetName());
    previous = person;
  });

  local.Sort<std::list>([](Person p1, Person p2) { return p1.GetAge() < p2.GetAge(); });

  previous = Person();
  previous.SetAge(-1);
  local.ForEach([&](Person person)
  {
    ASSERT_TRUE(previous.GetAge() <= person.GetAge());
    previous = person;
  });
}

TEST_F(SortFunctionalTest, MultiSetClass)
{
  ISortedQueryable<Person> local = BuildQueryable2(this->people.ToMultiSet());
  local.Sort<std::multiset>();

  ASSERT_EQ(this->people.Count(), local.Count());

  Person previous;
  previous.SetName("\0");
  local.ForEach([&](Person person)
  {
    ASSERT_TRUE(previous.GetName() <= person.GetName());
    previous = person;
  });

// have not figured out why this lambda doesn't build yet
//
//   local.Sort<std::multiset>([](Person p1, Person p2) { return p1.GetAge() < p2.GetAge(); });

//   previous = Person();
//   previous.SetAge(-1);
//   local.ForEach([&](Person person)
//   {
//     ASSERT_TRUE(previous.GetAge() <= person.GetAge());
//     previous = person;
//   });
}

TEST_F(SortFunctionalTest, VectorClass)
{
  IQueryable<Person> local = BuildQueryable2(this->people.ToVector());
  local.Sort<std::vector>();

  ASSERT_EQ(this->people.Count(), local.Count());

  Person previous;
  previous.SetName("\0");
  local.ForEach([&](Person person)
  {
    ASSERT_TRUE(previous.GetName() <= person.GetName());
    previous = person;
  });

  local.Sort<std::vector>([](Person p1, Person p2) { return p1.GetAge() < p2.GetAge(); });

  previous = Person();
  previous.SetAge(-1);
  local.ForEach([&](Person person)
  {
    ASSERT_TRUE(previous.GetAge() <= person.GetAge());
    previous = person;
  });
}

TEST_F(SortFunctionalTest, WhereSort)
{
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToVector());

  local
    .Where([](size_t value) { return (value % 2) == 0; })
    .Sort<std::vector>();

    ASSERT_TRUE(this->queryable.Count() > local.Count());

    size_t previous = 0;
    local.ForEach([&](size_t value)
    {
      ASSERT_TRUE((value % 2) == 0);
      ASSERT_TRUE(previous <= value);
      previous = value;
    });
}
