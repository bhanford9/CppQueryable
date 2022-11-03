#include <gtest/gtest.h>

#include <array>
#include <deque>
#include <string>
#include <vector>

#include "../../../DataStructures/Person.hpp"

#include "../../../Queryable/QueryBuilder.hpp"


using namespace QueryBuilder;

class MaxFunctionalTest : public ::testing::Test
{
protected:
    size_t expectedMax = 867;
    char expectedMaxChar = 't';
    std::string expectedMaxStr = "the cw";
    QueryableVector<size_t> queryable;
    QueryableVector<std::string> queryableStrings;

    MaxFunctionalTest()
        : queryable(
              BuildQueryable(
                  std::vector<size_t>({ 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, expectedMax, 1, 12 }))),
          queryableStrings(
              BuildQueryable(std::vector<std::string>({ "nbc", "fox", "abc", "cbs", "the cw" })))
    {
    }

    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

TEST_F(MaxFunctionalTest, MaxItemUninitialized)
{
    const QueryableVector<Person> emptyQueryable(BuildQueryable(std::vector<Person>()));
    const Person max = emptyQueryable.MaxItem<double>([](const Person & p) { return p.GetAge(); });

    ASSERT_DOUBLE_EQ(0.0, max.GetAge());
}

TEST_F(MaxFunctionalTest, MaxUninitialized)
{
    const QueryableVector<Person> emptyQueryable(BuildQueryable(std::vector<Person>()));
    const double max = emptyQueryable.Max<double>([&](const Person & p) { return p.GetAge(); });
    ASSERT_DOUBLE_EQ(0.0, max);
}

// TEST_F(MaxFunctionalTest, MaxUninitializedDefault)
// {
//   QueryableVector<double> emptyQueryable(BuildQueryable(std::vector<double>()));
//   double max = emptyQueryable.Max();
//   ASSERT_DOUBLE_EQ(0.0, max);
// }

TEST_F(MaxFunctionalTest, MaxSeededUninitialized)
{
    const double seed = 9;
    const QueryableVector<Person> emptyQueryable(BuildQueryable(std::vector<Person>()));
    const double max = emptyQueryable.Max<double>(
        [](const Person & p) { return p.GetAge(); },
        seed);
    ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxSeededUninitializedDefault)
{
    const double seed = 9;
    const QueryableVector<double> emptyQueryable(BuildQueryable(std::vector<double>()));
    const double max = emptyQueryable.Max(seed);
    ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxItemString)
{
    const std::string max = this->queryableStrings.MaxItem<char>(
        [](std::string str) { return str[0]; });
    ASSERT_STREQ(expectedMaxStr.c_str(), max.c_str());
}

TEST_F(MaxFunctionalTest, MaxString)
{
    const char max = this->queryableStrings.Max<char>([](std::string str) { return str[0]; });
    ASSERT_EQ(expectedMaxChar, max);
}

TEST_F(MaxFunctionalTest, MaxSmallerSeedString)
{
    const char seed = 'Z';
    const char max = this->queryableStrings.Max<char>([](std::string str) { return str[0]; }, seed);
    ASSERT_EQ(expectedMaxChar, max);
}

TEST_F(MaxFunctionalTest, MaxLargerSeedString)
{
    const char seed = 'v';
    const char max = this->queryableStrings.Max<char>([](std::string str) { return str[0]; }, seed);
    ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxItemDeque)
{
    const QueryableDeque<size_t> local = BuildQueryable(this->queryable.ToDeque());
    const size_t max = local.MaxItem<size_t>([](size_t value) { return value; });
    ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxDeque)
{
    const QueryableDeque<size_t> local = BuildQueryable(this->queryable.ToDeque());
    const size_t max = local.Max<size_t>([](size_t value) { return value; });
    ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxDequeDefault)
{
    const QueryableDeque<size_t> local = BuildQueryable(this->queryable.ToDeque());
    const size_t max = local.Max();
    ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxSeededLowerDeque)
{
    const size_t seed = this->expectedMax + 1;
    const QueryableDeque<size_t> local = BuildQueryable(this->queryable.ToDeque());
    const size_t max = local.Max<size_t>([](size_t value) { return value; }, seed);
    ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxSeededLowerDequeDefault)
{
    const size_t seed = this->expectedMax + 1;
    const QueryableDeque<size_t> local = BuildQueryable(this->queryable.ToDeque());
    const size_t max = local.Max(seed);
    ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxSeededHigherDeque)
{
    const size_t seed = this->expectedMax - 1;
    const QueryableDeque<size_t> local = BuildQueryable(this->queryable.ToDeque());
    const size_t max = local.Max<size_t>([](size_t value) { return value; }, seed);
    ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxSeededHigherDequeDefault)
{
    const size_t seed = this->expectedMax - 1;
    const QueryableDeque<size_t> local = BuildQueryable(this->queryable.ToDeque());
    const size_t max = local.Max(seed);
    ASSERT_EQ(this->expectedMax, max);
}


TEST_F(MaxFunctionalTest, MaxItemList)
{
    const QueryableList<size_t> local = BuildQueryable(this->queryable.ToList());
    const size_t max = local.Max<size_t>([](size_t value) { return value; });
    ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxList)
{
    const QueryableList<size_t> local = BuildQueryable(this->queryable.ToList());
    const size_t max = local.Max<size_t>([](size_t value) { return value; });
    ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxListDefault)
{
    const QueryableList<size_t> local = BuildQueryable(this->queryable.ToList());
    const size_t max = local.Max();
    ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxSeededLowerList)
{
    const size_t seed = this->expectedMax + 1;
    const QueryableList<size_t> local = BuildQueryable(this->queryable.ToList());
    const size_t max = local.Max<size_t>([](size_t value) { return value; }, seed);
    ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxSeededLowerListDefault)
{
    const size_t seed = this->expectedMax + 1;
    const QueryableList<size_t> local = BuildQueryable(this->queryable.ToList());
    const size_t max = local.Max(seed);
    ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxSeededHigherList)
{
    const size_t seed = this->expectedMax - 1;
    const QueryableList<size_t> local = BuildQueryable(this->queryable.ToList());
    const size_t max = local.Max<size_t>([](size_t value) { return value; }, seed);
    ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxSeededHigherListDefault)
{
    const size_t seed = this->expectedMax - 1;
    const QueryableList<size_t> local = BuildQueryable(this->queryable.ToList());
    const size_t max = local.Max(seed);
    ASSERT_EQ(this->expectedMax, max);
}


TEST_F(MaxFunctionalTest, MaxItemMultiSet)
{
    const QueryableMultiSet<size_t> local = BuildQueryable(this->queryable.ToMultiSet());
    const size_t max = local.Max<size_t>([](size_t value) { return value; });
    ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxMultiSet)
{
    const QueryableMultiSet<size_t> local = BuildQueryable(this->queryable.ToMultiSet());
    const size_t max = local.Max<size_t>([](size_t value) { return value; });
    ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxMultiSetDefault)
{
    const QueryableMultiSet<size_t> local = BuildQueryable(this->queryable.ToMultiSet());
    const size_t max = local.Max();
    ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxSeededLowerMultiSet)
{
    const size_t seed = this->expectedMax + 1;
    const QueryableMultiSet<size_t> local = BuildQueryable(this->queryable.ToMultiSet());
    const size_t max = local.Max<size_t>([](size_t value) { return value; }, seed);
    ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxSeededLowerMultiSetDefault)
{
    const size_t seed = this->expectedMax + 1;
    const QueryableMultiSet<size_t> local = BuildQueryable(this->queryable.ToMultiSet());
    const size_t max = local.Max(seed);
    ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxSeededHigherMultiSet)
{
    const size_t seed = this->expectedMax - 1;
    const QueryableMultiSet<size_t> local = BuildQueryable(this->queryable.ToMultiSet());
    const size_t max = local.Max<size_t>([](size_t value) { return value; }, seed);
    ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxSeededHigherMultiSetDefault)
{
    const size_t seed = this->expectedMax - 1;
    const QueryableMultiSet<size_t> local = BuildQueryable(this->queryable.ToMultiSet());
    const size_t max = local.Max(seed);
    ASSERT_EQ(this->expectedMax, max);
}


TEST_F(MaxFunctionalTest, MaxItemSet)
{
    const QueryableSet<size_t> local = BuildQueryable(this->queryable.ToSet());
    const size_t max = local.MaxItem<size_t>([](size_t value) { return value; });
    ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxSet)
{
    const QueryableSet<size_t> local = BuildQueryable(this->queryable.ToSet());
    const size_t max = local.Max<size_t>([](size_t value) { return value; });
    ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxSetDefault)
{
    const QueryableSet<size_t> local = BuildQueryable(this->queryable.ToSet());
    const size_t max = local.Max();
    ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxSeededLowerSet)
{
    const size_t seed = this->expectedMax + 1;
    const QueryableSet<size_t> local = BuildQueryable(this->queryable.ToSet());
    const size_t max = local.Max<size_t>([](size_t value) { return value; }, seed);
    ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxSeededLowerSetDefault)
{
    const size_t seed = this->expectedMax + 1;
    const QueryableSet<size_t> local = BuildQueryable(this->queryable.ToSet());
    const size_t max = local.Max(seed);
    ASSERT_EQ(seed, max);
}

TEST_F(MaxFunctionalTest, MaxSeededHigherSet)
{
    const size_t seed = this->expectedMax - 1;
    const QueryableSet<size_t> local = BuildQueryable(this->queryable.ToSet());
    const size_t max = local.Max<size_t>([](size_t value) { return value; }, seed);
    ASSERT_EQ(this->expectedMax, max);
}


TEST_F(MaxFunctionalTest, MaxSeededHigherSetDefault)
{
    const size_t seed = this->expectedMax - 1;
    const QueryableSet<size_t> local = BuildQueryable(this->queryable.ToSet());
    const size_t max = local.Max(seed);
    ASSERT_EQ(this->expectedMax, max);
}

TEST_F(MaxFunctionalTest, MaxWhere)
{
    const size_t expected = 8;
    const size_t max = this->queryable.Where([](size_t value) { return value < 10; }).Max<size_t>(
        [](size_t value) { return value; });
    ASSERT_EQ(expected, max);
}

TEST_F(MaxFunctionalTest, MaxWhereDefault)
{
    const size_t expected = 8;
    const size_t max = this->queryable.Where([](size_t value) { return value < 10; }).Max();
    ASSERT_EQ(expected, max);
}
