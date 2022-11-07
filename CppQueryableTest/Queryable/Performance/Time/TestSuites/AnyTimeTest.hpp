  
#ifndef CPPQUERYABLE_CPPQUERYABLETEST_QUERYABLE_PERFORMANCE_TIME_TESTSUITES_ANYTIMETEST_H
#define CPPQUERYABLE_CPPQUERYABLETEST_QUERYABLE_PERFORMANCE_TIME_TESTSUITES_ANYTIMETEST_H

#include <functional>
#include <sstream>

#include "../BaseTimeTest.hpp"
using namespace std::placeholders;

class AnyTimeTest final : public BaseTimeTest
{
public:
  AnyTimeTest()
  {
    this->methodName = "Any";
  }

protected:  
  size_t triggerValue = 99999999;
  std::string nameTriggerValue = "Hello World!";
  size_t triggerIndex = 0;

  void Init(const TimeTestParams & params)
  {
    switch (params.GetTriggerType())
    {
      case TriggerType::Type::Begin:
        this->triggerIndex = 0;
        break;
      case TriggerType::Type::Quarter:
        this->triggerIndex = params.GetContainerSize() * 0.25;
        break;
      case TriggerType::Type::Half:
        this->triggerIndex = params.GetContainerSize() * 0.5;
        break;
      case TriggerType::Type::ThreeQuarter:
        this->triggerIndex = params.GetContainerSize() * 0.75;
        break;
      case TriggerType::Type::End:
        this->triggerIndex = params.GetContainerSize() - 1;
        break;
      case TriggerType::Type::Never:
        this->triggerIndex = params.GetContainerSize() + 1;
        this->triggerValue++;
        break;
      case TriggerType::Type::NotApplicable:
      default:
        break;
    }
  }

  void LogBaseWithTriggerData(const TimeTestParams & params)
  {
    std::stringstream preCompareInfo;
    preCompareInfo
      << "\tTrigger Type: " << TriggerType::GetTriggerName(params.GetTriggerType()) << std::endl
      << "\tTrigger Index: " << this->triggerIndex << std::endl;
    this->LogBaseData(params, preCompareInfo.str());
  }

