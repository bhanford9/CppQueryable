// #include <gtest/gtest.h>

// #include <algorithm>
// #include <array>
// #include <deque>
// #include <iostream>
// #include <list>
// #include <set>
// #include <string>
// #include <vector>

// #include "../../../DataStructures/Animal.hpp"
// #include "../../../DataStructures/AnimalLibrary.hpp"
// #include "../../../DataStructures/DogWalker.hpp"
// #include "../../../DataStructures/Gender.hpp"
// #include "../../../DataStructures/Person.hpp"
// #include "../../../DataStructures/PersonAndPet.hpp"
// #include "../../../DataStructures/PersonAndPetLibrary.hpp"
// #include "../../../DataStructures/PersonLibrary.hpp"
// #include "../../../DataStructures/Point.hpp"

// #include "../../../Queryable/QueryBuilder.hpp"
// #include "../../../Queryable/QueryableType.hpp"

// using namespace QueryBuilder;

// class JoinFunctionalTest : public ::testing::Test
// {
// protected:
//   PersonLibrary personLibrary;
//   AnimalLibrary animalLibrary;
//   InternalQueryable<Person> people;
//   InternalQueryable<Animal> animals;
//   std::vector<PersonAndPet> petOwners;
//   std::function<bool(PersonAndPet, PersonAndPet)> comparison =
//     [](PersonAndPet a, PersonAndPet b) -> bool { return a.GetPerson() < b.GetPerson(); };
//   typedef decltype(comparison) TComparison;
//   std::function<bool(Person, Person)> comparisonId =
//     [](Person a, Person b) -> bool { return a.GetId() < b.GetId(); };
//   typedef decltype(comparisonId) TComparisonId;

//   void SetUp() override
//   {
//     this->people = InternalQueryable<Person>(this->personLibrary.GetPeople());
//     this->animals = InternalQueryable<Animal>(this->animalLibrary.GetAnimals());
//     this->petOwners = PersonAndPetLibrary().GetPetOwners();
//   }

//   void TearDown() override {}

//   bool PersonEqual(Person a, Person b)
//   {
//     return
//       a.GetId() == b.GetId() &&
//       a.GetName() == b.GetName() &&
//       a.GetAge() == b.GetAge() &&
//       a.GetHeight() == b.GetHeight() &&
//       a.GetGender() == b.GetGender();
//   }

//   bool AnimalEqual(Animal a, Animal b)
//   {
//     return
//       a.GetId() == b.GetId() &&
//       a.GetOwnerId() == b.GetOwnerId() &&
//       a.GetName() == b.GetName() &&
//       a.GetAge() == b.GetAge() &&
//       a.GetGender() == b.GetGender();
//   }

//   bool PetOwnerEqual(PersonAndPet a, PersonAndPet b)
//   {
//     return
//       this->PersonEqual(a.GetPerson(), b.GetPerson()) &&
//       this->AnimalEqual(a.GetAnimal(), b.GetAnimal());
//   }

//   void RemovePetOwnerDuplicates()
//   {
//     // sets can remove duplicate values based on comparison of (!(a < b) && !(b < a))
//     // need to remove duplicates freom expected in a similar way
//     int index = 0;
//     PersonAndPet previous;
//     for (auto it = this->petOwners.begin(); it != this->petOwners.end();)
//     {
//       if (index++ != 0)
//       {
//         if (previous.GetPerson().GetName() == (*it).GetPerson().GetName())
//         {
//           this->petOwners.erase(it);
//         }
//         else
//         {
//           previous = *it;
//           it++;
//         }
//       }
//       else
//       {
//         previous = *it;
//         it++;
//       }
//     }
//   }

//   void RemovePersonDuplicates(std::vector<Person> & people)
//   {
//     int index = 0;
//     Person previous;
//     for (auto it = people.begin(); it != people.end();)
//     {
//       if (index++ != 0)
//       {
//         if (previous.GetId() == (*it).GetId())
//         {
//           people.erase(it);
//         }
//         else
//         {
//           previous = *it;
//           it++;
//         }
//       }
//       else
//       {
//         previous = *it;
//         it++;
//       }
//     }
//   }
// };

// TEST_F(JoinFunctionalTest, JoinUninitializedDequeTest)
// {
//   InternalQueryable<Person> people(QueryableType::Deque);
//   InternalQueryable<Animal> animals(QueryableType::Deque);
//   InternalQueryable<PersonAndPet> & petOwners =
//     people.Join<Animal, long, PersonAndPet>(
//       animals,
//       [](Person person) { return person.GetId(); },
//       [](Animal animal) { return animal.GetOwnerId(); },
//       [](Person person, Animal animal) { return PersonAndPet(person, animal); },
//       this->comparison);

//   ASSERT_EQ(0, petOwners.Count());
//   ASSERT_TRUE(petOwners.GetType() == QueryableType::Deque);
// }

// TEST_F(JoinFunctionalTest, JoinUninitializedListTest)
// {
//   InternalQueryable<Person> people(QueryableType::List);
//   InternalQueryable<Animal> animals(QueryableType::List);
//   InternalQueryable<PersonAndPet> & petOwners =
//     people.Join<Animal, long, PersonAndPet>(
//       animals,
//       [](Person person) { return person.GetId(); },
//       [](Animal animal) { return animal.GetOwnerId(); },
//       [](Person person, Animal animal) { return PersonAndPet(person, animal); },
//       this->comparison);

