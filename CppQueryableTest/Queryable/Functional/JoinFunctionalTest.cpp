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

using namespace QueryBuilder;

class JoinFunctionalTest : public ::testing::Test
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

  void SetUp() override
  {
    this->people = Queryable<Person>(this->personLibrary.GetPeople());
    this->animals = Queryable<Animal>(this->animalLibrary.GetAnimals());
    this->petOwners = PersonAndPetLibrary().GetPetOwners();
  }

  void TearDown() override {}

  bool PersonEqual(Person a, Person b)
  {
    return
      a.GetId() == b.GetId() &&
      a.GetName() == b.GetName() &&
      a.GetAge() == b.GetAge() &&
      a.GetHeight() == b.GetHeight() &&
      a.GetGender() == b.GetGender();
  }

  bool AnimalEqual(Animal a, Animal b)
  {
    return
      a.GetId() == b.GetId() &&
      a.GetOwnerId() == b.GetOwnerId() &&
      a.GetName() == b.GetName() &&
      a.GetAge() == b.GetAge() &&
      a.GetGender() == b.GetGender();
  }

  bool PetOwnerEqual(PersonAndPet a, PersonAndPet b)
  {
    return
      this->PersonEqual(a.GetPerson(), b.GetPerson()) &&
      this->AnimalEqual(a.GetAnimal(), b.GetAnimal());
  }

  void RemovePetOwnerDuplicates()
  {
    // sets can remove duplicate values based on comparison of (!(a < b) && !(b < a))
    // need to remove duplicates freom expected in a similar way
    int index = 0;
    PersonAndPet previous;
    for (auto it = this->petOwners.begin(); it != this->petOwners.end();)
    {
      if (index++ != 0)
      {
        if (previous.GetPerson().GetName() == (*it).GetPerson().GetName())
        {
          this->petOwners.erase(it);
        }
        else
        {
          previous = *it;
          it++;
        }
      }
      else
      {
        previous = *it;
        it++;
      }
    }
  }

  void RemovePersonDuplicates(std::vector<Person> & people)
  {
    int index = 0;
    Person previous;
    for (auto it = people.begin(); it != people.end();)
    {
      if (index++ != 0)
      {
        if (previous.GetId() == (*it).GetId())
        {
          people.erase(it);
        }
        else
        {
          previous = *it;
          it++;
        }
      }
      else
      {
        previous = *it;
        it++;
      }
    }
  }
};

TEST_F(JoinFunctionalTest, JoinNullCollection)
{
  Queryable<Person> people(QueryableType::Deque);
  Queryable<PersonAndPet, TComparison>* petOwners =
    people.Join<Animal, long, PersonAndPet, TComparison>(
      NULL,
      [](Person person) { return person.GetId(); },
      [](Animal animal) { return animal.GetOwnerId(); },
      [](Person person, Animal animal) { return PersonAndPet(person, animal); },
      this->comparison);

  ASSERT_TRUE(petOwners);
  ASSERT_EQ(0, petOwners->Count());
  ASSERT_TRUE(petOwners->GetType() == QueryableType::Deque);
}

TEST_F(JoinFunctionalTest, JoinUninitializedDequeTest)
{
  Queryable<Person> people(QueryableType::Deque);
  Queryable<Animal> animals(QueryableType::Deque);
  Queryable<PersonAndPet, TComparison>* petOwners =
    people.Join<Animal, long, PersonAndPet, TComparison>(
      &animals,
      [](Person person) { return person.GetId(); },
      [](Animal animal) { return animal.GetOwnerId(); },
      [](Person person, Animal animal) { return PersonAndPet(person, animal); },
      this->comparison);

  ASSERT_TRUE(petOwners);
  ASSERT_EQ(0, petOwners->Count());
  ASSERT_TRUE(petOwners->GetType() == QueryableType::Deque);
}

TEST_F(JoinFunctionalTest, JoinUninitializedListTest)
{
  Queryable<Person> people(QueryableType::List);
  Queryable<Animal> animals(QueryableType::List);
  Queryable<PersonAndPet, TComparison>* petOwners =
    people.Join<Animal, long, PersonAndPet, TComparison>(
      &animals,
      [](Person person) { return person.GetId(); },
      [](Animal animal) { return animal.GetOwnerId(); },
      [](Person person, Animal animal) { return PersonAndPet(person, animal); },
      this->comparison);

  ASSERT_TRUE(petOwners);
  ASSERT_EQ(0, petOwners->Count());
  ASSERT_TRUE(petOwners->GetType() == QueryableType::List);
}

TEST_F(JoinFunctionalTest, JoinUninitializedMultiSetTest)
{
  Queryable<Person> people(QueryableType::MultiSet);
  Queryable<Animal> animals(QueryableType::MultiSet);
  Queryable<PersonAndPet, TComparison>* petOwners =
    people.Join<Animal, long, PersonAndPet, TComparison>(
      &animals,
      [](Person person) { return person.GetId(); },
      [](Animal animal) { return animal.GetOwnerId(); },
      [](Person person, Animal animal) { return PersonAndPet(person, animal); },
      this->comparison);

  ASSERT_TRUE(petOwners);
  ASSERT_EQ(0, petOwners->Count());
  ASSERT_TRUE(petOwners->GetType() == QueryableType::MultiSet);
}

