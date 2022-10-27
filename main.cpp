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
  QueryableSet<Person> local1 = BuildQueryable(people.ToSet());
  QueryableSet<Person> local2 = BuildQueryable(people.ToSet());
  QueryableVector<double> ages = local1
    .Select<double>([](Person p) { return p.GetAge(); });
  QueryableVector<std::string> names = local2
    .Select<std::string>([](Person p) { return p.GetName(); });

  // ASSERT_EQ(local1.Count(), ages.Count());
  // ASSERT_EQ(local1.Count(), names.Count());

  int i = 0;
  double previousAge = -1;
  local1.ForEach([&](Person p)
  {
    double currentAge = ages.At(i);
    std::string currentName = names.At(i);
    // ASSERT_STREQ(local2.At(i++).GetName().c_str(), currentName.c_str());
    previousAge = currentAge;
  });

    return 0;
}
