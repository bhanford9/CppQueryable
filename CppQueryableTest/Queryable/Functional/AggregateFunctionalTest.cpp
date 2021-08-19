#include <gtest/gtest.h>

#include <array>
#include <deque>
#include <exception>
#include <iostream>
#include <list>
#include <set>
#include <string>
#include <vector>

#include "../../../DataStructures/Gender.h"
#include "../../../DataStructures/Person.h"
#include "../../../DataStructures/PersonLibrary.h"

#include "../../../Queryable/QueryBuilder.h"
#include "../../../Queryable/QueryableVector.h"

using namespace QueryBuilder;

class AggregateFunctionalTest : public ::testing::Test
{
protected:
  PersonLibrary personLibrary;
  QueryableVector<Person> people;

  void SetUp() override
  {
    this->people = QueryableVector<Person>(this->personLibrary.GetPeople());
  }

  void TearDown() override {}
};

TEST_F(AggregateFunctionalTest, AggregateUninitialized)
{
  QueryableVector<Person> local;
  std::string result = local.Aggregate<std::string>([](std::string s, Person p)
  {
    return s + ", " + p.GetName();
  });

  ASSERT_STREQ("", result.c_str());
}

TEST_F(AggregateFunctionalTest, AggregateSeededUninitialized)
{
  std::string expected = "Hello World!";
  QueryableVector<Person> local;
  std::string result = local.Aggregate<std::string>([](std::string s, Person p)
  {
    return s + ", " + p.GetName();
  },
  &expected);

  ASSERT_STREQ(expected.c_str(), result.c_str());
}

TEST_F(AggregateFunctionalTest, AggregateFinalizerUninitialized)
{
  std::string expected = "Names: ";
  QueryableVector<Person> local;
  std::string result = local.Aggregate<std::string, std::string>(
    [](std::string s, Person p) { return s + ", " + p.GetName(); },
    [&](std::string output) -> std::string { return expected + output; });

  ASSERT_STREQ(expected.c_str(), result.c_str());
}

TEST_F(AggregateFunctionalTest, AggregateFinalizerSeededUninitialized)
{
  std::string expected = "Names: Hello World!";
  std::string finalizer = "Names: ";
  std::string seed = "Hello World!";
  QueryableVector<Person> local;
  std::string result = local.Aggregate<std::string, std::string>(
    [](std::string s, Person p) { return s + ", " + p.GetName(); },
    [&](std::string output) -> std::string { return finalizer + seed; },
    &expected);

  ASSERT_STREQ(expected.c_str(), result.c_str());
}

TEST_F(AggregateFunctionalTest, AggregateDeque)
{
  std::string expected = "Person 1 (Male) - Height: 73in\nPerson 10 (Female) - Height: 55in\nPerson 11 (Male) - Height: 68in\n";
  QueryableDeque<Person> local = BuildQueryable(this->people.ToDeque());
  std::string result = local
    .Where([](Person p) { return p.GetName().find("Person 1") != std::string::npos; })
    ->Aggregate<std::string>([](std::string s, Person p)
    {
      std::string newStr = p.GetName() + " (" +
        (p.IsMale() ? "Male" : "Female") +
        ") - Height: " + std::to_string(p.GetHeight()) + "in";
      return s + newStr + "\n";
    });

  ASSERT_STREQ(expected.c_str(), result.c_str());
}

TEST_F(AggregateFunctionalTest, AggregateList)
{
  std::string expected = "Person 1 (Male) - Height: 73in\nPerson 10 (Female) - Height: 55in\nPerson 11 (Male) - Height: 68in\n";
  QueryableList<Person> local = BuildQueryable(this->people.ToList());
  std::string result = local
    .Where([](Person p) { return p.GetName().find("Person 1") != std::string::npos; })
    ->Aggregate<std::string>([](std::string s, Person p)
    {
      std::string newStr = p.GetName() + " (" +
        (p.IsMale() ? "Male" : "Female") +
        ") - Height: " + std::to_string(p.GetHeight()) + "in";
      return s + newStr + "\n";
    });

  ASSERT_STREQ(expected.c_str(), result.c_str());
}

TEST_F(AggregateFunctionalTest, AggregateMultiSet)
{
  std::string expected = "Person 1 (Male) - Height: 73in\nPerson 10 (Female) - Height: 55in\nPerson 11 (Male) - Height: 68in\n";
  QueryableMultiSet<Person> local = BuildQueryable(this->people.ToMultiSet());
  std::string result = local
    .Where([](Person p) { return p.GetName().find("Person 1") != std::string::npos; })
    ->Aggregate<std::string>([](std::string s, Person p)
    {
      std::string newStr = p.GetName() + " (" +
        (p.IsMale() ? "Male" : "Female") +
        ") - Height: " + std::to_string(p.GetHeight()) + "in";
      return s + newStr + "\n";
    });

  ASSERT_STREQ(expected.c_str(), result.c_str());
}

TEST_F(AggregateFunctionalTest, AggregateSet)
{
  std::string expected = "Person 1 (Male) - Height: 73in\nPerson 10 (Female) - Height: 55in\nPerson 11 (Male) - Height: 68in\n";
  QueryableSet<Person> local = BuildQueryable(this->people.ToSet());
  std::string result = local
    .Where([](Person p) { return p.GetName().find("Person 1") != std::string::npos; })
    ->Aggregate<std::string>([](std::string s, Person p)
    {
      std::string newStr = p.GetName() + " (" +
        (p.IsMale() ? "Male" : "Female") +
        ") - Height: " + std::to_string(p.GetHeight()) + "in";
      return s + newStr + "\n";
    });

  ASSERT_STREQ(expected.c_str(), result.c_str());
}