TEST_F(JoinFunctionalTest, JoinUninitializedSetTest)
{
  Queryable<Person> people(QueryableType::Set);
  Queryable<Animal> animals(QueryableType::Set);
  Queryable<PersonAndPet, TComparison>* petOwners =
    people.Join<Animal, long, PersonAndPet, TComparison>(
      &animals,
      [](Person person) { return person.GetId(); },
      [](Animal animal) { return animal.GetOwnerId(); },
      [](Person person, Animal animal) { return PersonAndPet(person, animal); },
      this->comparison);

  ASSERT_TRUE(petOwners);
  ASSERT_EQ(0, petOwners->Count());
  ASSERT_TRUE(petOwners->GetType() == QueryableType::Set);
}

TEST_F(JoinFunctionalTest, JoinUninitializedVectorTest)
{
  Queryable<Person> people(QueryableType::Vector);
  Queryable<Animal> animals(QueryableType::Vector);
  Queryable<PersonAndPet, TComparison>* petOwners =
    people.Join<Animal, long, PersonAndPet, TComparison>(
      &animals,
      [](Person person) { return person.GetId(); },
      [](Animal animal) { return animal.GetOwnerId(); },
      [](Person person, Animal animal) { return PersonAndPet(person, animal); },
      this->comparison);

  ASSERT_TRUE(petOwners);
  ASSERT_EQ(0, petOwners->Count());
  ASSERT_TRUE(petOwners->GetType() == QueryableType::Vector);
}

TEST_F(JoinFunctionalTest, JoinFullVectorVectorDefaultOutTest)
{
  Queryable<PersonAndPet, TComparison>* result =
    this->people.Join<Animal, long, PersonAndPet, TComparison>(
      &this->animals,
      [](Person person) { return person.GetId(); },
      [](Animal animal) { return animal.GetOwnerId(); },
      [](Person person, Animal animal) { return PersonAndPet(person, animal); },
      this->comparison);

  ASSERT_TRUE(result);
  ASSERT_TRUE(result->GetType() == QueryableType::Vector);
  ASSERT_EQ(this->petOwners.size(), result->Count());

  for (int i = 0; i < result->Count(); i++)
  {
    ASSERT_TRUE(this->PetOwnerEqual(result->At(i), this->petOwners[i]));
  }
}

TEST_F(JoinFunctionalTest, JoinFullDequeListDefaultOutTest)
{
  Queryable<Person> dequePeople(this->people.ToDeque());
  Queryable<Animal> listAnimals(this->animals.ToList());

  Queryable<PersonAndPet, TComparison>* result =
    dequePeople.Join<Animal, long, PersonAndPet, TComparison>(
      &listAnimals,
      [](Person person) { return person.GetId(); },
      [](Animal animal) { return animal.GetOwnerId(); },
      [](Person person, Animal animal) { return PersonAndPet(person, animal); },
      this->comparison);

  ASSERT_TRUE(result);
  ASSERT_TRUE(result->GetType() == QueryableType::Deque);
  ASSERT_EQ(this->petOwners.size(), result->Count());

  for (int i = 0; i < result->Count(); i++)
  {
    ASSERT_TRUE(this->PetOwnerEqual(result->At(i), this->petOwners[i]));
  }
}

TEST_F(JoinFunctionalTest, JoinFullDequeMultiSetDefaultOutTest)
{
  Queryable<Person> dequePeople(this->people.ToDeque());
  Queryable<Animal> multiSetAnimals(this->animals.ToMultiSet());

  Queryable<PersonAndPet, TComparison>* result =
    dequePeople.Join<Animal, long, PersonAndPet, TComparison>(
      &multiSetAnimals,
      [](Person person) { return person.GetId(); },
      [](Animal animal) { return animal.GetOwnerId(); },
      [](Person person, Animal animal) { return PersonAndPet(person, animal); },
      this->comparison);

  ASSERT_TRUE(result);
  ASSERT_TRUE(result->GetType() == QueryableType::Deque);
  ASSERT_EQ(this->petOwners.size(), result->Count());

  // Join orders by ID, but sets are naturally ordered as well,
  // so the multiset gets ordered by name by default as well
  // which can make the output order different than the order of
  // added items
  std::sort(
    this->petOwners.begin(),
    this->petOwners.end(),
    [](PersonAndPet p1, PersonAndPet p2)
    {
      return p1.GetAnimal().GetOwnerId() <= p2.GetAnimal().GetOwnerId() &&
        p1.GetAnimal().GetName() < p2.GetAnimal().GetName();
    });

  for (int i = 0; i < result->Count(); i++)
  {
    ASSERT_TRUE(this->PetOwnerEqual(result->At(i), this->petOwners[i]));
  }
}

