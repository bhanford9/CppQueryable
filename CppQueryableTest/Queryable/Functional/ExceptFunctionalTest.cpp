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
  InternalQueryable<uint> queryable;
  InternalQueryable<uint> queryableEvens;
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
  InternalQueryable<Person> local;
  InternalQueryable<Person> & result = local.Except(local);

  ASSERT_EQ(0, result.Count());
}

TEST_F(ExceptFunctionalTest, ExceptLocalFullInputEmpty)
{
  InternalQueryable<uint> local;
  InternalQueryable<uint> & result = this->queryable.Except(local);

  ASSERT_EQ(this->startingInput.size(), result.Count());
}

TEST_F(ExceptFunctionalTest, ExceptLocalEmptyInputFull)
{
  InternalQueryable<uint> local;
  InternalQueryable<uint> & result = local.Except(this->queryable);

  ASSERT_EQ(0, result.Count());
}

TEST_F(ExceptFunctionalTest, ExceptAllSame)
{
  InternalQueryable<uint> a = BuildQueryable<uint>(std::vector<uint>({ 2, 5, 2, 5, 5, 5, 2, 2, 5 }));
  InternalQueryable<uint> b = BuildQueryable<uint>(std::vector<uint>({ 2, 5 }));
  InternalQueryable<uint> & result = a.Except(b);

  ASSERT_EQ(0, result.Count());
}

TEST_F(ExceptFunctionalTest, ExceptCustomCompare)
{
  PersonLibrary personLibrary;
  InternalQueryable<Person> local = BuildQueryable<Person>(personLibrary.GetPeople());
  InternalQueryable<Person> exceptions = BuildQueryable<Person>(std::vector<Person>({
    Person(33, "Person 4", 12, 60, Gender::Male),
    Person(99, "Person 6", 14, 62, Gender::Female)
  }));

  int originalLength = local.Count();
  int afterExceptLength = originalLength - exceptions.Count();

  InternalQueryable<Person> & result = local.Except(
    exceptions,
    [](Person a, Person b) { return a.GetName() < b.GetName(); });

  ASSERT_EQ(afterExceptLength, result.Count());
  result.ForEach([](Person p)
  {
    ASSERT_TRUE(p.GetName() != "Person 4");
    ASSERT_TRUE(p.GetName() != "Person 6");
  });
}

TEST_F(ExceptFunctionalTest, ExceptDequeDequeDefault)
{
  InternalQueryable<uint> local = BuildQueryable<uint>(this->queryable.ToDeque());
  InternalQueryable<uint> evens = BuildQueryable<uint>(this->queryableEvens.ToDeque());
  InternalQueryable<uint> & result = local.Except(evens);

  ASSERT_TRUE(result.GetType() == QueryableType::Deque);
  ASSERT_EQ(this->oddCount, result.Count());
}

TEST_F(ExceptFunctionalTest, ExceptDequeListDefault)
{
  InternalQueryable<uint> local = BuildQueryable<uint>(this->queryable.ToDeque());
  InternalQueryable<uint> evens = BuildQueryable<uint>(this->queryableEvens.ToList());
  InternalQueryable<uint> & result = local.Except(evens);

  ASSERT_TRUE(result.GetType() == QueryableType::Deque);
  ASSERT_EQ(this->oddCount, result.Count());
}

TEST_F(ExceptFunctionalTest, ExceptDequeMultiSetDefault)
{
  InternalQueryable<uint> local = BuildQueryable<uint>(this->queryable.ToDeque());
  InternalQueryable<uint> evens = BuildQueryable<uint>(this->queryableEvens.ToMultiSet());
  InternalQueryable<uint> & result = local.Except(evens);

  ASSERT_TRUE(result.GetType() == QueryableType::Deque);
  ASSERT_EQ(this->oddCount, result.Count());
}

