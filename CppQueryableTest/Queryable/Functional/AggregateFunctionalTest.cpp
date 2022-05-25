#include <gtest/gtest.h>

#include <exception>
#include <iostream>
#include <string>

#include "../../../DataStructures/Gender.hpp"
#include "../../../DataStructures/Person.hpp"
#include "../../../DataStructures/PersonLibrary.hpp"

#include "../../../Queryable/QueryBuilder.hpp"


using namespace QueryBuilder;

class AggregateFunctionalTest : public ::testing::Test
{
protected:
  PersonLibrary personLibrary;
  IQueryable<Person> people;

  AggregateFunctionalTest() :
    people(BuildQueryable2(this->personLibrary.GetPeople()))
  {
  }

  void SetUp() override
  {
  }

  void TearDown() override {}
};

TEST_F(AggregateFunctionalTest, AggregateTemplateUninitialized)
{
  IQueryable<Person> local(BuildQueryable2(std::vector<Person>()));
  std::string result = local.Aggregate<std::vector, std::string>([](std::string s, Person p)
  {
    return s + ", " + p.GetName();
  });

  ASSERT_STREQ("", result.c_str());
}

TEST_F(AggregateFunctionalTest, AggregateAsVectorUninitialized)
{
  IQueryable<Person> local(BuildQueryable2(std::vector<Person>()));
  std::string result = local
    .AsQueryableVector()
    .Aggregate<std::string>([](std::string s, Person p)
    {
      return s + ", " + p.GetName();
    });

  ASSERT_STREQ("", result.c_str());
}

TEST_F(AggregateFunctionalTest, AggregateExtendedUninitialized)
{
  IQueryable<Person> local(BuildQueryable2(std::vector<Person>()));
  std::string result = local
    .AsExtendedQueryable<std::vector>()
    .Aggregate<std::string>([](std::string s, Person p)
    {
      return s + ", " + p.GetName();
    });

  ASSERT_STREQ("", result.c_str());
}

TEST_F(AggregateFunctionalTest, AggregateTemplateSeededUninitialized)
{
  std::string expected = "Hello World!";
  IQueryable<Person> local(BuildQueryable2(std::vector<Person>()));
  std::string result = local.Aggregate<std::vector, std::string>([](std::string s, Person p)
  {
    return s + ", " + p.GetName();
  },
  &expected);

  ASSERT_STREQ(expected.c_str(), result.c_str());
}

TEST_F(AggregateFunctionalTest, AggregateAsVectorSeededUninitialized)
{
  std::string expected = "Hello World!";
  IQueryable<Person> local(BuildQueryable2(std::vector<Person>()));
  std::string result = local
    .AsQueryableVector()
    .Aggregate<std::string>([](std::string s, Person p)
    {
      return s + ", " + p.GetName();
    },
    &expected);

  ASSERT_STREQ(expected.c_str(), result.c_str());
}

TEST_F(AggregateFunctionalTest, AggregateExtendedSeededUninitialized)
{
  std::string expected = "Hello World!";
  IQueryable<Person> local(BuildQueryable2(std::vector<Person>()));
  std::string result = local
    .AsExtendedQueryable<std::vector>()
    .Aggregate<std::string>([](std::string s, Person p)
  {
    return s + ", " + p.GetName();
  },
  &expected);

  ASSERT_STREQ(expected.c_str(), result.c_str());
}

TEST_F(AggregateFunctionalTest, AggregateTemplateFinalizerUninitialized)
{
  std::string expected = "Names: ";
  IQueryable<Person> local(BuildQueryable2(std::vector<Person>()));
  std::string result = local.Aggregate<std::vector, std::string, std::string>(
      [](std::string s, Person p) { return s + ", " + p.GetName(); },
      [&](std::string output) -> std::string { return expected + output; });

  ASSERT_STREQ(expected.c_str(), result.c_str());
}

TEST_F(AggregateFunctionalTest, AggregateAsVectorFinalizerUninitialized)
{
  std::string expected = "Names: ";
  IQueryable<Person> local(BuildQueryable2(std::vector<Person>()));
  std::string result = local
    .AsQueryableVector()
    .Aggregate<std::string, std::string>(
      [](std::string s, Person p) { return s + ", " + p.GetName(); },
      [&](std::string output) -> std::string { return expected + output; });

  ASSERT_STREQ(expected.c_str(), result.c_str());
}

