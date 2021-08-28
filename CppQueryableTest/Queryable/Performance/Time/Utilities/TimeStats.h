#ifndef CPPQUERYABLE_CPPQUERYABLETEST_QUERYABLE_PERFORMANCE_TIME_UTILITIES_TIMESTATS_H
#define CPPQUERYABLE_CPPQUERYABLETEST_QUERYABLE_PERFORMANCE_TIME_UTILITIES_TIMESTATS_H

#include <chrono>
#include <cmath>
#include <ratio>
#include <string>

#include "Duration.h"
#include "TimingTypes.h"

class TimeStats
{
private:
  ulong count;
  Duration total;
  Duration max = Duration::Min();
  Duration min = Duration::Max();

public:
  TimeStats() {}
  TimeStats(const TimeStats & other)
  {
    this->count = other.GetIterations();
    this->total = other.GetTotal();
    this->max = other.GetMax();
    this->min = other.GetMin();
  }

  void Add(const Duration & time)
  {
    this->total += time;
    this->count++;

    if (time > max) this->max = time;
    if (time < min) this->min = time;
  }

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
      "\n\tTotal Time: " + this->total.MillisStr() +
      " milliseconds\n\tAverage Time: " + this->GetAverage().MillisStr() +
      " milliseconds\n\tFastest Time: " + this->min.MillisStr() +
      " milliseconds\n\tSlowest Time: " + this->max.MillisStr() +
      " milliseconds\n\tRange of Times: " + this->GetRange().MillisStr();
  }
};

#endif
