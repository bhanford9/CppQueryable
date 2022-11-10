#ifndef CPPQUERYABLE_CPPQUERYABLETEST_QUERYABLE_PERFORMANCE_TIME_TESTSUITES_AGGREGATETIMETEST_H
#define CPPQUERYABLE_CPPQUERYABLETEST_QUERYABLE_PERFORMANCE_TIME_TESTSUITES_AGGREGATETIMETEST_H

#include <functional>

#include "../BaseTimeTest.hpp"
using namespace std::placeholders;

class AggregateTimeTest final : public BaseTimeTest
{
private:
    size_t overload;
public:
  explicit AggregateTimeTest(size_t overload)
  {
    this->overload = overload;

    switch(this->overload)
    {
        case 0: this->methodName = "Aggregate - Simple"; break;
        case 1: this->methodName = "Aggregate - Seeded"; break;
        case 2: this->methodName = "Aggregate - Finalizer"; break;
        default: this->methodName = "Aggregate - Unassigned"; break;
    }
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

    switch(this->overload)
    {
    case 0:
    {
        this->testFxns["DequeNumberTest"] =
            [&](TestCaseParams & p) { this->DequeNumberSimpleTest(static_cast<TimeTestParams &>(p)); };
        this->testFxns["ListNumberTest"] =
            [&](TestCaseParams & p) { this->ListNumberSimpleTest(static_cast<TimeTestParams &>(p)); };
        this->testFxns["MultiSetNumberTest"] =
            [&](TestCaseParams & p) { this->MultiSetNumberSimpleTest(static_cast<TimeTestParams &>(p)); };
        this->testFxns["SetNumberTest"] =
            [&](TestCaseParams & p) { this->SetNumberSimpleTest(static_cast<TimeTestParams &>(p)); };
        this->testFxns["VectorNumberTest"] =
            [&](TestCaseParams & p) { this->VectorNumberSimpleTest(static_cast<TimeTestParams &>(p)); };
        this->testFxns["DequePersonTest"] =
            [&](TestCaseParams & p) { this->DequePersonSimpleTest(static_cast<TimeTestParams &>(p)); };
        this->testFxns["ListPersonTest"] =
            [&](TestCaseParams & p) { this->ListPersonSimpleTest(static_cast<TimeTestParams &>(p)); };
        this->testFxns["MultiSetPersonTest"] =
            [&](TestCaseParams & p) { this->MultiSetPersonSimpleTest(static_cast<TimeTestParams &>(p)); };
        this->testFxns["SetPersonTest"] =
            [&](TestCaseParams & p) { this->SetPersonSimpleTest(static_cast<TimeTestParams &>(p)); };
        this->testFxns["VectorPersonTest"] =
            [&](TestCaseParams & p) { this->VectorPersonSimpleTest(static_cast<TimeTestParams &>(p)); };
        break;
    }
    case 1:
    {
        this->testFxns["DequeNumberTest"] =
            [&](TestCaseParams & p) { this->DequeNumberSeededTest(static_cast<TimeTestParams &>(p)); };
        this->testFxns["ListNumberTest"] =
            [&](TestCaseParams & p) { this->ListNumberSeededTest(static_cast<TimeTestParams &>(p)); };
        this->testFxns["MultiSetNumberTest"] =
            [&](TestCaseParams & p) { this->MultiSetNumberSeededTest(static_cast<TimeTestParams &>(p)); };
        this->testFxns["SetNumberTest"] =
            [&](TestCaseParams & p) { this->SetNumberSeededTest(static_cast<TimeTestParams &>(p)); };
        this->testFxns["VectorNumberTest"] =
            [&](TestCaseParams & p) { this->VectorNumberSeededTest(static_cast<TimeTestParams &>(p)); };
        this->testFxns["DequePersonTest"] =
            [&](TestCaseParams & p) { this->DequePersonSeededTest(static_cast<TimeTestParams &>(p)); };
        this->testFxns["ListPersonTest"] =
            [&](TestCaseParams & p) { this->ListPersonSeededTest(static_cast<TimeTestParams &>(p)); };
        this->testFxns["MultiSetPersonTest"] =
            [&](TestCaseParams & p) { this->MultiSetPersonSeededTest(static_cast<TimeTestParams &>(p)); };
        this->testFxns["SetPersonTest"] =
            [&](TestCaseParams & p) { this->SetPersonSeededTest(static_cast<TimeTestParams &>(p)); };
        this->testFxns["VectorPersonTest"] =
            [&](TestCaseParams & p) { this->VectorPersonSeededTest(static_cast<TimeTestParams &>(p)); };
        break;
    }
    case 2:
    {
        this->testFxns["DequeNumberTest"] =
            [&](TestCaseParams & p) { this->DequeNumberFinalizerTest(static_cast<TimeTestParams &>(p)); };
        this->testFxns["ListNumberTest"] =
            [&](TestCaseParams & p) { this->ListNumberFinalizerTest(static_cast<TimeTestParams &>(p)); };
        this->testFxns["MultiSetNumberTest"] =
            [&](TestCaseParams & p) { this->MultiSetNumberFinalizerTest(static_cast<TimeTestParams &>(p)); };
        this->testFxns["SetNumberTest"] =
            [&](TestCaseParams & p) { this->SetNumberFinalizerTest(static_cast<TimeTestParams &>(p)); };
        this->testFxns["VectorNumberTest"] =
            [&](TestCaseParams & p) { this->VectorNumberFinalizerTest(static_cast<TimeTestParams &>(p)); };
        this->testFxns["DequePersonTest"] =
            [&](TestCaseParams & p) { this->DequePersonFinalizerTest(static_cast<TimeTestParams &>(p)); };
        this->testFxns["ListPersonTest"] =
            [&](TestCaseParams & p) { this->ListPersonFinalizerTest(static_cast<TimeTestParams &>(p)); };
        this->testFxns["MultiSetPersonTest"] =
            [&](TestCaseParams & p) { this->MultiSetPersonFinalizerTest(static_cast<TimeTestParams &>(p)); };
        this->testFxns["SetPersonTest"] =
            [&](TestCaseParams & p) { this->SetPersonFinalizerTest(static_cast<TimeTestParams &>(p)); };
        this->testFxns["VectorPersonTest"] =
            [&](TestCaseParams & p) { this->VectorPersonFinalizerTest(static_cast<TimeTestParams &>(p)); };
        break;
    }
    default:break;
    }

    BaseTimeTest::SetupTestSuite();
  }
  