TEST_F(AggregateFunctionalTest, AggregateExtendedFinalizerUninitialized)
{
  std::string expected = "Names: ";
  IQueryable<Person> local(BuildQueryable2(std::vector<Person>()));
  std::string result = local
    .AsExtendedQueryable<std::vector>()
    .Aggregate<std::string, std::string>(
      [](std::string s, Person p) { return s + ", " + p.GetName(); },
      [&](std::string output) -> std::string { return expected + output; });

  ASSERT_STREQ(expected.c_str(), result.c_str());
}

TEST_F(AggregateFunctionalTest, AggregateTemplateFinalizerSeededUninitialized)
{
  std::string expected = "Names: Hello World!";
  std::string finalizer = "Names: ";
  std::string seed = "Hello World!";
  IQueryable<Person> local(BuildQueryable2(std::vector<Person>()));
  std::string result = local.Aggregate<std::vector, std::string, std::string>(
    [](std::string s, Person p) { return s + ", " + p.GetName(); },
    [&](std::string output) -> std::string { return finalizer + seed; },
    &expected);

  ASSERT_STREQ(expected.c_str(), result.c_str());
}

TEST_F(AggregateFunctionalTest, AggregateAsVectorFinalizerSeededUninitialized)
{
  std::string expected = "Names: Hello World!";
  std::string finalizer = "Names: ";
  std::string seed = "Hello World!";
  IQueryable<Person> local(BuildQueryable2(std::vector<Person>()));
  std::string result = local
    .AsQueryableVector()
    .Aggregate<std::string, std::string>(
      [](std::string s, Person p) { return s + ", " + p.GetName(); },
      [&](std::string output) -> std::string { return finalizer + seed; },
      &expected);

  ASSERT_STREQ(expected.c_str(), result.c_str());
}

TEST_F(AggregateFunctionalTest, AggregateExtendedFinalizerSeededUninitialized)
{
  std::string expected = "Names: Hello World!";
  std::string finalizer = "Names: ";
  std::string seed = "Hello World!";
  IQueryable<Person> local(BuildQueryable2(std::vector<Person>()));
  std::string result = local
    .AsExtendedQueryable<std::vector>()
    .Aggregate<std::string, std::string>(
      [](std::string s, Person p) { return s + ", " + p.GetName(); },
      [&](std::string output) -> std::string { return finalizer + seed; },
      &expected);

  ASSERT_STREQ(expected.c_str(), result.c_str());
}

TEST_F(AggregateFunctionalTest, AggregateTemplateDeque)
{
  std::string expected = "Person 1 (Male) - Height: 73in\nPerson 10 (Female) - Height: 55in\nPerson 11 (Male) - Height: 68in\n";
  QueryableDeque<Person> local = BuildQueryable2(this->people.ToDeque());
  std::string result = local
    .Where([](Person p) { return p.GetName().find("Person 1") != std::string::npos; })
    .Aggregate<std::deque, std::string>([](std::string s, Person p)
    {
      std::string newStr = p.GetName() + " (" +
        (p.IsMale() ? "Male" : "Female") +
        ") - Height: " + std::to_string(p.GetHeight()) + "in";
      return s + newStr + "\n";
    });

  ASSERT_STREQ(expected.c_str(), result.c_str());
}

TEST_F(AggregateFunctionalTest, AggregateAsDeque)
{
  std::string expected = "Person 1 (Male) - Height: 73in\nPerson 10 (Female) - Height: 55in\nPerson 11 (Male) - Height: 68in\n";
  QueryableDeque<Person> local = BuildQueryable2(this->people.ToDeque());
  std::string result = local
    .Where([](Person p) { return p.GetName().find("Person 1") != std::string::npos; })
    .AsQueryableDeque()
    .Aggregate<std::string>([](std::string s, Person p)
    {
      std::string newStr = p.GetName() + " (" +
        (p.IsMale() ? "Male" : "Female") +
        ") - Height: " + std::to_string(p.GetHeight()) + "in";
      return s + newStr + "\n";
    });

  ASSERT_STREQ(expected.c_str(), result.c_str());
}

