#include <gtest/gtest.h>

#include <array>
#include <deque>
#include <exception>
#include <vector>

#include "../../../DataStructures/Person.hpp"

#include "../../../Queryable/QueryBuilder.hpp"


using namespace QueryBuilder;

class LastFunctionalTest : public ::testing::Test
{
protected:
    size_t expectedUnorderedLast;
    size_t expectedOrderedLast;
    size_t expectedUnorderedUnder40;
    size_t expectedOrderedUnder40;
    size_t threshold;
    QueryableVector<size_t> queryable;

    LastFunctionalTest()
        : expectedUnorderedLast(9), expectedOrderedLast(867), expectedUnorderedUnder40(9),
          expectedOrderedUnder40(34), threshold(40),
          queryable(
              BuildQueryable(
                  std::vector<size_t>(
                      {
                          4,
                          7,
                          4,
                          3,
                          76,
                          8,
                          45,
                          expectedOrderedLast,
                          76,
                          0,
                          expectedOrderedUnder40,
                          expectedUnorderedLast
                      })))
    {
    }

    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

TEST_F(LastFunctionalTest, LastVectorUninitialized)
{
    QueryableVector<Person> emptyQueryable(BuildQueryable(std::vector<Person>()));

    try
    {
        Person p = emptyQueryable.Last();
    }
    catch (std::runtime_error & ex)
    {
        ASSERT_STREQ(ex.what(), "Cannot get last item of empty collection.");
    }
}

TEST_F(LastFunctionalTest, LastVector)
{
    const size_t value = this->queryable.Last();
    ASSERT_EQ(this->expectedUnorderedLast, value);
}

TEST_F(LastFunctionalTest, LastSet)
{
    const size_t value = BuildQueryable(this->queryable.ToSet()).Last();
    ASSERT_EQ(this->expectedOrderedLast, value);
}

TEST_F(LastFunctionalTest, LastMultiSet)
{
    const size_t value = BuildQueryable(this->queryable.ToMultiSet()).Last();
    ASSERT_EQ(this->expectedOrderedLast, value);
}

TEST_F(LastFunctionalTest, LastDeque)
{
    const size_t value = BuildQueryable(this->queryable.ToDeque()).Last();
    ASSERT_EQ(this->expectedUnorderedLast, value);
}

TEST_F(LastFunctionalTest, LastList)
{
    const size_t value = BuildQueryable(this->queryable.ToList()).Last();
    ASSERT_EQ(this->expectedUnorderedLast, value);
}

TEST_F(LastFunctionalTest, LastWhereVectorUninitialized)
{
    QueryableVector<Person> emptyQueryable(BuildQueryable(std::vector<Person>()));

    try
    {
        Person p = emptyQueryable.Last([](const Person & p) { return true; });
    }
    catch (std::runtime_error & ex)
    {
        ASSERT_STREQ(ex.what(), "No item fitting the condition was found.");
    }
}

TEST_F(LastFunctionalTest, LastWhereConditionFails)
{
    try
    {
        this->queryable.Last([](size_t value) { return false; });
    }
    catch (std::runtime_error & ex)
    {
        ASSERT_STREQ(ex.what(), "No item fitting the condition was found.");
    }
}

TEST_F(LastFunctionalTest, LastWhereVector)
{
    const size_t value = this->queryable.Last(
        [&](size_t value) { return value < this->threshold; });
    ASSERT_EQ(this->expectedUnorderedUnder40, value);
}

TEST_F(LastFunctionalTest, LastWhereSet)
{
    const size_t value = BuildQueryable(this->queryable.ToSet()).Last(
        [&](size_t value) { return value < this->threshold; });
    ASSERT_EQ(this->expectedOrderedUnder40, value);
}

TEST_F(LastFunctionalTest, LastWhereMultiSet)
{
    const size_t value = BuildQueryable(this->queryable.ToMultiSet()).Last(
        [&](size_t value) { return value < this->threshold; });
    ASSERT_EQ(this->expectedOrderedUnder40, value);
}

TEST_F(LastFunctionalTest, LastWhereDeque)
{
    const size_t value = BuildQueryable(this->queryable.ToDeque()).Last(
        [&](size_t value) { return value < this->threshold; });
    ASSERT_EQ(this->expectedUnorderedUnder40, value);
}

TEST_F(LastFunctionalTest, LastWhereList)
{
    const size_t value = BuildQueryable(this->queryable.ToList()).Last(
        [&](size_t value) { return value < this->threshold; });
    ASSERT_EQ(this->expectedUnorderedUnder40, value);
}

TEST_F(LastFunctionalTest, LastWhereEven)
{
    const size_t expected = expectedOrderedUnder40;
    const size_t value = this->queryable.Where([](size_t value) { return value % 2 == 0; }).Last();
    ASSERT_EQ(expected, value);
}

TEST_F(LastFunctionalTest, LastWhereOdd)
{
    const size_t expected = expectedUnorderedLast;
    const size_t value = this->queryable.Where([](size_t value) { return value % 2 == 1; }).Last();
    ASSERT_EQ(expected, value);
}

TEST_F(LastFunctionalTest, LastWhereWhereEven)
{
    const size_t expected = 76;
    const size_t value = this->queryable.Where([](size_t value) { return value % 2 == 0; }).Last(
        [](size_t value) { return value > 40; });
    ASSERT_EQ(expected, value);
}

TEST_F(LastFunctionalTest, LastWhereWhereOdd)
{
    const size_t expected = expectedOrderedLast;
    const size_t value = this->queryable.Where([](size_t value) { return value % 2 == 1; }).Last(
        [](size_t value) { return value > 40; });
    ASSERT_EQ(expected, value);
}
