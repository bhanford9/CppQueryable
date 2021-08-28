#ifndef CPPQUERYABLE_CPPQUERYABLETEST_QUERYABLE_PERFORMANCE_TIME_UTILITIES_DURATION_H
#define CPPQUERYABLE_CPPQUERYABLETEST_QUERYABLE_PERFORMANCE_TIME_UTILITIES_DURATION_H

#include <chrono>
#include <cmath>
#include <ratio>
#include <sstream>
#include <string>
#include "TimingTypes.h"

class Duration
{
private:
  std::chrono::duration<double> duration;

  const uint HOUR_PER_DAY = 24;
  const uint MIN_PER_HOUR = 60;
  const uint SEC_PER_MIN = 60;
  const uint MILLI_PER_SEC = 1000;
  const uint MICRO_PER_MILLI = 1000;

  const uint NANO_PER_MICRO = 1000;
  const uint NANO_PER_MILLI = NANO_PER_MICRO * MICRO_PER_MILLI;
  const uint NANO_PER_SEC = NANO_PER_MILLI * MILLI_PER_SEC;
  const uint NANO_PER_MIN = NANO_PER_SEC * SEC_PER_MIN;

public:
  Duration() { }
  Duration(const Duration & duration) { this->duration = duration.Get(); }
  Duration(const std::chrono::duration<double> & duration) { this->duration = duration; }
  Duration(TTime start, TTime end) { this->Calculate(start, end); }

  static Duration Max() { return Duration(std::chrono::duration<double>::max()); }
  static Duration Min() { return Duration(std::chrono::duration<double>::min()); }

  std::chrono::duration<double> Get() const { return this->duration; }
  double Nanos() { return std::chrono::duration_cast<TNanos>(this->duration).count(); }
  double Micros() { return this->Nanos() / 1000.0; }
  double Millis() { return this->Micros() / 1000.0; }
  double Secs() { return this->Millis() / 1000.0; }
  double Mins() { return this->Secs() / 60.0; }
  std::string NanosStr() { return std::to_string(this->Nanos()); }
  std::string MicrosStr() { return std::to_string(this->Micros()); }
  std::string MillisStr() { return std::to_string(this->Millis()); }
  std::string SecsStr() { return std::to_string(this->Secs()); }
  std::string MinsStr() { return std::to_string(this->Mins()); }

  Duration * Calculate(TTime start, TTime end)
  {
    this->duration = end - start;
    return this;
  }

  std::string ToString()
  {
    double nanos = this->Nanos();

    int mins = std::floor(nanos / NANO_PER_MIN);
    nanos -= NANO_PER_MIN * mins;
    int secs = std::floor(nanos / NANO_PER_SEC);
    nanos -= NANO_PER_SEC * secs;
    int millis = std::floor(nanos / NANO_PER_MILLI);
    nanos -= NANO_PER_MILLI * millis;
    int micros = std::floor(nanos / NANO_PER_MICRO);
    nanos -= NANO_PER_MICRO * micros;

    std::stringstream stream;
    stream << std::setfill('0') << std::setw(2) << mins;
    std::string smins = stream.str();

    stream.str("");
    stream << std::setfill('0') << std::setw(2) << secs;
    std::string ssecs = stream.str();

    stream.str("");
    stream << std::setfill('0') << std::setw(3) << millis;
    std::string smillis = stream.str();

    stream.str("");
    stream << std::setfill('0') << std::setw(3) << micros;
    std::string smicros = stream.str();

    std::string snanos = std::to_string(nanos);

    return
      "\tDuration: " + smins + ":" + ssecs + ":" + smillis + ":" + smicros + ":" + snanos +
      "\n\tMinutes: " + smins +
      "\n\tSeconds: " + ssecs +
      "\n\tMilliseconds: " + smillis +
      "\n\tMicroseconds: " + smicros +
      "\n\tNanoseconds: " + snanos;
  }

  Duration operator+ (Duration other) const
  {
    return Duration(this->duration + other.Get());
  }

  Duration operator- (Duration other) const
  {
    return Duration(this->duration - other.Get());
  }

  Duration & operator+= (const Duration & other)
  {
    this->duration += other.Get();
    return *this;
  }

  Duration & operator-= (const Duration & other)
  {
    this->duration -= other.Get();
    return *this;
  }

  Duration operator/ (double divisor) const
  {
    return Duration(this->duration / divisor);
  }

  Duration & operator= (const Duration & other)
  {
    this->duration = other.Get();
    return *this;
  }
};

bool operator>(const Duration & lhs, const Duration & rhs)
{
  return lhs.Get() > rhs.Get();
}

bool operator<(const Duration & lhs, const Duration & rhs)
{
  return lhs.Get() < rhs.Get();
}

#endif
