#include <gtest/gtest.h>

#include <array>
#include <deque>
#include <iostream>
#include <list>
#include <set>
#include <string>
#include <vector>

#include "../../../DataStructures/Gender.hpp"
#include "../../../DataStructures/Person.hpp"
#include "../../../DataStructures/PersonLibrary.hpp"

#include "../../../Queryable/QueryBuilder.hpp"


using namespace QueryBuilder;

class EqualFunctionalTest : public ::testing::Test
{
protected:
  VectorQueryable<Person> queryablePeople;
  VectorQueryable<int> queryableInts;

  void SetUp() override
  {
    this->queryablePeople = BuildQueryable(std::vector<Person>(
    {
      Person(1, "Person 1", 26, 72, Gender::Male),
      Person(2, "Person 2", 34, 71, Gender::Female),
      Person(3, "Person 3", 22, 66, Gender::Female),
    }));
    this->queryableInts = BuildQueryable(std::vector<int>({ 4, 7, 4, 7, 4 }));
  }

  Person GetPersonWithId(int id)
  {
    Person p;
    p.SetId(id);
    return p;
  }

  Person GetPerson(int id, std::string name)
  {
    Person p;
    p.SetId(id);
    p.SetName(name);
    return p;
  }

  static bool LikeIds(Person p1, Person p2)
  {
    return p1.GetId() == p2.GetId();
  }

  void TearDown() override {}
};

// VECTOR (== comparison)
TEST_F(EqualFunctionalTest, EqualVectorsUninitializedTest)
{
  VectorQueryable<int> localQueryable;
  std::vector<int> localVector;

  ASSERT_TRUE(localQueryable.Equal(localVector));
}

TEST_F(EqualFunctionalTest, EqualQueryEmptyVectorOneTest)
{
  VectorQueryable<int> localQueryable;
  std::vector<int> localVector({ 9 });

  ASSERT_FALSE(localQueryable.Equal(localVector));
}

TEST_F(EqualFunctionalTest, EqualQueryOneVectorEmptyTest)
{
  VectorQueryable<int> localQueryable(std::vector<int>({ 9 }));
  std::vector<int> localVector;

  ASSERT_FALSE(localQueryable.Equal(localVector));
}

TEST_F(EqualFunctionalTest, EqualVectorQueryOneExtraTest)
{
  std::vector<int> localVector({ 4, 7, 4, 7 });
  ASSERT_FALSE(this->queryableInts.Equal(localVector));
}

TEST_F(EqualFunctionalTest, EqualVectorOneExtraTest)
{
  std::vector<int> localVector({ 4, 7, 4, 7, 4, 7 });
  ASSERT_FALSE(this->queryableInts.Equal(localVector));
}

TEST_F(EqualFunctionalTest, EqualVectorLastItemsSwappedTest)
{
  std::vector<int> localVector({ 4, 7, 4, 4, 7 });
  ASSERT_FALSE(this->queryableInts.Equal(localVector));
}

// SET (== comparison)
TEST_F(EqualFunctionalTest, EqualSetsUninitializedTest)
{
  SetQueryable<int> localQueryable;
  std::set<int> localSet;

  ASSERT_TRUE(localQueryable.Equal(localSet));
}

TEST_F(EqualFunctionalTest, EqualQueryEmptySetOneTest)
{
  SetQueryable<int> localQueryable;
  std::set<int> localSet({ 9 });

  ASSERT_FALSE(localQueryable.Equal(localSet));
}

TEST_F(EqualFunctionalTest, EqualQueryOneSetEmptyTest)
{
  SetQueryable<int> localQueryable(std::set<int>({ 9 }));
  std::set<int> localSet;

  ASSERT_FALSE(localQueryable.Equal(localSet));
}

TEST_F(EqualFunctionalTest, EqualSetQueryOneExtraTest)
{
  std::set<int> localSet({ 4, 7, 4, 7 });
  SetQueryable<int> queryableSet = BuildQueryable(this->queryableInts.ToSet());
  ASSERT_TRUE(queryableSet.Equal(localSet));
}

TEST_F(EqualFunctionalTest, EqualSetOneExtraTest)
{
  std::set<int> localSet({ 4, 7, 4, 7, 4, 7 });
  SetQueryable<int> queryableSet = BuildQueryable(this->queryableInts.ToSet());
  ASSERT_TRUE(queryableSet.Equal(localSet));
}

TEST_F(EqualFunctionalTest, EqualSetLastItemsSwappedTest)
{
  std::set<int> localSet({ 4, 7, 4, 4, 7 });
  SetQueryable<int> queryableSet = BuildQueryable(this->queryableInts.ToSet());
  ASSERT_TRUE(queryableSet.Equal(localSet));
}

