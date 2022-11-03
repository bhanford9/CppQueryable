#include <gtest/gtest.h>

#include <array>
#include <deque>
#include <string>
#include <vector>

#include "../../../DataStructures/Person.hpp"


#include "../../../Queryable/QueryBuilder.hpp"

using namespace QueryBuilder;

class ForEachFunctionalTest : public ::testing::Test
{
protected:
    QueryableVector<size_t> queryable;

    ForEachFunctionalTest()
        : queryable(
            BuildQueryable(std::vector<size_t>({ 7, 4, 7, 4, 3, 76, 8, 45, 34, 76, 8, 867 })))
    {
    }

    virtual void SetUp() override
    {
    }

    template <typename TStoring, template<typename, typename ...> typename TIterable, typename
              TIterating, typename ...TArgs>
    void TestForEach(Queryable<TStoring, TIterable, TIterating, TArgs...> & localQueryable)
    {
        std::vector<TIterating> iterated;

        localQueryable.ForEach(
            [&](TIterating value)
            {
                iterated.push_back(value);
            });

        for (size_t i = 0; i < localQueryable.Count(); i++)
        {
            ASSERT_EQ(localQueryable.At(i), iterated[i]);
        }
    }

    virtual void TearDown() override
    {
    }
};

TEST_F(ForEachFunctionalTest, ForEachVectorUninitialized)
{
    const QueryableVector<Person> emptyQueryable(BuildQueryable(std::vector<Person>()));
    emptyQueryable.ForEach([](const Person & p) { throw std::runtime_error("Should not hit"); });
    ASSERT_TRUE(true);
}

TEST_F(ForEachFunctionalTest, ForEachVector)
{
    std::vector<size_t> iterated(this->queryable.Count(), 0);
    size_t i = 0;

    this->queryable.ForEach(
        [&](const size_t value)
        {
            iterated[i++] = value;
        });

    for (i = 0; i < this->queryable.Count(); i++)
    {
        ASSERT_EQ(this->queryable.At(i), iterated[i]);
    }
}

TEST_F(ForEachFunctionalTest, ForEachDeque)
{
    QueryableDeque<size_t> localQueryable = BuildQueryable(this->queryable.ToDeque());
    this->TestForEach(localQueryable);
}

TEST_F(ForEachFunctionalTest, ForEachList)
{
    QueryableList<size_t> localQueryable = BuildQueryable(this->queryable.ToList());
    this->TestForEach(localQueryable);
}

TEST_F(ForEachFunctionalTest, ForEachMap)
{
    QueryableMap<size_t, std::string> localQueryable = BuildQueryable(
        this->queryable.ToMap<size_t, std::string>(
            [](const size_t value) { return value; },
            [](const size_t value) { return std::to_string(static_cast<double>(value) / 2.0); }));
    this->TestForEach(localQueryable);
}

TEST_F(ForEachFunctionalTest, ForEachMultiSet)
{
    QueryableMultiSet<size_t> localQueryable = BuildQueryable(this->queryable.ToMultiSet());
    this->TestForEach(localQueryable);
}

TEST_F(ForEachFunctionalTest, ForEachSet)
{
    QueryableSet<size_t> localQueryable = BuildQueryable(this->queryable.ToSet());
    this->TestForEach(localQueryable);
}

TEST_F(ForEachFunctionalTest, ForEachWhere)
{
    QueryableVector<size_t> IQueryable = BuildQueryable(
        std::vector<size_t>({ 7, 0, 7, 2, 3, 4, 6, 45, 8, 1, 3, 10, 99, 199 }));

    constexpr int expectedCount = 6;
    int count = 0;
    IQueryable.Where([](const size_t value) { return value % 2 == 0; }).ForEach(
        [&](const size_t value) { ASSERT_EQ(count++ * 2, value); });

    ASSERT_EQ(expectedCount, count);
}
