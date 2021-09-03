#include <gtest/gtest.h>

#include <iostream>
#include <string>

#include "../../../../DataStructures/Animal.h"
#include "../../../../DataStructures/Person.h"
#include "../../../../DataStructures/People.h"

#include "../../../../Queryable/Queryable.h"

#include "../../../../Queryable/QueryBuilder.h"

#include "Utilities/TimeStats.h"
#include "Utilities/TimingUtilities.h"

using namespace QueryBuilder;
using namespace TimingUtilities;

class WherePerformanceTest : public ::testing::Test
{
protected:
  std::string queryableName = "QUERYABLE";
  std::string standardName = "STANDARD";
  void SetUp() override
  {
  }

  void TearDown() override {}
};

TEST_F(WherePerformanceTest, SmallVectorTest)
{
  ulong iterations = 100;

  std::vector<uint> data = { 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 };
  Queryable<uint> local = BuildQueryable(data);

  TimeStats queryableStats = RunTimeAndLog(
    [&]() { local.Where([](uint value) { return (value % 2) == 0; }); },
    iterations,
    this->queryableName
  );

  std::function<void()> action = [&]()
  {
    std::vector<uint> standardWhered;
    for (uint value : data)
    {
      if ((value % 2) == 0)
      {
        standardWhered.push_back(value);
      }
    }
  };

  TimeStats standardStats = RunTimeAndLog(action, iterations, this->standardName);

  CompareAndLog(queryableStats, standardStats);
}

TEST_F(WherePerformanceTest, LargeVectorTest)
{
  ulong iterations = 100;

  std::vector<uint> data = { 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 };
  for (int i = 0; i < 100000; i++)
  {
    data.push_back(data[i % 12]);
  }

  Queryable<uint> local = BuildQueryable(data);

  TimeStats queryableStats = RunTimeAndLog(
    [&]() { local.Where([](uint value) { return (value % 2) == 0; }); },
    iterations,
    this->queryableName
  );

  std::function<void()> action = [&]()
  {
    std::vector<uint> standardWhered;
    for (uint value : data)
    {
      if ((value % 2) == 0)
      {
        standardWhered.push_back(value);
      }
    }
  };

  TimeStats standardStats = RunTimeAndLog(action, iterations, this->standardName);

  CompareAndLog(queryableStats, standardStats);
}

TEST_F(WherePerformanceTest, VectorWhereMaxNaiveTest)
{
  uint expected = 76;
  ulong iterations = 100;

  std::vector<uint> data = { 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 };
  for (int i = 0; i < 100000; i++)
  {
    data.push_back(data[i % 12]);
  }

  Queryable<uint> local = BuildQueryable(data);

  std::function<void(Queryable<uint>*)> queryableAction = [&](Queryable<uint>* q)
  {
    uint max = q->Where([](uint value) { return (value % 2) == 0; })->Max();
    ASSERT_EQ(expected, max);
  };

  TimeStats queryableStats = RunTimeAndLog(queryableAction, iterations, local, this->queryableName);

  std::function<void(std::vector<uint>*)> action = [&](std::vector<uint>* q)
  {
    std::vector<uint> standardWhered;
    for (uint value : *q)
    {
      if ((value % 2) == 0)
      {
        standardWhered.push_back(value);
      }
    }

    uint max = 0;
    for (uint value : standardWhered)
    {
      if (value > max)
      {
        max = value;
      }
    }

    ASSERT_EQ(expected, max);
  };

  TimeStats standardStats = RunTimeAndLog(action, iterations, data, this->standardName);

  CompareAndLog(queryableStats, standardStats);
}
