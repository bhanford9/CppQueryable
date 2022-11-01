#ifndef CPPQUERYABLETEST_QUERYABLE_FUNCTIONAL_HEADERS_ANYFUNCTIONALTEST_H
#define CPPQUERYABLETEST_QUERYABLE_FUNCTIONAL_HEADERS_ANYFUNCTIONALTEST_H

#include <gtest/gtest.h>

#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include "../../../DataStructures/Gender.hpp"
#include "../../../DataStructures/Person.hpp"
#include "../../../DataStructures/PersonLibrary.hpp"

#include "../../../Queryable/QueryBuilder.hpp"

#include "DetachedTestFixture.hpp"

using namespace QueryBuilder;

class AllFunctionalTest : public DetachedTestFixture
{
protected:
  QueryableVector<size_t> queryable;
  QueryableVector<std::string> queryableStrings;

public:
  AllFunctionalTest() :
    queryable(BuildQueryable(std::vector<size_t>({ 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 }))),
    queryableStrings(BuildQueryable(std::vector<std::string>({ "nbc", "fox", "abc", "cbs", "the cw"})))
  {
    this->tests.push_back(std::bind(&AllFunctionalTest::AllStringFalse, this));
    this->tests.push_back(std::bind(&AllFunctionalTest::AllStringTrue, this));
    this->tests.push_back(std::bind(&AllFunctionalTest::AllDequeFalse, this));
    this->tests.push_back(std::bind(&AllFunctionalTest::AllDequeTrue, this));
    this->tests.push_back(std::bind(&AllFunctionalTest::AllListFalse, this));
    this->tests.push_back(std::bind(&AllFunctionalTest::AllListTrue, this));
    this->tests.push_back(std::bind(&AllFunctionalTest::AllMapFalse, this));
    this->tests.push_back(std::bind(&AllFunctionalTest::AllMapTrue, this));
    this->tests.push_back(std::bind(&AllFunctionalTest::AllMultiSetFalse, this));
    this->tests.push_back(std::bind(&AllFunctionalTest::AllMultiSetTrue, this));
    this->tests.push_back(std::bind(&AllFunctionalTest::AllSetFalse, this));
    this->tests.push_back(std::bind(&AllFunctionalTest::AllSetTrue, this));
    this->tests.push_back(std::bind(&AllFunctionalTest::AllWhereFalse, this));
    this->tests.push_back(std::bind(&AllFunctionalTest::AllWhereTrue, this));
  }

  virtual std::string GetName() const
  {
    return "All";
  }

  void AllStringFalse();
  void AllStringTrue();
  void AllDequeFalse();
  void AllDequeTrue();
  void AllListFalse();
  void AllListTrue();
  void AllMapFalse();
  void AllMapTrue();
  void AllMultiSetFalse();
  void AllMultiSetTrue();
  void AllSetFalse();
  void AllSetTrue();
  void AllWhereFalse();
  void AllWhereTrue();
};

class AllFunctionalGTest : public ::testing::Test, public AllFunctionalTest
{
public:
  AllFunctionalGTest()
  {
  }

  void SetUp() override
  {
  }

  void TearDown() override {}
};

#endif