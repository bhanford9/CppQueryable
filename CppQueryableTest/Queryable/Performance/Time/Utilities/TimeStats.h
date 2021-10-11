#ifndef CPPQUERYABLE_CPPQUERYABLETEST_QUERYABLE_PERFORMANCE_TIME_UTILITIES_TIMESTATS_H
#define CPPQUERYABLE_CPPQUERYABLETEST_QUERYABLE_PERFORMANCE_TIME_UTILITIES_TIMESTATS_H

#include <chrono>
#include <cmath>
#include <iostream>
#include <ratio>
#include <string>

#include "Duration.h"
#include "TimingTypes.h"

class TimeStats
{
private:
  std::string name = "";
  ulong count = 0;
  Duration total;
  Duration max = Duration::Min();
  Duration min = Duration::Max();

public:
  TimeStats() {}
  explicit TimeStats(std::string name)
  {
    this->name = name;
  }
  TimeStats(const TimeStats & other)
  {
    this->name = other.name;
    this->count = other.count;
    this->total = other.total;
    this->max = other.max;
    this->min = other.min;
  }

  void Add(const Duration & time)
  {
    this->total += time;
    this->count++;

    if (time > max) this->max = time;
    if (time < min) this->min = time;
  }

  std::string GetName() const { return this->name; }
  ulong GetIterations() const { return this->count; }
  Duration GetTotal() const { return this->total; }
  Duration GetAverage() const { return this->total / this->count; }
  Duration GetMax() const { return this->max; }
  Duration GetMin() const { return this->min; }
  Duration GetRange() const { return this->max - this->min; }

  std::string ToString()
  {
    return
      "Total Iterations: " + std::to_string(this->count) +
      "\nTotal Time: " + this->total.ToString() +
      "\nAverage Time: " + this->GetAverage().ToString() +
      "\nFastest Time: " + this->min.ToString() +
      "\nSlowest Time: " + this->max.ToString() +
      "\nRange of Times: " + this->GetRange().ToString();
  }

  std::string ToSecString()
  {
    return
      "\tTotal Iterations: " + std::to_string(this->count) +
      "\n\tTotal Time:     " + this->total.SecsStr() +
      " seconds\n\tAverage Time:   " + this->GetAverage().SecsStr() +
      " seconds\n\tFastest Time:   " + this->min.SecsStr() +
      " seconds\n\tSlowest Time:   " + this->max.SecsStr() +
      " seconds\n\tRange of Times: " + this->GetRange().SecsStr();
  }

  std::string ToMilliString()
  {
    return
      "\tTotal Iterations: " + std::to_string(this->count) +
      "\n\tTotal Time:     " + this->total.MillisStr() +
      " milliseconds\n\tAverage Time:   " + this->GetAverage().MillisStr() +
      " milliseconds\n\tFastest Time:   " + this->min.MillisStr() +
      " milliseconds\n\tSlowest Time:   " + this->max.MillisStr() +
      " milliseconds\n\tRange of Times: " + this->GetRange().MillisStr();
  }

  std::string ToRatioString(
    std::string numeratorName,
    std::string denominatorName,
    double numeratorAverage,
    double denominatorAverage)
  {
    return
      "\tTotal Iterations: " + std::to_string(this->count) +
      "\n\tTotal Time:     " + this->CreateRatioString(numeratorName, denominatorName, this->total.Secs()) +
      "\n\tAverage Time:   " + this->CreateRatioString(numeratorName, denominatorName, numeratorAverage / denominatorAverage) +
      "\n\tFastest Time:   " + this->CreateRatioString(numeratorName, denominatorName, this->min.Secs()) +
      "\n\tSlowest Time:   " + this->CreateRatioString(numeratorName, denominatorName, this->max.Secs());
  }

  TimeStats Difference(const TimeStats & other) const
  {
    TimeStats result;
    result.name = this->name + " - " + other.GetName();
    result.count = this->count;
    result.total = this->total - other.total;
    result.min = this->min - other.min;
    result.max = this->max - other.max;
    return result;
  }

  TimeStats Ratio(const TimeStats & other) const
  {
    TimeStats result;
    result.name = this->name + " / " + other.GetName();
    result.count = this->count;
    result.total = this->total / other.total;
    result.min = this->min / other.min;
    result.max = this->max / other.max;
    return result;
  }

private:
  std::string CreateRatioString(
    std::string numeratorName,
    std::string denominatorName,
    double ratio) const
  {
    return
      ratio >= 1 ?
      denominatorName + " is " + std::to_string(ratio) + " times faster than " + numeratorName :
      numeratorName + " is " + std::to_string(1/ratio) + " times faster than " + denominatorName;
  }
};

#endif
