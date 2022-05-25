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
  uint expectedSum = 1144;
  uint expectedCount = 13;
  uint expectedAverage = expectedSum / expectedCount;

  uint expectedNoDupsSum = 1057;
  uint expectedNoDupsCount = 10;
  uint expectedNoDupsAverage = expectedNoDupsSum / expectedNoDupsCount;
  IQueryable<uint> queryable;

  AverageFunctionalTest() :
    queryable(BuildQueryable2(std::vector<uint>({ 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 867, 1, 12 })))
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
//   IQueryable<uint> emptyQueryable;
//   uint average = emptyQueryable.Average();
//   ASSERT_EQ(0, average);
// }

TEST_F(AverageFunctionalTest, AverageOperatorOverload)
{
  Point expected(5, 2.5);
  IQueryable<Point> points = BuildQueryable2(std::vector<Point>({
    Point(2, 4),
    Point(3, 5),
    Point(7, 1),
    Point(8, 0)
  }));

  double averageX = points.Average([](Point point) { return point.X; });
  double averageY = points.Average([](Point point) { return point.Y; });

  ASSERT_EQ(expected.X, averageX);
  ASSERT_EQ(expected.Y, averageY);

  // TODO --> this can only exist within the extended area
  Point average = points.Average<std::vector>([](const Point & sum, ulong count) { return Point(sum.X / count, sum.Y / count); });
  ASSERT_EQ(expected.X, average.X);
  ASSERT_EQ(expected.Y, average.Y);
}

TEST_F(AverageFunctionalTest, AverageVector)
{
  uint average = this->queryable.Average([](uint value) { return value; });
  ASSERT_EQ(this->expectedAverage, average);
}

TEST_F(AverageFunctionalTest, AverageVectorDefault)
{
  uint average = this->queryable.Average();
  ASSERT_EQ(this->expectedAverage, average);
}

TEST_F(AverageFunctionalTest, AverageDeque)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToDeque());
  uint average = local.Average([](uint value) { return value; });
  ASSERT_EQ(this->expectedAverage, average);
}

TEST_F(AverageFunctionalTest, AverageDequeDefault)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToDeque());
  uint average = local.Average();
  ASSERT_EQ(this->expectedAverage, average);
}

TEST_F(AverageFunctionalTest, AverageList)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToList());
  uint average = local.Average([](uint value) { return value; });
  ASSERT_EQ(this->expectedAverage, average);
}

TEST_F(AverageFunctionalTest, AverageListDefault)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToList());
  uint average = local.Average();
  ASSERT_EQ(this->expectedAverage, average);
}

TEST_F(AverageFunctionalTest, AverageMultiSet)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToMultiSet());
  uint average = local.Average([](uint value) { return value; });
  ASSERT_EQ(this->expectedAverage, average);
}

TEST_F(AverageFunctionalTest, AverageMultiSetDefault)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToMultiSet());
  uint average = local.Average();
  ASSERT_EQ(this->expectedAverage, average);
}

TEST_F(AverageFunctionalTest, AverageSet)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToSet());
  uint average = local.Average([](uint value) { return value; });
  ASSERT_EQ(this->expectedNoDupsAverage, average);
}

TEST_F(AverageFunctionalTest, AverageSetDefault)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToSet());
  uint average = local.Average();
  ASSERT_EQ(this->expectedNoDupsAverage, average);
}

TEST_F(AverageFunctionalTest, AverageWhere)
{
  uint expected = 185;
  uint average = this->queryable
    .Where([](uint value) { return value > 10; })
    .Average([](uint value) { return value; });
  ASSERT_EQ(expected, average);
}

TEST_F(AverageFunctionalTest, AverageWhereDefault)
{
  uint expected = 185;
  uint average = this->queryable
    .Where([](uint value) { return value > 10; })
    .Average();
  ASSERT_EQ(expected, average);
}
