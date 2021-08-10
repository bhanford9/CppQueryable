#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <deque>
#include <iostream>
#include <list>
#include <set>
#include <string>
#include <vector>

#include "../../../DataStructures/Animal.h"
#include "../../../DataStructures/AnimalLibrary.h"
#include "../../../DataStructures/DogWalker.h"
#include "../../../DataStructures/Gender.h"
#include "../../../DataStructures/Person.h"
#include "../../../DataStructures/PersonAndPet.h"
#include "../../../DataStructures/PersonAndPetLibrary.h"
#include "../../../DataStructures/PersonLibrary.h"
#include "../../../DataStructures/Point.h"

#include "../../../Queryable/QueryBuilder.h"
#include "../../../Queryable/QueryableType.h"
#include "../../../Queryable/Utilities/Group.h"
#include "../../../Queryable/Utilities/IGroup.h"

using namespace QueryBuilder;

class GroupByFunctionalTest : public ::testing::Test
{
protected:
  PersonLibrary personLibrary;
  AnimalLibrary animalLibrary;
  QueryableVector<Person> people;
  QueryableVector<Animal> animals;
  std::vector<PersonAndPet> petOwners;

  std::function<bool(PersonAndPet, PersonAndPet)> comparison =
    [](PersonAndPet a, PersonAndPet b) -> bool { return a.GetPerson() < b.GetPerson(); };
  typedef decltype(comparison) TComparison;
  std::function<bool(Person, Person)> comparisonId =
    [](Person a, Person b) -> bool { return a.GetId() < b.GetId(); };
  typedef decltype(comparisonId) TComparisonId;

  typedef IGroup<Gender, Person> TGenderPerson;

  void SetUp() override
  {
    this->people = QueryableVector<Person>(this->personLibrary.GetPeople());
    this->animals = QueryableVector<Animal>(this->animalLibrary.GetAnimals());
    this->petOwners = PersonAndPetLibrary().GetPetOwners();
  }

  void TearDown() override {}
};

TEST_F(GroupByFunctionalTest, DequeDefaultsTest)
{
  Queryable<TGenderPerson> * genderGroups = this->people.ToQueryableDeque()
    ->GroupBy<Gender>([](Person p) { return p.GetGender(); });
  Queryable<Person> males = this->people
    .WhereCopy([](Person p) { return p.GetGender() == Gender::Male; });
  Queryable<Person> females = this->people
    .WhereCopy([](Person p) { return p.GetGender() == Gender::Female; });

  ASSERT_TRUE(genderGroups != NULL);
  ASSERT_EQ(2, genderGroups->Count());
  ASSERT_TRUE(genderGroups->At(0).GetKey() == Gender::Male);
  ASSERT_TRUE(genderGroups->At(1).GetKey() == Gender::Female);

  genderGroups->ForEach([&](TGenderPerson group)
  {

    if (group.GetKey() == Gender::Male)
    {
      ASSERT_EQ(males.Count(), group.Count());
    }
    else
    {
      ASSERT_EQ(females.Count(), group.Count());
    }

    int i = 0;
    for (Person person : group)
    {
      if (group.GetKey() == Gender::Male)
      {
        ASSERT_TRUE(person == males.At(i++));
      }
      else
      {
        ASSERT_TRUE(person == females.At(i++));
      }
    }
  });
}

TEST_F(GroupByFunctionalTest, ListDefaultsTest)
{
  Queryable<TGenderPerson> * genderGroups = this->people.ToQueryableList()
    ->GroupBy<Gender>([](Person p) { return p.GetGender(); });
  Queryable<Person> males = this->people
    .WhereCopy([](Person p) { return p.GetGender() == Gender::Male; });
  Queryable<Person> females = this->people
    .WhereCopy([](Person p) { return p.GetGender() == Gender::Female; });

  ASSERT_TRUE(genderGroups != NULL);
  ASSERT_EQ(2, genderGroups->Count());
  ASSERT_TRUE(genderGroups->At(0).GetKey() == Gender::Male);
  ASSERT_TRUE(genderGroups->At(1).GetKey() == Gender::Female);

  genderGroups->ForEach([&](TGenderPerson group)
  {
    if (group.GetKey() == Gender::Male)
    {
      ASSERT_EQ(males.Count(), group.Count());
    }
    else
    {
      ASSERT_EQ(females.Count(), group.Count());
    }

    int i = 0;
    for (Person person : group)
    {
      if (group.GetKey() == Gender::Male)
      {
        ASSERT_TRUE(person == males.At(i++));
      }
      else
      {
        ASSERT_TRUE(person == females.At(i++));
      }
    }
  });
}

TEST_F(GroupByFunctionalTest, MultiSetDefaultsTest)
{
  Queryable<TGenderPerson> * genderGroups = this->people.ToQueryableMultiSet()
    ->GroupBy<Gender>([](Person p) { return p.GetGender(); });
  Queryable<Person> males = this->people
    .WhereCopy([](Person p) { return p.GetGender() == Gender::Male; });
  males.Sort();
  Queryable<Person> females = this->people
    .WhereCopy([](Person p) { return p.GetGender() == Gender::Female; });
  females.Sort();

  ASSERT_TRUE(genderGroups != NULL);
  ASSERT_EQ(2, genderGroups->Count());
  ASSERT_TRUE(genderGroups->At(0).GetKey() == Gender::Male);
  ASSERT_TRUE(genderGroups->At(1).GetKey() == Gender::Female);

  genderGroups->ForEach([&](TGenderPerson group)
  {
    if (group.GetKey() == Gender::Male)
    {
      ASSERT_EQ(males.Count(), group.Count());
    }
    else
    {
      ASSERT_EQ(females.Count(), group.Count());
    }

    int i = 0;
    for (Person person : group)
    {
      if (group.GetKey() == Gender::Male)
      {
        ASSERT_TRUE(person == males.At(i++));
      }
      else
      {
        ASSERT_TRUE(person == females.At(i++));
      }
    }
  });
}

