#include <cmath>
#include <iostream>
#include <string>

#include "../../../../DataStructures/Animal.hpp"
#include "../../../../DataStructures/Person.hpp"
#include "../../../../DataStructures/People.hpp"
#include "../../../../DataStructures/PersonLibrary.hpp"

#include "../../../../Queryable/InternalQueryable.hpp"

#include "../../../../Queryable/QueryBuilder.hpp"

#include "Utilities/TimeStats.hpp"
#include "Utilities/TimeTestParams/TimeTestCategory.hpp"
#include "Utilities/TimeTestParams/TimeTestParams.hpp"
#include "Utilities/TimingUtilities.hpp"

#include "TestSuites/AverageTimeTest.hpp"

using namespace QueryBuilder;

// TODO --> Average overload with custom divisor

void AverageTimeTest::DequeNumberTest(TimeTestParams & params)
{
  params.SetCategory(TimeTestCategory::Type::BuiltIn);

  std::vector<size_t> dataSample = { 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 };
  std::deque<size_t> data;
  for (size_t i = 0; i < params.GetContainerSize(); i++)
  {
    data.push_back(dataSample[i % 12]);
  }

  QueryableDeque<size_t> local = BuildQueryable(data);

  params.SetQueryableStats(RunTimeAndLog(
    [&]()
    { 
        local.Average([&](const size_t value)
        {
            this->ApplyLoad(params.GetLoad(), value);
            return static_cast<double>(value);
        });
    },
    params.GetIterations(),
    this->queryableName));

  double average = 0.0;
  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
        int i = 0;
        for (size_t value : data)
        {
            this->ApplyLoad(params.GetLoad(), value);
            average += value;
            ++i;
        }

        average /= i;
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseData(params);
}

void AverageTimeTest::ListNumberTest(TimeTestParams & params)
{
  params.SetCategory(TimeTestCategory::Type::BuiltIn);

  std::vector<size_t> dataSample = { 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 };
  std::list<size_t> data;
  for (size_t i = 0; i < params.GetContainerSize(); i++)
  {
    data.push_back(dataSample[i % 12]);
  }

  QueryableList<size_t> local = BuildQueryable(data);

  params.SetQueryableStats(RunTimeAndLog(
    [&]()
    { 
        local.Average([&](const size_t value)
        {
            this->ApplyLoad(params.GetLoad(), value);
            return static_cast<double>(value);
        });
    },
    params.GetIterations(),
    this->queryableName));

  double average = 0.0;
  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
        int i = 0;
        for (size_t value : data)
        {
            this->ApplyLoad(params.GetLoad(), value);
            average += value;
            ++i;
        }

        average /= i;
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseData(params);
}

void AverageTimeTest::MultiSetNumberTest(TimeTestParams & params)
{
  params.SetCategory(TimeTestCategory::Type::BuiltIn);

  std::vector<size_t> dataSample = { 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 };
  std::multiset<size_t> data;
  for (size_t i = 0; i < params.GetContainerSize(); i++)
  {
    data.insert(dataSample[i % 12]);
  }

  QueryableMultiSet<size_t> local = BuildQueryable(data);

  params.SetQueryableStats(RunTimeAndLog(
    [&]()
    { 
        local.Average([&](const size_t value)
        {
            this->ApplyLoad(params.GetLoad(), value);
            return static_cast<double>(value);
        });
    },
    params.GetIterations(),
    this->queryableName));

  double average = 0.0;
  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
        int i = 0;
        for (size_t value : data)
        {
            this->ApplyLoad(params.GetLoad(), value);
            average += value;
            ++i;
        }

        average /= i;
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseData(params);
}

void AverageTimeTest::SetNumberTest(TimeTestParams & params)
{
  params.SetCategory(TimeTestCategory::Type::BuiltIn);

  std::set<size_t> data;
  for (size_t i = 0; i < params.GetContainerSize(); i++)
  {
    data.insert(i);
  }

  QueryableSet<size_t> local = BuildQueryable(data);

  params.SetQueryableStats(RunTimeAndLog(
    [&]()
    { 
        local.Average([&](const size_t value)
        {
            this->ApplyLoad(params.GetLoad(), value);
            return static_cast<double>(value);
        });
    },
    params.GetIterations(),
    this->queryableName));

  double average = 0.0;
  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
        int i = 0;
        for (size_t value : data)
        {
            this->ApplyLoad(params.GetLoad(), value);
            average += value;
            ++i;
        }

        average /= i;
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseData(params);
}

