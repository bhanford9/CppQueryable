#include <gtest/gtest.h>

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

using namespace QueryBuilder;
using namespace TimingUtilities;

// THINGS TO TEST (for each container type and for both numeric and object items)
//  1) first element passes
//  2) passes at 25% of the way through
//  3) passes at 50% of the way through
//  4) passes at 75% of the way through
//  5) last element passes
//  6) no elements pass

class AnyTimeTest : public BaseTimeTest
{
protected:
  size_t triggerValue = 99999999;
  std::string nameTriggerValue = "Hello World!";
  size_t triggerIndex = 0;

  void SetUp() override
  {
    BaseTimeTest::SetUp();
    this->methodName = "Any";
  }

  void Init()
  {
    switch (this->params.GetTriggerType())
    {
      case TriggerType::Begin:
        this->triggerIndex = 0;
        break;
      case TriggerType::Quarter:
        this->triggerIndex = this->params.GetContainerSize() * 0.25;
        break;
      case TriggerType::Half:
        this->triggerIndex = this->params.GetContainerSize() * 0.5;
        break;
      case TriggerType::ThreeQuarter:
        this->triggerIndex = this->params.GetContainerSize() * 0.75;
        break;
      case TriggerType::End:
        this->triggerIndex = this->params.GetContainerSize() - 1;
        break;
      case TriggerType::Never:
        this->triggerIndex = this->params.GetContainerSize() + 1;
        this->triggerValue++;
        break;
      case TriggerType::NotApplicable:
      default:
        break;
    }
  }

  void LogBaseWithTriggerData()
  {
    std::stringstream preCompareInfo;
    preCompareInfo
      << "\tTrigger Type: " << GetTriggerName(this->params.GetTriggerType()) << std::endl
      << "\tTrigger Index: " << this->triggerIndex << std::endl;
    this->LogBaseData(preCompareInfo.str());
  }
};

TEST_P(AnyTimeTest, DequeNumberTest)
{
  this->params = GetParam();
  this->params.SetCategory(TimeTestCategory::BuiltIn);
  this->Init();

  std::vector<size_t> dataSample = { 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 };
  std::deque<size_t> data;
  for (size_t i = 0; i < params.GetContainerSize(); i++)
  {
    data.push_back(i == this->triggerIndex ? this->triggerValue : dataSample[i % 12]);
  }

  IQueryable<size_t> local = BuildQueryable2(data);

  this->queryableStats = RunTimeAndLog(
    [&]()
    {
      local.Any([&](size_t value)
      {
        this->ApplyLoad(this->params.GetLoad(), value);
        return value == this->triggerValue;
      });
    },
    params.GetIterations(),
    this->queryableName
  );

  this->standardStats = RunTimeAndLog(
    [&]()
    {
      for (size_t value : data)
      {
        this->ApplyLoad(this->params.GetLoad(), value);
        if (value == this->triggerValue)
        {
          return true;
        }
      }

      return false;
    },
    params.GetIterations(),
    this->standardName);

  this->LogBaseWithTriggerData();
}

TEST_P(AnyTimeTest, ListNumberTest)
{
  this->params = GetParam();
  this->params.SetCategory(TimeTestCategory::BuiltIn);
  this->Init();

  std::vector<size_t> dataSample = { 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 };
  std::list<size_t> data;
  for (size_t i = 0; i < params.GetContainerSize(); i++)
  {
    data.push_back(i == this->triggerIndex ? this->triggerValue : dataSample[i % 12]);
  }

  IQueryable<size_t> local = BuildQueryable2(data);

  this->queryableStats = RunTimeAndLog(
    [&]()
    {
      local.Any([&](size_t value)
      {
        this->ApplyLoad(this->params.GetLoad(), value);
        return value == this->triggerValue;
      });
    },
    params.GetIterations(),
    this->queryableName
  );

  this->standardStats = RunTimeAndLog(
    [&]()
    {
      for (size_t value : data)
      {
        this->ApplyLoad(this->params.GetLoad(), value);
        if (value == this->triggerValue)
        {
          return true;
        }
      }

      return false;
    },
    params.GetIterations(),
    this->standardName);

  this->LogBaseWithTriggerData();
}

