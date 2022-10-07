#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <vector>

#include "../../../DataStructures/Gender.hpp"
#include "../../../DataStructures/Person.hpp"
#include "../../../DataStructures/PersonLibrary.hpp"
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
  size_t expectedNoDupsAverage = expectedNoDupsSum / expectedNoDupsCount;
  QueryableVector<size_t> queryable;

  AverageFunctionalTest() :
    queryable(BuildQueryable(std::vector<size_t>({ 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 867, 1, 12 })))
  {
  }

  void SetUp() override
  {
  }

  void TearDown() override {}
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
//   size_t average = emptyQueryable.Average();
//   ASSERT_EQ(0, average);
// }

TEST_F(AverageFunctionalTest, AverageOperatorOverload)
{
  Point expected(5, 2.5);
  QueryableVector<Point> points = BuildQueryable(std::vector<Point>({
    Point(2, 4),
    Point(3, 5),
    Point(7, 1),
    Point(8, 0)
  }));

  double averageX = points.Average([](Point point) { return point.X; });
  double averageY = points.Average([](Point point) { return point.Y; });

  ASSERT_EQ(expected.X, averageX);
  ASSERT_EQ(expected.Y, averageY);
}

TEST_F(AverageFunctionalTest, AverageVector)
{
  size_t average = this->queryable.Average([](size_t value) { return value; });
  ASSERT_EQ(this->expectedAverage, average);
}

TEST_F(AverageFunctionalTest, AverageVectorDefault)
{
  size_t average = this->queryable.Average();
  ASSERT_EQ(this->expectedAverage, average);
}

TEST_F(AverageFunctionalTest, AverageDeque)
{
  QueryableDeque<size_t> local = BuildQueryable(this->queryable.ToDeque());
  size_t average = local.Average([](size_t value) { return value; });
  ASSERT_EQ(this->expectedAverage, average);
}

TEST_F(AverageFunctionalTest, AverageDequeDefault)
{
  QueryableDeque<size_t> local = BuildQueryable(this->queryable.ToDeque());
  size_t average = local.Average();
  ASSERT_EQ(this->expectedAverage, average);
}

TEST_F(AverageFunctionalTest, AverageList)
{
  QueryableList<size_t> local = BuildQueryable(this->queryable.ToList());
  size_t average = local.Average([](size_t value) { return value; });
  ASSERT_EQ(this->expectedAverage, average);
}

TEST_F(AverageFunctionalTest, AverageListDefault)
{
  QueryableList<size_t> local = BuildQueryable(this->queryable.ToList());
  size_t average = local.Average();
  ASSERT_EQ(this->expectedAverage, average);
}

TEST_F(AverageFunctionalTest, AverageMultiSet)
{
  QueryableMultiSet<size_t> local = BuildQueryable(this->queryable.ToMultiSet());
  size_t average = local.Average([](size_t value) { return value; });
  ASSERT_EQ(this->expectedAverage, average);
}

TEST_F(AverageFunctionalTest, AverageMultiSetDefault)
{
  QueryableMultiSet<size_t> local = BuildQueryable(this->queryable.ToMultiSet());
  size_t average = local.Average();
  ASSERT_EQ(this->expectedAverage, average);
}

TEST_F(AverageFunctionalTest, AverageSet)
{
  QueryableSet<size_t> local = BuildQueryable(this->queryable.ToSet());
  size_t average = local.Average([](size_t value) { return value; });
  ASSERT_EQ(this->expectedNoDupsAverage, average);
}

TEST_F(AverageFunctionalTest, AverageSetDefault)
{
  QueryableSet<size_t> local = BuildQueryable(this->queryable.ToSet());
  size_t average = local.Average();
  ASSERT_EQ(this->expectedNoDupsAverage, average);
}

TEST_F(AverageFunctionalTest, AverageWhere)
{
  size_t expected = 185;
  size_t average = this->queryable
    .Where([](size_t value) { return value > 10; })
    .Average([](size_t value) { return value; });
  ASSERT_EQ(expected, average);
}

TEST_F(AverageFunctionalTest, AverageWhereDefault)
{
  size_t expected = 185;
  size_t average = this->queryable
    .Where([](size_t value) { return value > 10; })
    .Average();
  ASSERT_EQ(expected, average);
}
