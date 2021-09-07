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
#include "../../../DataStructures/Point.h"

#include "../../../Queryable/QueryBuilder.h"


using namespace QueryBuilder;

class SortFunctionalTest : public ::testing::Test
{
protected:
  Queryable<uint> queryable;
  Queryable<Person> people;
  PersonLibrary personLibrary;

  void SetUp() override
  {
    this->queryable = BuildQueryable(std::vector<uint>({ 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 867, 1, 12 }));
    this->people = Queryable<Person>(this->personLibrary.GetPeople());
  }

  void TearDown() override {}
};

TEST_F(SortFunctionalTest, SortUninitialized)
{
  Queryable<Person> emptyQueryable;
  Queryable<Person> & result = emptyQueryable.Sort();
  result.ToList();
}

TEST_F(SortFunctionalTest, DequeDefault)
{
  Queryable<uint> local = BuildQueryable<uint>(this->queryable.ToDeque());
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
  Queryable<uint> local = BuildQueryable<uint>(this->queryable.ToList());
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
  Queryable<uint> local = BuildQueryable<uint>(this->queryable.ToMultiSet());
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
  Queryable<uint> local = BuildQueryable<uint>(this->queryable.ToSet());
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
  Queryable<uint> local = BuildQueryable<uint>(this->queryable.ToVector());
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
  Queryable<Person> local = BuildQueryable<Person>(this->people.ToDeque());
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
  Queryable<Person> local = BuildQueryable<Person>(this->people.ToList());
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
  Queryable<Person> local = BuildQueryable<Person>(this->people.ToMultiSet());
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
  Queryable<Person> local = BuildQueryable<Person>(this->people.ToSet());
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
  Queryable<Person> local = BuildQueryable<Person>(this->people.ToVector());
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
  Queryable<uint> local = BuildQueryable<uint>(this->queryable.ToVector());

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
