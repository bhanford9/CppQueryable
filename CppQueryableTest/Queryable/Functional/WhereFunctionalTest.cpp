#include <gtest/gtest.h>

#include <array>
#include <deque>
#include <iostream>
#include <list>
#include <set>
#include <string>
#include <vector>

#include "../../../DataStructures/Gender.hpp"
#include "../../../DataStructures/Person.hpp"
#include "../../../DataStructures/PersonLibrary.hpp"

#include "../../../Queryable/QueryBuilder.hpp"


using namespace QueryBuilder;

class WhereFunctionalTest : public ::testing::Test
{
protected:
  QueryableVector<Person> queryable;

  WhereFunctionalTest() :
    queryable(BuildQueryable(PersonLibrary().GetPeople()))
  {
  }

  void SetUp() override
  {
  }

  void TearDown() override {}
};

// TODO --> fix this
// TEST_F(WhereFunctionalTest, WhereVectorUninitializedTest)
// {
//   IQueryable<Person> emptyQueryable;

//   emptyQueryable.Where([](Person p) { return false; });

//   ASSERT_TRUE(true);
// }

TEST_F(WhereFunctionalTest, WhereVectorEvenTest)
{
  QueryableVector<int> localQueryable(BuildQueryable(std::vector<int>({ 4, 7, 4, 3, 76, 8, 45, 867, 76, 0 })));
  std::vector<int> expected({ 4, 4, 76, 8, 76, 0 });

  std::vector<int> values = localQueryable
    .Where([](int x) { return (x % 2) == 0; })
    .ToVector();

  ASSERT_EQ(expected.size(), values.size());
  for (int i = 0; i < (int)expected.size(); i++)
    ASSERT_EQ(expected[i], values[i]);
}

// TODO --> fix
// TEST_F(WhereFunctionalTest, WhereVectorSevenEightNineTest)
// {
//   std::vector<Person> expected(
//   {
//     Person(0, "Person 7", 0, 0, Gender::Male),
//     Person(0, "Person 8", 0, 0, Gender::Male),
//     Person(0, "Person 9", 0, 0, Gender::Male),
//   });

//   std::vector<Person> people = this->queryable
//     .Where([](Person p) { return p.GetName() >= "Person 7" && p.GetName() <= "Person 9"; })
//     .OrderBy<std::string>([](Person p) { return p.GetName(); })
//     .ToVector();

//   ASSERT_EQ(expected.size(), people.size());
//   for (int i = 0; i < (int)expected.size(); i++)
//     ASSERT_STREQ(expected[i].GetName().c_str(), people[i].GetName().c_str());
// }

TEST_F(WhereFunctionalTest, WhereVectorFemale)
{
  std::vector<Person> people = this->queryable
    .Where([](Person p) { return p.GetGender() == Gender::Female; })
    .ToVector();

  for (Person p : people)
    EXPECT_TRUE(p.GetGender() == Gender::Female);
}

TEST_F(WhereFunctionalTest, WhereSetFemale)
{
  using TCompare = std::function<bool(Person, Person)>;
  std::set<Person, TCompare> people =
    BuildQueryable(this->queryable.ToSet<TCompare>([](Person a, Person b) { return a < b; }))
      .Where([](Person p) { return p.GetGender() == Gender::Female; })
      .ToSet<TCompare>([](Person a, Person b) { return a < b; });

  for (Person p : people)
    ASSERT_TRUE(p.GetGender() == Gender::Female);
}

TEST_F(WhereFunctionalTest, WhereMapSetFemale)
{
  std::map<std::string, Gender> kvps = BuildQueryable(
    this->queryable.ToMap<std::string, Gender>(
      [](Person p) { return p.GetName(); },
      [](Person p) { return p.GetGender(); }))
    .Where([](std::pair<const std::string, Gender> kvp) { return kvp.second == Gender::Female; })
    .ToMap<std::string, Gender>(
      [](std::pair<const std::string, Gender> kvp) { return kvp.first; },
      [](std::pair<const std::string, Gender> kvp) { return kvp.second; });

  for (std::pair<const std::string, Gender> kvp : kvps)
  {
    ASSERT_TRUE(kvp.second == Gender::Female);
  }
}

TEST_F(WhereFunctionalTest, WhereMultiSetFemale)
{
  using TCompare = std::function<bool(Person, Person)>;
  std::multiset<Person, TCompare> people = BuildQueryable(this->queryable.ToMultiSet<TCompare>([](Person a, Person b) { return a < b; }))
    .Where([](Person p) { return p.GetGender() == Gender::Female; })
    .ToMultiSet<TCompare>([](Person a, Person b) { return a < b; });

  for (Person p : people)
    ASSERT_TRUE(p.GetGender() == Gender::Female);
}

TEST_F(WhereFunctionalTest, WhereDequeFemale)
{
  std::deque<Person> people = BuildQueryable(this->queryable.ToDeque())
    .Where([](Person p) { return p.GetGender() == Gender::Female; })
    .ToDeque();

  for (Person p : people)
    EXPECT_TRUE(p.GetGender() == Gender::Female) << p;
}

TEST_F(WhereFunctionalTest, WhereListFemale)
{
  std::list<Person> people = BuildQueryable(this->queryable.ToList())
    .Where([](Person p) { return p.GetGender() == Gender::Female; })
    .ToList();

  for (Person p : people)
    ASSERT_TRUE(p.GetGender() == Gender::Female);
}
