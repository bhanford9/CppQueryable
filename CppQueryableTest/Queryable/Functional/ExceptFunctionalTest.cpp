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


using namespace QueryBuilder;

class ExceptFunctionalTest : public ::testing::Test
{
protected:
  std::vector<uint> startingInput;
  std::vector<uint> evens;
  Queryable<uint> queryable;
  Queryable<uint> queryableEvens;
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
  Queryable<Person> local;
  Queryable<Person> * result = local.Except(local);

  ASSERT_TRUE(result != NULL);
  ASSERT_EQ(0, result->Count());
}

TEST_F(ExceptFunctionalTest, ExceptLocalFullInputEmpty)
{
  Queryable<uint> local;
  Queryable<uint> * result = this->queryable.Except(local);

  ASSERT_TRUE(result != NULL);
  ASSERT_EQ(this->startingInput.size(), result->Count());
}

TEST_F(ExceptFunctionalTest, ExceptLocalEmptyInputFull)
{
  Queryable<uint> local;
  Queryable<uint> * result = local.Except(this->queryable);

  ASSERT_TRUE(result != NULL);
  ASSERT_EQ(0, result->Count());
}

TEST_F(ExceptFunctionalTest, ExceptAllSame)
{
  Queryable<uint> a = BuildQueryable<uint>(std::vector<uint>({ 2, 5, 2, 5, 5, 5, 2, 2, 5 }));
  Queryable<uint> b = BuildQueryable<uint>(std::vector<uint>({ 2, 5 }));
  Queryable<uint> * result = a.Except(b);

  ASSERT_TRUE(result != NULL);
  ASSERT_EQ(0, result->Count());
}

