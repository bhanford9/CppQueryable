#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <string>
#include <vector>

#include "../../../DataStructures/AnimalLibrary.hpp"
#include "../../../DataStructures/Gender.hpp"
#include "../../../DataStructures/Person.hpp"
#include "../../../DataStructures/PersonAndPet.hpp"
#include "../../../DataStructures/PersonAndPetLibrary.hpp"
#include "../../../DataStructures/PersonLibrary.hpp"

#include "../../../Queryable/QueryBuilder.hpp"
#include "../../../Queryable/Utilities/Grouping.hpp"

using namespace QueryBuilder;

class GroupByFunctionalTest : public ::testing::Test
{
protected:
    PersonLibrary personLibrary;
    AnimalLibrary animalLibrary;
    QueryableVector<Person> people;
    std::vector<PersonAndPet> petOwners;

    std::function<bool(PersonAndPet, PersonAndPet)> comparison = [](
        PersonAndPet a,
        PersonAndPet b) -> bool
    {
        return a.GetPerson() < b.GetPerson();
    };
    typedef decltype(comparison) TComparison;
    std::function<bool(Person, Person)> comparisonId = [](
        const Person & a,
        const Person & b) -> bool
    {
        return a.GetId() < b.GetId();
    };
    typedef decltype(comparisonId) TComparisonId;

