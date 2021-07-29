#include <gtest/gtest.h>

#include <array>
#include <deque>
#include <iostream>
#include <list>
#include <set>
#include <string>
#include <vector>

#include "../../../DataStructures/Animal.h"
#include "../../../DataStructures/AnimalLibrary.h"
#include "../../../DataStructures/Gender.h"
#include "../../../DataStructures/Person.h"
#include "../../../DataStructures/PersonAndPet.h"
#include "../../../DataStructures/PersonLibrary.h"

#include "../../../Queryable/QueryBuilder.h"

using namespace QueryBuilder;

class JoinFunctionalTest : public ::testing::Test
{
protected:
  QueryableVector<Person> people;
  QueryableVector<Animal> animals;
  std::function<bool(PersonAndPet, PersonAndPet)> comparison =
    [](PersonAndPet a, PersonAndPet b) -> bool { std::cout << "comparison" << std::endl;return a.GetPerson() < b.GetPerson(); };
  typedef decltype(comparison) TComparison;


  void SetUp() override
  {
    this->people = QueryableVector<Person>(PersonLibrary().GetPeople());
    this->animals = QueryableVector<Animal>(AnimalLibrary().GetAnimals());
  }

  void TearDown() override {}
};

TEST_F(JoinFunctionalTest, JoinUninitializedDequeTest)
{
  QueryableDeque<Person> people;
  QueryableDeque<Animal> animals;
  Queryable<PersonAndPet, TComparison>* petOwners =
    people.Join<Animal, long, PersonAndPet, TComparison>(
      &animals,
      [](Person person) { return person.GetId(); },
      [](Animal animal) { return animal.GetOwnerId(); },
      [](Person person, Animal animal) { return PersonAndPet(person, animal); },
      this->comparison);

  ASSERT_TRUE(petOwners);
  ASSERT_EQ(0, petOwners->Count());
}

TEST_F(JoinFunctionalTest, JoinUninitializedListTest)
{
  QueryableList<Person> people;
  QueryableList<Animal> animals;
  Queryable<PersonAndPet, TComparison>* petOwners =
    people.Join<Animal, long, PersonAndPet, TComparison>(
      &animals,
      [](Person person) { return person.GetId(); },
      [](Animal animal) { return animal.GetOwnerId(); },
      [](Person person, Animal animal) { return PersonAndPet(person, animal); },
      this->comparison);

  ASSERT_TRUE(petOwners);
  ASSERT_EQ(0, petOwners->Count());
}

TEST_F(JoinFunctionalTest, JoinUninitializedMultiSetTest)
{
  QueryableMultiSet<Person> people;
  QueryableMultiSet<Animal> animals;
  Queryable<PersonAndPet, TComparison>* petOwners =
    people.Join<Animal, long, PersonAndPet, TComparison>(
      &animals,
      [](Person person) { return person.GetId(); },
      [](Animal animal) { return animal.GetOwnerId(); },
      [](Person person, Animal animal) { return PersonAndPet(person, animal); },
      this->comparison);

  ASSERT_TRUE(petOwners);
  ASSERT_EQ(0, petOwners->Count());
}

TEST_F(JoinFunctionalTest, JoinUninitializedSetTest)
{
  QueryableSet<Person> people;
  QueryableSet<Animal> animals;
  Queryable<PersonAndPet, TComparison>* petOwners =
    people.Join<Animal, long, PersonAndPet, TComparison>(
      &animals,
      [](Person person) { return person.GetId(); },
      [](Animal animal) { return animal.GetOwnerId(); },
      [](Person person, Animal animal) { return PersonAndPet(person, animal); },
      this->comparison);

  ASSERT_TRUE(petOwners);
  ASSERT_EQ(0, petOwners->Count());
}

TEST_F(JoinFunctionalTest, JoinUninitializedVectorTest)
{
  QueryableVector<Person> people;
  QueryableVector<Animal> animals;
  Queryable<PersonAndPet, TComparison>* petOwners =
    people.Join<Animal, long, PersonAndPet, TComparison>(
      &animals,
      [](Person person) { return person.GetId(); },
      [](Animal animal) { return animal.GetOwnerId(); },
      [](Person person, Animal animal) { return PersonAndPet(person, animal); },
      this->comparison);

  ASSERT_TRUE(petOwners);
  ASSERT_EQ(0, petOwners->Count());
}
