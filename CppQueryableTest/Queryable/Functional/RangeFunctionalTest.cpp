#include <gtest/gtest.h>

#include <array>
#include <deque>
#include <exception>
#include <iostream>
#include <list>
#include <set>
#include <string>
#include <vector>

#include "../../../DataStructures/Gender.h"
#include "../../../DataStructures/Person.h"
#include "../../../DataStructures/PersonLibrary.h"
#include "../../../DataStructures/Point.h"

#include "../../../Queryable/QueryBuilder.h"


using namespace QueryBuilder;

class RangeFunctionalTest : public ::testing::Test
{
protected:
  uint expectedRange = 866;
  Queryable<uint> queryable;

  void SetUp() override
  {
    this->queryable = BuildQueryable(std::vector<uint>({ 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 }));
  }

  void TearDown() override {}
};

TEST_F(RangeFunctionalTest, RangeUninitialized)
{
  Queryable<Person> emptyQueryable;
  double range = emptyQueryable.Range<double>([](Person p) { return p.GetAge(); });
  ASSERT_EQ(0.0, range);
}

TEST_F(RangeFunctionalTest, RangeUninitializedDefault)
{
  Queryable<Point> emptyQueryable;
  Point range = emptyQueryable.Range();
  ASSERT_EQ(0.0, range.X);
  ASSERT_EQ(0.0, range.Y);
}

TEST_F(RangeFunctionalTest, RangePoint)
{
  Point expected(6, -4);
  Queryable<Point> points = BuildQueryable(std::vector<Point>({
    Point(2, 4),
    Point(3, 5),
    Point(7, 1),
    Point(8, 0)
  }));

  Point range = points.Range<Point>([](Point point) { return point; });

  ASSERT_EQ(expected.X, range.X);
  ASSERT_EQ(expected.Y, range.Y);
}

TEST_F(RangeFunctionalTest, RangePointDefault)
{
  Point expected(6, -4);
  Queryable<Point> points = BuildQueryable(std::vector<Point>({
    Point(2, 4),
    Point(3, 5),
    Point(7, 1),
    Point(8, 0)
  }));

  Point range = points.Range();

  ASSERT_EQ(expected.X, range.X);
  ASSERT_EQ(expected.Y, range.Y);
}

TEST_F(RangeFunctionalTest, RangeDeque)
{
  Queryable<uint> local = BuildQueryable(this->queryable.ToDeque());
  uint range = local.Range<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedRange, range);
}

TEST_F(RangeFunctionalTest, RangeDequeDefault)
{
  Queryable<uint> local = BuildQueryable(this->queryable.ToDeque());
  uint range = local.Range();
  ASSERT_EQ(this->expectedRange, range);
}

TEST_F(RangeFunctionalTest, RangeList)
{
  Queryable<uint> local = BuildQueryable(this->queryable.ToList());
  uint range = local.Range<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedRange, range);
}

TEST_F(RangeFunctionalTest, RangeListDefault)
{
  Queryable<uint> local = BuildQueryable(this->queryable.ToList());
  uint range = local.Range();
  ASSERT_EQ(this->expectedRange, range);
}

TEST_F(RangeFunctionalTest, RangeMultiSet)
{
  Queryable<uint> local = BuildQueryable(this->queryable.ToMultiSet());
  uint range = local.Range<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedRange, range);
}

TEST_F(RangeFunctionalTest, RangeMultiSetDefault)
{
  Queryable<uint> local = BuildQueryable(this->queryable.ToMultiSet());
  uint range = local.Range();
  ASSERT_EQ(this->expectedRange, range);
}

TEST_F(RangeFunctionalTest, RangeSet)
{
  Queryable<uint> local = BuildQueryable(this->queryable.ToSet());
  uint range = local.Range<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedRange, range);
}

TEST_F(RangeFunctionalTest, RangeSetDefault)
{
  Queryable<uint> local = BuildQueryable(this->queryable.ToSet());
  uint range = local.Range();
  ASSERT_EQ(this->expectedRange, range);
}

TEST_F(RangeFunctionalTest, RangeWhere)
{
  uint expected = 855;
  uint range = this->queryable
    .Where([](uint value) { return value > 10; })
    ->Range<uint>([](uint value) { return value; });
  ASSERT_EQ(expected, range);
}

TEST_F(RangeFunctionalTest, RangeWhereDefault)
{
  uint expected = 855;
  uint range = this->queryable.Where([](uint value) { return value > 10; })->Range();
  ASSERT_EQ(expected, range);
}
