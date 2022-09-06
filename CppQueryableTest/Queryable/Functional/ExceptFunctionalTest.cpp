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
  std::vector<size_t> startingInput;
  std::vector<size_t> evens;
  IQueryable<size_t> queryable;
  IQueryable<size_t> queryableEvens;
  int oddCount = 5;

  ExceptFunctionalTest() :
    startingInput( std::vector<size_t>({ 1, 4, 7, 4, 3, 76, 8, 45, 34, 76, 0, 867 })),
    evens( std::vector<size_t>({ 4, 76, 8, 34, 76, 0 })),
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
  std::vector<size_t> local;
  std::vector<size_t> result = this->queryable
    .Except<std::vector>(local)
    .ToVector();

  ASSERT_EQ(this->startingInput.size(), result.size());
}

TEST_F(ExceptFunctionalTest, ExceptLocalFullInputEmptyAsVector)
{
  std::vector<size_t> local;
  std::vector<size_t> result = this->queryable
    .AsQueryableVector()
    .Except(local)
    .ToVector();

  ASSERT_EQ(this->startingInput.size(), result.size());
}

TEST_F(ExceptFunctionalTest, ExceptLocalFullInputEmptyExtended)
{
  std::vector<size_t> local;
  std::vector<size_t> result = this->queryable
    .AsExtendedQueryable<std::vector>()
    .Except(local)
    .ToVector();

  ASSERT_EQ(this->startingInput.size(), result.size());
}

