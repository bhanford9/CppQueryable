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

class OrderByFunctionalTest : public ::testing::Test
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

TEST_F(OrderByFunctionalTest, OrderByUninitialized)
{
  QueryableVector<Person> emptyQueryable;
  Queryable<Person> * result = emptyQueryable.OrderBy();

  ASSERT_FALSE(result == NULL);
}

TEST_F(OrderByFunctionalTest, DequeDefault)
{
  QueryableDeque<uint> local = BuildQueryable<uint>(this->queryable.ToDeque());
  local.OrderBy();

  ASSERT_EQ(this->queryable.Count(), local.Count());

  uint previous = 0;
  local.ForEach([&](uint value)
  {
    ASSERT_TRUE(previous <= value);
    previous = value;
  });
}

TEST_F(OrderByFunctionalTest, ListDefault)
{
  QueryableList<uint> local = BuildQueryable<uint>(this->queryable.ToList());
  local.OrderBy();

  ASSERT_EQ(this->queryable.Count(), local.Count());

  uint previous = 0;
  local.ForEach([&](uint value)
  {
    ASSERT_TRUE(previous <= value);
    previous = value;
  });
}

TEST_F(OrderByFunctionalTest, MultiSetDefault)
{
  QueryableMultiSet<uint> local = BuildQueryable<uint>(this->queryable.ToMultiSet());
  local.OrderBy();

  ASSERT_EQ(this->queryable.Count(), local.Count());

  uint previous = 0;
  local.ForEach([&](uint value)
  {
    ASSERT_TRUE(previous <= value);
    previous = value;
  });
}

TEST_F(OrderByFunctionalTest, DequeSet)
{
  QueryableSet<uint> local = BuildQueryable<uint>(this->queryable.ToSet());
  local.OrderBy();

  ASSERT_FALSE(this->queryable.Count() == local.Count());

  uint previous = 0;
  local.ForEach([&](uint value)
  {
    ASSERT_TRUE(previous <= value);
    previous = value;
  });
}

TEST_F(OrderByFunctionalTest, VectorDefault)
{
  QueryableVector<uint> local = BuildQueryable<uint>(this->queryable.ToVector());
  local.OrderBy();

  ASSERT_EQ(this->queryable.Count(), local.Count());

  uint previous = 0;
  local.ForEach([&](uint value)
  {
    ASSERT_TRUE(previous <= value);
    previous = value;
  });
}

TEST_F(OrderByFunctionalTest, DequeClass)
{
  QueryableDeque<Person> local = BuildQueryable<Person>(this->people.ToDeque());
  local.OrderBy();

  ASSERT_EQ(this->people.Count(), local.Count());

  Person previous;
  previous.SetName("\0");
  local.ForEach([&](Person person)
  {
    ASSERT_TRUE(previous.GetName() <= person.GetName());
    previous = person;
  });

  local.OrderBy<double>([](Person p) { return p.GetAge(); });

  previous = Person();
  previous.SetAge(-1);
  local.ForEach([&](Person person)
  {
    ASSERT_TRUE(previous.GetAge() <= person.GetAge());
    previous = person;
  });
}

TEST_F(OrderByFunctionalTest, ListClass)
{
  QueryableList<Person> local = BuildQueryable<Person>(this->people.ToList());
  local.OrderBy();

  ASSERT_EQ(this->people.Count(), local.Count());

  Person previous;
  previous.SetName("\0");
  local.ForEach([&](Person person)
  {
    ASSERT_TRUE(previous.GetName() <= person.GetName());
    previous = person;
  });

  local.OrderBy<double>([](Person p) { return p.GetAge(); });

  previous = Person();
  previous.SetAge(-1);
  local.ForEach([&](Person person)
  {
    ASSERT_TRUE(previous.GetAge() <= person.GetAge());
    previous = person;
  });
}

TEST_F(OrderByFunctionalTest, MultiSetClass)
{
  QueryableMultiSet<Person> local = BuildQueryable<Person>(this->people.ToMultiSet());
  local.OrderBy();

  ASSERT_EQ(this->people.Count(), local.Count());

  Person previous;
  previous.SetName("\0");
  local.ForEach([&](Person person)
  {
    ASSERT_TRUE(previous.GetName() <= person.GetName());
    previous = person;
  });

  local.OrderBy<double>([](Person p) { return p.GetAge(); });

  previous = Person();
  previous.SetAge(-1);
  local.ForEach([&](Person person)
  {
    ASSERT_TRUE(previous.GetAge() <= person.GetAge());
    previous = person;
  });
}

TEST_F(OrderByFunctionalTest, SetClass)
{
  QueryableSet<Person> local = BuildQueryable<Person>(this->people.ToSet());
  local.OrderBy();

  ASSERT_TRUE(this->people.Count() == local.Count());

  Person previous;
  previous.SetName("\0");
  local.ForEach([&](Person person)
  {
    ASSERT_TRUE(previous.GetName() <= person.GetName());
    previous = person;
  });

  local.OrderBy<double>([](Person p) { return p.GetAge(); });

  ASSERT_FALSE(this->people.Count() == local.Count());

  previous = Person();
  previous.SetAge(-1);
  local.ForEach([&](Person person)
  {
    ASSERT_TRUE(previous.GetAge() <= person.GetAge());
    previous = person;
  });
}

TEST_F(OrderByFunctionalTest, VectorClass)
{
  QueryableVector<Person> local = BuildQueryable<Person>(this->people.ToVector());
  local.OrderBy();

  ASSERT_EQ(this->people.Count(), local.Count());

  Person previous;
  previous.SetName("\0");
  local.ForEach([&](Person person)
  {
    ASSERT_TRUE(previous.GetName() <= person.GetName());
    previous = person;
  });

  local.OrderBy<double>([](Person p) { return p.GetAge(); });

  previous = Person();
  previous.SetAge(-1);
  local.ForEach([&](Person person)
  {
    ASSERT_TRUE(previous.GetAge() <= person.GetAge());
    previous = person;
  });
}

TEST_F(OrderByFunctionalTest, WhereOrderBy)
{
  QueryableVector<uint> local = BuildQueryable<uint>(this->queryable.ToVector());

  local
    .Where([](uint value) { return (value % 2) == 0; })
    ->OrderBy();

    ASSERT_TRUE(this->queryable.Count() > local.Count());

    uint previous = 0;
    local.ForEach([&](uint value)
    {
      ASSERT_TRUE((value % 2) == 0);
      ASSERT_TRUE(previous <= value);
      previous = value;
    });
}
