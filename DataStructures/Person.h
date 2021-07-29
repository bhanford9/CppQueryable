#ifndef CPPQUERYABLE_DATASTRUCTURES_PERSON_H
#define CPPQUERYABLE_DATASTRUCTURES_PERSON_H

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
  Person() { this->age = 0; }
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

  bool IsGender(Gender gender);
  bool IsMale();
  bool IsFemale();

  std::string ToString();

  bool operator<(const Person & other) const;
  bool operator==(const Person & other) const;
};

#endif
