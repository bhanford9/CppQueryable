#include <gtest/gtest.h>

#include <cmath>
#include <iostream>
#include <string>

#include "../../../../DataStructures/Animal.h"
#include "../../../../DataStructures/Person.h"
#include "../../../../DataStructures/People.h"
#include "../../../../DataStructures/PersonLibrary.h"

#include "../../../../Queryable/Queryable.h"

#include "../../../../Queryable/QueryBuilder.h"

#include "BaseTimeTest.h"
#include "Utilities/TimeStats.h"
#include "Utilities/TimeTestParams/TimeTestParams.h"
#include "Utilities/TimingUtilities.h"

using namespace QueryBuilder;
using namespace TimingUtilities;

class ForEachTimeTest : public BaseTimeTest
{
protected:
  void SetUp() override
  {
  }

  void TearDown() override {}
};

TEST_P(ForEachTimeTest, DequeNumberTest)
{
  TimeTestParams params = GetParam();

  std::vector<uint> dataSample = { 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 };
  std::deque<uint> data;
  for (uint64_t i = 0; i < params.GetContainerSize(); i++)
  {
    data.push_back(dataSample[i % 12]);
  }

  Queryable<uint> local = BuildQueryable(data);

  TimeStats queryableStats = RunTimeAndLog(
    [&]() { local.ForEach([](uint value) { (void)value; }); },
    params.GetIterations(),
    this->queryableName
  );

  std::function<void()> action = [&]()
  {
    for (uint value : data)
    {
      (void)value;
    }
  };

  TimeStats standardStats = RunTimeAndLog(action, params.GetIterations(), this->standardName);

  std::cout << "\nTest Data:" << std::endl;
  std::cout << "\tSize: " << params.GetContainerSize() << std::endl;
  std::cout << "\tIterations: " << params.GetIterations() << std::endl;
  CompareAndLog(queryableStats, standardStats);
}

TEST_P(ForEachTimeTest, ListNumberTest)
{
  TimeTestParams params = GetParam();

  std::vector<uint> dataSample = { 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 };
  std::list<uint> data;
  for (uint64_t i = 0; i < params.GetContainerSize(); i++)
  {
    data.push_back(dataSample[i % 12]);
  }

  Queryable<uint> local = BuildQueryable(data);

  TimeStats queryableStats = RunTimeAndLog(
    [&]() { local.ForEach([](uint value) { (void)value; }); },
    params.GetIterations(),
    this->queryableName
  );

  std::function<void()> action = [&]()
  {
    for (uint value : data)
    {
      (void)value;
    }
  };

  TimeStats standardStats = RunTimeAndLog(action, params.GetIterations(), this->standardName);

  std::cout << "\nTest Data:" << std::endl;
  std::cout << "\tSize: " << params.GetContainerSize() << std::endl;
  std::cout << "\tIterations: " << params.GetIterations() << std::endl;
  CompareAndLog(queryableStats, standardStats);
}

TEST_P(ForEachTimeTest, MultiSetNumberTest)
{
  TimeTestParams params = GetParam();

  std::vector<uint> dataSample = { 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 };
  std::multiset<uint, std::function<bool(uint, uint)>> data;
  for (uint64_t i = 0; i < params.GetContainerSize(); i++)
  {
    data.insert(dataSample[i % 12]);
  }

  Queryable<uint> local = BuildQueryable(data);

  TimeStats queryableStats = RunTimeAndLog(
    [&]() { local.ForEach([](uint value) { (void)value; }); },
    params.GetIterations(),
    this->queryableName
  );

  std::function<void()> action = [&]()
  {
    for (uint value : data)
    {
      (void)value;
    }
  };

  TimeStats standardStats = RunTimeAndLog(action, params.GetIterations(), this->standardName);

  std::cout << "\nTest Data:" << std::endl;
  std::cout << "\tSize: " << params.GetContainerSize() << std::endl;
  std::cout << "\tIterations: " << params.GetIterations() << std::endl;
  CompareAndLog(queryableStats, standardStats);
}