TEST_F(JoinFunctionalTest, JoinFullDequeSetDefaultOutTest)
{
  Queryable<Person> dequePeople(this->people.ToDeque());
  Queryable<Animal> setAnimals(this->animals.ToSet());

  Queryable<PersonAndPet, TComparison>* result =
    dequePeople.Join<Animal, long, PersonAndPet, TComparison>(
      &setAnimals,
      [](Person person) { return person.GetId(); },
      [](Animal animal) { return animal.GetOwnerId(); },
      [](Person person, Animal animal) { return PersonAndPet(person, animal); },
      this->comparison);

  ASSERT_TRUE(result);
  ASSERT_TRUE(result->GetType() == QueryableType::Deque);

  // Join orders by ID, but sets are naturally ordered as well,
  // so the set gets ordered by name by default as well
  // which can make the output order different than the order of
  // added items
  std::sort(
    this->petOwners.begin(),
    this->petOwners.end(),
    [](PersonAndPet p1, PersonAndPet p2)
    {
      return p1.GetAnimal().GetOwnerId() <= p2.GetAnimal().GetOwnerId() &&
        p1.GetAnimal().GetName() < p2.GetAnimal().GetName();
    });

  this->RemovePetOwnerDuplicates();

  ASSERT_EQ(this->petOwners.size(), result->Count());

  for (int i = 0; i < result->Count(); i++)
  {
    ASSERT_TRUE(this->PetOwnerEqual(result->At(i), this->petOwners[i]));
  }
}

TEST_F(JoinFunctionalTest, JoinFullDequeVectorDefaultOutTest)
{
  Queryable<Person> dequePeople(this->people.ToDeque());
  Queryable<Animal> vectorAnimals(this->animals.ToVector());

  Queryable<PersonAndPet, TComparison>* result =
    dequePeople.Join<Animal, long, PersonAndPet, TComparison>(
      &vectorAnimals,
      [](Person person) { return person.GetId(); },
      [](Animal animal) { return animal.GetOwnerId(); },
      [](Person person, Animal animal) { return PersonAndPet(person, animal); },
      this->comparison);

  ASSERT_TRUE(result);
  ASSERT_TRUE(result->GetType() == QueryableType::Deque);
  ASSERT_EQ(this->petOwners.size(), result->Count());

  for (int i = 0; i < result->Count(); i++)
  {
    ASSERT_TRUE(this->PetOwnerEqual(result->At(i), this->petOwners[i]));
  }
}

TEST_F(JoinFunctionalTest, JoinFullListDequeDefaultOutTest)
{
  Queryable<Person> listPeople(this->people.ToList());
  Queryable<Animal> dequeAnimals(this->animals.ToDeque());

  Queryable<PersonAndPet, TComparison>* result =
    listPeople.Join<Animal, long, PersonAndPet, TComparison>(
      &dequeAnimals,
      [](Person person) { return person.GetId(); },
      [](Animal animal) { return animal.GetOwnerId(); },
      [](Person person, Animal animal) { return PersonAndPet(person, animal); },
      this->comparison);

  ASSERT_TRUE(result);
  ASSERT_TRUE(result->GetType() == QueryableType::List);
  ASSERT_EQ(this->petOwners.size(), result->Count());

  for (int i = 0; i < result->Count(); i++)
  {
    ASSERT_TRUE(this->PetOwnerEqual(result->At(i), this->petOwners[i]));
  }
}

TEST_F(JoinFunctionalTest, JoinFullListMultiSetDefaultOutTest)
{
  Queryable<Person> listPeople(this->people.ToList());
  Queryable<Animal> multiSetAnimals(this->animals.ToMultiSet());

  Queryable<PersonAndPet, TComparison>* result =
    listPeople.Join<Animal, long, PersonAndPet, TComparison>(
      &multiSetAnimals,
      [](Person person) { return person.GetId(); },
      [](Animal animal) { return animal.GetOwnerId(); },
      [](Person person, Animal animal) { return PersonAndPet(person, animal); },
      this->comparison);

  ASSERT_TRUE(result);
  ASSERT_TRUE(result->GetType() == QueryableType::List);
  ASSERT_EQ(this->petOwners.size(), result->Count());

  // Join orders by ID, but sets are naturally ordered as well,
  // so the multiset gets ordered by name by default as well
  // which can make the output order different than the order of
  // added items
  std::sort(
    this->petOwners.begin(),
    this->petOwners.end(),
    [](PersonAndPet p1, PersonAndPet p2)
    {
      return p1.GetAnimal().GetOwnerId() <= p2.GetAnimal().GetOwnerId() &&
        p1.GetAnimal().GetName() < p2.GetAnimal().GetName();
    });

  for (int i = 0; i < result->Count(); i++)
  {
    ASSERT_TRUE(this->PetOwnerEqual(result->At(i), this->petOwners[i]));
  }
}

