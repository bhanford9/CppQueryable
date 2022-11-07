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

#include "TestSuites/AnyTimeTest.hpp"

using namespace QueryBuilder;

// THINGS TO TEST (for each container type and for both numeric and object items)
//  1) first element passes
//  2) passes at 25% of the way through
//  3) passes at 50% of the way through
//  4) passes at 75% of the way through
//  5) last element passes
//  6) no elements pass

void AnyTimeTest::DequeNumberTest(TimeTestParams & params)
{

  params.SetCategory(TimeTestCategory::Type::BuiltIn);
  this->Init(params);

  std::vector<size_t> dataSample = { 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 };
  std::deque<size_t> data;
  for (size_t i = 0; i < params.GetContainerSize(); i++)
  {
    data.push_back(i == this->triggerIndex ? this->triggerValue : dataSample[i % 12]);
  }

  QueryableDeque<size_t> local = BuildQueryable(data);

  params.SetQueryableStats(RunTimeAndLog(
    [&]()
    {
      local.Any([&](size_t value)
      {
        this->ApplyLoad(params.GetLoad(), value);
        return value == this->triggerValue;
      });
    },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
      for (size_t value : data)
      {
        this->ApplyLoad(params.GetLoad(), value);
        if (value == this->triggerValue)
        {
          return true;
        }
      }

      return false;
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseWithTriggerData(params);
}

void AnyTimeTest::ListNumberTest(TimeTestParams & params)
{

  params.SetCategory(TimeTestCategory::Type::BuiltIn);
  this->Init(params);

  std::vector<size_t> dataSample = { 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 };
  std::list<size_t> data;
  for (size_t i = 0; i < params.GetContainerSize(); i++)
  {
    data.push_back(i == this->triggerIndex ? this->triggerValue : dataSample[i % 12]);
  }

  QueryableList<size_t> local = BuildQueryable(data);

  params.SetQueryableStats(RunTimeAndLog(
    [&]()
    {
      local.Any([&](size_t value)
      {
        this->ApplyLoad(params.GetLoad(), value);
        return value == this->triggerValue;
      });
    },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
      for (size_t value : data)
      {
        this->ApplyLoad(params.GetLoad(), value);
        if (value == this->triggerValue)
        {
          return true;
        }
      }

      return false;
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseWithTriggerData(params);
}

void AnyTimeTest::MultiSetNumberTest(TimeTestParams & params)
{

  params.SetCategory(TimeTestCategory::Type::BuiltIn);
  this->Init(params);

  std::multiset<size_t> data;
  for (size_t i = 0; i < params.GetContainerSize(); i++)
  {
    if (i == this->triggerIndex)
    {
      this->triggerValue = i;
    }

    data.insert(i);
  }

  QueryableMultiSet<size_t> local = BuildQueryable(data);

  params.SetQueryableStats(RunTimeAndLog(
    [&]()
    {
      local.Any([&](size_t value)
      {
        this->ApplyLoad(params.GetLoad(), value);
        return value == this->triggerValue;
      });
    },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
      for (size_t value : data)
      {
        this->ApplyLoad(params.GetLoad(), value);
        if (value == this->triggerValue)
        {
          return true;
        }
      }

      return false;
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseWithTriggerData(params);
}

void AnyTimeTest::SetNumberTest(TimeTestParams & params)
{

  params.SetCategory(TimeTestCategory::Type::BuiltIn);
  this->Init(params);

  std::set<size_t> data;
  for (size_t i = 0; i < params.GetContainerSize(); i++)
  {
    if (i == this->triggerIndex)
    {
      this->triggerValue = i;
    }

    data.insert(i);
  }

  QueryableSet<size_t> local = BuildQueryable(data);

  params.SetQueryableStats(RunTimeAndLog(
    [&]()
    {
      local.Any([&](size_t value)
      {
        this->ApplyLoad(params.GetLoad(), value);
        return value == this->triggerValue;
      });
    },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
      for (size_t value : data)
      {
        this->ApplyLoad(params.GetLoad(), value);
        if (value == this->triggerValue)
        {
          return true;
        }
      }

      return false;
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseWithTriggerData(params);
}

void AnyTimeTest::VectorNumberTest(TimeTestParams & params)
{

  params.SetCategory(TimeTestCategory::Type::BuiltIn);
  this->Init(params);

  std::vector<size_t> dataSample = { 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 };
  std::vector<size_t> data;
  for (size_t i = 0; i < params.GetContainerSize(); i++)
  {
    data.push_back(i == this->triggerIndex ? this->triggerValue : dataSample[i % 12]);
  }

  QueryableVector<size_t> local = BuildQueryable(data);

  params.SetQueryableStats(RunTimeAndLog(
    [&]()
    {
      local.Any([&](size_t value)
      {
        this->ApplyLoad(params.GetLoad(), value);
        return value == this->triggerValue;
      });
    },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
      for (size_t value : data)
      {
        this->ApplyLoad(params.GetLoad(), value);
        if (value == this->triggerValue)
        {
          return true;
        }
      }

      return false;
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseWithTriggerData(params);
}

void AnyTimeTest::DequePersonTest(TimeTestParams & params)
{

  params.SetCategory(TimeTestCategory::Type::Class);
  this->Init(params);

  Person personTriggerValue(0, this->nameTriggerValue, 0, 0, Gender::Male);

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
    data.push_back(i == this->triggerIndex ? personTriggerValue : dataSample[i % 6]);
  }

  QueryableDeque<Person> local = BuildQueryable(data);

  params.SetQueryableStats(RunTimeAndLog(
    [&]()
    {
      local.Any([&](Person value)
      {
        this->ApplyLoad(params.GetLoad(), value);
        return value.GetName() == this->nameTriggerValue;
      });
    },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
      for (Person value : data)
      {
        this->ApplyLoad(params.GetLoad(), value);
        if (value.GetName() == this->nameTriggerValue)
        {
          return true;
        }
      }

      return false;
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseWithTriggerData(params);
}

void AnyTimeTest::ListPersonTest(TimeTestParams & params)
{

  params.SetCategory(TimeTestCategory::Type::Class);
  this->Init(params);

  Person personTriggerValue(0, this->nameTriggerValue, 0, 0, Gender::Male);

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
    data.push_back(i == this->triggerIndex ? personTriggerValue : dataSample[i % 6]);
  }


  QueryableList<Person> local = BuildQueryable(data);

  params.SetQueryableStats(RunTimeAndLog(
    [&]()
    {
      local.Any([&](Person value)
      {
        this->ApplyLoad(params.GetLoad(), value);
        return value.GetName() == this->nameTriggerValue;
      });
    },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
      for (Person value : data)
      {
        this->ApplyLoad(params.GetLoad(), value);
        if (value.GetName() == this->nameTriggerValue)
        {
          return true;
        }
      }

      return false;
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseWithTriggerData(params);
}

void AnyTimeTest::MultiSetPersonTest(TimeTestParams & params)
{

  params.SetCategory(TimeTestCategory::Type::Class);
  this->Init(params);

  std::multiset<Person> data;
  for (size_t i = 0; i < params.GetContainerSize(); i++)
  {
    std::string name = "Person " + std::to_string(i);
    Person person(0, name, 0, 0, Gender::Male);

    if (i == this->triggerIndex)
    {
      this->nameTriggerValue = name;
    }

    data.insert(person);
  }

  QueryableMultiSet<Person> local = BuildQueryable(data);

  params.SetQueryableStats(RunTimeAndLog(
    [&]()
    {
      local.Any([&](Person value)
      {
        this->ApplyLoad(params.GetLoad(), value);
        return value.GetName() == this->nameTriggerValue;
      });
    },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
      for (Person value : data)
      {
        this->ApplyLoad(params.GetLoad(), value);
        if (value.GetName() == this->nameTriggerValue)
        {
          return true;
        }
      }

      return false;
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseWithTriggerData(params);
}

void AnyTimeTest::SetPersonTest(TimeTestParams & params)
{

  params.SetCategory(TimeTestCategory::Type::Class);
  this->Init(params);

  std::set<Person> data;
  for (size_t i = 0; i < params.GetContainerSize(); i++)
  {
    std::string name = "Person " + std::to_string(i);
    Person person(0, name, 0, 0, Gender::Male);

    if (i == this->triggerIndex)
    {
      this->nameTriggerValue = name;
    }

    data.insert(person);
  }

  QueryableSet<Person> local = BuildQueryable(data);

  params.SetQueryableStats(RunTimeAndLog(
    [&]()
    {
      local.Any([&](Person value)
      {
        this->ApplyLoad(params.GetLoad(), value);
        return value.GetName() == this->nameTriggerValue;
      });
    },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
      for (Person value : data)
      {
        this->ApplyLoad(params.GetLoad(), value);
        if (value.GetName() == this->nameTriggerValue)
        {
          return true;
        }
      }

      return false;
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseWithTriggerData(params);
}

void AnyTimeTest::VectorPersonTest(TimeTestParams & params)
{

  params.SetCategory(TimeTestCategory::Type::Class);
  this->Init(params);

  Person personTriggerValue(0, this->nameTriggerValue, 0, 0, Gender::Male);

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
    data.push_back(i == this->triggerIndex ? personTriggerValue : dataSample[i % 6]);
  }

  QueryableVector<Person> local = BuildQueryable(data);

  params.SetQueryableStats(RunTimeAndLog(
    [&]()
    {
      local.Any([&](Person value)
      {
        this->ApplyLoad(params.GetLoad(), value);
        return value.GetName() == this->nameTriggerValue;
      });
    },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
      for (Person value : data)
      {
        this->ApplyLoad(params.GetLoad(), value);
        if (value.GetName() == this->nameTriggerValue)
        {
          return true;
        }
      }

      return false;
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseWithTriggerData(params);
}


