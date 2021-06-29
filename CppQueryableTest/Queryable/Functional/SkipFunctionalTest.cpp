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

#include "../../../Queryable/Queryable.h"

class SkipFunctionalTest : public ::testing::Test
{
protected:
  int SkipCount = 5;
  Queryable<uint, std::vector> queryable;

  void SetUp() override
  {
    this->queryable = Queryable<uint, std::vector>({ 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 });
  }

  template<typename TObj, template<typename...> typename TIterable>
  void TestSkip(Queryable<TObj, TIterable> localQueryable, int toSkip)
  {
    std::vector<uint> expected;
    for (int i = toSkip; i < localQueryable.Count(); i++)
    {
      expected.push_back(localQueryable.At(i));
    }

    Queryable<uint, TIterable> result = localQueryable.Skip(toSkip);

    ASSERT_EQ(expected.size(), result.Count());

    for (int i = 0; i < result.Count(); i++)
    {
      ASSERT_EQ(expected[i], result.At(i));
    }
  }

  template<typename TObj, template<typename...> typename TIterable>
  void TestSkipNegative(Queryable<TObj, TIterable> localQueryable, int toSkip)
  {
    std::vector<uint> expected;
    int endIndex = localQueryable.Count() + toSkip;
    for (int i = 0; i < endIndex; i++)
    {
      expected.push_back(localQueryable.At(i));
    }

    Queryable<uint, TIterable> result = localQueryable.Skip(toSkip);

    ASSERT_EQ(expected.size(), result.Count());

    for (int i = 0; i < result.Count(); i++)
    {
      ASSERT_EQ(expected[i], result.At(i));
    }
  }

  void TearDown() override {}
};

TEST_F(SkipFunctionalTest, SkipVectorUninitialized)
{
  Queryable<Person, std::vector> emptyQueryable;
  Queryable<Person, std::vector> result = emptyQueryable.Skip(this->SkipCount);

  ASSERT_EQ(0, result.Count());
}

TEST_F(SkipFunctionalTest, SkipVectorSkipMoreThanSize)
{
  this->TestSkip(this->queryable, this->queryable.Count() + 1);
}

TEST_F(SkipFunctionalTest, SkipVector)
{
  this->TestSkip(this->queryable, this->SkipCount);
}

TEST_F(SkipFunctionalTest, SkipSet)
{
  this->TestSkip(Queryable<uint, std::set>(this->queryable.ToSet()), this->SkipCount);
}

TEST_F(SkipFunctionalTest, SkipMultiSet)
{
  this->TestSkip(Queryable<uint, std::multiset>(this->queryable.ToMultiSet()), this->SkipCount);
}

TEST_F(SkipFunctionalTest, SkipDeque)
{
  this->TestSkip(Queryable<uint, std::deque>(this->queryable.ToDeque()), this->SkipCount);
}

TEST_F(SkipFunctionalTest, SkipList)
{
  this->TestSkip(Queryable<uint, std::list>(this->queryable.ToList()), this->SkipCount);
}

TEST_F(SkipFunctionalTest, SkipVectorNegative)
{
  this->TestSkipNegative(this->queryable, -this->SkipCount);
}

TEST_F(SkipFunctionalTest, SkipSetNegative)
{
  this->TestSkipNegative(Queryable<uint, std::set>(this->queryable.ToSet()), -this->SkipCount);
}

TEST_F(SkipFunctionalTest, SkipMultiSetNegative)
{
  this->TestSkipNegative(Queryable<uint, std::multiset>(this->queryable.ToMultiSet()), -this->SkipCount);
}

TEST_F(SkipFunctionalTest, SkipDequeNegative)
{
  this->TestSkipNegative(Queryable<uint, std::deque>(this->queryable.ToDeque()), -this->SkipCount);
}

TEST_F(SkipFunctionalTest, SkipListNegative)
{
  this->TestSkipNegative(Queryable<uint, std::list>(this->queryable.ToList()), -this->SkipCount);
}
