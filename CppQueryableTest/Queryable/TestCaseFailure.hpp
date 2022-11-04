#ifndef CPPQUERYABLETEST_QUERYABLE_TESTCASEFAILURE_H
#define CPPQUERYABLETEST_QUERYABLE_TESTCASEFAILURE_H

#include <exception>
#include <functional>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "TestCaseParams/TestCaseParams.hpp"

class TestCaseFailure
{
private:
    size_t testNumber;
    size_t iterationNumber;
    std::string testName;
    std::string failureMessage;
    std::exception exception;
    std::shared_ptr<TestCaseParams> params;

public:
    TestCaseFailure() :
        testNumber(0),
        iterationNumber(0),
        testName(""),
        failureMessage(""),
        exception(),
        params()
    {     
    }

    TestCaseFailure(
        size_t testNumber,
        size_t iteration,
        const std::string & testName,
        const std::string & message,
        const std::exception & exception,
        const std::shared_ptr<TestCaseParams> & params) :
        testNumber(testNumber),
        iterationNumber(iteration),
        testName(testName),
        failureMessage(message),
        exception(exception),
        params(params)
    {        
    }

    TestCaseFailure(
        size_t testNumber,
        size_t iteration,
        std::string && testName,
        std::string && message,
        std::exception && exception,
        std::shared_ptr<TestCaseParams> && params) :
        testNumber(testNumber),
        iterationNumber(iteration),
        testName(std::move(testName)),
        failureMessage(std::move(message)),
        exception(std::move(exception)),
        params(std::move(params))
    {        
    }

    size_t GetTestNumber() const { return this->testNumber; }
    size_t GetIteration() const { return this->iterationNumber; }
    std::string GetTestName() const { return this->testName; }
    std::string GetMessage() const { return this->failureMessage; }
    std::exception GetException() const { return this->exception; }
    std::shared_ptr<TestCaseParams> GetParams() const { return this->params; }
    void SetIteration(size_t i) { this->iterationNumber = i; }

    std::string ToString() const
    {
        std::stringstream str;
        str << "Test Number: " << this->testNumber << std::endl
            << "Iteration Number: " << this->iterationNumber << std::endl
            << "Test Name: " << this->testName << std::endl
            << "Error Message: " << this->failureMessage << std::endl
            << "Parameters: " << std::endl << this->params->ToString() << std::endl;
        return str.str();
    }
};

#endif