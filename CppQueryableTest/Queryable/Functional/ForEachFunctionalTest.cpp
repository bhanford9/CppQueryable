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


#include "../../../Queryable/QueryablesForwardDeclarations.hpp"

#include "../../../Queryable/QueryBuilder.hpp"

using namespace QueryBuilder;

class ForEachFunctionalTest : public ::testing::Test
{
protected:
  IQueryable<uint> queryable;

  ForEachFunctionalTest() :
    queryable(BuildQueryable2(std::vector<uint>({ 7, 4, 7, 4, 3, 76, 8, 45, 34, 76, 8, 867 })))
  {
  }

  void SetUp() override
  {
  }

  template<
    typename TObj,
    // template<typename, typename ...> typename TIterable,
    // typename TAllocator = std::allocator<TObj>,
    typename ...TArgs>
  void TestForEach (IBaseQueryable<TObj, TArgs...> & localQueryable)
  {
    std::vector<TObj> iterated(localQueryable.Count(), 0);
    size_t i = 0;

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
  IQueryable<Person> emptyQueryable(BuildQueryable2(std::vector<Person>()));
  emptyQueryable.ForEach([](Person p) { throw std::runtime_error("Should not hit"); });
  ASSERT_TRUE(true);
}

TEST_F(ForEachFunctionalTest, ForEachVector)
{
  std::vector<uint> iterated(this->queryable.Count(), 0);
  size_t i = 0;

  this->queryable.ForEach([&](uint value)
  {
    iterated[i++] = value;
  });

  for (i = 0; i < this->queryable.Count(); i++)
  {
    ASSERT_EQ(this->queryable.At(i), iterated[i]);
  }
}

TEST_F(ForEachFunctionalTest, ForEachDeque)
{
  IQueryable<uint> localQueryable = BuildQueryable2(this->queryable.ToDeque());
  this->TestForEach(localQueryable);
}

TEST_F(ForEachFunctionalTest, ForEachList)
{
  IQueryable<uint> localQueryable = BuildQueryable2(this->queryable.ToList());
  this->TestForEach(localQueryable);
}

TEST_F(ForEachFunctionalTest, ForEachMultiSet)
{
  ISortedQueryable<uint> localQueryable = BuildQueryable2(this->queryable.ToMultiSet());
  this->TestForEach(localQueryable);
}

TEST_F(ForEachFunctionalTest, ForEachSet)
{
  ISortedQueryable<uint> localQueryable = BuildQueryable2(this->queryable.ToSet());
  this->TestForEach(localQueryable);
}

TEST_F(ForEachFunctionalTest, ForEachWhere)
{
  IQueryable<uint> IQueryable = BuildQueryable2(std::vector<uint>({ 7, 0, 7, 2, 3, 4, 6, 45, 8, 1, 3, 10, 99, 199 }));

  int expectedCount = 6;
  int count = 0;
  IQueryable
    .Where([](uint value) { return value % 2 == 0; })
    .ForEach([&](uint value) { ASSERT_EQ(count++ * 2, value); });

  ASSERT_EQ(expectedCount, count);
}
