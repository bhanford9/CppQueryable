#include "Animal.hpp"
#include <sstream>
#include <utility>
#include "Gender.hpp"


Animal::Animal(
  const size_t id,
  const long ownerId,
  std::string name,
  const double age,
  const Gender gender) :
  heightInches(0)
{
  this->id = id;
  this->ownerId = ownerId;
  this->name = std::move(name);
  this->age = age;
  this->gender = gender;
}

size_t Animal::GetId() const
{
  return this->id;
}

long Animal::GetOwnerId() const
{
  return this->ownerId;
}

std::string Animal::GetName() const
{
  return this->name;
}

void Animal::SetName(std::string name)
{
  this->name = std::move(name);
}

double Animal::GetAge() const
{
  return this->age;
}

void Animal::SetAge(const double age)
{
  this->age = age;
}

Gender Animal::GetGender() const
{
  return this->gender;
}

void Animal::SetGender(const Gender gender)
{
  this->gender = gender;
}

bool Animal::IsGender(const Gender gender) const
{
  return this->gender == gender;
}

bool Animal::IsMale() const
{
  return this->gender == Gender::Male;
}

bool Animal::IsFemale() const
{
  return this->gender == Gender::Female;
}

std::string Animal::ToString() const
{
  return
    "Name: " + this->name +
    "\n\tOwner Id: " + std::to_string(this->ownerId) +
    "\n\tId: " + std::to_string(this->id) +
    "\n\tAge: " + std::to_string(this->age) +
    "\n\tGender: " + (this->IsMale() ? "M\n" : "F\n");
}

bool Animal::operator<(const Animal & other) const
{
  return this->name < other.name;
}
