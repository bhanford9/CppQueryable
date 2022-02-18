#include <functional>
#include <iostream>
#include <memory>
#include <set>
#include <string>
#include <vector>

#include "Queryable/Queryable.h"
#include "Queryable/QueryableData/IQueryableData.h"
#include "Queryable/QueryableData/SelectQueryableData/SelectQueryableData.h"
#include "Queryable/QueryableData/SelectQueryableData/SelectQueryableVectorData.h"
#include "Queryable/QueryableData/WhereQueryableData/WhereQueryableData.h"
#include "Queryable/QueryableData/WhereQueryableData/WhereQueryableVectorData.h"
#include "Queryable/QueryableData/QueryableData.h"
#include "Queryable/QueryBuilder.h"
#include "Queryable/QueryableType.h"
#include "DataStructures/People.h"
#include "DataStructures/PersonLibrary.h"

#include "DataStructures/Base.h"
#include "DataStructures/Derived.h"

using namespace QueryBuilder;

int main()
{

  PersonLibrary personLibrary;
  Queryable<Person> people = Queryable<Person>(personLibrary.GetPeople());


  std::vector<uint> startingInput;
  std::vector<uint> evens;
  Queryable<uint> queryable;
  Queryable<uint> queryableEvens;
  startingInput = std::vector<uint>({ 1, 4, 7, 4, 3, 76, 8, 45, 34, 76, 0, 867 });
  evens = std::vector<uint>({ 4, 76, 8, 34, 76, 0 });
  queryable = BuildQueryable(startingInput);
  queryableEvens = BuildQueryable(evens);

  std::cout << "attempting foreach" << std::endl;
  queryable.ForEach([](uint value) { std::cout << value << ", "; });
  std::cout << std::endl;

  Queryable<uint> local = BuildQueryable<uint>(queryable.ToList());
  std::cout << "local made\n\n" << std::endl;
  Queryable<uint> mevens = BuildQueryable<uint>(queryableEvens.ToList());
  std::cout << "mevens made\n\n" << std::endl;
  Queryable<uint> result = local.Where([](uint value) { return value > 10; });
  std::vector<uint> vectorResult = result.ToVector();


  // std::vector<uint> numbers({ 1, 65, 8, 45, 7, 63, 22, 14, 7, 9 });
  // std::function<bool(uint)> conditioner = [](uint value) { return value % 2 == 0; };
  // std::function<double(uint)> selector = [](uint value) { return static_cast<double>(value) / 2.0; };
  //
  // Queryable<uint> local(numbers);
  // local.Where(conditioner).ForEach([](uint value) { std::cout << "where value: " << value << std::endl; });
  // local.Select<double>(selector).ForEach([](double value) { std::cout << "select value: " << value << std::endl; });
  //
  // std::vector<Person> people(PersonLibrary().GetPeople());
  //
  // Queryable<Person> queryablePeople(people);
  // Queryable<std::string> queryableNames = queryablePeople
  //   .Select<std::string>([](Person p) { return p.GetName(); });
  //
  // queryableNames.ForEach([](std::string name) { std::cout << "name: " << name << std::endl; });
  //
  // std::cout << "count: " << queryableNames.Count() << std::endl;
  //
  // queryablePeople.Count();


  // QueryableVectorData<uint> queryableData(numbers);
  // std::shared_ptr<IQueryableData<uint>> sharedData = std::make_shared<QueryableVectorData<uint, double>>(queryableData);
  // IQueryableData<uint> * dummy = new SelectQueryableVectorData<uint, double>(sharedData, selector);
  // for (double value : queryableData)
  // {
  //   std::cout << "value as uint: " << value << std::endl;
  // }
  //
  // WhereQueryableVectorData<uint> whereQueryableData(&queryableData, conditioner);
  //
  // int count = 0;
  //
  // for (double value : whereQueryableData)
  // {
  //   if (++count > 12)
  //   break;
  //   std::cout << "even value: " << value << std::endl;
  // }
  //
  // SelectQueryableVectorData<uint, double> selectQueryableData(&queryableData, selector);
  //
  // for (double value : selectQueryableData)
  // {
  //   std::cout << "halved value as double: " << value << std::endl;
  // }
  //
  // SelectQueryableVectorData<uint, double> selectWhereQueryableData(&whereQueryableData, selector);
  //
  // for (double value : selectWhereQueryableData)
  // {
  //   std::cout << "halved even value as double: " << value << std::endl;
  // }


  return 0;
}