TEST_P(ForEachTimeTest, SetNumberTest)
{
  TimeTestParams params = GetParam();

  std::set<uint, std::function<bool(uint, uint)>> data;
  for (uint64_t i = 0; i < params.GetContainerSize(); i++)
  {
    data.insert(i);
  }

  Queryable<uint> local = BuildQueryable(data);

  TimeStats queryableStats = RunTimeAndLog(
    [&]() { local.ForEach([](uint value) { (void)value; }); },
    params.GetIterations(),
    this->queryableName
  );

  std::function<void()> action = [&]()
  {
    for (uint value : data)
    {
      (void)value;
    }
  };

  TimeStats standardStats = RunTimeAndLog(action, params.GetIterations(), this->standardName);

  std::cout << "\nTest Data:" << std::endl;
  std::cout << "\tSize: " << params.GetContainerSize() << std::endl;
  std::cout << "\tIterations: " << params.GetIterations() << std::endl;
  CompareAndLog(queryableStats, standardStats);
}

TEST_P(ForEachTimeTest, VectorNumberTest)
{
  TimeTestParams params = GetParam();

  std::vector<uint> dataSample = { 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 };
  std::vector<uint> data;
  for (uint64_t i = 0; i < params.GetContainerSize(); i++)
  {
    data.push_back(dataSample[i % 12]);
  }

  Queryable<uint> local = BuildQueryable(data);

  TimeStats queryableStats = RunTimeAndLog(
    [&]() { local.ForEach([](uint value) { (void)value; }); },
    params.GetIterations(),
    this->queryableName
  );

  std::function<void()> action = [&]()
  {
    for (uint value : data)
    {
      (void)value;
    }
  };

  TimeStats standardStats = RunTimeAndLog(action, params.GetIterations(), this->standardName);

  std::cout << "\nTest Data:" << std::endl;
  std::cout << "\tSize: " << params.GetContainerSize() << std::endl;
  std::cout << "\tIterations: " << params.GetIterations() << std::endl;
  CompareAndLog(queryableStats, standardStats);
}

TEST_P(ForEachTimeTest, DequePersonTest)
{
  TimeTestParams params = GetParam();

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

  Queryable<Person> local = BuildQueryable(data);

  TimeStats queryableStats = RunTimeAndLog(
    [&]() { local.ForEach([](Person value) { (void)value; }); },
    params.GetIterations(),
    this->queryableName
  );

  std::function<void()> action = [&]()
  {
    for (Person value : data)
    {
      (void)value;
    }
  };

  TimeStats standardStats = RunTimeAndLog(action, params.GetIterations(), this->standardName);

  std::cout << "\nTest Data:" << std::endl;
  std::cout << "\tSize: " << params.GetContainerSize() << std::endl;
  std::cout << "\tIterations: " << params.GetIterations() << std::endl;
  CompareAndLog(queryableStats, standardStats);
}

TEST_P(ForEachTimeTest, ListPersonTest)
{
  TimeTestParams params = GetParam();

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

  Queryable<Person> local = BuildQueryable(data);

  TimeStats queryableStats = RunTimeAndLog(
    [&]() { local.ForEach([](Person value) { (void)value; }); },
    params.GetIterations(),
    this->queryableName
  );

  std::function<void()> action = [&]()
  {
    for (Person value : data)
    {
      (void)value;
    }
  };

  TimeStats standardStats = RunTimeAndLog(action, params.GetIterations(), this->standardName);

  std::cout << "\nTest Data:" << std::endl;
  std::cout << "\tSize: " << params.GetContainerSize() << std::endl;
  std::cout << "\tIterations: " << params.GetIterations() << std::endl;
  CompareAndLog(queryableStats, standardStats);
}

TEST_P(ForEachTimeTest, MultiSetPersonTest)
{
  TimeTestParams params = GetParam();

  std::vector<Person> dataSample =
  {
    Person(0, "Person 4", 0, 0, Gender::Male),
    Person(0, "Person 5", 0, 0, Gender::Male),
    Person(0, "Person 6", 0, 0, Gender::Male),
    Person(0, "Person 7", 0, 0, Gender::Male),
    Person(0, "Person 8", 0, 0, Gender::Male),
    Person(0, "Person 9", 0, 0, Gender::Male),
  };

  std::multiset<Person, std::function<bool(Person, Person)>> data;
  for (uint64_t i = 0; i < params.GetContainerSize(); i++)
  {
    data.insert(dataSample[i % 6]);
  }

  Queryable<Person> local = BuildQueryable(data);

  TimeStats queryableStats = RunTimeAndLog(
    [&]() { local.ForEach([](Person value) { (void)value; }); },
    params.GetIterations(),
    this->queryableName
  );

  std::function<void()> action = [&]()
  {
    for (Person value : data)
    {
      (void)value;
    }
  };

  TimeStats standardStats = RunTimeAndLog(action, params.GetIterations(), this->standardName);

  std::cout << "\nTest Data:" << std::endl;
  std::cout << "\tSize: " << params.GetContainerSize() << std::endl;
  std::cout << "\tIterations: " << params.GetIterations() << std::endl;
  CompareAndLog(queryableStats, standardStats);
}

