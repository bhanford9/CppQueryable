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
  VectorInternalQueryable<uint> queryable;

  void SetUp() override
  {
    this->queryable = BuildQueryable(std::vector<uint>({ 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 867, 1, 12 }));
  }

  void TearDown() override {}
};

TEST_F(AverageFunctionalTest, AverageUninitialized)
{
  VectorInternalQueryable<Person> emptyQueryable;
  double average = emptyQueryable.Average<double>([](Person p) { return p.GetAge(); });
  ASSERT_EQ(0, average);
}

TEST_F(AverageFunctionalTest, AverageUninitializedCustomDivisor)
{
  Point expected(0, 0);
  VectorInternalQueryable<Point> emptyQueryable;
  Point average = emptyQueryable.Average([](const Point & sum, ulong count) { return count > 0 ? Point(sum.X / count, sum.Y / count) : Point(0,0); });
  ASSERT_EQ(expected.X, average.X);
  ASSERT_EQ(expected.Y, average.Y);
}

TEST_F(AverageFunctionalTest, AverageUninitializedDefault)
{
  VectorInternalQueryable<uint> emptyQueryable;
  uint average = emptyQueryable.Average();
  ASSERT_EQ(0, average);
}

TEST_F(AverageFunctionalTest, AverageOperatorOverload)
{
  Point expected(5, 2.5);
  VectorInternalQueryable<Point> points = BuildQueryable(std::vector<Point>({
    Point(2, 4),
    Point(3, 5),
    Point(7, 1),
    Point(8, 0)
  }));

  double averageX = points.Average<double>([](Point point) { return point.X; });
  double averageY = points.Average<double>([](Point point) { return point.Y; });

  ASSERT_EQ(expected.X, averageX);
  ASSERT_EQ(expected.Y, averageY);

  Point average = points.Average([](const Point & sum, ulong count) { return Point(sum.X / count, sum.Y / count); });
  ASSERT_EQ(expected.X, average.X);
  ASSERT_EQ(expected.Y, average.Y);
}

TEST_F(AverageFunctionalTest, AverageVector)
{
  uint average = this->queryable.Average<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedAverage, average);
}

TEST_F(AverageFunctionalTest, AverageVectorDefault)
{
  uint average = this->queryable.Average();
  ASSERT_EQ(this->expectedAverage, average);
}

TEST_F(AverageFunctionalTest, AverageDeque)
{
  DequeInternalQueryable<uint> local = BuildQueryable(this->queryable.ToDeque());
  uint average = local.Average<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedAverage, average);
}

TEST_F(AverageFunctionalTest, AverageDequeDefault)
{
  DequeInternalQueryable<uint> local = BuildQueryable(this->queryable.ToDeque());
  uint average = local.Average();
  ASSERT_EQ(this->expectedAverage, average);
}

TEST_F(AverageFunctionalTest, AverageList)
{
  ListInternalQueryable<uint> local = BuildQueryable(this->queryable.ToList());
  uint average = local.Average<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedAverage, average);
}

TEST_F(AverageFunctionalTest, AverageListDefault)
{
  ListInternalQueryable<uint> local = BuildQueryable(this->queryable.ToList());
  uint average = local.Average();
  ASSERT_EQ(this->expectedAverage, average);
}

TEST_F(AverageFunctionalTest, AverageMultiSet)
{
  MultiSetInternalQueryable<uint> local = BuildQueryable(this->queryable.ToMultiSet());
  uint average = local.Average<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedAverage, average);
}

TEST_F(AverageFunctionalTest, AverageMultiSetDefault)
{
  MultiSetInternalQueryable<uint> local = BuildQueryable(this->queryable.ToMultiSet());
  uint average = local.Average();
  ASSERT_EQ(this->expectedAverage, average);
}

TEST_F(AverageFunctionalTest, AverageSet)
{
  SetInternalQueryable<uint> local = BuildQueryable(this->queryable.ToSet());
  uint average = local.Average<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedNoDupsAverage, average);
}

TEST_F(AverageFunctionalTest, AverageSetDefault)
{
  SetInternalQueryable<uint> local = BuildQueryable(this->queryable.ToSet());
  uint average = local.Average();
  ASSERT_EQ(this->expectedNoDupsAverage, average);
}

TEST_F(AverageFunctionalTest, AverageWhere)
{
  uint expected = 185;
  uint average = this->queryable
    .Where([](uint value) { return value > 10; })
    .Average<uint>([](uint value) { return value; });
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
