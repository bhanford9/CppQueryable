#include <gtest/gtest.h>

#include <array>
#include <deque>
#include <vector>

#include "../../../DataStructures/Person.hpp"

#include "../../../Queryable/QueryBuilder.hpp"


using namespace QueryBuilder;

class SumFunctionalTest : public ::testing::Test
{
protected:
  size_t expectedSum = 1144;
  size_t expectedNoDupsSum = 1057;
  QueryableVector<size_t> queryable;

  SumFunctionalTest() :
    queryable(BuildQueryable(std::vector<size_t>({ 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 867, 1, 12 })))
  {
  }

  void SetUp() override
  {
  }

  void TearDown() override {}
};

TEST_F(SumFunctionalTest, SumUninitialized)
{
  const QueryableVector<Person> emptyQueryable(BuildQueryable(std::vector<Person>()));
  const double sum = emptyQueryable.Sum([](const Person & p) { return p.GetAge(); });
  ASSERT_EQ(0, sum);
}

// TEST_F(SumFunctionalTest, SumUninitializedDefault)
// {
//   Point expected(0, 0);
//   IQueryable<Point> emptyQueryable(BuildQueryable(std::vector<Point>()));
//   Point sum = emptyQueryable.Sum();
//   ASSERT_EQ(expected.X, sum.X);
//   ASSERT_EQ(expected.Y, sum.Y);
// }

// TEST_F(SumFunctionalTest, SumOperatorOverload)
// {
//   Point expected(20, 10);
//   IQueryable<Point> points = BuildQueryable(std::vector<Point>({
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
  const double sum = this->queryable.Sum([](size_t value) { return static_cast<double>(value); });
  ASSERT_EQ(this->expectedSum, sum);
}

TEST_F(SumFunctionalTest, SumVectorDefault)
{
  const double sum = this->queryable.Sum();
  ASSERT_EQ(this->expectedSum, sum);
}

TEST_F(SumFunctionalTest, SumDeque)
{
  const QueryableDeque<size_t> local = BuildQueryable(this->queryable.ToDeque());
  const double sum = local.Sum([](size_t value) { return static_cast<double>(value); });
  ASSERT_EQ(this->expectedSum, sum);
}

TEST_F(SumFunctionalTest, SumDequeDefault)
{
  const QueryableDeque<size_t> local = BuildQueryable(this->queryable.ToDeque());
  const double sum = local.Sum();
  ASSERT_EQ(this->expectedSum, sum);
}

TEST_F(SumFunctionalTest, SumList)
{
  const QueryableList<size_t> local = BuildQueryable(this->queryable.ToList());
  const double sum = local.Sum([](size_t value) { return static_cast<double>(value); });
  ASSERT_EQ(this->expectedSum, sum);
}

TEST_F(SumFunctionalTest, SumListDefault)
{
  const QueryableList<size_t> local = BuildQueryable(this->queryable.ToList());
  const double sum = local.Sum();
  ASSERT_EQ(this->expectedSum, sum);
}

TEST_F(SumFunctionalTest, SumMultiSet)
{
  const QueryableMultiSet<size_t> local = BuildQueryable(this->queryable.ToMultiSet());
  const double sum = local.Sum([](size_t value) { return static_cast<double>(value); });
  ASSERT_EQ(this->expectedSum, sum);
}

TEST_F(SumFunctionalTest, SumMultiSetDefault)
{
  const QueryableMultiSet<size_t> local = BuildQueryable(this->queryable.ToMultiSet());
  const double sum = local.Sum();
  ASSERT_EQ(this->expectedSum, sum);
}

TEST_F(SumFunctionalTest, SumSet)
{
  const QueryableSet<size_t> local = BuildQueryable(this->queryable.ToSet());
  const double sum = local.Sum([](size_t value) { return static_cast<double>(value); });
  ASSERT_EQ(this->expectedNoDupsSum, sum);
}

TEST_F(SumFunctionalTest, SumSetDefault)
{
  const QueryableSet<size_t> local = BuildQueryable(this->queryable.ToSet());
  const double sum = local.Sum();
  ASSERT_EQ(this->expectedNoDupsSum, sum);
}

TEST_F(SumFunctionalTest, SumWhere)
{
  const size_t expected = 1110;
  const double sum = this->queryable
                         .Where([](size_t value) { return value > 10; })
                         .Sum([](size_t value) { return static_cast<double>(value); });
  ASSERT_EQ(expected, sum);
}

TEST_F(SumFunctionalTest, SumWhereDefault)
{
  const size_t expected = 1110;
  const double sum = this->queryable
                         .Where([](size_t value) { return value > 10; })
                         .Sum();
  ASSERT_EQ(expected, sum);
}
