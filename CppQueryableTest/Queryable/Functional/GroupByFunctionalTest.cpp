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

  void SetUp() override
  {
    this->people = QueryableVector<Person>(this->personLibrary.GetPeople());
    this->animals = QueryableVector<Animal>(this->animalLibrary.GetAnimals());
    this->petOwners = PersonAndPetLibrary().GetPetOwners();
  }

  void TearDown() override {}
};

TEST_F(GroupByFunctionalTest, FirstTest)
{
  Queryable<IGroup<Gender, Person>> * genderGroups = this->people
    .GroupBy<Gender>([](Person p) { return p.GetGender(); });

  ASSERT_TRUE(genderGroups != NULL);
  ASSERT_EQ(2, genderGroups->Count());

  // for (IGroup<Gender, Person> group : *genderGroups)
  // {
  //   std::cout << "size: " << group.Count() << std::endl;
  // }
}
