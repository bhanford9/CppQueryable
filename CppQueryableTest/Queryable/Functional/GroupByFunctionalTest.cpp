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
// #include "../../../Queryable/Utilities/Group.hpp"

// using namespace QueryBuilder;

// class GroupByFunctionalTest : public ::testing::Test
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

//   typedef Group<Gender, Person> TGenderPerson;

//   void SetUp() override
//   {
//     this->people = InternalQueryable<Person>(this->personLibrary.GetPeople());
//     this->animals = InternalQueryable<Animal>(this->animalLibrary.GetAnimals());
//     this->petOwners = PersonAndPetLibrary().GetPetOwners();
//   }

//   void TearDown() override {}
// };

// TEST_F(GroupByFunctionalTest, DequeDefaultsTest)
// {
//   InternalQueryable<TGenderPerson> genderGroups = this->people.ToQueryableDeque()
//     .GroupBy<Gender>([](Person p) { return p.GetGender(); });
//   InternalQueryable<Person> males = this->people
//     .WhereCopy([](Person p) { return p.GetGender() == Gender::Male; });
//   InternalQueryable<Person> females = this->people
//     .WhereCopy([](Person p) { return p.GetGender() == Gender::Female; });

//   ASSERT_EQ(2, genderGroups.Count());
//   ASSERT_TRUE(genderGroups.At(0).GetKey() == Gender::Male);
//   ASSERT_TRUE(genderGroups.At(1).GetKey() == Gender::Female);

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

// TEST_F(GroupByFunctionalTest, ListDefaultsTest)
// {
//   InternalQueryable<TGenderPerson> genderGroups = this->people.ToQueryableList()
//     .GroupBy<Gender>([](Person p) { return p.GetGender(); });
//   InternalQueryable<Person> males = this->people
//     .WhereCopy([](Person p) { return p.GetGender() == Gender::Male; });
//   InternalQueryable<Person> females = this->people
//     .WhereCopy([](Person p) { return p.GetGender() == Gender::Female; });

//   ASSERT_EQ(2, genderGroups.Count());
//   ASSERT_TRUE(genderGroups.At(0).GetKey() == Gender::Male);
//   ASSERT_TRUE(genderGroups.At(1).GetKey() == Gender::Female);

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
//   InternalQueryable<TGenderPerson>  genderGroups = this->people.ToQueryableMultiSet()
//     .GroupBy<Gender>([](Person p) { return p.GetGender(); });
//   InternalQueryable<Person> males = this->people
//     .WhereCopy([](Person p) { return p.GetGender() == Gender::Male; });
//   males.Sort();
//   InternalQueryable<Person> females = this->people
//     .WhereCopy([](Person p) { return p.GetGender() == Gender::Female; });
//   females.Sort();

//   ASSERT_EQ(2, genderGroups.Count());
//   ASSERT_TRUE(genderGroups.At(0).GetKey() == Gender::Male);
//   ASSERT_TRUE(genderGroups.At(1).GetKey() == Gender::Female);

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

// TEST_F(GroupByFunctionalTest, SetDefaultsTest)
// {
//   InternalQueryable<TGenderPerson>  genderGroups = this->people.ToQueryableSet()
//     .GroupBy<Gender>([](Person p) { return p.GetGender(); });
//   InternalQueryable<Person> males = this->people
//     .WhereCopy([](Person p) { return p.GetGender() == Gender::Male; });
//   males = males.ToQueryableSet();
//   InternalQueryable<Person> females = this->people
//     .WhereCopy([](Person p) { return p.GetGender() == Gender::Female; });
//   females = females.ToQueryableSet();

//   ASSERT_EQ(2, genderGroups.Count());
//   ASSERT_TRUE(genderGroups.At(0).GetKey() == Gender::Male);
//   ASSERT_TRUE(genderGroups.At(1).GetKey() == Gender::Female);

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

