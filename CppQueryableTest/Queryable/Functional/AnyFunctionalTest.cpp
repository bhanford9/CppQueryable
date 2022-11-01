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

#include "Headers/AnyFunctionalTest.hpp"

using namespace QueryBuilder;

TEST_F(AnyFunctionalGTest, AnyUninitialized)
{
  this->AnyUninitialized();
}
void AnyFunctionalTest::AnyUninitialized()
{
  QueryableVector<Person> emptyQueryable(BuildQueryable(std::vector<Person>()));
  bool any = emptyQueryable.Any([](Person p) { return p.GetAge() > 10; });
  ASSERT_FALSE(any);
}

TEST_F(AnyFunctionalGTest, AnyStringFalse)
{
  this->AnyStringFalse();
}
void AnyFunctionalTest::AnyStringFalse()
{
  bool any = this->queryableStrings.Any([](std::string str) { return str[0] == 'z'; });
  ASSERT_FALSE(any);
}

TEST_F(AnyFunctionalGTest, AnyStringTrue)
{
  this->AnyStringTrue();
}
void AnyFunctionalTest::AnyStringTrue()
{
  bool any = this->queryableStrings.Any([](std::string str) { return str[0] == 'c'; });
  ASSERT_TRUE(any);
}

TEST_F(AnyFunctionalGTest, AnyDequeFalse)
{
  this->AnyDequeFalse();
}
void AnyFunctionalTest::AnyDequeFalse()
{
  QueryableDeque<size_t> local = BuildQueryable(this->queryable.ToDeque());
  bool any = local.Any([](size_t value) { return value > 5000; });
  ASSERT_FALSE(any);
}

TEST_F(AnyFunctionalGTest, AnyDequeTrue)
{
  this->AnyDequeTrue();
}
void AnyFunctionalTest::AnyDequeTrue()
{
  QueryableDeque<size_t> local = BuildQueryable(this->queryable.ToDeque());
  bool any = local.Any([](size_t value) { return value > 12; });
  ASSERT_TRUE(any);
}

TEST_F(AnyFunctionalGTest, AnyListFalse)
{
  this->AnyListFalse();
}
void AnyFunctionalTest::AnyListFalse()
{
  QueryableList<size_t> local = BuildQueryable(this->queryable.ToList());
  bool any = local.Any([](size_t value) { return value > 5000; });
  ASSERT_FALSE(any);
}

TEST_F(AnyFunctionalGTest, AnyListTrue)
{
  this->AnyListTrue();
}
void AnyFunctionalTest::AnyListTrue()
{
  QueryableMap<size_t, std::string> local = BuildQueryable(
    this->queryable.ToMap<size_t, std::string>(
      [](size_t value) { return value; },
      [](size_t value) { return std::to_string(value / 2.0); }));
  bool any = local.Any([](std::pair<const size_t, std::string> kvp) { return kvp.first > 12; });
  ASSERT_TRUE(any);
}

TEST_F(AnyFunctionalGTest, AnyMapFalse)
{
  this->AnyMapFalse();
}
void AnyFunctionalTest::AnyMapFalse()
{
  QueryableMap<size_t, std::string> local = BuildQueryable(
    this->queryable.ToMap<size_t, std::string>(
      [](size_t value) { return value; },
      [](size_t value) { return std::to_string(value / 2.0); }));
  bool any = local.Any([](std::pair<const size_t, std::string> kvp) { return kvp.first > 5000; });
  ASSERT_FALSE(any);
}

TEST_F(AnyFunctionalGTest, AnyMapTrue)
{
  this->AnyMapTrue();
}
void AnyFunctionalTest::AnyMapTrue()
{
  QueryableList<size_t> local = BuildQueryable(this->queryable.ToList());
  bool any = local.Any([](size_t value) { return value > 12; });
  ASSERT_TRUE(any);
}

TEST_F(AnyFunctionalGTest, AnyMultiSetFalse)
{
  this->AnyMultiSetFalse();
}
void AnyFunctionalTest::AnyMultiSetFalse()
{
  QueryableMultiSet<size_t> local = BuildQueryable(this->queryable.ToMultiSet());
  bool any = local.Any([](size_t value) { return value > 5000; });
  ASSERT_FALSE(any);
}

TEST_F(AnyFunctionalGTest, AnyMultiSetTrue)
{
  this->AnyMultiSetTrue();
}
void AnyFunctionalTest::AnyMultiSetTrue()
{
  QueryableMultiSet<size_t> local = BuildQueryable(this->queryable.ToMultiSet());
  bool any = local.Any([](size_t value) { return value > 12; });
  ASSERT_TRUE(any);
}

TEST_F(AnyFunctionalGTest, AnySetFalse)
{
  this->AnySetFalse();
}
void AnyFunctionalTest::AnySetFalse()
{
  QueryableSet<size_t> local = BuildQueryable(this->queryable.ToSet());
  bool any = local.Any([](size_t value) { return value > 5000; });
  ASSERT_FALSE(any);
}

TEST_F(AnyFunctionalGTest, AnySetTrue)
{
  this->AnySetTrue();
}
void AnyFunctionalTest::AnySetTrue()
{
  QueryableSet<size_t> local = BuildQueryable(this->queryable.ToSet());
  bool any = local.Any([](size_t value) { return value > 12; });
  ASSERT_TRUE(any);
}

TEST_F(AnyFunctionalGTest, AnyWhereFalse)
{
  this->AnyWhereFalse();
}
void AnyFunctionalTest::AnyWhereFalse()
{
  bool any = this->queryable
    .Where([](size_t value) { return value > 10; })
    .Any([](size_t value) { return value < 10; });
  ASSERT_FALSE(any);
}

TEST_F(AnyFunctionalGTest, AnyWhereTrue)
{
  this->AnyWhereTrue();
}
void AnyFunctionalTest::AnyWhereTrue()
{
  bool any = this->queryable
    .Where([](size_t value) { return value > 10; })
    .Any([](size_t value) { return value % 2 == 0; });
  ASSERT_TRUE(any);
}