TEST_F(ExceptFunctionalTest, ExceptAllSameTemplate)
{
  IQueryable<size_t> a = BuildQueryable2<size_t>(std::vector<size_t>({ 2, 5, 2, 5, 5, 5, 2, 2, 5 }));
  std::vector<size_t> b = std::vector<size_t>({ 2, 5 });
  std::vector<size_t> result = a
    .Except<std::vector>(b)
    .ToVector();

  ASSERT_EQ(0, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptAllSameAsVector)
{
  IQueryable<size_t> a = BuildQueryable2<size_t>(std::vector<size_t>({ 2, 5, 2, 5, 5, 5, 2, 2, 5 }));
  std::vector<size_t> b = std::vector<size_t>({ 2, 5 });
  std::vector<size_t> result = a
    .AsQueryableVector()
    .Except(b)
    .ToVector();

  ASSERT_EQ(0, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptAllSameExtended)
{
  IQueryable<size_t> a = BuildQueryable2<size_t>(std::vector<size_t>({ 2, 5, 2, 5, 5, 5, 2, 2, 5 }));
  std::vector<size_t> b = std::vector<size_t>({ 2, 5 });
  std::vector<size_t> result = a
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
  IQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToDeque());
  std::deque<size_t> evens = this->queryableEvens.ToDeque();
  std::deque<size_t> result = local
    .Except<std::deque>(evens)
    .ToDeque();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptAsDequeDequeDefault)
{
  IQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToDeque());
  std::deque<size_t> evens = this->queryableEvens.ToDeque();
  std::deque<size_t> result = local
    .AsQueryableDeque()
    .Except(evens)
    .ToDeque();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptExtendedDequeDequeDefault)
{
  IQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToDeque());
  std::deque<size_t> evens = this->queryableEvens.ToDeque();
  std::deque<size_t> result = local
    .AsExtendedQueryable<std::deque>()
    .Except(evens)
    .ToDeque();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptTemplateDequeListDefault)
{
  IQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToDeque());
  std::list<size_t> evens = this->queryableEvens.ToList();
  std::deque<size_t> result = local
    .Except<std::deque>(evens)
    .ToDeque();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptAsDequeListDefault)
{
  IQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToDeque());
  std::list<size_t> evens = this->queryableEvens.ToList();
  std::deque<size_t> result = local
    .AsQueryableDeque()
    .Except(evens)
    .ToDeque();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptExtendedDequeListDefault)
{
  IQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToDeque());
  std::list<size_t> evens = this->queryableEvens.ToList();
  std::deque<size_t> result = local
    .AsExtendedQueryable<std::deque>()
    .Except(evens)
    .ToDeque();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptTemplateDequeMultiSetDefault)
{
  IQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToDeque());
  std::multiset<size_t> evens = this->queryableEvens.ToMultiSet();
  std::deque<size_t> result = local
    .Except<std::deque>(evens)
    .ToDeque();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptAsDequeMultiSetDefault)
{
  IQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToDeque());
  std::multiset<size_t> evens = this->queryableEvens.ToMultiSet();
  std::deque<size_t> result = local
    .AsQueryableDeque()
    .Except(evens)
    .ToDeque();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptExtendedDequeMultiSetDefault)
{
  IQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToDeque());
  std::multiset<size_t> evens = this->queryableEvens.ToMultiSet();
  std::deque<size_t> result = local
    .AsExtendedQueryable<std::deque>()
    .Except(evens)
    .ToDeque();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptTemplateDequeSetDefault)
{
  IQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToDeque());
  std::set<size_t> evens = this->queryableEvens.ToSet();
  std::deque<size_t> result = local
    .Except<std::deque>(evens)
    .ToDeque();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptAsDequeSetDefault)
{
  IQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToDeque());
  std::set<size_t> evens = this->queryableEvens.ToSet();
  std::deque<size_t> result = local
    .AsQueryableDeque()
    .Except(evens)
    .ToDeque();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptExtendedDequeSetDefault)
{
  IQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToDeque());
  std::set<size_t> evens = this->queryableEvens.ToSet();
  std::deque<size_t> result = local
    .AsExtendedQueryable<std::deque>()
    .Except(evens)
    .ToDeque();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptTemplateDequeVectorDefault)
{
  IQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToDeque());
  std::vector<size_t> evens = this->queryableEvens.ToVector();
  std::deque<size_t> result = local
    .Except<std::deque>(evens)
    .ToDeque();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptAsDequeVectorDefault)
{
  IQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToDeque());
  std::vector<size_t> evens = this->queryableEvens.ToVector();
  std::deque<size_t> result = local
    .AsQueryableDeque()
    .Except(evens)
    .ToDeque();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptExtendedDequeVectorDefault)
{
  IQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToDeque());
  std::vector<size_t> evens = this->queryableEvens.ToVector();
  std::deque<size_t> result = local
    .AsExtendedQueryable<std::deque>()
    .Except(evens)
    .ToDeque();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptTemplateListDequeDefault)
{
  IQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToList());
  std::deque<size_t> evens = this->queryableEvens.ToDeque();
  std::list<size_t> result = local
    .Except<std::list>(evens)
    .ToList();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptAsListDequeDefault)
{
  IQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToList());
  std::deque<size_t> evens = this->queryableEvens.ToDeque();
  std::list<size_t> result = local
    .AsQueryableList()
    .Except(evens)
    .ToList();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptExtendedListDequeDefault)
{
  IQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToList());
  std::deque<size_t> evens = this->queryableEvens.ToDeque();
  std::list<size_t> result = local
    .AsExtendedQueryable<std::list>()
    .Except(evens)
    .ToList();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptTemplateListMultiSetDefault)
{
  IQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToList());
  std::multiset<size_t> evens = this->queryableEvens.ToMultiSet();
  std::list<size_t> result = local
    .Except<std::list>(evens)
    .ToList();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptAsListMultiSetDefault)
{
  IQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToList());
  std::multiset<size_t> evens = this->queryableEvens.ToMultiSet();
  std::list<size_t> result = local
    .AsQueryableList()
    .Except(evens)
    .ToList();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptExtendedListMultiSetDefault)
{
  IQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToList());
  std::multiset<size_t> evens = this->queryableEvens.ToMultiSet();
  std::list<size_t> result = local
    .AsExtendedQueryable<std::list>()
    .Except(evens)
    .ToList();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptTemplateListSetDefault)
{
  IQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToList());
  std::set<size_t> evens = this->queryableEvens.ToSet();
  std::list<size_t> result = local
    .Except<std::list>(evens)
    .ToList();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptAsListSetDefault)
{
  IQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToList());
  std::set<size_t> evens = this->queryableEvens.ToSet();
  std::list<size_t> result = local
    .AsQueryableList()
    .Except(evens)
    .ToList();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptExtendedListSetDefault)
{
  IQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToList());
  std::set<size_t> evens = this->queryableEvens.ToSet();
  std::list<size_t> result = local
    .AsExtendedQueryable<std::list>()
    .Except(evens)
    .ToList();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptTemplateListVectorDefault)
{
  IQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToList());
  std::vector<size_t> evens = this->queryableEvens.ToVector();
  std::list<size_t> result = local
    .Except<std::list>(evens)
    .ToList();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptAsListVectorDefault)
{
  IQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToList());
  std::vector<size_t> evens = this->queryableEvens.ToVector();
  std::list<size_t> result = local
    .AsQueryableList()
    .Except(evens)
    .ToList();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptExtendedListVectorDefault)
{
  IQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToList());
  std::vector<size_t> evens = this->queryableEvens.ToVector();
  std::list<size_t> result = local
    .AsExtendedQueryable<std::list>()
    .Except(evens)
    .ToList();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptTemplateMultiSetDequeDefault)
{
  ISortedQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToMultiSet());
  std::deque<size_t> evens = this->queryableEvens.ToDeque();
  std::multiset<size_t> result = local
    .Except<std::multiset>(evens)
    .ToMultiSet();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptAsMultiSetDequeDefault)
{
  ISortedQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToMultiSet());
  std::deque<size_t> evens = this->queryableEvens.ToDeque();
  std::multiset<size_t> result = local
    .AsQueryableMultiSet()
    .Except(evens)
    .ToMultiSet();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptExtendedMultiSetDequeDefault)
{
  ISortedQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToMultiSet());
  std::deque<size_t> evens = this->queryableEvens.ToDeque();
  std::multiset<size_t> result = local
    .AsExtendedQueryable<std::multiset>()
    .Except(evens)
    .ToMultiSet();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptTemplateMultiSetListDefault)
{
  ISortedQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToMultiSet());
  std::list<size_t> evens = this->queryableEvens.ToList();
  std::multiset<size_t> result = local
    .Except<std::multiset>(evens)
    .ToMultiSet();

  ASSERT_EQ(this->oddCount, result.size());
}


