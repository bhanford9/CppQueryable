#ifndef CPPQUERYABLE_DATASTRUCTURES_PEOPLE_H
#define CPPQUERYABLE_DATASTRUCTURES_PEOPLE_H

#include <vector>

#include "Person.h"
#include "../Queryable/Queryable.h"

class People : public Queryable<Person>
{
public:
  People() { }
  People(std::vector<Person> people)
    : Queryable<Person>(people)
  {
  }

  void Add(Person person)
  {
    this->items.get()->Add(person);
  }
};

#endif
