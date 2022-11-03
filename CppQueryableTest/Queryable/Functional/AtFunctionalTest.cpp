#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "../../../Queryable/QueryBuilder.hpp"


using namespace QueryBuilder;

class AtFunctionalTest : public ::testing::Test
{
protected:
  size_t atIndex = 9;
  size_t expectedUnorderedAt = 34;
  size_t expectedOrderedAt = 45;
  size_t expectedSetAt = 867;
  QueryableVector<size_t> queryable;

  AtFunctionalTest() :
    queryable(BuildQueryable(std::vector<size_t>({ 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 })))
  {
  }

  virtual void SetUp() override
  {
  }

  virtual void TearDown() override {}
};

// TEST_F(AtFunctionalTest, AtVectorUninitialized)
// {
//   IQueryable<Person> emptyQueryable;
//
//   try
//   {
//     Person p = emptyQueryable.At(this->atIndex);
//   }
//   catch (std::runtime_error& ex)
//   {
//     ASSERT_STREQ(ex.what(), "Specified index was outside the bounds of the container");
//   }
// }

TEST_F(AtFunctionalTest, AtVectorIndexToHigh)
{
  try
  {
    this->queryable.At(this->queryable.Count());
  }
  catch (std::runtime_error& ex)
  {
    ASSERT_STREQ(ex.what(), "Specified index was outside the bounds of the container");
  }
}

TEST_F(AtFunctionalTest, AtDeque)
{
  const size_t value = BuildQueryable(this->queryable.ToDeque()).At(this->atIndex);
  ASSERT_EQ(this->expectedUnorderedAt, value);
}

TEST_F(AtFunctionalTest, AtList)
{
  const size_t value = BuildQueryable(this->queryable.ToList()).At(this->atIndex);
  ASSERT_EQ(this->expectedUnorderedAt, value);
}

TEST_F(AtFunctionalTest, AtMap)
{
  const std::pair<const size_t, std::string> value = BuildQueryable(
    this->queryable.ToMap<size_t, std::string>(
      [](const size_t value) { return value; },
      [](const size_t value) { return std::to_string(static_cast<double>(value) / 2.0); }))
      .At(this->atIndex);

  ASSERT_EQ(this->expectedSetAt, value.first);
  ASSERT_EQ(std::to_string(static_cast<double>(this->expectedSetAt) / 2.0), value.second);
}

TEST_F(AtFunctionalTest, AtMultiSet)
{
  const size_t value = BuildQueryable(this->queryable.ToMultiSet()).At(this->atIndex);
  ASSERT_EQ(this->expectedOrderedAt, value);
}

TEST_F(AtFunctionalTest, AtSet)
{
  const size_t value = BuildQueryable(this->queryable.ToSet()).At(this->atIndex);
  ASSERT_EQ(this->expectedSetAt, value);
}

TEST_F(AtFunctionalTest, AtVector)
{
  const size_t value = this->queryable.At(this->atIndex);
  ASSERT_EQ(this->expectedUnorderedAt, value);
}

TEST_F(AtFunctionalTest, AtWhere)
{
  constexpr size_t expected = 8;
  const size_t value = this->queryable
                           .Where([](const size_t val) { return val % 2 == 0; })
                           .At(3);

  ASSERT_EQ(expected, value);
}