void AverageTimeTest::VectorNumberTest(TimeTestParams & params)
{
  params.SetCategory(TimeTestCategory::Type::BuiltIn);

  std::vector<size_t> dataSample = { 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 };
  std::vector<size_t> data;
  for (size_t i = 0; i < params.GetContainerSize(); i++)
  {
    data.push_back(dataSample[i % 12]);
  }

  QueryableVector<size_t> local = BuildQueryable(data);

  params.SetQueryableStats(RunTimeAndLog(
    [&]()
    { 
        local.Average([&](const size_t value)
        {
            this->ApplyLoad(params.GetLoad(), value);
            return static_cast<double>(value);
        });
    },
    params.GetIterations(),
    this->queryableName));

  double average = 0.0;
  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
        int i = 0;
        for (size_t value : data)
        {
            this->ApplyLoad(params.GetLoad(), value);
            average += value;
            ++i;
        }

        average /= i;
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseData(params);
}

void AverageTimeTest::DequePersonTest(TimeTestParams & params)
{
  params.SetCategory(TimeTestCategory::Type::Class);

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
    [&]()
    { 
        local.Average([&](const Person & person)
        {
            this->ApplyLoad(params.GetLoad(), person);
            return person.GetAge();
        });
    },
    params.GetIterations(),
    this->queryableName));

  double average = 0.0;
  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
        int i = 0;
        for (const Person & person : data)
        {
            this->ApplyLoad(params.GetLoad(), person);
            average += person.GetAge();
            ++i;
        }

        average /= i;
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseData(params);
}

void AverageTimeTest::ListPersonTest(TimeTestParams & params)
{
  params.SetCategory(TimeTestCategory::Type::Class);

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
    [&]()
    { 
        local.Average([&](const Person & person)
        {
            this->ApplyLoad(params.GetLoad(), person);
            return person.GetAge();
        });
    },
    params.GetIterations(),
    this->queryableName));

  double average = 0.0;
  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
        int i = 0;
        for (const Person & person : data)
        {
            this->ApplyLoad(params.GetLoad(), person);
            average += person.GetAge();
            ++i;
        }

        average /= i;
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseData(params);
}

void AverageTimeTest::MultiSetPersonTest(TimeTestParams & params)
{
  params.SetCategory(TimeTestCategory::Type::Class);

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
    [&]()
    { 
        local.Average([&](const Person & person)
        {
            this->ApplyLoad(params.GetLoad(), person);
            return person.GetAge();
        });
    },
    params.GetIterations(),
    this->queryableName));

  double average = 0.0;
  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
        int i = 0;
        for (const Person & person : data)
        {
            this->ApplyLoad(params.GetLoad(), person);
            average += person.GetAge();
            ++i;
        }

        average /= i;
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseData(params);
}

void AverageTimeTest::SetPersonTest(TimeTestParams & params)
{
  params.SetCategory(TimeTestCategory::Type::Class);

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
    [&]()
    { 
        local.Average([&](const Person & person)
        {
            this->ApplyLoad(params.GetLoad(), person);
            return person.GetAge();
        });
    },
    params.GetIterations(),
    this->queryableName));

  double average = 0.0;
  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
        int i = 0;
        for (const Person & person : data)
        {
            this->ApplyLoad(params.GetLoad(), person);
            average += person.GetAge();
            ++i;
        }

        average /= i;
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseData(params);
}

void AverageTimeTest::VectorPersonTest(TimeTestParams & params)
{
  params.SetCategory(TimeTestCategory::Type::Class);

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
    [&]()
    { 
        local.Average([&](const Person & person)
        {
            this->ApplyLoad(params.GetLoad(), person);
            return person.GetAge();
        });
    },
    params.GetIterations(),
    this->queryableName));

  double average = 0.0;
  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
        int i = 0;
        for (const Person & person : data)
        {
            this->ApplyLoad(params.GetLoad(), person);
            average += person.GetAge();
            ++i;
        }

        average /= i;
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseData(params);
}
