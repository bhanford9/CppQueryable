#ifndef CPPQUERYABLE_CPPQUERYABLETEST_QUERYABLE_PERFORMANCE_TIME_UTILITIES_DURATION_H
#define CPPQUERYABLE_CPPQUERYABLETEST_QUERYABLE_PERFORMANCE_TIME_UTILITIES_DURATION_H

#include <chrono>
#include <cmath>
#include <iostream>
#include <ratio>
#include <sstream>
#include <string>
#include "TimingTypes.hpp"

class Duration
{
private:
  std::chrono::duration<double> duration;

  const size_t HOUR_PER_DAY = 24;
  const size_t MIN_PER_HOUR = 60;
  const size_t SEC_PER_MIN = 60;
  const size_t MILLI_PER_SEC = 1000;
  const size_t MICRO_PER_MILLI = 1000;

  const size_t NANO_PER_MICRO = 1000;
  const size_t NANO_PER_MILLI = NANO_PER_MICRO * MICRO_PER_MILLI;
  const size_t NANO_PER_SEC = NANO_PER_MILLI * MILLI_PER_SEC;
  const size_t NANO_PER_MIN = NANO_PER_SEC * SEC_PER_MIN;

public:
  Duration() { }
  Duration(double duration) { this->duration = std::chrono::duration<double>(duration); }
  Duration(const Duration & duration) { this->duration = duration.duration; }
  Duration(const std::chrono::duration<double> & duration) { this->duration = duration; }
  Duration(TTime start, TTime end) { this->Calculate(start, end); }

  static Duration Max() { return Duration(std::chrono::duration<double>::max()); }
  static Duration Min() { return Duration(std::chrono::duration<double>::min()); }

  std::chrono::duration<double> Get() const { return this->duration; }
  double Nanos() const { return std::chrono::duration_cast<TNanos>(this->duration).count(); }
  double Micros() const { return this->Nanos() / 1000.0; }
  double Millis() const { return this->Micros() / 1000.0; }
  double Secs() const { return this->Millis() / 1000.0; }
  double Mins() const { return this->Secs() / 60.0; }
  std::string NanosStr() const { return std::to_string(this->Nanos()); }
  std::string MicrosStr() const { return std::to_string(this->Micros()); }
  std::string MillisStr() const { return std::to_string(this->Millis()); }
  std::string SecsStr() const { return std::to_string(this->Secs()); }
  std::string MinsStr() const { return std::to_string(this->Mins()); }

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

  Duration operator/ (Duration divisor) const
  {
    Duration result(TDurationSecs(this->Nanos() / divisor.Nanos()));
    return result;
  }

  Duration & operator= (const Duration & other)
  {
    this->duration = other.Get();
    return *this;
  }

  bool operator>(const Duration & rhs) const
  {
    return this->Get() > rhs.Get();
  }

  bool operator<(const Duration & rhs) const
  {
    return this->Get() < rhs.Get();
  }
};



#endif
