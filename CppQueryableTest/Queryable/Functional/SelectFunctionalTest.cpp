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

class SelectFunctionalTest : public ::testing::Test
{
protected:
  PersonLibrary personLibrary;
  QueryableVector<size_t> queryable;
  QueryableVector<Person> people;

  SelectFunctionalTest() :
    personLibrary(),
    queryable(BuildQueryable(std::vector<size_t>({ 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 867, 1, 12 }))),
    people(BuildQueryable(this->personLibrary.GetPeople()))
  {
  }

  void SetUp() override
  {
  }

  void TearDown() override {}
};

// TEST_F(SelectFunctionalTest, SelectUninitialized)
// {
//   IQueryable<Person> local(BuildQueryable(std::vector<Person>()));
//   IQueryable<std::string> result = local
//     .Select<std::string>([](Person p) { return p.GetName(); });
//   ASSERT_EQ(0, result.Count());
// }

TEST_F(SelectFunctionalTest, DequeDefaultOut)
{
  QueryableDeque<Person> local = BuildQueryable(this->people.ToDeque());
  QueryableDeque<Gender> result = local
    .Select<Gender>([](Person p) { return p.GetGender(); });

  ASSERT_EQ(local.Count(), result.Count());

  int i = 0;
  local.ForEach([&](Person p)
  {
    ASSERT_TRUE(p.GetGender() == result.At(i++));
  });
}

TEST_F(SelectFunctionalTest, ListDefaultOut)
{
  QueryableList<Person> local = BuildQueryable(this->people.ToList());
  QueryableList<Gender> result = local
    .Select<Gender>([](Person p) { return p.GetGender(); });

  ASSERT_EQ(local.Count(), result.Count());

  int i = 0;
  local.ForEach([&](Person p)
  {
    ASSERT_TRUE(p.GetGender() == result.At(i++));
  });
}

TEST_F(SelectFunctionalTest, MultiSetDefaultOut)
{
  QueryableMultiSet<Person> local1 = BuildQueryable(this->people.ToMultiSet());
  QueryableMultiSet<Person> local2 = BuildQueryable(this->people.ToMultiSet());
  QueryableMultiSet<double> ages = local1
    .Select<double>([](Person p) { return p.GetAge(); })
    .ToQueryable();
  QueryableMultiSet<std::string> names = local2
    .Select<std::string>([](Person p) { return p.GetName(); })
    .ToQueryable();

  ASSERT_EQ(local1.Count(), ages.Count());
  ASSERT_EQ(local1.Count(), names.Count());

  int i = 0;
  double previousAge = -1;
  local1.ForEach([&](Person p)
  {
    double currentAge = ages.At(i);
    std::string currentName = names.At(i);
    ASSERT_GE(currentAge, previousAge);
    ASSERT_STREQ(local2.At(i++).GetName().c_str(), currentName.c_str());
    previousAge = currentAge;
  });
}

TEST_F(SelectFunctionalTest, SetDefaultOut)
{
  QueryableSet<Person> local1 = BuildQueryable(this->people.ToSet());
  QueryableSet<Person> local2 = BuildQueryable(this->people.ToSet());
  QueryableSet<double> ages = local1
    .Select<double>([](Person p) { return p.GetAge(); })
    .ToQueryable();
  QueryableSet<std::string> names = local2
    .Select<std::string>([](Person p) { return p.GetName(); })
    .ToQueryable();

  // all the names are unique, so it is expected that their size is consistent with the originals
  // there are duplicate ages, so it is expected that their size is inconsistent with the originals
  ASSERT_NE(local1.Count(), ages.Count());
  ASSERT_EQ(local2.Count(), names.Count());
  ASSERT_EQ(local1.Count(), names.Count());

  double previousAge = -1;
  ages.ForEach([&](double age)
  {
    ASSERT_TRUE(age > previousAge);
    previousAge = age;
  });

  int i = 0;
  local2.ForEach([&](Person p)
  {
    ASSERT_TRUE(p.GetName() == names.At(i++));
  });
}

TEST_F(SelectFunctionalTest, VectorDefaultOut)
{
  QueryableVector<Person> local = BuildQueryable(this->people.ToVector());
  QueryableVector<Gender> result = local
    .Select<Gender>([](Person p) { return p.GetGender(); });

  ASSERT_EQ(local.Count(), result.Count());

  int i = 0;
  local.ForEach([&](Person p)
  {
    ASSERT_TRUE(p.GetGender() == result.At(i++));
  });
}

TEST_F(SelectFunctionalTest, SelectWhere)
{
  QueryableVector<Person> local1 = BuildQueryable(this->people.ToVector());
  QueryableVector<Person> local2 = BuildQueryable(this->people.ToVector());

  QueryableVector<double> ages1 = local1
    .Select<double>([](Person p) { return p.GetAge() / 10; })
    .Where([](double age) { return age > 3 && age < 8; });

  QueryableVector<double> ages2 = local2
    .Where([](Person p) { return p.GetAge() > 30 && p.GetAge() < 80; })
    .Select<double>([](Person p) { return p.GetAge() / 10; });

  ASSERT_EQ(5, ages1.Count());
  ASSERT_EQ(ages1.Count(), ages2.Count());

  int i = 0;
  ages1.ForEach([&](double age) { ASSERT_EQ(age, ages2.At(i++)); });
}
