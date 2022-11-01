#ifndef CPPQUERYABLE_DATASTRUCTURES_PERSON_H
#define CPPQUERYABLE_DATASTRUCTURES_PERSON_H

#include <iostream>
#include <string>

#include "Gender.hpp"

class Person
{
private:
  long id;
  std::string name;
  double age;
  int heightInches;
  Gender gender;

public:
  Person() :  
    id(0),
    name(""),
    age(0),
    heightInches(0),
    gender(Gender::Male)
  {
  }
  Person(const Person & other)
  {
    if (this != &other)
    {
      this->id = other.id;
      this->age = other.age;
      this->heightInches = other.heightInches;
      this->gender = other.gender;
      name = other.name;
    }
  }
  Person(Person && other)
  {
    if (this != &other)
    {
      this->id = other.id;
      this->age = other.age;
      this->heightInches = other.heightInches;
      this->gender = other.gender;
      name = std::move(other.name);
    }
  }
  Person(long id, std::string name, double age, int height, Gender gender);

  long GetId() const;
  void SetId(long id);
  std::string GetName() const;
  void SetName(std::string name);
  double GetAge() const;
  void SetAge(double age);
  int GetHeight() const;
  void SetHeight(int height);
  Gender GetGender() const;
  void SetGender(Gender gender);

  bool IsGender(Gender gender) const;
  bool IsMale() const;
  bool IsFemale() const;

  std::string ToString() const;

  Person operator=(const Person & other)
  {
    if (this != &other)
    {
      this->id = other.id;
      this->age = other.age;
      this->heightInches = other.heightInches;
      this->gender = other.gender;
      this->name = other.name;
    }

    return *this;
  }

  Person operator=(Person && other)
  {
    if (this != &other)
    {
      this->id = other.id;
      this->age = other.age;
      this->heightInches = other.heightInches;
      this->gender = other.gender;
      name = std::move(other.name);
    }

    return *this;
  }

  bool operator<(const Person & other) const;
  bool operator==(const Person & other) const;
  std::ostream & operator<<(std::ostream & str);
  friend std::ostream & operator<<(std::ostream & str, const Person & v)
  {
    str << v.ToString();
    return str;
  }
};

#endif
