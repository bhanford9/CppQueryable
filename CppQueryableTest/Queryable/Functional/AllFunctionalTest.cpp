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

class AllFunctionalTest : public ::testing::Test
{
protected:
  QueryableVector<uint> queryable;
  QueryableVector<std::string> queryableStrings;

  void SetUp() override
  {
    this->queryable = BuildQueryable(std::vector<uint>({ 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 }));
    this->queryableStrings = BuildQueryable(std::vector<std::string>({ "nbc", "fox", "abc", "cbs", "the cw"}));
  }

  void TearDown() override {}
};

TEST_F(AllFunctionalTest, AllUninitialized)
{
  QueryableVector<Person> emptyQueryable;
  bool all = emptyQueryable.All([](Person p) { return p.GetAge() > 10; });
  ASSERT_TRUE(all);
}

TEST_F(AllFunctionalTest, AllStringFalse)
{
  bool all = this->queryableStrings.All([](std::string str) { return str[0] == 'a'; });
  ASSERT_FALSE(all);
}

TEST_F(AllFunctionalTest, AllStringTrue)
{
  bool all = this->queryableStrings.All([](std::string str) { return str[0] >= 'a' && str[0] <= 'z'; });
  ASSERT_TRUE(all);
}

TEST_F(AllFunctionalTest, AllDequeFalse)
{
  QueryableDeque<uint> local = BuildQueryable(this->queryable.ToDeque());
  bool all = local.All([](uint value) { return value > 5; });
  ASSERT_FALSE(all);
}

TEST_F(AllFunctionalTest, AllDequeTrue)
{
  QueryableDeque<uint> local = BuildQueryable(this->queryable.ToDeque());
  bool all = local.All([](uint value) { return value < 5000; });
  ASSERT_TRUE(all);
}

TEST_F(AllFunctionalTest, AllListFalse)
{
  QueryableList<uint> local = BuildQueryable(this->queryable.ToList());
  bool all = local.All([](uint value) { return value > 5; });
  ASSERT_FALSE(all);
}

TEST_F(AllFunctionalTest, AllListTrue)
{
  QueryableList<uint> local = BuildQueryable(this->queryable.ToList());
  bool all = local.All([](uint value) { return value < 5000; });
  ASSERT_TRUE(all);
}

TEST_F(AllFunctionalTest, AllMultiSetFalse)
{
  QueryableMultiSet<uint> local = BuildQueryable(this->queryable.ToMultiSet());
  bool all = local.All([](uint value) { return value > 5; });
  ASSERT_FALSE(all);
}

TEST_F(AllFunctionalTest, AllMultiSetTrue)
{
  QueryableMultiSet<uint> local = BuildQueryable(this->queryable.ToMultiSet());
  bool all = local.All([](uint value) { return value < 5000; });
  ASSERT_TRUE(all);
}

TEST_F(AllFunctionalTest, AllSetFalse)
{
  QueryableSet<uint> local = BuildQueryable(this->queryable.ToSet());
  bool all = local.All([](uint value) { return value > 5; });
  ASSERT_FALSE(all);
}

TEST_F(AllFunctionalTest, AllSetTrue)
{
  QueryableSet<uint> local = BuildQueryable(this->queryable.ToSet());
  bool all = local.All([](uint value) { return value < 5000; });
  ASSERT_TRUE(all);
}

TEST_F(AllFunctionalTest, AllWhereFalse)
{
  bool all = this->queryable
    .Where([](uint value) { return value > 10; })
    ->All([](uint value) { return value < 20; });
  ASSERT_FALSE(all);
}

TEST_F(AllFunctionalTest, AllWhereTrue)
{
  bool all = this->queryable
    .Where([](uint value) { return value > 10; })
    ->All([](uint value) { return value < 2000; });
  ASSERT_TRUE(all);
}