TEST_F(AggregateFunctionalTest, AggregateVector)
{
  std::string expected = "Person 1 (Male) - Height: 73in\nPerson 10 (Female) - Height: 55in\nPerson 11 (Male) - Height: 68in\n";
  QueryableVector<Person> local = BuildQueryable(this->people.ToVector());
  std::string result = local
    .Where([](Person p) { return p.GetName().find("Person 1") != std::string::npos; })
    ->Aggregate<std::string>([](std::string s, Person p)
    {
      std::string newStr = p.GetName() + " (" +
        (p.IsMale() ? "Male" : "Female") +
        ") - Height: " + std::to_string(p.GetHeight()) + "in";
      return s + newStr + "\n";
    });

  ASSERT_STREQ(expected.c_str(), result.c_str());
}

TEST_F(AggregateFunctionalTest, AggregateSeededFinalizerDeque)
{
  std::string seed = "People: \n";
  std::string finalizer = "\n---END---\n";
  std::string expected = seed + "Person 1 (Male) - Height: 73in\nPerson 10 (Female) - Height: 55in\nPerson 11 (Male) - Height: 68in\n" + finalizer;
  QueryableDeque<Person> local = BuildQueryable(this->people.ToDeque());
  std::string result = local
    .Where([](Person p) { return p.GetName().find("Person 1") != std::string::npos; })
    ->Aggregate<std::string, std::string>(
      [](std::string s, Person p)
      {
        std::string newStr = p.GetName() + " (" +
          (p.IsMale() ? "Male" : "Female") +
          ") - Height: " + std::to_string(p.GetHeight()) + "in";
        return s + newStr + "\n";
      },
      [&](std::string str)
      {
        return str + finalizer;
      },
      &seed);

  ASSERT_STREQ(expected.c_str(), result.c_str());
}

TEST_F(AggregateFunctionalTest, AggregateSeededFinalizerList)
{
  std::string seed = "People: \n";
  std::string finalizer = "\n---END---\n";
  std::string expected = seed + "Person 1 (Male) - Height: 73in\nPerson 10 (Female) - Height: 55in\nPerson 11 (Male) - Height: 68in\n" + finalizer;
  QueryableList<Person> local = BuildQueryable(this->people.ToList());
  std::string result = local
    .Where([](Person p) { return p.GetName().find("Person 1") != std::string::npos; })
    ->Aggregate<std::string, std::string>([](std::string s, Person p)
    {
      std::string newStr = p.GetName() + " (" +
        (p.IsMale() ? "Male" : "Female") +
        ") - Height: " + std::to_string(p.GetHeight()) + "in";
      return s + newStr + "\n";
    },
    [&](std::string str)
    {
      return str + finalizer;
    },
    &seed);

  ASSERT_STREQ(expected.c_str(), result.c_str());
}

TEST_F(AggregateFunctionalTest, AggregateSeededFinalizerMultiSet)
{
  std::string seed = "People: \n";
  std::string finalizer = "\n---END---\n";
  std::string expected = seed + "Person 1 (Male) - Height: 73in\nPerson 10 (Female) - Height: 55in\nPerson 11 (Male) - Height: 68in\n" + finalizer;
  QueryableMultiSet<Person> local = BuildQueryable(this->people.ToMultiSet());
  std::string result = local
    .Where([](Person p) { return p.GetName().find("Person 1") != std::string::npos; })
    ->Aggregate<std::string, std::string>([](std::string s, Person p)
    {
      std::string newStr = p.GetName() + " (" +
        (p.IsMale() ? "Male" : "Female") +
        ") - Height: " + std::to_string(p.GetHeight()) + "in";
      return s + newStr + "\n";
    },
    [&](std::string str)
    {
      return str + finalizer;
    },
    &seed);

  ASSERT_STREQ(expected.c_str(), result.c_str());
}

TEST_F(AggregateFunctionalTest, AggregateSeededFinalizerSet)
{
  std::string seed = "People: \n";
  std::string finalizer = "\n---END---\n";
  std::string expected = seed + "Person 1 (Male) - Height: 73in\nPerson 10 (Female) - Height: 55in\nPerson 11 (Male) - Height: 68in\n" + finalizer;
  QueryableSet<Person> local = BuildQueryable(this->people.ToSet());
  std::string result = local
    .Where([](Person p) { return p.GetName().find("Person 1") != std::string::npos; })
    ->Aggregate<std::string, std::string>([](std::string s, Person p)
    {
      std::string newStr = p.GetName() + " (" +
        (p.IsMale() ? "Male" : "Female") +
        ") - Height: " + std::to_string(p.GetHeight()) + "in";
      return s + newStr + "\n";
    },
    [&](std::string str)
    {
      return str + finalizer;
    },
    &seed);

  ASSERT_STREQ(expected.c_str(), result.c_str());
}

TEST_F(AggregateFunctionalTest, AggregateSeededFinalizerVector)
{
  std::string seed = "People: \n";
  std::string finalizer = "\n---END---\n";
  std::string expected = seed + "Person 1 (Male) - Height: 73in\nPerson 10 (Female) - Height: 55in\nPerson 11 (Male) - Height: 68in\n" + finalizer;
  QueryableVector<Person> local = BuildQueryable(this->people.ToVector());
  std::string result = local
    .Where([](Person p) { return p.GetName().find("Person 1") != std::string::npos; })
    ->Aggregate<std::string, std::string>([](std::string s, Person p)
    {
      std::string newStr = p.GetName() + " (" +
        (p.IsMale() ? "Male" : "Female") +
        ") - Height: " + std::to_string(p.GetHeight()) + "in";
      return s + newStr + "\n";
    },
    [&](std::string str)
    {
      return str + finalizer;
    },
    &seed);

  ASSERT_STREQ(expected.c_str(), result.c_str());
}
