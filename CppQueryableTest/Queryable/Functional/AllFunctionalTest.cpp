#include <gtest/gtest.h>

#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include "../../../DataStructures/Gender.hpp"
#include "../../../DataStructures/Person.hpp"
#include "../../../DataStructures/PersonLibrary.hpp"

#include "../../../Queryable/QueryBuilder.hpp"


using namespace QueryBuilder;

class AllFunctionalTest : public ::testing::Test
{
protected:
  VectorInternalQueryable<uint> queryable;
  VectorInternalQueryable<std::string> queryableStrings;

  void SetUp() override
  {
    this->queryable = BuildQueryable(std::vector<uint>({ 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 }));
    this->queryableStrings = BuildQueryable(std::vector<std::string>({ "nbc", "fox", "abc", "cbs", "the cw"}));
  }

  void TearDown() override {}
};

TEST_F(AllFunctionalTest, AllUninitialized)
{
  VectorInternalQueryable<Person> emptyQueryable;
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
  DequeInternalQueryable<uint> local = BuildQueryable(this->queryable.ToDeque());
  bool all = local.All([](uint value) { return value > 5; });
  ASSERT_FALSE(all);
}

TEST_F(AllFunctionalTest, AllDequeTrue)
{
  DequeInternalQueryable<uint> local = BuildQueryable(this->queryable.ToDeque());
  bool all = local.All([](uint value) { return value < 5000; });
  ASSERT_TRUE(all);
}

TEST_F(AllFunctionalTest, AllListFalse)
{
  ListInternalQueryable<uint> local = BuildQueryable(this->queryable.ToList());
  bool all = local.All([](uint value) { return value > 5; });
  ASSERT_FALSE(all);
}

TEST_F(AllFunctionalTest, AllListTrue)
{
  ListInternalQueryable<uint> local = BuildQueryable(this->queryable.ToList());
  bool all = local.All([](uint value) { return value < 5000; });
  ASSERT_TRUE(all);
}

TEST_F(AllFunctionalTest, AllMultiSetFalse)
{
  MultiSetInternalQueryable<uint> local = BuildQueryable(this->queryable.ToMultiSet());
  bool all = local.All([](uint value) { return value > 5; });
  ASSERT_FALSE(all);
}

TEST_F(AllFunctionalTest, AllMultiSetTrue)
{
  MultiSetInternalQueryable<uint> local = BuildQueryable(this->queryable.ToMultiSet());
  bool all = local.All([](uint value) { return value < 5000; });
  ASSERT_TRUE(all);
}

TEST_F(AllFunctionalTest, AllSetFalse)
{
  SetInternalQueryable<uint> local = BuildQueryable(this->queryable.ToSet());
  bool all = local.All([](uint value) { return value > 5; });
  ASSERT_FALSE(all);
}

TEST_F(AllFunctionalTest, AllSetTrue)
{
  SetInternalQueryable<uint> local = BuildQueryable(this->queryable.ToSet());
  bool all = local.All([](uint value) { return value < 5000; });
  ASSERT_TRUE(all);
}

TEST_F(AllFunctionalTest, AllWhereFalse)
{
  bool all = this->queryable
    .Where([](uint value) { return value > 10; })
    .All([](uint value) { return value < 20; });
  ASSERT_FALSE(all);
}

TEST_F(AllFunctionalTest, AllWhereTrue)
{
  bool all = this->queryable
    .Where([](uint value) { return value > 10; })
    .All([](uint value) { return value < 2000; });
  ASSERT_TRUE(all);
}
