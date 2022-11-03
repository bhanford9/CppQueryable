#include <gtest/gtest.h>

#include <array>
#include <deque>
#include <vector>

#include "../../../DataStructures/Person.hpp"
#include "../../../DataStructures/Point.hpp"

#include "../../../Queryable/QueryBuilder.hpp"


using namespace QueryBuilder;

class RangeFunctionalTest : public ::testing::Test
{
protected:
    size_t expectedRange = 866;
    QueryableVector<size_t> queryable;

    RangeFunctionalTest()
        : queryable(
            BuildQueryable(std::vector<size_t>({ 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 })))
    {
    }

    virtual void SetUp() override
    {
    }

    virtual void TearDown() override
    {
    }
};

TEST_F(RangeFunctionalTest, RangeUninitialized)
{
    const QueryableVector<Person> emptyQueryable(BuildQueryable(std::vector<Person>()));
    const double range = emptyQueryable.Range<double>([](const Person & p) { return p.GetAge(); });
    ASSERT_EQ(0.0, range);
}

TEST_F(RangeFunctionalTest, RangeUninitializedDefault)
{
    const QueryableVector<Point> emptyQueryable(BuildQueryable(std::vector<Point>()));
    const Point range = emptyQueryable.Range<Point>(
        [](const Point & p) { return Point(p.X, p.Y); });
    ASSERT_EQ(0.0, range.X);
    ASSERT_EQ(0.0, range.Y);
}

TEST_F(RangeFunctionalTest, RangePoint)
{
    const Point expected(6, -4);
    const QueryableVector<Point> points = BuildQueryable(
        std::vector<Point>({ Point(2, 4), Point(3, 5), Point(7, 1), Point(8, 0) }));

    const Point range = points.Range<Point>([](const Point & point) { return point; });

    ASSERT_EQ(expected.X, range.X);
    ASSERT_EQ(expected.Y, range.Y);
}

TEST_F(RangeFunctionalTest, RangeDeque)
{
    const QueryableDeque<size_t> local = BuildQueryable(this->queryable.ToDeque());
    const size_t range = local.Range<size_t>([](const size_t value) { return value; });
    ASSERT_EQ(this->expectedRange, range);
}

TEST_F(RangeFunctionalTest, RangeDequeDefault)
{
    const QueryableDeque<size_t> local = BuildQueryable(this->queryable.ToDeque());
    const double range = local.Range();
    ASSERT_EQ(this->expectedRange, range);
}

TEST_F(RangeFunctionalTest, RangeList)
{
    const QueryableList<size_t> local = BuildQueryable(this->queryable.ToList());
    const size_t range = local.Range<size_t>([](const size_t value) { return value; });
    ASSERT_EQ(this->expectedRange, range);
}

TEST_F(RangeFunctionalTest, RangeListDefault)
{
    const QueryableList<size_t> local = BuildQueryable(this->queryable.ToList());
    const double range = local.Range();
    ASSERT_EQ(this->expectedRange, range);
}

TEST_F(RangeFunctionalTest, RangeMultiSet)
{
    const QueryableMultiSet<size_t> local = BuildQueryable(this->queryable.ToMultiSet());
    const size_t range = local.Range<size_t>([](const size_t value) { return value; });
    ASSERT_EQ(this->expectedRange, range);
}

TEST_F(RangeFunctionalTest, RangeMultiSetDefault)
{
    const QueryableMultiSet<size_t> local = BuildQueryable(this->queryable.ToMultiSet());
    const double range = local.Range();
    ASSERT_EQ(this->expectedRange, range);
}

TEST_F(RangeFunctionalTest, RangeSet)
{
    const QueryableSet<size_t> local = BuildQueryable(this->queryable.ToSet());
    const size_t range = local.Range<size_t>([](const size_t value) { return value; });
    ASSERT_EQ(this->expectedRange, range);
}

TEST_F(RangeFunctionalTest, RangeSetDefault)
{
    const QueryableSet<size_t> local = BuildQueryable(this->queryable.ToSet());
    const double range = local.Range();
    ASSERT_EQ(this->expectedRange, range);
}

TEST_F(RangeFunctionalTest, RangeWhere)
{
    constexpr size_t expected = 855;
    const size_t range = this->queryable.Where([](const size_t value) { return value > 10; }).Range<
        size_t>([](const size_t value) { return value; });
    ASSERT_EQ(expected, range);
}

TEST_F(RangeFunctionalTest, RangeWhereDefault)
{
    constexpr size_t expected = 855;
    const double range = this->queryable.Where([](const size_t value) { return value > 10; }).
        Range();
    ASSERT_EQ(expected, range);
}
