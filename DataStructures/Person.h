#ifndef QUERYPLAGROUND_DATASTRUCTURES_PERSON_H
#define QUERYPLAGROUND_DATASTRUCTURES_PERSON_H

#include <string>

#include "Gender.h"

class Person
{
private:
  std::string name;
  double age;
  int heightInches;
  Gender gender;

public:
  Person(std::string name, double age, int height, Gender gender);

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
};

#endif
