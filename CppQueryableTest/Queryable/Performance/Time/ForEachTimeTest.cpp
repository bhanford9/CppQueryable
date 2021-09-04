#include <gtest/gtest.h>

#include <iostream>
#include <string>

#include "../../../../DataStructures/Animal.h"
#include "../../../../DataStructures/Person.h"
#include "../../../../DataStructures/People.h"

#include "../../../../Queryable/Queryable.h"

#include "../../../../Queryable/QueryBuilder.h"

#include "Utilities/TimeStats.h"
#include "Utilities/TimeTestParams.h"
#include "Utilities/TimingUtilities.h"

using namespace QueryBuilder;
using namespace TimingUtilities;

class ForEachTimeTest : public ::testing::TestWithParam<TimeTestParams>
{
protected:
  std::string queryableName = "QUERYABLE";
  std::string standardName = "STANDARD";
  void SetUp() override
  {
  }

  void TearDown() override {}
};

TEST_P(ForEachTimeTest, SmallVectorTest)
{
  TimeTestParams params = GetParam();

  std::vector<uint> dataSample = { 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 };
  std::vector<uint> data;
  for (uint64_t i = 0; i < params.GetContainerSize(); i++)
  {
    data.push_back(dataSample[i % 12]);
  }

  Queryable<uint> local = BuildQueryable(data);

  TimeStats queryableStats = RunTimeAndLog(
    [&]() { local.ForEach([](uint value) { (void)value; }); },
    params.GetIterations(),
    this->queryableName
  );

  std::function<void()> action = [&]()
  {
    for (uint value : data)
    {
      (void)value;
    }
  };

  TimeStats standardStats = RunTimeAndLog(action, params.GetIterations(), this->standardName);

  CompareAndLog(queryableStats, standardStats);
}

INSTANTIATE_TEST_SUITE_P(
  ForEachTimeTesting,
  ForEachTimeTest,
  ::testing::Values(
    TimeTestParams(1, 30),
    TimeTestParams(10, 30),
    TimeTestParams(100, 30),
    TimeTestParams(1000, 30),
    TimeTestParams(10000, 30),
    TimeTestParams(100000, 30),
    TimeTestParams(1000000, 30)));
