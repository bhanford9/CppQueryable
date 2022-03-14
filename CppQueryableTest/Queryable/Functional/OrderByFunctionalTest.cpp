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

class OrderByFunctionalTest : public ::testing::Test
{
protected:
  VectorInternalQueryable<uint> queryable;
  VectorInternalQueryable<Person> people;
  PersonLibrary personLibrary;

  void SetUp() override
  {
    this->queryable = BuildQueryable(std::vector<uint>({ 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 867, 1, 12 }));
    this->people = VectorInternalQueryable<Person>(this->personLibrary.GetPeople());
  }

  void TearDown() override {}
};

TEST_F(OrderByFunctionalTest, OrderByUninitialized)
{
  VectorInternalQueryable<Person> emptyQueryable;
  VectorInternalQueryable<Person> result = emptyQueryable.OrderBy();
  result.ToList();
}

TEST_F(OrderByFunctionalTest, DequeDefault)
{
  DequeInternalQueryable<uint> local = BuildInternalQueryable<uint>(this->queryable.ToDeque());
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
  ListInternalQueryable<uint> local = BuildInternalQueryable<uint>(this->queryable.ToList());
  local.OrderBy();

  ASSERT_EQ(this->queryable.Count(), local.Count());

  uint previous = 0;
  local.ForEach([&](uint value)
  {
    ASSERT_TRUE(previous <= value);
    previous = value;
  });
}

// TEST_F(OrderByFunctionalTest, MultiSetDefault)
// {
//   InternalQueryable<uint> local = BuildInternalQueryable<uint>(this->queryable.ToMultiSet());
//   local.OrderBy();
//
//   ASSERT_EQ(this->queryable.Count(), local.Count());
//
//   uint previous = 0;
//   local.ForEach([&](uint value)
//   {
//     ASSERT_TRUE(previous <= value);
//     previous = value;
//   });
// }
//
// TEST_F(OrderByFunctionalTest, SetDefault)
// {
//   InternalQueryable<uint> local = BuildInternalQueryable<uint>(this->queryable.ToSet());
//   local.OrderBy();
//
//   ASSERT_FALSE(this->queryable.Count() == local.Count());
//
//   uint previous = 0;
//   local.ForEach([&](uint value)
//   {
//     ASSERT_TRUE(previous <= value);
//     previous = value;
//   });
// }

TEST_F(OrderByFunctionalTest, VectorDefault)
{
  VectorInternalQueryable<uint> local = BuildInternalQueryable<uint>(this->queryable.ToVector());
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
  DequeInternalQueryable<Person> local = BuildInternalQueryable<Person>(this->people.ToDeque());
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
  ListInternalQueryable<Person> local = BuildInternalQueryable<Person>(this->people.ToList());
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

// TEST_F(OrderByFunctionalTest, MultiSetClass)
// {
//   InternalQueryable<Person> local = BuildInternalQueryable<Person>(this->people.ToMultiSet());
//   local.OrderBy();
//
//   ASSERT_EQ(this->people.Count(), local.Count());
//
//   Person previous;
//   previous.SetName("\0");
//   local.ForEach([&](Person person)
//   {
//     ASSERT_TRUE(previous.GetName() <= person.GetName());
//     previous = person;
//   });
//
//   local.OrderBy<double>([](Person p) { return p.GetAge(); });
//
//   previous = Person();
//   previous.SetAge(-1);
//   local.ForEach([&](Person person)
//   {
//     ASSERT_TRUE(previous.GetAge() <= person.GetAge());
//     previous = person;
//   });
// }
//
// TEST_F(OrderByFunctionalTest, SetClass)
// {
//   InternalQueryable<Person> local = BuildInternalQueryable<Person>(this->people.ToSet());
//   local.OrderBy();
//
//   ASSERT_TRUE(this->people.Count() == local.Count());
//
//   Person previous;
//   previous.SetName("\0");
//   local.ForEach([&](Person person)
//   {
//     ASSERT_TRUE(previous.GetName() <= person.GetName());
//     previous = person;
//   });
//
//   local.OrderBy<double>([](Person p) { return p.GetAge(); });
//
//   ASSERT_FALSE(this->people.Count() == local.Count());
//
//   previous = Person();
//   previous.SetAge(-1);
//   local.ForEach([&](Person person)
//   {
//     ASSERT_TRUE(previous.GetAge() <= person.GetAge());
//     previous = person;
//   });
// }

TEST_F(OrderByFunctionalTest, VectorClass)
{
  VectorInternalQueryable<Person> local = BuildInternalQueryable<Person>(this->people.ToVector());
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
  VectorInternalQueryable<uint> local = BuildInternalQueryable<uint>(this->queryable.ToVector());

  local
    .Where([](uint value) { return (value % 2) == 0; })
    .OrderBy();

    ASSERT_TRUE(this->queryable.Count() > local.Count());

    uint previous = 0;
    local.ForEach([&](uint value)
    {
      ASSERT_TRUE((value % 2) == 0);
      ASSERT_TRUE(previous <= value);
      previous = value;
    });
}