// MULTISET (== comparison)
TEST_F(EqualFunctionalTest, EqualMultiSetsUninitializedTest)
{
  SetQueryable<int> localQueryable;
  std::multiset<int> localMultiSet;

  ASSERT_TRUE(localQueryable.Equal(localMultiSet));
}

TEST_F(EqualFunctionalTest, EqualQueryEmptyMultiSetOneTest)
{
  MultiSetQueryable<int> localQueryable;
  std::multiset<int> localMultiSet({ 9 });

  ASSERT_FALSE(localQueryable.Equal(localMultiSet));
}

TEST_F(EqualFunctionalTest, EqualQueryOneMultiSetEmptyTest)
{
  MultiSetQueryable<int> localQueryable(std::multiset<int>({ 9 }));
  std::multiset<int> localMultiSet;

  ASSERT_FALSE(localQueryable.Equal(localMultiSet));
}

TEST_F(EqualFunctionalTest, EqualMultiSetQueryOneExtraTest)
{
  std::multiset<int> localMultiSet({ 4, 7, 4, 7 });
  MultiSetQueryable<int> queryableMultiSet = BuildQueryable(this->queryableInts.ToMultiSet());
  ASSERT_FALSE(queryableMultiSet.Equal(localMultiSet));
}

TEST_F(EqualFunctionalTest, EqualMultiSetOneExtraTest)
{
  std::multiset<int> localMultiSet({ 4, 7, 4, 7, 4, 7 });
  MultiSetQueryable<int> queryableMultiSet = BuildQueryable(this->queryableInts.ToMultiSet());
  ASSERT_FALSE(queryableMultiSet.Equal(localMultiSet));
}

TEST_F(EqualFunctionalTest, EqualMultiSetLastItemsSwappedTest)
{
  std::multiset<int> localMultiSet({ 4, 7, 4, 4, 7 });
  MultiSetQueryable<int> queryableMultiSet = BuildQueryable(this->queryableInts.ToMultiSet());
  ASSERT_TRUE(queryableMultiSet.Equal(localMultiSet));
}

// DEQUE (== comparison)
TEST_F(EqualFunctionalTest, EqualDequesUninitializedTest)
{
  DequeQueryable<int> localQueryable;
  std::deque<int> localDeque;

  ASSERT_TRUE(localQueryable.Equal(localDeque));
}

TEST_F(EqualFunctionalTest, EqualQueryEmptyDequeOneTest)
{
  DequeQueryable<int> localQueryable;
  std::deque<int> localDeque({ 9 });

  ASSERT_FALSE(localQueryable.Equal(localDeque));
}

TEST_F(EqualFunctionalTest, EqualQueryOneDequeEmptyTest)
{
  DequeQueryable<int> localQueryable(std::deque<int>({ 9 }));
  std::deque<int> localDeque;

  ASSERT_FALSE(localQueryable.Equal(localDeque));
}

TEST_F(EqualFunctionalTest, EqualDequeQueryOneExtraTest)
{
  std::deque<int> localDeque({ 4, 7, 4, 7 });
  DequeQueryable<int> queryableDeque = BuildQueryable(this->queryableInts.ToDeque());
  ASSERT_FALSE(queryableDeque.Equal(localDeque));
}

TEST_F(EqualFunctionalTest, EqualDequeOneExtraTest)
{
  std::deque<int> localDeque({ 4, 7, 4, 7, 4, 7 });
  DequeQueryable<int> queryableDeque = BuildQueryable(this->queryableInts.ToDeque());
  ASSERT_FALSE(queryableDeque.Equal(localDeque));
}

TEST_F(EqualFunctionalTest, EqualDequeLastItemsSwappedTest)
{
  std::deque<int> localDeque({ 4, 7, 4, 4, 7 });
  DequeQueryable<int> queryableDeque = BuildQueryable(this->queryableInts.ToDeque());
  ASSERT_FALSE(queryableDeque.Equal(localDeque));
}

// LIST (== comparison)
TEST_F(EqualFunctionalTest, EqualListsUninitializedTest)
{
  ListQueryable<int> localQueryable;
  std::list<int> localList;

  ASSERT_TRUE(localQueryable.Equal(localList));
}

TEST_F(EqualFunctionalTest, EqualQueryEmptyListOneTest)
{
  ListQueryable<int> localQueryable;
  std::list<int> localList({ 9 });

  ASSERT_FALSE(localQueryable.Equal(localList));
}

