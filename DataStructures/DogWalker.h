#ifndef CPPQUERYABLE_DATASTRUCTURES_DOGWALKER_H
#define CPPQUERYABLE_DATASTRUCTURES_DOGWALKER_H

#include <vector>

#include "Animal.h"
#include "Person.h"

class DogWalker : public Person
{
public:
  std::vector<Animal> Dogs;

  DogWalker() { }
  DogWalker(Person person, Animal animal)
    : Person(person.GetId(), person.GetName(), person.GetAge(), person.GetHeight(), person.GetGender())
  {
    this->Dogs.push_back(animal);
  }
};

#endif
