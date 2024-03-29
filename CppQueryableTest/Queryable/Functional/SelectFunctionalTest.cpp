#include <gtest/gtest.h>

#include <array>
#include <deque>
#include <iostream>
#include <string>
#include <vector>

#include "../../../DataStructures/Gender.hpp"
#include "../../../DataStructures/Person.hpp"
#include "../../../DataStructures/PersonLibrary.hpp"

#include "../../../Queryable/QueryBuilder.hpp"

using namespace QueryBuilder;

class SelectFunctionalTest : public ::testing::Test
{
protected:
    PersonLibrary personLibrary;
    QueryableVector<size_t> queryable;
    QueryableVector<Person> people;

    SelectFunctionalTest()
        : personLibrary(),
          queryable(
              BuildQueryable(
                  std::vector<size_t>({ 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 867, 1, 12 }))),
          people(BuildQueryable(this->personLibrary.GetPeople()))
    {
    }

    virtual void SetUp() override
    {
    }

    virtual void TearDown() override
    {
    }
};

// TEST_F(SelectFunctionalTest, SelectUninitialized)
// {
//   IQueryable<Person> local(BuildQueryable(std::vector<Person>()));
//   IQueryable<std::string> result = local
//     .Select<std::string>([](Person p) { return p.GetName(); });
//   ASSERT_EQ(0, result.Count());
// }

TEST_F(SelectFunctionalTest, DequeDefaultOut)
{
    QueryableDeque<Person> local = BuildQueryable(this->people.ToDeque());
    QueryableVector<Gender> result = local.Select<Gender>(
        [](const Person & p) { return p.GetGender(); });

    ASSERT_EQ(local.Count(), result.Count());

    size_t i = 0;
    local.ForEach(
        [&](const Person & p)
        {
            ASSERT_TRUE(p.GetGender() == result.At(i++));
        });
}

TEST_F(SelectFunctionalTest, ListDefaultOut)
{
    QueryableList<Person> local = BuildQueryable(this->people.ToList());
    QueryableVector<Gender> result = local.Select<Gender>(
        [](const Person & p) { return p.GetGender(); });

    ASSERT_EQ(local.Count(), result.Count());

    size_t i = 0;
    local.ForEach(
        [&](const Person & p)
        {
            ASSERT_TRUE(p.GetGender() == result.At(i++));
        });
}

TEST_F(SelectFunctionalTest, MapDefaultOut)
{
    QueryableMap<std::string, Gender> local = BuildQueryable(
        this->people.ToMap<std::string, Gender>(
            [](const Person & p) { return p.GetName(); },
            [](const Person & p) { return p.GetGender(); }));
    QueryableVector<Gender> result = local.Select<Gender>(
        [](const std::pair<const std::string, Gender> & kvp) { return kvp.second; });

    ASSERT_EQ(local.Count(), result.Count());

    size_t i = 0;
    local.ForEach(
        [&](const std::pair<const std::string, Gender> & kvp)
        {
            ASSERT_TRUE(kvp.second == result.At(i++));
        });
}

TEST_F(SelectFunctionalTest, MultiSetDefaultOut)
{
    QueryableMultiSet<Person> local1 = BuildQueryable(this->people.ToMultiSet());
    QueryableMultiSet<Person> local2 = BuildQueryable(this->people.ToMultiSet());
    QueryableVector<double> ages = local1.Select<double>(
        [](const Person & p) { return p.GetAge(); });
    QueryableVector<std::string> names = local2.Select<std::string>(
        [](const Person & p) { return p.GetName(); });

    ASSERT_EQ(local1.Count(), ages.Count());
    ASSERT_EQ(local1.Count(), names.Count());

    size_t i = 0;
    local1.ForEach(
        [&](const Person &)
        {
            const std::string currentName = names.At(i);
            ASSERT_STREQ(local2.At(i++).GetName().c_str(), currentName.c_str());
        });
}

TEST_F(SelectFunctionalTest, SetDefaultOut)
{
    QueryableSet<Person> local1 = BuildQueryable(this->people.ToSet());

    std::cout << "-2" << std::endl;
    QueryableSet<Person> local2 = BuildQueryable(this->people.ToSet());
    std::cout << &"-1" << std::endl;
    QueryableVector<double> ages = local1.Select<double>(
        [](const Person & p) { return p.GetAge(); }).ToQueryable();
    std::cout << "0&" << std::endl;
    QueryableVector<std::string> names = local2.Select<std::string>(
        [](const Person & p) { return p.GetName(); }).ToQueryable();

    std::cout << "1" << std::endl;
    ASSERT_EQ(local2.Count(), names.Count());
    ASSERT_EQ(local1.Count(), names.Count());
    std::cout << "2" << std::endl;
    size_t i = 0;
    local2.ForEach(
        [&](const Person & p)
        {
            std::cout << i << std::endl;
            ASSERT_STREQ(p.GetName().c_str(), names.At(i++).c_str());
            // ASSERT_TRUE(p.GetName() == names.At(i++));
        });
}

TEST_F(SelectFunctionalTest, VectorDefaultOut)
{
    QueryableVector<Person> local = BuildQueryable(this->people.ToVector());
    QueryableVector<Gender> result = local.Select<Gender>(
        [](const Person & p) { return p.GetGender(); });

    ASSERT_EQ(local.Count(), result.Count());

    size_t i = 0;
    local.ForEach(
        [&](const Person & p)
        {
            ASSERT_TRUE(p.GetGender() == result.At(i++));
        });
}

TEST_F(SelectFunctionalTest, SelectWhere)
{
    QueryableVector<Person> local1 = BuildQueryable(this->people.ToVector());
    QueryableVector<Person> local2 = BuildQueryable(this->people.ToVector());

    QueryableVector<double> ages1 = local1.Select<double>(
        [](const Person & p) { return p.GetAge() / 10; }).Where(
        [](const double age) { return age > 3 && age < 8; });

    QueryableVector<double> ages2 = local2.Where(
        [](const Person & p) { return p.GetAge() > 30 && p.GetAge() < 80; }).Select<double>(
        [](const Person & p) { return p.GetAge() / 10; });

    ASSERT_EQ(5, ages1.Count());
    ASSERT_EQ(ages1.Count(), ages2.Count());

    size_t i = 0;
    ages1.ForEach([&](const double age) { ASSERT_EQ(age, ages2.At(i++)); });
}
