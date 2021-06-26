#include <gtest/gtest.h>

#include <array>
#include <deque>
#include <iostream>
#include <list>
#include <set>
#include <string>
#include <vector>

#include "../../../DataStructures/Gender.h"
#include "../../../DataStructures/Person.h"
#include "../../../DataStructures/PersonLibrary.h"

#include "../../../Queryable/Queryable.h"

class WhereFunctionalTest : public ::testing::Test
{
protected:
  Queryable<Person, std::vector> queryable;

  void SetUp() override
  {
    this->queryable = Queryable<Person, std::vector>(PersonLibrary().GetPeople());
  }

  void TearDown() override {}
};

TEST_F(WhereFunctionalTest, WhereVectorUninitializedTest)
{
  Queryable<Person, std::vector> emptyQueryable;

  emptyQueryable.Where([](Person p) { return false; });

  ASSERT_TRUE(true);
}

TEST_F(WhereFunctionalTest, WhereVectorEvenTest)
{
  Queryable<int, std::vector> nullableQueryable({2, 1, 3, 7, 8, 12, 17});
  std::vector<int> expected({2, 8, 12});

  std::vector<int> values = nullableQueryable
    .Where([](int x) { return (x % 2) == 0; })
    .ToVector();

  ASSERT_EQ(expected.size(), values.size());
  for (int i = 0; i < (int)expected.size(); i++)
    ASSERT_EQ(expected[i], values[i]);
}

TEST_F(WhereFunctionalTest, WhereVectorSevenEightNineTest)
{
  std::vector<Person> expected(
  {
    Person(0, "Person 7", 0, 0, Gender::Male),
    Person(0, "Person 8", 0, 0, Gender::Male),
    Person(0, "Person 9", 0, 0, Gender::Male),
  });

  std::cout << this->queryable.At(2).ToString() << std::endl;

  std::vector<Person> people = this->queryable
    .Where([](Person p) { return p.GetName() >= "Person 7" && p.GetName() <= "Person 9"; })
    .OrderBy<std::string>([](Person p) { return p.GetName(); })
    .ToVector();

  ASSERT_EQ(expected.size(), people.size());
  for (int i = 0; i < (int)expected.size(); i++)
    ASSERT_STREQ(expected[i].GetName().c_str(), people[i].GetName().c_str());
}

TEST_F(WhereFunctionalTest, WhereVectorFemale)
{
  std::vector<Person> people = this->queryable
    .Where([](Person p) { return p.GetGender() == Gender::Female; })
    .GetContainer();

  for (Person p : people)
    ASSERT_TRUE(p.GetGender() == Gender::Female);
}

TEST_F(WhereFunctionalTest, WhereSetFemale)
{
  std::set<Person> people = Queryable<Person, std::set>(this->queryable.ToSet())
    .Where([](Person p) { return p.GetGender() == Gender::Female; })
    .ToSet();

  for (Person p : people)
    ASSERT_TRUE(p.GetGender() == Gender::Female);
}

TEST_F(WhereFunctionalTest, WhereMultiSetFemale)
{
  std::multiset<Person> people = Queryable<Person, std::multiset>(this->queryable.ToMultiSet())
    .Where([](Person p) { return p.GetGender() == Gender::Female; })
    .ToMultiSet();

  for (Person p : people)
    ASSERT_TRUE(p.GetGender() == Gender::Female);
}

TEST_F(WhereFunctionalTest, WhereDequeFemale)
{
  std::deque<Person> people = Queryable<Person, std::deque>(this->queryable.ToDeque())
    .Where([](Person p) { return p.GetGender() == Gender::Female; })
    .ToDeque();

  for (Person p : people)
    ASSERT_TRUE(p.GetGender() == Gender::Female);
}

TEST_F(WhereFunctionalTest, WhereListFemale)
{
  std::list<Person> people = Queryable<Person, std::list>(this->queryable.ToList())
    .Where([](Person p) { return p.GetGender() == Gender::Female; })
    .ToList();

  for (Person p : people)
    ASSERT_TRUE(p.GetGender() == Gender::Female);
}