// TEST_F(GroupByFunctionalTest, VectorDefaultsTest)
// {
//   InternalQueryable<TGenderPerson>  genderGroups = this->people
//     .GroupBy<Gender>([](Person p) { return p.GetGender(); });
//   InternalQueryable<Person> males = this->people
//     .WhereCopy([](Person p) { return p.GetGender() == Gender::Male; });
//   InternalQueryable<Person> females = this->people
//     .WhereCopy([](Person p) { return p.GetGender() == Gender::Female; });

//   ASSERT_EQ(2, genderGroups.Count());
//   ASSERT_TRUE(genderGroups.At(0).GetKey() == Gender::Male);
//   ASSERT_TRUE(genderGroups.At(1).GetKey() == Gender::Female);

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

// TEST_F(GroupByFunctionalTest, CustomKeyCompareTest)
// {
//   InternalQueryable<TGenderPerson> genderGroups = this->people
//     .GroupBy<Gender, Person>(
//         [](Person p) { return p.GetGender(); },
//         QueryableType::Vector,
//         [](Gender a, Gender b) { return a == Gender::Female && b == Gender::Male; },
//         [](Person a, Person b) { return a < b;});

//   InternalQueryable<Person> males = this->people
//     .WhereCopy([](Person p) { return p.GetGender() == Gender::Male; });
//   InternalQueryable<Person> females = this->people
//     .WhereCopy([](Person p) { return p.GetGender() == Gender::Female; });

//   ASSERT_EQ(2, genderGroups.Count());
//   // order of keys are swapped
//   ASSERT_TRUE(genderGroups.At(1).GetKey() == Gender::Male);
//   ASSERT_TRUE(genderGroups.At(0).GetKey() == Gender::Female);

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

// TEST_F(GroupByFunctionalTest, GetKeyReturnNullTest)
// {
//   typedef Group<void*, Person> TVoidGroup;
//   InternalQueryable<TVoidGroup> voidGroups = this->people
//     .GroupBy<void*>([](Person p) { return (void*)NULL; });

//   ASSERT_EQ(1, voidGroups.Count());
//   ASSERT_TRUE(voidGroups.At(0).GetKey() == NULL);

//   voidGroups.ForEach([&](TVoidGroup group)
//   {
//     ASSERT_EQ(this->people.Count(), group.Count());

//     int i = 0;
//     for (Person person : group)
//     {
//       ASSERT_TRUE(person == this->people.At(i++));
//     }
//   });
// }

// TEST_F(GroupByFunctionalTest, DequeToListStorageTest)
// {
//   InternalQueryable<TGenderPerson> genderGroups = this->people.ToQueryableDeque()
//     .GroupBy<Gender>(
//       [](Person p) { return p.GetGender(); },
//       QueryableType::List);
//   InternalQueryable<Person> males = this->people
//     .WhereCopy([](Person p) { return p.GetGender() == Gender::Male; });
//   InternalQueryable<Person> females = this->people
//     .WhereCopy([](Person p) { return p.GetGender() == Gender::Female; });

//   ASSERT_EQ(2, genderGroups.Count());
//   ASSERT_TRUE(genderGroups.At(0).GetKey() == Gender::Male);
//   ASSERT_TRUE(genderGroups.At(1).GetKey() == Gender::Female);

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

// TEST_F(GroupByFunctionalTest, DequeToMultiSetStorageTest)
// {
//   InternalQueryable<TGenderPerson> genderGroups = this->people.ToQueryableDeque()
//     .GroupBy<Gender>(
//       [](Person p) { return p.GetGender(); },
//       QueryableType::MultiSet);
//   InternalQueryable<Person> males = this->people
//     .WhereCopy([](Person p) { return p.GetGender() == Gender::Male; });
//   males.Sort();
//   InternalQueryable<Person> females = this->people
//     .WhereCopy([](Person p) { return p.GetGender() == Gender::Female; });
//   females.Sort();

//   ASSERT_EQ(2, genderGroups.Count());
//   ASSERT_TRUE(genderGroups.At(0).GetKey() == Gender::Male);
//   ASSERT_TRUE(genderGroups.At(1).GetKey() == Gender::Female);

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

