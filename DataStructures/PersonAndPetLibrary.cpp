
#include <memory>
#include <vector>

#include "PersonAndPetLibrary.hpp"
#include "Animal.hpp"
#include "Gender.hpp"
#include "Person.hpp"
#include "PersonAndPet.hpp"

PersonAndPetLibrary::PersonAndPetLibrary()
{
  this->petOwners.push_back(std::make_shared<PersonAndPet>(
    Person(1, "Person 1", 26.5, 73, Gender::Male),
    Animal(0, 1, "Animal 9", 26.5, Gender::Male)
  ));
  this->petOwners.push_back(std::make_shared<PersonAndPet>(
    Person(2, "Person 5", 26.5, 71, Gender::Male),
    Animal(1, 2, "Animal 5", 26.5, Gender::Male)
  ));
  this->petOwners.push_back(std::make_shared<PersonAndPet>(
    Person(2, "Person 5", 26.5, 71, Gender::Male),
    Animal(2, 2, "Animal 10", 26.9, Gender::Female)
  ));
  this->petOwners.push_back(std::make_shared<PersonAndPet>(
    Person(3, "Person 9", 26.9, 62, Gender::Female),
    Animal(3, 3, "Animal 2", 26.9, Gender::Female)
  ));
  this->petOwners.push_back(std::make_shared<PersonAndPet>(
    Person(4, "Person 2", 26.9, 62, Gender::Female),
    Animal(4, 4, "Animal 6", 27, Gender::Female)
  ));
  this->petOwners.push_back(std::make_shared<PersonAndPet>(
    Person(4, "Person 2", 26.9, 62, Gender::Female),
    Animal(5, 4, "Animal 1", 27.5, Gender::Male)
  ));
  this->petOwners.push_back(std::make_shared<PersonAndPet>(
    Person(4, "Person 2", 26.9, 62, Gender::Female),
    Animal(6, 4, "Animal 11", 49, Gender::Male)
  ));
  this->petOwners.push_back(std::make_shared<PersonAndPet>(
    Person(5, "Person 6", 26.9, 61, Gender::Female),
    Animal(7, 5, "Animal 12", 51, Gender::Female)
  ));
  this->petOwners.push_back(std::make_shared<PersonAndPet>(
    Person(5, "Person 6", 26.9, 61, Gender::Female),
    Animal(8, 5, "Animal 8", 51, Gender::Female)
  ));
  this->petOwners.push_back(std::make_shared<PersonAndPet>(
    Person(6, "Person 10", 51, 55, Gender::Female),
    Animal(9, 6, "Animal 3", 52, Gender::Male)
  ));
  this->petOwners.push_back(std::make_shared<PersonAndPet>(
    Person(7, "Person 4", 51, 55, Gender::Female),
    Animal(10, 7, "Animal 7", 52, Gender::Male)
  ));
  this->petOwners.push_back(std::make_shared<PersonAndPet>(
    Person(8, "Person 8", 51, 55, Gender::Female),
    Animal(11, 8, "Animal 4", 61, Gender::Female)
  ));
}

std::vector<PersonAndPet> PersonAndPetLibrary::GetPetOwners() const
{
  std::vector<PersonAndPet> newPetOwners;

  for (const auto& petOwner : this->petOwners)
  {
    newPetOwners.push_back(*petOwner.get());
  }

  return newPetOwners;
}
