#ifndef CPPQUERYABLE_CPPQUERYABLETEST_QUERYABLE_PERFORMANCE_TIME_UTILITIES_TIMINGUTILITIES_H
#define CPPQUERYABLE_CPPQUERYABLETEST_QUERYABLE_PERFORMANCE_TIME_UTILITIES_TIMINGUTILITIES_H

#include <chrono>
#include <functional>
#include <iomanip>
#include <iostream>
#include <string>

#include "Duration.hpp"
#include "TimeStats.hpp"
#include "TimingTypes.hpp"

namespace TimingUtilities
{
  Duration RunAndTime(std::function<void()> action)
  {
    TTime start = THighRes::now();
    action();
    TTime end = THighRes::now();

    Duration duration(start, end);
    return duration;
  }

  TimeStats RunAndTime(std::function<void()> action, ulong iterations, std::string name = "")
  {
    TimeStats stats(name);

    for (ulong i = 0; i < iterations; i++)
    {
      stats.Add(RunAndTime(action));
    }

    return stats;
  }

  template<typename T>
  Duration RunAndTime(std::function<void(T*)> action, T args)
  {
    TTime start = THighRes::now();
    action(&args);
    TTime end = THighRes::now();

    Duration duration(start, end);
    return duration;
  }

  template<typename T>
  TimeStats RunAndTime(std::function<void(T*)> action, ulong iterations, T args, std::string name = "")
  {
    TimeStats stats(name);

    for (ulong i = 0; i < iterations; i++)
    {
      stats.Add(RunAndTime(action, args));
    }

    return stats;
  }

  // void RunTimeAndLog(std::function<void()> action, std::string name = "")
  // {
  //   if (name != "")
  //   {
  //     std::cout << name << std::endl;
  //   }
  //
  //   std::cout << RunAndTime(action).ToString() << std::endl;
  // }

  TimeStats RunTimeAndLog(std::function<void()> action, ulong iterations, std::string name = "")
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
  void RunTimeAndLog(std::function<void(T*)> action, T args, std::string name = "")
  {
    if (name != "")
    {
      std::cout << name << std::endl;
    }

    std::cout << RunAndTime(action, args, name).ToString() << std::endl;
  }

  template<typename T>
  TimeStats RunTimeAndLog(std::function<void(T*)> action, ulong iterations, T args, std::string name = "")
  {
    if (name != "")
    {
      std::cout << name << std::endl;
    }

    TimeStats stats = RunAndTime(action, iterations, args, name);
    std::cout << stats.ToMilliString() << std::endl;
    return stats;
  }

  void CompareAndLog(const TimeStats & numerator, const TimeStats & denominator)
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
