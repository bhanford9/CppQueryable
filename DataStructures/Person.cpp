#include <iostream>
#include <sstream>
#include <utility>

#include "Person.hpp"
#include "Gender.hpp"


Person::Person(size_t id, std::string name, double age, int height, Gender gender)
{
  this->id = id;
  this->name = std::move(name);
  this->age = age;
  this->heightInches = height;
  this->gender = gender;
}

size_t Person::GetId() const
{
  return this->id;
}

void Person::SetId(const long id)
{
  this->id = id;
}

std::string Person::GetName() const
{
  return this->name;
}

void Person::SetName(std::string name)
{
  this->name = std::move(name);
}

double Person::GetAge() const
{
  return this->age;
}

void Person::SetAge(const double age)
{
  this->age = age;
}

int Person::GetHeight() const
{
  return this->heightInches;
}

void Person::SetHeight(const int height)
{
  this->heightInches = height;
}

Gender Person::GetGender() const
{
  return this->gender;
}

void Person::SetGender(const Gender gender)
{
  this->gender = gender;
}

bool Person::IsGender(const Gender gender) const
{
  return this->gender == gender;
}

bool Person::IsMale() const
{
  return this->gender == Gender::Male;
}

bool Person::IsFemale() const
{
  return this->gender == Gender::Female;
}

std::string Person::ToString() const
{
  return
    "Name: " + this->name +
    "\n\tId: " + std::to_string(this->id) +
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

std::ostream & Person::operator<<(std::ostream & str) const
{
  str << this->ToString();
  return str;
}
