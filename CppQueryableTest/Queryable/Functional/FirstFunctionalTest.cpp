#include <gtest/gtest.h>

#include <array>
#include <deque>
#include <exception>
#include <string>
#include <vector>

#include "../../../DataStructures/Person.hpp"

#include "../../../Queryable/QueryBuilder.hpp"


using namespace QueryBuilder;

class FirstFunctionalTest : public ::testing::Test
{
protected:
    size_t expectedUnorderedFirst = 9;
    size_t expectedOrderedFirst = 0;
    size_t expectedUnorderedOver40 = 76;
    size_t expectedOrderedOver40 = 45;
    size_t threshold = 40;
    QueryableVector<size_t> queryable;

    FirstFunctionalTest()
        : queryable(
            BuildQueryable(
                std::vector<size_t>(
                    { expectedUnorderedFirst, 4, 7, 4, 3, 76, 8, 45, 34, 76, 0, 867 })))
    {
    }

    virtual void SetUp() override
    {
    }

    virtual void TearDown() override
    {
    }
};

TEST_F(FirstFunctionalTest, FirstVectorUninitialized)
{
    QueryableVector<Person> emptyQueryable(BuildQueryable(std::vector<Person>()));

    try
    {
        Person p = emptyQueryable.First();
    }
    catch (std::runtime_error & ex)
    {
        ASSERT_STREQ(ex.what(), "Cannot get first item of empty collection.");
    }
}

TEST_F(FirstFunctionalTest, FirstDeque)
{
    const size_t value = BuildQueryable(this->queryable.ToDeque()).First();
    ASSERT_EQ(this->expectedUnorderedFirst, value);
}

TEST_F(FirstFunctionalTest, FirstList)
{
    const size_t value = BuildQueryable(this->queryable.ToList()).First();
    ASSERT_EQ(this->expectedUnorderedFirst, value);
}

TEST_F(FirstFunctionalTest, FirstMap)
{
    const size_t value = BuildQueryable(
        this->queryable.ToMap<size_t, std::string>(
            [](const size_t value) { return value; },
            [](const size_t value)
            {
                return std::to_string(static_cast<double>(value) / 2.0);
            })).First().first;
    ASSERT_EQ(this->expectedOrderedFirst, value);
}

TEST_F(FirstFunctionalTest, FirstMultiSet)
{
    const size_t value = BuildQueryable(this->queryable.ToMultiSet()).First();
    ASSERT_EQ(this->expectedOrderedFirst, value);
}

TEST_F(FirstFunctionalTest, FirstSet)
{
    const size_t value = BuildQueryable(this->queryable.ToSet()).First();
    ASSERT_EQ(this->expectedOrderedFirst, value);
}

TEST_F(FirstFunctionalTest, FirstVector)
{
    const size_t value = this->queryable.First();
    ASSERT_EQ(this->expectedUnorderedFirst, value);
}

TEST_F(FirstFunctionalTest, FirstWhereVectorUninitialized)
{
    QueryableVector<Person> emptyQueryable(BuildQueryable(std::vector<Person>()));

    try
    {
        Person p = emptyQueryable.First([](const Person & p) { return true; });
    }
    catch (std::runtime_error & ex)
    {
        ASSERT_STREQ(ex.what(), "No item fitting the condition was found.");
    }
}

TEST_F(FirstFunctionalTest, FirstWhereConditionFails)
{
    try
    {
        this->queryable.First([](size_t value) { return false; });
    }
    catch (std::runtime_error & ex)
    {
        ASSERT_STREQ(ex.what(), "No item fitting the condition was found.");
    }
}

TEST_F(FirstFunctionalTest, FirstWhereDeque)
{
    const size_t value = BuildQueryable(this->queryable.ToDeque()).First(
        [&](const size_t v) { return v > this->threshold; });
    ASSERT_EQ(this->expectedUnorderedOver40, value);
}

TEST_F(FirstFunctionalTest, FirstWhereList)
{
    const size_t value = BuildQueryable(this->queryable.ToList()).First(
        [&](const size_t v) { return v > this->threshold; });
    ASSERT_EQ(this->expectedUnorderedOver40, value);
}

TEST_F(FirstFunctionalTest, FirstWhereMap)
{
    const size_t value = BuildQueryable(
        this->queryable.ToMap<size_t, std::string>(
            [](const size_t v) { return v; },
            [](const size_t v) { return std::to_string(static_cast<double>(v) / 2.0); })).First(
        [&](const std::pair<const size_t &, std::string> & kvp)
        {
            return kvp.first > this->threshold;
        }).first;
    ASSERT_EQ(this->expectedOrderedOver40, value);
}

TEST_F(FirstFunctionalTest, FirstWhereMultiSet)
{
    const size_t value = BuildQueryable(this->queryable.ToMultiSet()).First(
        [&](const size_t v) { return v > this->threshold; });
    ASSERT_EQ(this->expectedOrderedOver40, value);
}

TEST_F(FirstFunctionalTest, FirstWhereSet)
{
    const size_t value = BuildQueryable(this->queryable.ToSet()).First(
        [&](const size_t v) { return v > this->threshold; });
    ASSERT_EQ(this->expectedOrderedOver40, value);
}

TEST_F(FirstFunctionalTest, FirstWhereVector)
{
    const size_t value = this->queryable.First([&](const size_t v) { return v > this->threshold; });
    ASSERT_EQ(this->expectedUnorderedOver40, value);
}

TEST_F(FirstFunctionalTest, FirstWhereEven)
{
    constexpr size_t expected = 4;
    const size_t value = this->queryable.Where([](const size_t v) { return v % 2 == 0; }).First();
    ASSERT_EQ(expected, value);
}

TEST_F(FirstFunctionalTest, FirstWhereOdd)
{
    const size_t expected = expectedUnorderedFirst;
    const size_t value = this->queryable.Where([](const size_t v) { return v % 2 == 1; }).First();
    ASSERT_EQ(expected, value);
}

TEST_F(FirstFunctionalTest, FirstWhereWhereEven)
{
    constexpr size_t expected = 76;
    const size_t value = this->queryable.Where([](const size_t v) { return v % 2 == 0; }).First(
        [](const size_t v) { return v > 10; });
    ASSERT_EQ(expected, value);
}

TEST_F(FirstFunctionalTest, FirstWhereWhereOdd)
{
    constexpr size_t expected = 45;
    const size_t value = this->queryable.Where([](const size_t v) { return v % 2 == 1; }).First(
        [](const size_t v) { return v > 10; });
    ASSERT_EQ(expected, value);
}