TEST_F(ExceptFunctionalTest, ExceptAsMultiSetListDefault)
{
  ISortedQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToMultiSet());
  std::list<size_t> evens = this->queryableEvens.ToList();
  std::multiset<size_t> result = local
    .AsQueryableMultiSet()
    .Except(evens)
    .ToMultiSet();

  ASSERT_EQ(this->oddCount, result.size());
}


TEST_F(ExceptFunctionalTest, ExceptExtendedMultiSetListDefault)
{
  ISortedQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToMultiSet());
  std::list<size_t> evens = this->queryableEvens.ToList();
  std::multiset<size_t> result = local
    .AsExtendedQueryable<std::multiset>()
    .Except(evens)
    .ToMultiSet();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptTemplateMultiSetSetDefault)
{
  ISortedQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToMultiSet());
  std::set<size_t> evens = this->queryableEvens.ToSet();
  std::multiset<size_t> result = local
    .Except<std::multiset>(evens)
    .ToMultiSet();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptAsMultiSetSetDefault)
{
  ISortedQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToMultiSet());
  std::set<size_t> evens = this->queryableEvens.ToSet();
  std::multiset<size_t> result = local
    .AsQueryableMultiSet()
    .Except(evens)
    .ToMultiSet();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptExtendedMultiSetSetDefault)
{
  ISortedQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToMultiSet());
  std::set<size_t> evens = this->queryableEvens.ToSet();
  std::multiset<size_t> result = local
    .AsExtendedQueryable<std::multiset>()
    .Except(evens)
    .ToMultiSet();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptTemplateMultiSetVectorDefault)
{
  ISortedQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToMultiSet());
  std::vector<size_t> evens = this->queryableEvens.ToVector();
  std::multiset<size_t> result = local
    .Except<std::multiset>(evens)
    .ToMultiSet();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptAsMultiSetVectorDefault)
{
  ISortedQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToMultiSet());
  std::vector<size_t> evens = this->queryableEvens.ToVector();
  std::multiset<size_t> result = local
    .AsQueryableMultiSet()
    .Except(evens)
    .ToMultiSet();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptExtendedMultiSetVectorDefault)
{
  ISortedQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToMultiSet());
  std::vector<size_t> evens = this->queryableEvens.ToVector();
  std::multiset<size_t> result = local
    .AsExtendedQueryable<std::multiset>()
    .Except(evens)
    .ToMultiSet();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptTemplateSetDequeDefault)
{
  ISortedQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToSet());
  std::deque<size_t> evens = this->queryableEvens.ToDeque();
  std::set<size_t> result = local
    .Except<std::set>(evens)
    .ToSet();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptAsSetDequeDefault)
{
  ISortedQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToSet());
  std::deque<size_t> evens = this->queryableEvens.ToDeque();
  std::set<size_t> result = local
    .AsQueryableSet()
    .Except(evens)
    .ToSet();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptExtendedSetDequeDefault)
{
  ISortedQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToSet());
  std::deque<size_t> evens = this->queryableEvens.ToDeque();
  std::set<size_t> result = local
    .AsExtendedQueryable<std::set>()
    .Except(evens)
    .ToSet();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptTemplateSetListDefault)
{
  ISortedQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToSet());
  std::list<size_t> evens = this->queryableEvens.ToList();
  std::set<size_t> result = local
    .Except<std::set>(evens)
    .ToSet();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptAsSetListDefault)
{
  ISortedQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToSet());
  std::list<size_t> evens = this->queryableEvens.ToList();
  std::set<size_t> result = local
    .AsQueryableSet()
    .Except(evens)
    .ToSet();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptExtendedSetListDefault)
{
  ISortedQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToSet());
  std::list<size_t> evens = this->queryableEvens.ToList();
  std::set<size_t> result = local
    .AsExtendedQueryable<std::set>()
    .Except(evens)
    .ToSet();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptTemplateSetSetDefault)
{
  ISortedQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToSet());
  std::set<size_t> evens = this->queryableEvens.ToSet();
  std::set<size_t> result = local
    .Except<std::set>(evens)
    .ToSet();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptAsSetSetDefault)
{
  ISortedQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToSet());
  std::set<size_t> evens = this->queryableEvens.ToSet();
  std::set<size_t> result = local
    .AsQueryableSet()
    .Except(evens)
    .ToSet();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptExtendedSetSetDefault)
{
  ISortedQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToSet());
  std::set<size_t> evens = this->queryableEvens.ToSet();
  std::set<size_t> result = local
    .AsExtendedQueryable<std::set>()
    .Except(evens)
    .ToSet();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptTemplateSetVectorDefault)
{
  ISortedQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToSet());
  std::vector<size_t> evens = this->queryableEvens.ToVector();
  std::set<size_t> result = local
    .Except<std::set>(evens)
    .ToSet();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptAsSetVectorDefault)
{
  ISortedQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToSet());
  std::vector<size_t> evens = this->queryableEvens.ToVector();
  std::set<size_t> result = local
    .AsQueryableSet()
    .Except(evens)
    .ToSet();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptExtendedSetVectorDefault)
{
  ISortedQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToSet());
  std::vector<size_t> evens = this->queryableEvens.ToVector();
  std::set<size_t> result = local
    .AsExtendedQueryable<std::set>()
    .Except(evens)
    .ToSet();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptTemplateVectorDequeDefault)
{
  IQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToVector());
  std::deque<size_t> evens = this->queryableEvens.ToDeque();
  std::vector<size_t> result = local
    .Except<std::vector>(evens)
    .ToVector();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptAsVectorDequeDefault)
{
  IQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToVector());
  std::deque<size_t> evens = this->queryableEvens.ToDeque();
  std::vector<size_t> result = local
    .AsQueryableVector()
    .Except(evens)
    .ToVector();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptExtendedVectorDequeDefault)
{
  IQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToVector());
  std::deque<size_t> evens = this->queryableEvens.ToDeque();
  std::vector<size_t> result = local
    .AsExtendedQueryable<std::vector>()
    .Except(evens)
    .ToVector();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptTemplateVectorListDefault)
{
  IQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToVector());
  std::list<size_t> evens = this->queryableEvens.ToList();
  std::vector<size_t> result = local
    .Except<std::vector>(evens)
    .ToVector();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptAsVectorListDefault)
{
  IQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToVector());
  std::list<size_t> evens = this->queryableEvens.ToList();
  std::vector<size_t> result = local
    .AsQueryableVector()
    .Except(evens)
    .ToVector();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptExtendedVectorListDefault)
{
  IQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToVector());
  std::list<size_t> evens = this->queryableEvens.ToList();
  std::vector<size_t> result = local
    .AsExtendedQueryable<std::vector>()
    .Except(evens)
    .ToVector();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptTemplateVectorMultiSetDefault)
{
  IQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToVector());
  std::multiset<size_t> evens = this->queryableEvens.ToMultiSet();
  std::vector<size_t> result = local
    .Except<std::vector>(evens)
    .ToVector();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptAsVectorMultiSetDefault)
{
  IQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToVector());
  std::multiset<size_t> evens = this->queryableEvens.ToMultiSet();
  std::vector<size_t> result = local
    .AsQueryableVector()
    .Except(evens)
    .ToVector();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptExtendedVectorMultiSetDefault)
{
  IQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToVector());
  std::multiset<size_t> evens = this->queryableEvens.ToMultiSet();
  std::vector<size_t> result = local
    .AsExtendedQueryable<std::vector>()
    .Except(evens)
    .ToVector();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptTemplateVectorSetDefault)
{
  IQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToVector());
  std::set<size_t> evens = this->queryableEvens.ToSet();
  std::vector<size_t> result = local
    .Except<std::vector>(evens)
    .ToVector();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptAsVectorSetDefault)
{
  IQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToVector());
  std::set<size_t> evens = this->queryableEvens.ToSet();
  std::vector<size_t> result = local
    .AsQueryableVector()
    .Except(evens)
    .ToVector();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptExtendedVectorSetDefault)
{
  IQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToVector());
  std::set<size_t> evens = this->queryableEvens.ToSet();
  std::vector<size_t> result = local
    .AsExtendedQueryable<std::vector>()
    .Except(evens)
    .ToVector();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, WhereTemplateExcept)
{
  int oddsOverTen = 2;
  IQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToDeque());
  std::deque<size_t> evens = this->queryableEvens.ToDeque();
  std::deque<size_t> result = local
    .Where([](size_t value) { return value > 10; })
    .Except<std::deque>(evens)
    .ToDeque();

