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

#include "../../../Queryable/QueryBuilder.h"
#include "../../../Queryable/QueryableVector.h"

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
  QueryableVector<uint> queryable;

  void SetUp() override
  {
    this->queryable = BuildQueryable(std::vector<uint>({ 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 867, 1, 12 }));
  }

  void TearDown() override {}
};

TEST_F(AverageFunctionalTest, AverageUninitialized)
{
  QueryableVector<Person> emptyQueryable;
  double average = emptyQueryable.Average<double>([](Person p) { return p.GetAge(); });
  ASSERT_EQ(0, average);
}

TEST_F(AverageFunctionalTest, AverageVector)
{
  uint average = this->queryable.Average<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedAverage, average);
}

TEST_F(AverageFunctionalTest, AverageDeque)
{
  QueryableDeque<uint> local = BuildQueryable(this->queryable.ToDeque());
  uint average = local.Average<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedAverage, average);
}

TEST_F(AverageFunctionalTest, AverageList)
{
  QueryableList<uint> local = BuildQueryable(this->queryable.ToList());
  uint average = local.Average<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedAverage, average);
}

TEST_F(AverageFunctionalTest, AverageMultiSet)
{
  QueryableMultiSet<uint> local = BuildQueryable(this->queryable.ToMultiSet());
  uint average = local.Average<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedAverage, average);
}

TEST_F(AverageFunctionalTest, AverageSet)
{
  QueryableSet<uint> local = BuildQueryable(this->queryable.ToSet());
  uint average = local.Average<uint>([](uint value) { return value; });
  ASSERT_EQ(this->expectedNoDupsAverage, average);
}

TEST_F(AverageFunctionalTest, AverageWhere)
{
  uint expected = 185;
  uint average = this->queryable
    .Where([](uint value) { return value > 10; })
    ->Average<uint>([](uint value) { return value; });
  ASSERT_EQ(expected, average);
}
