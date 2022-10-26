#include <cstdint>
#include <functional>
#include <iostream>
#include <memory>
#include <set>
#include <string>
#include <vector>

#include "Queryable/InternalQueryables/VectorInternalQueryable.hpp"
#include "Queryable/QueryableData/IQueryableData.hpp"
// #include "Queryable/QueryableData/SelectQueryableData/SelectQueryableData.hpp"
// #include "Queryable/QueryableData/SelectQueryableData/SelectQueryableVectorData.hpp"
// #include "Queryable/QueryableData/WhereQueryableData/WhereQueryableData.hpp"
// #include "Queryable/QueryableData/WhereQueryableData/WhereQueryableVectorData.hpp"
#include "Queryable/QueryableData/WhereQueryableData/WhereQueryableMapData.hpp"
#include "Queryable/QueryableData/QueryableData.hpp"
// #include "Queryable/IQueryable.hpp"
#include "Queryable/ISortedQueryable.hpp"
#include "Queryable/QueryBuilder.hpp"
#include "Queryable/QueryableType.hpp"
#include "Queryable/InternalQueryable.hpp"
#include "Queryable/Queryable.hpp"
#include "DataStructures/People.hpp"
#include "DataStructures/PersonLibrary.hpp"

#include "DataStructures/Base.hpp"
#include "DataStructures/Derived.hpp"
#include "Queryable/QueryableData/QueryableVectorData.hpp"

using namespace QueryBuilder;

class Test
{
private:
    std::pair<const int, std::string> * kvp;

public:
  Test() { }

  void Set(std::vector<std::pair<const int, std::string>> vector)
  {
    kvp = &(*vector.begin());
  }
};

int main()
{
  PersonLibrary personLibrary;
  QueryableVector<Person> people(BuildQueryable(personLibrary.GetPeople()));
  std::cout << "1" << std::endl;
  auto genderGroups = BuildQueryable(
    people.ToMap<std::string, Person>(
      [](Person p) { std::cout << "getting name" << std::endl; return p.GetName(); },
      [](Person p) { return p; }))
    .GroupBy<Gender>([](std::pair<const std::string, Person> kvp) { std::cout << "in group by" << std::endl; return kvp.second.GetGender(); });
  std::cout << "2" << std::endl;
  auto males = BuildQueryable(people.ToList())
    .Where([](Person p) { return p.GetGender() == Gender::Male; });
  std::cout << "3" << std::endl;
  auto females = BuildQueryable(people.ToList())
    .Where([](Person p) { return p.GetGender() == Gender::Female; });

  std::cout << "4" << std::endl;

  for (const auto & group : genderGroups.ToVector())
  {
    std::cout << "key: " << (group.GetKey() == Gender::Male ? "M" : "F") << std::endl;
  }

  std::cout << "5" << std::endl;

  // ASSERT_EQ(2, genderGroups.Count());
  // ASSERT_TRUE(genderGroups.At(0).GetKey() == Gender::Male);
  // ASSERT_TRUE(genderGroups.At(1).GetKey() == Gender::Female);

  std::cout << "6" << std::endl;

  // for (const auto & item : BuildQueryable(
  //   this->people.ToMap<std::string, Person>(
  //     [](Person p) { return p.GetName(); },
  //     [](Person p) { return p; }))
  //   .ToVector())
  // {
  //   std::cout << "key: " << item.first << ", " << item.second << std::endl;
  // }

  genderGroups.ForEach([&](auto group)
  {
    if (group.Count() <= 0) throw;
    // ASSERT_GT(group.Count(), 0);
    if (group.GetKey() == Gender::Male)
    {
      if (males.Count() != group.Count()) throw;
      // ASSERT_EQ(males.Count(), group.Count());
    }
    else
    {
      if (females.Count() != group.Count()) throw;
      // ASSERT_EQ(females.Count(), group.Count());
    }

    int i = 0;
    for (const auto & kvp : group)
    {
      if (group.GetKey() == Gender::Male)
      {
        if (!(kvp.second == males.At(i++))) throw;
        // ASSERT_TRUE(kvp.second == males.At(i++));
      }
      else
      {
        if (!(kvp.second == females.At(i++))) throw;
        // ASSERT_TRUE(kvp.second == females.At(i++));
      }
    }
  });
    return 0;
}
