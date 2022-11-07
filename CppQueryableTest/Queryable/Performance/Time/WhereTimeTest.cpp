#include <iostream>
#include <string>

#include "../../../../DataStructures/Animal.hpp"
#include "../../../../DataStructures/Person.hpp"
#include "../../../../DataStructures/People.hpp"

#include "../../../../Queryable/InternalQueryable.hpp"
#include "../../../../Queryable/InternalQueryables/VectorInternalQueryable.hpp"

#include "../../../../Queryable/QueryBuilder.hpp"

#include "BaseTimeTest.hpp"
#include "Utilities/TimeStats.hpp"
#include "Utilities/TimeTestParams/TimeTestParams.hpp"
#include "Utilities/TimingUtilities.hpp"

#include "TestSuites/WhereTimeTest.hpp"

#include "Utilities/Duration.hpp"
#include "Utilities/TimingTypes.hpp"

using namespace QueryBuilder;

void WhereTimeTest::DequeNumberTest(TimeTestParams & params)
{
  
  params.SetCategory(TimeTestCategory::Type::BuiltIn);

  std::deque<size_t> dataSample = { 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 };
  std::deque<size_t> data;
  for (size_t i = 0; i < params.GetContainerSize(); i++)
  {
    data.push_back(dataSample[i % 12]);
  }

  QueryableDeque<size_t> local = BuildQueryable(data);

  params.SetQueryableStats(RunTimeAndLog(
    [&]()
    {
      local.Where([&](size_t value)
      {
        this->ApplyLoad(params.GetLoad(), value);
        return (value % 2) == 0;
      });
    },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
      std::deque<size_t> standardWhered;
      for (size_t value : data)
      {
        this->ApplyLoad(params.GetLoad(), value);
        if ((value % 2) == 0)
        {
          standardWhered.push_back(value);
        }
      }
      return standardWhered;
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseData(params);
}

void WhereTimeTest::DequeNumberCopyToQueryableDequeTest(TimeTestParams & params)
{
  
  params.SetCategory(TimeTestCategory::Type::BuiltIn);

  std::deque<size_t> dataSample = { 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 };
  std::deque<size_t> data;
  for (size_t i = 0; i < params.GetContainerSize(); i++)
  {
    data.push_back(dataSample[i % 12]);
  }

  QueryableDeque<size_t> local = BuildQueryable(data);

  params.SetQueryableStats(RunTimeAndLog(
    [&]()
    {
      local = local.Where([&](size_t value)
      {
        this->ApplyLoad(params.GetLoad(), value);
        return (value % 2) == 0;
      }).ToQueryable();
    },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
      std::deque<size_t> standardWhered;
      for (size_t value : data)
      {
        this->ApplyLoad(params.GetLoad(), value);
        if ((value % 2) == 0)
        {
          standardWhered.push_back(value);
        }
      }
      return standardWhered;
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseData(params);
}

void WhereTimeTest::DequeNumberCopyToDequeTest(TimeTestParams & params)
{
  
  params.SetCategory(TimeTestCategory::Type::BuiltIn);

  std::deque<size_t> dataSample = { 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 };
  std::deque<size_t> data;
  for (size_t i = 0; i < params.GetContainerSize(); i++)
  {
    data.push_back(dataSample[i % 12]);
  }

  QueryableDeque<size_t> local = BuildQueryable(data);

  params.SetQueryableStats(RunTimeAndLog(
    [&]()
    {
      std::deque<size_t> newData = local.Where([&](size_t value)
      {
        this->ApplyLoad(params.GetLoad(), value);
        return (value % 2) == 0;
      }).ToDeque();
    },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
      std::deque<size_t> standardWhered;
      for (size_t value : data)
      {
        this->ApplyLoad(params.GetLoad(), value);
        if ((value % 2) == 0)
        {
          standardWhered.push_back(value);
        }
      }
      return standardWhered;
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseData(params);
}



void WhereTimeTest::ListNumberTest(TimeTestParams & params)
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
      local.Where([&](size_t value)
      {
        this->ApplyLoad(params.GetLoad(), value);
        return (value % 2) == 0;
      });
    },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
      std::list<size_t> standardWhered;
      for (size_t value : data)
      {
        this->ApplyLoad(params.GetLoad(), value);
        if ((value % 2) == 0)
        {
          standardWhered.push_back(value);
        }
      }
      return standardWhered;
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseData(params);
}

void WhereTimeTest::ListNumberCopyToQueryableListTest(TimeTestParams & params)
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
      local = local.Where([&](size_t value)
      {
        this->ApplyLoad(params.GetLoad(), value);
        return (value % 2) == 0;
      }).ToQueryable();
    },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
      std::list<size_t> standardWhered;
      for (size_t value : data)
      {
        this->ApplyLoad(params.GetLoad(), value);
        if ((value % 2) == 0)
        {
          standardWhered.push_back(value);
        }
      }
      return standardWhered;
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseData(params);
}

void WhereTimeTest::ListNumberCopyToListTest(TimeTestParams & params)
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
      std::list<size_t> newData = local.Where([&](size_t value)
      {
        this->ApplyLoad(params.GetLoad(), value);
        return (value % 2) == 0;
      }).ToList();
    },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
      std::list<size_t> standardWhered;
      for (size_t value : data)
      {
        this->ApplyLoad(params.GetLoad(), value);
        if ((value % 2) == 0)
        {
          standardWhered.push_back(value);
        }
      }
      return standardWhered;
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseData(params);
}



