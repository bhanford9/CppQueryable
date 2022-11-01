#ifndef CPPQUERYABLETEST_QUERYABLE_FUNCTIONAL_HEADERS_ALLFUNCTIONALTEST_H
#define CPPQUERYABLETEST_QUERYABLE_FUNCTIONAL_HEADERS_ALLFUNCTIONALTEST_H

#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <vector>

#include "../../../DataStructures/Gender.hpp"
#include "../../../DataStructures/Person.hpp"
#include "../../../DataStructures/PersonLibrary.hpp"

#include "../../../Queryable/IQueryable.hpp"
#include "../../../Queryable/ISortedQueryable.hpp"

#include "../../../Queryable/QueryableAliases.hpp"
#include "../../../Queryable/QueryBuilder.hpp"

#include "DetachedTestFixture.hpp"

using namespace QueryBuilder;

class AnyFunctionalTest : public DetachedTestFixture
{
protected:
  QueryableVector<size_t> queryable;
  QueryableVector<std::string> queryableStrings;

public:
  AnyFunctionalTest() :
    queryable(BuildQueryable(std::vector<size_t>({ 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 }))),
    queryableStrings(BuildQueryable(std::vector<std::string>({ "nbc", "fox", "abc", "cbs", "the cw"})))
  {
    this->tests.push_back(std::bind(&AnyFunctionalTest::AnyUninitialized, this));
    this->tests.push_back(std::bind(&AnyFunctionalTest::AnyStringFalse, this));
    this->tests.push_back(std::bind(&AnyFunctionalTest::AnyStringTrue, this));
    this->tests.push_back(std::bind(&AnyFunctionalTest::AnyDequeFalse, this));
    this->tests.push_back(std::bind(&AnyFunctionalTest::AnyDequeTrue, this));
    this->tests.push_back(std::bind(&AnyFunctionalTest::AnyListFalse, this));
    this->tests.push_back(std::bind(&AnyFunctionalTest::AnyListTrue, this));
    this->tests.push_back(std::bind(&AnyFunctionalTest::AnyMapFalse, this));
    this->tests.push_back(std::bind(&AnyFunctionalTest::AnyMapTrue, this));
    this->tests.push_back(std::bind(&AnyFunctionalTest::AnyMultiSetFalse, this));
    this->tests.push_back(std::bind(&AnyFunctionalTest::AnyMultiSetTrue, this));
    this->tests.push_back(std::bind(&AnyFunctionalTest::AnySetFalse, this));
    this->tests.push_back(std::bind(&AnyFunctionalTest::AnySetTrue, this));
    this->tests.push_back(std::bind(&AnyFunctionalTest::AnyWhereFalse, this));
    this->tests.push_back(std::bind(&AnyFunctionalTest::AnyWhereTrue, this));
  }

  virtual std::string GetName() const
  {
    return "Any";
  }

  void AnyUninitialized();
  void AnyStringFalse();
  void AnyStringTrue();
  void AnyDequeFalse();
  void AnyDequeTrue();
  void AnyListFalse();
  void AnyListTrue();
  void AnyMapFalse();
  void AnyMapTrue();
  void AnyMultiSetFalse();
  void AnyMultiSetTrue();
  void AnySetFalse();
  void AnySetTrue();
  void AnyWhereFalse();
  void AnyWhereTrue();
};

class AnyFunctionalGTest : public ::testing::Test, public AnyFunctionalTest
{
protected:
  AnyFunctionalGTest()
  {
  }

  void SetUp() override
  {
  }

  void TearDown() override {}
};

#endif