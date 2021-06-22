#include "Gender.h"
#include "Person.h"


Person::Person(std::string name, double age, int height, Gender gender)
{
  this->name = name;
  this->age = age;
  this->heightInches = height;
  this->gender = gender;
}

std::string Person::GetName()
{
  return this->name;
}

void Person::SetName(std::string name)
{
  this->name = name;
}

double Person::GetAge()
{
  return this->age;
}

void Person::SetAge(double age)
{
  this->age = age;
}

int Person::GetHeight()
{
  return this->heightInches;
}

void Person::SetHeight(int height)
{
  this->heightInches = height;
}

Gender Person::GetGender()
{
  return this->gender;
}

void Person::SetGender(Gender gender)
{
  this->gender = gender;
}

bool Person::IsGender(Gender gender)
{
  return this->gender == gender;
}

bool Person::IsMale()
{
  return this->gender == Gender::Male;
}

bool Person::IsFemale()
{
  return this->gender == Gender::Female;
}