//   ASSERT_EQ(0, petOwners.Count());
//   ASSERT_TRUE(petOwners.GetType() == QueryableType::List);
// }

// TEST_F(JoinFunctionalTest, JoinUninitializedMultiSetTest)
// {
//   InternalQueryable<Person> people(QueryableType::MultiSet);
//   InternalQueryable<Animal> animals(QueryableType::MultiSet);
//   InternalQueryable<PersonAndPet> & petOwners =
//     people.Join<Animal, long, PersonAndPet>(
//       animals,
//       [](Person person) { return person.GetId(); },
//       [](Animal animal) { return animal.GetOwnerId(); },
//       [](Person person, Animal animal) { return PersonAndPet(person, animal); },
//       this->comparison);

//   ASSERT_EQ(0, petOwners.Count());
//   ASSERT_TRUE(petOwners.GetType() == QueryableType::MultiSet);
// }

// TEST_F(JoinFunctionalTest, JoinUninitializedSetTest)
// {
//   InternalQueryable<Person> people(QueryableType::Set);
//   InternalQueryable<Animal> animals(QueryableType::Set);
//   InternalQueryable<PersonAndPet> & petOwners =
//     people.Join<Animal, long, PersonAndPet>(
//       animals,
//       [](Person person) { return person.GetId(); },
//       [](Animal animal) { return animal.GetOwnerId(); },
//       [](Person person, Animal animal) { return PersonAndPet(person, animal); },
//       this->comparison);

//   ASSERT_EQ(0, petOwners.Count());
//   ASSERT_TRUE(petOwners.GetType() == QueryableType::Set);
// }

// TEST_F(JoinFunctionalTest, JoinUninitializedVectorTest)
// {
//   InternalQueryable<Person> people(QueryableType::Vector);
//   InternalQueryable<Animal> animals(QueryableType::Vector);
//   InternalQueryable<PersonAndPet> & petOwners =
//     people.Join<Animal, long, PersonAndPet>(
//       animals,
//       [](Person person) { return person.GetId(); },
//       [](Animal animal) { return animal.GetOwnerId(); },
//       [](Person person, Animal animal) { return PersonAndPet(person, animal); },
//       this->comparison);

//   ASSERT_EQ(0, petOwners.Count());
//   ASSERT_TRUE(petOwners.GetType() == QueryableType::Vector);
// }

// TEST_F(JoinFunctionalTest, JoinFullVectorVectorDefaultOutTest)
// {
//   InternalQueryable<PersonAndPet> & result =
//     this->people.Join<Animal, long, PersonAndPet>(
//       this->animals,
//       [](Person person) { return person.GetId(); },
//       [](Animal animal) { return animal.GetOwnerId(); },
//       [](Person person, Animal animal) { return PersonAndPet(person, animal); },
//       this->comparison);

//   ASSERT_TRUE(result.GetType() == QueryableType::Vector);
//   ASSERT_EQ(this->petOwners.size(), result.Count());

//   for (int i = 0; i < result.Count(); i++)
//   {
//     ASSERT_TRUE(this->PetOwnerEqual(result.At(i), this->petOwners[i]));
//   }
// }

// TEST_F(JoinFunctionalTest, JoinFullDequeListDefaultOutTest)
// {
//   InternalQueryable<Person> dequePeople(this->people.ToDeque());
//   InternalQueryable<Animal> listAnimals(this->animals.ToList());

//   InternalQueryable<PersonAndPet> & result =
//     dequePeople.Join<Animal, long, PersonAndPet>(
//       listAnimals,
//       [](Person person) { return person.GetId(); },
//       [](Animal animal) { return animal.GetOwnerId(); },
//       [](Person person, Animal animal) { return PersonAndPet(person, animal); },
//       this->comparison);

//   ASSERT_TRUE(result.GetType() == QueryableType::Deque);
//   ASSERT_EQ(this->petOwners.size(), result.Count());

//   for (int i = 0; i < result.Count(); i++)
//   {
//     ASSERT_TRUE(this->PetOwnerEqual(result.At(i), this->petOwners[i]));
//   }
// }

// TEST_F(JoinFunctionalTest, JoinFullDequeMultiSetDefaultOutTest)
// {
//   InternalQueryable<Person> dequePeople(this->people.ToDeque());
//   InternalQueryable<Animal> multiSetAnimals(this->animals.ToMultiSet());

//   InternalQueryable<PersonAndPet> & result =
//     dequePeople.Join<Animal, long, PersonAndPet>(
//       multiSetAnimals,
//       [](Person person) { return person.GetId(); },
//       [](Animal animal) { return animal.GetOwnerId(); },
//       [](Person person, Animal animal) { return PersonAndPet(person, animal); },
//       this->comparison);


//   ASSERT_TRUE(result.GetType() == QueryableType::Deque);
//   ASSERT_EQ(this->petOwners.size(), result.Count());