  void SetupTestSuite() override
  {
    std::vector<TimeTestParams> params;
    this->AddTestParam(std::make_shared<TimeTestParams>(30, 10, 10, TriggerType::Type::Begin));
    this->AddTestParam(std::make_shared<TimeTestParams>(30, 10, 10, TriggerType::Type::Quarter));
    this->AddTestParam(std::make_shared<TimeTestParams>(30, 10, 10, TriggerType::Type::Half));
    this->AddTestParam(std::make_shared<TimeTestParams>(30, 10, 10, TriggerType::Type::ThreeQuarter));
    this->AddTestParam(std::make_shared<TimeTestParams>(30, 10, 10, TriggerType::Type::End));
    this->AddTestParam(std::make_shared<TimeTestParams>(30, 10, 10, TriggerType::Type::Never));
    this->AddTestParam(std::make_shared<TimeTestParams>(30, 10, 50, TriggerType::Type::Begin));
    this->AddTestParam(std::make_shared<TimeTestParams>(30, 10, 50, TriggerType::Type::Quarter));
    this->AddTestParam(std::make_shared<TimeTestParams>(30, 10, 50, TriggerType::Type::Half));
    this->AddTestParam(std::make_shared<TimeTestParams>(30, 10, 50, TriggerType::Type::ThreeQuarter));
    this->AddTestParam(std::make_shared<TimeTestParams>(30, 10, 50, TriggerType::Type::End));
    this->AddTestParam(std::make_shared<TimeTestParams>(30, 10, 50, TriggerType::Type::Never));
    // this->AddTestParam(std::make_shared<TimeTestParams>(30, 10, 100, TriggerType::Type::Begin));
    // this->AddTestParam(std::make_shared<TimeTestParams>(30, 10, 100, TriggerType::Type::Quarter));
    // this->AddTestParam(std::make_shared<TimeTestParams>(30, 10, 100, TriggerType::Type::Half));
    // this->AddTestParam(std::make_shared<TimeTestParams>(30, 10, 100, TriggerType::Type::ThreeQuarter));
    // this->AddTestParam(std::make_shared<TimeTestParams>(30, 10, 100, TriggerType::Type::End));
    // this->AddTestParam(std::make_shared<TimeTestParams>(30, 10, 100, TriggerType::Type::Never));
    // this->AddTestParam(std::make_shared<TimeTestParams>(30, 100, 10, TriggerType::Type::Begin));
    // this->AddTestParam(std::make_shared<TimeTestParams>(30, 100, 10, TriggerType::Type::Quarter));
    // this->AddTestParam(std::make_shared<TimeTestParams>(30, 100, 10, TriggerType::Type::Half));
    // this->AddTestParam(std::make_shared<TimeTestParams>(30, 100, 10, TriggerType::Type::ThreeQuarter));
    // this->AddTestParam(std::make_shared<TimeTestParams>(30, 100, 10, TriggerType::Type::End));
    // this->AddTestParam(std::make_shared<TimeTestParams>(30, 100, 10, TriggerType::Type::Never));
    // this->AddTestParam(std::make_shared<TimeTestParams>(30, 100, 50, TriggerType::Type::Begin));
    // this->AddTestParam(std::make_shared<TimeTestParams>(30, 100, 50, TriggerType::Type::Quarter));
    // this->AddTestParam(std::make_shared<TimeTestParams>(30, 100, 50, TriggerType::Type::Half));
    // this->AddTestParam(std::make_shared<TimeTestParams>(30, 100, 50, TriggerType::Type::ThreeQuarter));
    // this->AddTestParam(std::make_shared<TimeTestParams>(30, 100, 50, TriggerType::Type::End));
    // this->AddTestParam(std::make_shared<TimeTestParams>(30, 100, 50, TriggerType::Type::Never));
    // this->AddTestParam(std::make_shared<TimeTestParams>(30, 100, 100, TriggerType::Type::Begin));
    // this->AddTestParam(std::make_shared<TimeTestParams>(30, 100, 100, TriggerType::Type::Quarter));
    // this->AddTestParam(std::make_shared<TimeTestParams>(30, 100, 100, TriggerType::Type::Half));
    // this->AddTestParam(std::make_shared<TimeTestParams>(30, 100, 100, TriggerType::Type::ThreeQuarter));
    // this->AddTestParam(std::make_shared<TimeTestParams>(30, 100, 100, TriggerType::Type::End));
    // this->AddTestParam(std::make_shared<TimeTestParams>(30, 100, 100, TriggerType::Type::Never));
    // this->AddTestParam(std::make_shared<TimeTestParams>(30, 1000, 10, TriggerType::Type::Begin));
    // this->AddTestParam(std::make_shared<TimeTestParams>(30, 1000, 10, TriggerType::Type::Quarter));
    // this->AddTestParam(std::make_shared<TimeTestParams>(30, 1000, 10, TriggerType::Type::Half));
    // this->AddTestParam(std::make_shared<TimeTestParams>(30, 1000, 10, TriggerType::Type::ThreeQuarter));
    // this->AddTestParam(std::make_shared<TimeTestParams>(30, 1000, 10, TriggerType::Type::End));
    // this->AddTestParam(std::make_shared<TimeTestParams>(30, 1000, 10, TriggerType::Type::Never));
    // this->AddTestParam(std::make_shared<TimeTestParams>(30, 1000, 50, TriggerType::Type::Begin));
    // this->AddTestParam(std::make_shared<TimeTestParams>(30, 1000, 50, TriggerType::Type::Quarter));
    // this->AddTestParam(std::make_shared<TimeTestParams>(30, 1000, 50, TriggerType::Type::Half));
    // this->AddTestParam(std::make_shared<TimeTestParams>(30, 1000, 50, TriggerType::Type::ThreeQuarter));
    // this->AddTestParam(std::make_shared<TimeTestParams>(30, 1000, 50, TriggerType::Type::End));
    // this->AddTestParam(std::make_shared<TimeTestParams>(30, 1000, 50, TriggerType::Type::Never));
    // this->AddTestParam(std::make_shared<TimeTestParams>(30, 1000, 100, TriggerType::Type::Begin));
    // this->AddTestParam(std::make_shared<TimeTestParams>(30, 1000, 100, TriggerType::Type::Quarter));
    // this->AddTestParam(std::make_shared<TimeTestParams>(30, 1000, 100, TriggerType::Type::Half));
    // this->AddTestParam(std::make_shared<TimeTestParams>(30, 1000, 100, TriggerType::Type::ThreeQuarter));
    // this->AddTestParam(std::make_shared<TimeTestParams>(30, 1000, 100, TriggerType::Type::End));
    // this->AddTestParam(std::make_shared<TimeTestParams>(30, 1000, 100, TriggerType::Type::Never));
    // this->AddTestParam(std::make_shared<TimeTestParams>(30, 10000, 10, TriggerType::Type::Begin));
    // this->AddTestParam(std::make_shared<TimeTestParams>(30, 10000, 10, TriggerType::Type::Quarter));
    // this->AddTestParam(std::make_shared<TimeTestParams>(30, 10000, 10, TriggerType::Type::Half));
    // this->AddTestParam(std::make_shared<TimeTestParams>(30, 10000, 10, TriggerType::Type::ThreeQuarter));
    // this->AddTestParam(std::make_shared<TimeTestParams>(30, 10000, 10, TriggerType::Type::End));
    // this->AddTestParam(std::make_shared<TimeTestParams>(30, 10000, 10, TriggerType::Type::Never));
    // this->AddTestParam(std::make_shared<TimeTestParams>(30, 10000, 50, TriggerType::Type::Begin));
    // this->AddTestParam(std::make_shared<TimeTestParams>(30, 10000, 50, TriggerType::Type::Quarter));
    // this->AddTestParam(std::make_shared<TimeTestParams>(30, 10000, 50, TriggerType::Type::Half));
    // this->AddTestParam(std::make_shared<TimeTestParams>(30, 10000, 50, TriggerType::Type::ThreeQuarter));
    // this->AddTestParam(std::make_shared<TimeTestParams>(30, 10000, 50, TriggerType::Type::End));
    // this->AddTestParam(std::make_shared<TimeTestParams>(30, 10000, 50, TriggerType::Type::Never));
    // this->AddTestParam(std::make_shared<TimeTestParams>(30, 10000, 100, TriggerType::Type::Begin));
    // this->AddTestParam(std::make_shared<TimeTestParams>(30, 10000, 100, TriggerType::Type::Quarter));
    // this->AddTestParam(std::make_shared<TimeTestParams>(30, 10000, 100, TriggerType::Type::Half));
    // this->AddTestParam(std::make_shared<TimeTestParams>(30, 10000, 100, TriggerType::Type::ThreeQuarter));
    // this->AddTestParam(std::make_shared<TimeTestParams>(30, 10000, 100, TriggerType::Type::End));
    // this->AddTestParam(std::make_shared<TimeTestParams>(30, 10000, 100, TriggerType::Type::Never));

    this->testFxns["DequeNumberTest"] =
      [&](TestCaseParams & p) { this->DequeNumberTest(static_cast<TimeTestParams &>(p)); };
    this->testFxns["ListNumberTest"] =
      [&](TestCaseParams & p) { this->ListNumberTest(static_cast<TimeTestParams &>(p)); };
    this->testFxns["MultiSetNumberTest"] =
      [&](TestCaseParams & p) { this->MultiSetNumberTest(static_cast<TimeTestParams &>(p)); };
    this->testFxns["SetNumberTest"] =
      [&](TestCaseParams & p) { this->SetNumberTest(static_cast<TimeTestParams &>(p)); };
    this->testFxns["VectorNumberTest"] =
      [&](TestCaseParams & p) { this->VectorNumberTest(static_cast<TimeTestParams &>(p)); };
    this->testFxns["DequePersonTest"] =
      [&](TestCaseParams & p) { this->DequePersonTest(static_cast<TimeTestParams &>(p)); };
    this->testFxns["ListPersonTest"] =
      [&](TestCaseParams & p) { this->ListPersonTest(static_cast<TimeTestParams &>(p)); };
    this->testFxns["MultiSetPersonTest"] =
      [&](TestCaseParams & p) { this->MultiSetPersonTest(static_cast<TimeTestParams &>(p)); };
    this->testFxns["SetPersonTest"] =
      [&](TestCaseParams & p) { this->SetPersonTest(static_cast<TimeTestParams &>(p)); };
    this->testFxns["VectorPersonTest"] =
      [&](TestCaseParams & p) { this->VectorPersonTest(static_cast<TimeTestParams &>(p)); };

    BaseTimeTest::SetupTestSuite();
  }

    void DequeNumberTest(TimeTestParams &);
    void ListNumberTest(TimeTestParams &);
    void MultiSetNumberTest(TimeTestParams &);
    void SetNumberTest(TimeTestParams &);
    void VectorNumberTest(TimeTestParams &);
    void DequePersonTest(TimeTestParams &);
    void ListPersonTest(TimeTestParams &);
    void MultiSetPersonTest(TimeTestParams &);
    void SetPersonTest(TimeTestParams &);
    void VectorPersonTest(TimeTestParams &);
};

#endif