void WhereTimeTest::MultiSetNumberTest(TimeTestParams & params)
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
      local.Where([&](size_t value)
      {
        this->ApplyLoad(params.GetLoad(), value);
        return (value % 2) == 0;
      });
    },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
      std::multiset<size_t> standardWhered;
      for (size_t value : data)
      {
        this->ApplyLoad(params.GetLoad(), value);
        if ((value % 2) == 0)
        {
          standardWhered.insert(value);
        }
      }
      return standardWhered;
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseData(params);
}

void WhereTimeTest::MultiSetNumberCopyToQueryableMultiSetTest(TimeTestParams & params)
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
      local = local.Where([&](size_t value)
      {
        this->ApplyLoad(params.GetLoad(), value);
        return (value % 2) == 0;
      }).ToQueryable();
    },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
      std::multiset<size_t> standardWhered;
      for (size_t value : data)
      {
        this->ApplyLoad(params.GetLoad(), value);
        if ((value % 2) == 0)
        {
          standardWhered.insert(value);
        }
      }
      return standardWhered;
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseData(params);
}

void WhereTimeTest::MultiSetNumberCopyToMultiSetTest(TimeTestParams & params)
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
      std::multiset<size_t> newData = local.Where([&](size_t value)
      {
        this->ApplyLoad(params.GetLoad(), value);
        return (value % 2) == 0;
      }).ToMultiSet();
    },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
      std::multiset<size_t> standardWhered;
      for (size_t value : data)
      {
        this->ApplyLoad(params.GetLoad(), value);
        if ((value % 2) == 0)
        {
          standardWhered.insert(value);
        }
      }
      return standardWhered;
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseData(params);
}



void WhereTimeTest::VectorNumberTest(TimeTestParams & params)
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
      local.Where([&](size_t value)
      {
        this->ApplyLoad(params.GetLoad(), value);
        return (value % 2) == 0;
      });
    },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
      std::vector<size_t> standardWhered;
      for (size_t value : data)
      {
        this->ApplyLoad(params.GetLoad(), value);
        if ((value % 2) == 0)
        {
          standardWhered.push_back(value);
        }
      }
      return standardWhered;
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseData(params);
}

void WhereTimeTest::VectorNumberCopyToQueryableVectorTest(TimeTestParams & params)
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
      local = local.Where([&](size_t value)
      {
        this->ApplyLoad(params.GetLoad(), value);
        return (value % 2) == 0;
      }).ToQueryable();
    },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
      std::vector<size_t> standardWhered;
      for (size_t value : data)
      {
        this->ApplyLoad(params.GetLoad(), value);
        if ((value % 2) == 0)
        {
          standardWhered.push_back(value);
        }
      }
      return standardWhered;
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseData(params);
}

void WhereTimeTest::VectorNumberCopyToVectorTest(TimeTestParams & params)
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
      std::vector<size_t> newData = local.Where([&](size_t value)
      {
        this->ApplyLoad(params.GetLoad(), value);
        return (value % 2) == 0;
      }).ToVector();
    },
    params.GetIterations(),
    this->queryableName));

  params.SetStandardStats(RunTimeAndLog(
    [&]()
    {
      std::vector<size_t> standardWhered;
      for (size_t value : data)
      {
        this->ApplyLoad(params.GetLoad(), value);
        if ((value % 2) == 0)
        {
          standardWhered.push_back(value);
        }
      }
      return standardWhered;
    },
    params.GetIterations(),
    this->standardName));

  this->LogBaseData(params);
}
