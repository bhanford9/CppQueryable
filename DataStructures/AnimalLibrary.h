#ifndef CPPQUERYABLE_DATASTRUCTURES_ANIMALLIBRARY_H
#define CPPQUERYABLE_DATASTRUCTURES_ANIMALLIBRARY_H

#include <memory>
#include <vector>

#include "Gender.h"
#include "Animal.h"

class AnimalLibrary
{
private:
  std::vector<std::unique_ptr<Animal>> animals;

public:
  AnimalLibrary();

  std::vector<Animal> GetAnimals();
};

#endif
