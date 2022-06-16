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
  uint expectedRange = 866;
  IQueryable<uint> queryable;

  RangeFunctionalTest() :
    queryable(BuildQueryable2(std::vector<uint>({ 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 })))
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
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToDeque());
  uint range = local
    .Range<std::deque, uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedRange, range);
}

TEST_F(RangeFunctionalTest, RangeAsDeque)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToDeque());
  uint range = local
    .AsQueryableDeque()
    .Range<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedRange, range);
}

TEST_F(RangeFunctionalTest, RangeExtendedDeque)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToDeque());
  uint range = local
    .AsExtendedQueryable<std::deque>()
    .Range<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedRange, range);
}

TEST_F(RangeFunctionalTest, RangeDequeDefault)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToDeque());
  uint range = local.Range();
  ASSERT_EQ(this->expectedRange, range);
}

TEST_F(RangeFunctionalTest, RangeTemplateList)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToList());
  uint range = local
    .Range<std::list, uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedRange, range);
}

TEST_F(RangeFunctionalTest, RangeAsList)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToList());
  uint range = local
    .AsQueryableList()
    .Range<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedRange, range);
}

TEST_F(RangeFunctionalTest, RangeExtendedList)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToList());
  uint range = local
    .AsExtendedQueryable<std::list>()
    .Range<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedRange, range);
}

TEST_F(RangeFunctionalTest, RangeListDefault)
{
  IQueryable<uint> local = BuildQueryable2(this->queryable.ToList());
  uint range = local.Range();
  ASSERT_EQ(this->expectedRange, range);
}

TEST_F(RangeFunctionalTest, RangeTemplateMultiSet)
{
  ISortedQueryable<uint> local = BuildQueryable2(this->queryable.ToMultiSet());
  uint range = local
    .Range<std::multiset, uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedRange, range);
}

TEST_F(RangeFunctionalTest, RangeAsMultiSet)
{
  ISortedQueryable<uint> local = BuildQueryable2(this->queryable.ToMultiSet());
  uint range = local
    .AsQueryableMultiSet()
    .Range<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedRange, range);
}

TEST_F(RangeFunctionalTest, RangeExtendedMultiSet)
{
  ISortedQueryable<uint> local = BuildQueryable2(this->queryable.ToMultiSet());
  uint range = local
    .AsExtendedQueryable<std::multiset>()
    .Range<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedRange, range);
}

TEST_F(RangeFunctionalTest, RangeMultiSetDefault)
{
  ISortedQueryable<uint> local = BuildQueryable2(this->queryable.ToMultiSet());
  uint range = local.Range();
  ASSERT_EQ(this->expectedRange, range);
}

TEST_F(RangeFunctionalTest, RangeTemplateSet)
{
  ISortedQueryable<uint> local = BuildQueryable2(this->queryable.ToSet());
  uint range = local
    .Range<std::set, uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedRange, range);
}

TEST_F(RangeFunctionalTest, RangeAsSet)
{
  ISortedQueryable<uint> local = BuildQueryable2(this->queryable.ToSet());
  uint range = local
    .AsQueryableSet()
    .Range<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedRange, range);
}

TEST_F(RangeFunctionalTest, RangeExtendedSet)
{
  ISortedQueryable<uint> local = BuildQueryable2(this->queryable.ToSet());
  uint range = local
    .AsExtendedQueryable<std::set>()
    .Range<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedRange, range);
}

TEST_F(RangeFunctionalTest, RangeSetDefault)
{
  ISortedQueryable<uint> local = BuildQueryable2(this->queryable.ToSet());
  uint range = local.Range();
  ASSERT_EQ(this->expectedRange, range);
}

TEST_F(RangeFunctionalTest, RangeTemplateWhere)
{
  uint expected = 855;
  uint range = this->queryable
    .Where([](uint value) { return value > 10; })
    .Range<std::vector, uint>([](uint value) { return value; });
  ASSERT_EQ(expected, range);
}

TEST_F(RangeFunctionalTest, RangeAsVectorWhere)
{
  uint expected = 855;
  uint range = this->queryable
    .Where([](uint value) { return value > 10; })
    .AsQueryableVector()
    .Range<uint>([](uint value) { return value; });
  ASSERT_EQ(expected, range);
}

TEST_F(RangeFunctionalTest, RangeExtendedWhere)
{
  uint expected = 855;
  uint range = this->queryable
    .Where([](uint value) { return value > 10; })
    .AsExtendedQueryable<std::vector>()
    .Range<uint>([](uint value) { return value; });
  ASSERT_EQ(expected, range);
}

TEST_F(RangeFunctionalTest, RangeWhereDefault)
{
  uint expected = 855;
  uint range = this->queryable.Where([](uint value) { return value > 10; }).Range();
  ASSERT_EQ(expected, range);
}
