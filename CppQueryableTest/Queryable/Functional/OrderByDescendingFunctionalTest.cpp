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
  VectorQueryable<uint> queryable;
  VectorQueryable<Person> people;
  PersonLibrary personLibrary;

  void SetUp() override
  {
    this->queryable = BuildQueryable(std::vector<uint>({ 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 867, 1, 12 }));
    this->people = VectorQueryable<Person>(this->personLibrary.GetPeople());
  }

  void TearDown() override {}
};


TEST_F(OrderByDescendingFunctionalTest, OrderByDescendingUninitialized)
{
  VectorQueryable<Person> emptyQueryable;
  const VectorQueryable<Person> & result = emptyQueryable.OrderByDescending();
  result.ToList();
}

TEST_F(OrderByDescendingFunctionalTest, DequeDefault)
{
  DequeQueryable<uint> local = BuildQueryable<uint>(this->queryable.ToDeque());
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
  ListQueryable<uint> local = BuildQueryable<uint>(this->queryable.ToList());
  local.OrderByDescending();

  ASSERT_EQ(this->queryable.Count(), local.Count());

  uint previous = 999999;
  local.ForEach([&](uint value)
  {
    ASSERT_TRUE(previous >= value);
    previous = value;
  });
}

// TEST_F(OrderByDescendingFunctionalTest, MultiSetDefault)
// {
//   Queryable<uint> local = BuildQueryable<uint>(this->queryable.ToMultiSet());
//   local.OrderByDescending();
//
//   ASSERT_EQ(this->queryable.Count(), local.Count());
//
//   uint previous = 999999;
//   local.ForEach([&](uint value)
//   {
//     ASSERT_TRUE(previous >= value);
//     previous = value;
//   });
// }
//
// TEST_F(OrderByDescendingFunctionalTest, SetDefault)
// {
//   Queryable<uint> local = BuildQueryable<uint>(this->queryable.ToSet());
//   local.OrderByDescending();
//
//   ASSERT_FALSE(this->queryable.Count() == local.Count());
//
//   uint previous = 999999;
//   local.ForEach([&](uint value)
//   {
//     ASSERT_TRUE(previous >= value);
//     previous = value;
//   });
// }

TEST_F(OrderByDescendingFunctionalTest, VectorDefault)
{
  VectorQueryable<uint> local = BuildQueryable<uint>(this->queryable.ToVector());
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
  DequeQueryable<Person> local = BuildQueryable<Person>(this->people.ToDeque());
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
  ListQueryable<Person> local = BuildQueryable<Person>(this->people.ToList());
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

// TEST_F(OrderByDescendingFunctionalTest, MultiSetClass)
// {
//   Queryable<Person> local = BuildQueryable<Person>(this->people.ToMultiSet());
//   local.OrderByDescending();
//
//   ASSERT_EQ(this->people.Count(), local.Count());
//
//   Person previous;
//   previous.SetName("~");
//   local.ForEach([&](Person person)
//   {
//     ASSERT_TRUE(previous.GetName() >= person.GetName());
//     previous = person;
//   });
//
//   local.OrderByDescending<double>([](Person p) { return p.GetAge(); });
//
//   previous = Person();
//   previous.SetAge(999999);
//   local.ForEach([&](Person person)
//   {
//     ASSERT_TRUE(previous.GetAge() >= person.GetAge());
//     previous = person;
//   });
// }
//
// TEST_F(OrderByDescendingFunctionalTest, SetClass)
// {
//   Queryable<Person> local = BuildQueryable<Person>(this->people.ToSet());
//   local.OrderByDescending();
//
//   ASSERT_TRUE(this->people.Count() == local.Count());
//
//   Person previous;
//   previous.SetName("~");
//   local.ForEach([&](Person person)
//   {
//     ASSERT_TRUE(previous.GetName() >= person.GetName());
//     previous = person;
//   });
//
//   local.OrderByDescending<double>([](Person p) { return p.GetAge(); });
//
//   ASSERT_FALSE(this->people.Count() == local.Count());
//
//   previous = Person();
//   previous.SetAge(999999);
//   local.ForEach([&](Person person)
//   {
//     ASSERT_TRUE(previous.GetAge() >= person.GetAge());
//     previous = person;
//   });
// }

TEST_F(OrderByDescendingFunctionalTest, VectorClass)
{
  VectorQueryable<Person> local = BuildQueryable<Person>(this->people.ToVector());
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
  VectorQueryable<uint> local = BuildQueryable<uint>(this->queryable.ToVector());

  local
    .Where([](uint value) { return (value % 2) == 0; })
    .OrderByDescending();

    ASSERT_TRUE(this->queryable.Count() > local.Count());

    uint previous = 999999;
    local.ForEach([&](uint value)
    {
      std::cout << "value; " << value << std::endl;
      ASSERT_TRUE((value % 2) == 0);
      ASSERT_TRUE(previous >= value);
      previous = value;
    });
}
