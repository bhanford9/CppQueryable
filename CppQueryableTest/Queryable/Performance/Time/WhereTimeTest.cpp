#include <gtest/gtest.h>

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

#include "Utilities/Duration.hpp"
#include "Utilities/TimingTypes.hpp"

using namespace QueryBuilder;
using namespace TimingUtilities;

class WhereTimeTest : public BaseTimeTest
{
protected:
  void SetUp() override
  {
    BaseTimeTest::SetUp();
    this->methodName = "Where";
  }
};

TEST_P(WhereTimeTest, DequeNumberTest)
{
  this->params = GetParam();
  this->params.SetCategory(TimeTestCategory::BuiltIn);

  std::deque<uint> dataSample = { 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 };
  std::deque<uint> data;
  for (uint64_t i = 0; i < params.GetContainerSize(); i++)
  {
    data.push_back(dataSample[i % 12]);
  }

  DequeInternalQueryable<uint> local = BuildQueryable(data);

  this->queryableStats = RunTimeAndLog(
    [&]()
    {
      local.Where([&](uint value)
      {
        this->ApplyLoad(this->params.GetLoad(), value);
        return (value % 2) == 0;
      });
    },
    params.GetIterations(),
    this->queryableName
  );

  this->standardStats = RunTimeAndLog(
    [&]()
    {
      std::deque<uint> standardWhered;
      for (uint value : data)
      {
        this->ApplyLoad(this->params.GetLoad(), value);
        if ((value % 2) == 0)
        {
          standardWhered.push_back(value);
        }
      }
      return standardWhered;
    },
    params.GetIterations(),
    this->standardName);

  this->LogBaseData();
}

TEST_P(WhereTimeTest, DequeNumberCopyToQueryableDequeTest)
{
  this->params = GetParam();
  this->params.SetCategory(TimeTestCategory::BuiltIn);

  std::deque<uint> dataSample = { 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 };
  std::deque<uint> data;
  for (uint64_t i = 0; i < params.GetContainerSize(); i++)
  {
    data.push_back(dataSample[i % 12]);
  }

  DequeInternalQueryable<uint> local = BuildQueryable(data);

  this->queryableStats = RunTimeAndLog(
    [&]()
    {
      local = local.Where([&](uint value)
      {
        this->ApplyLoad(this->params.GetLoad(), value);
        return (value % 2) == 0;
      }).ToQueryableDeque();
    },
    params.GetIterations(),
    this->queryableName
  );

  this->standardStats = RunTimeAndLog(
    [&]()
    {
      std::deque<uint> standardWhered;
      for (uint value : data)
      {
        this->ApplyLoad(this->params.GetLoad(), value);
        if ((value % 2) == 0)
        {
          standardWhered.push_back(value);
        }
      }
      return standardWhered;
    },
    params.GetIterations(),
    this->standardName);

  this->LogBaseData();
}

TEST_P(WhereTimeTest, DequeNumberCopyToDequeTest)
{
  this->params = GetParam();
  this->params.SetCategory(TimeTestCategory::BuiltIn);

  std::deque<uint> dataSample = { 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 };
  std::deque<uint> data;
  for (uint64_t i = 0; i < params.GetContainerSize(); i++)
  {
    data.push_back(dataSample[i % 12]);
  }

  DequeInternalQueryable<uint> local = BuildQueryable(data);

  this->queryableStats = RunTimeAndLog(
    [&]()
    {
      std::deque<uint> newData = local.Where([&](uint value)
      {
        this->ApplyLoad(this->params.GetLoad(), value);
        return (value % 2) == 0;
      }).ToDeque();
    },
    params.GetIterations(),
    this->queryableName
  );

  this->standardStats = RunTimeAndLog(
    [&]()
    {
      std::deque<uint> standardWhered;
      for (uint value : data)
      {
        this->ApplyLoad(this->params.GetLoad(), value);
        if ((value % 2) == 0)
        {
          standardWhered.push_back(value);
        }
      }
      return standardWhered;
    },
    params.GetIterations(),
    this->standardName);

  this->LogBaseData();
}



TEST_P(WhereTimeTest, ListNumberTest)
{
  this->params = GetParam();
  this->params.SetCategory(TimeTestCategory::BuiltIn);

  std::vector<uint> dataSample = { 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 };
  std::list<uint> data;
  for (uint64_t i = 0; i < params.GetContainerSize(); i++)
  {
    data.push_back(dataSample[i % 12]);
  }

  ListInternalQueryable<uint> local = BuildQueryable(data);

  this->queryableStats = RunTimeAndLog(
    [&]()
    {
      local.Where([&](uint value)
      {
        this->ApplyLoad(this->params.GetLoad(), value);
        return (value % 2) == 0;
      });
    },
    params.GetIterations(),
    this->queryableName
  );

  this->standardStats = RunTimeAndLog(
    [&]()
    {
      std::list<uint> standardWhered;
      for (uint value : data)
      {
        this->ApplyLoad(this->params.GetLoad(), value);
        if ((value % 2) == 0)
        {
          standardWhered.push_back(value);
        }
      }
      return standardWhered;
    },
    params.GetIterations(),
    this->standardName);

  this->LogBaseData();
}

