#include <gtest/gtest.h>

#include <string>

#include "../../../DataStructures/Person.hpp"
#include "../../../DataStructures/PersonLibrary.hpp"

#include "../../../Queryable/QueryBuilder.hpp"

#include "Headers/AggregateFunctionalTest.hpp"

TEST_F(AggregateFunctionalGTest, AggregateUninitialized)
{
    this->AggregateUninitializedTest();
}

void AggregateFunctionalTest::AggregateUninitializedTest() const
{
    QueryableVector<Person> local(BuildQueryable(std::vector<Person>()));
    const std::string result = local.Aggregate<std::string>(
        [](const std::string & s, const Person & p)
        {
            return s + ", " + p.GetName();
        });

    ASSERT_STREQ("", result.c_str());
}


TEST_F(AggregateFunctionalGTest, AggregateSeededUninitialized)
{
    this->AggregateSeededUninitialized();
}

void AggregateFunctionalTest::AggregateSeededUninitialized() const
{
    std::string expected = "Hello World!";
    QueryableVector<Person> local(BuildQueryable(std::vector<Person>()));
    const std::string result = local.Aggregate<std::string>(
        [](const std::string & s, const Person & p)
        {
            return s + ", " + p.GetName();
        },
        &expected);

    ASSERT_STREQ(expected.c_str(), result.c_str());
}

TEST_F(AggregateFunctionalGTest, AggregateFinalizerUninitialized)
{
    this->AggregateFinalizerUninitialized();
}

void AggregateFunctionalTest::AggregateFinalizerUninitialized() const
{
    const std::string expected = "Names: ";
    QueryableVector<Person> local(BuildQueryable(std::vector<Person>()));
    const std::string result = local.Aggregate<std::string, std::string>(
        [](const std::string & s, const Person & p) { return s + ", " + p.GetName(); },
        [&](const std::string & output) -> std::string { return expected + output; });

    ASSERT_STREQ(expected.c_str(), result.c_str());
}

TEST_F(AggregateFunctionalGTest, AggregateFinalizerSeededUninitialized)
{
    this->AggregateFinalizerSeededUninitialized();
}

void AggregateFunctionalTest::AggregateFinalizerSeededUninitialized() const
{
    std::string expected = "Names: Hello World!";
    const std::string finalizer = "Names: ";
    const std::string seed = "Hello World!";
    QueryableVector<Person> local(BuildQueryable(std::vector<Person>()));
    const std::string result = local.Aggregate<std::string, std::string>(
        [](const std::string & s, const Person & p) { return s + ", " + p.GetName(); },
        [&](const std::string & output) -> std::string { return finalizer + seed; },
        &expected);

    ASSERT_STREQ(expected.c_str(), result.c_str());
}

TEST_F(AggregateFunctionalGTest, AggregateDeque)
{
    this->AggregateDeque();
}

void AggregateFunctionalTest::AggregateDeque() const
{
    const std::string expected =
        "Person 1 (Male) - Height: 73in\nPerson 10 (Female) - Height: 55in\nPerson 11 (Male) - Height: 68in\n";
    QueryableDeque<Person> local = BuildQueryable(this->people.ToDeque());
    const std::string result = local.Where(
        [](const Person & p)
        {
            return p.GetName().find("Person 1") != std::string::npos;
        }).Aggregate<std::string>(
        [](const std::string & s, const Person & p)
        {
            const std::string newStr = p.GetName() + " (" + (p.IsMale() ? "Male" : "Female") +
                ") - Height: " + std::to_string(p.GetHeight()) + "in";
            return s + newStr + "\n";
        });

    ASSERT_STREQ(expected.c_str(), result.c_str());
}

TEST_F(AggregateFunctionalGTest, AggregateList)
{
    this->AggregateList();
}

void AggregateFunctionalTest::AggregateList() const
{
    const std::string expected =
        "Person 1 (Male) - Height: 73in\nPerson 10 (Female) - Height: 55in\nPerson 11 (Male) - Height: 68in\n";
    QueryableList<Person> local = BuildQueryable(this->people.ToList());
    const std::string result = local.Where(
        [](const Person & p)
        {
            return p.GetName().find("Person 1") != std::string::npos;
        }).Aggregate<std::string>(
        [](const std::string & s, const Person & p)
        {
            const std::string newStr = p.GetName() + " (" + (p.IsMale() ? "Male" : "Female") +
                ") - Height: " + std::to_string(p.GetHeight()) + "in";
            return s + newStr + "\n";
        });

    ASSERT_STREQ(expected.c_str(), result.c_str());
}

TEST_F(AggregateFunctionalGTest, AggregateMap)
{
    this->AggregateMap();
}