    GroupByFunctionalTest()
        : people(BuildQueryable(this->personLibrary.GetPeople())),
          petOwners(PersonAndPetLibrary().GetPetOwners())
    {
    }

    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

TEST_F(GroupByFunctionalTest, DequeDefaultsTest)
{
    auto males = BuildQueryable(this->people.ToDeque()).Where(
        [](const Person & p) { return p.GetGender() == Gender::Male; });
    auto females = BuildQueryable(this->people.ToDeque()).Where(
        [](const Person & p) { return p.GetGender() == Gender::Female; });

    auto genderGroups = BuildQueryable(this->people.ToDeque()).GroupBy<Gender>(
        [](const Person & p) { return p.GetGender(); });

    ASSERT_EQ(2, genderGroups.Count());
    ASSERT_TRUE(genderGroups.At(0).GetKey() == Gender::Male);
    ASSERT_TRUE(genderGroups.At(1).GetKey() == Gender::Female);

    genderGroups.ForEach(
        [&](auto group)
        {
            ASSERT_GT(group.Count(), 0);
            if (group.GetKey() == Gender::Male)
            {
                ASSERT_EQ(males.Count(), group.Count());
            }
            else
            {
                ASSERT_EQ(females.Count(), group.Count());
            }

            int i = 0;
            for (const Person & person : group)
            {
                if (group.GetKey() == Gender::Male)
                {
                    ASSERT_TRUE(person == males.At(i++));
                }
                else
                {
                    ASSERT_TRUE(person == females.At(i++));
                }
            }
        });
}

TEST_F(GroupByFunctionalTest, ListDefaultsTest)
{
    auto genderGroups = BuildQueryable(this->people.ToList()).GroupBy<Gender>(
        [](const Person & p) { return p.GetGender(); });
    auto males = BuildQueryable(this->people.ToList()).Where(
        [](const Person & p) { return p.GetGender() == Gender::Male; });
    auto females = BuildQueryable(this->people.ToList()).Where(
        [](const Person & p) { return p.GetGender() == Gender::Female; });

    ASSERT_EQ(2, genderGroups.Count());
    ASSERT_TRUE(genderGroups.At(0).GetKey() == Gender::Male);
    ASSERT_TRUE(genderGroups.At(1).GetKey() == Gender::Female);

    genderGroups.ForEach(
        [&](auto group)
        {
            ASSERT_GT(group.Count(), 0);
            if (group.GetKey() == Gender::Male)
            {
                ASSERT_EQ(males.Count(), group.Count());
            }
            else
            {
                ASSERT_EQ(females.Count(), group.Count());
            }

            int i = 0;
            for (const auto & person : group)
            {
                if (group.GetKey() == Gender::Male)
                {
                    ASSERT_TRUE(person == males.At(i++));
                }
                else
                {
                    ASSERT_TRUE(person == females.At(i++));
                }
            }
        });
}

TEST_F(GroupByFunctionalTest, MapDefaultsTest)
{
    // auto genderGroups = BuildQueryable(
    //   this->people.ToMap<std::string, Person>(
    //     [](Person p) { return p.GetName(); },
    //     [](Person p) { return p; }))
    //   .GroupBy<Gender>([](std::pair<const std::string, Person> kvp) { return kvp.second.GetGender(); });
    // auto males = BuildQueryable(this->people.ToList())
    //   .Where([](Person p) { return p.GetGender() == Gender::Male; });
    // auto females = BuildQueryable(this->people.ToList())
    //   .Where([](Person p) { return p.GetGender() == Gender::Female; });

    // ASSERT_EQ(2, genderGroups.Count());
    // ASSERT_TRUE(genderGroups.At(0).GetKey() == Gender::Male);
    // ASSERT_TRUE(genderGroups.At(1).GetKey() == Gender::Female);

    // genderGroups.ForEach([&](auto group)
    // {
    //   ASSERT_GT(group.Count(), 0);
    //   if (group.GetKey() == Gender::Male)
    //   {
    //     ASSERT_EQ(males.Count(), group.Count());
    //   }
    //   else
    //   {
    //     ASSERT_EQ(females.Count(), group.Count());
    //   }

    //   for (const auto & kvp : group)
    //   {
    //     if (group.GetKey() == Gender::Male)
    //     {
    //       ASSERT_TRUE(males.Contains(kvp.second));
    //     }
    //     else
    //     {
    //       ASSERT_TRUE(females.Contains(kvp.second));
    //     }
    //   }
    // });
}

TEST_F(GroupByFunctionalTest, MultiSetDefaultsTest)
{
    auto genderGroups = BuildQueryable(this->people.ToMultiSet()).GroupBy<Gender>(
        [](const Person & p) { return p.GetGender(); });
    QueryableMultiSet<Person> males = BuildQueryable(this->people.ToMultiSet()).Where(
        [](const Person & p) { return p.GetGender() == Gender::Male; });
    //   males.Sort();
    QueryableMultiSet<Person> females = BuildQueryable(this->people.ToMultiSet()).Where(
        [](const Person & p) { return p.GetGender() == Gender::Female; });
    //   females.Sort();

    ASSERT_EQ(2, genderGroups.Count());
    ASSERT_TRUE(genderGroups.At(0).GetKey() == Gender::Male);
    ASSERT_TRUE(genderGroups.At(1).GetKey() == Gender::Female);

    genderGroups.ForEach(
        [&](auto group)
        {
            ASSERT_GT(group.Count(), 0);
            if (group.GetKey() == Gender::Male)
            {
                ASSERT_EQ(males.Count(), group.Count());
            }
            else
            {
                ASSERT_EQ(females.Count(), group.Count());
            }

            int i = 0;
            for (Person person : group)
            {
                if (group.GetKey() == Gender::Male)
                {
                    ASSERT_TRUE(person == males.At(i++));
                }
                else
                {
                    ASSERT_TRUE(person == females.At(i++));
                }
            }
        });
}

TEST_F(GroupByFunctionalTest, SetDefaultsTest)
{
    auto genderGroups = BuildQueryable(this->people.ToSet()).GroupBy<Gender>(
        [](const Person & p) { return p.GetGender(); });
    QueryableSet<Person> males = BuildQueryable(this->people.ToSet()).Where(
        [](const Person & p) { return p.GetGender() == Gender::Male; });
    //   males = males.ToQueryableSet();
    QueryableSet<Person> females = BuildQueryable(this->people.ToSet()).Where(
        [](const Person & p) { return p.GetGender() == Gender::Female; });
    //   females = females.ToQueryableSet();

    ASSERT_EQ(2, genderGroups.Count());
    ASSERT_TRUE(genderGroups.At(0).GetKey() == Gender::Male);
    ASSERT_TRUE(genderGroups.At(1).GetKey() == Gender::Female);

    genderGroups.ForEach(
        [&](auto group)
        {
            ASSERT_GT(group.Count(), 0);
            if (group.GetKey() == Gender::Male)
            {
                ASSERT_EQ(males.Count(), group.Count());
            }
            else
            {
                ASSERT_EQ(females.Count(), group.Count());
            }

            int i = 0;
            for (Person person : group)
            {
                if (group.GetKey() == Gender::Male)
                {
                    ASSERT_TRUE(person == males.At(i++));
                }
                else
                {
                    ASSERT_TRUE(person == females.At(i++));
                }
            }
        });
}

TEST_F(GroupByFunctionalTest, VectorDefaultsTest)
{
    auto genderGroups = BuildQueryable(this->people.ToVector()).GroupBy<Gender>(
        [](const Person & p) { return p.GetGender(); });
    QueryableVector<Person> males = BuildQueryable(this->people.ToVector()).Where(
        [](const Person & p) { return p.GetGender() == Gender::Male; });
    QueryableVector<Person> females = BuildQueryable(this->people.ToVector()).Where(
        [](const Person & p) { return p.GetGender() == Gender::Female; });

    ASSERT_EQ(2, genderGroups.Count());
    ASSERT_TRUE(genderGroups.At(0).GetKey() == Gender::Male);
    ASSERT_TRUE(genderGroups.At(1).GetKey() == Gender::Female);

    genderGroups.ForEach(
        [&](auto group)
        {
            ASSERT_GT(group.Count(), 0);
            if (group.GetKey() == Gender::Male)
            {
                ASSERT_EQ(males.Count(), group.Count());
            }
            else
            {
                ASSERT_EQ(females.Count(), group.Count());
            }

            int i = 0;
            for (Person person : group)
            {
                if (group.GetKey() == Gender::Male)
                {
                    ASSERT_TRUE(person == males.At(i++));
                }
                else
                {
                    ASSERT_TRUE(person == females.At(i++));
                }
            }
        });
}

TEST_F(GroupByFunctionalTest, CustomKeyCompareTest)
{
    auto genderGroups = BuildQueryable(this->people.ToVector()).GroupBy<Gender>(
        [](const Person & p) { return p.GetGender(); },
        [](Gender a, Gender b) { return a == Gender::Female && b == Gender::Male; });

    QueryableVector<Person> males = BuildQueryable(this->people.ToVector()).Where(
        [](const Person & p) { return p.GetGender() == Gender::Male; });
    QueryableVector<Person> females = BuildQueryable(this->people.ToVector()).Where(
        [](const Person & p) { return p.GetGender() == Gender::Female; });

    ASSERT_EQ(2, genderGroups.Count());
    // order of keys are swapped
    ASSERT_TRUE(genderGroups.At(1).GetKey() == Gender::Male);
    ASSERT_TRUE(genderGroups.At(0).GetKey() == Gender::Female);

    genderGroups.ForEach(
        [&](auto group)
        {
            ASSERT_GT(group.Count(), 0);
            if (group.GetKey() == Gender::Male)
            {
                ASSERT_EQ(males.Count(), group.Count());
            }
            else
            {
                ASSERT_EQ(females.Count(), group.Count());
            }

            int i = 0;
            for (Person person : group)
            {
                if (group.GetKey() == Gender::Male)
                {
                    ASSERT_TRUE(person == males.At(i++));
                }
                else
                {
                    ASSERT_TRUE(person == females.At(i++));
                }
            }
        });
}

TEST_F(GroupByFunctionalTest, GetKeyReturnNullTest)
{
    auto voidGroups = BuildQueryable(this->people.ToVector()).GroupBy<void *>(
        [](const Person & p) { return (void *)NULL; });

    ASSERT_EQ(1, voidGroups.Count());
    ASSERT_TRUE(voidGroups.At(0).GetKey() == NULL);

    voidGroups.ForEach(
        [&](auto group)
        {
            ASSERT_EQ(this->people.Count(), group.Count());

            int i = 0;
            for (Person person : group)
            {
                ASSERT_TRUE(person == this->people.At(i++));
            }
        });
}

TEST_F(GroupByFunctionalTest, GroupByWhereTest)
{
    auto ageGroupsOverThirty = BuildQueryable(this->people.ToVector()).GroupBy<double>(
        [](const Person & p) { return p.GetAge(); }).Where(
        [](const auto & group) { return group.GetKey() > 30; });

    auto overThirtyAgeGroups = BuildQueryable(this->people.ToVector()).Where(
        [](const Person & person) { return person.GetAge() > 30; }).GroupBy<double>(
        [](const Person & p) { return p.GetAge(); });

    // ASSERT_TRUE(ageGroupsOverThirty != NULL);
    ASSERT_EQ(3, ageGroupsOverThirty.Count());
    ASSERT_EQ(3, overThirtyAgeGroups.Count());
    ASSERT_TRUE(ageGroupsOverThirty.At(0).GetKey() == 51);
    ASSERT_TRUE(ageGroupsOverThirty.At(1).GetKey() == 52);
    ASSERT_TRUE(ageGroupsOverThirty.At(2).GetKey() == 61);
    ASSERT_TRUE(overThirtyAgeGroups.At(0).GetKey() == 51);
    ASSERT_TRUE(overThirtyAgeGroups.At(1).GetKey() == 52);
    ASSERT_TRUE(overThirtyAgeGroups.At(2).GetKey() == 61);

    int iGroup = 0;
    ageGroupsOverThirty.ForEach(
        [&](auto group)
        {
            ASSERT_TRUE(group.Count() == overThirtyAgeGroups.At(iGroup).Count());

            int iPerson = 0;
            for (Person person : group)
            {
                ASSERT_TRUE(person == overThirtyAgeGroups.At(iGroup).ToVector()[iPerson++]);
            }

            iGroup++;
        });
}
