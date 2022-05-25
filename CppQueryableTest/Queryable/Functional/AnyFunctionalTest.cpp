#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <vector>

#include "../../../DataStructures/Gender.hpp"
#include "../../../DataStructures/Person.hpp"
#include "../../../DataStructures/PersonLibrary.hpp"

#include "../../../Queryable/IQueryable.hpp"
// #include "../../../Queryable/Queryable.hpp"
#include "../../../Queryable/QueryableAliases.hpp"
#include "../../../Queryable/QueryBuilder.hpp"


using namespace QueryBuilder;

class AnyFunctionalTest : public ::testing::Test
{
protected:
  IQueryable<uint> queryable;
  IQueryable<std::string> queryableStrings;

  AnyFunctionalTest() :
    queryable(BuildQueryable2(std::vector<uint>({ 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 }))),
    queryableStrings(BuildQueryable2(std::vector<std::string>({ "nbc", "fox", "abc", "cbs", "the cw"})))
  {
  }

  void SetUp() override
  {
  }

  void TearDown() override {}
};

TEST_F(AnyFunctionalTest, AnyUninitialized)
{
  IQueryable<Person> emptyQueryable(BuildQueryable2(std::vector<Person>()));
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
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToDeque());
  bool any = local.Any([](uint value) { return value > 5000; });
  ASSERT_FALSE(any);
}

TEST_F(AnyFunctionalTest, AnyDequeTrue)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToDeque());
  bool any = local.Any([](uint value) { return value > 12; });
  ASSERT_TRUE(any);
}

TEST_F(AnyFunctionalTest, AnyListFalse)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToList());
  bool any = local.Any([](uint value) { return value > 5000; });
  ASSERT_FALSE(any);
}

TEST_F(AnyFunctionalTest, AnyListTrue)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToList());
  bool any = local.Any([](uint value) { return value > 12; });
  ASSERT_TRUE(any);
}

TEST_F(AnyFunctionalTest, AnyMultiSetFalse)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToMultiSet());
  bool any = local.Any([](uint value) { return value > 5000; });
  ASSERT_FALSE(any);
}

TEST_F(AnyFunctionalTest, AnyMultiSetTrue)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToMultiSet());
  bool any = local.Any([](uint value) { return value > 12; });
  ASSERT_TRUE(any);
}

TEST_F(AnyFunctionalTest, AnySetFalse)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToSet());
  bool any = local.Any([](uint value) { return value > 5000; });
  ASSERT_FALSE(any);
}

TEST_F(AnyFunctionalTest, AnySetTrue)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToSet());
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
