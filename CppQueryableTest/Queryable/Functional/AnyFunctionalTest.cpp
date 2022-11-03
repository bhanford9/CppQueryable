#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "../../../DataStructures/Person.hpp"

#include "../../../Queryable/QueryableAliases.hpp"
#include "../../../Queryable/QueryBuilder.hpp"

#include "Headers/AnyFunctionalTest.hpp"

using namespace QueryBuilder;

TEST_F(AnyFunctionalGTest, AnyUninitialized)
{
    this->AnyUninitialized();
}

void AnyFunctionalTest::AnyUninitialized() const
{
    const QueryableVector<Person> emptyQueryable(BuildQueryable(std::vector<Person>()));
    const bool any = emptyQueryable.Any([](const Person & p) { return p.GetAge() > 10; });
    ASSERT_FALSE(any);
}

TEST_F(AnyFunctionalGTest, AnyStringFalse)
{
    this->AnyStringFalse();
}

void AnyFunctionalTest::AnyStringFalse() const
{
    const bool any = this->queryableStrings.Any(
        [](const std::string & str) { return str[0] == 'z'; });
    ASSERT_FALSE(any);
}

TEST_F(AnyFunctionalGTest, AnyStringTrue)
{
    this->AnyStringTrue();
}

void AnyFunctionalTest::AnyStringTrue() const
{
    const bool any = this->queryableStrings.Any(
        [](const std::string & str) { return str[0] == 'c'; });
    ASSERT_TRUE(any);
}

TEST_F(AnyFunctionalGTest, AnyDequeFalse)
{
    this->AnyDequeFalse();
}

void AnyFunctionalTest::AnyDequeFalse() const
{
    const QueryableDeque<size_t> local = BuildQueryable(this->queryable.ToDeque());
    const bool any = local.Any([](const size_t value) { return value > 5000; });
    ASSERT_FALSE(any);
}

TEST_F(AnyFunctionalGTest, AnyDequeTrue)
{
    this->AnyDequeTrue();
}

void AnyFunctionalTest::AnyDequeTrue() const
{
    const QueryableDeque<size_t> local = BuildQueryable(this->queryable.ToDeque());
    const bool any = local.Any([](const size_t value) { return value > 12; });
    ASSERT_TRUE(any);
}

TEST_F(AnyFunctionalGTest, AnyListFalse)
{
    this->AnyListFalse();
}

void AnyFunctionalTest::AnyListFalse() const
{
    const QueryableList<size_t> local = BuildQueryable(this->queryable.ToList());
    const bool any = local.Any([](const size_t value) { return value > 5000; });
    ASSERT_FALSE(any);
}

TEST_F(AnyFunctionalGTest, AnyListTrue)
{
    this->AnyListTrue();
}

void AnyFunctionalTest::AnyListTrue() const
{
    const QueryableMap<size_t, std::string> local = BuildQueryable(
        this->queryable.ToMap<size_t, std::string>(
            [](const size_t value) { return value; },
            [](const size_t value) { return std::to_string(static_cast<double>(value) / 2.0); }));
    const bool any = local.Any(
        [](const std::pair<const size_t &, std::string> & kvp) { return kvp.first > 12; });
    ASSERT_TRUE(any);
}

TEST_F(AnyFunctionalGTest, AnyMapFalse)
{
    this->AnyMapFalse();
}

void AnyFunctionalTest::AnyMapFalse() const
{
    const QueryableMap<size_t, std::string> local = BuildQueryable(
        this->queryable.ToMap<size_t, std::string>(
            [](const size_t value) { return value; },
            [](const size_t value) { return std::to_string(static_cast<double>(value) / 2.0); }));
    const bool any = local.Any(
        [](const std::pair<const size_t, std::string> & kvp) { return kvp.first > 5000; });
    ASSERT_FALSE(any);
}

TEST_F(AnyFunctionalGTest, AnyMapTrue)
{
    this->AnyMapTrue();
}

void AnyFunctionalTest::AnyMapTrue() const
{
    const QueryableList<size_t> local = BuildQueryable(this->queryable.ToList());
    const bool any = local.Any([](const size_t value) { return value > 12; });
    ASSERT_TRUE(any);
}

TEST_F(AnyFunctionalGTest, AnyMultiSetFalse)
{
    this->AnyMultiSetFalse();
}

void AnyFunctionalTest::AnyMultiSetFalse() const
{
    const QueryableMultiSet<size_t> local = BuildQueryable(this->queryable.ToMultiSet());
    const bool any = local.Any([](const size_t value) { return value > 5000; });
    ASSERT_FALSE(any);
}

TEST_F(AnyFunctionalGTest, AnyMultiSetTrue)
{
    this->AnyMultiSetTrue();
}

void AnyFunctionalTest::AnyMultiSetTrue() const
{
    const QueryableMultiSet<size_t> local = BuildQueryable(this->queryable.ToMultiSet());
    const bool any = local.Any([](const size_t value) { return value > 12; });
    ASSERT_TRUE(any);
}

TEST_F(AnyFunctionalGTest, AnySetFalse)
{
    this->AnySetFalse();
}

void AnyFunctionalTest::AnySetFalse() const
{
    const QueryableSet<size_t> local = BuildQueryable(this->queryable.ToSet());
    const bool any = local.Any([](const size_t value) { return value > 5000; });
    ASSERT_FALSE(any);
}

TEST_F(AnyFunctionalGTest, AnySetTrue)
{
    this->AnySetTrue();
}

void AnyFunctionalTest::AnySetTrue() const
{
    const QueryableSet<size_t> local = BuildQueryable(this->queryable.ToSet());
    const bool any = local.Any([](const size_t value) { return value > 12; });
    ASSERT_TRUE(any);
}

TEST_F(AnyFunctionalGTest, AnyWhereFalse)
{
    this->AnyWhereFalse();
}

void AnyFunctionalTest::AnyWhereFalse()
{
    const bool any = this->queryable.Where([](const size_t value) { return value > 10; }).Any(
        [](const size_t value) { return value < 10; });
    ASSERT_FALSE(any);
}

TEST_F(AnyFunctionalGTest, AnyWhereTrue)
{
    this->AnyWhereTrue();
}

void AnyFunctionalTest::AnyWhereTrue()
{
    const bool any = this->queryable.Where([](const size_t value) { return value > 10; }).Any(
        [](const size_t value) { return value % 2 == 0; });
    ASSERT_TRUE(any);
}
