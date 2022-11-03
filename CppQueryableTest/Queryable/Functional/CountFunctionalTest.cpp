#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "../../../Queryable/QueryBuilder.hpp"


using namespace QueryBuilder;

class CountFunctionalTest : public ::testing::Test
{
protected:
    size_t expectedWithDuplicates = 12;
    size_t expectedWithoutDuplicates = 8;
    QueryableVector<size_t> queryable;

    CountFunctionalTest()
        : queryable(
            BuildQueryable(std::vector<size_t>({ 7, 4, 7, 4, 3, 76, 8, 45, 34, 76, 8, 867 })))
    {
    }

    virtual void SetUp() override
    {
    }

    virtual void TearDown() override
    {
    }
};

// TEST_F(CountFunctionalTest, CountVectorUninitialized)
// {
//   IQueryable<Person> emptyQueryable;
//   ASSERT_EQ(0, emptyQueryable.Count());
// }

TEST_F(CountFunctionalTest, CountDeque)
{
    const size_t count = BuildQueryable(this->queryable.ToDeque()).Count();
    ASSERT_EQ(this->expectedWithDuplicates, count);
}

TEST_F(CountFunctionalTest, CountList)
{
    const size_t count = BuildQueryable(this->queryable.ToList()).Count();
    ASSERT_EQ(this->expectedWithDuplicates, count);
}

TEST_F(CountFunctionalTest, CounMap)
{
    const size_t count = BuildQueryable(
        this->queryable.ToMap<size_t, std::string>(
            [](const size_t value) { return value; },
            [](const size_t value)
            {
                return std::to_string(static_cast<double>(value) / 2.0);
            })).Count();
    ASSERT_EQ(this->expectedWithoutDuplicates, count);
}

TEST_F(CountFunctionalTest, CountMultiSet)
{
    const size_t count = BuildQueryable(this->queryable.ToMultiSet()).Count();
    ASSERT_EQ(this->expectedWithDuplicates, count);
}

TEST_F(CountFunctionalTest, CountSet)
{
    const size_t count = BuildQueryable(this->queryable.ToSet()).Count();
    ASSERT_EQ(this->expectedWithoutDuplicates, count);
}

TEST_F(CountFunctionalTest, CountVector)
{
    ASSERT_EQ(this->expectedWithDuplicates, this->queryable.Count());
}

TEST_F(CountFunctionalTest, CountWhere)
{
    constexpr size_t expected = 7;
    const size_t count = this->queryable.Where(
        [](const size_t value) { return value % 2 == 0; }).Count();

    ASSERT_EQ(expected, count);
}
