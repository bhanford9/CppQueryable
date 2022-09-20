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
  QueryableVector<size_t> queryable;
  QueryableVector<size_t> queryableEvens;
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

TEST_F(ExceptFunctionalTest, ExceptLocalFullInputEmpty)
{
  std::vector<size_t> local;
  std::vector<size_t> result = this->queryable
    .Except(local)
    .ToVector();

  ASSERT_EQ(this->startingInput.size(), result.size());
}

TEST_F(ExceptFunctionalTest, ExceptAllSame)
{
  QueryableVector<size_t> a = BuildQueryable2<size_t>(std::vector<size_t>({ 2, 5, 2, 5, 5, 5, 2, 2, 5 }));
  std::vector<size_t> b = std::vector<size_t>({ 2, 5 });
  std::vector<size_t> result = a
    .Except<>(b)
    .ToVector();

  ASSERT_EQ(0, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptCustomCompare)
{
  PersonLibrary personLibrary;
  QueryableVector<Person> local = BuildQueryable2<Person>(personLibrary.GetPeople());
  QueryableVector<Person> exceptions = BuildQueryable2<Person>(std::vector<Person>({
    Person(33, "Person 4", 12, 60, Gender::Male),
    Person(99, "Person 6", 14, 62, Gender::Female)
  }));

  int originalLength = local.Count();
  int afterExceptLength = originalLength - exceptions.Count();

  std::vector<Person> result = local
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

TEST_F(ExceptFunctionalTest, ExceptDequeDequeDefault)
{
  QueryableDeque<size_t> local = BuildQueryable2<size_t>(this->queryable.ToDeque());
  std::deque<size_t> evens = this->queryableEvens.ToDeque();
  std::deque<size_t> result = local
    .Except(evens)
    .ToDeque();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptDequeListDefault)
{
  QueryableDeque<size_t> local = BuildQueryable2<size_t>(this->queryable.ToDeque());
  std::list<size_t> evens = this->queryableEvens.ToList();
  std::deque<size_t> result = local
    .Except(evens)
    .ToDeque();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptDequeMultiSetDefault)
{
  QueryableDeque<size_t> local = BuildQueryable2<size_t>(this->queryable.ToDeque());
  std::multiset<size_t> evens = this->queryableEvens.ToMultiSet();
  std::deque<size_t> result = local
    .Except(evens)
    .ToDeque();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptDequeSetDefault)
{
  QueryableDeque<size_t> local = BuildQueryable2<size_t>(this->queryable.ToDeque());
  std::set<size_t> evens = this->queryableEvens.ToSet();
  std::deque<size_t> result = local
    .Except(evens)
    .ToDeque();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptDequeVectorDefault)
{
  QueryableDeque<size_t> local = BuildQueryable2<size_t>(this->queryable.ToDeque());
  std::vector<size_t> evens = this->queryableEvens.ToVector();
  std::deque<size_t> result = local
    .Except(evens)
    .ToDeque();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptListDequeDefault)
{
  QueryableList<size_t> local = BuildQueryable2<size_t>(this->queryable.ToList());
  std::deque<size_t> evens = this->queryableEvens.ToDeque();
  std::list<size_t> result = local
    .Except(evens)
    .ToList();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptListMultiSetDefault)
{
  QueryableList<size_t> local = BuildQueryable2<size_t>(this->queryable.ToList());
  std::multiset<size_t> evens = this->queryableEvens.ToMultiSet();
  std::list<size_t> result = local
    .Except(evens)
    .ToList();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptListSetDefault)
{
  QueryableList<size_t> local = BuildQueryable2<size_t>(this->queryable.ToList());
  std::set<size_t> evens = this->queryableEvens.ToSet();
  std::list<size_t> result = local
    .Except(evens)
    .ToList();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptListVectorDefault)
{
  QueryableList<size_t> local = BuildQueryable2<size_t>(this->queryable.ToList());
  std::vector<size_t> evens = this->queryableEvens.ToVector();
  std::list<size_t> result = local
    .Except(evens)
    .ToList();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptMultiSetDequeDefault)
{
  QueryableMultiSet<size_t> local = BuildQueryable2<size_t>(this->queryable.ToMultiSet());
  std::deque<size_t> evens = this->queryableEvens.ToDeque();
  std::multiset<size_t> result = local
    .Except(evens)
    .ToMultiSet();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptMultiSetListDefault)
{
  QueryableMultiSet<size_t> local = BuildQueryable2<size_t>(this->queryable.ToMultiSet());
  std::list<size_t> evens = this->queryableEvens.ToList();
  std::multiset<size_t> result = local
    .Except(evens)
    .ToMultiSet();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptMultiSetSetDefault)
{
  QueryableMultiSet<size_t> local = BuildQueryable2<size_t>(this->queryable.ToMultiSet());
  std::set<size_t> evens = this->queryableEvens.ToSet();
  std::multiset<size_t> result = local
    .Except(evens)
    .ToMultiSet();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptMultiSetVectorDefault)
{
  QueryableMultiSet<size_t> local = BuildQueryable2<size_t>(this->queryable.ToMultiSet());
  std::vector<size_t> evens = this->queryableEvens.ToVector();
  std::multiset<size_t> result = local
    .Except(evens)
    .ToMultiSet();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptSetDequeDefault)
{
  QueryableSet<size_t> local = BuildQueryable2<size_t>(this->queryable.ToSet());
  std::deque<size_t> evens = this->queryableEvens.ToDeque();
  std::set<size_t> result = local
    .Except(evens)
    .ToSet();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptSetListDefault)
{
  QueryableSet<size_t> local = BuildQueryable2<size_t>(this->queryable.ToSet());
  std::list<size_t> evens = this->queryableEvens.ToList();
  std::set<size_t> result = local
    .Except(evens)
    .ToSet();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptSetSetDefault)
{
  QueryableSet<size_t> local = BuildQueryable2<size_t>(this->queryable.ToSet());
  std::set<size_t> evens = this->queryableEvens.ToSet();
  std::set<size_t> result = local
    .Except(evens)
    .ToSet();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptSetVectorDefault)
{
  QueryableSet<size_t> local = BuildQueryable2<size_t>(this->queryable.ToSet());
  std::vector<size_t> evens = this->queryableEvens.ToVector();
  std::set<size_t> result = local
    .Except(evens)
    .ToSet();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptVectorDequeDefault)
{
  QueryableVector<size_t> local = BuildQueryable2<size_t>(this->queryable.ToVector());
  std::deque<size_t> evens = this->queryableEvens.ToDeque();
  std::vector<size_t> result = local
    .Except(evens)
    .ToVector();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptVectorListDefault)
{
  QueryableVector<size_t> local = BuildQueryable2<size_t>(this->queryable.ToVector());
  std::list<size_t> evens = this->queryableEvens.ToList();
  std::vector<size_t> result = local
    .Except(evens)
    .ToVector();

  ASSERT_EQ(this->oddCount, result.size());
}


TEST_F(ExceptFunctionalTest, ExceptVectorMultiSetDefault)
{
  QueryableVector<size_t> local = BuildQueryable2<size_t>(this->queryable.ToVector());
  std::multiset<size_t> evens = this->queryableEvens.ToMultiSet();
  std::vector<size_t> result = local
    .Except(evens)
    .ToVector();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptVectorSetDefault)
{
  QueryableVector<size_t> local = BuildQueryable2<size_t>(this->queryable.ToVector());
  std::set<size_t> evens = this->queryableEvens.ToSet();
  std::vector<size_t> result = local
    .Except(evens)
    .ToVector();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, WhereExcept)
{
  int oddsOverTen = 2;
  QueryableDeque<size_t> local = BuildQueryable2<size_t>(this->queryable.ToDeque());
  std::deque<size_t> evens = this->queryableEvens.ToDeque();
  std::deque<size_t> result = local
    .Where([](size_t value) { return value > 10; })
    .Except(evens)
    .ToDeque();

  ASSERT_EQ(oddsOverTen, result.size());
  for (int value : result) { ASSERT_TRUE(value > 10); }
}

TEST_F(ExceptFunctionalTest, ExceptWhere)
{
  int oddsUnderTen = 3;
  QueryableDeque<size_t> local = BuildQueryable2<size_t>(this->queryable.ToDeque());
  std::deque<size_t> evens = this->queryableEvens.ToDeque();
  std::deque<size_t> result = local
    .Except(evens)
    .Where([](size_t value) { return value < 10; })
    .ToDeque();


  ASSERT_EQ(oddsUnderTen, result.size());
  for (int value : result) { ASSERT_TRUE(value < 10); }
}

