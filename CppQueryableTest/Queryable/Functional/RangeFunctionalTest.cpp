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
  IQueryable<size_t> queryable;

  RangeFunctionalTest() :
    queryable(BuildQueryable2(std::vector<size_t>({ 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 })))
  {
  }

  void SetUp() override
  {
  }

  void TearDown() override {}
};

TEST_F(RangeFunctionalTest, RangeTemplateUninitialized)
{
  IQueryable<Person> emptyQueryable(BuildQueryable2(std::vector<Person>()));
  double range = emptyQueryable
    .Range<std::vector, double>([](Person p) { return p.GetAge(); });
  ASSERT_EQ(0.0, range);
}

TEST_F(RangeFunctionalTest, RangeAsVectorUninitialized)
{
  IQueryable<Person> emptyQueryable(BuildQueryable2(std::vector<Person>()));
  double range = emptyQueryable
    .AsQueryableVector()
    .Range<double>([](Person p) { return p.GetAge(); });
  ASSERT_EQ(0.0, range);
}

TEST_F(RangeFunctionalTest, RangeExtendedUninitialized)
{
  IQueryable<Person> emptyQueryable(BuildQueryable2(std::vector<Person>()));
  double range = emptyQueryable
    .AsExtendedQueryable<std::vector>()
    .Range<double>([](Person p) { return p.GetAge(); });
  ASSERT_EQ(0.0, range);
}

TEST_F(RangeFunctionalTest, RangeTemplateUninitializedDefault)
{
  IQueryable<Point> emptyQueryable(BuildQueryable2(std::vector<Point>()));
  Point range = emptyQueryable
    .Range<std::vector, Point>([](Point p) { return Point(p.X, p.Y); });
  ASSERT_EQ(0.0, range.X);
  ASSERT_EQ(0.0, range.Y);
}

TEST_F(RangeFunctionalTest, RangeasVectorUninitializedDefault)
{
  IQueryable<Point> emptyQueryable(BuildQueryable2(std::vector<Point>()));
  Point range = emptyQueryable
    .AsQueryableVector()
    .Range<Point>([](Point p) { return Point(p.X, p.Y); });
  ASSERT_EQ(0.0, range.X);
  ASSERT_EQ(0.0, range.Y);
}

TEST_F(RangeFunctionalTest, RangeExtendedUninitializedDefault)
{
  IQueryable<Point> emptyQueryable(BuildQueryable2(std::vector<Point>()));
  Point range = emptyQueryable
    .AsExtendedQueryable<std::vector>()
    .Range<Point>([](Point p) { return p; });
  ASSERT_EQ(0.0, range.X);
  ASSERT_EQ(0.0, range.Y);
}

TEST_F(RangeFunctionalTest, RangeTemplatePoint)
{
  Point expected(6, -4);
  IQueryable<Point> points = BuildQueryable2(std::vector<Point>({
    Point(2, 4),
    Point(3, 5),
    Point(7, 1),
    Point(8, 0)
  }));

  Point range = points
    .Range<std::vector, Point>([](Point point) { return point; });

  ASSERT_EQ(expected.X, range.X);
  ASSERT_EQ(expected.Y, range.Y);
}

TEST_F(RangeFunctionalTest, RangeAsVectorPoint)
{
  Point expected(6, -4);
  IQueryable<Point> points = BuildQueryable2(std::vector<Point>({
    Point(2, 4),
    Point(3, 5),
    Point(7, 1),
    Point(8, 0)
  }));

  Point range = points
    .AsQueryableVector()
    .Range<Point>([](Point point) { return point; });

  ASSERT_EQ(expected.X, range.X);
  ASSERT_EQ(expected.Y, range.Y);
}

TEST_F(RangeFunctionalTest, RangeExtendedPoint)
{
  Point expected(6, -4);
  IQueryable<Point> points = BuildQueryable2(std::vector<Point>({
    Point(2, 4),
    Point(3, 5),
    Point(7, 1),
    Point(8, 0)
  }));

  Point range = points
    .AsExtendedQueryable<std::vector>()
    .Range<Point>([](Point point) { return point; });

  ASSERT_EQ(expected.X, range.X);
  ASSERT_EQ(expected.Y, range.Y);
}

TEST_F(RangeFunctionalTest, RangeTemplateDeque)
{
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToDeque());
  size_t range = local
    .Range<std::deque, size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedRange, range);
}

