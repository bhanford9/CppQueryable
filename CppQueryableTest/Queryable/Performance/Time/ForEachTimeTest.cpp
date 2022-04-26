#include <gtest/gtest.h>

#include <cmath>
#include <iostream>
#include <string>

#include "../../../../DataStructures/Animal.hpp"
#include "../../../../DataStructures/Person.hpp"
#include "../../../../DataStructures/People.hpp"
#include "../../../../DataStructures/PersonLibrary.hpp"

#include "../../../../Queryable/InternalQueryable.hpp"

#include "../../../../Queryable/QueryBuilder.hpp"

#include "BaseTimeTest.hpp"
#include "Utilities/TimeStats.hpp"
#include "Utilities/TimeTestParams/TimeTestCategory.hpp"
#include "Utilities/TimeTestParams/TimeTestParams.hpp"
#include "Utilities/TimingUtilities.hpp"

using namespace QueryBuilder;
using namespace TimingUtilities;

class ForEachTimeTest : public BaseTimeTest
{
protected:
  void SetUp() override
  {
    BaseTimeTest::SetUp();
    this->methodName = "ForEach";
  }
};

TEST_P(ForEachTimeTest, DequeNumberTest)
{
  this->params = GetParam();
  this->params.SetCategory(TimeTestCategory::BuiltIn);

  std::vector<uint> dataSample = { 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 };
  std::deque<uint> data;
  for (uint64_t i = 0; i < params.GetContainerSize(); i++)
  {
    data.push_back(dataSample[i % 12]);
  }

  QueryableDeque<uint> local = BuildQueryable2(data);

  this->queryableStats = RunTimeAndLog(
    [&]() { local.ForEach([&](uint value) { this->ApplyLoad(this->params.GetLoad(), value); }); },
    params.GetIterations(),
    this->queryableName
  );

  this->standardStats = RunTimeAndLog(
    [&]() { for (uint value : data) { this->ApplyLoad(this->params.GetLoad(), value); }},
    params.GetIterations(),
    this->standardName);

  this->LogBaseData();
}

TEST_P(ForEachTimeTest, ListNumberTest)
{
  this->params = GetParam();
  this->params.SetCategory(TimeTestCategory::BuiltIn);

  std::vector<uint> dataSample = { 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 };
  std::list<uint> data;
  for (uint64_t i = 0; i < params.GetContainerSize(); i++)
  {
    data.push_back(dataSample[i % 12]);
  }

  QueryableList<uint> local = BuildQueryable2(data);

  this->queryableStats = RunTimeAndLog(
    [&]() { local.ForEach([&](uint value) { this->ApplyLoad(this->params.GetLoad(), value); }); },
    params.GetIterations(),
    this->queryableName
  );

  this->standardStats = RunTimeAndLog(
    [&]() { for (uint value : data) { this->ApplyLoad(this->params.GetLoad(), value); }},
    params.GetIterations(),
    this->standardName);

  this->LogBaseData();
}

TEST_P(ForEachTimeTest, MultiSetNumberTest)
{
  this->params = GetParam();
  this->params.SetCategory(TimeTestCategory::BuiltIn);

  std::vector<uint> dataSample = { 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 };
  std::multiset<uint> data;
  for (uint64_t i = 0; i < params.GetContainerSize(); i++)
  {
    data.insert(dataSample[i % 12]);
  }

  QueryableMultiSet<uint> local = BuildQueryable2(data);

  this->queryableStats = RunTimeAndLog(
    [&]() { local.ForEach([&](uint value) { this->ApplyLoad(this->params.GetLoad(), value); }); },
    params.GetIterations(),
    this->queryableName
  );

  this->standardStats = RunTimeAndLog(
    [&]() { for (uint value : data) { this->ApplyLoad(this->params.GetLoad(), value); }},
    params.GetIterations(),
    this->standardName);

  this->LogBaseData();
}

TEST_P(ForEachTimeTest, SetNumberTest)
{
  this->params = GetParam();
  this->params.SetCategory(TimeTestCategory::BuiltIn);

  std::set<uint> data;
  for (uint64_t i = 0; i < params.GetContainerSize(); i++)
  {
    data.insert(i);
  }

  QueryableSet<uint> local = BuildQueryable2(data);

  this->queryableStats = RunTimeAndLog(
    [&]() { local.ForEach([&](uint value) { this->ApplyLoad(this->params.GetLoad(), value); }); },
    params.GetIterations(),
    this->queryableName
  );

  this->standardStats = RunTimeAndLog(
    [&]() { for (uint value : data) { this->ApplyLoad(this->params.GetLoad(), value); }},
    params.GetIterations(),
    this->standardName);

  this->LogBaseData();
}

TEST_P(ForEachTimeTest, VectorNumberTest)
{
  this->params = GetParam();
  this->params.SetCategory(TimeTestCategory::BuiltIn);

  std::vector<uint> dataSample = { 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 };
  std::vector<uint> data;
  for (uint64_t i = 0; i < params.GetContainerSize(); i++)
  {
    data.push_back(dataSample[i % 12]);
  }

  QueryableVector<uint> local = BuildQueryable2(data);

  this->queryableStats = RunTimeAndLog(
    [&]() { local.ForEach([&](uint value) { this->ApplyLoad(this->params.GetLoad(), value); }); },
    params.GetIterations(),
    this->queryableName
  );

  this->standardStats = RunTimeAndLog(
    [&]() { for (uint value : data) { this->ApplyLoad(this->params.GetLoad(), value); }},
    params.GetIterations(),
    this->standardName);

  this->LogBaseData();
}

