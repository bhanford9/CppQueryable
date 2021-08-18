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
#include "../../../Queryable/QueryableVector.h"

using namespace QueryBuilder;

class SelectFunctionalTest : public ::testing::Test
{
protected:
  QueryableVector<uint> queryable;
  QueryableVector<Person> people;
  PersonLibrary personLibrary;

  void SetUp() override
  {
    this->queryable = BuildQueryable(std::vector<uint>({ 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 867, 1, 12 }));
    this->people = QueryableVector<Person>(this->personLibrary.GetPeople());
  }

  void TearDown() override {}
};

TEST_F(SelectFunctionalTest, SelectUninitialized)
{
  QueryableVector<Person> local;
  Queryable<std::string> * result = local
    .Select<std::string>([](Person p) { return p.GetName(); });
  ASSERT_TRUE(result != NULL);
  ASSERT_EQ(0, result->Count());
}

TEST_F(SelectFunctionalTest, DequeDefaultOut)
{
  QueryableDeque<Person> local = BuildQueryable(this->people.ToDeque());
  Queryable<Gender> * result = local.Select<Gender>([](Person p) { return p.GetGender(); });

  ASSERT_TRUE(result != NULL);
  ASSERT_EQ(local.Count(), result->Count());
  ASSERT_TRUE(result->GetType() == QueryableType::Deque);

  int i = 0;
  local.ForEach([&](Person p)
  {
    ASSERT_TRUE(p.GetGender() == result->At(i++));
  });
}

TEST_F(SelectFunctionalTest, ListDefaultOut)
{
  QueryableList<Person> local = BuildQueryable(this->people.ToList());
  Queryable<Gender> * result = local.Select<Gender>([](Person p) { return p.GetGender(); });

  ASSERT_TRUE(result != NULL);
  ASSERT_EQ(local.Count(), result->Count());
  ASSERT_TRUE(result->GetType() == QueryableType::List);

  int i = 0;
  local.ForEach([&](Person p)
  {
    ASSERT_TRUE(p.GetGender() == result->At(i++));
  });
}

TEST_F(SelectFunctionalTest, MultiSetDefaultOut)
{
  QueryableMultiSet<Person> local1 = BuildQueryable(this->people.ToMultiSet());
  QueryableMultiSet<Person> local2 = BuildQueryable(this->people.ToMultiSet());
  Queryable<double> * ages = local1.Select<double>([](Person p) { return p.GetAge(); });
  Queryable<std::string> * names = local2.Select<std::string>([](Person p) { return p.GetName(); });

  ASSERT_TRUE(ages != NULL);
  ASSERT_TRUE(names != NULL);
  ASSERT_EQ(local1.Count(), ages->Count());
  ASSERT_EQ(local1.Count(), names->Count());
  ASSERT_TRUE(ages->GetType() == QueryableType::MultiSet);
  ASSERT_TRUE(names->GetType() == QueryableType::MultiSet);

  int i = 0;
  double previousAge = -1;
  local1.ForEach([&](Person p)
  {
    double currentAge = ages->At(i);
    ASSERT_TRUE(currentAge >= previousAge);
    ASSERT_TRUE(p.GetName() == names->At(i++));
    previousAge = currentAge;
  });
}

TEST_F(SelectFunctionalTest, SetDefaultOut)
{
  QueryableSet<Person> local1 = BuildQueryable(this->people.ToSet());
  QueryableSet<Person> local2 = BuildQueryable(this->people.ToSet());
  Queryable<double> * ages = local1.Select<double>([](Person p) { return p.GetAge(); });
  Queryable<std::string> * names = local2.Select<std::string>([](Person p) { return p.GetName(); });

  ASSERT_TRUE(ages != NULL);
  ASSERT_TRUE(names != NULL);
  ASSERT_FALSE(local1.Count() == ages->Count());
  ASSERT_TRUE(local1.Count() == names->Count());
  ASSERT_TRUE(ages->GetType() == QueryableType::Set);
  ASSERT_TRUE(names->GetType() == QueryableType::Set);

  double previousAge = -1;
  ages->ForEach([&](double age)
  {
    ASSERT_TRUE(age > previousAge);
    previousAge = age;
  });

  int i = 0;
  local1.ForEach([&](Person p)
  {
    ASSERT_TRUE(p.GetName() == names->At(i++));
  });
}

