#ifndef CPPQUERYABLE_DATASTRUCTURES_ANIMAL_H
#define CPPQUERYABLE_DATASTRUCTURES_ANIMAL_H

#include <string>

#include "Gender.hpp"

class Animal
{
private:
  size_t id;
  long ownerId;
  std::string name;
  double age;
  int heightInches;
  Gender gender;

public:
  Animal()
  {
    this->id = 0;
    this->ownerId = 0;
    this->name = "";
    this->age = 0;
    this->heightInches = 0;
    this->gender = Gender::Male;
  }
  Animal(size_t id, long ownerId, std::string name, double age, Gender gender);

  size_t GetId() const;
  long GetOwnerId() const;
  std::string GetName() const;
  void SetName(std::string name);
  double GetAge() const;
  void SetAge(double age);
  Gender GetGender() const;
  void SetGender(Gender gender);

  bool IsGender(Gender gender) const;
  bool IsMale() const;
  bool IsFemale() const;

  std::string ToString() const;

  bool operator<(const Animal & other) const;
};

#endif
