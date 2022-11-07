#ifndef CPPQUERYABLE_CPPQUERYABLETEST_QUERYABLE_PERFORMANCE_TIME_UTILITIES_TIMETESTPARAMS_TIMETESTPARAMS_H
#define CPPQUERYABLE_CPPQUERYABLETEST_QUERYABLE_PERFORMANCE_TIME_UTILITIES_TIMETESTPARAMS_TIMETESTPARAMS_H

#include <sstream>
#include <string>

#include "../TimeStats.hpp"
#include "TimeTestCategory.hpp"
#include "TriggerType.hpp"
#include "../../../../TestCaseParams/TestCaseParams.hpp"

class TimeTestParams : public TestCaseParams
{
private:
  std::string id = "";
  TimeTestCategory::Type category = TimeTestCategory::Type::Other;
  std::string containerType = "";
  std::string methodName = "";
  TriggerType::Type triggerType = TriggerType::Type::NotApplicable;

  size_t containerSize = 0;
  size_t iterations = 0;
  size_t load = 1;

  TimeStats standardStats;
  TimeStats queryableStats;

  bool doLog = true;
  bool doRecordStats = false;
  std::string statsFilePath = "";

public:
  TimeTestParams() :
    id(""),
    category(TimeTestCategory::Type::Other),
    containerType(""),
    methodName(""),
    triggerType(TriggerType::Type::NotApplicable),
    containerSize(0),
    iterations(0),
    load(1),
    standardStats(TimeStats()),
    queryableStats(TimeStats()),
    doLog(true),
    doRecordStats(false),
    statsFilePath("")
  {
  }
  TimeTestParams(const TimeTestParams & other) : TimeTestParams()
  {
    this->id = other.id;
    this->category = other.category;
    this->containerType = other.containerType;
    this->methodName = other.methodName;
    this->triggerType = other.triggerType;

    this->containerSize = other.containerSize;
    this->iterations = other.iterations;
    this->load = other.load;

    this->standardStats = other.standardStats;
    this->queryableStats = other.queryableStats;

    this->doLog = other.doLog;
    this->doRecordStats = other.doRecordStats;
    this->statsFilePath = other.statsFilePath;
  }
  TimeTestParams(
    size_t iterations,
    size_t containerSize,
    size_t load = 1,
    TriggerType::Type triggerType = TriggerType::Type::NotApplicable,
    bool doLog = true,
    bool doRecordStats = false) : TimeTestParams()
  {
    this->iterations = iterations;
    this->containerSize = containerSize;
    this->load = load;
    this->triggerType = triggerType;
    this->doLog = doLog;
    this->doRecordStats = doRecordStats;
  }

  std::string GetId() const { return this->id; }
  TimeTestCategory::Type GetCategory() const { return this->category; }
  std::string GetContainerType() const { return this->containerType; }
  std::string GetMethodName() const { return this->methodName; }
  TriggerType::Type GetTriggerType() const { return this->triggerType; }

  size_t GetContainerSize() const { return this->containerSize; }
  size_t GetIterations() const { return this->iterations; }
  size_t GetLoad() const { return this->load; }

  TimeStats GetStandardStats() const { return this->standardStats; }
  TimeStats GetQueryableStats() const { return this->queryableStats; }

  bool GetDoLog() const { return this->doLog; }
  bool GetDoRecordStats() const { return this->doRecordStats; }
  std::string GetStatsFilePath() const { return this->statsFilePath; }

  void SetId(std::string id) { this->id = id; }
  void SetCategory(TimeTestCategory::Type category) { this->category = category; }
  void SetContainerType(std::string containerType) { this->containerType = containerType; }
  void SetMethodName(std::string methodName) { this->methodName = methodName; }
  void SetTriggerType(TriggerType::Type type) { this->triggerType = type; }

  void SetContainerSize(size_t containerSize) { this->containerSize = containerSize; }
  void SetIterations(size_t iterations) { this->iterations = iterations; }
  void SetLOod(size_t load) { this->load = load; }

  void SetStandardStats(TimeStats stats) { this->standardStats = stats; }
  void SetQueryableStats(TimeStats stats) { this->queryableStats = stats; }

  void SetDoLog(bool doLog) { this->doLog = doLog; }
  void SetDoRecordStats(bool doRecordStats) { this->doRecordStats = doRecordStats; }
  void SetStatsFilePath(std::string statsFilePath) { this->statsFilePath = statsFilePath; }

  virtual std::string ToString() const override
  {
    std::stringstream str;
    str
      << "\tid: " << this->id << std::endl
      << "\tcategory: " << TimeTestCategory::GetCategoryName(this->category) << std::endl
      << "\tcontainerType: " << this->containerType << std::endl
      << "\tmethodName: " << this->methodName << std::endl
      << "\ttriggerType: " << TriggerType::GetTriggerName(this->triggerType) << std::endl
      << "\tcontainerSize: " << this->containerSize << std::endl
      << "\titerations: " << this->iterations << std::endl
      << "\tload: " << this->load << std::endl;

    return str.str();
  }

  std::ostream & operator<<(std::ostream & str) const
  {
    str << this->ToString();
    return str;
  }

  friend std::ostream & operator<<(std::ostream & str, const TimeTestParams & params)
  {
    str << params.ToString();
    return str;
  }
};

#endif
