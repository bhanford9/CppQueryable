#include <gtest/gtest.h>

#include <array>
#include <deque>
#include <exception>
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

class ExceptFunctionalTest : public ::testing::Test
{
protected:
  std::vector<uint> startingInput;
  std::vector<uint> evens;
  IQueryable<uint> queryable;
  IQueryable<uint> queryableEvens;
  int oddCount = 5;

  ExceptFunctionalTest() :
    startingInput( std::vector<uint>({ 1, 4, 7, 4, 3, 76, 8, 45, 34, 76, 0, 867 })),
    evens( std::vector<uint>({ 4, 76, 8, 34, 76, 0 })),
    queryable( BuildQueryable2(this->startingInput)),
    queryableEvens( BuildQueryable2(this->evens))
  {
  }

  void SetUp() override
  {
  }

  void TearDown() override {}
};

TEST_F(ExceptFunctionalTest, ExceptLocalFullInputEmptyTemplate)
{
  std::vector<uint> local;
  std::vector<uint> result = this->queryable
    .Except<std::vector>(local)
    .ToVector();

  ASSERT_EQ(this->startingInput.size(), result.size());
}

TEST_F(ExceptFunctionalTest, ExceptLocalFullInputEmptyAsVector)
{
  std::vector<uint> local;
  std::vector<uint> result = this->queryable
    .AsQueryableVector()
    .Except(local)
    .ToVector();

  ASSERT_EQ(this->startingInput.size(), result.size());
}

TEST_F(ExceptFunctionalTest, ExceptLocalFullInputEmptyExtended)
{
  std::vector<uint> local;
  std::vector<uint> result = this->queryable
    .AsExtendedQueryable<std::vector>()
    .Except(local)
    .ToVector();

  ASSERT_EQ(this->startingInput.size(), result.size());
}