TEST_F(JoinFunctionalTest, JoinFullListSetDefaultOutTest)
{
  Queryable<Person> listPeople(this->people.ToList());
  Queryable<Animal> setAnimals(this->animals.ToSet());

  Queryable<PersonAndPet, TComparison>* result =
    listPeople.Join<Animal, long, PersonAndPet, TComparison>(
      &setAnimals,
      [](Person person) { return person.GetId(); },
      [](Animal animal) { return animal.GetOwnerId(); },
      [](Person person, Animal animal) { return PersonAndPet(person, animal); },
      this->comparison);

  ASSERT_TRUE(result);
  ASSERT_TRUE(result->GetType() == QueryableType::List);

  // Join orders by ID, but sets are naturally ordered as well,
  // so the set gets ordered by name by default as well
  // which can make the output order different than the order of
  // added items
  std::sort(
    this->petOwners.begin(),
    this->petOwners.end(),
    [](PersonAndPet p1, PersonAndPet p2)
    {
      return p1.GetAnimal().GetOwnerId() <= p2.GetAnimal().GetOwnerId() &&
        p1.GetAnimal().GetName() < p2.GetAnimal().GetName();
    });

  this->RemovePetOwnerDuplicates();

  ASSERT_EQ(this->petOwners.size(), result->Count());

  for (int i = 0; i < result->Count(); i++)
  {
    ASSERT_TRUE(this->PetOwnerEqual(result->At(i), this->petOwners[i]));
  }
}

TEST_F(JoinFunctionalTest, JoinFullListVectorDefaultOutTest)
{
  Queryable<Person> listPeople(this->people.ToList());
  Queryable<Animal> vectorAnimals(this->animals.ToVector());

  Queryable<PersonAndPet, TComparison>* result =
    listPeople.Join<Animal, long, PersonAndPet, TComparison>(
      &vectorAnimals,
      [](Person person) { return person.GetId(); },
      [](Animal animal) { return animal.GetOwnerId(); },
      [](Person person, Animal animal) { return PersonAndPet(person, animal); },
      this->comparison);

  ASSERT_TRUE(result);
  ASSERT_TRUE(result->GetType() == QueryableType::List);
  ASSERT_EQ(this->petOwners.size(), result->Count());

  for (int i = 0; i < result->Count(); i++)
  {
    ASSERT_TRUE(this->PetOwnerEqual(result->At(i), this->petOwners[i]));
  }
}

TEST_F(JoinFunctionalTest, JoinFullMultiSetDequeDefaultOutTest)
{
  Queryable<Person> multiSetPeople(this->people.ToMultiSet());
  Queryable<Animal> dequeAnimals(this->animals.ToDeque());

  Queryable<PersonAndPet, TComparison>* result =
    multiSetPeople.Join<Animal, long, PersonAndPet, TComparison>(
      &dequeAnimals,
      [](Person person) { return person.GetId(); },
      [](Animal animal) { return animal.GetOwnerId(); },
      [](Person person, Animal animal) { return PersonAndPet(person, animal); },
      this->comparison);

  ASSERT_TRUE(result);
  ASSERT_TRUE(result->GetType() == QueryableType::MultiSet);
  ASSERT_EQ(this->petOwners.size(), result->Count());

  // Join orders by ID, but sets are naturally ordered as well and the output
  // comparison function is telling the multiset to be ordered by the person's
  // name
  std::sort(
    this->petOwners.begin(),
    this->petOwners.end(),
    [](PersonAndPet p1, PersonAndPet p2)
    {
      return p1.GetPerson().GetName() < p2.GetPerson().GetName();
    });

  for (int i = 0; i < result->Count(); i++)
  {
    ASSERT_TRUE(this->PetOwnerEqual(result->At(i), this->petOwners[i]));
  }
}

TEST_F(JoinFunctionalTest, JoinFullMultiSetListDefaultOutTest)
{
  Queryable<Person> multiSetPeople(this->people.ToMultiSet());
  Queryable<Animal> listAnimals(this->animals.ToList());

  Queryable<PersonAndPet, TComparison>* result =
    multiSetPeople.Join<Animal, long, PersonAndPet, TComparison>(
      &listAnimals,
      [](Person person) { return person.GetId(); },
      [](Animal animal) { return animal.GetOwnerId(); },
      [](Person person, Animal animal) { return PersonAndPet(person, animal); },
      this->comparison);

  ASSERT_TRUE(result);
  ASSERT_TRUE(result->GetType() == QueryableType::MultiSet);
  ASSERT_EQ(this->petOwners.size(), result->Count());

  // Join orders by ID, but sets are naturally ordered as well and the output
  // comparison function is telling the multiset to be ordered by the person's
  // name
  std::sort(
    this->petOwners.begin(),
    this->petOwners.end(),
    [](PersonAndPet p1, PersonAndPet p2)
    {
      return p1.GetPerson().GetName() < p2.GetPerson().GetName();
    });

  for (int i = 0; i < result->Count(); i++)
  {
    ASSERT_TRUE(this->PetOwnerEqual(result->At(i), this->petOwners[i]));
  }
}

