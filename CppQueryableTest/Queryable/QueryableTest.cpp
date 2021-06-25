#include <gtest/gtest.h>

#include <iostream>

#include "../../Queryable/Queryable.h"

class QueryableTest : public ::testing::Test
{
 protected:
  void SetUp() override
  {
  }

  void TearDown() override {}
};

TEST(QueryableTest, DummyTest)
{
  std::cout << "test was ran" << std::endl;
  ASSERT_TRUE(true);
}
