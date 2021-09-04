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

  static TimeStats RunAndTime(std::function<void()> action, ulong iterations, std::string name = "")
  {
    TimeStats stats(name);

    for (ulong i = 0; i < iterations; i++)
    {
      stats.Add(RunAndTime(action));
    }

    return stats;
  }

  template<typename T>
  static Duration RunAndTime(std::function<void(T*)> action, T args)
  {
    TTime start = THighRes::now();
    action(&args);
    TTime end = THighRes::now();

    Duration duration(start, end);
    return duration;
  }

  template<typename T>
  static TimeStats RunAndTime(std::function<void(T*)> action, ulong iterations, T args, std::string name = "")
  {
    TimeStats stats(name);

    for (ulong i = 0; i < iterations; i++)
    {
      stats.Add(RunAndTime(action, args));
    }

    return stats;
  }

  // static void RunTimeAndLog(std::function<void()> action, std::string name = "")
  // {
  //   if (name != "")
  //   {
  //     std::cout << name << std::endl;
  //   }
  //
  //   std::cout << RunAndTime(action).ToString() << std::endl;
  // }

  static TimeStats RunTimeAndLog(std::function<void()> action, ulong iterations, std::string name = "")
  {
    if (name != "")
    {
      std::cout << name << std::endl;
    }

    TimeStats stats = RunAndTime(action, iterations, name);
    std::cout << stats.ToMilliString() << std::endl;
    return stats;
  }

  template<typename T>
  static void RunTimeAndLog(std::function<void(T*)> action, T args, std::string name = "")
  {
    if (name != "")
    {
      std::cout << name << std::endl;
    }

    std::cout << RunAndTime(action, args, name).ToString() << std::endl;
  }

  template<typename T>
  static TimeStats RunTimeAndLog(std::function<void(T*)> action, ulong iterations, T args, std::string name = "")
  {
    if (name != "")
    {
      std::cout << name << std::endl;
    }

    TimeStats stats = RunAndTime(action, iterations, args, name);
    std::cout << stats.ToMilliString() << std::endl;
    return stats;
  }

  static void CompareAndLog(const TimeStats & numerator, const TimeStats & denominator)
  {
    std::cout << numerator.GetName() + " VS " + denominator.GetName() << std::endl;
    std::cout << numerator
      .Ratio(denominator)
      .ToRatioString(
        numerator.GetName(),
        denominator.GetName(),
        numerator.GetAverage().Secs(),
        denominator.GetAverage().Secs())
      << std::endl;
  }
};

#endif