TEST_F(JoinFunctionalTest, JoinFullMultiSetSetDefaultOutTest)
{
  Queryable<Person> multiSetPeople(this->people.ToMultiSet());
  Queryable<Animal> setAnimals(this->animals.ToSet());

  Queryable<PersonAndPet, TComparison>* result =
    multiSetPeople.Join<Animal, long, PersonAndPet, TComparison>(
      &setAnimals,
      [](Person person) { return person.GetId(); },
      [](Animal animal) { return animal.GetOwnerId(); },
      [](Person person, Animal animal) { return PersonAndPet(person, animal); },
      this->comparison);

  ASSERT_TRUE(result);
  ASSERT_TRUE(result->GetType() == QueryableType::MultiSet);

  // Join orders by ID, but sets are naturally ordered as well and the output
  // comparison function is telling the multiset to be ordered by the person's
  // name
  std::sort(
    this->petOwners.begin(),
    this->petOwners.end(),
    [](PersonAndPet p1, PersonAndPet p2)
    {
      if (p1.GetAnimal().GetOwnerId() == p2.GetAnimal().GetOwnerId())
      {
        return p1.GetAnimal().GetName() < p2.GetAnimal().GetName();
      }
      return p1.GetPerson().GetName() <= p2.GetPerson().GetName();
    });

  this->RemovePetOwnerDuplicates();

  ASSERT_EQ(this->petOwners.size(), result->Count());
  for (int i = 0; i < result->Count(); i++)
  {
    ASSERT_TRUE(this->PetOwnerEqual(result->At(i), this->petOwners[i]));
  }
}

TEST_F(JoinFunctionalTest, JoinFullMultiSetVectorDefaultOutTest)
{
  Queryable<Person> multiSetPeople(this->people.ToMultiSet());
  Queryable<Animal> vectorAnimals(this->animals.ToVector());

  Queryable<PersonAndPet, TComparison>* result =
    multiSetPeople.Join<Animal, long, PersonAndPet, TComparison>(
      &vectorAnimals,
      [](Person person) { return person.GetId(); },
      [](Animal animal) { return animal.GetOwnerId(); },
      [](Person person, Animal animal) { return PersonAndPet(person, animal); },
      this->comparison);

  ASSERT_TRUE(result);
  ASSERT_TRUE(result->GetType() == QueryableType::MultiSet);
  ASSERT_EQ(this->petOwners.size(), result->Count());

  // Join orders by ID, but sets are naturally ordered as well and the output
  // comparison function is telling the multiset to be ordered by the person's
  // name
  std::sort(
    this->petOwners.begin(),
    this->petOwners.end(),
    [](PersonAndPet p1, PersonAndPet p2)
    {
      return p1.GetPerson().GetName() < p2.GetPerson().GetName();
    });

  for (int i = 0; i < result->Count(); i++)
  {
    ASSERT_TRUE(this->PetOwnerEqual(result->At(i), this->petOwners[i]));
  }
}

TEST_F(JoinFunctionalTest, JoinFullSetDequeDefaultOutTest)
{
  Queryable<Person> setPeople(this->people.ToSet());
  Queryable<Animal> dequeAnimals(this->animals.ToDeque());

  Queryable<PersonAndPet, TComparison>* result =
    setPeople.Join<Animal, long, PersonAndPet, TComparison>(
      &dequeAnimals,
      [](Person person) { return person.GetId(); },
      [](Animal animal) { return animal.GetOwnerId(); },
      [](Person person, Animal animal) { return PersonAndPet(person, animal); },
      this->comparison);

  ASSERT_TRUE(result);
  ASSERT_TRUE(result->GetType() == QueryableType::Set);

  // Join orders by ID, but sets are naturally ordered as well,
  // so the set gets ordered by name by default as well
  // which can make the output order different than the order of
  // added items
  std::sort(
    this->petOwners.begin(),
    this->petOwners.end(),
    [](PersonAndPet p1, PersonAndPet p2)
    {
      return p1.GetPerson() < p2.GetPerson();
    });

  this->RemovePetOwnerDuplicates();

  ASSERT_EQ(this->petOwners.size(), result->Count());

  for (int i = 0; i < result->Count(); i++)
  {
    ASSERT_TRUE(this->PetOwnerEqual(result->At(i), this->petOwners[i]));
  }
}

TEST_F(JoinFunctionalTest, JoinFullSetListDefaultOutTest)
{
  Queryable<Person> setPeople(this->people.ToSet());
  Queryable<Animal> listAnimals(this->animals.ToList());

  Queryable<PersonAndPet, TComparison>* result =
    setPeople.Join<Animal, long, PersonAndPet, TComparison>(
      &listAnimals,
      [](Person person) { return person.GetId(); },
      [](Animal animal) { return animal.GetOwnerId(); },
      [](Person person, Animal animal) { return PersonAndPet(person, animal); },
      this->comparison);

  ASSERT_TRUE(result);
  ASSERT_TRUE(result->GetType() == QueryableType::Set);

  // Join orders by ID, but sets are naturally ordered as well,
  // so the set gets ordered by name by default as well
  // which can make the output order different than the order of
  // added items
  std::sort(
    this->petOwners.begin(),
    this->petOwners.end(),
    [](PersonAndPet p1, PersonAndPet p2)
    {
      return p1.GetPerson() < p2.GetPerson();
    });

  this->RemovePetOwnerDuplicates();

  ASSERT_EQ(this->petOwners.size(), result->Count());

  for (int i = 0; i < result->Count(); i++)
  {
    ASSERT_TRUE(this->PetOwnerEqual(result->At(i), this->petOwners[i]));
  }
}

