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
#include "../../../Queryable/Queryable.hpp"


using namespace QueryBuilder;

class OrderByDescendingFunctionalTest : public ::testing::Test
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


// TEST_F(OrderByDescendingFunctionalTest, OrderByDescendingUninitialized)
// {
//   VectorInternalQueryable<Person> emptyQueryable;
//   VectorInternalQueryable<Person> result = emptyQueryable.OrderByDescending();
//   result.ToList();
// }
//
TEST_F(OrderByDescendingFunctionalTest, DequeDefault)
{
  DequeInternalQueryable<uint> local = BuildQueryable<uint>(this->queryable.ToDeque());
  Queryable<uint, std::deque> queryableDeque(local);
  queryableDeque.Sort([](uint a, uint b) { return a > b; });

  ASSERT_EQ(this->queryable.Count(), local.Count());

  uint previous = 999999;
  queryableDeque.ForEach([&](uint value)
  {
    ASSERT_TRUE(previous >= value);
    previous = value;
  });
}
TEST_F(OrderByDescendingFunctionalTest, VectorDefault)
{
  VectorInternalQueryable<uint> local = BuildQueryable<uint>(this->queryable.ToVector());
  Queryable<uint, std::deque> queryableVector(local);
  queryableVector.Sort([](uint a, uint b) { return a > b; });

  ASSERT_EQ(this->queryable.Count(), local.Count());

  uint previous = 999999;
  queryableVector.ForEach([&](uint value)
  {
    ASSERT_TRUE(previous >= value);
    previous = value;
  });
}
//
// TEST_F(OrderByDescendingFunctionalTest, ListDefault)
// {
//   ListInternalQueryable<uint> local = BuildQueryable<uint>(this->queryable.ToList());
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

// TEST_F(OrderByDescendingFunctionalTest, MultiSetDefault)
// {
//
//   MultiSetInternalQueryable<uint> qSetItems(std::move(this->queryable.ToMultiSet()));
//   Queryable<uint, std::multiset> local(reinterpret_cast<InternalQueryable<uint, std::multiset>*>(&qSetItems));
//   // Queryable<uint, std::multiset> local(BuildQueryable<uint>(this->queryable.ToMultiSet()));
//   Queryable<uint, std::multiset, std::less<uint>, std::allocator<uint>> orderedQueryable =
//     local.OrderByDescending<std::less<uint>>(std::less<uint>{});
//
//   // ASSERT_EQ(this->queryable.Count(), local.Count());
//
//   uint previous = 999999;
//   local.ForEach([&](uint value)
//   {
//     ASSERT_TRUE(previous >= value);
//     previous = value;
//   });
// }

// TEST_F(OrderByDescendingFunctionalTest, SetDefault)
// {
//   InternalQueryable<uint> local = BuildQueryable<uint>(this->queryable.ToSet());
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

// TEST_F(OrderByDescendingFunctionalTest, VectorDefault)
// {
//   VectorInternalQueryable<uint> local = BuildQueryable<uint>(this->queryable.ToVector());
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
// TEST_F(OrderByDescendingFunctionalTest, DequeClass)
// {
//   DequeInternalQueryable<Person> local = BuildQueryable<Person>(this->people.ToDeque());
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
// TEST_F(OrderByDescendingFunctionalTest, ListClass)
// {
//   ListInternalQueryable<Person> local = BuildQueryable<Person>(this->people.ToList());
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

// TEST_F(OrderByDescendingFunctionalTest, MultiSetClass)
// {
//   InternalQueryable<Person> local = BuildQueryable<Person>(this->people.ToMultiSet());
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

// TEST_F(OrderByDescendingFunctionalTest, SetClass)
// {
//   SetInternalQueryable<Person> local = BuildQueryable<Person>(this->people.ToSet());
//   local.ReOrderByDescending();
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
//   local.ReOrderByDescending<double>([](Person p) { return p.GetAge(); });
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

// TEST_F(OrderByDescendingFunctionalTest, VectorClass)
// {
//   VectorInternalQueryable<Person> local = BuildQueryable<Person>(this->people.ToVector());
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
// TEST_F(OrderByDescendingFunctionalTest, WhereOrderByDescending)
// {
//   VectorInternalQueryable<uint> local = BuildQueryable<uint>(this->queryable.ToVector());
//
//   local
//     .Where([](uint value) { return (value % 2) == 0; })
//     .OrderByDescending();
//
//     ASSERT_TRUE(this->queryable.Count() > local.Count());
//
//     uint previous = 999999;
//     local.ForEach([&](uint value)
//     {
//       ASSERT_TRUE((value % 2) == 0);
//       ASSERT_TRUE(previous >= value);
//       previous = value;
//     });
// }
