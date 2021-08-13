#include <gtest/gtest.h>

#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>
#include <thread>

class BaseTimeTest : public ::testing::Test
{
protected:
  void SetUp() override
  {
  }

  void TearDown() override {}

  typedef std::chrono::high_resolution_clock THighRes;
  typedef std::chrono::time_point<THighRes> TTime;
  typedef std::chrono::duration<double> TDuration;
  typedef std::chrono::microseconds TMicros;
  typedef std::chrono::milliseconds TMillis;

  TTime Now()
  {
    return THighRes::now();
  }

  TTime PrintWithTime(std::string message, TTime previous = TTime())
  {
    TTime now = this->Now();
    previous = previous == TTime() ? now : previous;

    TDuration epochElpased = now.time_since_epoch();
    uint64_t epochMicros = std::chrono::duration_cast<TMicros>(epochElpased).count();

    TDuration elapsed = now - previous;
    uint64_t elapsedMicros = std::chrono::duration_cast<TMicros>(elapsed).count();

    std::cout << "[" << epochMicros << "] (Elapsed: ";
    std::cout << std::setfill(' ') << std::setw(10) << elapsedMicros;
    std::cout << " micros) " << message << std::endl;

    return now;
  }
};

TEST_F(BaseTimeTest, SetupTest)
{
  TTime previous = PrintWithTime("Starting Test");

  std::this_thread::sleep_for(TMillis(1000));

  PrintWithTime("Ending Test", previous);
}
