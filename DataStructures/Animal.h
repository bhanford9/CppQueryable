#ifndef QUERYPLAGROUND_DATASTRUCTURES_ANIMAL_H
#define QUERYPLAGROUND_DATASTRUCTURES_ANIMAL_H

#include <string>

#include "Gender.h"

class Animal
{
private:
  std::string name;
  double age;
  int heightInches;
  Gender gender;

public:
  Animal(std::string name, double age, Gender gender);

  std::string GetName();
  void SetName(std::string name);
  double GetAge();
  void SetAge(double age);
  Gender GetGender();
  void SetGender(Gender gender);

  bool IsGender(Gender gender);
  bool IsMale();
  bool IsFemale();
};

#endif