void AggregateFunctionalTest::AggregateMap() const
{
    const std::string expected =
        "Person 1 (Male) - Height: 73in\nPerson 10 (Female) - Height: 55in\nPerson 11 (Male) - Height: 68in\n";
    QueryableMap<std::string, Person> local = BuildQueryable(
        this->people.ToMap<std::string, Person>(
            [](const Person & p) { return p.GetName(); },
            [](Person p) { return p; }));
    const std::string result = local.Where(
        [](const std::pair<const std::string, Person> & p)
        {
            return p.first.find("Person 1") != std::string::npos;
        }).Aggregate<std::string>(
        [](const std::string & s, const std::pair<const std::string, Person> & p)
        {
            const std::string newStr = p.first + " (" + (p.second.IsMale() ? "Male" : "Female") +
                ") - Height: " + std::to_string(p.second.GetHeight()) + "in";
            return s + newStr + "\n";
        });

    ASSERT_STREQ(expected.c_str(), result.c_str());
}

TEST_F(AggregateFunctionalGTest, AggregateMultiSet)
{
    this->AggregateMultiSet();
}

void AggregateFunctionalTest::AggregateMultiSet() const
{
    const std::string expected =
        "Person 1 (Male) - Height: 73in\nPerson 10 (Female) - Height: 55in\nPerson 11 (Male) - Height: 68in\n";
    QueryableMultiSet<Person> local = BuildQueryable(this->people.ToMultiSet());
    const std::string result = local.Where(
        [](const Person & p)
        {
            return p.GetName().find("Person 1") != std::string::npos;
        }).Aggregate<std::string>(
        [](const std::string & s, const Person & p)
        {
            const std::string newStr = p.GetName() + " (" + (p.IsMale() ? "Male" : "Female") +
                ") - Height: " + std::to_string(p.GetHeight()) + "in";
            return s + newStr + "\n";
        });

    ASSERT_STREQ(expected.c_str(), result.c_str());
}

TEST_F(AggregateFunctionalGTest, AggregateSet)
{
    this->AggregateSet();
}

void AggregateFunctionalTest::AggregateSet() const
{
    const std::string expected =
        "Person 1 (Male) - Height: 73in\nPerson 10 (Female) - Height: 55in\nPerson 11 (Male) - Height: 68in\n";
    QueryableSet<Person> local = BuildQueryable(this->people.ToSet());
    const std::string result = local.Where(
        [](const Person & p)
        {
            return p.GetName().find("Person 1") != std::string::npos;
        }).Aggregate<std::string>(
        [](const std::string & s, const Person & p)
        {
            const std::string newStr = p.GetName() + " (" + (p.IsMale() ? "Male" : "Female") +
                ") - Height: " + std::to_string(p.GetHeight()) + "in";
            return s + newStr + "\n";
        });

    ASSERT_STREQ(expected.c_str(), result.c_str());
}

TEST_F(AggregateFunctionalGTest, AggregateVector)
{
    this->AggregateVector();
}

void AggregateFunctionalTest::AggregateVector() const
{
    const std::string expected =
        "Person 1 (Male) - Height: 73in\nPerson 10 (Female) - Height: 55in\nPerson 11 (Male) - Height: 68in\n";
    QueryableVector<Person> local = BuildQueryable(this->people.ToVector());
    const std::string result = local.Where(
        [](const Person & p)
        {
            return p.GetName().find("Person 1") != std::string::npos;
        }).Aggregate<std::string>(
        [](const std::string & s, const Person & p)
        {
            const std::string newStr = p.GetName() + " (" + (p.IsMale() ? "Male" : "Female") +
                ") - Height: " + std::to_string(p.GetHeight()) + "in";
            return s + newStr + "\n";
        });

    ASSERT_STREQ(expected.c_str(), result.c_str());
}

TEST_F(AggregateFunctionalGTest, AggregateSeededFinalizerDeque)
{
    this->AggregateSeededFinalizerDeque();
}

void AggregateFunctionalTest::AggregateSeededFinalizerDeque() const
{
    std::string seed = "People: \n";
    const std::string finalizer = "\n---END---\n";
    const std::string expected = seed +
        "Person 1 (Male) - Height: 73in\nPerson 10 (Female) - Height: 55in\nPerson 11 (Male) - Height: 68in\n"
        + finalizer;
    QueryableDeque<Person> local = BuildQueryable(this->people.ToDeque());
    const std::string result = local.Where(
        [](const Person & p)
        {
            return p.GetName().find("Person 1") != std::string::npos;
        }).Aggregate<std::string, std::string>(
        [](const std::string & s, const Person & p)
        {
            const std::string newStr = p.GetName() + " (" + (p.IsMale() ? "Male" : "Female") +
                ") - Height: " + std::to_string(p.GetHeight()) + "in";
            return s + newStr + "\n";
        },
        [&](const std::string & str)
        {
            return str + finalizer;
        },
        &seed);

    ASSERT_STREQ(expected.c_str(), result.c_str());
}

