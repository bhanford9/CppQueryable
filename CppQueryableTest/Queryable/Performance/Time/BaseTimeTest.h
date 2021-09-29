#ifndef CPPQUERYABLE_CPPQUERYABLETEST_QUERYABLE_PERFORMANCE_TIME_BASETIMETEST_H
#define CPPQUERYABLE_CPPQUERYABLETEST_QUERYABLE_PERFORMANCE_TIME_BASETIMETEST_H

#include <gtest/gtest.h>
#include <iostream>
#include <fstream>

#include "Utilities/TimeTestParams/TimeTestCategory.h"
#include "Utilities/TimeTestParams/TimeTestParams.h"
#include "Utilities/TimeTestParams/TriggerType.h"

class BaseTimeTest : public ::testing::TestWithParam<TimeTestParams>
{
protected:
  std::string queryableName = "QUERYABLE";
  std::string standardName = "STANDARD";

  void SetUp() override
  {
  }

  void TearDown() override {}

  void ProcessResults(const TimeTestParams & params)
  {
    if (params.GetDoLog())
    {
      std::string logFilePath = params.GetStatsFilePath();

      std::ofstream fileStream;
      fileStream.open(logFilePath);

      fileStream << "Id: " << params.GetId()
                 << "\nCategory: " << GetCategoryName(params.GetCategory())
                 << "\nContainer: " << params.GetContainerType()
                 << "\nMethod: " << params.GetMethodName()
                 << "\nTrigger: " << GetTriggerName(params.GetTriggerType())
                 << "\nExecuter: " << params.GetExecuterName()
                 << "\nContainer Size: " << params.GetContainerSize()
                 << "\nIterations: " << params.GetIterations()
                 << "\nTotal Millis: " << params.GetTotalMillis()
                 << "\nAverage Millis: " << params.GetAverageMillis()
                 << "\nFastest Millis: " << params.GetFastestMillis()
                 << "\nSlowest Millis: " << params.GetSlowestMillis()
                 << "\nRange Millis: " << params.GetRangeMillis() << std::endl;

      fileStream.close();
    }
  }
};

#endif