TEST_F(JoinFunctionalTest, JoinFullSetMultiSetDefaultOutTest)
{
  Queryable<Person> setPeople(this->people.ToSet());
  Queryable<Animal> multiSetAnimals(this->animals.ToMultiSet());

  Queryable<PersonAndPet, TComparison>* result =
    setPeople.Join<Animal, long, PersonAndPet, TComparison>(
      &multiSetAnimals,
      [](Person person) { return person.GetId(); },
      [](Animal animal) { return animal.GetOwnerId(); },
      [](Person person, Animal animal) { return PersonAndPet(person, animal); },
      this->comparison);

  ASSERT_TRUE(result);
  ASSERT_TRUE(result->GetType() == QueryableType::Set);

  // Join orders by ID, but sets are naturally ordered as well,
  // so the set gets ordered by name by default as well
  // which can make the output order different than the order of
  // added items
  std::sort(
    this->petOwners.begin(),
    this->petOwners.end(),
    [](PersonAndPet p1, PersonAndPet p2)
    {
      if (p1.GetAnimal().GetOwnerId() == p2.GetAnimal().GetOwnerId())
      {
        return p1.GetAnimal().GetName() < p2.GetAnimal().GetName();
      }
      return p1.GetPerson().GetName() < p2.GetPerson().GetName();
    });

  this->RemovePetOwnerDuplicates();

  ASSERT_EQ(this->petOwners.size(), result->Count());

  for (int i = 0; i < result->Count(); i++)
  {
    ASSERT_TRUE(this->PetOwnerEqual(result->At(i), this->petOwners[i]));
  }
}

TEST_F(JoinFunctionalTest, JoinFullSetVectorDefaultOutTest)
{
  Queryable<Person> setPeople(this->people.ToSet());
  Queryable<Animal> vectorAnimals(this->animals.ToVector());

  Queryable<PersonAndPet, TComparison>* result =
    setPeople.Join<Animal, long, PersonAndPet, TComparison>(
      &vectorAnimals,
      [](Person person) { return person.GetId(); },
      [](Animal animal) { return animal.GetOwnerId(); },
      [](Person person, Animal animal) { return PersonAndPet(person, animal); },
      this->comparison);

  ASSERT_TRUE(result);
  ASSERT_TRUE(result->GetType() == QueryableType::Set);

  // Join orders by ID, but sets are naturally ordered as well,
  // so the set gets ordered by name by default as well
  // which can make the output order different than the order of
  // added items
  std::sort(
    this->petOwners.begin(),
    this->petOwners.end(),
    [](PersonAndPet p1, PersonAndPet p2)
    {
      return p1.GetPerson() < p2.GetPerson();
    });

  this->RemovePetOwnerDuplicates();

  ASSERT_EQ(this->petOwners.size(), result->Count());

  for (int i = 0; i < result->Count(); i++)
  {
    ASSERT_TRUE(this->PetOwnerEqual(result->At(i), this->petOwners[i]));
  }
}

TEST_F(JoinFunctionalTest, JoinFullVectorDequeDefaultOutTest)
{
  Queryable<Person> vectorPeople(this->people.ToVector());
  Queryable<Animal> dequeAnimals(this->animals.ToDeque());

  Queryable<PersonAndPet, TComparison>* result =
    vectorPeople.Join<Animal, long, PersonAndPet, TComparison>(
      &dequeAnimals,
      [](Person person) { return person.GetId(); },
      [](Animal animal) { return animal.GetOwnerId(); },
      [](Person person, Animal animal) { return PersonAndPet(person, animal); },
      this->comparison);

  ASSERT_TRUE(result);
  ASSERT_TRUE(result->GetType() == QueryableType::Vector);
  ASSERT_EQ(this->petOwners.size(), result->Count());

  for (int i = 0; i < result->Count(); i++)
  {
    ASSERT_TRUE(this->PetOwnerEqual(result->At(i), this->petOwners[i]));
  }
}

TEST_F(JoinFunctionalTest, JoinFullVectorListDefaultOutTest)
{
  Queryable<Person> vectorPeople(this->people.ToVector());
  Queryable<Animal> listAnimals(this->animals.ToList());

  Queryable<PersonAndPet, TComparison>* result =
    vectorPeople.Join<Animal, long, PersonAndPet, TComparison>(
      &listAnimals,
      [](Person person) { return person.GetId(); },
      [](Animal animal) { return animal.GetOwnerId(); },
      [](Person person, Animal animal) { return PersonAndPet(person, animal); },
      this->comparison);

  ASSERT_TRUE(result);
  ASSERT_TRUE(result->GetType() == QueryableType::Vector);
  ASSERT_EQ(this->petOwners.size(), result->Count());

  for (int i = 0; i < result->Count(); i++)
  {
    ASSERT_TRUE(this->PetOwnerEqual(result->At(i), this->petOwners[i]));
  }
}

