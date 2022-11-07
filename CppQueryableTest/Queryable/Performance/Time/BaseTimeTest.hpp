#ifndef CPPQUERYABLE_CPPQUERYABLETEST_QUERYABLE_PERFORMANCE_TIME_BASETIMETEST_H
#define CPPQUERYABLE_CPPQUERYABLETEST_QUERYABLE_PERFORMANCE_TIME_BASETIMETEST_H

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <time.h>

#include "Utilities/TimingUtilities.hpp"
#include "Utilities/TimeStats.hpp"
#include "Utilities/TimeTestParams/DateTimeUtils.hpp"
#include "Utilities/TimeTestParams/TimeTestCategory.hpp"
#include "Utilities/TimeTestParams/TimeTestParams.hpp"
#include "Utilities/TimeTestParams/TriggerType.hpp"
#include "../../TestSuite.hpp"
#include "../../TestCase.hpp"
#include "../../../../Queryable/Utilities/Casting.hpp"

class BaseTimeTest : public TestSuite
{
protected:
  std::string dequeName = "Deque";
  std::string listName = "List";
  std::string mapName = "Map";
  std::string multiSetName = "MultiSet";
  std::string setName = "Set";
  std::string vectorName = "Vector";
  std::vector<std::shared_ptr<TimeTestParams>> params;

public:
  std::string queryableName = "QUERYABLE";
  std::string standardName = "STANDARD";
  std::string methodName = "";
  std::string containerName = "";
  std::string currentPath = __FILE__;
  TimeStats standardStats;
  TimeStats queryableStats;

  BaseTimeTest() :
    methodName(""),
    containerName(""),
    standardStats(TimeStats()),
    queryableStats(TimeStats())
  {
  }

  std::string GetContainerNameFromTestName(const std::string & testName)
  {
    if (testName.compare(0, this->dequeName.length(), this->dequeName) == 0)
    {
      return this->dequeName;
    }
    else if (testName.compare(0, this->listName.length(), this->listName) == 0)
    {
      return this->listName;
    }
    else if (testName.compare(0, this->mapName.length(), this->mapName) == 0)
    {
      return this->mapName;
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

  void AddTestParam(std::shared_ptr<TimeTestParams> param)
  {
    this->params.emplace_back(param);
  }

  virtual void SetupTestSuite() override
  {
    size_t i = 0;
    for (const auto & kvp : this->testFxns)
    {
      std::vector<std::shared_ptr<TestCaseParams>> testCaseParams;

      for (auto param : this->params)
      {
        TimeTestParams copy = *param;
        copy.SetMethodName(kvp.first);
        testCaseParams.emplace_back(
          FutureStd::reinterpret_pointer_cast<TestCaseParams>(
            std::make_shared<TimeTestParams>(copy)));
      }

      this->tests.emplace_back(TestCase(i++, kvp.first, kvp.second, testCaseParams));
    }
  }

  virtual void TeardownTestSuite() override
  {
  }

  virtual std::string GetName() const override
  {
    return this->methodName;
  }

  void SetupTest(TestCase & test) override
  {
    this->containerName = this->GetContainerNameFromTestName(test.GetName());
    for (auto & param : test.GetParams())
    {
      (static_cast<TimeTestParams *>(param.get()))->SetMethodName(this->methodName);
      (static_cast<TimeTestParams *>(param.get()))->SetContainerType(containerName);
    }
  }

  void TeardownTest(TestCase & test) override
  {
    for (auto & param : test.GetParams())
    {
      TimeTestParams * params = static_cast<TimeTestParams *>(param.get());
      params->SetStandardStats(params->GetStandardStats());
      params->SetQueryableStats(params->GetQueryableStats());
      this->ProcessResults(*params, this->results[test.GetTestCaseNumber()]);
    }
  }

  void LogBaseData(const TimeTestParams & params, const std::string & preCompareInfo = "")
  {
    std::cout << "\nTest Data:" << std::endl << params << std::endl;
    CompareAndLog(params.GetQueryableStats(), params.GetStandardStats());
  }

  template<typename T = size_t>
  void ApplyLoad(size_t magnitude, T useDummy)
  {
    (void)useDummy;
    double value = 0.0;
    for (size_t i = 0; i < magnitude; i++)
    {
      value = sqrt(value * i / (value + 100));
    }
  }

  void ProcessResults(const TimeTestParams & params, const TestCaseResult & results)
  {
    if (params.GetDoLog())
    {

      std::cout << "suite start time: " << this->suiteStartTime << std::endl;

      int indexOfLastSlash = currentPath.find_last_of('/');
      std::string currentDir = currentPath.substr(0, indexOfLastSlash);

      std::string logFileDirectory =
        currentDir + "/Logs/" +
        params.GetContainerType() + "/" +
        params.GetMethodName() + "/" +
        this->suiteStartTime + "/";
      std::string logFilePath =
        logFileDirectory +
        GetCategoryName(params.GetCategory()) + "Category_" + GetTriggerName(params.GetTriggerType()) + "Trigger.qbl.txt";

      std::cout << "path to write to: " << logFilePath << std::endl;

      // File Directory Structure:
      //   -- ContainerType
      //   ---- MethodName
      //   ------ YYYY-MM-DD-HH-MM-SS
      //   -------- Category_Trigger_Id

      auto _ = system(("mkdir -p " + logFileDirectory).c_str());
      std::ofstream fileStream;
      fileStream.open(logFilePath, std::ios_base::app);

      fileStream << "Category: " << GetCategoryName(params.GetCategory())
                 << "\nContainer: " << params.GetContainerType()
                 << "\nMethod: " << params.GetMethodName()
                 << "\nTrigger: " << GetTriggerName(params.GetTriggerType())
                 << "\nContainer Size: " << params.GetContainerSize()
                 << "\nIterations: " << params.GetIterations()
                 << "\nLoad Magnitude: " << params.GetLoad()
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

#endif
