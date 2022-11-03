#include <gtest/gtest.h>

#include <array>
#include <deque>
#include <string>
#include <vector>

#include "../../../DataStructures/Person.hpp"

#include "../../../Queryable/QueryBuilder.hpp"


using namespace QueryBuilder;

class MinFunctionalTest : public ::testing::Test
{
protected:
    size_t expectedMin = 1;
    char expectedMinChar = 'a';
    std::string expectedMinStr = "abc";
    QueryableVector<size_t> queryable;
    QueryableVector<std::string> queryableStrings;

    MinFunctionalTest()
        : queryable(
              BuildQueryable(
                  std::vector<size_t>({ 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, expectedMin, 867, 12 }))),
          queryableStrings(
              BuildQueryable(std::vector<std::string>({ "nbc", "fox", "abc", "cbs", "the cw" })))
    {
    }

    virtual void SetUp() override
    {
    }

    virtual void TearDown() override
    {
    }
};

TEST_F(MinFunctionalTest, MinItemUninitialized)
{
    const QueryableVector<Person> emptyQueryable(BuildQueryable(std::vector<Person>()));
    const Person min = emptyQueryable.MinItem<double>([](const Person & p) { return p.GetAge(); });
    ASSERT_DOUBLE_EQ(0.0, min.GetAge());
}

TEST_F(MinFunctionalTest, MinUninitialized)
{
    const QueryableVector<Person> emptyQueryable(BuildQueryable(std::vector<Person>()));
    const auto min = emptyQueryable.Min<double>([&](const Person & p) { return p.GetAge(); });
    ASSERT_DOUBLE_EQ(0.0, min);
}

// TEST_F(MinFunctionalTest, MinUninitializedDefault)
// {
//   QueryableVector<double> emptyQueryable(BuildQueryable(std::vector<double>()));
//   double min = emptyQueryable.Min();
//   ASSERT_DOUBLE_EQ(0.0, min);
// }

TEST_F(MinFunctionalTest, MinSeededUninitialized)
{
    constexpr double seed = 9;
    const QueryableVector<Person> emptyQueryable(BuildQueryable(std::vector<Person>()));
    const auto min = emptyQueryable.Min<double>(
        [](const Person & p) { return p.GetAge(); },
        seed);
    ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinSeededUninitializedDefault)
{
    constexpr double seed = 9;
    const QueryableVector<double> emptyQueryable(BuildQueryable(std::vector<double>()));
    const double min = emptyQueryable.Min(seed);
    ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinItemString)
{
    const std::string min = this->queryableStrings.MinItem<char>(
        [](const std::string & str) { return str[0]; });
    ASSERT_STREQ(expectedMinStr.c_str(), min.c_str());
}

TEST_F(MinFunctionalTest, MinString)
{
    const char min = this->queryableStrings.Min<char>([](const std::string & str) { return str[0]; });
    ASSERT_EQ(expectedMinChar, min);
}

TEST_F(MinFunctionalTest, MinSmallerSeedString)
{
    constexpr char seed = 'Z';
    const char min = this->queryableStrings.Min<char>([](const std::string & str) { return str[0]; }, seed);
    ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinLargerSeedString)
{
    constexpr char seed = 'c';
    const char min = this->queryableStrings.Min<char>([](const std::string & str) { return str[0]; }, seed);
    ASSERT_EQ(expectedMinChar, min);
}

