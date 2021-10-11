#ifndef CPPQUERYABLE_CPPQUERYABLETEST_QUERYABLE_PERFORMANCE_TIME_BASETIMETEST_H
#define CPPQUERYABLE_CPPQUERYABLETEST_QUERYABLE_PERFORMANCE_TIME_BASETIMETEST_H

#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <time.h>

#include "Utilities/TimeStats.h"
#include "Utilities/TimeTestParams/DateTimeUtils.h"
#include "Utilities/TimeTestParams/TimeTestCategory.h"
#include "Utilities/TimeTestParams/TimeTestParams.h"
#include "Utilities/TimeTestParams/TriggerType.h"

class BaseTimeTest : public ::testing::TestWithParam<TimeTestParams>
{
protected:
  std::string dequeName = "Deque";
  std::string listName = "List";
  std::string multiSetName = "MultiSet";
  std::string setName = "Set";
  std::string vectorName = "Vector";

public:
  std::string queryableName = "QUERYABLE";
  std::string standardName = "STANDARD";
  std::string methodName = "";
  std::string containerName = "";
  std::string currentPath = __FILE__;
  TimeStats standardStats;
  TimeStats queryableStats;
  TimeTestParams params;
  static std::string suiteStartTime;

  static void SetUpTestSuite()
  {
    // suiteStartTime = DateTimeUtils::DateTimeString();
  }

  static void TearDownTestSuite()
  {
  }

  std::string GetContainerNameFromTestName(std::string testName)
  {
    if (testName.compare(0, this->dequeName.length(), this->dequeName) == 0)
    {
      return this->dequeName;
    }
    else if (testName.compare(0, this->listName.length(), this->listName) == 0)
    {
      return this->listName;
    }
    else if (testName.compare(0, this->multiSetName.length(), this->multiSetName) == 0)
    {
      return this->multiSetName;
    }
    else if (testName.compare(0, this->setName.length(), this->setName) == 0)
    {
      return this->setName;
    }
    else if (testName.compare(0, this->vectorName.length(), this->vectorName) == 0)
    {
      return this->vectorName;
    }

    return "Invalid Test Case Name: " + testName;
  }

  void SetUp() override
  {
    const testing::TestInfo* const testInfo =
      testing::UnitTest::GetInstance()->current_test_info();

    printf("We are in test %s of test suite %s.\n",
      testInfo->name(),
      testInfo->test_suite_name());

    this->containerName = this->GetContainerNameFromTestName(testInfo->name());
  }

  void TearDown() override
  {
    this->params.SetMethodName(this->methodName);
    this->params.SetContainerType(this->containerName);
    this->params.SetStandardStats(this->standardStats);
    this->params.SetQueryableStats(this->queryableStats);
    this->ProcessResults(this->params);
  }

  void ProcessResults(const TimeTestParams & params)
  {
    if (params.GetDoLog())
    {

      std::cout << "suite start time: " << BaseTimeTest::suiteStartTime << std::endl;

      int indexOfLastSlash = currentPath.find_last_of('/');
      std::string currentDir = currentPath.substr(0, indexOfLastSlash);

      std::string logFileDirectory =
        currentDir + "/Logs/" +
        params.GetContainerType() + "/" +
        params.GetMethodName() + "/" +
        BaseTimeTest::suiteStartTime + "/";
      std::string logFilePath =
        logFileDirectory +
        GetCategoryName(params.GetCategory()) + "Category_" + GetTriggerName(params.GetTriggerType()) + "Trigger.qbl.txt";

      std::cout << "path to write to: " << logFilePath << std::endl;

      // File Directory Structure:
      //   -- ContainerType
      //   ---- MethodName
      //   ------ YYYY-MM-DD-HH-MM-SS
      //   -------- Category_Trigger_Id

      // Workbook Structure:
      //   Workbook Name: Container Type
      //   Sheet Name: Method Name
      //   Columns: Executer, Category, Trigger, Container Size, Iterations, Total, Average, Fastest, Slowest, Range
      //   Row Counts: 2 Executer, 7 Category, 10 Triggers, 7 Sizes, 1 Iteration, 1 Total, 1 Average, 1 Fastest, 1 Slowest, 1 Range
      //   Total Rows: 2 x 7 x 10 x 7 x 1 = 980   (per container, per method, but not all combinations are valid)

      system(("mkdir -p " + logFileDirectory).c_str());
      std::ofstream fileStream;
      fileStream.open(logFilePath, std::ios_base::app);

      fileStream << "Category: " << GetCategoryName(params.GetCategory())
                 << "\nContainer: " << params.GetContainerType()
                 << "\nMethod: " << params.GetMethodName()
                 << "\nTrigger: " << GetTriggerName(params.GetTriggerType())
                 << "\nContainer Size: " << params.GetContainerSize()
                 << "\nIterations: " << params.GetIterations()
                 << "\nStandard Total Millis: " << params.GetStandardStats().GetTotal().Millis()
                 << "\nStandard Average Millis: " << params.GetStandardStats().GetAverage().Millis()
                 << "\nStandard Fastest Millis: " << params.GetStandardStats().GetMin().Millis()
                 << "\nStandard Slowest Millis: " << params.GetStandardStats().GetMax().Millis()
                 << "\nStandard Range Millis: " << params.GetStandardStats().GetRange().Millis()
                 << "\nQueryable Total Millis: " << params.GetQueryableStats().GetTotal().Millis()
                 << "\nQueryable Average Millis: " << params.GetQueryableStats().GetAverage().Millis()
                 << "\nQueryable Fastest Millis: " << params.GetQueryableStats().GetMin().Millis()
                 << "\nQueryable Slowest Millis: " << params.GetQueryableStats().GetMax().Millis()
                 << "\nQueryable Range Millis: " << params.GetQueryableStats().GetRange().Millis()
                 << "\n" << std::endl;

      fileStream.close();
    }
  }
};

std::string BaseTimeTest::suiteStartTime = DateTimeUtils::DateTimeString();

#endif
