#include <gtest/gtest.h>

#include <array>
#include <deque>
#include <exception>
#include <iostream>
#include <list>
#include <set>
#include <string>
#include <vector>

#include "../../../DataStructures/Gender.hpp"
#include "../../../DataStructures/Person.hpp"
#include "../../../DataStructures/PersonLibrary.hpp"
#include "../../../DataStructures/Point.hpp"

#include "../../../Queryable/QueryBuilder.hpp"


using namespace QueryBuilder;

class RangeFunctionalTest : public ::testing::Test
{
protected:
  size_t expectedRange = 866;
  QueryableVector<size_t> queryable;

  RangeFunctionalTest() :
    queryable(BuildQueryable2(std::vector<size_t>({ 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 })))
  {
  }

  void SetUp() override
  {
  }

  void TearDown() override {}
};

TEST_F(RangeFunctionalTest, RangeUninitialized)
{
  QueryableVector<Person> emptyQueryable(BuildQueryable2(std::vector<Person>()));
  double range = emptyQueryable
    .Range<double>([](Person p) { return p.GetAge(); });
  ASSERT_EQ(0.0, range);
}

TEST_F(RangeFunctionalTest, RangeUninitializedDefault)
{
  QueryableVector<Point> emptyQueryable(BuildQueryable2(std::vector<Point>()));
  Point range = emptyQueryable
    .Range<Point>([](Point p) { return Point(p.X, p.Y); });
  ASSERT_EQ(0.0, range.X);
  ASSERT_EQ(0.0, range.Y);
}

TEST_F(RangeFunctionalTest, RangePoint)
{
  Point expected(6, -4);
  QueryableVector<Point> points = BuildQueryable2(std::vector<Point>({
    Point(2, 4),
    Point(3, 5),
    Point(7, 1),
    Point(8, 0)
  }));

  Point range = points
    .Range<Point>([](Point point) { return point; });

  ASSERT_EQ(expected.X, range.X);
  ASSERT_EQ(expected.Y, range.Y);
}

TEST_F(RangeFunctionalTest, RangeDeque)
{
  QueryableDeque<size_t> local = BuildQueryable2(this->queryable.ToDeque());
  size_t range = local
    .Range<size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedRange, range);
}

TEST_F(RangeFunctionalTest, RangeDequeDefault)
{
  QueryableDeque<size_t> local = BuildQueryable2(this->queryable.ToDeque());
  size_t range = local.Range();
  ASSERT_EQ(this->expectedRange, range);
}

TEST_F(RangeFunctionalTest, RangeList)
{
  QueryableList<size_t> local = BuildQueryable2(this->queryable.ToList());
  size_t range = local
    .Range<size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedRange, range);
}

TEST_F(RangeFunctionalTest, RangeListDefault)
{
  QueryableList<size_t> local = BuildQueryable2(this->queryable.ToList());
  size_t range = local.Range();
  ASSERT_EQ(this->expectedRange, range);
}

TEST_F(RangeFunctionalTest, RangeMultiSet)
{
  QueryableMultiSet<size_t> local = BuildQueryable2(this->queryable.ToMultiSet());
  size_t range = local
    .Range<size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedRange, range);
}

TEST_F(RangeFunctionalTest, RangeMultiSetDefault)
{
  QueryableMultiSet<size_t> local = BuildQueryable2(this->queryable.ToMultiSet());
  size_t range = local.Range();
  ASSERT_EQ(this->expectedRange, range);
}

TEST_F(RangeFunctionalTest, RangeSet)
{
  QueryableSet<size_t> local = BuildQueryable2(this->queryable.ToSet());
  size_t range = local
    .Range<size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedRange, range);
}

TEST_F(RangeFunctionalTest, RangeSetDefault)
{
  QueryableSet<size_t> local = BuildQueryable2(this->queryable.ToSet());
  size_t range = local.Range();
  ASSERT_EQ(this->expectedRange, range);
}

TEST_F(RangeFunctionalTest, RangeWhere)
{
  size_t expected = 855;
  size_t range = this->queryable
    .Where([](size_t value) { return value > 10; })
    .Range<size_t>([](size_t value) { return value; });
  ASSERT_EQ(expected, range);
}

TEST_F(RangeFunctionalTest, RangeWhereDefault)
{
  size_t expected = 855;
  size_t range = this->queryable.Where([](size_t value) { return value > 10; }).Range();
  ASSERT_EQ(expected, range);
}
