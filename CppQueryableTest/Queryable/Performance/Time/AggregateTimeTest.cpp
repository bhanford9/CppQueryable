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

#include "TestSuites/AggregateTimeTest.hpp"

using namespace QueryBuilder;

void AggregateTimeTest::DequeNumberSimpleTest(TimeTestParams & params)
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
        size_t max = local.Aggregate([&](const size_t & accumulation, const size_t & value)
        {
            this->ApplyLoad(params.GetLoad(), value);
            return accumulation > value ? accumulation : value;
        });
    },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
        size_t max = 0;

        for (size_t value : data)
        {
            this->ApplyLoad(params.GetLoad(), value);
            max = value > max ? value : max;
        }
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseData(params);
}

void AggregateTimeTest::ListNumberSimpleTest(TimeTestParams & params)
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
        size_t max = local.Aggregate([&](const size_t & accumulation, const size_t & value)
        {
            this->ApplyLoad(params.GetLoad(), value);
            return accumulation > value ? accumulation : value;
        });
    },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
        size_t max = 0;

        for (size_t value : data)
        {
            this->ApplyLoad(params.GetLoad(), value);
            max = value > max ? value : max;
        }
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseData(params);
}

void AggregateTimeTest::MultiSetNumberSimpleTest(TimeTestParams & params)
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
        size_t max = local.Aggregate([&](const size_t & accumulation, const size_t & value)
        {
            this->ApplyLoad(params.GetLoad(), value);
            return accumulation > value ? accumulation : value;
        });
    },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
        size_t max = 0;

        for (size_t value : data)
        {
            this->ApplyLoad(params.GetLoad(), value);
            max = value > max ? value : max;
        }
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseData(params);
}

void AggregateTimeTest::SetNumberSimpleTest(TimeTestParams & params)
{
  params.SetCategory(TimeTestCategory::Type::BuiltIn);

  std::vector<size_t> dataSample = { 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 };
  std::set<size_t> data;
  for (size_t i = 0; i < params.GetContainerSize(); i++)
  {
    data.insert(dataSample[i % 12]);
  }

  QueryableSet<size_t> local = BuildQueryable(data);

  params.SetQueryableStats(RunTimeAndLog(
    [&]()
    {
        size_t max = local.Aggregate([&](const size_t & accumulation, const size_t & value)
        {
            this->ApplyLoad(params.GetLoad(), value);
            return accumulation > value ? accumulation : value;
        });
    },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
        size_t max = 0;

        for (size_t value : data)
        {
            this->ApplyLoad(params.GetLoad(), value);
            max = value > max ? value : max;
        }
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseData(params);
}

void AggregateTimeTest::VectorNumberSimpleTest(TimeTestParams & params)
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
        size_t max = local.Aggregate([&](const size_t & accumulation, const size_t & value)
        {
            this->ApplyLoad(params.GetLoad(), value);
            return accumulation > value ? accumulation : value;
        });
    },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
        size_t max = 0;

        for (size_t value : data)
        {
            this->ApplyLoad(params.GetLoad(), value);
            max = value > max ? value : max;
        }
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseData(params);
}

void AggregateTimeTest::DequePersonSimpleTest(TimeTestParams & params)
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
        Person max = local.Aggregate([&](const Person & accumulation, const Person & value)
        {
            this->ApplyLoad(params.GetLoad(), value);
            return accumulation.GetAge() > value.GetAge() ? accumulation : value;
        });
    },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
        Person max;

        for (const Person & value : data)
        {
            this->ApplyLoad(params.GetLoad(), value);
            max = value.GetAge() > max.GetAge() ? value : max;
        }
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseData(params);
}

void AggregateTimeTest::ListPersonSimpleTest(TimeTestParams & params)
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
        Person max = local.Aggregate([&](const Person & accumulation, const Person & value)
        {
            this->ApplyLoad(params.GetLoad(), value);
            return accumulation.GetAge() > value.GetAge() ? accumulation : value;
        });
    },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
        Person max;

        for (const Person & value : data)
        {
            this->ApplyLoad(params.GetLoad(), value);
            max = value.GetAge() > max.GetAge() ? value : max;
        }
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseData(params);
}

void AggregateTimeTest::MultiSetPersonSimpleTest(TimeTestParams & params)
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
        Person max = local.Aggregate([&](const Person & accumulation, const Person & value)
        {
            this->ApplyLoad(params.GetLoad(), value);
            return accumulation.GetAge() > value.GetAge() ? accumulation : value;
        });
    },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
        Person max;

        for (const Person & value : data)
        {
            this->ApplyLoad(params.GetLoad(), value);
            max = value.GetAge() > max.GetAge() ? value : max;
        }
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseData(params);
}

