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

class ForEachFunctionalTest : public ::testing::Test
{
protected:
  Queryable<uint, std::vector> queryable;

  void SetUp() override
  {
    this->queryable = Queryable<uint, std::vector>({ 7, 4, 7, 4, 3, 76, 8, 45, 34, 76, 8, 867 });
  }

  template<typename TObj, template<typename...> typename TIterable>
  void TestForEach (Queryable<TObj, TIterable> localQueryable)
  {
    std::vector<TObj> iterated(localQueryable.Count(), 0);
    int i = 0;

    localQueryable.ForEach([&](TObj value)
    {
      iterated[i++] = value;
    });

    for (i = 0; i < localQueryable.Count(); i++)
    {
      ASSERT_EQ(localQueryable.At(i), iterated[i]);
    }
  }

  void TearDown() override {}
};

TEST_F(ForEachFunctionalTest, ForEachVectorUninitialized)
{
  Queryable<Person, std::vector> emptyQueryable;
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
  Queryable<uint, std::set> localQueryable = this->queryable.ToSet();
  this->TestForEach(localQueryable);
}

TEST_F(ForEachFunctionalTest, ForEachMultiSet)
{
  Queryable<uint, std::multiset> localQueryable = this->queryable.ToMultiSet();
  this->TestForEach(localQueryable);
}

TEST_F(ForEachFunctionalTest, ForEachDeque)
{
  Queryable<uint, std::deque> localQueryable = this->queryable.ToDeque();
  this->TestForEach(localQueryable);
}

TEST_F(ForEachFunctionalTest, ForEachList)
{
  Queryable<uint, std::list> localQueryable = this->queryable.ToList();
  this->TestForEach(localQueryable);
}
