#ifndef CPPQUERYABLE_CPPQUERYABLETEST_QUERYABLE_PERFORMANCE_TIME_UTILITIES_TIMETESTPARAMS_TIMETESTPARAMS_H
#define CPPQUERYABLE_CPPQUERYABLETEST_QUERYABLE_PERFORMANCE_TIME_UTILITIES_TIMETESTPARAMS_TIMETESTPARAMS_H

#include <string>

#include "../TimeStats.hpp"
#include "TimeTestCategory.hpp"
#include "TriggerType.hpp"

class TimeTestParams
{
private:
  std::string id = "";
  TimeTestCategory category = TimeTestCategory::Other;
  std::string containerType = "";
  std::string methodName = "";
  TriggerType triggerType = TriggerType::NotApplicable;

  uint64_t containerSize = 0;
  uint64_t iterations = 0;
  uint16_t load = 1;

  TimeStats standardStats;
  TimeStats queryableStats;

  bool doLog = true;
  bool doRecordStats = false;
  std::string statsFilePath = "";

public:
  TimeTestParams() :
    id(""),
    category(TimeTestCategory::Other),
    containerType(""),
    methodName(""),
    triggerType(TriggerType::NotApplicable),
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
    uint64_t iterations,
    uint64_t containerSize,
    uint16_t load = 1,
    TriggerType triggerType = TriggerType::NotApplicable,
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
  TimeTestCategory GetCategory() const { return this->category; }
  std::string GetContainerType() const { return this->containerType; }
  std::string GetMethodName() const { return this->methodName; }
  TriggerType GetTriggerType() const { return this->triggerType; }

  uint64_t GetContainerSize() const { return this->containerSize; }
  uint64_t GetIterations() const { return this->iterations; }
  uint16_t GetLoad() const { return this->load; }

  TimeStats GetStandardStats() const { return this->standardStats; }
  TimeStats GetQueryableStats() const { return this->queryableStats; }

  bool GetDoLog() const { return this->doLog; }
  bool GetDoRecordStats() const { return this->doRecordStats; }
  std::string GetStatsFilePath() const { return this->statsFilePath; }

  void SetId(std::string id) { this->id = id; }
  void SetCategory(TimeTestCategory category) { this->category = category; }
  void SetContainerType(std::string containerType) { this->containerType = containerType; }
  void SetMethodName(std::string methodName) { this->methodName = methodName; }
  void SetTriggerType(TriggerType type) { this->triggerType = type; }

  void SetContainerSize(uint64_t containerSize) { this->containerSize = containerSize; }
  void SetIterations(uint64_t iterations) { this->iterations = iterations; }
  void SetLOod(uint16_t load) { this->load = load; }

  void SetStandardStats(TimeStats stats) { this->standardStats = stats; }
  void SetQueryableStats(TimeStats stats) { this->queryableStats = stats; }

  void SetDoLog(bool doLog) { this->doLog = doLog; }
  void SetDoRecordStats(bool doRecordStats) { this->doRecordStats = doRecordStats; }
  void SetStatsFilePath(std::string statsFilePath) { this->statsFilePath = statsFilePath; }
};

#endif
