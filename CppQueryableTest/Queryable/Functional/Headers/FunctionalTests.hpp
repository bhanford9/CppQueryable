#ifndef CPPQUERYABLETEST_QUERYABLE_FUNCTIONAL_HEADERS_FUNCTIONALTESTS_H
#define CPPQUERYABLETEST_QUERYABLE_FUNCTIONAL_HEADERS_FUNCTIONALTESTS_H

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "AggregateFunctionalTest.hpp"
#include "AllFunctionalTest.hpp"
#include "AnyFunctionalTest.hpp"

class FunctionalTests
{
protected:
  std::map<std::string, std::shared_ptr<DetachedTestFixture>> tests;

public:
  FunctionalTests()
  {
    this->Aggregate = std::make_shared<AggregateFunctionalTest>();
    this->All = std::make_shared<AllFunctionalTest>();
    this->Any = std::make_shared<AnyFunctionalTest>();

    this->AddTest(this->Aggregate->GetName(), this->Aggregate);
    this->AddTest(this->All->GetName(), this->All);
    this->AddTest(this->Any->GetName(), this->Any);
  }

  void RunAll()
  {
    for (auto kvp : tests)
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

  template<typename T>
  void AddTest(const std::string & name, const std::shared_ptr<T> & test)
  {
    this->tests[name + "FunctionalTest"] =
        std::shared_ptr<DetachedTestFixture>(
            test,
            reinterpret_cast<DetachedTestFixture*>(
                test.get()));
  }

  std::shared_ptr<AggregateFunctionalTest> Aggregate;
  std::shared_ptr<AllFunctionalTest> All;
  std::shared_ptr<AnyFunctionalTest> Any;
};

#endif