TEST_F(EqualFunctionalTest, EqualQueryOneListEmptyTest)
{
  ListQueryable<int> localQueryable(std::list<int>({ 9 }));
  std::list<int> localList;

  ASSERT_FALSE(localQueryable.Equal(localList));
}

TEST_F(EqualFunctionalTest, EqualListQueryOneExtraTest)
{
  std::list<int> localList({ 4, 7, 4, 7 });
  ListQueryable<int> queryableList(this->queryableInts.ToList());
  ASSERT_FALSE(queryableList.Equal(localList));
}

TEST_F(EqualFunctionalTest, EqualListOneExtraTest)
{
  std::list<int> localList({ 4, 7, 4, 7, 4, 7 });
  ListQueryable<int> queryableList(this->queryableInts.ToList());
  ASSERT_FALSE(queryableList.Equal(localList));
}

TEST_F(EqualFunctionalTest, EqualListLastItemsSwappedTest)
{
  std::list<int> localList({ 4, 7, 4, 4, 7 });
  ListQueryable<int> queryableList(this->queryableInts.ToList());
  ASSERT_FALSE(queryableList.Equal(localList));
}




// MISC (custom comparison)
TEST_F(EqualFunctionalTest, EqualEmptiesAlwaysEqual)
{
  VectorQueryable<Person> localQueryable;
  std::vector<Person> localVector;
  ASSERT_TRUE(localQueryable.Equal(localVector, [](Person p1, Person p2){ return false; }));
}

TEST_F(EqualFunctionalTest, EqualCustomForcedEqual)
{
  std::vector<Person> localVector(
  {
    this->GetPersonWithId(9),
    this->GetPersonWithId(10),
    this->GetPersonWithId(11),
  });

  ASSERT_TRUE(this->queryablePeople.Equal(localVector, [](Person p1, Person p2){ return true; }));
}

TEST_F(EqualFunctionalTest, EqualCustomForcedNotEqual)
{
  std::vector<Person> localVector(
  {
    this->GetPersonWithId(1),
    this->GetPersonWithId(2),
    this->GetPersonWithId(3),
  });

  ASSERT_FALSE(this->queryablePeople.Equal(localVector, [](Person p1, Person p2){ return false; }));
}




// VECTOR (custom comparison)
TEST_F(EqualFunctionalTest, EqualCustomQueryEmptyVectorOneTest)
{
  VectorQueryable<Person> localQueryable;
  std::vector<Person> localVector({ this->GetPersonWithId(1) });

  ASSERT_FALSE(localQueryable.Equal(localVector, LikeIds));
}

TEST_F(EqualFunctionalTest, EqualCustomQueryOneVectorEmptyTest)
{
  VectorQueryable<Person> localQueryable = BuildQueryable(std::vector<Person>({ this->GetPersonWithId(1) }));
  std::vector<Person> localVector;

  ASSERT_FALSE(localQueryable.Equal(localVector, LikeIds));
}

TEST_F(EqualFunctionalTest, EqualCustomVectorQueryOneExtraTest)
{
  std::vector<Person> localVector({ this->GetPersonWithId(1), this->GetPersonWithId(2) });
  ASSERT_FALSE(this->queryablePeople.Equal(localVector, LikeIds));
}

TEST_F(EqualFunctionalTest, EqualCustomVectorOneExtraTest)
{
  std::vector<Person> localVector(
  {
    this->GetPersonWithId(1),
    this->GetPersonWithId(2),
    this->GetPersonWithId(3),
    this->GetPersonWithId(4)
  });

  ASSERT_FALSE(this->queryablePeople.Equal(localVector, LikeIds));
}

TEST_F(EqualFunctionalTest, EqualCustomVectorLastItemsSwappedTest)
{
  std::vector<Person> localVector(
  {
    this->GetPersonWithId(1),
    this->GetPersonWithId(3),
    this->GetPersonWithId(2),
  });

  ASSERT_FALSE(this->queryablePeople.Equal(localVector, LikeIds));
}

// SET (custom comparison)
TEST_F(EqualFunctionalTest, EqualCustomQueryEmptySetOneTest)
{
  SetQueryable<Person> localQueryable;
  std::set<Person> localSet({ this->GetPersonWithId(1) });

  ASSERT_FALSE(localQueryable.Equal(localSet, LikeIds));
}

TEST_F(EqualFunctionalTest, EqualCustomQueryOneSetEmptyTest)
{
  SetQueryable<Person> localQueryable(std::set<Person>({ this->GetPersonWithId(1) }));
  std::set<Person> localSet;

  ASSERT_FALSE(localQueryable.Equal(localSet, LikeIds));
}

