#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <vector>

#include "../../../DataStructures/Gender.hpp"
#include "../../../DataStructures/Person.hpp"
#include "../../../DataStructures/PersonLibrary.hpp"

#include "../../../Queryable/QueryBuilder.hpp"


using namespace QueryBuilder;

class ContainsFunctionalTest : public ::testing::Test
{
protected:
  VectorQueryable<uint> queryable;

  void SetUp() override
  {
    this->queryable = BuildQueryable(std::vector<uint>({ 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 }));
  }

  void TearDown() override {}
};

TEST_F(ContainsFunctionalTest, ContainsUninitialized)
{
  VectorQueryable<uint> emptyQueryable;
  bool contains = emptyQueryable.Contains(12);
  ASSERT_FALSE(contains);
}

TEST_F(ContainsFunctionalTest, ContainsObjectCompare)
{
  VectorQueryable<Person> people = PersonLibrary().GetPeople();

  // Person equality is based off of the ID (first param)
  Person goodPerson(7, "Person 4", 51, 55, Gender::Female);
  Person badPerson(16, "Person 4", 51, 55, Gender::Female);
  ASSERT_TRUE(people.Contains(goodPerson));
  ASSERT_FALSE(people.Contains(badPerson));
}

TEST_F(ContainsFunctionalTest, DequeContains)
{
  int count = this->queryable.Count();
  DequeQueryable<uint> local = BuildQueryable(this->queryable.ToDeque());
  ASSERT_EQ(count, local.Count());
  ASSERT_TRUE(local.Contains(76));
  ASSERT_FALSE(local.Contains(99));
}

TEST_F(ContainsFunctionalTest, ListContains)
{
  int count = this->queryable.Count();
  ListQueryable<uint> local = BuildQueryable(this->queryable.ToList());
  ASSERT_EQ(count, local.Count());
  ASSERT_TRUE(local.Contains(76));
  ASSERT_FALSE(local.Contains(99));
}

TEST_F(ContainsFunctionalTest, MultiSetContains)
{
  int count = this->queryable.Count();
  MultiSetQueryable<uint> local = BuildQueryable(this->queryable.ToMultiSet());
  ASSERT_EQ(count, local.Count());
  ASSERT_TRUE(local.Contains(76));
  ASSERT_FALSE(local.Contains(99));
}

TEST_F(ContainsFunctionalTest, SetContains)
{
  int count = this->queryable.Count();
  SetQueryable<uint> local = BuildQueryable(this->queryable.ToSet());
  ASSERT_TRUE(count > local.Count());
  ASSERT_TRUE(local.Contains(76));
  ASSERT_FALSE(local.Contains(99));
}

TEST_F(ContainsFunctionalTest, VectorContains)
{
  int count = this->queryable.Count();
  VectorQueryable<uint> local = BuildQueryable(this->queryable.ToVector());
  ASSERT_EQ(count, local.Count());
  ASSERT_TRUE(local.Contains(76));
  ASSERT_FALSE(local.Contains(99));
}

TEST_F(ContainsFunctionalTest, WhereContains)
{
  // TODO --> figure out why WHERE cannot be done in succession
  // TODO --> figure out what is desired when WHERE is done is succession
  ASSERT_TRUE(this->queryable
    .Where([](uint value) { return value % 2 == 1; })
    .Contains(1));
  ASSERT_FALSE(this->queryable
    .Where([](uint value) { return value % 2 == 1; })
    .Contains(8));
}
