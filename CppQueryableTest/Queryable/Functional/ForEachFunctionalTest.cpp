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

class ForEachFunctionalTest : public ::testing::Test
{
protected:
  Queryable<uint> queryable;

  void SetUp() override
  {
    this->queryable = BuildQueryable(std::vector<uint>({ 7, 4, 7, 4, 3, 76, 8, 45, 34, 76, 8, 867 }));
  }

  template<typename TObj>
  void TestForEach (Queryable<TObj> * localQueryable)
  {
    std::vector<TObj> iterated(localQueryable->Count(), 0);
    int i = 0;

    localQueryable->ForEach([&](TObj value)
    {
      iterated[i++] = value;
    });

    for (i = 0; i < localQueryable->Count(); i++)
    {
      ASSERT_EQ(localQueryable->At(i), iterated[i]);
    }
  }

  void TearDown() override {}
};

TEST_F(ForEachFunctionalTest, ForEachVectorUninitialized)
{
  Queryable<Person> emptyQueryable;
  emptyQueryable.ForEach([](Person p) { throw std::runtime_error("Should not hit"); });
  ASSERT_TRUE(true);
}

TEST_F(ForEachFunctionalTest, ForEachVector)
{
  std::vector<uint> iterated(this->queryable.Count(), 0);
  int i = 0;

  this->queryable.ForEach([&](uint value)
  {
    iterated[i++] = value;
  });

  for (i = 0; i < this->queryable.Count(); i++)
  {
    ASSERT_EQ(this->queryable.At(i), iterated[i]);
  }
}

TEST_F(ForEachFunctionalTest, ForEachSet)
{
  Queryable<uint> localQueryable = this->queryable.ToSet();
  this->TestForEach(&localQueryable);
}

TEST_F(ForEachFunctionalTest, ForEachMultiSet)
{
  Queryable<uint> localQueryable = this->queryable.ToMultiSet();
  this->TestForEach(&localQueryable);
}

TEST_F(ForEachFunctionalTest, ForEachDeque)
{
  Queryable<uint> localQueryable = this->queryable.ToDeque();
  this->TestForEach(&localQueryable);
}

TEST_F(ForEachFunctionalTest, ForEachList)
{
  Queryable<uint> localQueryable = this->queryable.ToList();
  this->TestForEach(&localQueryable);
}

TEST_F(ForEachFunctionalTest, ForEachWhere)
{
  Queryable<uint> queryableVector = BuildQueryable(std::vector<uint>({ 7, 0, 7, 2, 3, 4, 6, 45, 8, 1, 3, 10 }));
  int expectedCount = 6;
  int count = 0;
  queryableVector
    .Where([](uint value) { return value % 2 == 0; })
    ->ForEach([&](uint value) { ASSERT_EQ(count++ * 2, value); });

  ASSERT_EQ(expectedCount, count);
}
