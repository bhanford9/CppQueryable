#include <string>
#include <vector>

// #include "Queryable/QueryableData/SelectQueryableData/SelectQueryableData.hpp"
// #include "Queryable/QueryableData/SelectQueryableData/SelectQueryableVectorData.hpp"
// #include "Queryable/QueryableData/WhereQueryableData/WhereQueryableData.hpp"
// #include "Queryable/QueryableData/WhereQueryableData/WhereQueryableVectorData.hpp"
// #include "Queryable/IQueryable.hpp"
#include "DataStructures/PersonLibrary.hpp"
#include "Queryable/Queryable.hpp"
#include "Queryable/QueryBuilder.hpp"

using namespace QueryBuilder;


int main()
{
  // std::cout << "within main" << std::endl;
  PersonLibrary personLibrary;
  const QueryableVector<Person> people(BuildQueryable(personLibrary.GetPeople()));

  QueryableMultiSet<Person> local1 = BuildQueryable(people.ToMultiSet());
  QueryableMultiSet<Person> local2 = BuildQueryable(people.ToMultiSet());
  const QueryableVector<double> ages = local1
    .Select<double>([](const Person & p) { return p.GetAge(); });
  const QueryableVector<std::string> names = local2
    .Select<std::string>([](const Person & p) { return p.GetName(); });

  // ASSERT_EQ(local1.Count(), ages.Count());
  // ASSERT_EQ(local1.Count(), names.Count());

  const size_t i = 0;
  double previousAge = -1;
  local1.ForEach([&](const Person & p)
  {
    const double currentAge = ages.At(i);
    std::string currentName = names.At(i);
    // ASSERT_STREQ(local2.At(i++).GetName().c_str(), currentName.c_str());
    previousAge = currentAge;
    // std::cout << p << std::endl;
  });

  return 0;
}