//   // Join orders by ID, but sets are naturally ordered as well,
//   // so the multiset gets ordered by name by default as well
//   // which can make the output order different than the order of
//   // added items
//   std::sort(
//     this->petOwners.begin(),
//     this->petOwners.end(),
//     [](PersonAndPet p1, PersonAndPet p2)
//     {
//       return p1.GetAnimal().GetOwnerId() <= p2.GetAnimal().GetOwnerId() &&
//         p1.GetAnimal().GetName() < p2.GetAnimal().GetName();
//     });

//   for (int i = 0; i < result.Count(); i++)
//   {
//     ASSERT_TRUE(this->PetOwnerEqual(result.At(i), this->petOwners[i]));
//   }
// }

// TEST_F(JoinFunctionalTest, JoinFullDequeSetDefaultOutTest)
// {
//   InternalQueryable<Person> dequePeople(this->people.ToDeque());
//   InternalQueryable<Animal> setAnimals(this->animals.ToSet());

//   InternalQueryable<PersonAndPet> & result =
//     dequePeople.Join<Animal, long, PersonAndPet>(
//       setAnimals,
//       [](Person person) { return person.GetId(); },
//       [](Animal animal) { return animal.GetOwnerId(); },
//       [](Person person, Animal animal) { return PersonAndPet(person, animal); },
//       this->comparison);


//   ASSERT_TRUE(result.GetType() == QueryableType::Deque);

//   // Join orders by ID, but sets are naturally ordered as well,
//   // so the set gets ordered by name by default as well
//   // which can make the output order different than the order of
//   // added items
//   std::sort(
//     this->petOwners.begin(),
//     this->petOwners.end(),
//     [](PersonAndPet p1, PersonAndPet p2)
//     {
//       return p1.GetAnimal().GetOwnerId() <= p2.GetAnimal().GetOwnerId() &&
//         p1.GetAnimal().GetName() < p2.GetAnimal().GetName();
//     });

//   this->RemovePetOwnerDuplicates();

//   ASSERT_EQ(this->petOwners.size(), result.Count());

//   for (int i = 0; i < result.Count(); i++)
//   {
//     ASSERT_TRUE(this->PetOwnerEqual(result.At(i), this->petOwners[i]));
//   }
// }

// TEST_F(JoinFunctionalTest, JoinFullDequeVectorDefaultOutTest)
// {
//   InternalQueryable<Person> dequePeople(this->people.ToDeque());
//   InternalQueryable<Animal> vectorAnimals(this->animals.ToVector());

//   InternalQueryable<PersonAndPet> & result =
//     dequePeople.Join<Animal, long, PersonAndPet>(
//       vectorAnimals,
//       [](Person person) { return person.GetId(); },
//       [](Animal animal) { return animal.GetOwnerId(); },
//       [](Person person, Animal animal) { return PersonAndPet(person, animal); },
//       this->comparison);


//   ASSERT_TRUE(result.GetType() == QueryableType::Deque);
//   ASSERT_EQ(this->petOwners.size(), result.Count());

//   for (int i = 0; i < result.Count(); i++)
//   {
//     ASSERT_TRUE(this->PetOwnerEqual(result.At(i), this->petOwners[i]));
//   }
// }

// TEST_F(JoinFunctionalTest, JoinFullListDequeDefaultOutTest)
// {
//   InternalQueryable<Person> listPeople(this->people.ToList());
//   InternalQueryable<Animal> dequeAnimals(this->animals.ToDeque());

//   InternalQueryable<PersonAndPet> & result =
//     listPeople.Join<Animal, long, PersonAndPet>(
//       dequeAnimals,
//       [](Person person) { return person.GetId(); },
//       [](Animal animal) { return animal.GetOwnerId(); },
//       [](Person person, Animal animal) { return PersonAndPet(person, animal); },
//       this->comparison);


//   ASSERT_TRUE(result.GetType() == QueryableType::List);
//   ASSERT_EQ(this->petOwners.size(), result.Count());

//   for (int i = 0; i < result.Count(); i++)
//   {
//     ASSERT_TRUE(this->PetOwnerEqual(result.At(i), this->petOwners[i]));
//   }
// }

// TEST_F(JoinFunctionalTest, JoinFullListMultiSetDefaultOutTest)
// {
//   InternalQueryable<Person> listPeople(this->people.ToList());
//   InternalQueryable<Animal> multiSetAnimals(this->animals.ToMultiSet());

//   InternalQueryable<PersonAndPet> & result =
//     listPeople.Join<Animal, long, PersonAndPet>(
//       multiSetAnimals,
//       [](Person person) { return person.GetId(); },
//       [](Animal animal) { return animal.GetOwnerId(); },
//       [](Person person, Animal animal) { return PersonAndPet(person, animal); },
//       this->comparison);


//   ASSERT_TRUE(result.GetType() == QueryableType::List);
//   ASSERT_EQ(this->petOwners.size(), result.Count());

//   // Join orders by ID, but sets are naturally ordered as well,
//   // so the multiset gets ordered by name by default as well
//   // which can make the output order different than the order of
//   // added items
//   std::sort(
//     this->petOwners.begin(),
//     this->petOwners.end(),
//     [](PersonAndPet p1, PersonAndPet p2)
//     {
//       return p1.GetAnimal().GetOwnerId() <= p2.GetAnimal().GetOwnerId() &&
//         p1.GetAnimal().GetName() < p2.GetAnimal().GetName();
//     });

