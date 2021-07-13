#ifndef CPPQUERYABLE_DATASTRUCTURES_PEOPLE_H
#define CPPQUERYABLE_DATASTRUCTURES_PEOPLE_H

#include <vector>

#include "Person.h"
#include "../Queryable/QueryableVector.h"

class People : public QueryableVector<Person>
{
public:
  People() { }
  People(std::vector<Person> people)
    : QueryableVector<Person>(people)
  {
  }

  void Add(Person person)
  {
    this->items.get()->Add(person);
  }
};

#endif
