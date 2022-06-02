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
  IQueryable<uint> queryable;
  IQueryable<Person> people;

  SelectFunctionalTest() :
    personLibrary(),
    queryable(BuildQueryable2(std::vector<uint>({ 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 867, 1, 12 }))),
    people(BuildQueryable2(this->personLibrary.GetPeople()))
  {
  }

  void SetUp() override
  {
  }

  void TearDown() override {}
};

// TEST_F(SelectFunctionalTest, SelectUninitialized)
// {
//   IQueryable<Person> local(BuildQueryable2(std::vector<Person>()));
//   IQueryable<std::string> result = local
//     .Select<std::string>([](Person p) { return p.GetName(); });
//   ASSERT_EQ(0, result.Count());
// }

TEST_F(SelectFunctionalTest, DequeDefaultOut)
{
  IQueryable<Person> local = BuildQueryable2(this->people.ToDeque());
  IQueryable<Gender> result = local
    .Select<std::deque, Gender>([](Person p) { return p.GetGender(); });

  ASSERT_EQ(local.Count(), result.Count());

  int i = 0;
  local.ForEach([&](Person p)
  {
    ASSERT_TRUE(p.GetGender() == result.At(i++));
  });
}

TEST_F(SelectFunctionalTest, ListDefaultOut)
{
  IQueryable<Person> local = BuildQueryable2(this->people.ToList());
  IQueryable<Gender> result = local
    .Select<std::list, Gender>([](Person p) { return p.GetGender(); });

  ASSERT_EQ(local.Count(), result.Count());

  int i = 0;
  local.ForEach([&](Person p)
  {
    ASSERT_TRUE(p.GetGender() == result.At(i++));
  });
}

TEST_F(SelectFunctionalTest, MultiSetDefaultOut)
{
  IQueryable<Person> local1 = BuildQueryable2(this->people.ToMultiSet());
  IQueryable<Person> local2 = BuildQueryable2(this->people.ToMultiSet());
  QueryableMultiSet<double> ages = local1
    .Select<std::multiset, double>([](Person p) { return p.GetAge(); })
    .ToQueryableMultiSet();
  QueryableMultiSet<std::string> names = local2
    .Select<std::multiset, std::string>([](Person p) { return p.GetName(); })
    .ToQueryableMultiSet();

  ASSERT_EQ(local1.Count(), ages.Count());
  ASSERT_EQ(local1.Count(), names.Count());

  int i = 0;
  double previousAge = -1;
  local1.ForEach([&](Person p)
  {
    double currentAge = ages.At(i);
    std::string currentName = names.At(i);
    ASSERT_TRUE(currentAge >= previousAge);
    ASSERT_TRUE(local2.At(i++).GetName() == currentName);
    previousAge = currentAge;
  });
}

TEST_F(SelectFunctionalTest, SetDefaultOut)
{
  IQueryable<Person> local1 = BuildQueryable2(this->people.ToSet());
  IQueryable<Person> local2 = BuildQueryable2(this->people.ToSet());
  QueryableSet<double> ages = local1
    .Select<std::set, double>([](Person p) { return p.GetAge(); })
    .ToQueryableSet();
  QueryableSet<std::string> names = local2
    .Select<std::set, std::string>([](Person p) { return p.GetName(); })
    .ToQueryableSet();

  // all the names are unique, so it is expected that their size is consistent with the originals
  // there are duplicate ages, so it is expected that their size is inconsistent with the originals
  ASSERT_TRUE(local1.Count() != ages.Count());
  ASSERT_TRUE(local2.Count() == names.Count());
  ASSERT_TRUE(local1.Count() == names.Count());

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
  IQueryable<Person> local = BuildQueryable2(this->people.ToVector());
  IQueryable<Gender> result = local
    .Select<std::vector, Gender>([](Person p) { return p.GetGender(); });

  ASSERT_EQ(local.Count(), result.Count());

  int i = 0;
  local.ForEach([&](Person p)
  {
    ASSERT_TRUE(p.GetGender() == result.At(i++));
  });
}

TEST_F(SelectFunctionalTest, SelectWhere)
{
  IQueryable<Person> local1 = BuildQueryable2(this->people.ToVector());
  IQueryable<Person> local2 = BuildQueryable2(this->people.ToVector());

  QueryableVector<double> ages1 = local1
    .Select<std::vector, double>([](Person p) { return p.GetAge() / 10; })
    .Where([](double age) { return age > 3 && age < 8; })
    .ToQueryableVector();

  QueryableVector<double> ages2 = local2
    .Where([](Person p) { return p.GetAge() > 30 && p.GetAge() < 80; })
    .Select<std::vector, double>([](Person p) { return p.GetAge() / 10; })
    .ToQueryableVector();

  ASSERT_EQ(5, ages1.Count());
  ASSERT_EQ(ages1.Count(), ages2.Count());

  int i = 0;
  ages1.ForEach([&](double age) { ASSERT_EQ(age, ages2.At(i++)); });
}
