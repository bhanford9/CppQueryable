#ifndef CPPQUERYABLETEST_QUERYABLE_TESTCASERESULT_H
#define CPPQUERYABLETEST_QUERYABLE_TESTCASERESULT_H

#include <sstream>
#include <string>
#include <vector>

#include "TestCaseParams/TestCaseParams.hpp"
#include "TestCaseFailure.hpp"

class TestCaseResult
{
private:
    size_t testNumber;
    size_t testsRan;
    std::string testName;
    size_t testsPassed;
    std::vector<TestCaseFailure> failures;

public:
    TestCaseResult() :
        testNumber(), testName(), testsRan(), testsPassed(), failures()
    {        
    }

    TestCaseResult(size_t testNumber, const std::string & testName) :
        testNumber(testNumber), testName(testName), testsRan(), testsPassed(), failures()
    {        
    }

    TestCaseResult(
        size_t testNumber,
        const std::string testName,
        size_t testsRan,
        size_t testsPassed,
        const std::vector<TestCaseFailure> & failures) :
        testNumber(testNumber),
        testName(testName),
        testsRan(testsRan),
        testsPassed(testsPassed),
        failures(failures)
    {        
    }

    TestCaseResult(
        size_t testNumber,
        const std::string testName,
        size_t testsRan,
        size_t testsPassed,
        std::vector<TestCaseFailure> && failures) :
        testNumber(testNumber),
        testName(testName),
        testsRan(testsRan),
        testsPassed(testsPassed),
        failures(std::move(failures))
    {        
    }

    void AddRun() { ++this->testsRan; }
    void AddPassed() { ++this->testsPassed; }
    size_t GetTestNumber() const { return this->testNumber; }
    std::string GetTestName() const { return this->testName; }
    size_t GetTotalRan() const { return this->testsRan; }
    size_t GetTotalPassed() const { return this->testsPassed; }
    size_t GetTotalFailed() const { return this->testsRan - this->testsPassed; }
    std::vector<TestCaseFailure> GetFailures() const { return this->failures; }
    bool GetPassState() const { return this->testsPassed == this->testsRan; }
    
    void AddFailure(const TestCaseFailure & failure)
    {
        this->failures.emplace_back(failure);
    }

    void AddFailure(
        size_t iteration,
        const std::string & message,
        const std::exception & exception,
        const std::shared_ptr<TestCaseParams> & params)
    {
        this->failures.emplace_back(
            TestCaseFailure(
                this->testNumber,
                iteration,
                this->testName,
                message,
                exception,
                params));
    }

    void AddFailure(
        size_t iteration,
        std::string && message,
        std::exception && exception,
        std::shared_ptr<TestCaseParams> && params)
    {
        this->failures.emplace_back(
            TestCaseFailure(
                this->testNumber,
                iteration,
                std::move(this->testName),
                std::move(message),
                std::move(exception),
                std::move(params)));
    }

    std::string ToString() const
    {
        std::stringstream str;

        str << this->testsPassed << " / " << this->testsRan << " Passed" << std::endl;

        for (const TestCaseFailure & failure : this->failures)
        {
            str << failure.ToString() << std::endl;
        }

        return str.str();
    }
};

#endif