TEST_F(MinFunctionalTest, MinItemDeque)
{
    const QueryableDeque<size_t> local = BuildQueryable(this->queryable.ToDeque());
    const auto min = local.MinItem<size_t>([](const size_t value) { return value; });
    ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinDeque)
{
    const QueryableDeque<size_t> local = BuildQueryable(this->queryable.ToDeque());
    const auto min = local.Min<size_t>([](const size_t value) { return value; });
    ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinDequeDefault)
{
    const QueryableDeque<size_t> local = BuildQueryable(this->queryable.ToDeque());
    const size_t min = local.Min();
    ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinSeededLowerDeque)
{
    constexpr size_t seed = 0;
    const QueryableDeque<size_t> local = BuildQueryable(this->queryable.ToDeque());
    const auto min = local.Min<size_t>([](const size_t value) { return value; }, seed);
    ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinSeededLowerDequeDefault)
{
    constexpr size_t seed = 0;
    const QueryableDeque<size_t> local = BuildQueryable(this->queryable.ToDeque());
    const size_t min = local.Min(seed);
    ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinSeededHigherDeque)
{
    const size_t seed = expectedMin + 1;
    const QueryableDeque<size_t> local = BuildQueryable(this->queryable.ToDeque());
    const auto min = local.Min<size_t>([](const size_t value) { return value; }, seed);
    ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinSeededHigherDequeDefault)
{
    const size_t seed = expectedMin + 1;
    const QueryableDeque<size_t> local = BuildQueryable(this->queryable.ToDeque());
    const size_t min = local.Min(seed);
    ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinItemList)
{
    const QueryableList<size_t> local = BuildQueryable(this->queryable.ToList());
    const auto min = local.MinItem<size_t>([](const size_t value) { return value; });
    ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinList)
{
    const QueryableList<size_t> local = BuildQueryable(this->queryable.ToList());
    const auto min = local.Min<size_t>([](const size_t value) { return value; });
    ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinListDefault)
{
    const QueryableList<size_t> local = BuildQueryable(this->queryable.ToList());
    const size_t min = local.Min();
    ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinSeededLowerList)
{
    constexpr size_t seed = 0;
    const QueryableList<size_t> local = BuildQueryable(this->queryable.ToList());
    const auto min = local.Min<size_t>([](const size_t value) { return value; }, seed);
    ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinSeededLowerListDefault)
{
    constexpr size_t seed = 0;
    const QueryableList<size_t> local = BuildQueryable(this->queryable.ToList());
    const size_t min = local.Min(seed);
    ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinSeededHigherList)
{
    const size_t seed = expectedMin + 1;
    const QueryableList<size_t> local = BuildQueryable(this->queryable.ToList());
    const auto min = local.Min<size_t>([](const size_t value) { return value; }, seed);
    ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinSeededHigherListDefault)
{
    const size_t seed = expectedMin + 1;
    const QueryableList<size_t> local = BuildQueryable(this->queryable.ToList());
    const size_t min = local.Min(seed);
    ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinItemMultiSet)
{
    const QueryableMultiSet<size_t> local = BuildQueryable(this->queryable.ToMultiSet());
    const auto min = local.MinItem<size_t>([](const size_t value) { return value; });
    ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinMultiSet)
{
    const QueryableMultiSet<size_t> local = BuildQueryable(this->queryable.ToMultiSet());
    const auto min = local.Min<size_t>([](const size_t value) { return value; });
    ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinMultiSetDefault)
{
    const QueryableMultiSet<size_t> local = BuildQueryable(this->queryable.ToMultiSet());
    const size_t min = local.Min();
    ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinSeededLowerMultiSet)
{
    constexpr size_t seed = 0;
    const QueryableMultiSet<size_t> local = BuildQueryable(this->queryable.ToMultiSet());
    const auto min = local.Min<size_t>([](const size_t value) { return value; }, seed);
    ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinSeededLowerMultiSetDefault)
{
    constexpr size_t seed = 0;
    const QueryableMultiSet<size_t> local = BuildQueryable(this->queryable.ToMultiSet());
    const size_t min = local.Min(seed);
    ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinSeededHigherMultiSet)
{
    const size_t seed = expectedMin + 1;
    const QueryableMultiSet<size_t> local = BuildQueryable(this->queryable.ToMultiSet());
    const auto min = local.Min<size_t>([](const size_t value) { return value; }, seed);
    ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinSeededHigherMultiSetDefault)
{
    const size_t seed = expectedMin + 1;
    const QueryableMultiSet<size_t> local = BuildQueryable(this->queryable.ToMultiSet());
    const size_t min = local.Min(seed);
    ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinItemSet)
{
    const QueryableSet<size_t> local = BuildQueryable(this->queryable.ToSet());
    const auto min = local.MinItem<size_t>([](const size_t value) { return value; });
    ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinSet)
{
    const QueryableSet<size_t> local = BuildQueryable(this->queryable.ToSet());
    const auto min = local.Min<size_t>([](const size_t value) { return value; });
    ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinSetDefault)
{
    const QueryableSet<size_t> local = BuildQueryable(this->queryable.ToSet());
    const size_t min = local.Min();
    ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinSeededLowerSet)
{
    constexpr size_t seed = 0;
    const QueryableSet<size_t> local = BuildQueryable(this->queryable.ToSet());
    const auto min = local.Min<size_t>([](const size_t value) { return value; }, seed);
    ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinSeededLowerSetDefault)
{
    constexpr size_t seed = 0;
    const QueryableSet<size_t> local = BuildQueryable(this->queryable.ToSet());
    const size_t min = local.Min(seed);
    ASSERT_EQ(seed, min);
}

TEST_F(MinFunctionalTest, MinSeededHigherSet)
{
    const size_t seed = expectedMin + 1;
    const QueryableSet<size_t> local = BuildQueryable(this->queryable.ToSet());
    const auto min = local.Min<size_t>([](const size_t value) { return value; }, seed);
    ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinSeededHigherSetDefault)
{
    const size_t seed = expectedMin + 1;
    const QueryableSet<size_t> local = BuildQueryable(this->queryable.ToSet());
    const size_t min = local.Min(seed);
    ASSERT_EQ(this->expectedMin, min);
}

TEST_F(MinFunctionalTest, MinWhere)
{
    constexpr size_t expected = 12;
    const auto min = this->queryable.Where([](const size_t value) { return value > 10; }).Min<size_t>(
        [](const size_t value) { return value; });
    ASSERT_EQ(expected, min);
}

TEST_F(MinFunctionalTest, MinWhereDefault)
{
    constexpr size_t expected = 12;
    const size_t min = this->queryable.Where([](const size_t value) { return value > 10; }).Min();
    ASSERT_EQ(expected, min);
}
