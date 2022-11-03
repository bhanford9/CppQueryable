#ifndef CPPQUERYABLE_DATASTRUCTURES_NUMBERNAMENAME_H
#define CPPQUERYABLE_DATASTRUCTURES_NUMBERNAMENAME_H

#include <string>

#include "Animal.hpp"
#include "Person.hpp"

class PersonAndPet
{
public:
  Person person;
  Animal pet;

  PersonAndPet() { }
  PersonAndPet(Person person, Animal pet)
  {
    this->person = person;
    this->pet = pet;
  }

  Person GetPerson() { return this->person; }
  Animal GetAnimal() { return this->pet; }


  bool operator<(const PersonAndPet & other) const
  {
    return this->person < other.person;
  }

  std::string ToString()
  {
    return
      "\n" +
      this->GetPerson().ToString() +
      this->GetAnimal().ToString() +
      "\n";
  }
};

#endif
