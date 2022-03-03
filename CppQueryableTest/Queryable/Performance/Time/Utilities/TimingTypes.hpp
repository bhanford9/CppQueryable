#ifndef CPPQUERYABLE_CPPQUERYABLETEST_QUERYABLE_PERFORMANCE_TIME_UTILITIES_TIMINGTYPES_H
#define CPPQUERYABLE_CPPQUERYABLETEST_QUERYABLE_PERFORMANCE_TIME_TUTILITIES_IMINGTYPES_H

#include <chrono>
#include <iomanip>

typedef std::chrono::high_resolution_clock THighRes;
typedef std::chrono::time_point<THighRes> TTime;
typedef std::chrono::nanoseconds TNanos;
typedef std::chrono::microseconds TMicros;
typedef std::chrono::milliseconds TMillis;
typedef std::chrono::seconds TSecs;
typedef std::chrono::minutes TMins;
typedef std::chrono::hours THours;
typedef std::chrono::duration<double, std::nano> TDurationNanos;
typedef std::chrono::duration<double, std::micro> TDurationMicros;
typedef std::chrono::duration<double, std::milli> TDurationMillis;
typedef std::chrono::duration<double> TDurationSecs;
typedef std::chrono::duration<double, std::ratio<60>> TDurationMins;
typedef std::chrono::duration<double, std::ratio<360>> TDurationHours;

#endif
