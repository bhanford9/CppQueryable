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
  InternalQueryable<uint> queryable;
  InternalQueryable<Person> people;
  PersonLibrary personLibrary;

  void SetUp() override
  {
    this->queryable = BuildQueryable(std::vector<uint>({ 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 867, 1, 12 }));
    this->people = InternalQueryable<Person>(this->personLibrary.GetPeople());
  }

  void TearDown() override {}
};

TEST_F(SortFunctionalTest, SortUninitialized)
{
  InternalQueryable<Person> emptyQueryable;
  InternalQueryable<Person> & result = emptyQueryable.Sort();
  result.ToList();
}

TEST_F(SortFunctionalTest, DequeDefault)
{
  InternalQueryable<uint> local = BuildInternalQueryable<uint>(this->queryable.ToDeque());
  local.Sort();

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
  InternalQueryable<uint> local = BuildInternalQueryable<uint>(this->queryable.ToList());
  local.Sort();

  ASSERT_EQ(this->queryable.Count(), local.Count());

  uint previous = 0;
  local.ForEach([&](uint value)
  {
    ASSERT_TRUE(previous <= value);
    previous = value;
  });
}

TEST_F(SortFunctionalTest, MultiSetDefault)
{
  InternalQueryable<uint> local = BuildInternalQueryable<uint>(this->queryable.ToMultiSet());
  local.Sort();

  ASSERT_EQ(this->queryable.Count(), local.Count());

  uint previous = 0;
  local.ForEach([&](uint value)
  {
    ASSERT_TRUE(previous <= value);
    previous = value;
  });
}

TEST_F(SortFunctionalTest, DequeSet)
{
  InternalQueryable<uint> local = BuildInternalQueryable<uint>(this->queryable.ToSet());
  local.Sort();

  ASSERT_FALSE(this->queryable.Count() == local.Count());

  uint previous = 0;
  local.ForEach([&](uint value)
  {
    ASSERT_TRUE(previous <= value);
    previous = value;
  });
}

TEST_F(SortFunctionalTest, VectorDefault)
{
  InternalQueryable<uint> local = BuildInternalQueryable<uint>(this->queryable.ToVector());
  local.Sort();

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
  InternalQueryable<Person> local = BuildInternalQueryable<Person>(this->people.ToDeque());
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
  InternalQueryable<Person> local = BuildInternalQueryable<Person>(this->people.ToList());
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
  InternalQueryable<Person> local = BuildInternalQueryable<Person>(this->people.ToMultiSet());
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

TEST_F(SortFunctionalTest, SetClass)
{
  InternalQueryable<Person> local = BuildInternalQueryable<Person>(this->people.ToSet());
  local.Sort();

  ASSERT_TRUE(this->people.Count() == local.Count());

  Person previous;
  previous.SetName("\0");
  local.ForEach([&](Person person)
  {
    ASSERT_TRUE(previous.GetName() <= person.GetName());
    previous = person;
  });

  local.Sort([](Person p1, Person p2) { return p1.GetAge() < p2.GetAge(); });

  ASSERT_FALSE(this->people.Count() == local.Count());

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
  InternalQueryable<Person> local = BuildInternalQueryable<Person>(this->people.ToVector());
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
  InternalQueryable<uint> local = BuildInternalQueryable<uint>(this->queryable.ToVector());

  local
    .Where([](uint value) { return (value % 2) == 0; })
    .Sort();

    ASSERT_TRUE(this->queryable.Count() > local.Count());

    uint previous = 0;
    local.ForEach([&](uint value)
    {
      ASSERT_TRUE((value % 2) == 0);
      ASSERT_TRUE(previous <= value);
      previous = value;
    });
}