TEST_F(JoinFunctionalTest, JoinFullVectorMultiSetDefaultOutTest)
{
  Queryable<Person> vectorPeople(this->people.ToVector());
  Queryable<Animal> multiSetAnimals(this->animals.ToMultiSet());

  Queryable<PersonAndPet, TComparison>* result =
    vectorPeople.Join<Animal, long, PersonAndPet, TComparison>(
      &multiSetAnimals,
      [](Person person) { return person.GetId(); },
      [](Animal animal) { return animal.GetOwnerId(); },
      [](Person person, Animal animal) { return PersonAndPet(person, animal); },
      this->comparison);

  ASSERT_TRUE(result);
  ASSERT_TRUE(result->GetType() == QueryableType::Vector);
  ASSERT_EQ(this->petOwners.size(), result->Count());

  // Join orders by ID, but sets are naturally ordered as well,
  // so the multiset gets ordered by name by default as well
  // which can make the output order different than the order of
  // added items
  std::sort(
    this->petOwners.begin(),
    this->petOwners.end(),
    [](PersonAndPet p1, PersonAndPet p2)
    {
      return p1.GetAnimal().GetOwnerId() <= p2.GetAnimal().GetOwnerId() &&
        p1.GetAnimal().GetName() < p2.GetAnimal().GetName();
    });

  for (int i = 0; i < result->Count(); i++)
  {
    ASSERT_TRUE(this->PetOwnerEqual(result->At(i), this->petOwners[i]));
  }
}

TEST_F(JoinFunctionalTest, JoinFullVectorSetDefaultOutTest)
{
  Queryable<Person> vectorPeople(this->people.ToVector());
  Queryable<Animal> setAnimals(this->animals.ToSet());

  Queryable<PersonAndPet, TComparison>* result =
    vectorPeople.Join<Animal, long, PersonAndPet, TComparison>(
      &setAnimals,
      [](Person person) { return person.GetId(); },
      [](Animal animal) { return animal.GetOwnerId(); },
      [](Person person, Animal animal) { return PersonAndPet(person, animal); },
      this->comparison);

  ASSERT_TRUE(result);
  ASSERT_TRUE(result->GetType() == QueryableType::Vector);

  // Join orders by ID, but sets are naturally ordered as well,
  // so the set gets ordered by name by default as well
  // which can make the output order different than the order of
  // added items
  std::sort(
    this->petOwners.begin(),
    this->petOwners.end(),
    [](PersonAndPet p1, PersonAndPet p2)
    {
      return p1.GetAnimal().GetOwnerId() <= p2.GetAnimal().GetOwnerId() &&
        p1.GetAnimal().GetName() < p2.GetAnimal().GetName();
    });

  this->RemovePetOwnerDuplicates();

  ASSERT_EQ(this->petOwners.size(), result->Count());

  for (int i = 0; i < result->Count(); i++)
  {
    ASSERT_TRUE(this->PetOwnerEqual(result->At(i), this->petOwners[i]));
  }
}

TEST_F(JoinFunctionalTest, JoinFullDequeListListOutTest)
{
  Queryable<Person> dequePeople(this->people.ToDeque());
  Queryable<Animal> listAnimals(this->animals.ToList());

  Queryable<PersonAndPet, TComparison>* result =
    dequePeople.Join<Animal, long, PersonAndPet, TComparison>(
      &listAnimals,
      [](Person person) { return person.GetId(); },
      [](Animal animal) { return animal.GetOwnerId(); },
      [](Person person, Animal animal) { return PersonAndPet(person, animal); },
      this->comparison,
      QueryableType::List);

  ASSERT_TRUE(result);
  ASSERT_TRUE(result->GetType() == QueryableType::List);
  ASSERT_EQ(this->petOwners.size(), result->Count());

  for (int i = 0; i < result->Count(); i++)
  {
    ASSERT_TRUE(this->PetOwnerEqual(result->At(i), this->petOwners[i]));
  }
}

TEST_F(JoinFunctionalTest, JoinFullDequeListMultiSetOutTest)
{
  Queryable<Person> dequePeople(this->people.ToDeque());
  Queryable<Animal> listAnimals(this->animals.ToList());

  Queryable<PersonAndPet, TComparison>* result =
    dequePeople.Join<Animal, long, PersonAndPet, TComparison>(
      &listAnimals,
      [](Person person) { return person.GetId(); },
      [](Animal animal) { return animal.GetOwnerId(); },
      [](Person person, Animal animal) { return PersonAndPet(person, animal); },
      this->comparison,
      QueryableType::MultiSet);

  ASSERT_TRUE(result);
  ASSERT_TRUE(result->GetType() == QueryableType::MultiSet);
  ASSERT_EQ(this->petOwners.size(), result->Count());

  std::sort(
    this->petOwners.begin(),
    this->petOwners.end(),
    [](PersonAndPet p1, PersonAndPet p2)
    {
      return p1.GetPerson() < p2.GetPerson();
    });

  for (int i = 0; i < result->Count(); i++)
  {
    ASSERT_TRUE(this->PetOwnerEqual(result->At(i), this->petOwners[i]));
  }
}