TEST_F(GroupByFunctionalTest, SetDefaultsTest)
{
  Queryable<TGenderPerson> * genderGroups = this->people.ToQueryableSet()
    ->GroupBy<Gender>([](Person p) { return p.GetGender(); });
  Queryable<Person> males = this->people
    .WhereCopy([](Person p) { return p.GetGender() == Gender::Male; });
  males = *males.ToQueryableSet();
  Queryable<Person> females = this->people
    .WhereCopy([](Person p) { return p.GetGender() == Gender::Female; });
  females = *females.ToQueryableSet();

  ASSERT_TRUE(genderGroups != NULL);
  ASSERT_EQ(2, genderGroups->Count());
  ASSERT_TRUE(genderGroups->At(0).GetKey() == Gender::Male);
  ASSERT_TRUE(genderGroups->At(1).GetKey() == Gender::Female);

  genderGroups->ForEach([&](TGenderPerson group)
  {
    if (group.GetKey() == Gender::Male)
    {
      ASSERT_EQ(males.Count(), group.Count());
    }
    else
    {
      ASSERT_EQ(females.Count(), group.Count());
    }

    int i = 0;
    for (Person person : group)
    {
      if (group.GetKey() == Gender::Male)
      {
        ASSERT_TRUE(person == males.At(i++));
      }
      else
      {
        ASSERT_TRUE(person == females.At(i++));
      }
    }
  });
}


TEST_F(GroupByFunctionalTest, VectorDefaultsTest)
{
  Queryable<TGenderPerson> * genderGroups = this->people
    .GroupBy<Gender>([](Person p) { return p.GetGender(); });
  Queryable<Person> males = this->people
    .WhereCopy([](Person p) { return p.GetGender() == Gender::Male; });
  Queryable<Person> females = this->people
    .WhereCopy([](Person p) { return p.GetGender() == Gender::Female; });

  ASSERT_TRUE(genderGroups != NULL);
  ASSERT_EQ(2, genderGroups->Count());
  ASSERT_TRUE(genderGroups->At(0).GetKey() == Gender::Male);
  ASSERT_TRUE(genderGroups->At(1).GetKey() == Gender::Female);

  genderGroups->ForEach([&](TGenderPerson group)
  {
    if (group.GetKey() == Gender::Male)
    {
      ASSERT_EQ(males.Count(), group.Count());
    }
    else
    {
      ASSERT_EQ(females.Count(), group.Count());
    }

    int i = 0;
    for (Person person : group)
    {
      if (group.GetKey() == Gender::Male)
      {
        ASSERT_TRUE(person == males.At(i++));
      }
      else
      {
        ASSERT_TRUE(person == females.At(i++));
      }
    }
  });
}

TEST_F(GroupByFunctionalTest, CustomKeyCompareTest)
{
  typedef IGroup<Gender, Person, std::function<bool(Gender,Gender)>, std::function<bool(Person,Person)>> TGroupBy;
  Queryable<TGroupBy> * genderGroups = this->people
    .GroupBy<Gender, Person, std::function<bool(Gender,Gender)>, std::function<bool(Person,Person)>>(
        [](Person p) { return p.GetGender(); },
        QueryableType::Vector,
        [](Person a, Person b) { return a < b;},
        [](Person p) { return p; },
        [](Gender a, Gender b) { return a == Gender::Female && b == Gender::Male; });

  Queryable<Person> males = this->people
    .WhereCopy([](Person p) { return p.GetGender() == Gender::Male; });
  Queryable<Person> females = this->people
    .WhereCopy([](Person p) { return p.GetGender() == Gender::Female; });

  ASSERT_TRUE(genderGroups != NULL);
  ASSERT_EQ(2, genderGroups->Count());
  // order of keys are swapped
  ASSERT_TRUE(genderGroups->At(1).GetKey() == Gender::Male);
  ASSERT_TRUE(genderGroups->At(0).GetKey() == Gender::Female);

  genderGroups->ForEach([&](TGroupBy group)
  {
    if (group.GetKey() == Gender::Male)
    {
      ASSERT_EQ(males.Count(), group.Count());
    }
    else
    {
      ASSERT_EQ(females.Count(), group.Count());
    }

    int i = 0;
    for (Person person : group)
    {
      if (group.GetKey() == Gender::Male)
      {
        ASSERT_TRUE(person == males.At(i++));
      }
      else
      {
        ASSERT_TRUE(person == females.At(i++));
      }
    }
  });
}

// alternate storage type (i.e. vector->GroupBy(x => x.GetName(), Type::Set))
// custom data compare with default data retrieve
// custom data compare and retrieve
// GroupBy --> Where
