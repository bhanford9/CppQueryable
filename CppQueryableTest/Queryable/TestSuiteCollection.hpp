#ifndef CPPQUERYABLETEST_QUERYABLE_TESTSUITECOLLECTION_H
#define CPPQUERYABLETEST_QUERYABLE_TESTSUITECOLLECTION_H

#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>

#include "TestSuite.hpp"
#include "Performance/Time/TestSuites/AggregateTimeTest.hpp"
#include "Performance/Time/TestSuites/AllTimeTest.hpp"
#include "Performance/Time/TestSuites/AnyTimeTest.hpp"
#include "Performance/Time/TestSuites/ForEachTimeTest.hpp"
#include "Performance/Time/TestSuites/WhereTimeTest.hpp"

class TestSuiteCollection
{
private:
  std::string functionalSuffix = "FunctionalTest";
  std::string timeSuffix = "TimeTest";

protected:
  std::map<std::string, std::shared_ptr<TestSuite>> tests;

public:
  TestSuiteCollection()
  {
    this->AggregateSimple = std::make_shared<AggregateTimeTest>(0);
    this->AggregateSeeded = std::make_shared<AggregateTimeTest>(1);
    this->AggregateFinalizer = std::make_shared<AggregateTimeTest>(2);
    this->All = std::make_shared<AllTimeTest>();
    this->Any = std::make_shared<AnyTimeTest>();
    this->ForEach = std::make_shared<ForEachTimeTest>();
    this->Where = std::make_shared<WhereTimeTest>();

    this->AddTimeTestSuite(this->AggregateSimple);
    this->AddTimeTestSuite(this->AggregateSeeded);
    this->AddTimeTestSuite(this->AggregateFinalizer);
    this->AddTimeTestSuite(this->All);
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

  void RunTestSuite(const std::string & name)
  {
    std::string nameWithoutWildcard = name;
    if (this->EndsWithWildcard(name, nameWithoutWildcard))
    {
      for (const auto & kvp : this->tests)
      {
        if (kvp.first.rfind(nameWithoutWildcard, 0) == 0)
        {
          kvp.second->RunAll();
        }
      }
    }
    else
    {
      this->tests[name]->RunAll();
    }
  }

  bool IsValidSuite(const std::string & name) const
  {
    std::string nameWithoutWildcard = name;
    if (this->EndsWithWildcard(name, nameWithoutWildcard))
    {
      for (const auto & kvp : this->tests)
      {
        if (kvp.first.rfind(nameWithoutWildcard, 0) == 0)
        {
          return true;
        }
      }

      return false;
    }

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
    this->AddTestSuite(test, this->functionalSuffix);
  }

  void AddTimeTestSuite(const std::shared_ptr<TestSuite> & test)
  {
    this->AddTestSuite(test, this->timeSuffix);
  }

  void AddTestSuite(const std::shared_ptr<TestSuite> & testSuite, const std::string & suffix)
  {
    this->tests[testSuite->GetName() + suffix] = testSuite;
  }

  bool EndsWithWildcard(const std::string & name, std::string & nameWithoutWildcard) const
  {
    if (*(--name.end()) == '*')
    {      
      nameWithoutWildcard = name;
      nameWithoutWildcard.pop_back();
      return true;
    }

    return false;
  }

  std::shared_ptr<AggregateTimeTest> AggregateSimple;
  std::shared_ptr<AggregateTimeTest> AggregateSeeded;
  std::shared_ptr<AggregateTimeTest> AggregateFinalizer;
  std::shared_ptr<AllTimeTest> All;
  std::shared_ptr<AnyTimeTest> Any;
  std::shared_ptr<ForEachTimeTest> ForEach;
  std::shared_ptr<WhereTimeTest> Where;
};

#endif