TEST_F(JoinFunctionalTest, JoinFullDequeListSetOutTest)
{
  Queryable<Person> dequePeople(this->people.ToDeque());
  Queryable<Animal> listAnimals(this->animals.ToList());

  Queryable<PersonAndPet, TComparison>* result =
    dequePeople.Join<Animal, long, PersonAndPet, TComparison>(
      &listAnimals,
      [](Person person) { return person.GetId(); },
      [](Animal animal) { return animal.GetOwnerId(); },
      [](Person person, Animal animal) { return PersonAndPet(person, animal); },
      this->comparison,
      QueryableType::Set);

  ASSERT_TRUE(result);
  ASSERT_TRUE(result->GetType() == QueryableType::Set);

  std::sort(
    this->petOwners.begin(),
    this->petOwners.end(),
    [](PersonAndPet p1, PersonAndPet p2)
    {
      return p1.GetPerson() < p2.GetPerson();
    });

  this->RemovePetOwnerDuplicates();

  ASSERT_EQ(this->petOwners.size(), result->Count());

  for (int i = 0; i < result->Count(); i++)
  {
    ASSERT_TRUE(this->PetOwnerEqual(result->At(i), this->petOwners[i]));
  }
}

TEST_F(JoinFunctionalTest, DefaultOutComparisonTest)
{
  double expectedX = 9;
  double expectedY = 10;

  Queryable<Person> dequePeople(this->people.ToDeque());
  Queryable<Animal> setAnimals(this->animals.ToSet());

  // Testing that supplying the comparison type is not necessary when the default
  //   comparison for a class can be used.
  // This is more likely the common use case and it is much more convecient to
  //   only have to deal with 3 type parameters and 4 variable parameters
  Queryable<Point>* result =
    dequePeople.Join<Animal, long, Point>(
      &setAnimals,
      [](Person person) { return person.GetId(); },
      [](Animal animal) { return animal.GetOwnerId(); },
      [&](Person person, Animal animal) { return Point(expectedX, expectedY); });

  ASSERT_TRUE(result->Count() > 0);

  result->ForEach([&](Point p)
  {
    ASSERT_EQ(expectedX, p.X);
    ASSERT_EQ(expectedY, p.Y);
  });
}

TEST_F(JoinFunctionalTest, PassedInCompareOverwritesDefaultTest)
{
  // person is ordered by name by default
  // passing in an ID comparison should overwrite this
  Queryable<Person> setPeople(this->people.ToSet());
  Queryable<Animal> listAnimals(this->animals.ToList());

  Queryable<Person, TComparisonId>* result =
    setPeople.Join<Animal, long, Person, TComparisonId>(
      &listAnimals,
      [](Person person) { return person.GetId(); },
      [](Animal animal) { return animal.GetOwnerId(); },
      [](Person person, Animal animal) { return person; },
      this->comparisonId);

  ASSERT_TRUE(result);
  ASSERT_TRUE(result->GetType() == QueryableType::Set);

  std::vector<Person> sortedPeople;
  this->animals.ForEach([&](Animal a)
  {
    if (this->people.Any([&](Person p) { return p.GetId() == a.GetOwnerId(); }))
      sortedPeople.push_back(this->people.First([&](Person p) { return p.GetId() == a.GetOwnerId(); } ));
  });
  std::sort(sortedPeople.begin(), sortedPeople.end(), this->comparisonId);

  this->RemovePersonDuplicates(sortedPeople);

  ASSERT_EQ(sortedPeople.size(), result->Count());

  for (int i = 0; i < result->Count(); i++)
  {
    ASSERT_TRUE(result->At(i).GetId() == sortedPeople[i].GetId());
  }
}

TEST_F(JoinFunctionalTest, WhereJoinWhereTest)
{
  Queryable<Person> dequePeople(this->people.ToDeque());
  Queryable<Animal> listAnimals(this->animals.ToList());

  Queryable<DogWalker>* result =
    dequePeople
      .Where([](Person p) { return p.GetId() >= 2 && p.GetId() <= 5; })
      ->Join<Animal, long, DogWalker>(
        &listAnimals,
        [](Person person) { return person.GetId(); },
        [](Animal animal) { return animal.GetOwnerId(); },
        [](Person person, Animal animal) { return DogWalker(person, animal); })
      ->Where([](DogWalker dw) { return dw.GetId() % 2 == 0; });

  int expectedCount = 0;
  this->animals.ForEach([&](Animal a) { if (a.GetOwnerId() >= 2 && a.GetOwnerId() <= 5 && a.GetOwnerId() % 2 == 0) expectedCount++; });

  ASSERT_TRUE(expectedCount > 0);
  ASSERT_EQ(expectedCount, result->Count());

  result->ForEach([](DogWalker dw) { ASSERT_TRUE(dw.GetId() == 2 || dw.GetId() == 4); });
}


// THINGS TO TEST
//
// - Where --> Join --> Where