    void DequeNumberSimpleTest(TimeTestParams &);
    void ListNumberSimpleTest(TimeTestParams &);
    void MultiSetNumberSimpleTest(TimeTestParams &);
    void SetNumberSimpleTest(TimeTestParams &);
    void VectorNumberSimpleTest(TimeTestParams &);
    void DequePersonSimpleTest(TimeTestParams &);
    void ListPersonSimpleTest(TimeTestParams &);
    void MultiSetPersonSimpleTest(TimeTestParams &);
    void SetPersonSimpleTest(TimeTestParams &);
    void VectorPersonSimpleTest(TimeTestParams &);

    void DequeNumberSeededTest(TimeTestParams &);
    void ListNumberSeededTest(TimeTestParams &);
    void MultiSetNumberSeededTest(TimeTestParams &);
    void SetNumberSeededTest(TimeTestParams &);
    void VectorNumberSeededTest(TimeTestParams &);
    void DequePersonSeededTest(TimeTestParams &);
    void ListPersonSeededTest(TimeTestParams &);
    void MultiSetPersonSeededTest(TimeTestParams &);
    void SetPersonSeededTest(TimeTestParams &);
    void VectorPersonSeededTest(TimeTestParams &);

    void DequeNumberFinalizerTest(TimeTestParams &);
    void ListNumberFinalizerTest(TimeTestParams &);
    void MultiSetNumberFinalizerTest(TimeTestParams &);
    void SetNumberFinalizerTest(TimeTestParams &);
    void VectorNumberFinalizerTest(TimeTestParams &);
    void DequePersonFinalizerTest(TimeTestParams &);
    void ListPersonFinalizerTest(TimeTestParams &);
    void MultiSetPersonFinalizerTest(TimeTestParams &);
    void SetPersonFinalizerTest(TimeTestParams &);
    void VectorPersonFinalizerTest(TimeTestParams &);
};

#endif