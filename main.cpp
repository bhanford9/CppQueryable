#include <iostream>

#include "Queryable/QueryBuilder.h"

using namespace QueryBuilder;

int main()
{
  std::vector<int> vectorInts({ 1, 3, 25, 6, 8, 9});
  BuildQueryable(vectorInts)
    .Where([](int value) { return value % 2 == 1; })
    .ForEach([](int value) { std::cout << "int: " << value << std::endl; });

  std::cout << std::endl;

  std::set<int> setInts({ 1, 3, 25, 3, 8, 9});
  BuildQueryable(setInts)
    .ForEach([](int value) { std::cout << "int: " << value << std::endl; });

  std::cout << std::endl;

  std::multiset<int> multiSetInts({ 1, 3, 25, 3, 8, 9});
  BuildQueryable(multiSetInts)
    .ForEach([](int value) { std::cout << "int: " << value << std::endl; });

  std::cout << std::endl;

  std::list<int> listInts({ 1, 3, 25, 3, 8, 9, 24});
  BuildQueryable(listInts)
    .ForEach([](int value) { std::cout << "int: " << value << std::endl; });

  std::cout << std::endl;

  std::deque<int> dequeInts({ 1, 3, 25, 3, 8, 9, 21});
  BuildQueryable(dequeInts)
    .ForEach([](int value) { std::cout << "int: " << value << std::endl; });

  return 0;
}
