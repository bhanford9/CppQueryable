#ifndef CPPQUERYABLE_CPPQUERYABLETEST_QUERYABLE_PERFORMANCE_TIME_TESTSUITES_FOREACHTIMETEST_H
#define CPPQUERYABLE_CPPQUERYABLETEST_QUERYABLE_PERFORMANCE_TIME_TESTSUITES_FOREACHTIMETEST_H

#include <functional>

#include "../BaseTimeTest.hpp"
using namespace std::placeholders;

class ForEachTimeTest final : public BaseTimeTest
{
public:
  ForEachTimeTest()
  {
    this->methodName = "ForEach";
  }

protected:
  void SetupTestSuite() override
  {
    std::vector<TimeTestParams> params;
    this->AddTestParam(std::make_shared<TimeTestParams>(30, 10, 1));
    this->AddTestParam(std::make_shared<TimeTestParams>(30, 10, 10));
    this->AddTestParam(std::make_shared<TimeTestParams>(30, 10, 50));
    this->AddTestParam(std::make_shared<TimeTestParams>(30, 10, 100));
    this->AddTestParam(std::make_shared<TimeTestParams>(30, 30, 1));
    this->AddTestParam(std::make_shared<TimeTestParams>(30, 30, 10));
    this->AddTestParam(std::make_shared<TimeTestParams>(30, 30, 50));
    this->AddTestParam(std::make_shared<TimeTestParams>(30, 30, 100));
    this->AddTestParam(std::make_shared<TimeTestParams>(30, 1000, 1));
    this->AddTestParam(std::make_shared<TimeTestParams>(30, 1000, 10));
    this->AddTestParam(std::make_shared<TimeTestParams>(30, 1000, 50));
    this->AddTestParam(std::make_shared<TimeTestParams>(30, 1000, 100));
    this->AddTestParam(std::make_shared<TimeTestParams>(30, 10000, 1));
    this->AddTestParam(std::make_shared<TimeTestParams>(30, 10000, 10));
    this->AddTestParam(std::make_shared<TimeTestParams>(30, 10000, 50));
    this->AddTestParam(std::make_shared<TimeTestParams>(30, 10000, 100));

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