TEST_P(AnyTimeTest, MultiSetNumberTest)
{
  this->params = GetParam();
  this->params.SetCategory(TimeTestCategory::BuiltIn);
  this->Init();

  std::multiset<size_t> data;
  for (size_t i = 0; i < params.GetContainerSize(); i++)
  {
    if (i == this->triggerIndex)
    {
      this->triggerValue = i;
    }

    data.insert(i);
  }

  IQueryable<size_t> local = BuildQueryable2(data);

  this->queryableStats = RunTimeAndLog(
    [&]()
    {
      local.Any([&](size_t value)
      {
        this->ApplyLoad(this->params.GetLoad(), value);
        return value == this->triggerValue;
      });
    },
    params.GetIterations(),
    this->queryableName
  );

  this->standardStats = RunTimeAndLog(
    [&]()
    {
      for (size_t value : data)
      {
        this->ApplyLoad(this->params.GetLoad(), value);
        if (value == this->triggerValue)
        {
          return true;
        }
      }

      return false;
    },
    params.GetIterations(),
    this->standardName);

  this->LogBaseWithTriggerData();
}

TEST_P(AnyTimeTest, SetNumberTest)
{
  this->params = GetParam();
  this->params.SetCategory(TimeTestCategory::BuiltIn);
  this->Init();

  std::set<size_t> data;
  for (size_t i = 0; i < params.GetContainerSize(); i++)
  {
    if (i == this->triggerIndex)
    {
      this->triggerValue = i;
    }

    data.insert(i);
  }

  IQueryable<size_t> local = BuildQueryable2(data);

  this->queryableStats = RunTimeAndLog(
    [&]()
    {
      local.Any([&](size_t value)
      {
        this->ApplyLoad(this->params.GetLoad(), value);
        return value == this->triggerValue;
      });
    },
    params.GetIterations(),
    this->queryableName
  );

  this->standardStats = RunTimeAndLog(
    [&]()
    {
      for (size_t value : data)
      {
        this->ApplyLoad(this->params.GetLoad(), value);
        if (value == this->triggerValue)
        {
          return true;
        }
      }

      return false;
    },
    params.GetIterations(),
    this->standardName);

  this->LogBaseWithTriggerData();
}

TEST_P(AnyTimeTest, VectorNumberTest)
{
  this->params = GetParam();
  this->params.SetCategory(TimeTestCategory::BuiltIn);
  this->Init();

  std::vector<size_t> dataSample = { 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 };
  std::vector<size_t> data;
  for (size_t i = 0; i < params.GetContainerSize(); i++)
  {
    data.push_back(i == this->triggerIndex ? this->triggerValue : dataSample[i % 12]);
  }

  IQueryable<size_t> local = BuildQueryable2(data);

  this->queryableStats = RunTimeAndLog(
    [&]()
    {
      local.Any([&](size_t value)
      {
        this->ApplyLoad(this->params.GetLoad(), value);
        return value == this->triggerValue;
      });
    },
    params.GetIterations(),
    this->queryableName
  );

  this->standardStats = RunTimeAndLog(
    [&]()
    {
      for (size_t value : data)
      {
        this->ApplyLoad(this->params.GetLoad(), value);
        if (value == this->triggerValue)
        {
          return true;
        }
      }

      return false;
    },
    params.GetIterations(),
    this->standardName);

  this->LogBaseWithTriggerData();
}

TEST_P(AnyTimeTest, DequePersonTest)
{
  this->params = GetParam();
  this->params.SetCategory(TimeTestCategory::Class);
  this->Init();

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

  IQueryable<Person> local = BuildQueryable2(data);

  this->queryableStats = RunTimeAndLog(
    [&]()
    {
      local.Any([&](Person value)
      {
        this->ApplyLoad(this->params.GetLoad(), value);
        return value.GetName() == this->nameTriggerValue;
      });
    },
    params.GetIterations(),
    this->queryableName
  );

  this->standardStats = RunTimeAndLog(
    [&]()
    {
      for (Person value : data)
      {
        this->ApplyLoad(this->params.GetLoad(), value);
        if (value.GetName() == this->nameTriggerValue)
        {
          return true;
        }
      }

      return false;
    },
    params.GetIterations(),
    this->standardName);

  this->LogBaseWithTriggerData();
}