//   std::cout << "Evens:" << std::endl;
//   for (size_t value : evens) std::cout << value << ", ";
//   std::cout << "\nResults:" << std::endl;
//   for (size_t value : result) std::cout << value << ", ";
//   std::cout << std::endl;

  ASSERT_EQ(oddsOverTen, result.size());
  for (int value : result) { ASSERT_TRUE(value > 10); }
}

TEST_F(ExceptFunctionalTest, WhereAsDequeExcept)
{
  int oddsOverTen = 2;
  IQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToDeque());
  std::deque<size_t> evens = this->queryableEvens.ToDeque();
  std::deque<size_t> result = local
    .Where([](size_t value) { return value > 10; })
    .AsQueryableDeque()
    .Except(evens)
    .ToDeque();

  ASSERT_EQ(oddsOverTen, result.size());
  for (int value : result) { ASSERT_TRUE(value > 10); }
}

TEST_F(ExceptFunctionalTest, WhereExtendedExcept)
{
  int oddsOverTen = 2;
  IQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToDeque());
  std::deque<size_t> evens = this->queryableEvens.ToDeque();
  std::deque<size_t> result = local
    .Where([](size_t value) { return value > 10; })
    .AsExtendedQueryable<std::deque>()
    .Except(evens)
    .ToDeque();

  ASSERT_EQ(oddsOverTen, result.size());
  for (int value : result) { ASSERT_TRUE(value > 10); }
}

