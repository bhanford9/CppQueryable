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
  QueryableVector<size_t> queryable;

  ContainsFunctionalTest() :
    queryable(BuildQueryable2(std::vector<size_t>({ 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 })))
  {
  }

  void SetUp() override
  {
  }

  void TearDown() override {}
};

// TEST_F(ContainsFunctionalTest, ContainsUninitialized)
// {
//   IQueryable<size_t> emptyQueryable;
//   bool contains = emptyQueryable.Contains(12);
//   ASSERT_FALSE(contains);
// }

TEST_F(ContainsFunctionalTest, ContainsObjectCompare)
{
  QueryableVector<Person> people = BuildQueryable2(PersonLibrary().GetPeople());

  // Person equality is based off of the ID (first param)
  Person goodPerson(7, "Person 4", 51, 55, Gender::Female);
  Person badPerson(16, "Person 4", 51, 55, Gender::Female);
  ASSERT_TRUE(people.Contains(goodPerson));
  ASSERT_FALSE(people.Contains(badPerson));
}

TEST_F(ContainsFunctionalTest, DequeContains)
{
  size_t count = this->queryable.Count();
  QueryableDeque<size_t> local = BuildQueryable2(this->queryable.ToDeque());
  ASSERT_EQ(count, local.Count());
  ASSERT_TRUE(local.Contains(76));
  ASSERT_FALSE(local.Contains(99));
}

TEST_F(ContainsFunctionalTest, ListContains)
{
  size_t count = this->queryable.Count();
  QueryableList<size_t> local = BuildQueryable2(this->queryable.ToList());
  ASSERT_EQ(count, local.Count());
  ASSERT_TRUE(local.Contains(76));
  ASSERT_FALSE(local.Contains(99));
}

TEST_F(ContainsFunctionalTest, MultiSetContains)
{
  size_t count = this->queryable.Count();
  QueryableMultiSet<size_t> local = BuildQueryable2(this->queryable.ToMultiSet());
  ASSERT_EQ(count, local.Count());
  ASSERT_TRUE(local.Contains(76));
  ASSERT_FALSE(local.Contains(99));
}

TEST_F(ContainsFunctionalTest, SetContains)
{
  size_t count = this->queryable.Count();
  QueryableSet<size_t> local = BuildQueryable2(this->queryable.ToSet());
  ASSERT_TRUE(count > local.Count());
  ASSERT_TRUE(local.Contains(76));
  ASSERT_FALSE(local.Contains(99));
}

TEST_F(ContainsFunctionalTest, VectorContains)
{
  size_t count = this->queryable.Count();
  QueryableVector<size_t> local = BuildQueryable2(this->queryable.ToVector());
  ASSERT_EQ(count, local.Count());
  ASSERT_TRUE(local.Contains(76));
  ASSERT_FALSE(local.Contains(99));
}

TEST_F(ContainsFunctionalTest, WhereContains)
{
  // TODO --> figure out why WHERE cannot be done in succession
  // TODO --> figure out what is desired when WHERE is done is succession
  ASSERT_TRUE(this->queryable
    .Where([](size_t value) { return value % 2 == 1; })
    .Contains(1));
  // ASSERT_FALSE(this->queryable
  //   .Where([](size_t value) { return value % 2 == 1; })
  //   .Contains(8));
}