TEST_P(AnyTimeTest, ListPersonTest)
{
  this->params = GetParam();
  this->params.SetCategory(TimeTestCategory::Class);
  this->Init();

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


  IQueryable<Person> local = BuildQueryable2(data);

  this->queryableStats = RunTimeAndLog(
    [&]()
    {
      local.Any([&](Person value)
      {
        this->ApplyLoad(this->params.GetLoad(), value);
        return value.GetName() == this->nameTriggerValue;
      });
    },
    params.GetIterations(),
    this->queryableName
  );

  this->standardStats = RunTimeAndLog(
    [&]()
    {
      for (Person value : data)
      {
        this->ApplyLoad(this->params.GetLoad(), value);
        if (value.GetName() == this->nameTriggerValue)
        {
          return true;
        }
      }

      return false;
    },
    params.GetIterations(),
    this->standardName);

  this->LogBaseWithTriggerData();
}

TEST_P(AnyTimeTest, MultiSetPersonTest)
{
  this->params = GetParam();
  this->params.SetCategory(TimeTestCategory::Class);
  this->Init();

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

  IQueryable<Person> local = BuildQueryable2(data);

  this->queryableStats = RunTimeAndLog(
    [&]()
    {
      local.Any([&](Person value)
      {
        this->ApplyLoad(this->params.GetLoad(), value);
        return value.GetName() == this->nameTriggerValue;
      });
    },
    params.GetIterations(),
    this->queryableName
  );

  this->standardStats = RunTimeAndLog(
    [&]()
    {
      for (Person value : data)
      {
        this->ApplyLoad(this->params.GetLoad(), value);
        if (value.GetName() == this->nameTriggerValue)
        {
          return true;
        }
      }

      return false;
    },
    params.GetIterations(),
    this->standardName);

  this->LogBaseWithTriggerData();
}

TEST_P(AnyTimeTest, SetPersonTest)
{
  this->params = GetParam();
  this->params.SetCategory(TimeTestCategory::Class);
  this->Init();

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

  IQueryable<Person> local = BuildQueryable2(data);

  this->queryableStats = RunTimeAndLog(
    [&]()
    {
      local.Any([&](Person value)
      {
        this->ApplyLoad(this->params.GetLoad(), value);
        return value.GetName() == this->nameTriggerValue;
      });
    },
    params.GetIterations(),
    this->queryableName
  );

  this->standardStats = RunTimeAndLog(
    [&]()
    {
      for (Person value : data)
      {
        this->ApplyLoad(this->params.GetLoad(), value);
        if (value.GetName() == this->nameTriggerValue)
        {
          return true;
        }
      }

      return false;
    },
    params.GetIterations(),
    this->standardName);

  this->LogBaseWithTriggerData();
}

TEST_P(AnyTimeTest, VectorPersonTest)
{
  this->params = GetParam();
  this->params.SetCategory(TimeTestCategory::Class);
  this->Init();

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

  IQueryable<Person> local = BuildQueryable2(data);

  this->queryableStats = RunTimeAndLog(
    [&]()
    {
      local.Any([&](Person value)
      {
        this->ApplyLoad(this->params.GetLoad(), value);
        return value.GetName() == this->nameTriggerValue;
      });
    },
    params.GetIterations(),
    this->queryableName
  );

  this->standardStats = RunTimeAndLog(
    [&]()
    {
      for (Person value : data)
      {
        this->ApplyLoad(this->params.GetLoad(), value);
        if (value.GetName() == this->nameTriggerValue)
        {
          return true;
        }
      }

      return false;
    },
    params.GetIterations(),
    this->standardName);

  this->LogBaseWithTriggerData();
}