// TEST_F(GroupByFunctionalTest, DequeToSetStorageTest)
// {
//   InternalQueryable<TGenderPerson> genderGroups = this->people.ToQueryableDeque()
//     .GroupBy<Gender>(
//       [](Person p) { return p.GetGender(); },
//       QueryableType::Set);
//   InternalQueryable<Person> males = this->people
//     .WhereCopy([](Person p) { return p.GetGender() == Gender::Male; });
//   males = males.ToQueryableSet();
//   InternalQueryable<Person> females = this->people
//     .WhereCopy([](Person p) { return p.GetGender() == Gender::Female; });
//   females = females.ToQueryableSet();

//   ASSERT_EQ(2, genderGroups.Count());
//   ASSERT_TRUE(genderGroups.At(0).GetKey() == Gender::Male);
//   ASSERT_TRUE(genderGroups.At(1).GetKey() == Gender::Female);

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

// TEST_F(GroupByFunctionalTest, CustomDataCompareTest)
// {
//   InternalQueryable<TGenderPerson> genderGroups = this->people
//     .GroupBy<Gender, Person>(
//         [](Person p) { return p.GetGender(); },
//         QueryableType::MultiSet,
//         [](Gender a, Gender b) { return a == Gender::Female && b == Gender::Male; },
//         [](Person a, Person b) { return a.GetAge() < b.GetAge(); });

//   InternalQueryable<Person> males = this->people
//     .WhereCopy([](Person p) { return p.GetGender() == Gender::Male; });
//   males.OrderBy<double>([](Person p) { return p.GetAge(); });
//   InternalQueryable<Person> females = this->people
//     .WhereCopy([](Person p) { return p.GetGender() == Gender::Female; });
//   males.OrderBy<double>([](Person p) { return p.GetAge(); });

//   ASSERT_EQ(2, genderGroups.Count());
//   // order of keys are swapped
//   ASSERT_TRUE(genderGroups.At(1).GetKey() == Gender::Male);
//   ASSERT_TRUE(genderGroups.At(0).GetKey() == Gender::Female);

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

//     int i = 0;
//     double previousAge = -1;
//     for (Person person : group)
//     {
//       ASSERT_TRUE(person.GetAge() >= previousAge);
//       previousAge = person.GetAge();

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

// TEST_F(GroupByFunctionalTest, GroupByWhereTest)
// {
//   typedef Group<double, Person> TAgePerson;
//   InternalQueryable<TAgePerson> ageGroupsOverThirty = this->people
//     .GroupBy<double>([](Person p) { return p.GetAge(); })
//     .WhereCopy([](TAgePerson group) { return group.GetKey() > 30; });

//   InternalQueryable<Person> people2 = BuildQueryable(this->people.ToVector());
//   InternalQueryable<TAgePerson> overThirtyAgeGroups = people2
//     .Where([](Person person) { return person.GetAge() > 30; })
//     .GroupBy<double>([](Person p) { return p.GetAge(); });

//   // ASSERT_TRUE(ageGroupsOverThirty != NULL);
//   ASSERT_EQ(3, ageGroupsOverThirty.Count());
//   ASSERT_EQ(3, overThirtyAgeGroups.Count());
//   ASSERT_TRUE(ageGroupsOverThirty.At(0).GetKey() == 51);
//   ASSERT_TRUE(ageGroupsOverThirty.At(1).GetKey() == 52);
//   ASSERT_TRUE(ageGroupsOverThirty.At(2).GetKey() == 61);
//   ASSERT_TRUE(overThirtyAgeGroups.At(0).GetKey() == 51);
//   ASSERT_TRUE(overThirtyAgeGroups.At(1).GetKey() == 52);
//   ASSERT_TRUE(overThirtyAgeGroups.At(2).GetKey() == 61);

//   int iGroup = 0;
//   ageGroupsOverThirty.ForEach([&](TAgePerson group)
//   {
//     ASSERT_TRUE(group.Count() == overThirtyAgeGroups.At(iGroup).Count());

//     int iPerson = 0;
//     for (Person person : group)
//     {
//       ASSERT_TRUE(person == overThirtyAgeGroups.At(iGroup).ToVector()[iPerson++]);
//     }

//     iGroup++;
//   });
// }
