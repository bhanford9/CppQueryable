#include <gtest/gtest.h>

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
    queryable(BuildQueryable(std::vector<size_t>({ 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 })))
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
  const QueryableVector<Person> people = BuildQueryable(PersonLibrary().GetPeople());

  // Person equality is based off of the ID (first param)
  const Person goodPerson(7, "Person 4", 51, 55, Gender::Female);
  const Person badPerson(16, "Person 4", 51, 55, Gender::Female);
  ASSERT_TRUE(people.Contains(goodPerson));
  ASSERT_FALSE(people.Contains(badPerson));
}

TEST_F(ContainsFunctionalTest, DequeContains)
{
  const size_t count = this->queryable.Count();
  QueryableDeque<size_t> local = BuildQueryable(this->queryable.ToDeque());
  ASSERT_EQ(count, local.Count());
  ASSERT_TRUE(local.Contains(76));
  ASSERT_FALSE(local.Contains(99));
}

TEST_F(ContainsFunctionalTest, ListContains)
{
  const size_t count = this->queryable.Count();
  QueryableList<size_t> local = BuildQueryable(this->queryable.ToList());
  ASSERT_EQ(count, local.Count());
  ASSERT_TRUE(local.Contains(76));
  ASSERT_FALSE(local.Contains(99));
}

TEST_F(ContainsFunctionalTest, MapContains)
{
  const size_t count = this->queryable.Count();
  QueryableMap<size_t, std::string> local = BuildQueryable(
    this->queryable.ToMap<size_t, std::string>(
      [](size_t value) { return value; },
      [](size_t value) { return std::to_string(value / 2.0); }));
  ASSERT_GT(count, local.Count());
  ASSERT_TRUE(local.Contains(local.First([](std::pair<const size_t, std::string> kvp) { return kvp.first == 76; })));
  ASSERT_FALSE(local.Contains(std::pair<const size_t, std::string>(76, "38")));
}

TEST_F(ContainsFunctionalTest, MultiSetContains)
{
  const size_t count = this->queryable.Count();
  QueryableMultiSet<size_t> local = BuildQueryable(this->queryable.ToMultiSet());
  ASSERT_EQ(count, local.Count());
  ASSERT_TRUE(local.Contains(76));
  ASSERT_FALSE(local.Contains(99));
}

TEST_F(ContainsFunctionalTest, SetContains)
{
  const size_t count = this->queryable.Count();
  QueryableSet<size_t> local = BuildQueryable(this->queryable.ToSet());
  ASSERT_GT(count, local.Count());
  ASSERT_TRUE(local.Contains(76));
  ASSERT_FALSE(local.Contains(99));
}

TEST_F(ContainsFunctionalTest, VectorContains)
{
  const size_t count = this->queryable.Count();
  QueryableVector<size_t> local = BuildQueryable(this->queryable.ToVector());
  ASSERT_EQ(count, local.Count());
  ASSERT_TRUE(local.Contains(76));
  ASSERT_FALSE(local.Contains(99));
}

TEST_F(ContainsFunctionalTest, WhereContains)
{
  ASSERT_TRUE(this->queryable
    .Where([](size_t value) { return value % 2 == 1; })
    .Contains(1));
  ASSERT_FALSE(this->queryable
    .Where([](size_t value) { return value % 2 == 1; })
    .Contains(8));
}
