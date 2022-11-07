#ifndef CPPQUERYABLETEST_QUERYABLE_TESTCASE_H
#define CPPQUERYABLETEST_QUERYABLE_TESTCASE_H

#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "TestCaseParams/TestCaseParams.hpp"
#include "TestCaseResult.hpp"

class TestCase
{
protected:
    std::size_t testCaseNumber;
    std::string name;
    std::vector<std::shared_ptr<TestCaseParams>> params;
    std::function<void(TestCaseParams &)> testCase;

public:
    TestCase() : testCaseNumber(0), name(""), params(), testCase()
    {
    }

    TestCase(
        size_t nth,
        const std::string & name,
        const std::function<void()> & test) :
        testCaseNumber(nth),
        name(name),
        params(),
        testCase([&](TestCaseParams &) { test(); })
    {
    }

    TestCase(
        size_t nth,
        const std::string & name,
        const std::function<void(TestCaseParams &)> & test) :
        testCaseNumber(nth),
        name(name),
        params(),
        testCase(test)
    {
    }

    TestCase(
        size_t nth,
        std::string && name,
        std::function<void(TestCaseParams &)> && test) :
        testCaseNumber(nth),
        name(std::move(name)),
        params(),
        testCase(std::move(test))
    {
    }

    TestCase(
        size_t nth,
        const std::string name,
        const std::function<void(TestCaseParams &)> & test,
        const std::shared_ptr<TestCaseParams> & params) :
        testCaseNumber(nth),
        name(name),
        params(std::vector<std::shared_ptr<TestCaseParams>>(1, params)),
        testCase(test)
    {
    }

    TestCase(
        size_t nth,
        std::string && name,
        std::function<void(TestCaseParams &)> && test,
        std::shared_ptr<TestCaseParams> && params) :
        testCaseNumber(nth),
        name(std::move(name)),
        params(std::vector<std::shared_ptr<TestCaseParams>>(1, params)),
        testCase(std::move(test))
    {
    }

    TestCase(
        size_t nth,
        const std::string name,
        const std::function<void(TestCaseParams &)> & test,
        const std::vector<std::shared_ptr<TestCaseParams>> & params) :
        testCaseNumber(nth),
        name(name),
        params(params),
        testCase(test)
    {
    }

    virtual ~TestCase() = default;

    size_t GetTestCaseNumber() const { return this->testCaseNumber; }
    std::string GetName() const { return this->name; }
    std::vector<std::shared_ptr<TestCaseParams>> GetParams() const { return this->params; }

    void AddParams(const std::shared_ptr<TestCaseParams> & params)
    {
        this->params.emplace_back(params);
    }

    void AddParams(std::shared_ptr<TestCaseParams> && params)
    {
        this->params.emplace_back(std::move(params));
    }

    TestCaseResult operator()() const { return this->Execute(); }

    TestCaseResult Execute() const
    {
        size_t testsRan = 0;
        size_t testsPassed = 0;
        TestCaseResult result(this->testCaseNumber, this->name);

        for (const std::shared_ptr<TestCaseParams> & p : this->params)
        {
            try
            {
                this->testCase(*p);
                ++testsPassed;
                result.AddPassed();
            }
            catch (const std::exception & ex)
            {
                result.AddFailure(
                    testsRan,
                    std::move(ex.what()),
                    std::move(ex),
                    std::move(p));
            }

            ++testsRan;
            result.AddRun();
        }

        return result;
    }
};

#endif