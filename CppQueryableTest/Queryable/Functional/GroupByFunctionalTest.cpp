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

using namespace QueryBuilder;

class GroupByFunctionalTest : public ::testing::Test
{
protected:
  PersonLibrary personLibrary;
  AnimalLibrary animalLibrary;
  Queryable<Person> people;
  Queryable<Animal> animals;
  std::vector<PersonAndPet> petOwners;

  std::function<bool(PersonAndPet, PersonAndPet)> comparison =
    [](PersonAndPet a, PersonAndPet b) -> bool { return a.GetPerson() < b.GetPerson(); };
  typedef decltype(comparison) TComparison;
  std::function<bool(Person, Person)> comparisonId =
    [](Person a, Person b) -> bool { return a.GetId() < b.GetId(); };
  typedef decltype(comparisonId) TComparisonId;

  typedef Group<Gender, Person> TGenderPerson;

  void SetUp() override
  {
    this->people = Queryable<Person>(this->personLibrary.GetPeople());
    this->animals = Queryable<Animal>(this->animalLibrary.GetAnimals());
    this->petOwners = PersonAndPetLibrary().GetPetOwners();
  }

  void TearDown() override {}
};

TEST_F(GroupByFunctionalTest, DequeDefaultsTest)
{
  Queryable<TGenderPerson> genderGroups = this->people.ToQueryableDeque()
    .GroupBy<Gender>([](Person p) { return p.GetGender(); });
  Queryable<Person> males = this->people
    .WhereCopy([](Person p) { return p.GetGender() == Gender::Male; });
  Queryable<Person> females = this->people
    .WhereCopy([](Person p) { return p.GetGender() == Gender::Female; });

  ASSERT_EQ(2, genderGroups.Count());
  ASSERT_TRUE(genderGroups.At(0).GetKey() == Gender::Male);
  ASSERT_TRUE(genderGroups.At(1).GetKey() == Gender::Female);

  genderGroups.ForEach([&](TGenderPerson group)
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

// TEST_F(GroupByFunctionalTest, ListDefaultsTest)
// {
//   Queryable<TGenderPerson> & genderGroups = this->people.ToQueryableList()
//     .GroupBy<Gender>([](Person p) { return p.GetGender(); });
//   Queryable<Person> males = this->people
//     .WhereCopy([](Person p) { return p.GetGender() == Gender::Male; });
//   Queryable<Person> females = this->people
//     .WhereCopy([](Person p) { return p.GetGender() == Gender::Female; });
//
//   ASSERT_EQ(2, genderGroups.Count());
//   ASSERT_TRUE(genderGroups.At(0).GetKey() == Gender::Male);
//   ASSERT_TRUE(genderGroups.At(1).GetKey() == Gender::Female);
//
//   genderGroups.ForEach([&](TGenderPerson group)
//   {
//     if (group.GetKey() == Gender::Male)
//     {
//       ASSERT_EQ(males.Count(), group.Count());
//     }
//     else
//     {
//       ASSERT_EQ(females.Count(), group.Count());
//     }
//
//     int i = 0;
//     for (Person person : group)
//     {
//       if (group.GetKey() == Gender::Male)
//       {
//         ASSERT_TRUE(person == males.At(i++));
//       }
//       else
//       {
//         ASSERT_TRUE(person == females.At(i++));
//       }
//     }
//   });
// }

// TEST_F(GroupByFunctionalTest, MultiSetDefaultsTest)
// {
//   Queryable<TGenderPerson> & genderGroups = this->people.ToQueryableMultiSet()
//     .GroupBy<Gender>([](Person p) { return p.GetGender(); });
//   Queryable<Person> males = this->people
//     .WhereCopy([](Person p) { return p.GetGender() == Gender::Male; });
//   males.Sort();
//   Queryable<Person> females = this->people
//     .WhereCopy([](Person p) { return p.GetGender() == Gender::Female; });
//   females.Sort();
//
//   ASSERT_EQ(2, genderGroups.Count());
//   ASSERT_TRUE(genderGroups.At(0).GetKey() == Gender::Male);
//   ASSERT_TRUE(genderGroups.At(1).GetKey() == Gender::Female);
//
//   genderGroups.ForEach([&](TGenderPerson group)
//   {
//     if (group.GetKey() == Gender::Male)
//     {
//       ASSERT_EQ(males.Count(), group.Count());
//     }
//     else
//     {
//       ASSERT_EQ(females.Count(), group.Count());
//     }
//
//     int i = 0;
//     for (Person person : group)
//     {
//       if (group.GetKey() == Gender::Male)
//       {
//         ASSERT_TRUE(person == males.At(i++));
//       }
//       else
//       {
//         ASSERT_TRUE(person == females.At(i++));
//       }
//     }
//   });
// }
//
// TEST_F(GroupByFunctionalTest, SetDefaultsTest)
// {
//   Queryable<TGenderPerson> & genderGroups = this->people.ToQueryableSet()
//     .GroupBy<Gender>([](Person p) { return p.GetGender(); });
//   Queryable<Person> males = this->people
//     .WhereCopy([](Person p) { return p.GetGender() == Gender::Male; });
//   males = males.ToQueryableSet();
//   Queryable<Person> females = this->people
//     .WhereCopy([](Person p) { return p.GetGender() == Gender::Female; });
//   females = females.ToQueryableSet();
//
//   ASSERT_EQ(2, genderGroups.Count());
//   ASSERT_TRUE(genderGroups.At(0).GetKey() == Gender::Male);
//   ASSERT_TRUE(genderGroups.At(1).GetKey() == Gender::Female);
//
//   genderGroups.ForEach([&](TGenderPerson group)
//   {
//     if (group.GetKey() == Gender::Male)
//     {
//       ASSERT_EQ(males.Count(), group.Count());
//     }
//     else
//     {
//       ASSERT_EQ(females.Count(), group.Count());
//     }
//
//     int i = 0;
//     for (Person person : group)
//     {
//       if (group.GetKey() == Gender::Male)
//       {
//         ASSERT_TRUE(person == males.At(i++));
//       }
//       else
//       {
//         ASSERT_TRUE(person == females.At(i++));
//       }
//     }
//   });
// }
//
// TEST_F(GroupByFunctionalTest, VectorDefaultsTest)
// {
//   Queryable<TGenderPerson> & genderGroups = this->people
//     .GroupBy<Gender>([](Person p) { return p.GetGender(); });
//   Queryable<Person> males = this->people
//     .WhereCopy([](Person p) { return p.GetGender() == Gender::Male; });
//   Queryable<Person> females = this->people
//     .WhereCopy([](Person p) { return p.GetGender() == Gender::Female; });
//
//   ASSERT_EQ(2, genderGroups.Count());
//   ASSERT_TRUE(genderGroups.At(0).GetKey() == Gender::Male);
//   ASSERT_TRUE(genderGroups.At(1).GetKey() == Gender::Female);
//
//   genderGroups.ForEach([&](TGenderPerson group)
//   {
//     if (group.GetKey() == Gender::Male)
//     {
//       ASSERT_EQ(males.Count(), group.Count());
//     }
//     else
//     {
//       ASSERT_EQ(females.Count(), group.Count());
//     }
//
//     int i = 0;
//     for (Person person : group)
//     {
//       if (group.GetKey() == Gender::Male)
//       {
//         ASSERT_TRUE(person == males.At(i++));
//       }
//       else
//       {
//         ASSERT_TRUE(person == females.At(i++));
//       }
//     }
//   });
// }
//
// TEST_F(GroupByFunctionalTest, CustomKeyCompareTest)
// {
//   typedef IGroup<Gender, Person, std::function<bool(Gender,Gender)>, std::function<bool(Person,Person)>> TGroupBy;
//   Queryable<TGroupBy> & genderGroups = this->people
//     .GroupBy<Gender, Person, std::function<bool(Gender,Gender)>, std::function<bool(Person,Person)>>(
//         [](Person p) { return p.GetGender(); },
//         QueryableType::Vector,
//         [](Person a, Person b) { return a < b;},
//         [](Gender a, Gender b) { return a == Gender::Female && b == Gender::Male; });
//
//   Queryable<Person> males = this->people
//     .WhereCopy([](Person p) { return p.GetGender() == Gender::Male; });
//   Queryable<Person> females = this->people
//     .WhereCopy([](Person p) { return p.GetGender() == Gender::Female; });
//
//   ASSERT_EQ(2, genderGroups.Count());
//   // order of keys are swapped
//   ASSERT_TRUE(genderGroups.At(1).GetKey() == Gender::Male);
//   ASSERT_TRUE(genderGroups.At(0).GetKey() == Gender::Female);
//
//   genderGroups.ForEach([&](TGroupBy group)
//   {
//     if (group.GetKey() == Gender::Male)
//     {
//       ASSERT_EQ(males.Count(), group.Count());
//     }
//     else
//     {
//       ASSERT_EQ(females.Count(), group.Count());
//     }
//
//     int i = 0;
//     for (Person person : group)
//     {
//       if (group.GetKey() == Gender::Male)
//       {
//         ASSERT_TRUE(person == males.At(i++));
//       }
//       else
//       {
//         ASSERT_TRUE(person == females.At(i++));
//       }
//     }
//   });
// }
//
// TEST_F(GroupByFunctionalTest, GetKeyReturnNullTest)
// {
//   typedef IGroup<void*, Person> TVoidGroup;
//   Queryable<TVoidGroup> & voidGroups = this->people
//     .GroupBy<void*>([](Person p) { return (void*)NULL; });
//
//   ASSERT_EQ(1, voidGroups.Count());
//   ASSERT_TRUE(voidGroups.At(0).GetKey() == NULL);
//
//   voidGroups.ForEach([&](TVoidGroup group)
//   {
//     ASSERT_EQ(this->people.Count(), group.Count());
//
//     int i = 0;
//     for (Person person : group)
//     {
//       ASSERT_TRUE(person == this->people.At(i++));
//     }
//   });
// }
//
// TEST_F(GroupByFunctionalTest, DequeToListStorageTest)
// {
//   Queryable<TGenderPerson> & genderGroups = this->people.ToQueryableDeque()
//     .GroupBy<Gender>(
//       [](Person p) { return p.GetGender(); },
//       QueryableType::List);
//   Queryable<Person> males = this->people
//     .WhereCopy([](Person p) { return p.GetGender() == Gender::Male; });
//   Queryable<Person> females = this->people
//     .WhereCopy([](Person p) { return p.GetGender() == Gender::Female; });
//
//   ASSERT_EQ(2, genderGroups.Count());
//   ASSERT_TRUE(genderGroups.At(0).GetKey() == Gender::Male);
//   ASSERT_TRUE(genderGroups.At(1).GetKey() == Gender::Female);
//
//   genderGroups.ForEach([&](TGenderPerson group)
//   {
//
//     if (group.GetKey() == Gender::Male)
//     {
//       ASSERT_EQ(males.Count(), group.Count());
//     }
//     else
//     {
//       ASSERT_EQ(females.Count(), group.Count());
//     }
//
//     int i = 0;
//     for (Person person : group)
//     {
//       if (group.GetKey() == Gender::Male)
//       {
//         ASSERT_TRUE(person == males.At(i++));
//       }
//       else
//       {
//         ASSERT_TRUE(person == females.At(i++));
//       }
//     }
//   });
// }
//
// TEST_F(GroupByFunctionalTest, DequeToMultiSetStorageTest)
// {
//   Queryable<TGenderPerson> & genderGroups = this->people.ToQueryableDeque()
//     .GroupBy<Gender>(
//       [](Person p) { return p.GetGender(); },
//       QueryableType::MultiSet);
//   Queryable<Person> males = this->people
//     .WhereCopy([](Person p) { return p.GetGender() == Gender::Male; });
//   males.Sort();
//   Queryable<Person> females = this->people
//     .WhereCopy([](Person p) { return p.GetGender() == Gender::Female; });
//   females.Sort();
//
//   ASSERT_EQ(2, genderGroups.Count());
//   ASSERT_TRUE(genderGroups.At(0).GetKey() == Gender::Male);
//   ASSERT_TRUE(genderGroups.At(1).GetKey() == Gender::Female);
//
//   genderGroups.ForEach([&](TGenderPerson group)
//   {
//
//     if (group.GetKey() == Gender::Male)
//     {
//       ASSERT_EQ(males.Count(), group.Count());
//     }
//     else
//     {
//       ASSERT_EQ(females.Count(), group.Count());
//     }
//
//     int i = 0;
//     for (Person person : group)
//     {
//       if (group.GetKey() == Gender::Male)
//       {
//         ASSERT_TRUE(person == males.At(i++));
//       }
//       else
//       {
//         ASSERT_TRUE(person == females.At(i++));
//       }
//     }
//   });
// }
//
// TEST_F(GroupByFunctionalTest, DequeToSetStorageTest)
// {
//   Queryable<TGenderPerson> & genderGroups = this->people.ToQueryableDeque()
//     .GroupBy<Gender>(
//       [](Person p) { return p.GetGender(); },
//       QueryableType::Set);
//   Queryable<Person> males = this->people
//     .WhereCopy([](Person p) { return p.GetGender() == Gender::Male; });
//   males = males.ToQueryableSet();
//   Queryable<Person> females = this->people
//     .WhereCopy([](Person p) { return p.GetGender() == Gender::Female; });
//   females = females.ToQueryableSet();
//
//   ASSERT_EQ(2, genderGroups.Count());
//   ASSERT_TRUE(genderGroups.At(0).GetKey() == Gender::Male);
//   ASSERT_TRUE(genderGroups.At(1).GetKey() == Gender::Female);
//
//   genderGroups.ForEach([&](TGenderPerson group)
//   {
//
//     if (group.GetKey() == Gender::Male)
//     {
//       ASSERT_EQ(males.Count(), group.Count());
//     }
//     else
//     {
//       ASSERT_EQ(females.Count(), group.Count());
//     }
//
//     int i = 0;
//     for (Person person : group)
//     {
//       if (group.GetKey() == Gender::Male)
//       {
//         ASSERT_TRUE(person == males.At(i++));
//       }
//       else
//       {
//         ASSERT_TRUE(person == females.At(i++));
//       }
//     }
//   });
// }
//
// TEST_F(GroupByFunctionalTest, CustomDataCompareTest)
// {
//   typedef IGroup<Gender, Person, std::function<bool(Gender,Gender)>, std::function<bool(Person,Person)>> TGroupBy;
//   Queryable<TGroupBy> & genderGroups = this->people
//     .GroupBy<Gender, Person, std::function<bool(Gender,Gender)>, std::function<bool(Person,Person)>>(
//         [](Person p) { return p.GetGender(); },
//         QueryableType::MultiSet,
//         [](Person a, Person b) { return a.GetAge() < b.GetAge(); },
//         [](Gender a, Gender b) { return a == Gender::Female && b == Gender::Male; });
//
//   Queryable<Person> males = this->people
//     .WhereCopy([](Person p) { return p.GetGender() == Gender::Male; });
//   males.OrderBy<double>([](Person p) { return p.GetAge(); });
//   Queryable<Person> females = this->people
//     .WhereCopy([](Person p) { return p.GetGender() == Gender::Female; });
//   males.OrderBy<double>([](Person p) { return p.GetAge(); });
//
//   ASSERT_EQ(2, genderGroups.Count());
//   // order of keys are swapped
//   ASSERT_TRUE(genderGroups.At(1).GetKey() == Gender::Male);
//   ASSERT_TRUE(genderGroups.At(0).GetKey() == Gender::Female);
//
//   genderGroups.ForEach([&](TGroupBy group)
//   {
//     if (group.GetKey() == Gender::Male)
//     {
//       ASSERT_EQ(males.Count(), group.Count());
//     }
//     else
//     {
//       ASSERT_EQ(females.Count(), group.Count());
//     }
//
//     int i = 0;
//     double previousAge = -1;
//     for (Person person : group)
//     {
//       ASSERT_TRUE(person.GetAge() >= previousAge);
//       previousAge = person.GetAge();
//
//       if (group.GetKey() == Gender::Male)
//       {
//         ASSERT_TRUE(person.GetAge() == males.At(i++).GetAge());
//       }
//       else
//       {
//         ASSERT_TRUE(person.GetAge() == females.At(i++).GetAge());
//       }
//     }
//   });
// }
//
// TEST_F(GroupByFunctionalTest, GroupByWhereTest)
// {
//   typedef IGroup<double, Person> TAgePerson;
//   Queryable<TAgePerson> ageGroupsOverThirty = this->people
//     .GroupBy<double>([](Person p) { return p.GetAge(); })
//     .WhereCopy([](TAgePerson group) { return group.GetKey() > 30; });
//
//   Queryable<Person> people2 = BuildQueryable(this->people.ToVector());
//   Queryable<TAgePerson> & overThirtyAgeGroups = people2
//     .Where([](Person person) { return person.GetAge() > 30; })
//     .GroupBy<double>([](Person p) { return p.GetAge(); });
//
//   // ASSERT_TRUE(ageGroupsOverThirty != NULL);
//   ASSERT_EQ(3, ageGroupsOverThirty.Count());
//   ASSERT_EQ(3, overThirtyAgeGroups.Count());
//   ASSERT_TRUE(ageGroupsOverThirty.At(0).GetKey() == 51);
//   ASSERT_TRUE(ageGroupsOverThirty.At(1).GetKey() == 52);
//   ASSERT_TRUE(ageGroupsOverThirty.At(2).GetKey() == 61);
//   ASSERT_TRUE(overThirtyAgeGroups.At(0).GetKey() == 51);
//   ASSERT_TRUE(overThirtyAgeGroups.At(1).GetKey() == 52);
//   ASSERT_TRUE(overThirtyAgeGroups.At(2).GetKey() == 61);
//
//   int iGroup = 0;
//   ageGroupsOverThirty.ForEach([&](TAgePerson group)
//   {
//     ASSERT_TRUE(group.Count() == overThirtyAgeGroups.At(iGroup).Count());
//
//     int iPerson = 0;
//     for (Person person : group)
//     {
//       ASSERT_TRUE(person == overThirtyAgeGroups.At(iGroup).ToVector()[iPerson++]);
//     }
//
//     iGroup++;
//   });
// }
