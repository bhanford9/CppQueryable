#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "Headers/AllFunctionalTest.hpp"

#include "../../../Queryable/QueryBuilder.hpp"

using namespace QueryBuilder;

TEST_F(AllFunctionalGTest, AllStringFalse)
{
    this->AllStringFalse();
}

void AllFunctionalTest::AllStringFalse() const
{
    const bool all = this->queryableStrings.All(
        [](const std::string & str) { return str[0] == 'a'; });
    ASSERT_FALSE(all);
}

TEST_F(AllFunctionalGTest, AllStringTrue)
{
    this->AllStringTrue();
}

void AllFunctionalTest::AllStringTrue() const
{
    const bool all = this->queryableStrings.All(
        [](const std::string & str) { return str[0] >= 'a' && str[0] <= 'z'; });
    ASSERT_TRUE(all);
}

TEST_F(AllFunctionalGTest, AllDequeFalse)
{
    this->AllDequeFalse();
}

void AllFunctionalTest::AllDequeFalse() const
{
    const QueryableDeque<size_t> local = BuildQueryable(this->queryable.ToDeque());
    const bool all = local.All([](const size_t value) { return value > 5; });
    ASSERT_FALSE(all);
}

TEST_F(AllFunctionalGTest, AllDequeTrue)
{
    this->AllDequeTrue();
}

void AllFunctionalTest::AllDequeTrue() const
{
    const QueryableDeque<size_t> local = BuildQueryable(this->queryable.ToDeque());
    const bool all = local.All([](const size_t value) { return value < 5000; });
    ASSERT_TRUE(all);
}

TEST_F(AllFunctionalGTest, AllListFalse)
{
    this->AllListFalse();
}

void AllFunctionalTest::AllListFalse() const
{
    const QueryableList<size_t> local = BuildQueryable(this->queryable.ToList());
    const bool all = local.All([](const size_t value) { return value > 5; });
    ASSERT_FALSE(all);
}

TEST_F(AllFunctionalGTest, AllListTrue)
{
    this->AllListTrue();
}

void AllFunctionalTest::AllListTrue() const
{
    const QueryableList<size_t> local = BuildQueryable(this->queryable.ToList());
    const bool all = local.All([](const size_t value) { return value < 5000; });
    ASSERT_TRUE(all);
}

TEST_F(AllFunctionalGTest, AllMapFalse)
{
    this->AllMapFalse();
}

void AllFunctionalTest::AllMapFalse() const
{
    const QueryableMap<size_t, std::string> local = BuildQueryable(
        this->queryable.ToMap<size_t, std::string>(
            [](const size_t value) { return value; },
            [](const size_t value) { return std::to_string(static_cast<double>(value) / 2.0); }));
    const bool all = local.All(
        [](const std::pair<const size_t, std::string> & kvp) { return kvp.first > 5; });
    ASSERT_FALSE(all);
}

TEST_F(AllFunctionalGTest, AllMapTrue)
{
    this->AllMapTrue();
}

void AllFunctionalTest::AllMapTrue() const
{
    const QueryableMap<size_t, std::string> local = BuildQueryable(
        this->queryable.ToMap<size_t, std::string>(
            [](const size_t value) { return value; },
            [](const size_t value) { return std::to_string(static_cast<double>(value) / 2.0); }));
    const bool all = local.All(
        [](const std::pair<const size_t, std::string> & kvp) { return kvp.first < 5000; });
    ASSERT_TRUE(all);
}

TEST_F(AllFunctionalGTest, AllMultiSetFalse)
{
    this->AllMultiSetFalse();
}

void AllFunctionalTest::AllMultiSetFalse() const
{
    const QueryableMultiSet<size_t> local = BuildQueryable(this->queryable.ToMultiSet());
    const bool all = local.All([](const size_t value) { return value > 5; });
    ASSERT_FALSE(all);
}

TEST_F(AllFunctionalGTest, AllMultiSetTrue)
{
    this->AllMultiSetTrue();
}

void AllFunctionalTest::AllMultiSetTrue() const
{
    const QueryableMultiSet<size_t> local = BuildQueryable(this->queryable.ToMultiSet());
    const bool all = local.All([](const size_t value) { return value < 5000; });
    ASSERT_TRUE(all);
}

TEST_F(AllFunctionalGTest, AllSetFalse)
{
    this->AllSetFalse();
}

void AllFunctionalTest::AllSetFalse() const
{
    const QueryableSet<size_t> local = BuildQueryable(this->queryable.ToSet());
    const bool all = local.All([](const size_t value) { return value > 5; });
    ASSERT_FALSE(all);
}

TEST_F(AllFunctionalGTest, AllSetTrue)
{
    this->AllSetTrue();
}

void AllFunctionalTest::AllSetTrue() const
{
    const QueryableSet<size_t> local = BuildQueryable(this->queryable.ToSet());
    const bool all = local.All([](const size_t value) { return value < 5000; });
    ASSERT_TRUE(all);
}

TEST_F(AllFunctionalGTest, AllWhereFalse)
{
    this->AllWhereFalse();
}

void AllFunctionalTest::AllWhereFalse()
{
    const bool all = this->queryable.Where([](const size_t value) { return value > 10; }).All(
        [](const size_t value) { return value < 20; });
    ASSERT_FALSE(all);
}

TEST_F(AllFunctionalGTest, AllWhereTrue)
{
    this->AllWhereTrue();
}

void AllFunctionalTest::AllWhereTrue()
{
    const bool all = this->queryable.Where([](const size_t value) { return value > 10; }).All(
        [](const size_t value) { return value < 2000; });
    ASSERT_TRUE(all);
}
