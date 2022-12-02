#include <iostream>
#include <sstream>
#include <string>

#include "../../../../DataStructures/Animal.hpp"
#include "../../../../DataStructures/Person.hpp"
#include "../../../../DataStructures/People.hpp"
#include "../../../../DataStructures/PersonLibrary.hpp"

#include "../../../../Queryable/InternalQueryable.hpp"

#include "../../../../Queryable/QueryBuilder.hpp"

#include "BaseTimeTest.hpp"
#include "Utilities/TimeStats.hpp"
#include "Utilities/TimeTestParams/TimeTestParams.hpp"
#include "Utilities/TimeTestParams/TriggerType.hpp"
#include "Utilities/TimingUtilities.hpp"

#include "TestSuites/AtTimeTest.hpp"

using namespace QueryBuilder;

void AtTimeTest::DequeNumberTest(TimeTestParams & params)
{
  params.SetCategory(TimeTestCategory::Type::BuiltIn);
  this->Init(params);

  std::vector<size_t> dataSample = { 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 };
  std::deque<size_t> data;
  for (size_t i = 0; i < params.GetContainerSize(); i++)
  {
    data.push_back(dataSample[i % 12]);
  }

  QueryableDeque<size_t> local = BuildQueryable(data);

  params.SetQueryableStats(RunTimeAndLog(
    [&]() { auto value = local.At(this->triggerIndex); },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
        auto iterator = data.begin();
        std::advance(iterator, this->triggerIndex);
        auto value = *iterator;
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseWithTriggerData(params);
}

void AtTimeTest::ListNumberTest(TimeTestParams & params)
{
  params.SetCategory(TimeTestCategory::Type::BuiltIn);
  this->Init(params);

  std::vector<size_t> dataSample = { 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 };
  std::list<size_t> data;
  for (size_t i = 0; i < params.GetContainerSize(); i++)
  {
    data.push_back(dataSample[i % 12]);
  }

  QueryableList<size_t> local = BuildQueryable(data);

  params.SetQueryableStats(RunTimeAndLog(
    [&]() { auto value = local.At(this->triggerIndex); },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
        auto iterator = data.begin();
        std::advance(iterator, this->triggerIndex);
        auto value = *iterator;
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseWithTriggerData(params);
}

void AtTimeTest::MultiSetNumberTest(TimeTestParams & params)
{
  params.SetCategory(TimeTestCategory::Type::BuiltIn);
  this->Init(params);

  std::vector<size_t> dataSample = { 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 };
  std::multiset<size_t> data;
  for (size_t i = 0; i < params.GetContainerSize(); i++)
  {
    data.insert(dataSample[i % 12]);
  }

  QueryableMultiSet<size_t> local = BuildQueryable(data);

  params.SetQueryableStats(RunTimeAndLog(
    [&]() { auto value = local.At(this->triggerIndex); },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
        auto iterator = data.begin();
        std::advance(iterator, this->triggerIndex);
        auto value = *iterator;
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseWithTriggerData(params);
}

void AtTimeTest::SetNumberTest(TimeTestParams & params)
{
  params.SetCategory(TimeTestCategory::Type::BuiltIn);
  this->Init(params);

  std::vector<size_t> dataSample = { 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 };
  std::set<size_t> data;
  for (size_t i = 0; i < params.GetContainerSize(); i++)
  {
    data.insert(dataSample[i % 12]);
  }

  QueryableSet<size_t> local = BuildQueryable(data);

  params.SetQueryableStats(RunTimeAndLog(
    [&]() { auto value = local.At(this->triggerIndex); },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
        auto iterator = data.begin();
        std::advance(iterator, this->triggerIndex);
        auto value = *iterator;
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseWithTriggerData(params);
}

void AtTimeTest::VectorNumberTest(TimeTestParams & params)
{
  params.SetCategory(TimeTestCategory::Type::BuiltIn);
  this->Init(params);

  std::vector<size_t> dataSample = { 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 };
  std::vector<size_t> data;
  for (size_t i = 0; i < params.GetContainerSize(); i++)
  {
    data.push_back(dataSample[i % 12]);
  }

  QueryableVector<size_t> local = BuildQueryable(data);

  params.SetQueryableStats(RunTimeAndLog(
    [&]() { auto value = local.At(this->triggerIndex); },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
        auto iterator = data.begin();
        std::advance(iterator, this->triggerIndex);
        auto value = *iterator;
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseWithTriggerData(params);
}

void AtTimeTest::DequePersonTest(TimeTestParams & params)
{
  params.SetCategory(TimeTestCategory::Type::Class);
  this->Init(params);

  std::vector<Person> dataSample =
  {
    Person(0, "Person 4", 0, 0, Gender::Male),
    Person(0, "Person 5", 0, 0, Gender::Male),
    Person(0, "Person 6", 0, 0, Gender::Male),
    Person(0, "Person 7", 0, 0, Gender::Male),
    Person(0, "Person 8", 0, 0, Gender::Male),
    Person(0, "Person 9", 0, 0, Gender::Male),
  };

  std::deque<Person> data;
  for (size_t i = 0; i < params.GetContainerSize(); i++)
  {
    data.push_back(dataSample[i % 6]);
  }

  QueryableDeque<Person> local = BuildQueryable(data);

  params.SetQueryableStats(RunTimeAndLog(
    [&]() { auto value = local.At(this->triggerIndex); },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
        auto iterator = data.begin();
        std::advance(iterator, this->triggerIndex);
        auto value = *iterator;
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseWithTriggerData(params);
}

void AtTimeTest::ListPersonTest(TimeTestParams & params)
{
  params.SetCategory(TimeTestCategory::Type::Class);
  this->Init(params);

  std::vector<Person> dataSample =
  {
    Person(0, "Person 4", 0, 0, Gender::Male),
    Person(0, "Person 5", 0, 0, Gender::Male),
    Person(0, "Person 6", 0, 0, Gender::Male),
    Person(0, "Person 7", 0, 0, Gender::Male),
    Person(0, "Person 8", 0, 0, Gender::Male),
    Person(0, "Person 9", 0, 0, Gender::Male),
  };

  std::list<Person> data;
  for (size_t i = 0; i < params.GetContainerSize(); i++)
  {
    data.push_back(dataSample[i % 6]);
  }

  QueryableList<Person> local = BuildQueryable(data);

  params.SetQueryableStats(RunTimeAndLog(
    [&]() { auto value = local.At(this->triggerIndex); },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
        auto iterator = data.begin();
        std::advance(iterator, this->triggerIndex);
        auto value = *iterator;
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseWithTriggerData(params);
}

void AtTimeTest::MultiSetPersonTest(TimeTestParams & params)
{
  params.SetCategory(TimeTestCategory::Type::Class);
  this->Init(params);

  std::vector<Person> dataSample =
  {
    Person(0, "Person 4", 0, 0, Gender::Male),
    Person(0, "Person 5", 0, 0, Gender::Male),
    Person(0, "Person 6", 0, 0, Gender::Male),
    Person(0, "Person 7", 0, 0, Gender::Male),
    Person(0, "Person 8", 0, 0, Gender::Male),
    Person(0, "Person 9", 0, 0, Gender::Male),
  };

  std::multiset<Person> data;
  for (size_t i = 0; i < params.GetContainerSize(); i++)
  {
    data.insert(dataSample[i % 6]);
  }

  QueryableMultiSet<Person> local = BuildQueryable(data);

  params.SetQueryableStats(RunTimeAndLog(
    [&]() { auto value = local.At(this->triggerIndex); },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
        auto iterator = data.begin();
        std::advance(iterator, this->triggerIndex);
        auto value = *iterator;
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseWithTriggerData(params);
}

void AtTimeTest::SetPersonTest(TimeTestParams & params)
{
  params.SetCategory(TimeTestCategory::Type::Class);
  this->Init(params);

  std::vector<Person> dataSample =
  {
    Person(0, "Person 4", 0, 0, Gender::Male),
    Person(0, "Person 5", 0, 0, Gender::Male),
    Person(0, "Person 6", 0, 0, Gender::Male),
    Person(0, "Person 7", 0, 0, Gender::Male),
    Person(0, "Person 8", 0, 0, Gender::Male),
    Person(0, "Person 9", 0, 0, Gender::Male),
  };

  std::set<Person> data;
  for (size_t i = 0; i < params.GetContainerSize(); i++)
  {
    data.insert(dataSample[i % 6]);
  }

  QueryableSet<Person> local = BuildQueryable(data);

  params.SetQueryableStats(RunTimeAndLog(
    [&]() { auto value = local.At(this->triggerIndex); },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
        auto iterator = data.begin();
        std::advance(iterator, this->triggerIndex);
        auto value = *iterator;
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseWithTriggerData(params);
}

void AtTimeTest::VectorPersonTest(TimeTestParams & params)
{
  params.SetCategory(TimeTestCategory::Type::Class);
  this->Init(params);

  std::vector<Person> dataSample =
  {
    Person(0, "Person 4", 0, 0, Gender::Male),
    Person(0, "Person 5", 0, 0, Gender::Male),
    Person(0, "Person 6", 0, 0, Gender::Male),
    Person(0, "Person 7", 0, 0, Gender::Male),
    Person(0, "Person 8", 0, 0, Gender::Male),
    Person(0, "Person 9", 0, 0, Gender::Male),
  };

  std::vector<Person> data;
  for (size_t i = 0; i < params.GetContainerSize(); i++)
  {
    data.push_back(dataSample[i % 6]);
  }

  QueryableVector<Person> local = BuildQueryable(data);

  params.SetQueryableStats(RunTimeAndLog(
    [&]() { auto value = local.At(this->triggerIndex); },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
        auto iterator = data.begin();
        std::advance(iterator, this->triggerIndex);
        auto value = *iterator;
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseWithTriggerData(params);
}


