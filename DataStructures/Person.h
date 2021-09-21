#ifndef CPPQUERYABLE_DATASTRUCTURES_PERSON_H
#define CPPQUERYABLE_DATASTRUCTURES_PERSON_H

#include <iostream>
#include <string>

#include "Gender.h"

class Person
{
private:
  long id;
  std::string name;
  double age;
  int heightInches;
  Gender gender;

public:
  Person()
  {
    // std::cout << "enter person default constructor" << std::endl;
    this->id = 0;
    this->name = "";
    this->age = 0;
    this->heightInches = 0;
    this->gender = Gender::Male;
    // std::cout << "exit person default constructor" << std::endl;
  }
  Person(const Person & other) = default;
  // {
  //   // std::cout << "enter person copy constructor" << std::endl;
  //   this->id = other.id;
  //   this->name = other.name;
  //   this->age = other.age;
  //   this->heightInches = other.heightInches;
  //   this->gender = other.gender;
  //   // std::cout << "exit person copy constructor" << std::endl;
  // }
  Person(long id, std::string name, double age, int height, Gender gender);

  long GetId();
  void SetId(long id);
  std::string GetName();
  void SetName(std::string name);
  double GetAge();
  void SetAge(double age);
  int GetHeight();
  void SetHeight(int height);
  Gender GetGender();
  void SetGender(Gender gender);

  bool IsGender(Gender gender) const;
  bool IsMale() const;
  bool IsFemale() const;

  std::string ToString() const;

  // Person operator=(Person other)
  // {
  //   std::cout << "enter person copy method" << std::endl;
  //   this->id = other.id;
  //   this->name = other.name;
  //   this->age = other.age;
  //   this->heightInches = other.heightInches;
  //   this->gender = other.gender;
  //   std::cout << "exit person copy method" << std::endl;
  //   return *this;
  // }

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
