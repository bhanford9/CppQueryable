#include <gtest/gtest.h>

#include <array>
#include <deque>
#include <exception>
#include <iostream>
#include <list>
#include <set>
#include <string>
#include <vector>

#include "../../../DataStructures/Gender.h"
#include "../../../DataStructures/Person.h"
#include "../../../DataStructures/PersonLibrary.h"

#include "../../../Queryable/QueryBuilder.h"
#include "../../../Queryable/QueryableVector.h"

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
    this->queryable = BuildQueryable(this->startingInput);
    this->queryableEvens = BuildQueryable(this->evens);
  }

  void TearDown() override {}
};

TEST_F(ExceptFunctionalTest, ExceptLocalEmptyInputEmpty)
{
  QueryableVector<Person> local;
  Queryable<Person> * result = local.Except(local);

  ASSERT_TRUE(result != NULL);
  ASSERT_EQ(0, result->Count());
}

TEST_F(ExceptFunctionalTest, ExceptLocalFullInputEmpty)
{
  QueryableVector<uint> local;
  Queryable<uint> * result = this->queryable.Except(local);

  ASSERT_TRUE(result != NULL);
  ASSERT_EQ(this->startingInput.size(), result->Count());
}

TEST_F(ExceptFunctionalTest, ExceptLocalEmptyInputFull)
{
  QueryableVector<uint> local;
  Queryable<uint> * result = local.Except(this->queryable);

  ASSERT_TRUE(result != NULL);
  ASSERT_EQ(0, result->Count());
}

TEST_F(ExceptFunctionalTest, ExceptAllSame)
{
  QueryableVector<uint> a = BuildQueryable<uint>(std::vector<uint>({ 2, 5, 2, 5, 5, 5, 2, 2, 5 }));
  QueryableVector<uint> b = BuildQueryable<uint>(std::vector<uint>({ 2, 5 }));
  Queryable<uint> * result = a.Except(b);

  ASSERT_TRUE(result != NULL);
  ASSERT_EQ(0, result->Count());
}

TEST_F(ExceptFunctionalTest, ExceptCustomCompare)
{
  PersonLibrary personLibrary;
  QueryableVector<Person> local = BuildQueryable<Person>(personLibrary.GetPeople());
  QueryableVector<Person> exceptions = BuildQueryable<Person>(std::vector<Person>({
    Person(33, "Person 4", 12, 60, Gender::Male),
    Person(99, "Person 6", 14, 62, Gender::Female)
  }));

  int originalLength = local.Count();
  int afterExceptLength = originalLength - exceptions.Count();

  Queryable<Person> * result = local.Except(
    exceptions,
    [](Person a, Person b) { return a.GetName() < b.GetName(); });

  ASSERT_TRUE(result != NULL);
  ASSERT_EQ(afterExceptLength, result->Count());
  result->ForEach([](Person p)
  {
    ASSERT_TRUE(p.GetName() != "Person 4");
    ASSERT_TRUE(p.GetName() != "Person 6");
  });
}

TEST_F(ExceptFunctionalTest, ExceptDequeDequeDefault)
{
  QueryableDeque<uint> local = BuildQueryable<uint>(this->queryable.ToDeque());
  QueryableDeque<uint> evens = BuildQueryable<uint>(this->queryableEvens.ToDeque());
  Queryable<uint> * result = local.Except(evens);

  ASSERT_TRUE(result != NULL);
  ASSERT_TRUE(result->GetType() == QueryableType::Deque);
  ASSERT_EQ(this->oddCount, result->Count());
}

TEST_F(ExceptFunctionalTest, ExceptDequeListDefault)
{
  QueryableDeque<uint> local = BuildQueryable<uint>(this->queryable.ToDeque());
  QueryableList<uint> evens = BuildQueryable<uint>(this->queryableEvens.ToList());
  Queryable<uint> * result = local.Except(evens);

  ASSERT_TRUE(result != NULL);
  ASSERT_TRUE(result->GetType() == QueryableType::Deque);
  ASSERT_EQ(this->oddCount, result->Count());
}

TEST_F(ExceptFunctionalTest, ExceptDequeMultiSetDefault)
{
  QueryableDeque<uint> local = BuildQueryable<uint>(this->queryable.ToDeque());
  QueryableMultiSet<uint> evens = BuildQueryable<uint>(this->queryableEvens.ToMultiSet());
  Queryable<uint> * result = local.Except(evens);

  ASSERT_TRUE(result != NULL);
  ASSERT_TRUE(result->GetType() == QueryableType::Deque);
  ASSERT_EQ(this->oddCount, result->Count());
}

