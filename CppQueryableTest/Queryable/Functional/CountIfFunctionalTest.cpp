#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "../../../Queryable/QueryBuilder.hpp"


using namespace QueryBuilder;

class CountIfFunctionalTest : public ::testing::Test
{
protected:
    size_t expectedEvensWithDuplicates    = 7;
    size_t expectedEvensWithoutDuplicates = 4;
    QueryableVector<size_t> queryable;

    CountIfFunctionalTest()
        : queryable(
            BuildQueryable(std::vector<size_t>({ 7, 4, 7, 4, 3, 76, 8, 45, 34, 76, 8, 867 })))
    {
    }

    virtual void SetUp() override
    {
    }

    static bool IsEven(const size_t value)
    {
        return (value % 2) == 0;
    }

    virtual void TearDown() override
    {
    }
};

// TEST_F(CountIfFunctionalTest, CountIfVectorUninitialized)
// {
//   IQueryable<Person> emptyQueryable;
//   ASSERT_EQ(0, emptyQueryable.CountIf([](Person p) { return true; }));
// }

TEST_F(CountIfFunctionalTest, CountIfDeque)
{
    const size_t count = BuildQueryable(this->queryable.ToDeque()).CountIf(this->IsEven);
    ASSERT_EQ(this->expectedEvensWithDuplicates, count);
}

TEST_F(CountIfFunctionalTest, CountIfList)
{
    const size_t count = BuildQueryable(this->queryable.ToList()).CountIf(this->IsEven);
    ASSERT_EQ(this->expectedEvensWithDuplicates, count);
}

TEST_F(CountIfFunctionalTest, CountIfMap)
{
    const size_t count = BuildQueryable(
        this->queryable
        .ToMap<size_t, std::string>(
            [](const size_t value) { return value; },
            [](const size_t value)
            {
                return std::to_string(static_cast<double>(value) / 2.0);
            }))
        .CountIf(
            [](const std::pair<const size_t, std::string> & kvp) { return kvp.first % 2 == 0; });
    ASSERT_EQ(this->expectedEvensWithoutDuplicates, count);
}

TEST_F(CountIfFunctionalTest, CountIfMultiSet)
{
    const size_t count = BuildQueryable(this->queryable.ToMultiSet()).CountIf(this->IsEven);
    ASSERT_EQ(this->expectedEvensWithDuplicates, count);
}

TEST_F(CountIfFunctionalTest, CountIfSet)
{
    const size_t count = BuildQueryable(this->queryable.ToSet()).CountIf(this->IsEven);
    ASSERT_EQ(this->expectedEvensWithoutDuplicates, count);
}

TEST_F(CountIfFunctionalTest, CountIfVector)
{
    ASSERT_EQ(this->expectedEvensWithDuplicates, this->queryable.CountIf(this->IsEven));
}

TEST_F(CountIfFunctionalTest, CountIfWhere)
{
    const auto count = this->queryable
        .Where([](const size_t value) { return value % 2 == 0; })
        .CountIf([](const size_t) { return true; });

    ASSERT_EQ(expectedEvensWithDuplicates, count);
}