TEST_F(AggregateFunctionalTest, AggregateExtendedDeque)
{
  std::string expected = "Person 1 (Male) - Height: 73in\nPerson 10 (Female) - Height: 55in\nPerson 11 (Male) - Height: 68in\n";
  QueryableDeque<Person> local = BuildQueryable2(this->people.ToDeque());
  std::string result = local
    .Where([](Person p) { return p.GetName().find("Person 1") != std::string::npos; })
    .AsExtendedQueryable<std::deque>()
    .Aggregate<std::string>([](std::string s, Person p)
    {
      std::string newStr = p.GetName() + " (" +
        (p.IsMale() ? "Male" : "Female") +
        ") - Height: " + std::to_string(p.GetHeight()) + "in";
      return s + newStr + "\n";
    });

  ASSERT_STREQ(expected.c_str(), result.c_str());
}

TEST_F(AggregateFunctionalTest, AggregateTemplateList)
{
  std::string expected = "Person 1 (Male) - Height: 73in\nPerson 10 (Female) - Height: 55in\nPerson 11 (Male) - Height: 68in\n";
  QueryableList<Person> local = BuildQueryable2(this->people.ToList());
  std::string result = local
    .Where([](Person p) { return p.GetName().find("Person 1") != std::string::npos; })
    .Aggregate<std::list, std::string>([](std::string s, Person p)
    {
      std::string newStr = p.GetName() + " (" +
        (p.IsMale() ? "Male" : "Female") +
        ") - Height: " + std::to_string(p.GetHeight()) + "in";
      return s + newStr + "\n";
    });

  ASSERT_STREQ(expected.c_str(), result.c_str());
}

TEST_F(AggregateFunctionalTest, AggregateAsList)
{
  std::string expected = "Person 1 (Male) - Height: 73in\nPerson 10 (Female) - Height: 55in\nPerson 11 (Male) - Height: 68in\n";
  QueryableList<Person> local = BuildQueryable2(this->people.ToList());
  std::string result = local
    .Where([](Person p) { return p.GetName().find("Person 1") != std::string::npos; })
    .AsQueryableList()
    .Aggregate<std::string>([](std::string s, Person p)
    {
      std::string newStr = p.GetName() + " (" +
        (p.IsMale() ? "Male" : "Female") +
        ") - Height: " + std::to_string(p.GetHeight()) + "in";
      return s + newStr + "\n";
    });

  ASSERT_STREQ(expected.c_str(), result.c_str());
}

TEST_F(AggregateFunctionalTest, AggregateExtendedList)
{
  std::string expected = "Person 1 (Male) - Height: 73in\nPerson 10 (Female) - Height: 55in\nPerson 11 (Male) - Height: 68in\n";
  QueryableList<Person> local = BuildQueryable2(this->people.ToList());
  std::string result = local
    .Where([](Person p) { return p.GetName().find("Person 1") != std::string::npos; })
    .AsExtendedQueryable<std::list>()
    .Aggregate<std::string>([](std::string s, Person p)
    {
      std::string newStr = p.GetName() + " (" +
        (p.IsMale() ? "Male" : "Female") +
        ") - Height: " + std::to_string(p.GetHeight()) + "in";
      return s + newStr + "\n";
    });

  ASSERT_STREQ(expected.c_str(), result.c_str());
}

TEST_F(AggregateFunctionalTest, AggregateTemplateMultiSet)
{
  std::string expected = "Person 1 (Male) - Height: 73in\nPerson 10 (Female) - Height: 55in\nPerson 11 (Male) - Height: 68in\n";
  QueryableMultiSet<Person> local = BuildQueryable2(this->people.ToMultiSet());
  std::string result = local
    .Where([](Person p) { return p.GetName().find("Person 1") != std::string::npos; })
    .Aggregate<std::multiset, std::string>([](std::string s, Person p)
    {
      std::string newStr = p.GetName() + " (" +
        (p.IsMale() ? "Male" : "Female") +
        ") - Height: " + std::to_string(p.GetHeight()) + "in";
      return s + newStr + "\n";
    });

  ASSERT_STREQ(expected.c_str(), result.c_str());
}

