#ifndef CPPQUERYABLE_DATASTRUCTURES_NUMBERNAMENAME_H
#define CPPQUERYABLE_DATASTRUCTURES_NUMBERNAMENAME_H

#include <string>

#include "Person.h"
#include "Animal.h"

class PersonAndPet
{
public:
  int id;
  Person person;
  Animal pet;

  PersonAndPet(int id, Person person, Animal pet)
  {
    this->id = id;
    this->person = person;
    this->pet = pet;
  }

  int GetId() { return this->id; }
  Person GetPerson() { return this->person; }
  Animal GetAnimal() { return this->pet; }
};

#endif
