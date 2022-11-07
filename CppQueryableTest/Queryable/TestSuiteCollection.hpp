#ifndef CPPQUERYABLETEST_QUERYABLE_TESTSUITECOLLECTION_H
#define CPPQUERYABLETEST_QUERYABLE_TESTSUITECOLLECTION_H

#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>

#include "TestSuite.hpp"
#include "Performance/Time/TestSuites/AnyTimeTest.hpp"
#include "Performance/Time/TestSuites/ForEachTimeTest.hpp"
#include "Performance/Time/TestSuites/WhereTimeTest.hpp"

class TestSuiteCollection
{
protected:
  std::map<std::string, std::shared_ptr<TestSuite>> tests;

public:
  TestSuiteCollection()
  {
    this->Any = std::make_shared<AnyTimeTest>();
    this->ForEach = std::make_shared<ForEachTimeTest>();
    this->Where = std::make_shared<WhereTimeTest>();

    this->AddTimeTestSuite(this->Any);
    this->AddTimeTestSuite(this->ForEach);
    this->AddTimeTestSuite(this->Where);
  }

  void RunAll()
  {
    for (const auto & kvp : tests)
    {
      kvp.second->RunAll();
    }
  }

  void RunTestSuite(std::string name)
  {
    this->tests[name]->RunAll();
  }

  bool IsValidSuite(std::string name) const
  {
    return this->tests.find(name) != this->tests.end();
  }

  std::set<std::string> GetAvailableTestSuites() const
  {
    std::set<std::string> keys;
    for (const auto & kvp : this->tests) keys.insert(kvp.first);
    return keys;
  }

  void AddFunctionalTestSuite(const std::shared_ptr<TestSuite> & test)
  {
    this->AddTestSuite(test, "FunctionalTest");
  }

  void AddTimeTestSuite(const std::shared_ptr<TestSuite> & test)
  {
    this->AddTestSuite(test, "TimeTest");
  }

  void AddTestSuite(const std::shared_ptr<TestSuite> & testSuite, const std::string & suffix)
  {
    this->tests[testSuite->GetName() + suffix] = testSuite;
  }

  std::shared_ptr<AnyTimeTest> Any;
  std::shared_ptr<ForEachTimeTest> ForEach;
  std::shared_ptr<WhereTimeTest> Where;
};

#endif