TEST_F(AggregateFunctionalTest, AggregateAsMultiSet)
{
  std::string expected = "Person 1 (Male) - Height: 73in\nPerson 10 (Female) - Height: 55in\nPerson 11 (Male) - Height: 68in\n";
  QueryableMultiSet<Person> local = BuildQueryable2(this->people.ToMultiSet());
  std::string result = local
    .Where([](Person p) { return p.GetName().find("Person 1") != std::string::npos; })
    .AsQueryableMultiSet()
    .Aggregate<std::string>([](std::string s, Person p)
    {
      std::string newStr = p.GetName() + " (" +
        (p.IsMale() ? "Male" : "Female") +
        ") - Height: " + std::to_string(p.GetHeight()) + "in";
      return s + newStr + "\n";
    });

  ASSERT_STREQ(expected.c_str(), result.c_str());
}

TEST_F(AggregateFunctionalTest, AggregateExtendedMultiSet)
{
  std::string expected = "Person 1 (Male) - Height: 73in\nPerson 10 (Female) - Height: 55in\nPerson 11 (Male) - Height: 68in\n";
  QueryableMultiSet<Person> local = BuildQueryable2(this->people.ToMultiSet());
  std::string result = local
    .Where([](Person p) { return p.GetName().find("Person 1") != std::string::npos; })
    .AsExtendedQueryable<std::multiset>()
    .Aggregate<std::string>([](std::string s, Person p)
    {
      std::string newStr = p.GetName() + " (" +
        (p.IsMale() ? "Male" : "Female") +
        ") - Height: " + std::to_string(p.GetHeight()) + "in";
      return s + newStr + "\n";
    });

  ASSERT_STREQ(expected.c_str(), result.c_str());
}

TEST_F(AggregateFunctionalTest, AggregateTemplateSet)
{
  std::string expected = "Person 1 (Male) - Height: 73in\nPerson 10 (Female) - Height: 55in\nPerson 11 (Male) - Height: 68in\n";
  QueryableSet<Person> local = BuildQueryable2(this->people.ToSet());
  std::string result = local
    .Where([](Person p) { return p.GetName().find("Person 1") != std::string::npos; })
    .Aggregate<std::set, std::string>([](std::string s, Person p)
    {
      std::string newStr = p.GetName() + " (" +
        (p.IsMale() ? "Male" : "Female") +
        ") - Height: " + std::to_string(p.GetHeight()) + "in";
      return s + newStr + "\n";
    });

  ASSERT_STREQ(expected.c_str(), result.c_str());
}

TEST_F(AggregateFunctionalTest, AggregateAsSet)
{
  std::string expected = "Person 1 (Male) - Height: 73in\nPerson 10 (Female) - Height: 55in\nPerson 11 (Male) - Height: 68in\n";
  QueryableSet<Person> local = BuildQueryable2(this->people.ToSet());
  std::string result = local
    .Where([](Person p) { return p.GetName().find("Person 1") != std::string::npos; })
    .AsQueryableSet()
    .Aggregate<std::string>([](std::string s, Person p)
    {
      std::string newStr = p.GetName() + " (" +
        (p.IsMale() ? "Male" : "Female") +
        ") - Height: " + std::to_string(p.GetHeight()) + "in";
      return s + newStr + "\n";
    });

  ASSERT_STREQ(expected.c_str(), result.c_str());
}

TEST_F(AggregateFunctionalTest, AggregateExtendedSet)
{
  std::string expected = "Person 1 (Male) - Height: 73in\nPerson 10 (Female) - Height: 55in\nPerson 11 (Male) - Height: 68in\n";
  QueryableSet<Person> local = BuildQueryable2(this->people.ToSet());
  std::string result = local
    .Where([](Person p) { return p.GetName().find("Person 1") != std::string::npos; })
    .AsExtendedQueryable<std::set>()
    .Aggregate<std::string>([](std::string s, Person p)
    {
      std::string newStr = p.GetName() + " (" +
        (p.IsMale() ? "Male" : "Female") +
        ") - Height: " + std::to_string(p.GetHeight()) + "in";
      return s + newStr + "\n";
    });

  ASSERT_STREQ(expected.c_str(), result.c_str());
}