TEST_F(ExceptFunctionalTest, ExceptDequeSetDefault)
{
  InternalQueryable<uint> local = BuildQueryable<uint>(this->queryable.ToDeque());
  InternalQueryable<uint> evens = BuildQueryable<uint>(this->queryableEvens.ToSet());
  InternalQueryable<uint> & result = local.Except(evens);

  ASSERT_TRUE(result.GetType() == QueryableType::Deque);
  ASSERT_EQ(this->oddCount, result.Count());
}

TEST_F(ExceptFunctionalTest, ExceptDequeVectorDefault)
{
  InternalQueryable<uint> local = BuildQueryable<uint>(this->queryable.ToDeque());
  InternalQueryable<uint> evens = BuildQueryable<uint>(this->queryableEvens.ToVector());
  InternalQueryable<uint> & result = local.Except(evens);

  ASSERT_TRUE(result.GetType() == QueryableType::Deque);
  ASSERT_EQ(this->oddCount, result.Count());
}

TEST_F(ExceptFunctionalTest, ExceptListDequeDefault)
{
  InternalQueryable<uint> local = BuildQueryable<uint>(this->queryable.ToList());
  InternalQueryable<uint> evens = BuildQueryable<uint>(this->queryableEvens.ToDeque());
  InternalQueryable<uint> & result = local.Except(evens);

  ASSERT_TRUE(result.GetType() == QueryableType::List);
  ASSERT_EQ(this->oddCount, result.Count());
}

TEST_F(ExceptFunctionalTest, ExceptListMultiSetDefault)
{
  InternalQueryable<uint> local = BuildQueryable<uint>(this->queryable.ToList());
  InternalQueryable<uint> evens = BuildQueryable<uint>(this->queryableEvens.ToMultiSet());
  InternalQueryable<uint> & result = local.Except(evens);

  ASSERT_TRUE(result.GetType() == QueryableType::List);
  ASSERT_EQ(this->oddCount, result.Count());
}

TEST_F(ExceptFunctionalTest, ExceptListSetDefault)
{
  InternalQueryable<uint> local = BuildQueryable<uint>(this->queryable.ToList());
  InternalQueryable<uint> evens = BuildQueryable<uint>(this->queryableEvens.ToSet());
  InternalQueryable<uint> & result = local.Except(evens);

  ASSERT_TRUE(result.GetType() == QueryableType::List);
  ASSERT_EQ(this->oddCount, result.Count());
}

TEST_F(ExceptFunctionalTest, ExceptListVectorDefault)
{
  InternalQueryable<uint> local = BuildQueryable<uint>(this->queryable.ToList());
  InternalQueryable<uint> evens = BuildQueryable<uint>(this->queryableEvens.ToVector());
  InternalQueryable<uint> & result = local.Except(evens);

  ASSERT_TRUE(result.GetType() == QueryableType::List);
  ASSERT_EQ(this->oddCount, result.Count());
}

TEST_F(ExceptFunctionalTest, ExceptMultiSetDequeDefault)
{
  InternalQueryable<uint> local = BuildQueryable<uint>(this->queryable.ToMultiSet());
  InternalQueryable<uint> evens = BuildQueryable<uint>(this->queryableEvens.ToDeque());
  InternalQueryable<uint> & result = local.Except(evens);

  ASSERT_TRUE(result.GetType() == QueryableType::MultiSet);
  ASSERT_EQ(this->oddCount, result.Count());
}

TEST_F(ExceptFunctionalTest, ExceptMultiSetListDefault)
{
  InternalQueryable<uint> local = BuildQueryable<uint>(this->queryable.ToMultiSet());
  InternalQueryable<uint> evens = BuildQueryable<uint>(this->queryableEvens.ToList());
  InternalQueryable<uint> & result = local.Except(evens);

  ASSERT_TRUE(result.GetType() == QueryableType::MultiSet);
  ASSERT_EQ(this->oddCount, result.Count());
}

TEST_F(ExceptFunctionalTest, ExceptMultiSetSetDefault)
{
  InternalQueryable<uint> local = BuildQueryable<uint>(this->queryable.ToMultiSet());
  InternalQueryable<uint> evens = BuildQueryable<uint>(this->queryableEvens.ToSet());
  InternalQueryable<uint> & result = local.Except(evens);

  ASSERT_TRUE(result.GetType() == QueryableType::MultiSet);
  ASSERT_EQ(this->oddCount, result.Count());
}