void AggregateTimeTest::SetPersonSimpleTest(TimeTestParams & params)
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
        Person max = local.Aggregate([&](const Person & accumulation, const Person & value)
        {
            this->ApplyLoad(params.GetLoad(), value);
            return accumulation.GetAge() > value.GetAge() ? accumulation : value;
        });
    },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
        Person max;

        for (const Person & value : data)
        {
            this->ApplyLoad(params.GetLoad(), value);
            max = value.GetAge() > max.GetAge() ? value : max;
        }
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseData(params);
}

void AggregateTimeTest::VectorPersonSimpleTest(TimeTestParams & params)
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
        Person max = local.Aggregate([&](const Person & accumulation, const Person & value)
        {
            this->ApplyLoad(params.GetLoad(), value);
            return accumulation.GetAge() > value.GetAge() ? accumulation : value;
        });
    },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
        Person max;

        for (const Person & value : data)
        {
            this->ApplyLoad(params.GetLoad(), value);
            max = value.GetAge() > max.GetAge() ? value : max;
        }
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseData(params);
}


void AggregateTimeTest::DequeNumberSeededTest(TimeTestParams & params)
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
        double max = local.Aggregate<double>(
            12.5,
            [&](const double & accumulation, const size_t & value)
            {
                this->ApplyLoad(params.GetLoad(), value);
                return accumulation > static_cast<double>(value) ? accumulation : static_cast<double>(value);
            });
    },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
        double max = 12.5;

        for (size_t value : data)
        {
            this->ApplyLoad(params.GetLoad(), value);
            max = static_cast<double>(value) > max ? static_cast<double>(value) : max;
        }
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseData(params);
}

void AggregateTimeTest::ListNumberSeededTest(TimeTestParams & params)
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
        double max = local.Aggregate<double>(
            12.5,
            [&](const double & accumulation, const size_t & value)
            {
                this->ApplyLoad(params.GetLoad(), value);
                return accumulation > static_cast<double>(value) ? accumulation : static_cast<double>(value);
            });
    },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
        double max = 12.5;

        for (size_t value : data)
        {
            this->ApplyLoad(params.GetLoad(), value);
            max = static_cast<double>(value) > max ? static_cast<double>(value) : max;
        }
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseData(params);
}

void AggregateTimeTest::MultiSetNumberSeededTest(TimeTestParams & params)
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
        double max = local.Aggregate<double>(
            12.5,
            [&](const double & accumulation, const size_t & value)
            {
                this->ApplyLoad(params.GetLoad(), value);
                return accumulation > static_cast<double>(value) ? accumulation : static_cast<double>(value);
            });
    },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
        double max = 12.5;

        for (size_t value : data)
        {
            this->ApplyLoad(params.GetLoad(), value);
            max = static_cast<double>(value) > max ? static_cast<double>(value) : max;
        }
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseData(params);
}

void AggregateTimeTest::SetNumberSeededTest(TimeTestParams & params)
{
  params.SetCategory(TimeTestCategory::Type::BuiltIn);

  std::vector<size_t> dataSample = { 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 };
  std::set<size_t> data;
  for (size_t i = 0; i < params.GetContainerSize(); i++)
  {
    data.insert(dataSample[i % 12]);
  }

  QueryableSet<size_t> local = BuildQueryable(data);

  params.SetQueryableStats(RunTimeAndLog(
    [&]()
    {
        double max = local.Aggregate<double>(
            12.5,
            [&](const double & accumulation, const size_t & value)
            {
                this->ApplyLoad(params.GetLoad(), value);
                return accumulation > static_cast<double>(value) ? accumulation : static_cast<double>(value);
            });
    },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
        double max = 12.5;

        for (size_t value : data)
        {
            this->ApplyLoad(params.GetLoad(), value);
            max = static_cast<double>(value) > max ? static_cast<double>(value) : max;
        }
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseData(params);
}

void AggregateTimeTest::VectorNumberSeededTest(TimeTestParams & params)
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
        double max = local.Aggregate<double>(
            12.5,
            [&](const double & accumulation, const size_t & value)
            {
                this->ApplyLoad(params.GetLoad(), value);
                return accumulation > static_cast<double>(value) ? accumulation : static_cast<double>(value);
            });
    },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
        double max = 12.5;

        for (size_t value : data)
        {
            this->ApplyLoad(params.GetLoad(), value);
            max = static_cast<double>(value) > max ? static_cast<double>(value) : max;
        }
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseData(params);
}

void AggregateTimeTest::DequePersonSeededTest(TimeTestParams & params)
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
        std::string peopleString = local.Aggregate<std::string>(
            "People: \n",
            [&](const std::string & accumulation, const Person & value)
            {
                this->ApplyLoad(params.GetLoad(), value);
                return accumulation + value.ToString();
            });
    },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
        std::string peopleString = "People: \n";

        for (const Person & value : data)
        {
            this->ApplyLoad(params.GetLoad(), value);
            peopleString += value.ToString();
        }
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseData(params);
}

