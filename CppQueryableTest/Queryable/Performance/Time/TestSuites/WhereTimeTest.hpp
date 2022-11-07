#ifndef CPPQUERYABLE_CPPQUERYABLETEST_QUERYABLE_PERFORMANCE_TIME_TESTSUITES_WHERETIMETEST_H
#define CPPQUERYABLE_CPPQUERYABLETEST_QUERYABLE_PERFORMANCE_TIME_TESTSUITES_WHERETIMETEST_H

#include <functional>

#include "../BaseTimeTest.hpp"
using namespace std::placeholders;

class WhereTimeTest final : public BaseTimeTest
{
public:
  WhereTimeTest()
  {
    this->methodName = "Where";
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
    this->testFxns["DequeNumberCopyToQueryableDequeTest"] =
        [&](TestCaseParams & p) { this->DequeNumberCopyToQueryableDequeTest(static_cast<TimeTestParams &>(p)); };
    this->testFxns["DequeNumberCopyToDequeTest"] =
        [&](TestCaseParams & p) { this->DequeNumberCopyToDequeTest(static_cast<TimeTestParams &>(p)); };
    this->testFxns["ListNumberTest"] =
        [&](TestCaseParams & p) { this->ListNumberTest(static_cast<TimeTestParams &>(p)); };
    this->testFxns["ListNumberCopyToQueryableListTest"] =
        [&](TestCaseParams & p) { this->ListNumberCopyToQueryableListTest(static_cast<TimeTestParams &>(p)); };
    this->testFxns["ListNumberCopyToListTest"] =
        [&](TestCaseParams & p) { this->ListNumberCopyToListTest(static_cast<TimeTestParams &>(p)); };
    this->testFxns["MultiSetNumberTest"] =
        [&](TestCaseParams & p) { this->MultiSetNumberTest(static_cast<TimeTestParams &>(p)); };
    this->testFxns["MultiSetNumberCopyToQueryableMultiSetTest"] =
        [&](TestCaseParams & p) { this->MultiSetNumberCopyToQueryableMultiSetTest(static_cast<TimeTestParams &>(p)); };
    this->testFxns["MultiSetNumberCopyToMultiSetTest"] =
        [&](TestCaseParams & p) { this->MultiSetNumberCopyToMultiSetTest(static_cast<TimeTestParams &>(p)); };
    this->testFxns["VectorNumberTest"] =
        [&](TestCaseParams & p) { this->VectorNumberTest(static_cast<TimeTestParams &>(p)); };
    this->testFxns["VectorNumberCopyToQueryableVectorTest"] =
        [&](TestCaseParams & p) { this->VectorNumberCopyToQueryableVectorTest(static_cast<TimeTestParams &>(p)); };
    this->testFxns["VectorNumberCopyToVectorTest"] =
        [&](TestCaseParams & p) { this->VectorNumberCopyToVectorTest(static_cast<TimeTestParams &>(p)); };

    BaseTimeTest::SetupTestSuite();
  }

    void DequeNumberTest(TimeTestParams &);
    void DequeNumberCopyToQueryableDequeTest(TimeTestParams &);
    void DequeNumberCopyToDequeTest(TimeTestParams &);
    void ListNumberTest(TimeTestParams &);
    void ListNumberCopyToQueryableListTest(TimeTestParams &);
    void ListNumberCopyToListTest(TimeTestParams &);
    void MultiSetNumberTest(TimeTestParams &);
    void MultiSetNumberCopyToQueryableMultiSetTest(TimeTestParams &);
    void MultiSetNumberCopyToMultiSetTest(TimeTestParams &);
    void VectorNumberTest(TimeTestParams &);
    void VectorNumberCopyToQueryableVectorTest(TimeTestParams &);
    void VectorNumberCopyToVectorTest(TimeTestParams &);
};

#endif