TEST_F(ExceptFunctionalTest, ExceptMultiSetVectorDefault)
{
  InternalQueryable<uint> local = BuildQueryable<uint>(this->queryable.ToMultiSet());
  InternalQueryable<uint> evens = BuildQueryable<uint>(this->queryableEvens.ToVector());
  InternalQueryable<uint> & result = local.Except(evens);

  ASSERT_TRUE(result.GetType() == QueryableType::MultiSet);
  ASSERT_EQ(this->oddCount, result.Count());
}

TEST_F(ExceptFunctionalTest, ExceptVectorDequeDefault)
{
  InternalQueryable<uint> local = BuildQueryable<uint>(this->queryable.ToVector());
  InternalQueryable<uint> evens = BuildQueryable<uint>(this->queryableEvens.ToDeque());
  InternalQueryable<uint> & result = local.Except(evens);

  ASSERT_TRUE(result.GetType() == QueryableType::Vector);
  ASSERT_EQ(this->oddCount, result.Count());
}

TEST_F(ExceptFunctionalTest, ExceptVectorListDefault)
{
  InternalQueryable<uint> local = BuildQueryable<uint>(this->queryable.ToVector());
  InternalQueryable<uint> evens = BuildQueryable<uint>(this->queryableEvens.ToList());
  InternalQueryable<uint> & result = local.Except(evens);

  ASSERT_TRUE(result.GetType() == QueryableType::Vector);
  ASSERT_EQ(this->oddCount, result.Count());
}

TEST_F(ExceptFunctionalTest, ExceptVectorMultiSetDefault)
{
  InternalQueryable<uint> local = BuildQueryable<uint>(this->queryable.ToVector());
  InternalQueryable<uint> evens = BuildQueryable<uint>(this->queryableEvens.ToMultiSet());
  InternalQueryable<uint> & result = local.Except(evens);

  ASSERT_TRUE(result.GetType() == QueryableType::Vector);
  ASSERT_EQ(this->oddCount, result.Count());
}

TEST_F(ExceptFunctionalTest, ExceptVectorSetDefault)
{
  InternalQueryable<uint> local = BuildQueryable<uint>(this->queryable.ToVector());
  InternalQueryable<uint> evens = BuildQueryable<uint>(this->queryableEvens.ToSet());
  InternalQueryable<uint> & result = local.Except(evens);

  ASSERT_TRUE(result.GetType() == QueryableType::Vector);
  ASSERT_EQ(this->oddCount, result.Count());
}

TEST_F(ExceptFunctionalTest, WhereExcept)
{
  int oddsOverTen = 2;
  InternalQueryable<uint> local = BuildQueryable<uint>(this->queryable.ToDeque());
  InternalQueryable<uint> evens = BuildQueryable<uint>(this->queryableEvens.ToDeque());
  InternalQueryable<uint> & result = local
    .Where([](uint value) { return value > 10; })
    .Except(evens);

  ASSERT_TRUE(result.GetType() == QueryableType::Deque);
  ASSERT_EQ(oddsOverTen, result.Count());
  result.ForEach([](int value) { ASSERT_TRUE(value > 10); });
}

TEST_F(ExceptFunctionalTest, ExceptWhere)
{
  int oddsUnderTen = 3;
  InternalQueryable<uint> local = BuildQueryable<uint>(this->queryable.ToDeque());
  InternalQueryable<uint> evens = BuildQueryable<uint>(this->queryableEvens.ToDeque());
  InternalQueryable<uint> & result = local
    .Except(evens)
    .Where([](uint value) { return value < 10; });

  ASSERT_TRUE(result.GetType() == QueryableType::Deque);
  ASSERT_EQ(oddsUnderTen, result.Count());
  result.ForEach([](int value) { ASSERT_TRUE(value < 10); });
}