TEST_F(ExceptFunctionalTest, ExceptCustomCompare)
{
  PersonLibrary personLibrary;
  Queryable<Person> local = BuildQueryable<Person>(personLibrary.GetPeople());
  Queryable<Person> exceptions = BuildQueryable<Person>(std::vector<Person>({
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
  Queryable<uint> local = BuildQueryable<uint>(this->queryable.ToDeque());
  Queryable<uint> evens = BuildQueryable<uint>(this->queryableEvens.ToDeque());
  Queryable<uint> * result = local.Except(evens);

  ASSERT_TRUE(result != NULL);
  ASSERT_TRUE(result->GetType() == QueryableType::Deque);
  ASSERT_EQ(this->oddCount, result->Count());
}

TEST_F(ExceptFunctionalTest, ExceptDequeListDefault)
{
  Queryable<uint> local = BuildQueryable<uint>(this->queryable.ToDeque());
  Queryable<uint> evens = BuildQueryable<uint>(this->queryableEvens.ToList());
  Queryable<uint> * result = local.Except(evens);

  ASSERT_TRUE(result != NULL);
  ASSERT_TRUE(result->GetType() == QueryableType::Deque);
  ASSERT_EQ(this->oddCount, result->Count());
}

TEST_F(ExceptFunctionalTest, ExceptDequeMultiSetDefault)
{
  Queryable<uint> local = BuildQueryable<uint>(this->queryable.ToDeque());
  Queryable<uint> evens = BuildQueryable<uint>(this->queryableEvens.ToMultiSet());
  Queryable<uint> * result = local.Except(evens);

  ASSERT_TRUE(result != NULL);
  ASSERT_TRUE(result->GetType() == QueryableType::Deque);
  ASSERT_EQ(this->oddCount, result->Count());
}

TEST_F(ExceptFunctionalTest, ExceptDequeSetDefault)
{
  Queryable<uint> local = BuildQueryable<uint>(this->queryable.ToDeque());
  Queryable<uint> evens = BuildQueryable<uint>(this->queryableEvens.ToSet());
  Queryable<uint> * result = local.Except(evens);

  ASSERT_TRUE(result != NULL);
  ASSERT_TRUE(result->GetType() == QueryableType::Deque);
  ASSERT_EQ(this->oddCount, result->Count());
}

TEST_F(ExceptFunctionalTest, ExceptDequeVectorDefault)
{
  Queryable<uint> local = BuildQueryable<uint>(this->queryable.ToDeque());
  Queryable<uint> evens = BuildQueryable<uint>(this->queryableEvens.ToVector());
  Queryable<uint> * result = local.Except(evens);

  ASSERT_TRUE(result != NULL);
  ASSERT_TRUE(result->GetType() == QueryableType::Deque);
  ASSERT_EQ(this->oddCount, result->Count());
}

TEST_F(ExceptFunctionalTest, ExceptListDequeDefault)
{
  Queryable<uint> local = BuildQueryable<uint>(this->queryable.ToList());
  Queryable<uint> evens = BuildQueryable<uint>(this->queryableEvens.ToDeque());
  Queryable<uint> * result = local.Except(evens);

  ASSERT_TRUE(result != NULL);
  ASSERT_TRUE(result->GetType() == QueryableType::List);
  ASSERT_EQ(this->oddCount, result->Count());
}

TEST_F(ExceptFunctionalTest, ExceptListMultiSetDefault)
{
  Queryable<uint> local = BuildQueryable<uint>(this->queryable.ToList());
  Queryable<uint> evens = BuildQueryable<uint>(this->queryableEvens.ToMultiSet());
  Queryable<uint> * result = local.Except(evens);

  ASSERT_TRUE(result != NULL);
  ASSERT_TRUE(result->GetType() == QueryableType::List);
  ASSERT_EQ(this->oddCount, result->Count());
}

TEST_F(ExceptFunctionalTest, ExceptListSetDefault)
{
  Queryable<uint> local = BuildQueryable<uint>(this->queryable.ToList());
  Queryable<uint> evens = BuildQueryable<uint>(this->queryableEvens.ToSet());
  Queryable<uint> * result = local.Except(evens);

  ASSERT_TRUE(result != NULL);
  ASSERT_TRUE(result->GetType() == QueryableType::List);
  ASSERT_EQ(this->oddCount, result->Count());
}

TEST_F(ExceptFunctionalTest, ExceptListVectorDefault)
{
  Queryable<uint> local = BuildQueryable<uint>(this->queryable.ToList());
  Queryable<uint> evens = BuildQueryable<uint>(this->queryableEvens.ToVector());
  Queryable<uint> * result = local.Except(evens);

  ASSERT_TRUE(result != NULL);
  ASSERT_TRUE(result->GetType() == QueryableType::List);
  ASSERT_EQ(this->oddCount, result->Count());
}

TEST_F(ExceptFunctionalTest, ExceptMultiSetDequeDefault)
{
  Queryable<uint> local = BuildQueryable<uint>(this->queryable.ToMultiSet());
  Queryable<uint> evens = BuildQueryable<uint>(this->queryableEvens.ToDeque());
  Queryable<uint> * result = local.Except(evens);

  ASSERT_TRUE(result != NULL);
  ASSERT_TRUE(result->GetType() == QueryableType::MultiSet);
  ASSERT_EQ(this->oddCount, result->Count());
}

TEST_F(ExceptFunctionalTest, ExceptMultiSetListDefault)
{
  Queryable<uint> local = BuildQueryable<uint>(this->queryable.ToMultiSet());
  Queryable<uint> evens = BuildQueryable<uint>(this->queryableEvens.ToList());
  Queryable<uint> * result = local.Except(evens);

  ASSERT_TRUE(result != NULL);
  ASSERT_TRUE(result->GetType() == QueryableType::MultiSet);
  ASSERT_EQ(this->oddCount, result->Count());
}

TEST_F(ExceptFunctionalTest, ExceptMultiSetSetDefault)
{
  Queryable<uint> local = BuildQueryable<uint>(this->queryable.ToMultiSet());
  Queryable<uint> evens = BuildQueryable<uint>(this->queryableEvens.ToSet());
  Queryable<uint> * result = local.Except(evens);

  ASSERT_TRUE(result != NULL);
  ASSERT_TRUE(result->GetType() == QueryableType::MultiSet);
  ASSERT_EQ(this->oddCount, result->Count());
}

TEST_F(ExceptFunctionalTest, ExceptMultiSetVectorDefault)
{
  Queryable<uint> local = BuildQueryable<uint>(this->queryable.ToMultiSet());
  Queryable<uint> evens = BuildQueryable<uint>(this->queryableEvens.ToVector());
  Queryable<uint> * result = local.Except(evens);

  ASSERT_TRUE(result != NULL);
  ASSERT_TRUE(result->GetType() == QueryableType::MultiSet);
  ASSERT_EQ(this->oddCount, result->Count());
}

TEST_F(ExceptFunctionalTest, ExceptVectorDequeDefault)
{
  Queryable<uint> local = BuildQueryable<uint>(this->queryable.ToVector());
  Queryable<uint> evens = BuildQueryable<uint>(this->queryableEvens.ToDeque());
  Queryable<uint> * result = local.Except(evens);

  ASSERT_TRUE(result != NULL);
  ASSERT_TRUE(result->GetType() == QueryableType::Vector);
  ASSERT_EQ(this->oddCount, result->Count());
}

TEST_F(ExceptFunctionalTest, ExceptVectorListDefault)
{
  Queryable<uint> local = BuildQueryable<uint>(this->queryable.ToVector());
  Queryable<uint> evens = BuildQueryable<uint>(this->queryableEvens.ToList());
  Queryable<uint> * result = local.Except(evens);

  ASSERT_TRUE(result != NULL);
  ASSERT_TRUE(result->GetType() == QueryableType::Vector);
  ASSERT_EQ(this->oddCount, result->Count());
}

TEST_F(ExceptFunctionalTest, ExceptVectorMultiSetDefault)
{
  Queryable<uint> local = BuildQueryable<uint>(this->queryable.ToVector());
  Queryable<uint> evens = BuildQueryable<uint>(this->queryableEvens.ToMultiSet());
  Queryable<uint> * result = local.Except(evens);

  ASSERT_TRUE(result != NULL);
  ASSERT_TRUE(result->GetType() == QueryableType::Vector);
  ASSERT_EQ(this->oddCount, result->Count());
}

TEST_F(ExceptFunctionalTest, ExceptVectorSetDefault)
{
  Queryable<uint> local = BuildQueryable<uint>(this->queryable.ToVector());
  Queryable<uint> evens = BuildQueryable<uint>(this->queryableEvens.ToSet());
  Queryable<uint> * result = local.Except(evens);

  ASSERT_TRUE(result != NULL);
  ASSERT_TRUE(result->GetType() == QueryableType::Vector);
  ASSERT_EQ(this->oddCount, result->Count());
}

TEST_F(ExceptFunctionalTest, ExceptWhere)
{
  int oddsOverTen = 2;
  Queryable<uint> local = BuildQueryable<uint>(this->queryable.ToDeque());
  Queryable<uint> evens = BuildQueryable<uint>(this->queryableEvens.ToDeque());
  Queryable<uint> * result = local
    .Where([](uint value) { return value > 10; })
    .Except(evens);

  ASSERT_TRUE(result != NULL);
  ASSERT_TRUE(result->GetType() == QueryableType::Deque);
  ASSERT_EQ(oddsOverTen, result->Count());
  result->ForEach([](int value) { ASSERT_TRUE(value > 10); });
}

TEST_F(ExceptFunctionalTest, WhereExcept)
{
  int oddsUnderTen = 3;
  Queryable<uint> local = BuildQueryable<uint>(this->queryable.ToDeque());
  Queryable<uint> evens = BuildQueryable<uint>(this->queryableEvens.ToDeque());
  Queryable<uint> & result = local
    .Except(evens)
    ->Where([](uint value) { return value < 10; });

  ASSERT_TRUE(result.GetType() == QueryableType::Deque);
  ASSERT_EQ(oddsUnderTen, result.Count());
  result.ForEach([](int value) { ASSERT_TRUE(value < 10); });
}
