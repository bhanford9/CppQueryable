#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "../../../DataStructures/Point.hpp"

#include "../../../Queryable/QueryBuilder.hpp"


using namespace QueryBuilder;

class AverageFunctionalTest : public ::testing::Test
{
protected:
    size_t expectedSum = 1144;
    size_t expectedCount = 13;
    size_t expectedAverage = expectedSum / expectedCount;

    size_t expectedNoDupsSum = 1057;
    size_t expectedNoDupsCount = 10;
    double expectedNoDupsAverage = static_cast<double>(expectedNoDupsSum) / static_cast<double>(expectedNoDupsCount);
    QueryableVector<size_t> queryable;

    AverageFunctionalTest()
        : queryable(
            BuildQueryable(std::vector<size_t>({ 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 867, 1, 12 })))
    {
    }

    virtual void SetUp() override
    {
    }

    virtual void TearDown() override
    {
    }
};

// TEST_F(AverageFunctionalTest, AverageUninitialized)
// {
//   IQueryable<Person> emptyQueryable;
//   double average = emptyQueryable.Average([](Person p) { return p.GetAge(); });
//   ASSERT_EQ(0, average);
// }
//
// TEST_F(AverageFunctionalTest, AverageUninitializedCustomDivisor)
// {
//   Point expected(0, 0);
//   IQueryable<Point> emptyQueryable;
//   Point average = emptyQueryable.Average([](const Point & sum, ulong count) { return count > 0 ? Point(sum.X / count, sum.Y / count) : Point(0,0); });
//   ASSERT_EQ(expected.X, average.X);
//   ASSERT_EQ(expected.Y, average.Y);
// }
//
// TEST_F(AverageFunctionalTest, AverageUninitializedDefault)
// {
//   IQueryable<size_t> emptyQueryable;
//   double average = emptyQueryable.Average();
//   ASSERT_EQ(0, average);
// }

TEST_F(AverageFunctionalTest, AverageOperatorOverload)
{
    const Point expected(5, 2.5);
    const QueryableVector<Point> points = BuildQueryable(
        std::vector<Point>({ Point(2, 4), Point(3, 5), Point(7, 1), Point(8, 0) }));

    const double averageX = points.Average([](const Point & point) { return point.X; });
    const double averageY = points.Average([](const Point & point) { return point.Y; });

    ASSERT_EQ(expected.X, averageX);
    ASSERT_EQ(expected.Y, averageY);
}

TEST_F(AverageFunctionalTest, AverageVector)
{
    const double average = this->queryable.Average(
        [](const size_t value) { return static_cast<double>(value); });
    ASSERT_EQ(this->expectedAverage, average);
}

TEST_F(AverageFunctionalTest, AverageVectorDefault)
{
    const double average = this->queryable.Average();
    ASSERT_EQ(this->expectedAverage, average);
}

TEST_F(AverageFunctionalTest, AverageDeque)
{
    const QueryableDeque<size_t> local = BuildQueryable(this->queryable.ToDeque());
    const double average = local.Average(
        [](const size_t value) { return static_cast<double>(value); });
    ASSERT_EQ(this->expectedAverage, average);
}

TEST_F(AverageFunctionalTest, AverageDequeDefault)
{
    const QueryableDeque<size_t> local = BuildQueryable(this->queryable.ToDeque());
    const double average = local.Average();
    ASSERT_EQ(this->expectedAverage, average);
}

TEST_F(AverageFunctionalTest, AverageList)
{
    const QueryableList<size_t> local = BuildQueryable(this->queryable.ToList());
    const double average = local.Average(
        [](const size_t value) { return static_cast<double>(value); });
    ASSERT_EQ(this->expectedAverage, average);
}

TEST_F(AverageFunctionalTest, AverageListDefault)
{
    const QueryableList<size_t> local = BuildQueryable(this->queryable.ToList());
    const double average = local.Average();
    ASSERT_EQ(this->expectedAverage, average);
}

TEST_F(AverageFunctionalTest, AverageMap)
{
    const QueryableMap<size_t, std::string> local = BuildQueryable(
        this->queryable.ToMap<size_t, std::string>(
            [](const size_t value) { return value; },
            [](const size_t value) { return std::to_string(static_cast<double>(value) / 2.0); }));
    const double average = local.Average(
        [](const std::pair<const size_t, std::string> & kvp)
        {
            return static_cast<double>(kvp.first);
        });
    ASSERT_EQ(this->expectedNoDupsAverage, average);
}

TEST_F(AverageFunctionalTest, AverageMultiSet)
{
    const QueryableMultiSet<size_t> local = BuildQueryable(this->queryable.ToMultiSet());
    const double average = local.Average(
        [](const size_t value) { return static_cast<double>(value); });
    ASSERT_EQ(this->expectedAverage, average);
}

TEST_F(AverageFunctionalTest, AverageMultiSetDefault)
{
    const QueryableMultiSet<size_t> local = BuildQueryable(this->queryable.ToMultiSet());
    const double average = local.Average();
    ASSERT_EQ(this->expectedAverage, average);
}

TEST_F(AverageFunctionalTest, AverageSet)
{
    const QueryableSet<size_t> local = BuildQueryable(this->queryable.ToSet());
    const double average = local.Average(
        [](const size_t value) { return static_cast<double>(value); });
    ASSERT_EQ(this->expectedNoDupsAverage, average);
}

TEST_F(AverageFunctionalTest, AverageSetDefault)
{
    const QueryableSet<size_t> local = BuildQueryable(this->queryable.ToSet());
    const double average = local.Average();
    ASSERT_EQ(this->expectedNoDupsAverage, average);
}

TEST_F(AverageFunctionalTest, AverageWhere)
{
    constexpr size_t expected = 185;
    const double average = this->queryable
        .Where([](const size_t value) { return value > 10; })
        .Average([](const size_t value) { return static_cast<double>(value); });
    ASSERT_EQ(expected, average);
}

TEST_F(AverageFunctionalTest, AverageWhereDefault)
{
    constexpr size_t expected = 185;
    const double average = this->queryable
        .Where([](const size_t value) { return value > 10; })
        .Average();
    ASSERT_EQ(expected, average);
}
