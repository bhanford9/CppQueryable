#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <vector>

#include "../../../DataStructures/Gender.hpp"
#include "../../../DataStructures/Person.hpp"
#include "../../../DataStructures/PersonLibrary.hpp"

#include "../../../Queryable/QueryBuilder.hpp"


using namespace QueryBuilder;

class AnyFunctionalTest : public ::testing::Test
{
protected:
  VectorQueryable<uint> queryable;
  VectorQueryable<std::string> queryableStrings;

  void SetUp() override
  {
    this->queryable = BuildQueryable(std::vector<uint>({ 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 }));
    std::vector<std::string> networks({ "nbc", "fox", "abc", "cbs", "the cw"});
    this->queryableStrings = BuildQueryable(networks);
  }

  void TearDown() override {}
};

TEST_F(AnyFunctionalTest, AnyUninitialized)
{
  VectorQueryable<Person> emptyQueryable;
  bool any = emptyQueryable.Any([](Person p) { return p.GetAge() > 10; });
  ASSERT_FALSE(any);
}

TEST_F(AnyFunctionalTest, AnyStringFalse)
{
  bool any = this->queryableStrings.Any([](std::string str) { return str[0] == 'z'; });
  ASSERT_FALSE(any);
}

TEST_F(AnyFunctionalTest, AnyStringTrue)
{
  bool any = this->queryableStrings.Any([](std::string str) { return str[0] == 'c'; });
  ASSERT_TRUE(any);
}

TEST_F(AnyFunctionalTest, AnyDequeFalse)
{
  DequeQueryable<uint> local = BuildQueryable(this->queryable.ToDeque());
  bool any = local.Any([](uint value) { return value > 5000; });
  ASSERT_FALSE(any);
}

TEST_F(AnyFunctionalTest, AnyDequeTrue)
{
  DequeQueryable<uint> local = BuildQueryable(this->queryable.ToDeque());
  bool any = local.Any([](uint value) { return value > 12; });
  ASSERT_TRUE(any);
}

TEST_F(AnyFunctionalTest, AnyListFalse)
{
  ListQueryable<uint> local = BuildQueryable(this->queryable.ToList());
  bool any = local.Any([](uint value) { return value > 5000; });
  ASSERT_FALSE(any);
}

TEST_F(AnyFunctionalTest, AnyListTrue)
{
  ListQueryable<uint> local = BuildQueryable(this->queryable.ToList());
  bool any = local.Any([](uint value) { return value > 12; });
  ASSERT_TRUE(any);
}

TEST_F(AnyFunctionalTest, AnyMultiSetFalse)
{
  MultiSetQueryable<uint> local = BuildQueryable(this->queryable.ToMultiSet());
  bool any = local.Any([](uint value) { return value > 5000; });
  ASSERT_FALSE(any);
}

TEST_F(AnyFunctionalTest, AnyMultiSetTrue)
{
  MultiSetQueryable<uint> local = BuildQueryable(this->queryable.ToMultiSet());
  bool any = local.Any([](uint value) { return value > 12; });
  ASSERT_TRUE(any);
}

TEST_F(AnyFunctionalTest, AnySetFalse)
{
  SetQueryable<uint> local = BuildQueryable(this->queryable.ToSet());
  bool any = local.Any([](uint value) { return value > 5000; });
  ASSERT_FALSE(any);
}

TEST_F(AnyFunctionalTest, AnySetTrue)
{
  SetQueryable<uint> local = BuildQueryable(this->queryable.ToSet());
  bool any = local.Any([](uint value) { return value > 12; });
  ASSERT_TRUE(any);
}

TEST_F(AnyFunctionalTest, AnyWhereFalse)
{
  bool any = this->queryable
    .Where([](uint value) { return value > 10; })
    .Any([](uint value) { return value < 10; });
  ASSERT_FALSE(any);
}

TEST_F(AnyFunctionalTest, AnyWhereTrue)
{
  bool any = this->queryable
    .Where([](uint value) { return value > 10; })
    .Any([](uint value) { return value % 2 == 0; });
  ASSERT_TRUE(any);
}