TEST_F(ExceptFunctionalTest, ExceptDequeSetDefault)
{
  QueryableDeque<uint> local = BuildQueryable<uint>(this->queryable.ToDeque());
  QueryableSet<uint> evens = BuildQueryable<uint>(this->queryableEvens.ToSet());
  Queryable<uint> * result = local.Except(evens);

  ASSERT_TRUE(result != NULL);
  ASSERT_TRUE(result->GetType() == QueryableType::Deque);
  ASSERT_EQ(this->oddCount, result->Count());
}

TEST_F(ExceptFunctionalTest, ExceptDequeVectorDefault)
{
  QueryableDeque<uint> local = BuildQueryable<uint>(this->queryable.ToDeque());
  QueryableVector<uint> evens = BuildQueryable<uint>(this->queryableEvens.ToVector());
  Queryable<uint> * result = local.Except(evens);

  ASSERT_TRUE(result != NULL);
  ASSERT_TRUE(result->GetType() == QueryableType::Deque);
  ASSERT_EQ(this->oddCount, result->Count());
}

TEST_F(ExceptFunctionalTest, ExceptListDequeDefault)
{
  QueryableList<uint> local = BuildQueryable<uint>(this->queryable.ToList());
  QueryableDeque<uint> evens = BuildQueryable<uint>(this->queryableEvens.ToDeque());
  Queryable<uint> * result = local.Except(evens);

  ASSERT_TRUE(result != NULL);
  ASSERT_TRUE(result->GetType() == QueryableType::List);
  ASSERT_EQ(this->oddCount, result->Count());
}

TEST_F(ExceptFunctionalTest, ExceptListMultiSetDefault)
{
  QueryableList<uint> local = BuildQueryable<uint>(this->queryable.ToList());
  QueryableMultiSet<uint> evens = BuildQueryable<uint>(this->queryableEvens.ToMultiSet());
  Queryable<uint> * result = local.Except(evens);

  ASSERT_TRUE(result != NULL);
  ASSERT_TRUE(result->GetType() == QueryableType::List);
  ASSERT_EQ(this->oddCount, result->Count());
}

TEST_F(ExceptFunctionalTest, ExceptListSetDefault)
{
  QueryableList<uint> local = BuildQueryable<uint>(this->queryable.ToList());
  QueryableSet<uint> evens = BuildQueryable<uint>(this->queryableEvens.ToSet());
  Queryable<uint> * result = local.Except(evens);

  ASSERT_TRUE(result != NULL);
  ASSERT_TRUE(result->GetType() == QueryableType::List);
  ASSERT_EQ(this->oddCount, result->Count());
}

TEST_F(ExceptFunctionalTest, ExceptListVectorDefault)
{
  QueryableList<uint> local = BuildQueryable<uint>(this->queryable.ToList());
  QueryableVector<uint> evens = BuildQueryable<uint>(this->queryableEvens.ToVector());
  Queryable<uint> * result = local.Except(evens);

  ASSERT_TRUE(result != NULL);
  ASSERT_TRUE(result->GetType() == QueryableType::List);
  ASSERT_EQ(this->oddCount, result->Count());
}

TEST_F(ExceptFunctionalTest, ExceptMultiSetDequeDefault)
{
  QueryableMultiSet<uint> local = BuildQueryable<uint>(this->queryable.ToMultiSet());
  QueryableDeque<uint> evens = BuildQueryable<uint>(this->queryableEvens.ToDeque());
  Queryable<uint> * result = local.Except(evens);

  ASSERT_TRUE(result != NULL);
  ASSERT_TRUE(result->GetType() == QueryableType::MultiSet);
  ASSERT_EQ(this->oddCount, result->Count());
}

TEST_F(ExceptFunctionalTest, ExceptMultiSetListDefault)
{
  QueryableMultiSet<uint> local = BuildQueryable<uint>(this->queryable.ToMultiSet());
  QueryableList<uint> evens = BuildQueryable<uint>(this->queryableEvens.ToList());
  Queryable<uint> * result = local.Except(evens);

  ASSERT_TRUE(result != NULL);
  ASSERT_TRUE(result->GetType() == QueryableType::MultiSet);
  ASSERT_EQ(this->oddCount, result->Count());
}

