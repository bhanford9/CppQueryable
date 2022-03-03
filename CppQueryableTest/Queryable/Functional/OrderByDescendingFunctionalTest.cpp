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

class OrderByDescendingFunctionalTest : public ::testing::Test
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

TEST_F(OrderByDescendingFunctionalTest, OrderByDescendingUninitialized)
{
  Queryable<Person> emptyQueryable;
  Queryable<Person> & result = emptyQueryable.OrderByDescending();
  result.ToList();
}

TEST_F(OrderByDescendingFunctionalTest, DequeDefault)
{
  Queryable<uint> local = BuildQueryable<uint>(this->queryable.ToDeque());
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
  Queryable<uint> local = BuildQueryable<uint>(this->queryable.ToList());
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
  Queryable<uint> local = BuildQueryable<uint>(this->queryable.ToMultiSet());
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
  Queryable<uint> local = BuildQueryable<uint>(this->queryable.ToSet());
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
  Queryable<uint> local = BuildQueryable<uint>(this->queryable.ToVector());
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
  Queryable<Person> local = BuildQueryable<Person>(this->people.ToDeque());
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
  Queryable<Person> local = BuildQueryable<Person>(this->people.ToList());
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
  Queryable<Person> local = BuildQueryable<Person>(this->people.ToMultiSet());
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
  Queryable<Person> local = BuildQueryable<Person>(this->people.ToSet());
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
  Queryable<Person> local = BuildQueryable<Person>(this->people.ToVector());
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
  Queryable<uint> local = BuildQueryable<uint>(this->queryable.ToVector());

  local
    .Where([](uint value) { return (value % 2) == 0; })
    .OrderByDescending();

    ASSERT_TRUE(this->queryable.Count() > local.Count());

    uint previous = 999999;
    local.ForEach([&](uint value)
    {
      ASSERT_TRUE((value % 2) == 0);
      ASSERT_TRUE(previous >= value);
      previous = value;
    });
}
