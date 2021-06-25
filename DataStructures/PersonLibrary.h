#ifndef CPPQUERYABLE_DATASTRUCTURES_PERSONLIBRARY_H
#define CPPQUERYABLE_DATASTRUCTURES_PERSONLIBRARY_H

#include <memory>
#include <vector>

#include "Gender.h"
#include "Person.h"

class PersonLibrary
{
private:
  std::vector<std::unique_ptr<Person>> people;

public:
  PersonLibrary();

  std::vector<Person> GetPeople();
};

#endif