//   for (int i = 0; i < result.Count(); i++)
//   {
//     ASSERT_TRUE(this->PetOwnerEqual(result.At(i), this->petOwners[i]));
//   }
// }

// TEST_F(JoinFunctionalTest, JoinFullListSetDefaultOutTest)
// {
//   InternalQueryable<Person> listPeople(this->people.ToList());
//   InternalQueryable<Animal> setAnimals(this->animals.ToSet());

//   InternalQueryable<PersonAndPet> & result =
//     listPeople.Join<Animal, long, PersonAndPet>(
//       setAnimals,
//       [](Person person) { return person.GetId(); },
//       [](Animal animal) { return animal.GetOwnerId(); },
//       [](Person person, Animal animal) { return PersonAndPet(person, animal); },
//       this->comparison);


//   ASSERT_TRUE(result.GetType() == QueryableType::List);

//   // Join orders by ID, but sets are naturally ordered as well,
//   // so the set gets ordered by name by default as well
//   // which can make the output order different than the order of
//   // added items
//   std::sort(
//     this->petOwners.begin(),
//     this->petOwners.end(),
//     [](PersonAndPet p1, PersonAndPet p2)
//     {
//       return p1.GetAnimal().GetOwnerId() <= p2.GetAnimal().GetOwnerId() &&
//         p1.GetAnimal().GetName() < p2.GetAnimal().GetName();
//     });

//   this->RemovePetOwnerDuplicates();

//   ASSERT_EQ(this->petOwners.size(), result.Count());

//   for (int i = 0; i < result.Count(); i++)
//   {
//     ASSERT_TRUE(this->PetOwnerEqual(result.At(i), this->petOwners[i]));
//   }
// }

// TEST_F(JoinFunctionalTest, JoinFullListVectorDefaultOutTest)
// {
//   InternalQueryable<Person> listPeople(this->people.ToList());
//   InternalQueryable<Animal> vectorAnimals(this->animals.ToVector());

//   InternalQueryable<PersonAndPet> & result =
//     listPeople.Join<Animal, long, PersonAndPet>(
//       vectorAnimals,
//       [](Person person) { return person.GetId(); },
//       [](Animal animal) { return animal.GetOwnerId(); },
//       [](Person person, Animal animal) { return PersonAndPet(person, animal); },
//       this->comparison);


//   ASSERT_TRUE(result.GetType() == QueryableType::List);
//   ASSERT_EQ(this->petOwners.size(), result.Count());

//   for (int i = 0; i < result.Count(); i++)
//   {
//     ASSERT_TRUE(this->PetOwnerEqual(result.At(i), this->petOwners[i]));
//   }
// }

// TEST_F(JoinFunctionalTest, JoinFullMultiSetDequeDefaultOutTest)
// {
//   InternalQueryable<Person> multiSetPeople(this->people.ToMultiSet());
//   InternalQueryable<Animal> dequeAnimals(this->animals.ToDeque());

//   InternalQueryable<PersonAndPet> & result =
//     multiSetPeople.Join<Animal, long, PersonAndPet>(
//       dequeAnimals,
//       [](Person person) { return person.GetId(); },
//       [](Animal animal) { return animal.GetOwnerId(); },
//       [](Person person, Animal animal) { return PersonAndPet(person, animal); },
//       this->comparison);


//   ASSERT_TRUE(result.GetType() == QueryableType::MultiSet);
//   ASSERT_EQ(this->petOwners.size(), result.Count());

//   // Join orders by ID, but sets are naturally ordered as well and the output
//   // comparison function is telling the multiset to be ordered by the person's
//   // name
//   std::sort(
//     this->petOwners.begin(),
//     this->petOwners.end(),
//     [](PersonAndPet p1, PersonAndPet p2)
//     {
//       return p1.GetPerson().GetName() < p2.GetPerson().GetName();
//     });

//   for (int i = 0; i < result.Count(); i++)
//   {
//     ASSERT_TRUE(this->PetOwnerEqual(result.At(i), this->petOwners[i]));
//   }
// }

// TEST_F(JoinFunctionalTest, JoinFullMultiSetListDefaultOutTest)
// {
//   InternalQueryable<Person> multiSetPeople(this->people.ToMultiSet());
//   InternalQueryable<Animal> listAnimals(this->animals.ToList());

//   InternalQueryable<PersonAndPet> & result =
//     multiSetPeople.Join<Animal, long, PersonAndPet>(
//       listAnimals,
//       [](Person person) { return person.GetId(); },
//       [](Animal animal) { return animal.GetOwnerId(); },
//       [](Person person, Animal animal) { return PersonAndPet(person, animal); },
//       this->comparison);


//   ASSERT_TRUE(result.GetType() == QueryableType::MultiSet);
//   ASSERT_EQ(this->petOwners.size(), result.Count());

//   // Join orders by ID, but sets are naturally ordered as well and the output
//   // comparison function is telling the multiset to be ordered by the person's
//   // name
//   std::sort(
//     this->petOwners.begin(),
//     this->petOwners.end(),
//     [](PersonAndPet p1, PersonAndPet p2)
//     {
//       return p1.GetPerson().GetName() < p2.GetPerson().GetName();
//     });

//   for (int i = 0; i < result.Count(); i++)
//   {
//     ASSERT_TRUE(this->PetOwnerEqual(result.At(i), this->petOwners[i]));
//   }
// }