TEST_P(ForEachTimeTest, DequePersonTest)
{
  this->params = GetParam();
  this->params.SetCategory(TimeTestCategory::Class);

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
  for (uint64_t i = 0; i < params.GetContainerSize(); i++)
  {
    data.push_back(dataSample[i % 6]);
  }

  QueryableDeque<Person> local = BuildQueryable2(data);

  this->queryableStats = RunTimeAndLog(
    [&]() { local.ForEach([&](Person value) { this->ApplyLoad<Person>(this->params.GetLoad(), value); }); },
    params.GetIterations(),
    this->queryableName
  );

  this->standardStats = RunTimeAndLog(
    [&]() { for (Person value : data) { this->ApplyLoad<Person>(this->params.GetLoad(), value); }},
    params.GetIterations(),
    this->standardName);

  this->LogBaseData();
}

TEST_P(ForEachTimeTest, ListPersonTest)
{
  this->params = GetParam();
  this->params.SetCategory(TimeTestCategory::Class);

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
  for (uint64_t i = 0; i < params.GetContainerSize(); i++)
  {
    data.push_back(dataSample[i % 6]);
  }

  QueryableList<Person> local = BuildQueryable2(data);

  this->queryableStats = RunTimeAndLog(
    [&]() { local.ForEach([&](Person value) { this->ApplyLoad<Person>(this->params.GetLoad(), value); }); },
    params.GetIterations(),
    this->queryableName
  );

  this->standardStats = RunTimeAndLog(
    [&]() { for (Person value : data) { this->ApplyLoad<Person>(this->params.GetLoad(), value); }},
    params.GetIterations(),
    this->standardName);

  this->LogBaseData();
}

TEST_P(ForEachTimeTest, MultiSetPersonTest)
{
  this->params = GetParam();
  this->params.SetCategory(TimeTestCategory::Class);

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
  for (uint64_t i = 0; i < params.GetContainerSize(); i++)
  {
    data.insert(dataSample[i % 6]);
  }

  QueryableMultiSet<Person> local = BuildQueryable2(data);

  this->queryableStats = RunTimeAndLog(
    [&]() { local.ForEach([&](Person value) { this->ApplyLoad<Person>(this->params.GetLoad(), value); }); },
    params.GetIterations(),
    this->queryableName
  );

  this->standardStats = RunTimeAndLog(
    [&]() { for (Person value : data) { this->ApplyLoad<Person>(this->params.GetLoad(), value); }},
    params.GetIterations(),
    this->standardName);

  this->LogBaseData();
}

TEST_P(ForEachTimeTest, SetPersonTest)
{
  this->params = GetParam();
  this->params.SetCategory(TimeTestCategory::Class);

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
  for (uint64_t i = 0; i < params.GetContainerSize(); i++)
  {
    data.insert(dataSample[i % 6]);
  }

  QueryableSet<Person> local = BuildQueryable2(data);

  this->queryableStats = RunTimeAndLog(
    [&]() { local.ForEach([&](Person value) { this->ApplyLoad<Person>(this->params.GetLoad(), value); }); },
    params.GetIterations(),
    this->queryableName
  );

  this->standardStats = RunTimeAndLog(
    [&]() { for (Person value : data) { this->ApplyLoad<Person>(this->params.GetLoad(), value); }},
    params.GetIterations(),
    this->standardName);

  this->LogBaseData();
}

TEST_P(ForEachTimeTest, VectorPersonTest)
{
  this->params = GetParam();
  this->params.SetCategory(TimeTestCategory::Class);

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
  for (uint64_t i = 0; i < params.GetContainerSize(); i++)
  {
    data.push_back(dataSample[i % 6]);
  }

  QueryableVector<Person> local = BuildQueryable2(data);

  this->queryableStats = RunTimeAndLog(
    [&]() { local.ForEach([&](Person value) { this->ApplyLoad<Person>(this->params.GetLoad(), value); }); },
    params.GetIterations(),
    this->queryableName
  );

  this->standardStats = RunTimeAndLog(
    [&]() { for (Person value : data) { this->ApplyLoad<Person>(this->params.GetLoad(), value); }},
    params.GetIterations(),
    this->standardName);

  this->LogBaseData();
}

INSTANTIATE_TEST_SUITE_P(
  ForEachTimeTesting,
  ForEachTimeTest,
  ::testing::Values(
    TimeTestParams(30, 10, 1),
    TimeTestParams(30, 10, 10),
    TimeTestParams(30, 10, 50),
    TimeTestParams(30, 10, 100),
    TimeTestParams(30, 30, 1),
    TimeTestParams(30, 30, 10),
    TimeTestParams(30, 30, 50),
    TimeTestParams(30, 30, 100),
    TimeTestParams(30, 1000, 1),
    TimeTestParams(30, 1000, 10),
    TimeTestParams(30, 1000, 50),
    TimeTestParams(30, 1000, 100),
    TimeTestParams(30, 10000, 1),
    TimeTestParams(30, 10000, 10),
    TimeTestParams(30, 10000, 50),
    TimeTestParams(30, 10000, 100)));
