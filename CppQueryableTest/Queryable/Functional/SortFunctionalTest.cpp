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
  QueryableVector<size_t> queryable;
  PersonLibrary personLibrary;
  QueryableVector<Person> people;

  SortFunctionalTest() :
    queryable(BuildQueryable(std::vector<size_t>({ 1, 2, 3, 7, 45, 8, 23, 9 }))), //7, 3, 7, 4, 4, 76, 8, 45, 76, 34, 867, 1, 12 }))),
    personLibrary(),
    people(BuildQueryable(this->personLibrary.GetPeople()))
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
  QueryableDeque<size_t> local = BuildQueryable(this->queryable.ToDeque());
  local.Sort();

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
  QueryableList<size_t> local = BuildQueryable(this->queryable.ToList());
  local.Sort();

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
  QueryableMultiSet<size_t> local = BuildQueryable(this->queryable.ToMultiSet());
  local.Sort();

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
  QueryableSet<size_t> local = BuildQueryable(this->queryable.ToSet());
  local.Sort();

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
  QueryableVector<size_t> local = BuildQueryable(this->queryable.ToVector());
  local.Sort();

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
  QueryableDeque<Person> local = BuildQueryable(this->people.ToDeque());
  local.Sort();

  ASSERT_EQ(this->people.Count(), local.Count());

  Person previous;
  previous.SetName("\0");
  local.ForEach([&](Person person)
  {
    ASSERT_TRUE(previous.GetName() <= person.GetName());
    previous = person;
  });

  local.Sort([](Person p1, Person p2) { return p1.GetAge() < p2.GetAge(); });

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
  QueryableList<Person> local = BuildQueryable(this->people.ToList());
  local.Sort();

  ASSERT_EQ(this->people.Count(), local.Count());

  Person previous;
  previous.SetName("\0");
  local.ForEach([&](Person person)
  {
    ASSERT_TRUE(previous.GetName() <= person.GetName());
    previous = person;
  });

  local.Sort([](Person p1, Person p2) { return p1.GetAge() < p2.GetAge(); });

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
  QueryableMultiSet<Person> local = BuildQueryable(this->people.ToMultiSet());
  local.Sort();

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
//   local.Sort([](Person p1, Person p2) { return p1.GetAge() < p2.GetAge(); });

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
  QueryableVector<Person> local = BuildQueryable(this->people.ToVector());
  local.Sort();

  ASSERT_EQ(this->people.Count(), local.Count());

  Person previous;
  previous.SetName("\0");
  local.ForEach([&](Person person)
  {
    ASSERT_TRUE(previous.GetName() <= person.GetName());
    previous = person;
  });

  local.Sort([](Person p1, Person p2) { return p1.GetAge() < p2.GetAge(); });

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
  QueryableVector<size_t> local = BuildQueryable(this->queryable.ToVector());

  local
    .Where([](size_t value) { return (value % 2) == 0; })
    .Sort();

    ASSERT_TRUE(this->queryable.Count() > local.Count());

    size_t previous = 0;
    local.ForEach([&](size_t value)
    {
      ASSERT_TRUE((value % 2) == 0);
      ASSERT_TRUE(previous <= value);
      previous = value;
    });
}