// TEST_F(JoinFunctionalTest, JoinFullMultiSetSetDefaultOutTest)
// {
//   InternalQueryable<Person> multiSetPeople(this->people.ToMultiSet());
//   InternalQueryable<Animal> setAnimals(this->animals.ToSet());

//   InternalQueryable<PersonAndPet> & result =
//     multiSetPeople.Join<Animal, long, PersonAndPet>(
//       setAnimals,
//       [](Person person) { return person.GetId(); },
//       [](Animal animal) { return animal.GetOwnerId(); },
//       [](Person person, Animal animal) { return PersonAndPet(person, animal); },
//       this->comparison);


//   ASSERT_TRUE(result.GetType() == QueryableType::MultiSet);

//   // Join orders by ID, but sets are naturally ordered as well and the output
//   // comparison function is telling the multiset to be ordered by the person's
//   // name
//   std::sort(
//     this->petOwners.begin(),
//     this->petOwners.end(),
//     [](PersonAndPet p1, PersonAndPet p2)
//     {
//       if (p1.GetAnimal().GetOwnerId() == p2.GetAnimal().GetOwnerId())
//       {
//         return p1.GetAnimal().GetName() < p2.GetAnimal().GetName();
//       }
//       return p1.GetPerson().GetName() <= p2.GetPerson().GetName();
//     });

//   this->RemovePetOwnerDuplicates();

//   ASSERT_EQ(this->petOwners.size(), result.Count());
//   for (int i = 0; i < result.Count(); i++)
//   {
//     ASSERT_TRUE(this->PetOwnerEqual(result.At(i), this->petOwners[i]));
//   }
// }

// TEST_F(JoinFunctionalTest, JoinFullMultiSetVectorDefaultOutTest)
// {
//   InternalQueryable<Person> multiSetPeople(this->people.ToMultiSet());
//   InternalQueryable<Animal> vectorAnimals(this->animals.ToVector());

//   InternalQueryable<PersonAndPet> & result =
//     multiSetPeople.Join<Animal, long, PersonAndPet>(
//       vectorAnimals,
//       [](Person person) { return person.GetId(); },
//       [](Animal animal) { return animal.GetOwnerId(); },
//       [](Person person, Animal animal) { return PersonAndPet(person, animal); },
//       this->comparison);


//   ASSERT_TRUE(result.GetType() == QueryableType::MultiSet);
//   ASSERT_EQ(this->petOwners.size(), result.Count());

//   // Join orders by ID, but sets are naturally ordered as well and the output
//   // comparison function is telling the multiset to be ordered by the person's
//   // name
//   std::sort(
//     this->petOwners.begin(),
//     this->petOwners.end(),
//     [](PersonAndPet p1, PersonAndPet p2)
//     {
//       return p1.GetPerson().GetName() < p2.GetPerson().GetName();
//     });

//   for (int i = 0; i < result.Count(); i++)
//   {
//     ASSERT_TRUE(this->PetOwnerEqual(result.At(i), this->petOwners[i]));
//   }
// }

// TEST_F(JoinFunctionalTest, JoinFullSetDequeDefaultOutTest)
// {
//   InternalQueryable<Person> setPeople(this->people.ToSet());
//   InternalQueryable<Animal> dequeAnimals(this->animals.ToDeque());

//   InternalQueryable<PersonAndPet> & result =
//     setPeople.Join<Animal, long, PersonAndPet>(
//       dequeAnimals,
//       [](Person person) { return person.GetId(); },
//       [](Animal animal) { return animal.GetOwnerId(); },
//       [](Person person, Animal animal) { return PersonAndPet(person, animal); },
//       this->comparison);


//   ASSERT_TRUE(result.GetType() == QueryableType::Set);

//   // Join orders by ID, but sets are naturally ordered as well,
//   // so the set gets ordered by name by default as well
//   // which can make the output order different than the order of
//   // added items
//   std::sort(
//     this->petOwners.begin(),
//     this->petOwners.end(),
//     [](PersonAndPet p1, PersonAndPet p2)
//     {
//       return p1.GetPerson() < p2.GetPerson();
//     });

//   this->RemovePetOwnerDuplicates();

//   ASSERT_EQ(this->petOwners.size(), result.Count());

//   for (int i = 0; i < result.Count(); i++)
//   {
//     ASSERT_TRUE(this->PetOwnerEqual(result.At(i), this->petOwners[i]));
//   }
// }

// TEST_F(JoinFunctionalTest, JoinFullSetListDefaultOutTest)
// {
//   InternalQueryable<Person> setPeople(this->people.ToSet());
//   InternalQueryable<Animal> listAnimals(this->animals.ToList());

//   InternalQueryable<PersonAndPet> & result =
//     setPeople.Join<Animal, long, PersonAndPet>(
//       listAnimals,
//       [](Person person) { return person.GetId(); },
//       [](Animal animal) { return animal.GetOwnerId(); },
//       [](Person person, Animal animal) { return PersonAndPet(person, animal); },
//       this->comparison);


//   ASSERT_TRUE(result.GetType() == QueryableType::Set);

