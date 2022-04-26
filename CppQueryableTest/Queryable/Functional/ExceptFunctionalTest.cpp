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
  QueryableVector<uint> queryable;
  QueryableVector<uint> queryableEvens;
  int oddCount = 5;

  void SetUp() override
  {
    this->startingInput = std::vector<uint>({ 1, 4, 7, 4, 3, 76, 8, 45, 34, 76, 0, 867 });
    this->evens = std::vector<uint>({ 4, 76, 8, 34, 76, 0 });
    this->queryable = BuildQueryable2(this->startingInput);
    this->queryableEvens = BuildQueryable2(this->evens);
  }

  void TearDown() override {}
};

TEST_F(ExceptFunctionalTest, ExceptLocalFullInputEmpty)
{
  std::vector<uint> local;
  std::vector<uint> result = this->queryable.Except(local).ToVector();

  ASSERT_EQ(this->startingInput.size(), result.size());
}

TEST_F(ExceptFunctionalTest, ExceptAllSame)
{
  QueryableVector<uint> a = BuildQueryable2<uint>(std::vector<uint>({ 2, 5, 2, 5, 5, 5, 2, 2, 5 }));
  std::vector<uint> b = std::vector<uint>({ 2, 5 });
  std::vector<uint> result = a.Except(b).ToVector();

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

  std::vector<Person> result = local.Except(
    exceptions.ToVector(),
    [](Person a, Person b) { return a.GetName() < b.GetName(); }).ToVector();

  ASSERT_EQ(afterExceptLength, result.size());
  for (Person p : result)
  {
    ASSERT_TRUE(p.GetName() != "Person 4");
    ASSERT_TRUE(p.GetName() != "Person 6");
  }
}

TEST_F(ExceptFunctionalTest, ExceptDequeDequeDefault)
{
  QueryableDeque<uint> local = BuildQueryable2<uint>(this->queryable.ToDeque());
  std::deque<uint> evens = this->queryableEvens.ToDeque();
  std::deque<uint> result = local.Except(evens).ToDeque();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptDequeListDefault)
{
  QueryableDeque<uint> local = BuildQueryable2<uint>(this->queryable.ToDeque());
  std::list<uint> evens = this->queryableEvens.ToList();
  std::deque<uint> result = local.Except(evens).ToDeque();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptDequeMultiSetDefault)
{
  QueryableDeque<uint> local = BuildQueryable2<uint>(this->queryable.ToDeque());
  std::multiset<uint> evens = this->queryableEvens.ToMultiSet();
  std::deque<uint> result = local.Except(evens).ToDeque();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptDequeSetDefault)
{
  QueryableDeque<uint> local = BuildQueryable2<uint>(this->queryable.ToDeque());
  std::set<uint> evens = this->queryableEvens.ToSet();
  std::deque<uint> result = local.Except(evens).ToDeque();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptDequeVectorDefault)
{
  QueryableDeque<uint> local = BuildQueryable2<uint>(this->queryable.ToDeque());
  std::vector<uint> evens = this->queryableEvens.ToVector();
  std::deque<uint> result = local.Except(evens).ToDeque();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptListDequeDefault)
{
  QueryableList<uint> local = BuildQueryable2<uint>(this->queryable.ToList());
  std::deque<uint> evens = this->queryableEvens.ToDeque();
  std::list<uint> result = local.Except(evens).ToList();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptListMultiSetDefault)
{
  QueryableList<uint> local = BuildQueryable2<uint>(this->queryable.ToList());
  std::multiset<uint> evens = this->queryableEvens.ToMultiSet();
  std::list<uint> result = local.Except(evens).ToList();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptListSetDefault)
{
  QueryableList<uint> local = BuildQueryable2<uint>(this->queryable.ToList());
  std::set<uint> evens = this->queryableEvens.ToSet();
  std::list<uint> result = local.Except(evens).ToList();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptListVectorDefault)
{
  QueryableList<uint> local = BuildQueryable2<uint>(this->queryable.ToList());
  std::vector<uint> evens = this->queryableEvens.ToVector();
  std::list<uint> result = local.Except(evens).ToList();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptMultiSetDequeDefault)
{
  QueryableMultiSet<uint> local = BuildQueryable2<uint>(this->queryable.ToMultiSet());
  std::deque<uint> evens = this->queryableEvens.ToDeque();
  std::multiset<uint> result = local.Except(evens).ToMultiSet();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptMultiSetListDefault)
{
  // TODO --> all tests need to be written like this instead
  QueryableMultiSet<uint> local = BuildQueryable2<uint>(this->queryable.ToMultiSet());
  // QueryableList<uint> evens = BuildQueryable2<uint>(this->queryableEvens.ToList());
  std::multiset<uint> result = local.Except(this->queryableEvens.ToList()).ToMultiSet();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptMultiSetSetDefault)
{
  QueryableMultiSet<uint> local = BuildQueryable2<uint>(this->queryable.ToMultiSet());
  std::set<uint> evens = this->queryableEvens.ToSet();
  std::multiset<uint> result = local.Except(evens).ToMultiSet();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptMultiSetVectorDefault)
{
  QueryableMultiSet<uint> local = BuildQueryable2<uint>(this->queryable.ToMultiSet());
  std::vector<uint> evens = this->queryableEvens.ToVector();
  std::multiset<uint> result = local.Except(evens).ToMultiSet();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptVectorDequeDefault)
{
  QueryableVector<uint> local = BuildQueryable2<uint>(this->queryable.ToVector());
  std::deque<uint> evens = this->queryableEvens.ToDeque();
  std::vector<uint> result = local.Except(evens).ToVector();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptVectorListDefault)
{
  QueryableVector<uint> local = BuildQueryable2<uint>(this->queryable.ToVector());
  std::list<uint> evens = this->queryableEvens.ToList();
  std::vector<uint> result = local.Except(evens).ToVector();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptVectorMultiSetDefault)
{
  QueryableVector<uint> local = BuildQueryable2<uint>(this->queryable.ToVector());
  std::multiset<uint> evens = this->queryableEvens.ToMultiSet();
  std::vector<uint> result = local.Except(evens).ToVector();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, ExceptVectorSetDefault)
{
  QueryableVector<uint> local = BuildQueryable2<uint>(this->queryable.ToVector());
  std::set<uint> evens = this->queryableEvens.ToSet();
  std::vector<uint> result = local.Except(evens).ToVector();

  ASSERT_EQ(this->oddCount, result.size());
}

TEST_F(ExceptFunctionalTest, WhereExcept)
{
  int oddsOverTen = 2;
  QueryableDeque<uint> local = BuildQueryable2<uint>(this->queryable.ToDeque());
  std::deque<uint> evens = this->queryableEvens.ToDeque();
  std::deque<uint> result = local
    .Where([](uint value) { return value > 10; })
    .Except(evens)
    .ToDeque();

  ASSERT_EQ(oddsOverTen, result.size());
  for (int value : result) { ASSERT_TRUE(value > 10); }
}

TEST_F(ExceptFunctionalTest, ExceptWhere)
{
  int oddsUnderTen = 3;
  QueryableDeque<uint> local = BuildQueryable2<uint>(this->queryable.ToDeque());
  std::deque<uint> evens = this->queryableEvens.ToDeque();
  std::deque<uint> result = local
    .Except(evens)
    .Where([](uint value) { return value < 10; })
    .ToDeque();


  ASSERT_EQ(oddsUnderTen, result.size());
  for (int value : result) { ASSERT_TRUE(value < 10); }
}
