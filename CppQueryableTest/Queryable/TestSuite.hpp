#ifndef CPPQUERYABLETEST_QUERYABLE_TESTSUITE_H
#define CPPQUERYABLETEST_QUERYABLE_TESTSUITE_H

#include <ctime>
#include <functional>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "TestCase.hpp"
#include "TestCaseResult.hpp"

class TestSuite
{
protected:
  std::map<std::string, std::function<void(TestCaseParams &)>> testFxns;
  std::vector<TestCase> tests;
  std::vector<TestCaseResult> results;
  std::string suiteStartTime;

public:
 
  TestSuite() { }

  virtual std::string GetName() const = 0;

  virtual void SetupTestSuite() {}
  virtual void TeardownTestSuite() {}
  virtual void SetupTest(TestCase & test) {}
  virtual void TeardownTest(TestCase & test) {}

  void RunAll()
  {
    
    auto time = std::time(nullptr);
    auto localTime = *std::localtime(&time);
    std::stringstream timeStream;
    timeStream << std::put_time(&localTime, "%Y-%m-%d-%H-%M-%S");
    this->suiteStartTime = timeStream.str();

    std::cout << "Starting Test Suite: " << this->GetName() << std::endl;
    this->SetupTestSuite();

    size_t testsRan = 0;
    size_t testsPassing = 0;
    
    for (TestCase & test : tests)
    {
      std::cout << "Starting Test: " << test.GetName() << "..." << std::endl;
      
      this->SetupTest(test);      
      
      TestCaseResult result = test();
      
      std::cout << "Test Complete: " << test.GetName() << " : " << result.ToString() << std::endl;

      testsRan += result.GetTotalRan();
      testsPassing += result.GetTotalPassed();
      this->results.emplace_back(result);

      this->TeardownTest(test);
    }

    std::cout << std::endl << "Test Suite Complete: " << this->GetName()
      << " (Passing " << testsPassing << " / " << this->GetTestCount() << ")"
      << std::endl;
    
    this->TeardownTestSuite();
  }

  template<typename T>
  void AddTest(void (*testMethod)(), T * object)
  {
    this->tests.push_back(std::bind(testMethod, object));
  }

  int GetTestCount()
  {
    return this->tests.size();
  }
};

#endif