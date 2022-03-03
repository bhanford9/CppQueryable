
#include <memory>
#include <vector>

#include "Gender.hpp"
#include "Person.hpp"
#include "PersonLibrary.hpp"

PersonLibrary::PersonLibrary()
{
  this->people.push_back(std::make_unique<Person>(this->people.size(), "Person 3", 26.5, 73, Gender::Male));
  this->people.push_back(std::make_unique<Person>(this->people.size(), "Person 1", 26.5, 73, Gender::Male));
  this->people.push_back(std::make_unique<Person>(this->people.size(), "Person 5", 26.5, 71, Gender::Male));
  this->people.push_back(std::make_unique<Person>(this->people.size(), "Person 9", 26.9, 62, Gender::Female));
  this->people.push_back(std::make_unique<Person>(this->people.size(), "Person 2", 26.9, 62, Gender::Female));
  this->people.push_back(std::make_unique<Person>(this->people.size(), "Person 6", 26.9, 61, Gender::Female));
  this->people.push_back(std::make_unique<Person>(this->people.size(), "Person 10", 51, 55, Gender::Female));
  this->people.push_back(std::make_unique<Person>(this->people.size(), "Person 4", 51, 55, Gender::Female));
  this->people.push_back(std::make_unique<Person>(this->people.size(), "Person 8", 51, 55, Gender::Female));
  this->people.push_back(std::make_unique<Person>(this->people.size(), "Person 7", 52, 60, Gender::Male));
  this->people.push_back(std::make_unique<Person>(this->people.size(), "Person 11", 61, 68, Gender::Male));
}

std::vector<Person> PersonLibrary::GetPeople()
{
  std::vector<Person> newPeople;

  for (const auto& person : this->people)
  {
    newPeople.push_back(*person.get());
  }

  return newPeople;
}
