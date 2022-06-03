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
  IQueryable<uint> queryable;
  PersonLibrary personLibrary;
  IQueryable<Person> people;

  SortFunctionalTest() :
    queryable(BuildQueryable2(std::vector<uint>({ 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 867, 1, 12 }))),
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
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToDeque());
  local = local.Sort<std::deque>();

  ASSERT_EQ(this->queryable.Count(), local.Count());

  uint previous = 0;
  local.ForEach([&](uint value)
  {
    ASSERT_TRUE(previous <= value);
    previous = value;
  });
}

TEST_F(SortFunctionalTest, ListDefault)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToList());
  local.Sort<std::list>();

  ASSERT_EQ(this->queryable.Count(), local.Count());

  uint previous = 0;
  local.ForEach([&](uint value)
  {
    ASSERT_TRUE(previous <= value);
    previous = value;
  });
}

TEST_F(SortFunctionalTest, VectorDefault)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToVector());
  local = local.Sort<std::vector>();

  ASSERT_EQ(this->queryable.Count(), local.Count());

  uint previous = 0;
  local.ForEach([&](uint value)
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
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToVector());

  local
    .Where([](uint value) { return (value % 2) == 0; })
    .Sort<std::vector>();

    ASSERT_TRUE(this->queryable.Count() > local.Count())
        << "\n\tQueryable Count: " << this->queryable.Count()
        << "\n\tLocal Count: " << local.Count()
        << std::endl;

    uint previous = 0;
    local.ForEach([&](uint value)
    {
      ASSERT_TRUE((value % 2) == 0);
      ASSERT_TRUE(previous <= value);
      previous = value;
    });
}
