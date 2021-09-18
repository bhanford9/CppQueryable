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
#include "../../../DataStructures/Point.h"

#include "../../../Queryable/QueryBuilder.h"


using namespace QueryBuilder;

class SelectFunctionalTest : public ::testing::Test
{
protected:
  Queryable<uint> queryable;
  Queryable<Person> people;
  PersonLibrary personLibrary;

  void SetUp() override
  {
    this->queryable = BuildQueryable(std::vector<uint>({ 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 867, 1, 12 }));
    this->people = Queryable<Person>(this->personLibrary.GetPeople());
  }

  void TearDown() override {}
};

TEST_F(SelectFunctionalTest, SelectUninitialized)
{
  Queryable<Person> local;
  Queryable<std::string> result = local
    .Select<std::string>([](Person p) { return p.GetName(); });
  ASSERT_EQ(0, result.Count());
}

TEST_F(SelectFunctionalTest, DequeDefaultOut)
{
  Queryable<Person> local = BuildQueryable(this->people.ToDeque());
  Queryable<Gender> result = local.Select<Gender>([](Person p) { return p.GetGender(); });

  ASSERT_EQ(local.Count(), result.Count());
  ASSERT_TRUE(result.GetType() == QueryableType::Deque);

  int i = 0;
  local.ForEach([&](Person p)
  {
    ASSERT_TRUE(p.GetGender() == result.At(i++));
  });
}

TEST_F(SelectFunctionalTest, ListDefaultOut)
{
  Queryable<Person> local = BuildQueryable(this->people.ToList());
  Queryable<Gender> result = local.Select<Gender>([](Person p) { return p.GetGender(); });

  ASSERT_EQ(local.Count(), result.Count());
  ASSERT_TRUE(result.GetType() == QueryableType::List);

  int i = 0;
  local.ForEach([&](Person p)
  {
    ASSERT_TRUE(p.GetGender() == result.At(i++));
  });
}

TEST_F(SelectFunctionalTest, MultiSetDefaultOut)
{
  Queryable<Person> local1 = BuildQueryable(this->people.ToMultiSet());
  Queryable<Person> local2 = BuildQueryable(this->people.ToMultiSet());
  Queryable<double> ages = local1.Select<double>([](Person p) { return p.GetAge(); });
  Queryable<std::string> names = local2.Select<std::string>([](Person p) { return p.GetName(); });

  ASSERT_EQ(local1.Count(), ages.Count());
  ASSERT_EQ(local1.Count(), names.Count());
  ASSERT_TRUE(ages.GetType() == QueryableType::MultiSet);
  ASSERT_TRUE(names.GetType() == QueryableType::MultiSet);

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
  Queryable<Person> local1 = BuildQueryable(this->people.ToSet());
  Queryable<Person> local2 = BuildQueryable(this->people.ToSet());
  Queryable<double> ages = local1.Select<double>([](Person p) { return p.GetAge(); });
  Queryable<std::string> names = local2.Select<std::string>([](Person p) { return p.GetName(); });

  ASSERT_TRUE(local1.Count() == ages.Count());
  ASSERT_TRUE(local2.Count() == names.Count());
  ASSERT_FALSE(local1.Count() == names.Count());

  ASSERT_TRUE(ages.GetType() == QueryableType::Set);
  ASSERT_TRUE(names.GetType() == QueryableType::Set);

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
  Queryable<Person> local = BuildQueryable(this->people.ToVector());
  Queryable<Gender> result = local.Select<Gender>([](Person p) { return p.GetGender(); });

  ASSERT_EQ(local.Count(), result.Count());
  ASSERT_TRUE(result.GetType() == QueryableType::Vector);

  int i = 0;
  local.ForEach([&](Person p)
  {
    ASSERT_TRUE(p.GetGender() == result.At(i++));
  });
}

TEST_F(SelectFunctionalTest, SelectWhere)
{
  Queryable<Person> local1 = BuildQueryable(this->people.ToVector());
  Queryable<Person> local2 = BuildQueryable(this->people.ToVector());

  Queryable<double> ages1 = local1
    .Select<double>([](Person p) { return p.GetAge() / 10; })
    .Where([](double age) { return age > 3 && age < 8; });
  Queryable<double> ages2 = local2
    .Where([](Person p) { return p.GetAge() > 30 && p.GetAge() < 80; })
    .Select<double>([](Person p) { return p.GetAge() / 10; });

  ASSERT_EQ(5, ages1.Count());
  ASSERT_EQ(ages1.Count(), ages2.Count());

  int i = 0;
  ages1.ForEach([&](double age) { ASSERT_EQ(age, ages2.At(i++)); });
}
