#include "Gender.h"
#include "Animal.h"


Animal::Animal(std::string name, double age, Gender gender)
{
  this->name = name;
  this->age = age;
  this->gender = gender;
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