TEST_F(ExceptFunctionalTest, ExceptTemplateWhere)
{
  int oddsUnderTen = 3;
  IQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToDeque());
  std::deque<size_t> evens = this->queryableEvens.ToDeque();
  std::deque<size_t> result = local
    .Except<std::deque>(evens)
    .Where([](size_t value) { return value < 10; })
    .ToDeque();


  ASSERT_EQ(oddsUnderTen, result.size());
  for (int value : result) { ASSERT_TRUE(value < 10); }
}

TEST_F(ExceptFunctionalTest, ExceptAsDequeWhere)
{
  int oddsUnderTen = 3;
  IQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToDeque());
  std::deque<size_t> evens = this->queryableEvens.ToDeque();
  std::deque<size_t> result = local
    .AsQueryableDeque()
    .Except(evens)
    .Where([](size_t value) { return value < 10; })
    .ToDeque();


  ASSERT_EQ(oddsUnderTen, result.size());
  for (int value : result) { ASSERT_TRUE(value < 10); }
}

TEST_F(ExceptFunctionalTest, ExceptExtendedWhere)
{
  int oddsUnderTen = 3;
  IQueryable<size_t> local = BuildQueryable2<size_t>(this->queryable.ToDeque());
  std::deque<size_t> evens = this->queryableEvens.ToDeque();
  std::deque<size_t> result = local
    .AsExtendedQueryable<std::deque>()
    .Except(evens)
    .Where([](size_t value) { return value < 10; })
    .ToDeque();


  ASSERT_EQ(oddsUnderTen, result.size());
  for (int value : result) { ASSERT_TRUE(value < 10); }
}