TEST_F(SelectFunctionalTest, VectorDefaultOut)
{
  QueryableVector<Person> local = BuildQueryable(this->people.ToVector());
  Queryable<Gender> * result = local.Select<Gender>([](Person p) { return p.GetGender(); });

  ASSERT_TRUE(result != NULL);
  ASSERT_EQ(local.Count(), result->Count());
  ASSERT_TRUE(result->GetType() == QueryableType::Vector);

  int i = 0;
  local.ForEach([&](Person p)
  {
    ASSERT_TRUE(p.GetGender() == result->At(i++));
  });
}

TEST_F(SelectFunctionalTest, DequeListOut)
{
  QueryableDeque<Person> local = BuildQueryable(this->people.ToDeque());
  Queryable<Gender> * result = local
    .Select<Gender>([](Person p) { return p.GetGender(); }, QueryableType::List);

  ASSERT_TRUE(result != NULL);
  ASSERT_EQ(local.Count(), result->Count());
  ASSERT_TRUE(result->GetType() == QueryableType::List);

  int i = 0;
  local.ForEach([&](Person p)
  {
    ASSERT_TRUE(p.GetGender() == result->At(i++));
  });
}

TEST_F(SelectFunctionalTest, DequeMultiSetOut)
{
  QueryableDeque<Person> local = BuildQueryable(this->people.ToDeque());
  Queryable<Gender> * result = local
    .Select<Gender>([](Person p) { return p.GetGender(); }, QueryableType::MultiSet);

  ASSERT_TRUE(result != NULL);
  ASSERT_EQ(local.Count(), result->Count());
  ASSERT_TRUE(result->GetType() == QueryableType::MultiSet);

  bool foundDifferent = false;
  int i = 0;
  local.ForEach([&](Person p)
  {
    if (p.GetGender() != result->At(i++))
    {
      foundDifferent = true;
    }
  });

  ASSERT_TRUE(foundDifferent);
}

TEST_F(SelectFunctionalTest, DequeSetOut)
{
  QueryableDeque<Person> local = BuildQueryable(this->people.ToDeque());
  Queryable<Gender> * result = local
    .Select<Gender>([](Person p) { return p.GetGender(); }, QueryableType::Set);

  ASSERT_TRUE(result != NULL);
  ASSERT_FALSE(local.Count() == result->Count());
  ASSERT_EQ(2, result->Count());
  ASSERT_TRUE(result->GetType() == QueryableType::Set);
}

TEST_F(SelectFunctionalTest, DequeVectorOut)
{
  QueryableDeque<Person> local = BuildQueryable(this->people.ToDeque());
  Queryable<Gender> * result = local
    .Select<Gender>([](Person p) { return p.GetGender(); }, QueryableType::Vector);

  ASSERT_TRUE(result != NULL);
  ASSERT_EQ(local.Count(), result->Count());
  ASSERT_TRUE(result->GetType() == QueryableType::Vector);

  int i = 0;
  local.ForEach([&](Person p)
  {
    ASSERT_TRUE(p.GetGender() == result->At(i++));
  });
}

TEST_F(SelectFunctionalTest, SelectWhere)
{
  QueryableVector<Person> local1 = BuildQueryable(this->people.ToVector());
  QueryableVector<Person> local2 = BuildQueryable(this->people.ToVector());
  Queryable<double> * ages1 = local1
    .Select<double>([](Person p) { return p.GetAge() / 10; })
    ->Where([](double age) { return age > 3 && age < 8; });
  Queryable<double> * ages2 = local2
    .Where([](Person p) { return p.GetAge() > 30 && p.GetAge() < 80; })
    ->Select<double>([](Person p) { return p.GetAge() / 10; });

  ASSERT_TRUE(ages1 != NULL);
  ASSERT_TRUE(ages2 != NULL);
  ASSERT_EQ(5, ages1->Count());
  ASSERT_EQ(ages1->Count(), ages2->Count());

  int i = 0;
  ages1->ForEach([&](double age) { ASSERT_EQ(age, ages2->At(i++)); });
}