TEST_F(AggregateFunctionalTest, AggregateTemplateVector)
{
  std::string expected = "Person 1 (Male) - Height: 73in\nPerson 10 (Female) - Height: 55in\nPerson 11 (Male) - Height: 68in\n";
  QueryableVector<Person> local = BuildQueryable2(this->people.ToVector());
  std::string result = local
    .Where([](Person p) { return p.GetName().find("Person 1") != std::string::npos; })
    .Aggregate<std::vector, std::string>([](std::string s, Person p)
    {
      std::string newStr = p.GetName() + " (" +
        (p.IsMale() ? "Male" : "Female") +
        ") - Height: " + std::to_string(p.GetHeight()) + "in";
      return s + newStr + "\n";
    });

  ASSERT_STREQ(expected.c_str(), result.c_str());
}

TEST_F(AggregateFunctionalTest, AggregateAsVector)
{
  std::string expected = "Person 1 (Male) - Height: 73in\nPerson 10 (Female) - Height: 55in\nPerson 11 (Male) - Height: 68in\n";
  QueryableVector<Person> local = BuildQueryable2(this->people.ToVector());
  std::string result = local
    .Where([](Person p) { return p.GetName().find("Person 1") != std::string::npos; })
    .AsQueryableVector()
    .Aggregate<std::string>([](std::string s, Person p)
    {
      std::string newStr = p.GetName() + " (" +
        (p.IsMale() ? "Male" : "Female") +
        ") - Height: " + std::to_string(p.GetHeight()) + "in";
      return s + newStr + "\n";
    });

  ASSERT_STREQ(expected.c_str(), result.c_str());
}

TEST_F(AggregateFunctionalTest, AggregateExtendedVector)
{
  std::string expected = "Person 1 (Male) - Height: 73in\nPerson 10 (Female) - Height: 55in\nPerson 11 (Male) - Height: 68in\n";
  QueryableVector<Person> local = BuildQueryable2(this->people.ToVector());
  std::string result = local
    .Where([](Person p) { return p.GetName().find("Person 1") != std::string::npos; })
    .AsExtendedQueryable<std::vector>()
    .Aggregate<std::string>([](std::string s, Person p)
    {
      std::string newStr = p.GetName() + " (" +
        (p.IsMale() ? "Male" : "Female") +
        ") - Height: " + std::to_string(p.GetHeight()) + "in";
      return s + newStr + "\n";
    });

  ASSERT_STREQ(expected.c_str(), result.c_str());
}

