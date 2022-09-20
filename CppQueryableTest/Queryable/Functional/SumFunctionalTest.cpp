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

class SumFunctionalTest : public ::testing::Test
{
protected:
  size_t expectedSum = 1144;
  size_t expectedNoDupsSum = 1057;
  QueryableVector<size_t> queryable;

  SumFunctionalTest() :
    queryable(BuildQueryable2(std::vector<size_t>({ 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 867, 1, 12 })))
  {
  }

  void SetUp() override
  {
  }

  void TearDown() override {}
};

TEST_F(SumFunctionalTest, SumUninitialized)
{
  QueryableVector<Person> emptyQueryable(BuildQueryable2(std::vector<Person>()));
  double sum = emptyQueryable.Sum([](Person p) { return p.GetAge(); });
  ASSERT_EQ(0, sum);
}

// TEST_F(SumFunctionalTest, SumUninitializedDefault)
// {
//   Point expected(0, 0);
//   IQueryable<Point> emptyQueryable(BuildQueryable2(std::vector<Point>()));
//   Point sum = emptyQueryable.Sum();
//   ASSERT_EQ(expected.X, sum.X);
//   ASSERT_EQ(expected.Y, sum.Y);
// }

// TEST_F(SumFunctionalTest, SumOperatorOverload)
// {
//   Point expected(20, 10);
//   IQueryable<Point> points = BuildQueryable2(std::vector<Point>({
//     Point(2, 4),
//     Point(3, 5),
//     Point(7, 1),
//     Point(8, 0)
//   }));

//   Point sum = points.Sum([](Point point) { return point; });

//   ASSERT_EQ(expected.X, sum.X);
//   ASSERT_EQ(expected.Y, sum.Y);
// }

TEST_F(SumFunctionalTest, SumVector)
{
  size_t sum = this->queryable.Sum([](size_t value) { return value; });
  ASSERT_EQ(this->expectedSum, sum);
}

TEST_F(SumFunctionalTest, SumVectorDefault)
{
  size_t sum = this->queryable.Sum();
  ASSERT_EQ(this->expectedSum, sum);
}

TEST_F(SumFunctionalTest, SumDeque)
{
  QueryableDeque<size_t> local = BuildQueryable2(this->queryable.ToDeque());
  size_t sum = local.Sum([](size_t value) { return value; });
  ASSERT_EQ(this->expectedSum, sum);
}

TEST_F(SumFunctionalTest, SumDequeDefault)
{
  QueryableDeque<size_t> local = BuildQueryable2(this->queryable.ToDeque());
  size_t sum = local.Sum();
  ASSERT_EQ(this->expectedSum, sum);
}

TEST_F(SumFunctionalTest, SumList)
{
  QueryableList<size_t> local = BuildQueryable2(this->queryable.ToList());
  size_t sum = local.Sum([](size_t value) { return value; });
  ASSERT_EQ(this->expectedSum, sum);
}

TEST_F(SumFunctionalTest, SumListDefault)
{
  QueryableList<size_t> local = BuildQueryable2(this->queryable.ToList());
  size_t sum = local.Sum();
  ASSERT_EQ(this->expectedSum, sum);
}

TEST_F(SumFunctionalTest, SumMultiSet)
{
  QueryableMultiSet<size_t> local = BuildQueryable2(this->queryable.ToMultiSet());
  size_t sum = local.Sum([](size_t value) { return value; });
  ASSERT_EQ(this->expectedSum, sum);
}

TEST_F(SumFunctionalTest, SumMultiSetDefault)
{
  QueryableMultiSet<size_t> local = BuildQueryable2(this->queryable.ToMultiSet());
  size_t sum = local.Sum();
  ASSERT_EQ(this->expectedSum, sum);
}

TEST_F(SumFunctionalTest, SumSet)
{
  QueryableSet<size_t> local = BuildQueryable2(this->queryable.ToSet());
  size_t sum = local.Sum([](size_t value) { return value; });
  ASSERT_EQ(this->expectedNoDupsSum, sum);
}

TEST_F(SumFunctionalTest, SumSetDefault)
{
  QueryableSet<size_t> local = BuildQueryable2(this->queryable.ToSet());
  size_t sum = local.Sum();
  ASSERT_EQ(this->expectedNoDupsSum, sum);
}

TEST_F(SumFunctionalTest, SumWhere)
{
  size_t expected = 1110;
  size_t sum = this->queryable
    .Where([](size_t value) { return value > 10; })
    .Sum([](size_t value) { return value; });
  ASSERT_EQ(expected, sum);
}

TEST_F(SumFunctionalTest, SumWhereDefault)
{
  size_t expected = 1110;
  size_t sum = this->queryable
    .Where([](size_t value) { return value > 10; })
    .Sum();
  ASSERT_EQ(expected, sum);
}