TEST_F(RangeFunctionalTest, RangeAsDeque)
{
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToDeque());
  size_t range = local
    .AsQueryableDeque()
    .Range<size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedRange, range);
}

TEST_F(RangeFunctionalTest, RangeExtendedDeque)
{
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToDeque());
  size_t range = local
    .AsExtendedQueryable<std::deque>()
    .Range<size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedRange, range);
}

TEST_F(RangeFunctionalTest, RangeDequeDefault)
{
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToDeque());
  size_t range = local.Range();
  ASSERT_EQ(this->expectedRange, range);
}

TEST_F(RangeFunctionalTest, RangeTemplateList)
{
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToList());
  size_t range = local
    .Range<std::list, size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedRange, range);
}

TEST_F(RangeFunctionalTest, RangeAsList)
{
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToList());
  size_t range = local
    .AsQueryableList()
    .Range<size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedRange, range);
}

TEST_F(RangeFunctionalTest, RangeExtendedList)
{
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToList());
  size_t range = local
    .AsExtendedQueryable<std::list>()
    .Range<size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedRange, range);
}

TEST_F(RangeFunctionalTest, RangeListDefault)
{
  IQueryable<size_t> local = BuildQueryable2(this->queryable.ToList());
  size_t range = local.Range();
  ASSERT_EQ(this->expectedRange, range);
}

TEST_F(RangeFunctionalTest, RangeTemplateMultiSet)
{
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToMultiSet());
  size_t range = local
    .Range<std::multiset, size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedRange, range);
}

TEST_F(RangeFunctionalTest, RangeAsMultiSet)
{
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToMultiSet());
  size_t range = local
    .AsQueryableMultiSet()
    .Range<size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedRange, range);
}

TEST_F(RangeFunctionalTest, RangeExtendedMultiSet)
{
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToMultiSet());
  size_t range = local
    .AsExtendedQueryable<std::multiset>()
    .Range<size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedRange, range);
}

TEST_F(RangeFunctionalTest, RangeMultiSetDefault)
{
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToMultiSet());
  size_t range = local.Range();
  ASSERT_EQ(this->expectedRange, range);
}

TEST_F(RangeFunctionalTest, RangeTemplateSet)
{
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToSet());
  size_t range = local
    .Range<std::set, size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedRange, range);
}

TEST_F(RangeFunctionalTest, RangeAsSet)
{
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToSet());
  size_t range = local
    .AsQueryableSet()
    .Range<size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedRange, range);
}

TEST_F(RangeFunctionalTest, RangeExtendedSet)
{
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToSet());
  size_t range = local
    .AsExtendedQueryable<std::set>()
    .Range<size_t>([](size_t value) { return value; });
  ASSERT_EQ(this->expectedRange, range);
}

TEST_F(RangeFunctionalTest, RangeSetDefault)
{
  ISortedQueryable<size_t> local = BuildQueryable2(this->queryable.ToSet());
  size_t range = local.Range();
  ASSERT_EQ(this->expectedRange, range);
}

TEST_F(RangeFunctionalTest, RangeTemplateWhere)
{
  size_t expected = 855;
  size_t range = this->queryable
    .Where([](size_t value) { return value > 10; })
    .Range<std::vector, size_t>([](size_t value) { return value; });
  ASSERT_EQ(expected, range);
}

TEST_F(RangeFunctionalTest, RangeAsVectorWhere)
{
  size_t expected = 855;
  size_t range = this->queryable
    .Where([](size_t value) { return value > 10; })
    .AsQueryableVector()
    .Range<size_t>([](size_t value) { return value; });
  ASSERT_EQ(expected, range);
}

TEST_F(RangeFunctionalTest, RangeExtendedWhere)
{
  size_t expected = 855;
  size_t range = this->queryable
    .Where([](size_t value) { return value > 10; })
    .AsExtendedQueryable<std::vector>()
    .Range<size_t>([](size_t value) { return value; });
  ASSERT_EQ(expected, range);
}

TEST_F(RangeFunctionalTest, RangeWhereDefault)
{
  size_t expected = 855;
  size_t range = this->queryable.Where([](size_t value) { return value > 10; }).Range();
  ASSERT_EQ(expected, range);
}
