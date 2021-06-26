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
  ASSERT_TRUE(true);
}