TEST_F(ExceptFunctionalTest, ExceptMultiSetSetDefault)
{
  QueryableMultiSet<uint> local = BuildQueryable<uint>(this->queryable.ToMultiSet());
  QueryableSet<uint> evens = BuildQueryable<uint>(this->queryableEvens.ToSet());
  Queryable<uint> * result = local.Except(evens);

  ASSERT_TRUE(result != NULL);
  ASSERT_TRUE(result->GetType() == QueryableType::MultiSet);
  ASSERT_EQ(this->oddCount, result->Count());
}

TEST_F(ExceptFunctionalTest, ExceptMultiSetVectorDefault)
{
  QueryableMultiSet<uint> local = BuildQueryable<uint>(this->queryable.ToMultiSet());
  QueryableVector<uint> evens = BuildQueryable<uint>(this->queryableEvens.ToVector());
  Queryable<uint> * result = local.Except(evens);

  ASSERT_TRUE(result != NULL);
  ASSERT_TRUE(result->GetType() == QueryableType::MultiSet);
  ASSERT_EQ(this->oddCount, result->Count());
}

TEST_F(ExceptFunctionalTest, ExceptVectorDequeDefault)
{
  QueryableVector<uint> local = BuildQueryable<uint>(this->queryable.ToVector());
  QueryableDeque<uint> evens = BuildQueryable<uint>(this->queryableEvens.ToDeque());
  Queryable<uint> * result = local.Except(evens);

  ASSERT_TRUE(result != NULL);
  ASSERT_TRUE(result->GetType() == QueryableType::Vector);
  ASSERT_EQ(this->oddCount, result->Count());
}

TEST_F(ExceptFunctionalTest, ExceptVectorListDefault)
{
  QueryableVector<uint> local = BuildQueryable<uint>(this->queryable.ToVector());
  QueryableList<uint> evens = BuildQueryable<uint>(this->queryableEvens.ToList());
  Queryable<uint> * result = local.Except(evens);

  ASSERT_TRUE(result != NULL);
  ASSERT_TRUE(result->GetType() == QueryableType::Vector);
  ASSERT_EQ(this->oddCount, result->Count());
}

TEST_F(ExceptFunctionalTest, ExceptVectorMultiSetDefault)
{
  QueryableVector<uint> local = BuildQueryable<uint>(this->queryable.ToVector());
  QueryableMultiSet<uint> evens = BuildQueryable<uint>(this->queryableEvens.ToMultiSet());
  Queryable<uint> * result = local.Except(evens);

  ASSERT_TRUE(result != NULL);
  ASSERT_TRUE(result->GetType() == QueryableType::Vector);
  ASSERT_EQ(this->oddCount, result->Count());
}

TEST_F(ExceptFunctionalTest, ExceptVectorSetDefault)
{
  QueryableVector<uint> local = BuildQueryable<uint>(this->queryable.ToVector());
  QueryableSet<uint> evens = BuildQueryable<uint>(this->queryableEvens.ToSet());
  Queryable<uint> * result = local.Except(evens);

  ASSERT_TRUE(result != NULL);
  ASSERT_TRUE(result->GetType() == QueryableType::Vector);
  ASSERT_EQ(this->oddCount, result->Count());
}

TEST_F(ExceptFunctionalTest, ExceptWhere)
{
  int oddsOverTen = 2;
  QueryableDeque<uint> local = BuildQueryable<uint>(this->queryable.ToDeque());
  QueryableDeque<uint> evens = BuildQueryable<uint>(this->queryableEvens.ToDeque());
  Queryable<uint> * result = local
    .Where([](uint value) { return value > 10; })
    ->Except(evens);

  ASSERT_TRUE(result != NULL);
  ASSERT_TRUE(result->GetType() == QueryableType::Deque);
  ASSERT_EQ(oddsOverTen, result->Count());
  result->ForEach([](int value) { ASSERT_TRUE(value > 10); });
}

TEST_F(ExceptFunctionalTest, WhereExcept)
{
  int oddsUnderTen = 3;
  QueryableDeque<uint> local = BuildQueryable<uint>(this->queryable.ToDeque());
  QueryableDeque<uint> evens = BuildQueryable<uint>(this->queryableEvens.ToDeque());
  Queryable<uint> * result = local
    .Except(evens)
    ->Where([](uint value) { return value < 10; });

  ASSERT_TRUE(result != NULL);
  ASSERT_TRUE(result->GetType() == QueryableType::Deque);
  ASSERT_EQ(oddsUnderTen, result->Count());
  result->ForEach([](int value) { ASSERT_TRUE(value < 10); });
}
