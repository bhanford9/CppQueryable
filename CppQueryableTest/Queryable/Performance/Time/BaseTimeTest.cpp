#include <gtest/gtest.h>

#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>
#include <thread>

#include "Utilities/Duration.h"
#include "Utilities/TimeStats.h"
#include "Utilities/TimingTypes.h"
#include "Utilities/TimingUtilities.h"

using namespace TimingUtilities;

class BaseTimeTest : public ::testing::Test
{
protected:
  void SetUp() override
  {
  }

  void TearDown() override {}

  TTime Now()
  {
    return THighRes::now();
  }

  TTime PrintWithTime(std::string message, TTime previous = TTime())
  {
    TTime now = this->Now();
    previous = previous == TTime() ? now : previous;

    Duration epochElpased(now.time_since_epoch());
    uint64_t epochMicros = std::chrono::duration_cast<TMicros>(epochElpased.Get()).count();

    Duration elapsed(now - previous);
    uint64_t elapsedMicros = std::chrono::duration_cast<TMicros>(elapsed.Get()).count();

    std::cout << "[" << epochMicros << "] (Elapsed: ";
    std::cout << std::setfill(' ') << std::setw(10) << elapsedMicros;
    std::cout << " micros) " << message << std::endl;

    return now;
  }
};

TEST_F(BaseTimeTest, SetupTest)
{
  TTime previous = PrintWithTime("Starting Test");

  TimeStats stats = RunAndTime([]() { std::this_thread::sleep_for(TMillis(10)); }, 4);
  std::cout << stats.ToSecString() << std::endl;

  PrintWithTime("Ending Test", previous);
}
