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

#include "../../../Queryable/QueryBuilder.h"


using namespace QueryBuilder;

class ContainsFunctionalTest : public ::testing::Test
{
protected:
  Queryable<uint> queryable;

  void SetUp() override
  {
    this->queryable = BuildQueryable(std::vector<uint>({ 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 }));
  }

  void TearDown() override {}
};

TEST_F(ContainsFunctionalTest, ContainsUninitialized)
{
  Queryable<uint> emptyQueryable;
  bool contains = emptyQueryable.Contains(12);
  ASSERT_FALSE(contains);
}

TEST_F(ContainsFunctionalTest, ContainsObjectCompare)
{
  Queryable<Person> people = PersonLibrary().GetPeople();

  // Person equality is based off of the ID (first param)
  Person goodPerson(7, "Person 4", 51, 55, Gender::Female);
  Person badPerson(16, "Person 4", 51, 55, Gender::Female);
  ASSERT_TRUE(people.Contains(goodPerson));
  ASSERT_FALSE(people.Contains(badPerson));
}

TEST_F(ContainsFunctionalTest, DequeContains)
{
  int count = this->queryable.Count();
  Queryable<uint>* local = this->queryable.ToQueryableDeque();
  ASSERT_EQ(count, local->Count());
  ASSERT_TRUE(local->Contains(76));
  ASSERT_FALSE(local->Contains(99));
}

TEST_F(ContainsFunctionalTest, ListContains)
{
  int count = this->queryable.Count();
  Queryable<uint>* local = this->queryable.ToQueryableList();
  ASSERT_EQ(count, local->Count());
  ASSERT_TRUE(local->Contains(76));
  ASSERT_FALSE(local->Contains(99));
}

TEST_F(ContainsFunctionalTest, MultiSetContains)
{
  int count = this->queryable.Count();
  Queryable<uint>* local = this->queryable.ToQueryableMultiSet();
  ASSERT_EQ(count, local->Count());
  ASSERT_TRUE(local->Contains(76));
  ASSERT_FALSE(local->Contains(99));
}

TEST_F(ContainsFunctionalTest, SetContains)
{
  int count = this->queryable.Count();
  Queryable<uint>* local = this->queryable.ToQueryableSet();
  ASSERT_TRUE(count > local->Count());
  ASSERT_TRUE(local->Contains(76));
  ASSERT_FALSE(local->Contains(99));
}

TEST_F(ContainsFunctionalTest, VectorContains)
{
  int count = this->queryable.Count();
  Queryable<uint>* local = this->queryable.ToQueryableVector();
  ASSERT_EQ(count, local->Count());
  ASSERT_TRUE(local->Contains(76));
  ASSERT_FALSE(local->Contains(99));
}

TEST_F(ContainsFunctionalTest, WhereContains)
{
  ASSERT_TRUE(this->queryable
    .WhereCopy([](uint value) { return value % 2 == 1; })
    .Contains(1));
  ASSERT_FALSE(this->queryable
    .WhereCopy([](uint value) { return value % 2 == 1; })
    .Contains(8));
}
// where -> contains