INSTANTIATE_TEST_SUITE_P(
  AnyTimeTesting,
  AnyTimeTest,
  ::testing::Values(
    TimeTestParams(30, 10, 10, TriggerType::Begin),
    TimeTestParams(30, 10, 10, TriggerType::Quarter),
    TimeTestParams(30, 10, 10, TriggerType::Half),
    TimeTestParams(30, 10, 10, TriggerType::ThreeQuarter),
    TimeTestParams(30, 10, 10, TriggerType::End),
    TimeTestParams(30, 10, 10, TriggerType::Never),
    TimeTestParams(30, 10, 50, TriggerType::Begin),
    TimeTestParams(30, 10, 50, TriggerType::Quarter),
    TimeTestParams(30, 10, 50, TriggerType::Half),
    TimeTestParams(30, 10, 50, TriggerType::ThreeQuarter),
    TimeTestParams(30, 10, 50, TriggerType::End),
    TimeTestParams(30, 10, 50, TriggerType::Never),
    TimeTestParams(30, 10, 100, TriggerType::Begin),
    TimeTestParams(30, 10, 100, TriggerType::Quarter),
    TimeTestParams(30, 10, 100, TriggerType::Half),
    TimeTestParams(30, 10, 100, TriggerType::ThreeQuarter),
    TimeTestParams(30, 10, 100, TriggerType::End),
    TimeTestParams(30, 10, 100, TriggerType::Never),
    TimeTestParams(30, 100, 10, TriggerType::Begin),
    TimeTestParams(30, 100, 10, TriggerType::Quarter),
    TimeTestParams(30, 100, 10, TriggerType::Half),
    TimeTestParams(30, 100, 10, TriggerType::ThreeQuarter),
    TimeTestParams(30, 100, 10, TriggerType::End),
    TimeTestParams(30, 100, 10, TriggerType::Never),
    TimeTestParams(30, 100, 50, TriggerType::Begin),
    TimeTestParams(30, 100, 50, TriggerType::Quarter),
    TimeTestParams(30, 100, 50, TriggerType::Half),
    TimeTestParams(30, 100, 50, TriggerType::ThreeQuarter),
    TimeTestParams(30, 100, 50, TriggerType::End),
    TimeTestParams(30, 100, 50, TriggerType::Never),
    TimeTestParams(30, 100, 100, TriggerType::Begin),
    TimeTestParams(30, 100, 100, TriggerType::Quarter),
    TimeTestParams(30, 100, 100, TriggerType::Half),
    TimeTestParams(30, 100, 100, TriggerType::ThreeQuarter),
    TimeTestParams(30, 100, 100, TriggerType::End),
    TimeTestParams(30, 100, 100, TriggerType::Never),
    TimeTestParams(30, 1000, 10, TriggerType::Begin),
    TimeTestParams(30, 1000, 10, TriggerType::Quarter),
    TimeTestParams(30, 1000, 10, TriggerType::Half),
    TimeTestParams(30, 1000, 10, TriggerType::ThreeQuarter),
    TimeTestParams(30, 1000, 10, TriggerType::End),
    TimeTestParams(30, 1000, 10, TriggerType::Never),
    TimeTestParams(30, 1000, 50, TriggerType::Begin),
    TimeTestParams(30, 1000, 50, TriggerType::Quarter),
    TimeTestParams(30, 1000, 50, TriggerType::Half),
    TimeTestParams(30, 1000, 50, TriggerType::ThreeQuarter),
    TimeTestParams(30, 1000, 50, TriggerType::End),
    TimeTestParams(30, 1000, 50, TriggerType::Never),
    TimeTestParams(30, 1000, 100, TriggerType::Begin),
    TimeTestParams(30, 1000, 100, TriggerType::Quarter),
    TimeTestParams(30, 1000, 100, TriggerType::Half),
    TimeTestParams(30, 1000, 100, TriggerType::ThreeQuarter),
    TimeTestParams(30, 1000, 100, TriggerType::End),
    TimeTestParams(30, 1000, 100, TriggerType::Never),
    TimeTestParams(30, 10000, 10, TriggerType::Begin),
    TimeTestParams(30, 10000, 10, TriggerType::Quarter),
    TimeTestParams(30, 10000, 10, TriggerType::Half),
    TimeTestParams(30, 10000, 10, TriggerType::ThreeQuarter),
    TimeTestParams(30, 10000, 10, TriggerType::End),
    TimeTestParams(30, 10000, 10, TriggerType::Never),
    TimeTestParams(30, 10000, 50, TriggerType::Begin),
    TimeTestParams(30, 10000, 50, TriggerType::Quarter),
    TimeTestParams(30, 10000, 50, TriggerType::Half),
    TimeTestParams(30, 10000, 50, TriggerType::ThreeQuarter),
    TimeTestParams(30, 10000, 50, TriggerType::End),
    TimeTestParams(30, 10000, 50, TriggerType::Never),
    TimeTestParams(30, 10000, 100, TriggerType::Begin),
    TimeTestParams(30, 10000, 100, TriggerType::Quarter),
    TimeTestParams(30, 10000, 100, TriggerType::Half),
    TimeTestParams(30, 10000, 100, TriggerType::ThreeQuarter),
    TimeTestParams(30, 10000, 100, TriggerType::End),
    TimeTestParams(30, 10000, 100, TriggerType::Never)));
