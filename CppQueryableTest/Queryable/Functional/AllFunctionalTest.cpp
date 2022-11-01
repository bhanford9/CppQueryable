#include <gtest/gtest.h>

#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include "../../../DataStructures/Gender.hpp"
#include "../../../DataStructures/Person.hpp"
#include "../../../DataStructures/PersonLibrary.hpp"

#include "Headers/AllFunctionalTest.hpp"

#include "../../../Queryable/QueryBuilder.hpp"

using namespace QueryBuilder;

TEST_F(AllFunctionalGTest, AllStringFalse)
{
  this->AllStringFalse();
}
void AllFunctionalTest::AllStringFalse()
{
  bool all = this->queryableStrings.All([](std::string str) { return str[0] == 'a'; });
  ASSERT_FALSE(all);
}

TEST_F(AllFunctionalGTest, AllStringTrue)
{
  this->AllStringTrue();
}
void AllFunctionalTest::AllStringTrue()
{
  bool all = this->queryableStrings.All([](std::string str) { return str[0] >= 'a' && str[0] <= 'z'; });
  ASSERT_TRUE(all);
}

TEST_F(AllFunctionalGTest, AllDequeFalse)
{
  this->AllDequeFalse();
}
void AllFunctionalTest::AllDequeFalse()
{
  QueryableDeque<size_t> local = BuildQueryable(this->queryable.ToDeque());
  bool all = local.All([](size_t value) { return value > 5; });
  ASSERT_FALSE(all);
}

TEST_F(AllFunctionalGTest, AllDequeTrue)
{
  this->AllDequeTrue();
}
void AllFunctionalTest::AllDequeTrue()
{
  QueryableDeque<size_t> local = BuildQueryable(this->queryable.ToDeque());
  bool all = local.All([](size_t value) { return value < 5000; });
  ASSERT_TRUE(all);
}

TEST_F(AllFunctionalGTest, AllListFalse)
{
  this->AllListFalse();
}
void AllFunctionalTest::AllListFalse()
{
  QueryableList<size_t> local = BuildQueryable(this->queryable.ToList());
  bool all = local.All([](size_t value) { return value > 5; });
  ASSERT_FALSE(all);
}

TEST_F(AllFunctionalGTest, AllListTrue)
{
  this->AllListTrue();
}
void AllFunctionalTest::AllListTrue()
{
  QueryableList<size_t> local = BuildQueryable(this->queryable.ToList());
  bool all = local.All([](size_t value) { return value < 5000; });
  ASSERT_TRUE(all);
}

TEST_F(AllFunctionalGTest, AllMapFalse)
{
  this->AllMapFalse();
}
void AllFunctionalTest::AllMapFalse()
{
  QueryableMap<size_t, std::string> local = BuildQueryable(
    this->queryable.ToMap<size_t, std::string>(
      [](size_t value) { return value; },
      [](size_t value) { return std::to_string(value / 2.0); }));
  bool all = local.All([](std::pair<const size_t, std::string> kvp) { return kvp.first > 5; });
  ASSERT_FALSE(all);
}

TEST_F(AllFunctionalGTest, AllMapTrue)
{
  this->AllMapTrue();
}
void AllFunctionalTest::AllMapTrue()
{
  QueryableMap<size_t, std::string> local = BuildQueryable(
    this->queryable.ToMap<size_t, std::string>(
      [](size_t value) { return value; },
      [](size_t value) { return std::to_string(value / 2.0); }));
  bool all = local.All([](std::pair<const size_t, std::string> kvp) { return kvp.first < 5000; });
  ASSERT_TRUE(all);
}

TEST_F(AllFunctionalGTest, AllMultiSetFalse)
{
  this->AllMultiSetFalse();
}
void AllFunctionalTest::AllMultiSetFalse()
{
  QueryableMultiSet<size_t> local = BuildQueryable(this->queryable.ToMultiSet());
  bool all = local.All([](size_t value) { return value > 5; });
  ASSERT_FALSE(all);
}

TEST_F(AllFunctionalGTest, AllMultiSetTrue)
{
  this->AllMultiSetTrue();
}
void AllFunctionalTest::AllMultiSetTrue()
{
  QueryableMultiSet<size_t> local = BuildQueryable(this->queryable.ToMultiSet());
  bool all = local.All([](size_t value) { return value < 5000; });
  ASSERT_TRUE(all);
}

TEST_F(AllFunctionalGTest, AllSetFalse)
{
  this->AllSetFalse();
}
void AllFunctionalTest::AllSetFalse()
{
  QueryableSet<size_t> local = BuildQueryable(this->queryable.ToSet());
  bool all = local.All([](size_t value) { return value > 5; });
  ASSERT_FALSE(all);
}

TEST_F(AllFunctionalGTest, AllSetTrue)
{
  this->AllSetTrue();
}
void AllFunctionalTest::AllSetTrue()
{
  QueryableSet<size_t> local = BuildQueryable(this->queryable.ToSet());
  bool all = local.All([](size_t value) { return value < 5000; });
  ASSERT_TRUE(all);
}

TEST_F(AllFunctionalGTest, AllWhereFalse)
{
  this->AllWhereFalse();
}
void AllFunctionalTest::AllWhereFalse()
{
  bool all = this->queryable
    .Where([](size_t value) { return value > 10; })
    .All([](size_t value) { return value < 20; });
  ASSERT_FALSE(all);
}

TEST_F(AllFunctionalGTest, AllWhereTrue)
{
  this->AllWhereTrue();
}
void AllFunctionalTest::AllWhereTrue()
{
  bool all = this->queryable
    .Where([](size_t value) { return value > 10; })
    .All([](size_t value) { return value < 2000; });
  ASSERT_TRUE(all);
}
