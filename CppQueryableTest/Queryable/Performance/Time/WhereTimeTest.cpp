#include <gtest/gtest.h>

#include <iostream>
#include <string>

#include "../../../../DataStructures/Animal.h"
#include "../../../../DataStructures/Person.h"
#include "../../../../DataStructures/People.h"

#include "../../../../Queryable/Queryable.h"

#include "../../../../Queryable/QueryBuilder.h"

#include "BaseTimeTest.h"
#include "Utilities/TimeStats.h"
#include "Utilities/TimeTestParams/TimeTestParams.h"
#include "Utilities/TimingUtilities.h"

#include "Utilities/Duration.h"
#include "Utilities/TimingTypes.h"

using namespace QueryBuilder;
using namespace TimingUtilities;

class WhereTimeTest : public BaseTimeTest
{
protected:
  void SetUp() override
  {
    BaseTimeTest::SetUp();
    this->methodName = "Where";
  }
};

TEST_P(WhereTimeTest, VectorTest)
{
  this->params = GetParam();
  this->params.SetCategory(TimeTestCategory::BuiltInLowLoad);

  std::vector<uint> dataSample = { 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 };
  std::vector<uint> data;
  for (uint64_t i = 0; i < params.GetContainerSize(); i++)
  {
    data.push_back(dataSample[i % 12]);
  }

  Queryable<uint> local = BuildQueryable(data);

  this->queryableStats = RunTimeAndLog(
    [&]() { local.Where([](uint value) { return (value % 2) == 0; }); },
    params.GetIterations(),
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

  this->standardStats = RunTimeAndLog(action, params.GetIterations(), this->standardName);

  CompareAndLog(this->queryableStats, this->standardStats);
}

TEST_P(WhereTimeTest, VectorHeavyLoadTest)
{
  this->params = GetParam();
  this->params.SetCategory(TimeTestCategory::BuiltInHeavyLoad);

  std::vector<uint> dataSample = { 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 };
  std::vector<uint> data;
  for (uint64_t i = 0; i < params.GetContainerSize(); i++)
  {
    data.push_back(dataSample[i % 12]);
  }

  this->queryableStats = RunTimeAndLog(
    [&]()
    {
      Queryable<uint> local = BuildQueryable(data);

      local.Where([](uint value)
      {
        for (int i = 0; i < 100; i++)
        {
          value = sqrt(value * i / (value + 100));
        }

        return (value % 2) == 0;
      });

      local.ToVector();
    },
    params.GetIterations(),
    this->queryableName
  );

  std::function<void()> action = [&]()
  {
    std::vector<uint> standardWhered;
    for (uint value : data)
    {
      for (int i = 0; i < 100; i++)
      {
        value = sqrt(value * i / (value + 100));
      }

      if ((value % 2) == 0)
      {
        standardWhered.push_back(value);
      }
    }
  };

  this->standardStats = RunTimeAndLog(action, params.GetIterations(), this->standardName);

  CompareAndLog(this->queryableStats, this->standardStats);
}

// just an example for now. Won't actually care about naive approaches for timed tests
// TEST_P(WhereTimeTest, VectorWhereMaxNaiveTest)
// {
//   this->params = GetParam();
//   uint expected = params.GetContainerSize() >= 10 ? 76 : 4;
//
//   std::vector<uint> dataSample = { 4, 7, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 };
//   std::vector<uint> data;
//   for (uint64_t i = 0; i < params.GetContainerSize(); i++)
//   {
//     data.push_back(dataSample[i % 12]);
//   }
//
//   Queryable<uint> local = BuildQueryable(data);
//
//   std::function<void(Queryable<uint>*)> queryableAction = [&](Queryable<uint>* q)
//   {
//     uint max = q->Where([](uint value) { return (value % 2) == 0; }).Max();
//     ASSERT_EQ(expected, max);
//   };
//
//   TimeStats queryableStats = RunTimeAndLog(queryableAction, params.GetIterations(), local, this->queryableName);
//
//   std::function<void(std::vector<uint>*)> action = [&](std::vector<uint>* q)
//   {
//     std::vector<uint> standardWhered;
//     for (uint value : *q)
//     {
//       if ((value % 2) == 0)
//       {
//         standardWhered.push_back(value);
//       }
//     }
//
//     uint max = 0;
//     for (uint value : standardWhered)
//     {
//       if (value > max)
//       {
//         max = value;
//       }
//     }
//
//     ASSERT_EQ(expected, max);
//   };
//
//   TimeStats standardStats = RunTimeAndLog(action, params.GetIterations(), data, this->standardName);
//
//   std::cout << "\nTest Data:" << std::endl;
//   std::cout << "\tSize: " << params.GetContainerSize() << std::endl;
//   std::cout << "\tIterations: " << params.GetIterations() << std::endl;
//   CompareAndLog(queryableStats, standardStats);
// }

INSTANTIATE_TEST_SUITE_P(
  ForEachTimeTesting,
  WhereTimeTest,
  ::testing::Values(
    TimeTestParams(30, 100)));

// INSTANTIATE_TEST_SUITE_P(
//   ForEachTimeTesting,
//   WhereTimeTest,
//   ::testing::Values(
//     TimeTestParams(30, 1),
//     TimeTestParams(30, 10),
//     TimeTestParams(30, 100),
//     TimeTestParams(30, 1000),
//     TimeTestParams(30, 10000),
//     TimeTestParams(30, 100000),
//     TimeTestParams(30, 1000000)));
