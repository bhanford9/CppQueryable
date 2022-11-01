#ifndef CPPQUERYABLE_DATASTRUCTURES_PERSONLIBRARY_H
#define CPPQUERYABLE_DATASTRUCTURES_PERSONLIBRARY_H

#include <memory>
#include <vector>

#include "Gender.hpp"
#include "Person.hpp"

class PersonLibrary
{
private:
  std::vector<std::shared_ptr<Person>> people;

public:
  PersonLibrary();

  std::vector<Person> GetPeople();
};

#endif