void AggregateTimeTest::ListPersonSeededTest(TimeTestParams & params)
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
        std::string peopleString = local.Aggregate<std::string>(
            "People: \n",
            [&](const std::string & accumulation, const Person & value)
            {
                this->ApplyLoad(params.GetLoad(), value);
                return accumulation + value.ToString();
            });
    },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
        std::string peopleString = "People: \n";

        for (const Person & value : data)
        {
            this->ApplyLoad(params.GetLoad(), value);
            peopleString += value.ToString();
        }
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseData(params);
}

void AggregateTimeTest::MultiSetPersonSeededTest(TimeTestParams & params)
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
        std::string peopleString = local.Aggregate<std::string>(
            "People: \n",
            [&](const std::string & accumulation, const Person & value)
            {
                this->ApplyLoad(params.GetLoad(), value);
                return accumulation + value.ToString();
            });
    },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
        std::string peopleString = "People: \n";

        for (const Person & value : data)
        {
            this->ApplyLoad(params.GetLoad(), value);
            peopleString += value.ToString();
        }
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseData(params);
}

void AggregateTimeTest::SetPersonSeededTest(TimeTestParams & params)
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
        std::string peopleString = local.Aggregate<std::string>(
            "People: \n",
            [&](const std::string & accumulation, const Person & value)
            {
                this->ApplyLoad(params.GetLoad(), value);
                return accumulation + value.ToString();
            });
    },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
        std::string peopleString = "People: \n";

        for (const Person & value : data)
        {
            this->ApplyLoad(params.GetLoad(), value);
            peopleString += value.ToString();
        }
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseData(params);
}

void AggregateTimeTest::VectorPersonSeededTest(TimeTestParams & params)
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
        std::string peopleString = local.Aggregate<std::string>(
            "People: \n",
            [&](const std::string & accumulation, const Person & value)
            {
                this->ApplyLoad(params.GetLoad(), value);
                return accumulation + value.ToString();
            });
    },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
        std::string peopleString = "People: \n";

        for (const Person & value : data)
        {
            this->ApplyLoad(params.GetLoad(), value);
            peopleString += value.ToString();
        }
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseData(params);
}


void AggregateTimeTest::DequeNumberFinalizerTest(TimeTestParams & params)
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
        std::string max = local.Aggregate<std::string, double>(
            12.5,
            [&](const double & accumulation, const size_t & value)
            {
                this->ApplyLoad(params.GetLoad(), value);
                return accumulation > static_cast<double>(value) ? accumulation : static_cast<double>(value);
            },
            [](const double & accumulation) { return std::to_string(accumulation); });
    },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
        double max = 12.5;
        std::string maxStr = "";

        for (size_t value : data)
        {
            this->ApplyLoad(params.GetLoad(), value);
            max = static_cast<double>(value) > max ? static_cast<double>(value) : max;
        }

        maxStr = std::to_string(max);
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseData(params);
}

void AggregateTimeTest::ListNumberFinalizerTest(TimeTestParams & params)
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
        std::string max = local.Aggregate<std::string, double>(
            12.5,
            [&](const double & accumulation, const size_t & value)
            {
                this->ApplyLoad(params.GetLoad(), value);
                return accumulation > static_cast<double>(value) ? accumulation : static_cast<double>(value);
            },
            [](const double & accumulation) { return std::to_string(accumulation); });
    },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
        double max = 12.5;
        std::string maxStr = "";

        for (size_t value : data)
        {
            this->ApplyLoad(params.GetLoad(), value);
            max = static_cast<double>(value) > max ? static_cast<double>(value) : max;
        }

        maxStr = std::to_string(max);
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseData(params);
}

void AggregateTimeTest::MultiSetNumberFinalizerTest(TimeTestParams & params)
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
        std::string max = local.Aggregate<std::string, double>(
            12.5,
            [&](const double & accumulation, const size_t & value)
            {
                this->ApplyLoad(params.GetLoad(), value);
                return accumulation > static_cast<double>(value) ? accumulation : static_cast<double>(value);
            },
            [](const double & accumulation) { return std::to_string(accumulation); });
    },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
        double max = 12.5;
        std::string maxStr = "";

        for (size_t value : data)
        {
            this->ApplyLoad(params.GetLoad(), value);
            max = static_cast<double>(value) > max ? static_cast<double>(value) : max;
        }

        maxStr = std::to_string(max);
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseData(params);
}