TEST_F(EqualFunctionalTest, EqualCustomSetQueryOneExtraTest)
{
  std::set<Person> localSet({ this->GetPersonWithId(1), this->GetPersonWithId(2) });
  SetQueryable<Person> localQueryable(this->queryablePeople.ToSet());
  ASSERT_FALSE(localQueryable.Equal(localSet, LikeIds));
}

TEST_F(EqualFunctionalTest, EqualCustomSetOneExtraTest)
{
  std::set<Person> localSet(
  {
    this->GetPersonWithId(1),
    this->GetPersonWithId(2),
    this->GetPersonWithId(3),
    this->GetPersonWithId(4)
  });

  SetQueryable<Person> localQueryable(this->queryablePeople.ToSet());
  ASSERT_FALSE(localQueryable.Equal(localSet, LikeIds));
}

TEST_F(EqualFunctionalTest, EqualCustomSetLastItemsSwappedSameNamesTest)
{
  std::set<Person> localSet(
  {
    this->GetPersonWithId(1),
    this->GetPersonWithId(3),
    this->GetPersonWithId(2),
  });

  SetQueryable<Person> localQueryable(this->queryablePeople.ToSet());
  ASSERT_FALSE(localQueryable.Equal(localSet, LikeIds));
}

TEST_F(EqualFunctionalTest, EqualCustomSetLastItemsSwappedDiffNamesTest)
{
  std::set<Person> localSet(
  {
    this->GetPerson(1, "P1"),
    this->GetPerson(3, "P3"),
    this->GetPerson(2, "P2"),
  });

  // the set re-orders based on name which puts the IDs back in the proper order for equality to pass
  SetQueryable<Person> localQueryable(this->queryablePeople.ToSet());
  ASSERT_TRUE(localQueryable.Equal(localSet, LikeIds));
}

// MULTISET (custom comparison)
TEST_F(EqualFunctionalTest, EqualCustomQueryEmptyMultiSetOneTest)
{
  MultiSetQueryable<Person> localQueryable;
  std::multiset<Person> localMultiSet({ this->GetPersonWithId(1) });

  ASSERT_FALSE(localQueryable.Equal(localMultiSet, LikeIds));
}

TEST_F(EqualFunctionalTest, EqualCustomQueryOneMultiSetEmptyTest)
{
  MultiSetQueryable<Person> localQueryable(std::multiset<Person>({ this->GetPersonWithId(1) }));
  std::multiset<Person> localMultiSet;

  ASSERT_FALSE(localQueryable.Equal(localMultiSet, LikeIds));
}

TEST_F(EqualFunctionalTest, EqualCustomMultiSetQueryOneExtraTest)
{
  std::multiset<Person> localMultiSet({ this->GetPersonWithId(1), this->GetPersonWithId(2) });
  MultiSetQueryable<Person> localQueryable(this->queryablePeople.ToMultiSet());
  ASSERT_FALSE(localQueryable.Equal(localMultiSet, LikeIds));
}

TEST_F(EqualFunctionalTest, EqualCustomMultiSetOneExtraTest)
{
  std::multiset<Person> localMultiSet(
  {
    this->GetPersonWithId(1),
    this->GetPersonWithId(2),
    this->GetPersonWithId(3),
    this->GetPersonWithId(4)
  });

  MultiSetQueryable<Person> localQueryable(this->queryablePeople.ToMultiSet());
  ASSERT_FALSE(localQueryable.Equal(localMultiSet, LikeIds));
}

TEST_F(EqualFunctionalTest, EqualCustomMultiSetLastItemsSwappedTest)
{
  std::multiset<Person> localMultiSet(
  {
    this->GetPersonWithId(1),
    this->GetPersonWithId(3),
    this->GetPersonWithId(2),
  });

  MultiSetQueryable<Person> localQueryable(this->queryablePeople.ToMultiSet());
  ASSERT_FALSE(localQueryable.Equal(localMultiSet, LikeIds));
}

TEST_F(EqualFunctionalTest, EqualCustomMultiSetLastItemsSwappedDiffNamesTest)
{
  std::multiset<Person> localMultiSet(
  {
    this->GetPerson(1, "P1"),
    this->GetPerson(3, "P3"),
    this->GetPerson(2, "P2"),
  });

  // the multiset re-orders based on name which puts the IDs back in the proper order for equality to pass
  MultiSetQueryable<Person> localQueryable(this->queryablePeople.ToMultiSet());
  ASSERT_TRUE(localQueryable.Equal(localMultiSet, LikeIds));
}

