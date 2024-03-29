
#include <memory>
#include <vector>

#include "Gender.hpp"
#include "Animal.hpp"
#include "AnimalLibrary.hpp"

AnimalLibrary::AnimalLibrary()
{
  this->animals.push_back(std::make_shared<Animal>(this->animals.size(), 1, "Animal 9", 26.5, Gender::Male));
  this->animals.push_back(std::make_shared<Animal>(this->animals.size(), 2, "Animal 5", 26.5, Gender::Male));
  this->animals.push_back(std::make_shared<Animal>(this->animals.size(), 2, "Animal 10", 26.9, Gender::Female));
  this->animals.push_back(std::make_shared<Animal>(this->animals.size(), 3, "Animal 2", 26.9, Gender::Female));
  this->animals.push_back(std::make_shared<Animal>(this->animals.size(), 4, "Animal 6", 27, Gender::Female));
  this->animals.push_back(std::make_shared<Animal>(this->animals.size(), 4, "Animal 1", 27.5, Gender::Male));
  this->animals.push_back(std::make_shared<Animal>(this->animals.size(), 4, "Animal 11", 49, Gender::Male));
  this->animals.push_back(std::make_shared<Animal>(this->animals.size(), 5, "Animal 12", 51, Gender::Female));
  this->animals.push_back(std::make_shared<Animal>(this->animals.size(), 5, "Animal 8", 51, Gender::Female));
  this->animals.push_back(std::make_shared<Animal>(this->animals.size(), 6, "Animal 3", 52, Gender::Male));
  this->animals.push_back(std::make_shared<Animal>(this->animals.size(), 7, "Animal 7", 52, Gender::Male));
  this->animals.push_back(std::make_shared<Animal>(this->animals.size(), 8, "Animal 4", 61, Gender::Female));
  this->animals.push_back(std::make_shared<Animal>(this->animals.size(), 100, "No Owner", 46, Gender::Female));

}

std::vector<Animal> AnimalLibrary::GetAnimals() const
{
  std::vector<Animal> newAnimals;

  for (const auto& animal : this->animals)
  {
    newAnimals.push_back(*animal.get());
  }

  return newAnimals;
}