TEST_F(ExceptFunctionalTest, ExceptAllSameTemplate)
{
  IQueryable<uint> a = BuildQueryable2<uint>(std::vector<uint>({ 2, 5, 2, 5, 5, 5, 2, 2, 5 }));
  std::vector<uint> b = std::vector<uint>({ 2, 5 });
  std::vector<uint> result = a
    .Except<std::vector>(b)
    .ToVector();

  ASSERT_EQ(0, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptAllSameAsVector)
{
  IQueryable<uint> a = BuildQueryable2<uint>(std::vector<uint>({ 2, 5, 2, 5, 5, 5, 2, 2, 5 }));
  std::vector<uint> b = std::vector<uint>({ 2, 5 });
  std::vector<uint> result = a
    .AsQueryableVector()
    .Except(b)
    .ToVector();

  ASSERT_EQ(0, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptAllSameExtended)
{
  IQueryable<uint> a = BuildQueryable2<uint>(std::vector<uint>({ 2, 5, 2, 5, 5, 5, 2, 2, 5 }));
  std::vector<uint> b = std::vector<uint>({ 2, 5 });
  std::vector<uint> result = a
    .AsExtendedQueryable<std::vector>()
    .Except(b)
    .ToVector();

  ASSERT_EQ(0, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptCustomCompareTemplate)
{
  PersonLibrary personLibrary;
  IQueryable<Person> local = BuildQueryable2<Person>(personLibrary.GetPeople());
  IQueryable<Person> exceptions = BuildQueryable2<Person>(std::vector<Person>({
    Person(33, "Person 4", 12, 60, Gender::Male),
    Person(99, "Person 6", 14, 62, Gender::Female)
  }));

  int originalLength = local.Count();
  int afterExceptLength = originalLength - exceptions.Count();

  std::vector<Person> result = local
    .Except<std::vector>(
      exceptions.ToVector(),
      [](Person a, Person b) { return a.GetName() < b.GetName(); })
    .ToVector();

  ASSERT_EQ(afterExceptLength, result.size());
  for (Person p : result)
  {
    ASSERT_TRUE(p.GetName() != "Person 4");
    ASSERT_TRUE(p.GetName() != "Person 6");
  }
}

TEST_F(ExceptFunctionalTest, ExceptCustomCompareAsVector)
{
  PersonLibrary personLibrary;
  IQueryable<Person> local = BuildQueryable2<Person>(personLibrary.GetPeople());
  IQueryable<Person> exceptions = BuildQueryable2<Person>(std::vector<Person>({
    Person(33, "Person 4", 12, 60, Gender::Male),
    Person(99, "Person 6", 14, 62, Gender::Female)
  }));

  int originalLength = local.Count();
  int afterExceptLength = originalLength - exceptions.Count();

  std::vector<Person> result = local
    .AsQueryableVector()
    .Except(
      exceptions.ToVector(),
      [](Person a, Person b) { return a.GetName() < b.GetName(); })
    .ToVector();

  ASSERT_EQ(afterExceptLength, result.size());
  for (Person p : result)
  {
    ASSERT_TRUE(p.GetName() != "Person 4");
    ASSERT_TRUE(p.GetName() != "Person 6");
  }
}

TEST_F(ExceptFunctionalTest, ExceptCustomCompareExtended)
{
  PersonLibrary personLibrary;
  IQueryable<Person> local = BuildQueryable2<Person>(personLibrary.GetPeople());
  IQueryable<Person> exceptions = BuildQueryable2<Person>(std::vector<Person>({
    Person(33, "Person 4", 12, 60, Gender::Male),
    Person(99, "Person 6", 14, 62, Gender::Female)
  }));

  int originalLength = local.Count();
  int afterExceptLength = originalLength - exceptions.Count();

  std::vector<Person> result = local
    .AsExtendedQueryable<std::vector>()
    .Except(
      exceptions.ToVector(),
      [](Person a, Person b) { return a.GetName() < b.GetName(); })
    .ToVector();

  ASSERT_EQ(afterExceptLength, result.size());
  for (Person p : result)
  {
    ASSERT_TRUE(p.GetName() != "Person 4");
    ASSERT_TRUE(p.GetName() != "Person 6");
  }
}

TEST_F(ExceptFunctionalTest, ExceptTemplateDequeDequeDefault)
{
  IQueryable<uint> local = BuildQueryable2<uint>(this->queryable.ToDeque());
  std::deque<uint> evens = this->queryableEvens.ToDeque();
  std::deque<uint> result = local
    .Except<std::deque>(evens)
    .ToDeque();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptAsDequeDequeDefault)
{
  IQueryable<uint> local = BuildQueryable2<uint>(this->queryable.ToDeque());
  std::deque<uint> evens = this->queryableEvens.ToDeque();
  std::deque<uint> result = local
    .AsQueryableDeque()
    .Except(evens)
    .ToDeque();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptExtendedDequeDequeDefault)
{
  IQueryable<uint> local = BuildQueryable2<uint>(this->queryable.ToDeque());
  std::deque<uint> evens = this->queryableEvens.ToDeque();
  std::deque<uint> result = local
    .AsExtendedQueryable<std::deque>()
    .Except(evens)
    .ToDeque();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptTemplateDequeListDefault)
{
  IQueryable<uint> local = BuildQueryable2<uint>(this->queryable.ToDeque());
  std::list<uint> evens = this->queryableEvens.ToList();
  std::deque<uint> result = local
    .Except<std::deque>(evens)
    .ToDeque();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptAsDequeListDefault)
{
  IQueryable<uint> local = BuildQueryable2<uint>(this->queryable.ToDeque());
  std::list<uint> evens = this->queryableEvens.ToList();
  std::deque<uint> result = local
    .AsQueryableDeque()
    .Except(evens)
    .ToDeque();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptExtendedDequeListDefault)
{
  IQueryable<uint> local = BuildQueryable2<uint>(this->queryable.ToDeque());
  std::list<uint> evens = this->queryableEvens.ToList();
  std::deque<uint> result = local
    .AsExtendedQueryable<std::deque>()
    .Except(evens)
    .ToDeque();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptTemplateDequeMultiSetDefault)
{
  IQueryable<uint> local = BuildQueryable2<uint>(this->queryable.ToDeque());
  std::multiset<uint> evens = this->queryableEvens.ToMultiSet();
  std::deque<uint> result = local
    .Except<std::deque>(evens)
    .ToDeque();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptAsDequeMultiSetDefault)
{
  IQueryable<uint> local = BuildQueryable2<uint>(this->queryable.ToDeque());
  std::multiset<uint> evens = this->queryableEvens.ToMultiSet();
  std::deque<uint> result = local
    .AsQueryableDeque()
    .Except(evens)
    .ToDeque();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptExtendedDequeMultiSetDefault)
{
  IQueryable<uint> local = BuildQueryable2<uint>(this->queryable.ToDeque());
  std::multiset<uint> evens = this->queryableEvens.ToMultiSet();
  std::deque<uint> result = local
    .AsExtendedQueryable<std::deque>()
    .Except(evens)
    .ToDeque();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptTemplateDequeSetDefault)
{
  IQueryable<uint> local = BuildQueryable2<uint>(this->queryable.ToDeque());
  std::set<uint> evens = this->queryableEvens.ToSet();
  std::deque<uint> result = local
    .Except<std::deque>(evens)
    .ToDeque();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptAsDequeSetDefault)
{
  IQueryable<uint> local = BuildQueryable2<uint>(this->queryable.ToDeque());
  std::set<uint> evens = this->queryableEvens.ToSet();
  std::deque<uint> result = local
    .AsQueryableDeque()
    .Except(evens)
    .ToDeque();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptExtendedDequeSetDefault)
{
  IQueryable<uint> local = BuildQueryable2<uint>(this->queryable.ToDeque());
  std::set<uint> evens = this->queryableEvens.ToSet();
  std::deque<uint> result = local
    .AsExtendedQueryable<std::deque>()
    .Except(evens)
    .ToDeque();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptTemplateDequeVectorDefault)
{
  IQueryable<uint> local = BuildQueryable2<uint>(this->queryable.ToDeque());
  std::vector<uint> evens = this->queryableEvens.ToVector();
  std::deque<uint> result = local
    .Except<std::deque>(evens)
    .ToDeque();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptAsDequeVectorDefault)
{
  IQueryable<uint> local = BuildQueryable2<uint>(this->queryable.ToDeque());
  std::vector<uint> evens = this->queryableEvens.ToVector();
  std::deque<uint> result = local
    .AsQueryableDeque()
    .Except(evens)
    .ToDeque();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptExtendedDequeVectorDefault)
{
  IQueryable<uint> local = BuildQueryable2<uint>(this->queryable.ToDeque());
  std::vector<uint> evens = this->queryableEvens.ToVector();
  std::deque<uint> result = local
    .AsExtendedQueryable<std::deque>()
    .Except(evens)
    .ToDeque();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptTemplateListDequeDefault)
{
  IQueryable<uint> local = BuildQueryable2<uint>(this->queryable.ToList());
  std::deque<uint> evens = this->queryableEvens.ToDeque();
  std::list<uint> result = local
    .Except<std::list>(evens)
    .ToList();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptAsListDequeDefault)
{
  IQueryable<uint> local = BuildQueryable2<uint>(this->queryable.ToList());
  std::deque<uint> evens = this->queryableEvens.ToDeque();
  std::list<uint> result = local
    .AsQueryableList()
    .Except(evens)
    .ToList();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptExtendedListDequeDefault)
{
  IQueryable<uint> local = BuildQueryable2<uint>(this->queryable.ToList());
  std::deque<uint> evens = this->queryableEvens.ToDeque();
  std::list<uint> result = local
    .AsExtendedQueryable<std::list>()
    .Except(evens)
    .ToList();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptTemplateListMultiSetDefault)
{
  IQueryable<uint> local = BuildQueryable2<uint>(this->queryable.ToList());
  std::multiset<uint> evens = this->queryableEvens.ToMultiSet();
  std::list<uint> result = local
    .Except<std::list>(evens)
    .ToList();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptAsListMultiSetDefault)
{
  IQueryable<uint> local = BuildQueryable2<uint>(this->queryable.ToList());
  std::multiset<uint> evens = this->queryableEvens.ToMultiSet();
  std::list<uint> result = local
    .AsQueryableList()
    .Except(evens)
    .ToList();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptExtendedListMultiSetDefault)
{
  IQueryable<uint> local = BuildQueryable2<uint>(this->queryable.ToList());
  std::multiset<uint> evens = this->queryableEvens.ToMultiSet();
  std::list<uint> result = local
    .AsExtendedQueryable<std::list>()
    .Except(evens)
    .ToList();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptTemplateListSetDefault)
{
  IQueryable<uint> local = BuildQueryable2<uint>(this->queryable.ToList());
  std::set<uint> evens = this->queryableEvens.ToSet();
  std::list<uint> result = local
    .Except<std::list>(evens)
    .ToList();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptAsListSetDefault)
{
  IQueryable<uint> local = BuildQueryable2<uint>(this->queryable.ToList());
  std::set<uint> evens = this->queryableEvens.ToSet();
  std::list<uint> result = local
    .AsQueryableList()
    .Except(evens)
    .ToList();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptExtendedListSetDefault)
{
  IQueryable<uint> local = BuildQueryable2<uint>(this->queryable.ToList());
  std::set<uint> evens = this->queryableEvens.ToSet();
  std::list<uint> result = local
    .AsExtendedQueryable<std::list>()
    .Except(evens)
    .ToList();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptTemplateListVectorDefault)
{
  IQueryable<uint> local = BuildQueryable2<uint>(this->queryable.ToList());
  std::vector<uint> evens = this->queryableEvens.ToVector();
  std::list<uint> result = local
    .Except<std::list>(evens)
    .ToList();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptAsListVectorDefault)
{
  IQueryable<uint> local = BuildQueryable2<uint>(this->queryable.ToList());
  std::vector<uint> evens = this->queryableEvens.ToVector();
  std::list<uint> result = local
    .AsQueryableList()
    .Except(evens)
    .ToList();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptExtendedListVectorDefault)
{
  IQueryable<uint> local = BuildQueryable2<uint>(this->queryable.ToList());
  std::vector<uint> evens = this->queryableEvens.ToVector();
  std::list<uint> result = local
    .AsExtendedQueryable<std::list>()
    .Except(evens)
    .ToList();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptTemplateMultiSetDequeDefault)
{
  IQueryable<uint> local = BuildQueryable2<uint>(this->queryable.ToMultiSet());
  std::deque<uint> evens = this->queryableEvens.ToDeque();
  std::multiset<uint> result = local
    .Except<std::multiset>(evens)
    .ToMultiSet();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptAsMultiSetDequeDefault)
{
  IQueryable<uint> local = BuildQueryable2<uint>(this->queryable.ToMultiSet());
  std::deque<uint> evens = this->queryableEvens.ToDeque();
  std::multiset<uint> result = local
    .AsQueryableMultiSet()
    .Except(evens)
    .ToMultiSet();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptExtendedMultiSetDequeDefault)
{
  IQueryable<uint> local = BuildQueryable2<uint>(this->queryable.ToMultiSet());
  std::deque<uint> evens = this->queryableEvens.ToDeque();
  std::multiset<uint> result = local
    .AsExtendedQueryable<std::multiset>()
    .Except(evens)
    .ToMultiSet();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptTemplateMultiSetListDefault)
{
  IQueryable<uint> local = BuildQueryable2<uint>(this->queryable.ToMultiSet());
  std::list<uint> evens = this->queryableEvens.ToList();
  std::multiset<uint> result = local
    .Except<std::multiset>(evens)
    .ToMultiSet();

  ASSERT_EQ(this->oddCount, result.size());
}


TEST_F(ExceptFunctionalTest, ExceptAsMultiSetListDefault)
{
  IQueryable<uint> local = BuildQueryable2<uint>(this->queryable.ToMultiSet());
  std::list<uint> evens = this->queryableEvens.ToList();
  std::multiset<uint> result = local
    .AsQueryableMultiSet()
    .Except(evens)
    .ToMultiSet();

  ASSERT_EQ(this->oddCount, result.size());
}


TEST_F(ExceptFunctionalTest, ExceptExtendedMultiSetListDefault)
{
  IQueryable<uint> local = BuildQueryable2<uint>(this->queryable.ToMultiSet());
  std::list<uint> evens = this->queryableEvens.ToList();
  std::multiset<uint> result = local
    .AsExtendedQueryable<std::multiset>()
    .Except(evens)
    .ToMultiSet();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptTemplateMultiSetSetDefault)
{
  IQueryable<uint> local = BuildQueryable2<uint>(this->queryable.ToMultiSet());
  std::set<uint> evens = this->queryableEvens.ToSet();
  std::multiset<uint> result = local
    .Except<std::multiset>(evens)
    .ToMultiSet();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptAsMultiSetSetDefault)
{
  IQueryable<uint> local = BuildQueryable2<uint>(this->queryable.ToMultiSet());
  std::set<uint> evens = this->queryableEvens.ToSet();
  std::multiset<uint> result = local
    .AsQueryableMultiSet()
    .Except(evens)
    .ToMultiSet();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptExtendedMultiSetSetDefault)
{
  IQueryable<uint> local = BuildQueryable2<uint>(this->queryable.ToMultiSet());
  std::set<uint> evens = this->queryableEvens.ToSet();
  std::multiset<uint> result = local
    .AsExtendedQueryable<std::multiset>()
    .Except(evens)
    .ToMultiSet();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptTemplateMultiSetVectorDefault)
{
  IQueryable<uint> local = BuildQueryable2<uint>(this->queryable.ToMultiSet());
  std::vector<uint> evens = this->queryableEvens.ToVector();
  std::multiset<uint> result = local
    .Except<std::multiset>(evens)
    .ToMultiSet();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptAsMultiSetVectorDefault)
{
  IQueryable<uint> local = BuildQueryable2<uint>(this->queryable.ToMultiSet());
  std::vector<uint> evens = this->queryableEvens.ToVector();
  std::multiset<uint> result = local
    .AsQueryableMultiSet()
    .Except(evens)
    .ToMultiSet();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptExtendedMultiSetVectorDefault)
{
  IQueryable<uint> local = BuildQueryable2<uint>(this->queryable.ToMultiSet());
  std::vector<uint> evens = this->queryableEvens.ToVector();
  std::multiset<uint> result = local
    .AsExtendedQueryable<std::multiset>()
    .Except(evens)
    .ToMultiSet();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptTemplateVectorDequeDefault)
{
  IQueryable<uint> local = BuildQueryable2<uint>(this->queryable.ToVector());
  std::deque<uint> evens = this->queryableEvens.ToDeque();
  std::vector<uint> result = local
    .Except<std::vector>(evens)
    .ToVector();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptAsVectorDequeDefault)
{
  IQueryable<uint> local = BuildQueryable2<uint>(this->queryable.ToVector());
  std::deque<uint> evens = this->queryableEvens.ToDeque();
  std::vector<uint> result = local
    .AsQueryableVector()
    .Except(evens)
    .ToVector();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptExtendedVectorDequeDefault)
{
  IQueryable<uint> local = BuildQueryable2<uint>(this->queryable.ToVector());
  std::deque<uint> evens = this->queryableEvens.ToDeque();
  std::vector<uint> result = local
    .AsExtendedQueryable<std::vector>()
    .Except(evens)
    .ToVector();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptTemplateVectorListDefault)
{
  IQueryable<uint> local = BuildQueryable2<uint>(this->queryable.ToVector());
  std::list<uint> evens = this->queryableEvens.ToList();
  std::vector<uint> result = local
    .Except<std::vector>(evens)
    .ToVector();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptAsVectorListDefault)
{
  IQueryable<uint> local = BuildQueryable2<uint>(this->queryable.ToVector());
  std::list<uint> evens = this->queryableEvens.ToList();
  std::vector<uint> result = local
    .AsQueryableVector()
    .Except(evens)
    .ToVector();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptExtendedVectorListDefault)
{
  IQueryable<uint> local = BuildQueryable2<uint>(this->queryable.ToVector());
  std::list<uint> evens = this->queryableEvens.ToList();
  std::vector<uint> result = local
    .AsExtendedQueryable<std::vector>()
    .Except(evens)
    .ToVector();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptTemplateVectorMultiSetDefault)
{
  IQueryable<uint> local = BuildQueryable2<uint>(this->queryable.ToVector());
  std::multiset<uint> evens = this->queryableEvens.ToMultiSet();
  std::vector<uint> result = local
    .Except<std::vector>(evens)
    .ToVector();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptAsVectorMultiSetDefault)
{
  IQueryable<uint> local = BuildQueryable2<uint>(this->queryable.ToVector());
  std::multiset<uint> evens = this->queryableEvens.ToMultiSet();
  std::vector<uint> result = local
    .AsQueryableVector()
    .Except(evens)
    .ToVector();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptExtendedVectorMultiSetDefault)
{
  IQueryable<uint> local = BuildQueryable2<uint>(this->queryable.ToVector());
  std::multiset<uint> evens = this->queryableEvens.ToMultiSet();
  std::vector<uint> result = local
    .AsExtendedQueryable<std::vector>()
    .Except(evens)
    .ToVector();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptTemplateVectorSetDefault)
{
  IQueryable<uint> local = BuildQueryable2<uint>(this->queryable.ToVector());
  std::set<uint> evens = this->queryableEvens.ToSet();
  std::vector<uint> result = local
    .Except<std::vector>(evens)
    .ToVector();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptAsVectorSetDefault)
{
  IQueryable<uint> local = BuildQueryable2<uint>(this->queryable.ToVector());
  std::set<uint> evens = this->queryableEvens.ToSet();
  std::vector<uint> result = local
    .AsQueryableVector()
    .Except(evens)
    .ToVector();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptExtendedVectorSetDefault)
{
  IQueryable<uint> local = BuildQueryable2<uint>(this->queryable.ToVector());
  std::set<uint> evens = this->queryableEvens.ToSet();
  std::vector<uint> result = local
    .AsExtendedQueryable<std::vector>()
    .Except(evens)
    .ToVector();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, WhereTemplateExcept)
{
  int oddsOverTen = 2;
  IQueryable<uint> local = BuildQueryable2<uint>(this->queryable.ToDeque());
  std::deque<uint> evens = this->queryableEvens.ToDeque();
  std::deque<uint> result = local
    .Where([](uint value) { return value > 10; })
    .Except<std::deque>(evens)
    .ToDeque();

  ASSERT_EQ(oddsOverTen, result.size());
  for (int value : result) { ASSERT_TRUE(value > 10); }
}

TEST_F(ExceptFunctionalTest, WhereAsDequeExcept)
{
  int oddsOverTen = 2;
  IQueryable<uint> local = BuildQueryable2<uint>(this->queryable.ToDeque());
  std::deque<uint> evens = this->queryableEvens.ToDeque();
  std::deque<uint> result = local
    .Where([](uint value) { return value > 10; })
    .AsQueryableDeque()
    .Except(evens)
    .ToDeque();

  ASSERT_EQ(oddsOverTen, result.size());
  for (int value : result) { ASSERT_TRUE(value > 10); }
}

TEST_F(ExceptFunctionalTest, WhereExtendedExcept)
{
  int oddsOverTen = 2;
  IQueryable<uint> local = BuildQueryable2<uint>(this->queryable.ToDeque());
  std::deque<uint> evens = this->queryableEvens.ToDeque();
  std::deque<uint> result = local
    .Where([](uint value) { return value > 10; })
    .AsExtendedQueryable<std::deque>()
    .Except(evens)
    .ToDeque();

  ASSERT_EQ(oddsOverTen, result.size());
  for (int value : result) { ASSERT_TRUE(value > 10); }
}

TEST_F(ExceptFunctionalTest, ExceptTemplateWhere)
{
  int oddsUnderTen = 3;
  IQueryable<uint> local = BuildQueryable2<uint>(this->queryable.ToDeque());
  std::deque<uint> evens = this->queryableEvens.ToDeque();
  std::deque<uint> result = local
    .Except<std::deque>(evens)
    .Where([](uint value) { return value < 10; })
    .ToDeque();


  ASSERT_EQ(oddsUnderTen, result.size());
  for (int value : result) { ASSERT_TRUE(value < 10); }
}

TEST_F(ExceptFunctionalTest, ExceptAsDequeWhere)
{
  int oddsUnderTen = 3;
  IQueryable<uint> local = BuildQueryable2<uint>(this->queryable.ToDeque());
  std::deque<uint> evens = this->queryableEvens.ToDeque();
  std::deque<uint> result = local
    .AsQueryableDeque()
    .Except(evens)
    .Where([](uint value) { return value < 10; })
    .ToDeque();


  ASSERT_EQ(oddsUnderTen, result.size());
  for (int value : result) { ASSERT_TRUE(value < 10); }
}

TEST_F(ExceptFunctionalTest, ExceptExtendedWhere)
{
  int oddsUnderTen = 3;
  IQueryable<uint> local = BuildQueryable2<uint>(this->queryable.ToDeque());
  std::deque<uint> evens = this->queryableEvens.ToDeque();
  std::deque<uint> result = local
    .AsExtendedQueryable<std::deque>()
    .Except(evens)
    .Where([](uint value) { return value < 10; })
    .ToDeque();


  ASSERT_EQ(oddsUnderTen, result.size());
  for (int value : result) { ASSERT_TRUE(value < 10); }
}
