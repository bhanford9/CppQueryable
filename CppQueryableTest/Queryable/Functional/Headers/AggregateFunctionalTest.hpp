#ifndef CPPQUERYABLETEST_QUERYABLE_FUNCTIONAL_HEADERS_AGGREGATEFUNCTIONALTEST_H
#define CPPQUERYABLETEST_QUERYABLE_FUNCTIONAL_HEADERS_AGGREGATEFUNCTIONALTEST_H

#include <gtest/gtest.h>

#include <exception>
#include <functional>
#include <iostream>
#include <string>

#include "../../../DataStructures/Gender.hpp"
#include "../../../DataStructures/Person.hpp"
#include "../../../DataStructures/PersonLibrary.hpp"

#include "../../../Queryable/QueryBuilder.hpp"

#include "DetachedTestFixture.hpp"

using namespace QueryBuilder;

class AggregateFunctionalTest : public DetachedTestFixture
{
protected:
  PersonLibrary personLibrary;
  QueryableVector<Person> people;

public:
  AggregateFunctionalTest() :
    people(BuildQueryable(this->personLibrary.GetPeople()))
  {
    this->tests.push_back(std::bind(&AggregateFunctionalTest::AggregateUninitializedTest, this));
    this->tests.push_back(std::bind(&AggregateFunctionalTest::AggregateSeededUninitialized, this));
    this->tests.push_back(std::bind(&AggregateFunctionalTest::AggregateFinalizerUninitialized, this));
    this->tests.push_back(std::bind(&AggregateFunctionalTest::AggregateFinalizerSeededUninitialized, this));
    this->tests.push_back(std::bind(&AggregateFunctionalTest::AggregateDeque, this));
    this->tests.push_back(std::bind(&AggregateFunctionalTest::AggregateList, this));
    this->tests.push_back(std::bind(&AggregateFunctionalTest::AggregateMap, this));
    this->tests.push_back(std::bind(&AggregateFunctionalTest::AggregateMultiSet, this));
    this->tests.push_back(std::bind(&AggregateFunctionalTest::AggregateSet, this));
    this->tests.push_back(std::bind(&AggregateFunctionalTest::AggregateVector, this));
    this->tests.push_back(std::bind(&AggregateFunctionalTest::AggregateSeededFinalizerDeque, this));
    this->tests.push_back(std::bind(&AggregateFunctionalTest::AggregateSeededFinalizerList, this));
    this->tests.push_back(std::bind(&AggregateFunctionalTest::AggregateSeededFinalizerMultiSet, this));
    this->tests.push_back(std::bind(&AggregateFunctionalTest::AggregateSeededFinalizerSet, this));
    this->tests.push_back(std::bind(&AggregateFunctionalTest::AggregateSeededFinalizerVector, this));
  }

  virtual std::string GetName() const
  {
    return "Aggregate";
  }

  void AggregateUninitializedTest() const;
  void AggregateSeededUninitialized() const;
  void AggregateFinalizerUninitialized() const;
  void AggregateFinalizerSeededUninitialized() const;
  void AggregateDeque() const;
  void AggregateList() const;
  void AggregateMap() const;
  void AggregateMultiSet() const;
  void AggregateSet() const;
  void AggregateVector() const;
  void AggregateSeededFinalizerDeque() const;
  void AggregateSeededFinalizerList() const;
  void AggregateSeededFinalizerMultiSet() const;
  void AggregateSeededFinalizerSet() const;
  void AggregateSeededFinalizerVector() const;
};

class AggregateFunctionalGTest : public ::testing::Test, public AggregateFunctionalTest
{
public:
  AggregateFunctionalGTest()
  {
  }

  void SetUp() override
  {
  }

  void TearDown() override {}
};

#endif