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
  VectorQueryable<uint> queryable;
  VectorQueryable<std::string> queryableStrings;

  void SetUp() override
  {
    this->queryable = BuildQueryable2(std::vector<uint>({ 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 }));
    this->queryableStrings = BuildQueryable2(std::vector<std::string>({ "nbc", "fox", "abc", "cbs", "the cw"}));
  }

  void TearDown() override {}
};

TEST_F(AllFunctionalTest, AllUninitialized)
{
  std::cout << "one" << std::endl;
  VectorQueryable<Person> emptyQueryable;
  std::cout << "two" << std::endl;
  bool all = emptyQueryable.All([](Person p) { return p.GetAge() > 10; });
  std::cout << "three" << std::endl;
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
  DequeQueryable<uint> local = BuildQueryable2(this->queryable.ToDeque());
  bool all = local.All([](uint value) { return value > 5; });
  ASSERT_FALSE(all);
}

TEST_F(AllFunctionalTest, AllDequeTrue)
{
  DequeQueryable<uint> local = BuildQueryable2(this->queryable.ToDeque());
  bool all = local.All([](uint value) { return value < 5000; });
  ASSERT_TRUE(all);
}

TEST_F(AllFunctionalTest, AllListFalse)
{
  ListQueryable<uint> local = BuildQueryable2(this->queryable.ToList());
  bool all = local.All([](uint value) { return value > 5; });
  ASSERT_FALSE(all);
}

TEST_F(AllFunctionalTest, AllListTrue)
{
  ListQueryable<uint> local = BuildQueryable2(this->queryable.ToList());
  bool all = local.All([](uint value) { return value < 5000; });
  ASSERT_TRUE(all);
}

TEST_F(AllFunctionalTest, AllMultiSetFalse)
{
  MultiSetQueryable<uint> local = BuildQueryable2(this->queryable.ToMultiSet());
  bool all = local.All([](uint value) { return value > 5; });
  ASSERT_FALSE(all);
}

TEST_F(AllFunctionalTest, AllMultiSetTrue)
{
  MultiSetQueryable<uint> local = BuildQueryable2(this->queryable.ToMultiSet());
  bool all = local.All([](uint value) { return value < 5000; });
  ASSERT_TRUE(all);
}

TEST_F(AllFunctionalTest, AllSetFalse)
{
  SetQueryable<uint> local = BuildQueryable2(this->queryable.ToSet());
  bool all = local.All([](uint value) { return value > 5; });
  ASSERT_FALSE(all);
}

TEST_F(AllFunctionalTest, AllSetTrue)
{
  SetQueryable<uint> local = BuildQueryable2(this->queryable.ToSet());
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