// DEQUE (custom comparison)
TEST_F(EqualFunctionalTest, EqualCustomQueryEmptyDequeOneTest)
{
  DequeQueryable<Person> localQueryable;
  std::deque<Person> localDeque({ this->GetPersonWithId(1) });

  ASSERT_FALSE(localQueryable.Equal(localDeque, LikeIds));
}

TEST_F(EqualFunctionalTest, EqualCustomQueryOneDequeEmptyTest)
{
  DequeQueryable<Person> localQueryable = BuildQueryable(std::deque<Person>({ this->GetPersonWithId(1) }));
  std::deque<Person> localDeque;

  ASSERT_FALSE(localQueryable.Equal(localDeque, LikeIds));
}

TEST_F(EqualFunctionalTest, EqualCustomDequeQueryOneExtraTest)
{
  std::deque<Person> localDeque(
  {
    this->GetPersonWithId(1),
    this->GetPersonWithId(2),
    this->GetPersonWithId(3),
    this->GetPersonWithId(4)
  });

  DequeQueryable<Person> localQueryable(this->queryablePeople.ToDeque());
  ASSERT_FALSE(localQueryable.Equal(localDeque, LikeIds));
}

TEST_F(EqualFunctionalTest, EqualCustomDequeOneExtraTest)
{
  std::deque<Person> localDeque(
  {
    this->GetPersonWithId(1),
    this->GetPersonWithId(3),
    this->GetPersonWithId(2),
  });

  DequeQueryable<Person> localQueryable(this->queryablePeople.ToDeque());
  ASSERT_FALSE(localQueryable.Equal(localDeque, LikeIds));
}

TEST_F(EqualFunctionalTest, EqualCustomDequeLastItemsSwappedTest)
{
  std::deque<Person> localDeque(
  {
    this->GetPersonWithId(1),
    this->GetPersonWithId(3),
    this->GetPersonWithId(2),
  });

  DequeQueryable<Person> localQueryable(this->queryablePeople.ToDeque());
  ASSERT_FALSE(localQueryable.Equal(localDeque, LikeIds));
}

// LIST (custom comparison)
TEST_F(EqualFunctionalTest, EqualCustomQueryEmptyListOneTest)
{
  ListQueryable<Person> localQueryable;
  std::list<Person> localList({ this->GetPersonWithId(1) });

  ASSERT_FALSE(localQueryable.Equal(localList, LikeIds));
}

TEST_F(EqualFunctionalTest, EqualCustomQueryOneListEmptyTest)
{
  ListQueryable<Person> localQueryable(std::list<Person>({ this->GetPersonWithId(1) }));
  std::list<Person> localList;

  ASSERT_FALSE(localQueryable.Equal(localList, LikeIds));
}

TEST_F(EqualFunctionalTest, EqualCustomListQueryOneExtraTest)
{
  std::list<Person> localList(
  {
    this->GetPersonWithId(1),
    this->GetPersonWithId(2),
    this->GetPersonWithId(3),
    this->GetPersonWithId(4)
  });

  ListQueryable<Person> localQueryable(this->queryablePeople.ToList());
  ASSERT_FALSE(localQueryable.Equal(localList, LikeIds));
}

TEST_F(EqualFunctionalTest, EqualCustomListOneExtraTest)
{
  std::list<Person> localList(
  {
    this->GetPersonWithId(1),
    this->GetPersonWithId(3),
    this->GetPersonWithId(2),
  });

  ListQueryable<Person> localQueryable(this->queryablePeople.ToList());
  ASSERT_FALSE(localQueryable.Equal(localList, LikeIds));
}

TEST_F(EqualFunctionalTest, EqualCustomListLastItemsSwappedTest)
{
  std::list<Person> localList(
  {
    this->GetPersonWithId(1),
    this->GetPersonWithId(3),
    this->GetPersonWithId(2),
  });

  ListQueryable<Person> localQueryable(this->queryablePeople.ToList());
  ASSERT_FALSE(localQueryable.Equal(localList, LikeIds));
}

TEST_F(EqualFunctionalTest, EqualWhereEven)
{
  bool areEqual = this->queryableInts
    .Where([](int value) { return value % 2 == 0; })
    .Equal(std::vector<int>({ 4, 4, 4 }));

  ASSERT_TRUE(areEqual);
}

TEST_F(EqualFunctionalTest, EqualWhereOdd)
{
  bool areEqual = this->queryableInts
    .Where([](int value) { return value % 2 == 1; })
    .Equal(std::vector<int>({ 7, 7 }));

  ASSERT_TRUE(areEqual);
}
