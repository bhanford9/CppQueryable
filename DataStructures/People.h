#ifndef CPPQUERYABLE_DATASTRUCTURES_PEOPLE_H
#define CPPQUERYABLE_DATASTRUCTURES_PEOPLE_H

#include <vector>

#include "Person.h"
#include "../Queryable/Queryable.h"

class People : public Queryable<Person, std::vector>
{
public:
  People() { }
  People(std::vector<Person> people)
    : Queryable<Person, std::vector>(people)
  {
  }

  void Add(Person person)
  {
    this->items.push_back(person);
  }
};

#endif
