#include <iostream>
#include "Gender.h"
#include "Animal.h"


Animal::Animal(long id, long ownerId, std::string name, double age, Gender gender)
{
  this->id = id;
  this->ownerId = ownerId;
  this->name = name;
  this->age = age;
  this->gender = gender;
}

long Animal::GetId()
{
  return this->id;
}

long Animal::GetOwnerId()
{
  return this->ownerId;
}

std::string Animal::GetName()
{
  return this->name;
}

void Animal::SetName(std::string name)
{
  this->name = name;
}

double Animal::GetAge()
{
  return this->age;
}

void Animal::SetAge(double age)
{
  this->age = age;
}

Gender Animal::GetGender()
{
  return this->gender;
}

void Animal::SetGender(Gender gender)
{
  this->gender = gender;
}

bool Animal::IsGender(Gender gender)
{
  return this->gender == gender;
}

bool Animal::IsMale()
{
  return this->gender == Gender::Male;
}

bool Animal::IsFemale()
{
  return this->gender == Gender::Female;
}

std::string Animal::ToString()
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