TEST_P(WhereTimeTest, ListNumberCopyToQueryableListTest)
{
  this->params = GetParam();
  this->params.SetCategory(TimeTestCategory::BuiltIn);

  std::vector<uint> dataSample = { 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 };
  std::list<uint> data;
  for (uint64_t i = 0; i < params.GetContainerSize(); i++)
  {
    data.push_back(dataSample[i % 12]);
  }

  ListInternalQueryable<uint> local = BuildQueryable(data);

  this->queryableStats = RunTimeAndLog(
    [&]()
    {
      local = local.Where([&](uint value)
      {
        this->ApplyLoad(this->params.GetLoad(), value);
        return (value % 2) == 0;
      }).ToQueryableList();
    },
    params.GetIterations(),
    this->queryableName
  );

  this->standardStats = RunTimeAndLog(
    [&]()
    {
      std::list<uint> standardWhered;
      for (uint value : data)
      {
        this->ApplyLoad(this->params.GetLoad(), value);
        if ((value % 2) == 0)
        {
          standardWhered.push_back(value);
        }
      }
      return standardWhered;
    },
    params.GetIterations(),
    this->standardName);

  this->LogBaseData();
}

TEST_P(WhereTimeTest, ListNumberCopyToListTest)
{
  this->params = GetParam();
  this->params.SetCategory(TimeTestCategory::BuiltIn);

  std::vector<uint> dataSample = { 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 };
  std::list<uint> data;
  for (uint64_t i = 0; i < params.GetContainerSize(); i++)
  {
    data.push_back(dataSample[i % 12]);
  }

  ListInternalQueryable<uint> local = BuildQueryable(data);

  this->queryableStats = RunTimeAndLog(
    [&]()
    {
      std::list<uint> newData = local.Where([&](uint value)
      {
        this->ApplyLoad(this->params.GetLoad(), value);
        return (value % 2) == 0;
      }).ToList();
    },
    params.GetIterations(),
    this->queryableName
  );

  this->standardStats = RunTimeAndLog(
    [&]()
    {
      std::list<uint> standardWhered;
      for (uint value : data)
      {
        this->ApplyLoad(this->params.GetLoad(), value);
        if ((value % 2) == 0)
        {
          standardWhered.push_back(value);
        }
      }
      return standardWhered;
    },
    params.GetIterations(),
    this->standardName);

  this->LogBaseData();
}



TEST_P(WhereTimeTest, MultiSetNumberTest)
{
  this->params = GetParam();
  this->params.SetCategory(TimeTestCategory::BuiltIn);

  std::vector<uint> dataSample = { 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 };
  std::multiset<uint> data;
  for (uint64_t i = 0; i < params.GetContainerSize(); i++)
  {
    data.insert(dataSample[i % 12]);
  }

  MultiSetInternalQueryable<uint> local = BuildQueryable(data);

  this->queryableStats = RunTimeAndLog(
    [&]()
    {
      local.Where([&](uint value)
      {
        this->ApplyLoad(this->params.GetLoad(), value);
        return (value % 2) == 0;
      });
    },
    params.GetIterations(),
    this->queryableName
  );

  this->standardStats = RunTimeAndLog(
    [&]()
    {
      std::multiset<uint> standardWhered;
      for (uint value : data)
      {
        this->ApplyLoad(this->params.GetLoad(), value);
        if ((value % 2) == 0)
        {
          standardWhered.insert(value);
        }
      }
      return standardWhered;
    },
    params.GetIterations(),
    this->standardName);

  this->LogBaseData();
}

TEST_P(WhereTimeTest, MultiSetNumberCopyToQueryableMultiSetTest)
{
  this->params = GetParam();
  this->params.SetCategory(TimeTestCategory::BuiltIn);

  std::vector<uint> dataSample = { 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 };
  std::multiset<uint> data;
  for (uint64_t i = 0; i < params.GetContainerSize(); i++)
  {
    data.insert(dataSample[i % 12]);
  }

  MultiSetInternalQueryable<uint> local = BuildQueryable(data);

  this->queryableStats = RunTimeAndLog(
    [&]()
    {
      local = local.Where([&](uint value)
      {
        this->ApplyLoad(this->params.GetLoad(), value);
        return (value % 2) == 0;
      }).ToQueryableMultiSet();
    },
    params.GetIterations(),
    this->queryableName
  );

  this->standardStats = RunTimeAndLog(
    [&]()
    {
      std::multiset<uint> standardWhered;
      for (uint value : data)
      {
        this->ApplyLoad(this->params.GetLoad(), value);
        if ((value % 2) == 0)
        {
          standardWhered.insert(value);
        }
      }
      return standardWhered;
    },
    params.GetIterations(),
    this->standardName);

  this->LogBaseData();
}