TEST_P(ForEachTimeTest, SetPersonTest)
{
  TimeTestParams params = GetParam();

  std::vector<Person> dataSample =
  {
    Person(0, "Person 4", 0, 0, Gender::Male),
    Person(0, "Person 5", 0, 0, Gender::Male),
    Person(0, "Person 6", 0, 0, Gender::Male),
    Person(0, "Person 7", 0, 0, Gender::Male),
    Person(0, "Person 8", 0, 0, Gender::Male),
    Person(0, "Person 9", 0, 0, Gender::Male),
  };

  std::set<Person, std::function<bool(Person, Person)>> data;
  for (uint64_t i = 0; i < params.GetContainerSize(); i++)
  {
    data.insert(dataSample[i % 6]);
  }

  Queryable<Person> local = BuildQueryable(data);

  TimeStats queryableStats = RunTimeAndLog(
    [&]() { local.ForEach([](Person value) { (void)value; }); },
    params.GetIterations(),
    this->queryableName
  );

  std::function<void()> action = [&]()
  {
    for (Person value : data)
    {
      (void)value;
    }
  };

  TimeStats standardStats = RunTimeAndLog(action, params.GetIterations(), this->standardName);

  std::cout << "\nTest Data:" << std::endl;
  std::cout << "\tSize: " << params.GetContainerSize() << std::endl;
  std::cout << "\tIterations: " << params.GetIterations() << std::endl;
  CompareAndLog(queryableStats, standardStats);
}

TEST_P(ForEachTimeTest, VectorPersonTest)
{
  TimeTestParams params = GetParam();

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

  Queryable<Person> local = BuildQueryable(data);

  TimeStats queryableStats = RunTimeAndLog(
    [&]() { local.ForEach([](Person value) { (void)value; }); },
    params.GetIterations(),
    this->queryableName
  );

  std::function<void()> action = [&]()
  {
    for (Person value : data)
    {
      (void)value;
    }
  };

  TimeStats standardStats = RunTimeAndLog(action, params.GetIterations(), this->standardName);

  std::cout << "\nTest Data:" << std::endl;
  std::cout << "\tSize: " << params.GetContainerSize() << std::endl;
  std::cout << "\tIterations: " << params.GetIterations() << std::endl;
  CompareAndLog(queryableStats, standardStats);
}

TEST_P(ForEachTimeTest, VectorNumberHeavyLoadTest)
{
  TimeTestParams params = GetParam();

  std::vector<uint> dataSample = { 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 };
  std::vector<uint> data;
  for (uint64_t i = 0; i < params.GetContainerSize(); i++)
  {
    data.push_back(dataSample[i % 12]);
  }

  Queryable<uint> local = BuildQueryable(data);

  TimeStats queryableStats = RunTimeAndLog(
    [&]() {
      local.ForEach([](uint value)
      {
        for (int i = 0; i < 10; i++)
        {
          value = sqrt(value * i / (value + 100));
        }
      });
    },
    params.GetIterations(),
    this->queryableName
  );

  std::function<void()> action = [&]()
  {
    for (uint value : data)
    {
      for (int i = 0; i < 10; i++)
      {
        value = sqrt(value * i / (value + 100));
      }
    }
  };

  TimeStats standardStats = RunTimeAndLog(action, params.GetIterations(), this->standardName);

  std::cout << "\nTest Data:" << std::endl;
  std::cout << "\tSize: " << params.GetContainerSize() << std::endl;
  std::cout << "\tIterations: " << params.GetIterations() << std::endl;
  CompareAndLog(queryableStats, standardStats);
}

INSTANTIATE_TEST_SUITE_P(
  ForEachTimeTesting,
  ForEachTimeTest,
  ::testing::Values(
    TimeTestParams(30, 1),
    TimeTestParams(30, 10),
    TimeTestParams(30, 100),
    TimeTestParams(30, 1000),
    TimeTestParams(30, 10000),
    TimeTestParams(30, 100000),
    TimeTestParams(30, 1000000)));