TEST_F(AggregateFunctionalGTest, AggregateSeededFinalizerList)
{
    this->AggregateSeededFinalizerList();
}

void AggregateFunctionalTest::AggregateSeededFinalizerList() const
{
    std::string seed = "People: \n";
    const std::string finalizer = "\n---END---\n";
    const std::string expected = seed +
        "Person 1 (Male) - Height: 73in\nPerson 10 (Female) - Height: 55in\nPerson 11 (Male) - Height: 68in\n"
        + finalizer;
    QueryableList<Person> local = BuildQueryable(this->people.ToList());
    const std::string result = local.Where(
        [](const Person & p)
        {
            return p.GetName().find("Person 1") != std::string::npos;
        }).Aggregate<std::string, std::string>(
        [](const std::string & s, const Person & p)
        {
            const std::string newStr = p.GetName() + " (" + (p.IsMale() ? "Male" : "Female") +
                ") - Height: " + std::to_string(p.GetHeight()) + "in";
            return s + newStr + "\n";
        },
        [&](const std::string & str)
        {
            return str + finalizer;
        },
        &seed);

    ASSERT_STREQ(expected.c_str(), result.c_str());
}

TEST_F(AggregateFunctionalGTest, AggregateSeededFinalizerMultiSet)
{
    this->AggregateSeededFinalizerMultiSet();
}

void AggregateFunctionalTest::AggregateSeededFinalizerMultiSet() const
{
    std::string seed = "People: \n";
    const std::string finalizer = "\n---END---\n";
    const std::string expected = seed +
        "Person 1 (Male) - Height: 73in\nPerson 10 (Female) - Height: 55in\nPerson 11 (Male) - Height: 68in\n"
        + finalizer;
    QueryableMultiSet<Person> local = BuildQueryable(this->people.ToMultiSet());
    const std::string result = local.Where(
        [](const Person & p)
        {
            return p.GetName().find("Person 1") != std::string::npos;
        }).Aggregate<std::string, std::string>(
        [](const std::string & s, const Person & p)
        {
            const std::string newStr = p.GetName() + " (" + (p.IsMale() ? "Male" : "Female") +
                ") - Height: " + std::to_string(p.GetHeight()) + "in";
            return s + newStr + "\n";
        },
        [&](const std::string & str)
        {
            return str + finalizer;
        },
        &seed);

    ASSERT_STREQ(expected.c_str(), result.c_str());
}

TEST_F(AggregateFunctionalGTest, AggregateSeededFinalizerSet)
{
    this->AggregateSeededFinalizerSet();
}

void AggregateFunctionalTest::AggregateSeededFinalizerSet() const
{
    std::string seed = "People: \n";
    const std::string finalizer = "\n---END---\n";
    const std::string expected = seed +
        "Person 1 (Male) - Height: 73in\nPerson 10 (Female) - Height: 55in\nPerson 11 (Male) - Height: 68in\n"
        + finalizer;
    QueryableSet<Person> local = BuildQueryable(this->people.ToSet());
    const std::string result = local.Where(
        [](const Person & p)
        {
            return p.GetName().find("Person 1") != std::string::npos;
        }).Aggregate<std::string, std::string>(
        [](const std::string & s, const Person & p)
        {
            const std::string newStr = p.GetName() + " (" + (p.IsMale() ? "Male" : "Female") +
                ") - Height: " + std::to_string(p.GetHeight()) + "in";
            return s + newStr + "\n";
        },
        [&](const std::string & str)
        {
            return str + finalizer;
        },
        &seed);

    ASSERT_STREQ(expected.c_str(), result.c_str());
}

TEST_F(AggregateFunctionalGTest, AggregateSeededFinalizerVector)
{
    this->AggregateSeededFinalizerVector();
}

void AggregateFunctionalTest::AggregateSeededFinalizerVector() const
{
    std::string seed = "People: \n";
    const std::string finalizer = "\n---END---\n";
    const std::string expected = seed +
        "Person 1 (Male) - Height: 73in\nPerson 10 (Female) - Height: 55in\nPerson 11 (Male) - Height: 68in\n"
        + finalizer;
    QueryableVector<Person> local = BuildQueryable(this->people.ToVector());
    const std::string result = local.Where(
        [](const Person & p)
        {
            return p.GetName().find("Person 1") != std::string::npos;
        }).Aggregate<std::string, std::string>(
        [](const std::string & s, const Person & p)
        {
            const std::string newStr = p.GetName() + " (" + (p.IsMale() ? "Male" : "Female") +
                ") - Height: " + std::to_string(p.GetHeight()) + "in";
            return s + newStr + "\n";
        },
        [&](const std::string & str)
        {
            return str + finalizer;
        },
        &seed);

    ASSERT_STREQ(expected.c_str(), result.c_str());
}

// TODO --> Where and Select with Aggregate methods