//   // Join orders by ID, but sets are naturally ordered as well,
//   // so the set gets ordered by name by default as well
//   // which can make the output order different than the order of
//   // added items
//   std::sort(
//     this->petOwners.begin(),
//     this->petOwners.end(),
//     [](PersonAndPet p1, PersonAndPet p2)
//     {
//       return p1.GetPerson() < p2.GetPerson();
//     });

//   this->RemovePetOwnerDuplicates();

//   ASSERT_EQ(this->petOwners.size(), result.Count());

//   for (int i = 0; i < result.Count(); i++)
//   {
//     ASSERT_TRUE(this->PetOwnerEqual(result.At(i), this->petOwners[i]));
//   }
// }

// TEST_F(JoinFunctionalTest, JoinFullSetMultiSetDefaultOutTest)
// {
//   InternalQueryable<Person> setPeople(this->people.ToSet());
//   InternalQueryable<Animal> multiSetAnimals(this->animals.ToMultiSet());

//   InternalQueryable<PersonAndPet> & result =
//     setPeople.Join<Animal, long, PersonAndPet>(
//       multiSetAnimals,
//       [](Person person) { return person.GetId(); },
//       [](Animal animal) { return animal.GetOwnerId(); },
//       [](Person person, Animal animal) { return PersonAndPet(person, animal); },
//       this->comparison);


//   ASSERT_TRUE(result.GetType() == QueryableType::Set);

//   // Join orders by ID, but sets are naturally ordered as well,
//   // so the set gets ordered by name by default as well
//   // which can make the output order different than the order of
//   // added items
//   std::sort(
//     this->petOwners.begin(),
//     this->petOwners.end(),
//     [](PersonAndPet p1, PersonAndPet p2)
//     {
//       if (p1.GetAnimal().GetOwnerId() == p2.GetAnimal().GetOwnerId())
//       {
//         return p1.GetAnimal().GetName() < p2.GetAnimal().GetName();
//       }
//       return p1.GetPerson().GetName() < p2.GetPerson().GetName();
//     });

//   this->RemovePetOwnerDuplicates();

//   ASSERT_EQ(this->petOwners.size(), result.Count());

//   for (int i = 0; i < result.Count(); i++)
//   {
//     ASSERT_TRUE(this->PetOwnerEqual(result.At(i), this->petOwners[i]));
//   }
// }

// TEST_F(JoinFunctionalTest, JoinFullSetVectorDefaultOutTest)
// {
//   InternalQueryable<Person> setPeople(this->people.ToSet());
//   InternalQueryable<Animal> vectorAnimals(this->animals.ToVector());

//   InternalQueryable<PersonAndPet> & result =
//     setPeople.Join<Animal, long, PersonAndPet>(
//       vectorAnimals,
//       [](Person person) { return person.GetId(); },
//       [](Animal animal) { return animal.GetOwnerId(); },
//       [](Person person, Animal animal) { return PersonAndPet(person, animal); },
//       this->comparison);


//   ASSERT_TRUE(result.GetType() == QueryableType::Set);

//   // Join orders by ID, but sets are naturally ordered as well,
//   // so the set gets ordered by name by default as well
//   // which can make the output order different than the order of
//   // added items
//   std::sort(
//     this->petOwners.begin(),
//     this->petOwners.end(),
//     [](PersonAndPet p1, PersonAndPet p2)
//     {
//       return p1.GetPerson() < p2.GetPerson();
//     });

//   this->RemovePetOwnerDuplicates();

//   ASSERT_EQ(this->petOwners.size(), result.Count());

//   for (int i = 0; i < result.Count(); i++)
//   {
//     ASSERT_TRUE(this->PetOwnerEqual(result.At(i), this->petOwners[i]));
//   }
// }

// TEST_F(JoinFunctionalTest, JoinFullVectorDequeDefaultOutTest)
// {
//   InternalQueryable<Person> vectorPeople(this->people.ToVector());
//   InternalQueryable<Animal> dequeAnimals(this->animals.ToDeque());

//   InternalQueryable<PersonAndPet> & result =
//     vectorPeople.Join<Animal, long, PersonAndPet>(
//       dequeAnimals,
//       [](Person person) { return person.GetId(); },
//       [](Animal animal) { return animal.GetOwnerId(); },
//       [](Person person, Animal animal) { return PersonAndPet(person, animal); },
//       this->comparison);


//   ASSERT_TRUE(result.GetType() == QueryableType::Vector);
//   ASSERT_EQ(this->petOwners.size(), result.Count());

//   for (int i = 0; i < result.Count(); i++)
//   {
//     ASSERT_TRUE(this->PetOwnerEqual(result.At(i), this->petOwners[i]));
//   }
// }

// TEST_F(JoinFunctionalTest, JoinFullVectorListDefaultOutTest)
// {
//   InternalQueryable<Person> vectorPeople(this->people.ToVector());
//   InternalQueryable<Animal> listAnimals(this->animals.ToList());

//   InternalQueryable<PersonAndPet> & result =
//     vectorPeople.Join<Animal, long, PersonAndPet>(
//       listAnimals,
//       [](Person person) { return person.GetId(); },
//       [](Animal animal) { return animal.GetOwnerId(); },
//       [](Person person, Animal animal) { return PersonAndPet(person, animal); },
//       this->comparison);


//   ASSERT_TRUE(result.GetType() == QueryableType::Vector);
//   ASSERT_EQ(this->petOwners.size(), result.Count());

