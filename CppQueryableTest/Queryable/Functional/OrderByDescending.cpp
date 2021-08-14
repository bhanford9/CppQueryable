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
#include "../../../Queryable/QueryableVector.h"

using namespace QueryBuilder;

class OrderByDescendingFunctionalTest : public ::testing::Test
{
protected:
  QueryableVector<uint> queryable;
  QueryableVector<Person> people;
  PersonLibrary personLibrary;

  void SetUp() override
  {
    this->queryable = BuildQueryable(std::vector<uint>({ 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 867, 1, 12 }));
    this->people = QueryableVector<Person>(this->personLibrary.GetPeople());
  }

  void TearDown() override {}
};

TEST_F(OrderByDescendingFunctionalTest, OrderByDescendingUninitialized)
{
  QueryableVector<Person> emptyQueryable;
  Queryable<Person> * result = emptyQueryable.OrderByDescending();

  ASSERT_FALSE(result == NULL);
}

TEST_F(OrderByDescendingFunctionalTest, DequeDefault)
{
  QueryableDeque<uint> local = BuildQueryable<uint>(this->queryable.ToDeque());
  local.OrderByDescending();

  ASSERT_EQ(this->queryable.Count(), local.Count());

  uint previous = 999999;
  local.ForEach([&](uint value)
  {
    ASSERT_TRUE(previous >= value);
    previous = value;
  });
}

TEST_F(OrderByDescendingFunctionalTest, ListDefault)
{
  QueryableList<uint> local = BuildQueryable<uint>(this->queryable.ToList());
  local.OrderByDescending();

  ASSERT_EQ(this->queryable.Count(), local.Count());

  uint previous = 999999;
  local.ForEach([&](uint value)
  {
    ASSERT_TRUE(previous >= value);
    previous = value;
  });
}

TEST_F(OrderByDescendingFunctionalTest, MultiSetDefault)
{
  QueryableMultiSet<uint> local = BuildQueryable<uint>(this->queryable.ToMultiSet());
  local.OrderByDescending();

  ASSERT_EQ(this->queryable.Count(), local.Count());

  uint previous = 999999;
  local.ForEach([&](uint value)
  {
    ASSERT_TRUE(previous >= value);
    previous = value;
  });
}

TEST_F(OrderByDescendingFunctionalTest, DequeSet)
{
  QueryableSet<uint> local = BuildQueryable<uint>(this->queryable.ToSet());
  local.OrderByDescending();

  ASSERT_FALSE(this->queryable.Count() == local.Count());

  uint previous = 999999;
  local.ForEach([&](uint value)
  {
    ASSERT_TRUE(previous >= value);
    previous = value;
  });
}

TEST_F(OrderByDescendingFunctionalTest, VectorDefault)
{
  QueryableVector<uint> local = BuildQueryable<uint>(this->queryable.ToVector());
  local.OrderByDescending();

  ASSERT_EQ(this->queryable.Count(), local.Count());

  uint previous = 999999;
  local.ForEach([&](uint value)
  {
    ASSERT_TRUE(previous >= value);
    previous = value;
  });
}

TEST_F(OrderByDescendingFunctionalTest, DequeClass)
{
  QueryableDeque<Person> local = BuildQueryable<Person>(this->people.ToDeque());
  local.OrderByDescending();

  ASSERT_EQ(this->people.Count(), local.Count());

  Person previous;
  previous.SetName("~");
  local.ForEach([&](Person person)
  {
    ASSERT_TRUE(previous.GetName() >= person.GetName());
    previous = person;
  });

  local.OrderByDescending<double>([](Person p) { return p.GetAge(); });

  previous = Person();
  previous.SetAge(999999);
  local.ForEach([&](Person person)
  {
    ASSERT_TRUE(previous.GetAge() >= person.GetAge());
    previous = person;
  });
}

TEST_F(OrderByDescendingFunctionalTest, ListClass)
{
  QueryableList<Person> local = BuildQueryable<Person>(this->people.ToList());
  local.OrderByDescending();

  ASSERT_EQ(this->people.Count(), local.Count());

  Person previous;
  previous.SetName("~");
  local.ForEach([&](Person person)
  {
    ASSERT_TRUE(previous.GetName() >= person.GetName());
    previous = person;
  });

  local.OrderByDescending<double>([](Person p) { return p.GetAge(); });

  previous = Person();
  previous.SetAge(999999);
  local.ForEach([&](Person person)
  {
    ASSERT_TRUE(previous.GetAge() >= person.GetAge());
    previous = person;
  });
}

TEST_F(OrderByDescendingFunctionalTest, MultiSetClass)
{
  QueryableMultiSet<Person> local = BuildQueryable<Person>(this->people.ToMultiSet());
  local.OrderByDescending();

  ASSERT_EQ(this->people.Count(), local.Count());

  Person previous;
  previous.SetName("~");
  local.ForEach([&](Person person)
  {
    ASSERT_TRUE(previous.GetName() >= person.GetName());
    previous = person;
  });

  local.OrderByDescending<double>([](Person p) { return p.GetAge(); });

  previous = Person();
  previous.SetAge(999999);
  local.ForEach([&](Person person)
  {
    ASSERT_TRUE(previous.GetAge() >= person.GetAge());
    previous = person;
  });
}

TEST_F(OrderByDescendingFunctionalTest, SetClass)
{
  QueryableSet<Person> local = BuildQueryable<Person>(this->people.ToSet());
  local.OrderByDescending();

  ASSERT_TRUE(this->people.Count() == local.Count());

  Person previous;
  previous.SetName("~");
  local.ForEach([&](Person person)
  {
    ASSERT_TRUE(previous.GetName() >= person.GetName());
    previous = person;
  });

  local.OrderByDescending<double>([](Person p) { return p.GetAge(); });

  ASSERT_FALSE(this->people.Count() == local.Count());

  previous = Person();
  previous.SetAge(999999);
  local.ForEach([&](Person person)
  {
    ASSERT_TRUE(previous.GetAge() >= person.GetAge());
    previous = person;
  });
}

TEST_F(OrderByDescendingFunctionalTest, VectorClass)
{
  QueryableVector<Person> local = BuildQueryable<Person>(this->people.ToVector());
  local.OrderByDescending();

  ASSERT_EQ(this->people.Count(), local.Count());

  Person previous;
  previous.SetName("~");
  local.ForEach([&](Person person)
  {
    ASSERT_TRUE(previous.GetName() >= person.GetName());
    previous = person;
  });

  local.OrderByDescending<double>([](Person p) { return p.GetAge(); });

  previous = Person();
  previous.SetAge(999999);
  local.ForEach([&](Person person)
  {
    ASSERT_TRUE(previous.GetAge() >= person.GetAge());
    previous = person;
  });
}

TEST_F(OrderByDescendingFunctionalTest, WhereOrderByDescending)
{
  QueryableVector<uint> local = BuildQueryable<uint>(this->queryable.ToVector());

  local
    .Where([](uint value) { return (value % 2) == 0; })
    ->OrderByDescending();

    ASSERT_TRUE(this->queryable.Count() > local.Count());

    uint previous = 999999;
    local.ForEach([&](uint value)
    {
      ASSERT_TRUE((value % 2) == 0);
      ASSERT_TRUE(previous >= value);
      previous = value;
    });
}
