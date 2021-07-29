#include <iostream>

#include "Gender.h"
#include "Person.h"


Person::Person(long id, std::string name, double age, int height, Gender gender)
{
  this->id = id;
  this->name = name;
  this->age = age;
  this->heightInches = height;
  this->gender = gender;
}

long Person::GetId()
{
  return this->id;
}

void Person::SetId(long id)
{
  this->id = id;
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

std::string Person::ToString()
{
  return "Name: " + this->name +
    "\n\tAge: " + std::to_string(this->age) +
    "\n\tHeight (in): " + std::to_string(this->heightInches) +
    "\n\tGender: " + (this->IsMale() ? "M\n" : "F\n");
}

bool Person::operator<(const Person & other) const
{
  return this->name < other.name;
}

bool Person::operator==(const Person & other) const
{
  return this->id == other.id;
}
