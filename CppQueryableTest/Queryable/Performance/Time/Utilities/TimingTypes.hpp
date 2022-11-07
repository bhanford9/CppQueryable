#ifndef CPPQUERYABLE_CPPQUERYABLETEST_QUERYABLE_PERFORMANCE_TIME_UTILITIES_TIMINGTYPES_H
#define CPPQUERYABLE_CPPQUERYABLETEST_QUERYABLE_PERFORMANCE_TIME_TUTILITIES_IMINGTYPES_H

#include <chrono>
#include <iomanip>

using THighRes = std::chrono::high_resolution_clock;
using TTime = std::chrono::time_point<THighRes>;
using TNanos = std::chrono::nanoseconds;
using TMicros = std::chrono::microseconds;
using TMillis = std::chrono::milliseconds;
using TSecs = std::chrono::seconds;
using TMins = std::chrono::minutes;
using THours = std::chrono::hours;
using TDurationNanos = std::chrono::duration<double, std::nano>;
using TDurationMicros = std::chrono::duration<double, std::micro>;
using TDurationMillis = std::chrono::duration<double, std::milli>;
using TDurationSecs = std::chrono::duration<double>;
using TDurationMins = std::chrono::duration<double, std::ratio<60>>;
using TDurationHours = std::chrono::duration<double, std::ratio<360>>;

#endif