TEST_F(AggregateFunctionalTest, AggregateSeededFinalizerTemplateDeque)
{
  std::string seed = "People: \n";
  std::string finalizer = "\n---END---\n";
  std::string expected = seed + "Person 1 (Male) - Height: 73in\nPerson 10 (Female) - Height: 55in\nPerson 11 (Male) - Height: 68in\n" + finalizer;
  QueryableDeque<Person> local = BuildQueryable2(this->people.ToDeque());
  std::string result = local
    .Where([](Person p) { return p.GetName().find("Person 1") != std::string::npos; })
    .Aggregate<std::deque, std::string, std::string>(
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

TEST_F(AggregateFunctionalTest, AggregateSeededFinalizerAsDeque)
{
  std::string seed = "People: \n";
  std::string finalizer = "\n---END---\n";
  std::string expected = seed + "Person 1 (Male) - Height: 73in\nPerson 10 (Female) - Height: 55in\nPerson 11 (Male) - Height: 68in\n" + finalizer;
  QueryableDeque<Person> local = BuildQueryable2(this->people.ToDeque());
  std::string result = local
    .Where([](Person p) { return p.GetName().find("Person 1") != std::string::npos; })
    .AsQueryableDeque()
    .Aggregate<std::string, std::string>(
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

TEST_F(AggregateFunctionalTest, AggregateSeededFinalizerExtendedDeque)
{
  std::string seed = "People: \n";
  std::string finalizer = "\n---END---\n";
  std::string expected = seed + "Person 1 (Male) - Height: 73in\nPerson 10 (Female) - Height: 55in\nPerson 11 (Male) - Height: 68in\n" + finalizer;
  QueryableDeque<Person> local = BuildQueryable2(this->people.ToDeque());
  std::string result = local
    .Where([](Person p) { return p.GetName().find("Person 1") != std::string::npos; })
    .AsExtendedQueryable<std::deque>()
    .Aggregate<std::string, std::string>(
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

TEST_F(AggregateFunctionalTest, AggregateSeededFinalizerTemplateList)
{
  std::string seed = "People: \n";
  std::string finalizer = "\n---END---\n";
  std::string expected = seed + "Person 1 (Male) - Height: 73in\nPerson 10 (Female) - Height: 55in\nPerson 11 (Male) - Height: 68in\n" + finalizer;
  QueryableList<Person> local = BuildQueryable2(this->people.ToList());
  std::string result = local
    .Where([](Person p) { return p.GetName().find("Person 1") != std::string::npos; })
    .Aggregate<std::list, std::string, std::string>([](std::string s, Person p)
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

TEST_F(AggregateFunctionalTest, AggregateSeededFinalizerAsList)
{
  std::string seed = "People: \n";
  std::string finalizer = "\n---END---\n";
  std::string expected = seed + "Person 1 (Male) - Height: 73in\nPerson 10 (Female) - Height: 55in\nPerson 11 (Male) - Height: 68in\n" + finalizer;
  QueryableList<Person> local = BuildQueryable2(this->people.ToList());
  std::string result = local
    .Where([](Person p) { return p.GetName().find("Person 1") != std::string::npos; })
    .AsQueryableList()
    .Aggregate<std::string, std::string>([](std::string s, Person p)
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

TEST_F(AggregateFunctionalTest, AggregateSeededFinalizerExtendedList)
{
  std::string seed = "People: \n";
  std::string finalizer = "\n---END---\n";
  std::string expected = seed + "Person 1 (Male) - Height: 73in\nPerson 10 (Female) - Height: 55in\nPerson 11 (Male) - Height: 68in\n" + finalizer;
  QueryableList<Person> local = BuildQueryable2(this->people.ToList());
  std::string result = local
    .Where([](Person p) { return p.GetName().find("Person 1") != std::string::npos; })
    .AsExtendedQueryable<std::list>()
    .Aggregate<std::string, std::string>([](std::string s, Person p)
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

TEST_F(AggregateFunctionalTest, AggregateSeededFinalizerTemplateMultiSet)
{
  std::string seed = "People: \n";
  std::string finalizer = "\n---END---\n";
  std::string expected = seed + "Person 1 (Male) - Height: 73in\nPerson 10 (Female) - Height: 55in\nPerson 11 (Male) - Height: 68in\n" + finalizer;
  QueryableMultiSet<Person> local = BuildQueryable2(this->people.ToMultiSet());
  std::string result = local
    .Where([](Person p) { return p.GetName().find("Person 1") != std::string::npos; })
    .Aggregate<std::multiset, std::string, std::string>([](std::string s, Person p)
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

TEST_F(AggregateFunctionalTest, AggregateSeededFinalizerAsMultiSet)
{
  std::string seed = "People: \n";
  std::string finalizer = "\n---END---\n";
  std::string expected = seed + "Person 1 (Male) - Height: 73in\nPerson 10 (Female) - Height: 55in\nPerson 11 (Male) - Height: 68in\n" + finalizer;
  QueryableMultiSet<Person> local = BuildQueryable2(this->people.ToMultiSet());
  std::string result = local
    .Where([](Person p) { return p.GetName().find("Person 1") != std::string::npos; })
    .AsQueryableMultiSet()
    .Aggregate<std::string, std::string>([](std::string s, Person p)
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

TEST_F(AggregateFunctionalTest, AggregateSeededFinalizerExtendedMultiSet)
{
  std::string seed = "People: \n";
  std::string finalizer = "\n---END---\n";
  std::string expected = seed + "Person 1 (Male) - Height: 73in\nPerson 10 (Female) - Height: 55in\nPerson 11 (Male) - Height: 68in\n" + finalizer;
  QueryableMultiSet<Person> local = BuildQueryable2(this->people.ToMultiSet());
  std::string result = local
    .Where([](Person p) { return p.GetName().find("Person 1") != std::string::npos; })
    .AsExtendedQueryable<std::multiset>()
    .Aggregate<std::string, std::string>([](std::string s, Person p)
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

TEST_F(AggregateFunctionalTest, AggregateSeededFinalizerTemplateSet)
{
  std::string seed = "People: \n";
  std::string finalizer = "\n---END---\n";
  std::string expected = seed + "Person 1 (Male) - Height: 73in\nPerson 10 (Female) - Height: 55in\nPerson 11 (Male) - Height: 68in\n" + finalizer;
  QueryableSet<Person> local = BuildQueryable2(this->people.ToSet());
  std::string result = local
    .Where([](Person p) { return p.GetName().find("Person 1") != std::string::npos; })
    .Aggregate<std::set, std::string, std::string>([](std::string s, Person p)
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

TEST_F(AggregateFunctionalTest, AggregateSeededFinalizerAsSet)
{
  std::string seed = "People: \n";
  std::string finalizer = "\n---END---\n";
  std::string expected = seed + "Person 1 (Male) - Height: 73in\nPerson 10 (Female) - Height: 55in\nPerson 11 (Male) - Height: 68in\n" + finalizer;
  QueryableSet<Person> local = BuildQueryable2(this->people.ToSet());
  std::string result = local
    .Where([](Person p) { return p.GetName().find("Person 1") != std::string::npos; })
    .AsQueryableSet()
    .Aggregate<std::string, std::string>([](std::string s, Person p)
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

TEST_F(AggregateFunctionalTest, AggregateSeededFinalizerExtendedSet)
{
  std::string seed = "People: \n";
  std::string finalizer = "\n---END---\n";
  std::string expected = seed + "Person 1 (Male) - Height: 73in\nPerson 10 (Female) - Height: 55in\nPerson 11 (Male) - Height: 68in\n" + finalizer;
  QueryableSet<Person> local = BuildQueryable2(this->people.ToSet());
  std::string result = local
    .Where([](Person p) { return p.GetName().find("Person 1") != std::string::npos; })
    .AsExtendedQueryable<std::set>()
    .Aggregate<std::string, std::string>([](std::string s, Person p)
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

TEST_F(AggregateFunctionalTest, AggregateSeededFinalizerTemplateVector)
{
  std::string seed = "People: \n";
  std::string finalizer = "\n---END---\n";
  std::string expected = seed + "Person 1 (Male) - Height: 73in\nPerson 10 (Female) - Height: 55in\nPerson 11 (Male) - Height: 68in\n" + finalizer;
  QueryableVector<Person> local = BuildQueryable2(this->people.ToVector());
  std::string result = local
    .Where([](Person p) { return p.GetName().find("Person 1") != std::string::npos; })
    .Aggregate<std::vector, std::string, std::string>([](std::string s, Person p)
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

TEST_F(AggregateFunctionalTest, AggregateSeededFinalizerAsVector)
{
  std::string seed = "People: \n";
  std::string finalizer = "\n---END---\n";
  std::string expected = seed + "Person 1 (Male) - Height: 73in\nPerson 10 (Female) - Height: 55in\nPerson 11 (Male) - Height: 68in\n" + finalizer;
  QueryableVector<Person> local = BuildQueryable2(this->people.ToVector());
  std::string result = local
    .Where([](Person p) { return p.GetName().find("Person 1") != std::string::npos; })
    .AsQueryableVector()
    .Aggregate<std::string, std::string>([](std::string s, Person p)
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

TEST_F(AggregateFunctionalTest, AggregateSeededFinalizerExtendedVector)
{
  std::string seed = "People: \n";
  std::string finalizer = "\n---END---\n";
  std::string expected = seed + "Person 1 (Male) - Height: 73in\nPerson 10 (Female) - Height: 55in\nPerson 11 (Male) - Height: 68in\n" + finalizer;
  QueryableVector<Person> local = BuildQueryable2(this->people.ToVector());
  std::string result = local
    .Where([](Person p) { return p.GetName().find("Person 1") != std::string::npos; })
    .AsExtendedQueryable<std::vector>()
    .Aggregate<std::string, std::string>([](std::string s, Person p)
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

// TODO --> Where and Select with Aggregate methods
