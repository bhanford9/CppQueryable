#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "Queryable/Queryable.h"
#include "Queryable/QueryBuilder.h"
#include "Queryable/QueryableType.h"
#include "DataStructures/People.h"
#include "DataStructures/PersonLibrary.h"

using namespace QueryBuilder;

int main()
{
  {
    PersonLibrary library;
    People people(library.GetPeople());

    Queryable<double> * ages = people
      .Select<double>([](Person p) { return p.GetAge(); });

    ages->ForEach([](double age) { std::cout << "age: " << age << std::endl; });

    std::cout << std::endl;

    std::set<std::string> strings({"hello", "ello", "llo", "lo", "o"});
    BuildQueryable(strings)
      .Select<char>([](std::string str) { return str[0]; })
      ->ForEach([](char c) { std::cout << "character: " << c << std::endl; });

    std::cout << std::endl;

      BuildQueryable(strings)
        .Select<char>([](std::string str) { return str[0]; }, QueryableType::List)
        ->ForEach([](char c) { std::cout << "character: " << c << std::endl; });

    std::cout << std::endl;

    std::vector<int> vectorInts({ 1, 3, 25, 6, 8, 9});
    std::vector<int> newInts = BuildQueryable(vectorInts)
      .Where([](int value) { return value % 2 == 1; })
      ->ToVector();
      //->ForEach([](int value) { std::cout << "int: " << value << std::endl; });
    for (int value : newInts)
    {
      std::cout << "value: " << value << std::endl;
    }

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
  }
  return 0;
}
