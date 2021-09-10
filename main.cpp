#include <functional>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "Queryable/Queryable.h"
#include "Queryable/QueryableData/SelectQueryableData/SelectQueryableData.h"
#include "Queryable/QueryableData/SelectQueryableData/SelectQueryableVectorData.h"
#include "Queryable/QueryableData/WhereQueryableData/WhereQueryableData.h"
#include "Queryable/QueryableData/WhereQueryableData/WhereQueryableVectorData.h"
#include "Queryable/QueryableData/QueryableData.h"
#include "Queryable/QueryBuilder.h"
#include "Queryable/QueryableType.h"
#include "DataStructures/People.h"
#include "DataStructures/PersonLibrary.h"

using namespace QueryBuilder;

int main()
{
  std::vector<uint> numbers({ 1, 65, 8, 45, 7, 63, 22, 14, 7, 9 });
  QueryableVectorData<uint> queryableData(numbers);
  for (double value : queryableData)
  {
    std::cout << "value as uint: " << value << std::endl;
  }

  std::function<bool(uint)> conditioner = [](uint value) { return value % 2 == 0; };
  WhereQueryableVectorData<uint> whereQueryableData(&queryableData, conditioner);

  for (double value : whereQueryableData)
  {
    std::cout << "even value: " << value << std::endl;
  }

  std::function<double(uint)> selector = [](uint value) { return static_cast<double>(value) / 2.0; };
  SelectQueryableVectorData<uint, double> selectQueryableData(&queryableData, selector);

  for (double value : selectQueryableData)
  {
    std::cout << "halved value as double: " << value << std::endl;
  }

  SelectQueryableVectorData<uint, double> selectWhereQueryableData(&whereQueryableData, selector);

  for (double value : selectWhereQueryableData)
  {
    std::cout << "halved even value as double: " << value << std::endl;
  }


  return 0;
}
