#ifndef CPPQUERYABLE_CPPQUERYABLETEST_QUERYABLE_PERFORMANCE_TIME_UTILITIES_TIMETESTPARAMS_H
#define CPPQUERYABLE_CPPQUERYABLETEST_QUERYABLE_PERFORMANCE_TIME_UTILITIES_TIMETESTPARAMS_H

#include <string>

#include "TriggerType.h"

class TimeTestParams
{
private:
  uint64_t iterations = 0;
  uint64_t containerSize = 0;
  bool doLog = true;
  bool doRecordStats = false;
  std::string statsFilePath = "";
  TriggerType triggerType = TriggerType::NotApplicable;

public:
  TimeTestParams() { }
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

  uint64_t GetIterations() const { return this->iterations; }
  uint64_t GetContainerSize() const { return this->containerSize; }
  bool GetDoLog() const { return this->doLog; }
  bool GetDoRecordStats() const { return this->doRecordStats; }
  std::string GetStatsFilePath() const { return this->statsFilePath; }
  TriggerType GetTriggerType() const { return this->triggerType; }

  void SetIterations(uint64_t iterations) { this->iterations = iterations; }
  void SetContainerSize(uint64_t containerSize) { this->containerSize = containerSize; }
  void SetDoLog(bool doLog) { this->doLog = doLog; }
  void SetDoRecordStats(bool doRecordStats) { this->doRecordStats = doRecordStats; }
  void SetStatsFilePath(std::string statsFilePath) { this->statsFilePath = statsFilePath; }
  void SetTriggerType(TriggerType type) { this->triggerType = type; }
};

#endif
