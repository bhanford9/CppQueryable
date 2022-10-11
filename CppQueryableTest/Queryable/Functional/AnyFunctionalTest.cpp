#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <vector>

#include "../../../DataStructures/Gender.hpp"
#include "../../../DataStructures/Person.hpp"
#include "../../../DataStructures/PersonLibrary.hpp"

#include "../../../Queryable/IQueryable.hpp"
#include "../../../Queryable/ISortedQueryable.hpp"
// #include "../../../Queryable/Queryable.hpp"
#include "../../../Queryable/QueryableAliases.hpp"
#include "../../../Queryable/QueryBuilder.hpp"

using namespace QueryBuilder;

class AnyFunctionalTest : public ::testing::Test
{
protected:
  QueryableVector<size_t> queryable;
  QueryableVector<std::string> queryableStrings;

  AnyFunctionalTest() :
    queryable(BuildQueryable(std::vector<size_t>({ 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 }))),
    queryableStrings(BuildQueryable(std::vector<std::string>({ "nbc", "fox", "abc", "cbs", "the cw"})))
  {
  }

  void SetUp() override
  {
  }

  void TearDown() override {}
};

TEST_F(AnyFunctionalTest, AnyUninitialized)
{
  QueryableVector<Person> emptyQueryable(BuildQueryable(std::vector<Person>()));
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
  QueryableDeque<size_t> local = BuildQueryable(this->queryable.ToDeque());
  bool any = local.Any([](size_t value) { return value > 5000; });
  ASSERT_FALSE(any);
}

TEST_F(AnyFunctionalTest, AnyDequeTrue)
{
  QueryableDeque<size_t> local = BuildQueryable(this->queryable.ToDeque());
  bool any = local.Any([](size_t value) { return value > 12; });
  ASSERT_TRUE(any);
}

TEST_F(AnyFunctionalTest, AnyListFalse)
{
  QueryableList<size_t> local = BuildQueryable(this->queryable.ToList());
  bool any = local.Any([](size_t value) { return value > 5000; });
  ASSERT_FALSE(any);
}

TEST_F(AnyFunctionalTest, AnyListTrue)
{
  QueryableMap<size_t, std::string> local = BuildQueryable(
    this->queryable.ToMap<size_t, std::string>(
      [](size_t value) { return value; },
      [](size_t value) { return std::to_string(value / 2.0); }));
  bool any = local.Any([](std::pair<const size_t, std::string> kvp) { return kvp.first > 12; });
  ASSERT_TRUE(any);
}

TEST_F(AnyFunctionalTest, AnyMapFalse)
{
  QueryableMap<size_t, std::string> local = BuildQueryable(
    this->queryable.ToMap<size_t, std::string>(
      [](size_t value) { return value; },
      [](size_t value) { return std::to_string(value / 2.0); }));
  bool any = local.Any([](std::pair<const size_t, std::string> kvp) { return kvp.first > 5000; });
  ASSERT_FALSE(any);
}

TEST_F(AnyFunctionalTest, AnyMapTrue)
{
  QueryableList<size_t> local = BuildQueryable(this->queryable.ToList());
  bool any = local.Any([](size_t value) { return value > 12; });
  ASSERT_TRUE(any);
}

TEST_F(AnyFunctionalTest, AnyMultiSetFalse)
{
  QueryableMultiSet<size_t> local = BuildQueryable(this->queryable.ToMultiSet());
  bool any = local.Any([](size_t value) { return value > 5000; });
  ASSERT_FALSE(any);
}

TEST_F(AnyFunctionalTest, AnyMultiSetTrue)
{
  QueryableMultiSet<size_t> local = BuildQueryable(this->queryable.ToMultiSet());
  bool any = local.Any([](size_t value) { return value > 12; });
  ASSERT_TRUE(any);
}

TEST_F(AnyFunctionalTest, AnySetFalse)
{
  QueryableSet<size_t> local = BuildQueryable(this->queryable.ToSet());
  bool any = local.Any([](size_t value) { return value > 5000; });
  ASSERT_FALSE(any);
}

TEST_F(AnyFunctionalTest, AnySetTrue)
{
  QueryableSet<size_t> local = BuildQueryable(this->queryable.ToSet());
  bool any = local.Any([](size_t value) { return value > 12; });
  ASSERT_TRUE(any);
}

TEST_F(AnyFunctionalTest, AnyWhereFalse)
{
  bool any = this->queryable
    .Where([](size_t value) { return value > 10; })
    .Any([](size_t value) { return value < 10; });
  ASSERT_FALSE(any);
}

TEST_F(AnyFunctionalTest, AnyWhereTrue)
{
  bool any = this->queryable
    .Where([](size_t value) { return value > 10; })
    .Any([](size_t value) { return value % 2 == 0; });
  ASSERT_TRUE(any);
}
