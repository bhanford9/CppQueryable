#ifndef CPPQUERYABLE_CPPQUERYABLETEST_QUERYABLE_PERFORMANCE_TIME_UTILITIES_TIMETESTPARAMS_TIMETESTPARAMS_H
#define CPPQUERYABLE_CPPQUERYABLETEST_QUERYABLE_PERFORMANCE_TIME_UTILITIES_TIMETESTPARAMS_TIMETESTPARAMS_H

#include <string>

#include "TimeTestCategory.h"
#include "TriggerType.h"

class TimeTestParams
{
private:
  std::string id = "";
  TimeTestCategory category = TimeTestCategory::Other;
  std::string containerType = "";
  std::string methodName = "";
  TriggerType triggerType = TriggerType::NotApplicable;
  std::string executerName = "";

  uint64_t containerSize = 0;
  uint64_t iterations = 0;
  double totalMillis = 0;
  double averageMillis = 0;
  double fastestMillis = 0;
  double slowestMillis = 0;
  double rangeMillis = 0;

  bool doLog = true;
  bool doRecordStats = false;
  std::string statsFilePath = "";

public:
  TimeTestParams() { }
  TimeTestParams(const TimeTestParams & other)
  {
    this->id = other.id;
    this->category = other.category;
    this->containerType = other.containerType;
    this->methodName = other.methodName;
    this->triggerType = other.triggerType;
    this->executerName = other.executerName;

    this->containerSize = other.containerSize;
    this->iterations = other.iterations;
    this->totalMillis = other.totalMillis;
    this->averageMillis = other.averageMillis;
    this->fastestMillis = other.fastestMillis;
    this->slowestMillis = other.slowestMillis;
    this->rangeMillis = other.rangeMillis;

    this->doLog = other.doLog;
    this->doRecordStats = other.doRecordStats;
    this->statsFilePath = other.statsFilePath;
  }
  TimeTestParams(
    uint64_t iterations,
    uint64_t containerSize,
    TriggerType triggerType = TriggerType::NotApplicable,
    bool doLog = true,
    bool doRecordStats = false,
    std::string statsFilePath = "")
  {
    this->iterations = iterations;
    this->containerSize = containerSize;
    this->triggerType = triggerType;
    this->doLog = doLog;
    this->doRecordStats = doRecordStats;
    this->statsFilePath = statsFilePath;
  }

  std::string GetId() const { return this->id; }
  TimeTestCategory GetCategory() const { return this->category; }
  std::string GetContainerType() const { return this->containerType; }
  std::string GetMethodName() const { return this->methodName; }
  TriggerType GetTriggerType() const { return this->triggerType; }
  std::string GetExecuterName() const { return this->executerName; }

  uint64_t GetContainerSize() const { return this->containerSize; }
  uint64_t GetIterations() const { return this->iterations; }
  double GetTotalMillis() const { return this->totalMillis; }
  double GetAverageMillis() const { return this->averageMillis; }
  double GetFastestMillis() const { return this->fastestMillis; }
  double GetSlowestMillis() const { return this->slowestMillis; }
  double GetRangeMillis() const { return this->rangeMillis; }

  bool GetDoLog() const { return this->doLog; }
  bool GetDoRecordStats() const { return this->doRecordStats; }
  std::string GetStatsFilePath() const { return this->statsFilePath; }

  void SetId(std::string id) { this->id = id; }
  void SetCategory(TimeTestCategory category) { this->category = category; }
  void SetContainerType(std::string containerType) { this->containerType = containerType; }
  void SetMethodName(std::string methodName) { this->methodName = methodName; }
  void SetTriggerType(TriggerType type) { this->triggerType = type; }
  void SetExecuterName(std::string executerName) { this->executerName = executerName; }

  void SetContainerSize(uint64_t containerSize) { this->containerSize = containerSize; }
  void SetIterations(uint64_t iterations) { this->iterations = iterations; }
  void SetTotalMillis(double totalMillis) { this->totalMillis = totalMillis; }
  void SetAverageMillis(double averageMillis) { this->averageMillis = averageMillis; }
  void SetFastestMillis(double fastestMillis) { this->fastestMillis = fastestMillis; }
  void SetSlowestMillis(double slowestMillis) { this->slowestMillis = slowestMillis; }
  void SetRangeMillis(double raangeMillis) { this->rangeMillis = rangeMillis; }

  void SetDoLog(bool doLog) { this->doLog = doLog; }
  void SetDoRecordStats(bool doRecordStats) { this->doRecordStats = doRecordStats; }
  void SetStatsFilePath(std::string statsFilePath) { this->statsFilePath = statsFilePath; }
};

#endif