TEST_P(WhereTimeTest, MultiSetNumberCopyToMultiSetTest)
{
  this->params = GetParam();
  this->params.SetCategory(TimeTestCategory::BuiltIn);

  std::vector<uint> dataSample = { 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 };
  std::multiset<uint> data;
  for (uint64_t i = 0; i < params.GetContainerSize(); i++)
  {
    data.insert(dataSample[i % 12]);
  }

  MultiSetInternalQueryable<uint> local = BuildQueryable(data);

  this->queryableStats = RunTimeAndLog(
    [&]()
    {
      std::multiset<uint> newData = local.Where([&](uint value)
      {
        this->ApplyLoad(this->params.GetLoad(), value);
        return (value % 2) == 0;
      }).ToMultiSet();
    },
    params.GetIterations(),
    this->queryableName
  );

  this->standardStats = RunTimeAndLog(
    [&]()
    {
      std::multiset<uint> standardWhered;
      for (uint value : data)
      {
        this->ApplyLoad(this->params.GetLoad(), value);
        if ((value % 2) == 0)
        {
          standardWhered.insert(value);
        }
      }
      return standardWhered;
    },
    params.GetIterations(),
    this->standardName);

  this->LogBaseData();
}






TEST_P(WhereTimeTest, VectorNumberTest)
{
  this->params = GetParam();
  this->params.SetCategory(TimeTestCategory::BuiltIn);

  std::vector<uint> dataSample = { 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 };
  std::vector<uint> data;
  for (uint64_t i = 0; i < params.GetContainerSize(); i++)
  {
    data.push_back(dataSample[i % 12]);
  }

  VectorInternalQueryable<uint> local = BuildQueryable(data);

  this->queryableStats = RunTimeAndLog(
    [&]()
    {
      local.Where([&](uint value)
      {
        this->ApplyLoad(this->params.GetLoad(), value);
        return (value % 2) == 0;
      });
    },
    params.GetIterations(),
    this->queryableName
  );

  this->standardStats = RunTimeAndLog(
    [&]()
    {
      std::vector<uint> standardWhered;
      for (uint value : data)
      {
        this->ApplyLoad(this->params.GetLoad(), value);
        if ((value % 2) == 0)
        {
          standardWhered.push_back(value);
        }
      }
      return standardWhered;
    },
    params.GetIterations(),
    this->standardName);

  this->LogBaseData();
}

TEST_P(WhereTimeTest, VectorNumberCopyToQueryableVectorTest)
{
  this->params = GetParam();
  this->params.SetCategory(TimeTestCategory::BuiltIn);

  std::vector<uint> dataSample = { 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 };
  std::vector<uint> data;
  for (uint64_t i = 0; i < params.GetContainerSize(); i++)
  {
    data.push_back(dataSample[i % 12]);
  }

  VectorInternalQueryable<uint> local = BuildQueryable(data);

  this->queryableStats = RunTimeAndLog(
    [&]()
    {
      local = local.Where([&](uint value)
      {
        this->ApplyLoad(this->params.GetLoad(), value);
        return (value % 2) == 0;
      }).ToQueryableVector();
    },
    params.GetIterations(),
    this->queryableName
  );

  this->standardStats = RunTimeAndLog(
    [&]()
    {
      std::vector<uint> standardWhered;
      for (uint value : data)
      {
        this->ApplyLoad(this->params.GetLoad(), value);
        if ((value % 2) == 0)
        {
          standardWhered.push_back(value);
        }
      }
      return standardWhered;
    },
    params.GetIterations(),
    this->standardName);

  this->LogBaseData();
}

TEST_P(WhereTimeTest, VectorNumberCopyToVectorTest)
{
  this->params = GetParam();
  this->params.SetCategory(TimeTestCategory::BuiltIn);

  std::vector<uint> dataSample = { 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 };
  std::vector<uint> data;
  for (uint64_t i = 0; i < params.GetContainerSize(); i++)
  {
    data.push_back(dataSample[i % 12]);
  }

  VectorInternalQueryable<uint> local = BuildQueryable(data);

  this->queryableStats = RunTimeAndLog(
    [&]()
    {
      std::vector<uint> newData = local.Where([&](uint value)
      {
        this->ApplyLoad(this->params.GetLoad(), value);
        return (value % 2) == 0;
      }).ToVector();
    },
    params.GetIterations(),
    this->queryableName
  );

  this->standardStats = RunTimeAndLog(
    [&]()
    {
      std::vector<uint> standardWhered;
      for (uint value : data)
      {
        this->ApplyLoad(this->params.GetLoad(), value);
        if ((value % 2) == 0)
        {
          standardWhered.push_back(value);
        }
      }
      return standardWhered;
    },
    params.GetIterations(),
    this->standardName);

  this->LogBaseData();
}

INSTANTIATE_TEST_SUITE_P(
  WhereTimeTesting,
  WhereTimeTest,
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
