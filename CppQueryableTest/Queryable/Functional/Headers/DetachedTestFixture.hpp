#ifndef CPPQUERYABLETEST_QUERYABLE_FUNCTIONAL_HEADERS_DETACHEDTESTFIXTURE_H
#define CPPQUERYABLETEST_QUERYABLE_FUNCTIONAL_HEADERS_DETACHEDTESTFIXTURE_H

#include <functional>
#include <iostream>
#include <string>
#include <vector>

class DetachedTestFixture
{
protected:
  std::vector<std::function<void()>> tests;
  std::vector<std::string> errors;

public:
 
  DetachedTestFixture() { }

  virtual std::string GetName() const = 0;

  void RunAll()
  {    
    std::cout << "Starting Test Suite: " << this->GetName() << std::endl;

    int testsRan = 0;
    int testsPassing = 0;
    
    for (const std::function<void()> & test : tests)
    {
      testsRan++;

      try
      {
        test();
        testsPassing++;
      }
      catch (const std::exception & ex)
      {
        errors.push_back(ex.what());
      }
    }

    std::cout << "Test Suite Complete: " << this->GetName()
      << " (Passing " << testsPassing << " / " << this->GetTestCount() << ")"
      << std::endl;
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