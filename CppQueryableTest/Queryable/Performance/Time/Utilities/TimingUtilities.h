#ifndef CPPQUERYABLE_CPPQUERYABLETEST_QUERYABLE_PERFORMANCE_TIME_UTILITIES_TIMINGUTILITIES_H
#define CPPQUERYABLE_CPPQUERYABLETEST_QUERYABLE_PERFORMANCE_TIME_UTILITIES_TIMINGUTILITIES_H

#include <chrono>
#include <functional>
#include <iomanip>
#include <iostream>
#include <string>

#include "Duration.h"
#include "TimeStats.h"
#include "TimingTypes.h"

namespace TimingUtilities
{
  static Duration RunAndTime(std::function<void()> action)
  {
    TTime start = THighRes::now();
    action();
    TTime end = THighRes::now();
    Duration duration(start, end);
    return duration;
  }

  static TimeStats RunAndTime(std::function<void()> action, ulong iterations)
  {
    TimeStats stats;
    for (ulong i = 0; i < iterations; i++)
      stats.Add(RunAndTime(action));
    return stats;
  }
};

#endif
