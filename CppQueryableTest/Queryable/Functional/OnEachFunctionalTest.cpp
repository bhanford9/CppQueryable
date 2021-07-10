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

class OnEachFunctionalTest : public ::testing::Test
{
protected:
  QueryableVector<uint> queryable;
  std::vector<uint> expectedWithDuplicates;
  std::set<uint> expectedWithoutDuplicates;

  void SetUp() override
  {
    this->queryable = QueryableVector<uint>({ 7, 4, 7, 4, 3, 76, 8, 45, 34, 76, 8, 867 });
    this->queryable.ForEach([&](uint value)
    {
      this->expectedWithDuplicates.push_back(value + 9);
      this->expectedWithoutDuplicates.insert(value + 9);
    });
  }

  void TearDown() override {}
};

TEST_F(OnEachFunctionalTest, OnEachVectorUninitialized)
{
  QueryableVector<Person> emptyQueryable;
  emptyQueryable.OnEach([](Person & p) { p.SetName("anything"); });
  ASSERT_TRUE(true);
}

TEST_F(OnEachFunctionalTest, OnEachInternalChange)
{
  std::string expectedName = "anything";
  int expectedAge = 32;
  std::vector<Person> people({Person(1, "bob", 30, 74, Gender::Male)});
  QueryableVector<Person> localQueryable(people);

  localQueryable.OnEach([&](Person & p)
  {
    p.SetName(expectedName);
    p.SetAge(expectedAge);
  });

  ASSERT_EQ(expectedName, localQueryable.At(0).GetName());
  ASSERT_EQ(expectedAge, localQueryable.At(0).GetAge());
}

TEST_F(OnEachFunctionalTest, OnEachVector)
{
  this->queryable.OnEach([](uint & value) { value += 9; });

  for (int i = 0; i < this->queryable.Count(); i++)
  {
    ASSERT_EQ(this->expectedWithDuplicates[i], this->queryable.At(i));
  }
}

// sets do not contain mutable contents and a separate OnEach method would need to be created for these

// TEST_F(OnEachFunctionalTest, OnEachSet)
// {
//   Queryable<uint, std::set> localQueryable = this->queryable.ToSet();
//   localQueryable.OnEach([](uint * value) { *value += 9; });
//
//   int i = 0;
//
//   for (uint value : this->expectedWithoutDuplicates)
//   {
//     std::cout << "expected: " << value << ", actual: " << localQueryable.At(i) << std::endl;
//     ASSERT_EQ(value, localQueryable.At(i++));
//   }
// }

// TEST_F(OnEachFunctionalTest, OnEachMultiSet)
// {
//   Queryable<uint, std::multiset> localQueryable = this->queryable.ToMultiSet();
//   localQueryable.OnEach([](uint * value) { *value += 9; });
//
//   for (int i = 0; i < localQueryable.Count(); i++)
//   {
//     ASSERT_EQ(this->expectedWithDuplicates[i], localQueryable.At(i));
//   }
// }

TEST_F(OnEachFunctionalTest, OnEachDeque)
{
  QueryableDeque<uint> localQueryable = this->queryable.ToDeque();
  localQueryable.OnEach([](uint & value) { value += 9; });

  for (int i = 0; i < localQueryable.Count(); i++)
  {
    ASSERT_EQ(this->expectedWithDuplicates[i], localQueryable.At(i));
  }
}

TEST_F(OnEachFunctionalTest, OnEachList)
{
  QueryableList<uint> localQueryable = this->queryable.ToList();
  localQueryable.OnEach([](uint & value) { value += 9; });

  for (int i = 0; i < localQueryable.Count(); i++)
  {
    ASSERT_EQ(this->expectedWithDuplicates[i], localQueryable.At(i));
  }
}