void AggregateTimeTest::SetNumberFinalizerTest(TimeTestParams & params)
{
  params.SetCategory(TimeTestCategory::Type::BuiltIn);

  std::vector<size_t> dataSample = { 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 };
  std::set<size_t> data;
  for (size_t i = 0; i < params.GetContainerSize(); i++)
  {
    data.insert(dataSample[i % 12]);
  }

  QueryableSet<size_t> local = BuildQueryable(data);

  params.SetQueryableStats(RunTimeAndLog(
    [&]()
    {
        std::string max = local.Aggregate<std::string, double>(
            12.5,
            [&](const double & accumulation, const size_t & value)
            {
                this->ApplyLoad(params.GetLoad(), value);
                return accumulation > static_cast<double>(value) ? accumulation : static_cast<double>(value);
            },
            [](const double & accumulation) { return std::to_string(accumulation); });
    },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
        double max = 12.5;
        std::string maxStr = "";

        for (size_t value : data)
        {
            this->ApplyLoad(params.GetLoad(), value);
            max = static_cast<double>(value) > max ? static_cast<double>(value) : max;
        }

        maxStr = std::to_string(max);
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseData(params);
}

void AggregateTimeTest::VectorNumberFinalizerTest(TimeTestParams & params)
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
        std::string max = local.Aggregate<std::string, double>(
            12.5,
            [&](const double & accumulation, const size_t & value)
            {
                this->ApplyLoad(params.GetLoad(), value);
                return accumulation > static_cast<double>(value) ? accumulation : static_cast<double>(value);
            },
            [](const double & accumulation) { return std::to_string(accumulation); });
    },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
        double max = 12.5;
        std::string maxStr = "";

        for (size_t value : data)
        {
            this->ApplyLoad(params.GetLoad(), value);
            max = static_cast<double>(value) > max ? static_cast<double>(value) : max;
        }

        maxStr = std::to_string(max);
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseData(params);
}

void AggregateTimeTest::DequePersonFinalizerTest(TimeTestParams & params)
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
        std::string peopleString = local.Aggregate<std::string, std::string>(
            "People: \n",
            [&](const std::string & accumulation, const Person & value)
            {
                this->ApplyLoad(params.GetLoad(), value);
                return accumulation + value.ToString();
            },
            [](const std::string & accumulation) { return accumulation + "\n\n"; });
    },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
        std::string peopleString = "People: \n";

        for (const Person & value : data)
        {
            this->ApplyLoad(params.GetLoad(), value);
            peopleString += value.ToString();
        }

        peopleString += "\n\n";
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseData(params);
}

void AggregateTimeTest::ListPersonFinalizerTest(TimeTestParams & params)
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
        std::string peopleString = local.Aggregate<std::string, std::string>(
            "People: \n",
            [&](const std::string & accumulation, const Person & value)
            {
                this->ApplyLoad(params.GetLoad(), value);
                return accumulation + value.ToString();
            },
            [](const std::string & accumulation) { return accumulation + "\n\n"; });
    },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
        std::string peopleString = "People: \n";

        for (const Person & value : data)
        {
            this->ApplyLoad(params.GetLoad(), value);
            peopleString += value.ToString();
        }

        peopleString += "\n\n";
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseData(params);
}

void AggregateTimeTest::MultiSetPersonFinalizerTest(TimeTestParams & params)
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
        std::string peopleString = local.Aggregate<std::string, std::string>(
            "People: \n",
            [&](const std::string & accumulation, const Person & value)
            {
                this->ApplyLoad(params.GetLoad(), value);
                return accumulation + value.ToString();
            },
            [](const std::string & accumulation) { return accumulation + "\n\n"; });
    },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
        std::string peopleString = "People: \n";

        for (const Person & value : data)
        {
            this->ApplyLoad(params.GetLoad(), value);
            peopleString += value.ToString();
        }

        peopleString += "\n\n";
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseData(params);
}

void AggregateTimeTest::SetPersonFinalizerTest(TimeTestParams & params)
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
        std::string peopleString = local.Aggregate<std::string, std::string>(
            "People: \n",
            [&](const std::string & accumulation, const Person & value)
            {
                this->ApplyLoad(params.GetLoad(), value);
                return accumulation + value.ToString();
            },
            [](const std::string & accumulation) { return accumulation + "\n\n"; });
    },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
        std::string peopleString = "People: \n";

        for (const Person & value : data)
        {
            this->ApplyLoad(params.GetLoad(), value);
            peopleString += value.ToString();
        }

        peopleString += "\n\n";
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseData(params);
}

void AggregateTimeTest::VectorPersonFinalizerTest(TimeTestParams & params)
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
        std::string peopleString = local.Aggregate<std::string, std::string>(
            "People: \n",
            [&](const std::string & accumulation, const Person & value)
            {
                this->ApplyLoad(params.GetLoad(), value);
                return accumulation + value.ToString();
            },
            [](const std::string & accumulation) { return accumulation + "\n\n"; });
    },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
        std::string peopleString = "People: \n";

        for (const Person & value : data)
        {
            this->ApplyLoad(params.GetLoad(), value);
            peopleString += value.ToString();
        }

        peopleString += "\n\n";
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseData(params);
}