#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <vector>

#include "../../../DataStructures/Gender.hpp"
#include "../../../DataStructures/Person.hpp"
#include "../../../DataStructures/PersonLibrary.hpp"

#include "../../../Queryable/Queryable.hpp"
#include "../../../Queryable/QueryableAliases.hpp"
#include "../../../Queryable/QueryBuilder.hpp"


using namespace QueryBuilder;

class AnyFunctionalTest : public ::testing::Test
{
protected:
  QueryableVector<uint> queryable;
  QueryableVector<std::string> queryableStrings;

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

// TEST_F(AnyFunctionalTest, AnyUninitialized)
// {
//   QueryableVector<Person> emptyQueryable;
//   bool any = emptyQueryable.Any([](Person p) { return p.GetAge() > 10; });
//   ASSERT_FALSE(any);
// }

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
  QueryableDeque<uint> local = BuildQueryable2(this->queryable.ToDeque());
  bool any = local.Any([](uint value) { return value > 5000; });
  ASSERT_FALSE(any);
}

TEST_F(AnyFunctionalTest, AnyDequeTrue)
{
  QueryableDeque<uint> local = BuildQueryable2(this->queryable.ToDeque());
  bool any = local.Any([](uint value) { return value > 12; });
  ASSERT_TRUE(any);
}

TEST_F(AnyFunctionalTest, AnyListFalse)
{
  QueryableList<uint> local = BuildQueryable2(this->queryable.ToList());
  bool any = local.Any([](uint value) { return value > 5000; });
  ASSERT_FALSE(any);
}

TEST_F(AnyFunctionalTest, AnyListTrue)
{
  QueryableList<uint> local = BuildQueryable2(this->queryable.ToList());
  bool any = local.Any([](uint value) { return value > 12; });
  ASSERT_TRUE(any);
}

TEST_F(AnyFunctionalTest, AnyMultiSetFalse)
{
  QueryableMultiSet<uint> local = BuildQueryable2(this->queryable.ToMultiSet());
  bool any = local.Any([](uint value) { return value > 5000; });
  ASSERT_FALSE(any);
}

TEST_F(AnyFunctionalTest, AnyMultiSetTrue)
{
  QueryableMultiSet<uint> local = BuildQueryable2(this->queryable.ToMultiSet());
  bool any = local.Any([](uint value) { return value > 12; });
  ASSERT_TRUE(any);
}

TEST_F(AnyFunctionalTest, AnySetFalse)
{
  QueryableSet<uint> local = BuildQueryable2(this->queryable.ToSet());
  bool any = local.Any([](uint value) { return value > 5000; });
  ASSERT_FALSE(any);
}

TEST_F(AnyFunctionalTest, AnySetTrue)
{
  QueryableSet<uint> local = BuildQueryable2(this->queryable.ToSet());
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
