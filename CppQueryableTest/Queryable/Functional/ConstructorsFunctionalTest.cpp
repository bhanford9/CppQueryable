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

class ConstructorsFunctionalTest : public ::testing::Test
{
protected:
  Queryable<uint> queryable;

  void SetUp() override
  {
    this->queryable = BuildQueryable(std::vector<uint>({ 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 }));
  }

  void TearDown() override {}
};

TEST_F(ConstructorsFunctionalTest, StandardDeque)
{
  std::deque<uint> localDeque = this->queryable.ToDeque();
  int expectedCount = localDeque.size();
  Queryable<uint> local = localDeque;

  ASSERT_TRUE(local.GetType() == QueryableType::Deque);
  ASSERT_EQ(expectedCount, local.Count());

  Queryable<uint> local2(localDeque);

  ASSERT_TRUE(local2.GetType() == QueryableType::Deque);
  ASSERT_EQ(expectedCount, local2.Count());

  for (uint & value : localDeque) value++;
  int i = 0;
  local.ForEach([&](uint value)
  {
    auto it = localDeque.begin();
    std::advance(it, i);
    ASSERT_EQ(*it, value + 1);
    ASSERT_EQ(*it, local2.At(i++) + 1);
  });
}

TEST_F(ConstructorsFunctionalTest, StandardList)
{
  std::list<uint> localList = this->queryable.ToList();
  int expectedCount = localList.size();
  Queryable<uint> local = localList;

  ASSERT_TRUE(local.GetType() == QueryableType::List);
  ASSERT_EQ(expectedCount, local.Count());

  Queryable<uint> local2(localList);

  ASSERT_TRUE(local2.GetType() == QueryableType::List);
  ASSERT_EQ(expectedCount, local2.Count());

  for (uint & value : localList) value++;
  int i = 0;
  local.ForEach([&](uint value)
  {
    auto it = localList.begin();
    std::advance(it, i);
    ASSERT_EQ(*it, value + 1);
    ASSERT_EQ(*it, local2.At(i++) + 1);
  });
}

TEST_F(ConstructorsFunctionalTest, StandardMultiSet)
{
  std::multiset<uint> localMultiset = this->queryable.ToMultiSet();
  int expectedCount = localMultiset.size();
  Queryable<uint> local = localMultiset;

  ASSERT_TRUE(local.GetType() == QueryableType::MultiSet);
  ASSERT_EQ(expectedCount, local.Count());

  Queryable<uint> local2(localMultiset);

  ASSERT_TRUE(local2.GetType() == QueryableType::MultiSet);
  ASSERT_EQ(expectedCount, local2.Count());
}

TEST_F(ConstructorsFunctionalTest, StandardSet)
{
  std::set<uint> localSet = this->queryable.ToSet();
  int expectedCount = localSet.size();
  Queryable<uint> local = localSet;

  ASSERT_TRUE(local.GetType() == QueryableType::Set);
  ASSERT_EQ(expectedCount, local.Count());

  Queryable<uint> local2(localSet);

  ASSERT_TRUE(local2.GetType() == QueryableType::Set);
  ASSERT_EQ(expectedCount, local2.Count());
}

TEST_F(ConstructorsFunctionalTest, StandardVector)
{
  std::vector<uint> localVector = this->queryable.ToVector();
  int expectedCount = localVector.size();
  Queryable<uint> local = localVector;

  ASSERT_TRUE(local.GetType() == QueryableType::Vector);
  ASSERT_EQ(expectedCount, local.Count());

  Queryable<uint> local2(localVector);

  ASSERT_TRUE(local2.GetType() == QueryableType::Vector);
  ASSERT_EQ(expectedCount, local2.Count());

  for (uint & value : localVector) value++;
  int i = 0;
  local.ForEach([&](uint value)
  {
    auto it = localVector.begin();
    std::advance(it, i);
    ASSERT_EQ(*it, value + 1);
    ASSERT_EQ(*it, local2.At(i++) + 1);
  });
}