//   for (int i = 0; i < result.Count(); i++)
//   {
//     ASSERT_TRUE(this->PetOwnerEqual(result.At(i), this->petOwners[i]));
//   }
// }

// TEST_F(JoinFunctionalTest, JoinFullVectorMultiSetDefaultOutTest)
// {
//   InternalQueryable<Person> vectorPeople(this->people.ToVector());
//   InternalQueryable<Animal> multiSetAnimals(this->animals.ToMultiSet());

//   InternalQueryable<PersonAndPet> & result =
//     vectorPeople.Join<Animal, long, PersonAndPet>(
//       multiSetAnimals,
//       [](Person person) { return person.GetId(); },
//       [](Animal animal) { return animal.GetOwnerId(); },
//       [](Person person, Animal animal) { return PersonAndPet(person, animal); },
//       this->comparison);


//   ASSERT_TRUE(result.GetType() == QueryableType::Vector);
//   ASSERT_EQ(this->petOwners.size(), result.Count());

//   // Join orders by ID, but sets are naturally ordered as well,
//   // so the multiset gets ordered by name by default as well
//   // which can make the output order different than the order of
//   // added items
//   std::sort(
//     this->petOwners.begin(),
//     this->petOwners.end(),
//     [](PersonAndPet p1, PersonAndPet p2)
//     {
//       return p1.GetAnimal().GetOwnerId() <= p2.GetAnimal().GetOwnerId() &&
//         p1.GetAnimal().GetName() < p2.GetAnimal().GetName();
//     });

//   for (int i = 0; i < result.Count(); i++)
//   {
//     ASSERT_TRUE(this->PetOwnerEqual(result.At(i), this->petOwners[i]));
//   }
// }

// TEST_F(JoinFunctionalTest, JoinFullVectorSetDefaultOutTest)
// {
//   InternalQueryable<Person> vectorPeople(this->people.ToVector());
//   InternalQueryable<Animal> setAnimals(this->animals.ToSet());

//   InternalQueryable<PersonAndPet> & result =
//     vectorPeople.Join<Animal, long, PersonAndPet>(
//       setAnimals,
//       [](Person person) { return person.GetId(); },
//       [](Animal animal) { return animal.GetOwnerId(); },
//       [](Person person, Animal animal) { return PersonAndPet(person, animal); },
//       this->comparison);


//   ASSERT_TRUE(result.GetType() == QueryableType::Vector);

//   // Join orders by ID, but sets are naturally ordered as well,
//   // so the set gets ordered by name by default as well
//   // which can make the output order different than the order of
//   // added items
//   std::sort(
//     this->petOwners.begin(),
//     this->petOwners.end(),
//     [](PersonAndPet p1, PersonAndPet p2)
//     {
//       return p1.GetAnimal().GetOwnerId() <= p2.GetAnimal().GetOwnerId() &&
//         p1.GetAnimal().GetName() < p2.GetAnimal().GetName();
//     });

//   this->RemovePetOwnerDuplicates();

//   ASSERT_EQ(this->petOwners.size(), result.Count());

//   for (int i = 0; i < result.Count(); i++)
//   {
//     ASSERT_TRUE(this->PetOwnerEqual(result.At(i), this->petOwners[i]));
//   }
// }

// TEST_F(JoinFunctionalTest, JoinFullDequeListListOutTest)
// {
//   InternalQueryable<Person> dequePeople(this->people.ToDeque());
//   InternalQueryable<Animal> listAnimals(this->animals.ToList());

//   InternalQueryable<PersonAndPet> & result =
//     dequePeople.Join<Animal, long, PersonAndPet>(
//       listAnimals,
//       [](Person person) { return person.GetId(); },
//       [](Animal animal) { return animal.GetOwnerId(); },
//       [](Person person, Animal animal) { return PersonAndPet(person, animal); },
//       this->comparison,
//       QueryableType::List);


//   ASSERT_TRUE(result.GetType() == QueryableType::List);
//   ASSERT_EQ(this->petOwners.size(), result.Count());

//   for (int i = 0; i < result.Count(); i++)
//   {
//     ASSERT_TRUE(this->PetOwnerEqual(result.At(i), this->petOwners[i]));
//   }
// }

// TEST_F(JoinFunctionalTest, JoinFullDequeListMultiSetOutTest)
// {
//   InternalQueryable<Person> dequePeople(this->people.ToDeque());
//   InternalQueryable<Animal> listAnimals(this->animals.ToList());

//   InternalQueryable<PersonAndPet> & result =
//     dequePeople.Join<Animal, long, PersonAndPet>(
//       listAnimals,
//       [](Person person) { return person.GetId(); },
//       [](Animal animal) { return animal.GetOwnerId(); },
//       [](Person person, Animal animal) { return PersonAndPet(person, animal); },
//       this->comparison,
//       QueryableType::MultiSet);


//   ASSERT_TRUE(result.GetType() == QueryableType::MultiSet);
//   ASSERT_EQ(this->petOwners.size(), result.Count());

//   std::sort(
//     this->petOwners.begin(),
//     this->petOwners.end(),
//     [](PersonAndPet p1, PersonAndPet p2)
//     {
//       return p1.GetPerson() < p2.GetPerson();
//     });

