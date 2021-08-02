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
#include "../../../DataStructures/Gender.h"
#include "../../../DataStructures/Person.h"
#include "../../../DataStructures/PersonAndPet.h"
#include "../../../DataStructures/PersonAndPetLibrary.h"
#include "../../../DataStructures/PersonLibrary.h"

#include "../../../Queryable/QueryBuilder.h"
#include "../../../Queryable/QueryableType.h"

using namespace QueryBuilder;

class JoinFunctionalTest : public ::testing::Test
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


  void SetUp() override
  {
    this->people = QueryableVector<Person>(this->personLibrary.GetPeople());
    this->animals = QueryableVector<Animal>(this->animalLibrary.GetAnimals());
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
};

TEST_F(JoinFunctionalTest, JoinNullCollection)
{
  QueryableDeque<Person> people;
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
  ASSERT_TRUE(petOwners->GetType() == QueryableType::Deque);
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
  ASSERT_TRUE(petOwners->GetType() == QueryableType::List);
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
  ASSERT_TRUE(petOwners->GetType() == QueryableType::MultiSet);
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
  ASSERT_TRUE(petOwners->GetType() == QueryableType::Set);
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
  QueryableDeque<Person> dequePeople(this->people.ToDeque());
  QueryableList<Animal> listAnimals(this->animals.ToList());

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
  QueryableDeque<Person> dequePeople(this->people.ToDeque());
  QueryableMultiSet<Animal> multiSetAnimals(this->animals.ToMultiSet());

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
  QueryableDeque<Person> dequePeople(this->people.ToDeque());
  QueryableSet<Animal> setAnimals(this->animals.ToSet());

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

  // sets can remove duplicate values based on comparison of (!(a < b) && !(b < a))
  // need to remove duplicates freom expected in a similar way
  int index = 0;
  PersonAndPet previous;
  for (auto it = this->petOwners.begin(); it != this->petOwners.end();)
  {
    if (index++ != 0)
    {
      if (previous.GetAnimal().GetOwnerId() == (*it).GetAnimal().GetOwnerId())
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

  ASSERT_EQ(this->petOwners.size(), result->Count());

  for (int i = 0; i < result->Count(); i++)
  {
    ASSERT_TRUE(this->PetOwnerEqual(result->At(i), this->petOwners[i]));
  }
}

TEST_F(JoinFunctionalTest, JoinFullDequeVectorDefaultOutTest)
{
  QueryableDeque<Person> dequePeople(this->people.ToDeque());
  QueryableVector<Animal> vectorAnimals(this->animals.ToVector());

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
  QueryableList<Person> listPeople(this->people.ToList());
  QueryableDeque<Animal> dequeAnimals(this->animals.ToDeque());

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
  QueryableList<Person> listPeople(this->people.ToList());
  QueryableMultiSet<Animal> multiSetAnimals(this->animals.ToMultiSet());

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
  QueryableList<Person> listPeople(this->people.ToList());
  QueryableSet<Animal> setAnimals(this->animals.ToSet());

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

  // sets can remove duplicate values based on comparison of (!(a < b) && !(b < a))
  // need to remove duplicates freom expected in a similar way
  int index = 0;
  PersonAndPet previous;
  for (auto it = this->petOwners.begin(); it != this->petOwners.end();)
  {
    if (index++ != 0)
    {
      if (previous.GetAnimal().GetOwnerId() == (*it).GetAnimal().GetOwnerId())
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

  ASSERT_EQ(this->petOwners.size(), result->Count());

  for (int i = 0; i < result->Count(); i++)
  {
    ASSERT_TRUE(this->PetOwnerEqual(result->At(i), this->petOwners[i]));
  }
}

TEST_F(JoinFunctionalTest, JoinFullListVectorDefaultOutTest)
{
  QueryableList<Person> listPeople(this->people.ToList());
  QueryableVector<Animal> vectorAnimals(this->animals.ToVector());

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
  QueryableMultiSet<Person> multiSetPeople(this->people.ToMultiSet());
  QueryableDeque<Animal> dequeAnimals(this->animals.ToDeque());

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
  QueryableMultiSet<Person> multiSetPeople(this->people.ToMultiSet());
  QueryableList<Animal> listAnimals(this->animals.ToList());

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
  QueryableMultiSet<Person> multiSetPeople(this->people.ToMultiSet());
  QueryableSet<Animal> setAnimals(this->animals.ToSet());

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

  // sets can remove duplicate values based on comparison of (!(a < b) && !(b < a))
  // need to remove duplicates freom expected in a similar way
  int index = 0;
  PersonAndPet previous;
  for (auto it = this->petOwners.begin(); it != this->petOwners.end();)
  {
    if (index++ != 0)
    {
      if (previous.GetAnimal().GetOwnerId() == (*it).GetAnimal().GetOwnerId())
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

  ASSERT_EQ(this->petOwners.size(), result->Count());
  for (int i = 0; i < result->Count(); i++)
  {
    ASSERT_TRUE(this->PetOwnerEqual(result->At(i), this->petOwners[i]));
  }
}

TEST_F(JoinFunctionalTest, JoinFullMultiSetVectorDefaultOutTest)
{
  QueryableMultiSet<Person> multiSetPeople(this->people.ToMultiSet());
  QueryableVector<Animal> vectorAnimals(this->animals.ToVector());

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

// deque, list
// deque, multiset
// deque, set
// deque, vector
// list, deque
// list, multiset
// list, set
// list, vector
// multiset, deque
// multiset, list
// multiset, set
// multiset, vector
// set, deque
// set, list
// set, multiset
// set, vector
// vector, deque
// vector, list
// vector, multiset
// vector, set


// *** Test case to ensure compare is being used as out compare for sets

// THINGS TO TEST
// - TOut built in type without need for comparison
// - TOut class with less-than overload so comparison not needed
// - test different queryable type return types (every combination)
// - test collection different queryable type than caller  (every combination)
//
// - Where --> Join --> Where
