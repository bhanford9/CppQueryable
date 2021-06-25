#include <gtest/gtest.h>

#include <iostream>

// include some dummy data structures
#include "../../../DataStructures/Animal.h"
#include "../../../DataStructures/Person.h"
#include "../../../DataStructures/People.h"

#include "../../../Queryable/Queryable.h"

class WherePerformanceTest : public ::testing::Test
{
 protected:
  void SetUp() override
  {
  }

  void TearDown() override {}
};

TEST(WherePerformanceTest, DummyTest)
{
  std::cout << "test was ran" << std::endl;
  ASSERT_TRUE(true);
}
