#ifndef CPPQUERYABLE_DATASTRUCTURES_ANIMAL_H
#define CPPQUERYABLE_DATASTRUCTURES_ANIMAL_H

#include <string>

#include "Gender.h"

class Animal
{
private:
  long id;
  long ownerId;
  std::string name;
  double age;
  int heightInches;
  Gender gender;

public:
  Animal() { this->age = 0; }
  Animal(long id, long ownerId, std::string name, double age, Gender gender);

  long GetId();
  long GetOwnerId();
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