//   for (int i = 0; i < result.Count(); i++)
//   {
//     ASSERT_TRUE(this->PetOwnerEqual(result.At(i), this->petOwners[i]));
//   }
// }

// TEST_F(JoinFunctionalTest, JoinFullDequeListSetOutTest)
// {
//   InternalQueryable<Person> dequePeople(this->people.ToDeque());
//   InternalQueryable<Animal> listAnimals(this->animals.ToList());

//   InternalQueryable<PersonAndPet> & result =
//     dequePeople.Join<Animal, long, PersonAndPet>(
//       listAnimals,
//       [](Person person) { return person.GetId(); },
//       [](Animal animal) { return animal.GetOwnerId(); },
//       [](Person person, Animal animal) { return PersonAndPet(person, animal); },
//       this->comparison,
//       QueryableType::Set);


//   ASSERT_TRUE(result.GetType() == QueryableType::Set);

//   std::sort(
//     this->petOwners.begin(),
//     this->petOwners.end(),
//     [](PersonAndPet p1, PersonAndPet p2)
//     {
//       return p1.GetPerson() < p2.GetPerson();
//     });

//   this->RemovePetOwnerDuplicates();

//   ASSERT_EQ(this->petOwners.size(), result.Count());

//   for (int i = 0; i < result.Count(); i++)
//   {
//     ASSERT_TRUE(this->PetOwnerEqual(result.At(i), this->petOwners[i]));
//   }
// }

// TEST_F(JoinFunctionalTest, DefaultOutComparisonTest)
// {
//   double expectedX = 9;
//   double expectedY = 10;

//   InternalQueryable<Person> dequePeople(this->people.ToDeque());
//   InternalQueryable<Animal> setAnimals(this->animals.ToSet());

//   // Testing that supplying the comparison type is not necessary when the default
//   //   comparison for a class can be used.
//   // This is more likely the common use case and it is much more convecient to
//   //   only have to deal with 3 type parameters and 4 variable parameters
//   InternalQueryable<Point> & result =
//     dequePeople.Join<Animal, long, Point>(
//       setAnimals,
//       [](Person person) { return person.GetId(); },
//       [](Animal animal) { return animal.GetOwnerId(); },
//       [&](Person person, Animal animal) { return Point(expectedX, expectedY); },
//       [](Point a, Point b) { return a < b; });

//   ASSERT_TRUE(result.Count() > 0);

//   result.ForEach([&](Point p)
//   {
//     ASSERT_EQ(expectedX, p.X);
//     ASSERT_EQ(expectedY, p.Y);
//   });
// }

// TEST_F(JoinFunctionalTest, PassedInCompareOverwritesDefaultTest)
// {
//   // person is ordered by name by default
//   // passing in an ID comparison should overwrite this
//   InternalQueryable<Person> setPeople(this->people.ToSet());
//   InternalQueryable<Animal> listAnimals(this->animals.ToList());

//   InternalQueryable<Person> & result =
//     setPeople.Join<Animal, long, Person>(
//       listAnimals,
//       [](Person person) { return person.GetId(); },
//       [](Animal animal) { return animal.GetOwnerId(); },
//       [](Person person, Animal animal) { return person; },
//       this->comparisonId);

//   ASSERT_TRUE(result.GetType() == QueryableType::Set);

//   std::vector<Person> sortedPeople;
//   this->animals.ForEach([&](Animal a)
//   {
//     if (this->people.Any([&](Person p) { return p.GetId() == a.GetOwnerId(); }))
//       sortedPeople.push_back(this->people.First([&](Person p) { return p.GetId() == a.GetOwnerId(); } ));
//   });
//   std::sort(sortedPeople.begin(), sortedPeople.end(), this->comparisonId);

//   this->RemovePersonDuplicates(sortedPeople);

//   ASSERT_EQ(sortedPeople.size(), result.Count());

//   for (int i = 0; i < result.Count(); i++)
//   {
//     ASSERT_TRUE(result.At(i).GetId() == sortedPeople[i].GetId());
//   }
// }

// TEST_F(JoinFunctionalTest, WhereJoinWhereTest)
// {
//   InternalQueryable<Person> dequePeople(this->people.ToDeque());
//   InternalQueryable<Animal> listAnimals(this->animals.ToList());

//   InternalQueryable<DogWalker> & result =
//     dequePeople
//       .Where([](Person p) { return p.GetId() >= 2 && p.GetId() <= 5; })
//       .Join<Animal, long, DogWalker>(
//         listAnimals,
//         [](Person person) { return person.GetId(); },
//         [](Animal animal) { return animal.GetOwnerId(); },
//         [](Person person, Animal animal) { return DogWalker(person, animal); },
//         this->comparisonId)
//       .Where([](DogWalker dw) { return dw.GetId() % 2 == 0; });

//   int expectedCount = 0;
//   this->animals.ForEach([&](Animal a) { if (a.GetOwnerId() >= 2 && a.GetOwnerId() <= 5 && a.GetOwnerId() % 2 == 0) expectedCount++; });

//   ASSERT_TRUE(expectedCount > 0);
//   ASSERT_EQ(expectedCount, result.Count());

//   result.ForEach([](DogWalker dw) { ASSERT_TRUE(dw.GetId() == 2 || dw.GetId() == 4); });
// }
