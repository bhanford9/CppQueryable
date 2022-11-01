#ifndef CPPQUERYABLE_DATASTRUCTURES_ANIMALLIBRARY_H
#define CPPQUERYABLE_DATASTRUCTURES_ANIMALLIBRARY_H

#include <memory>
#include <vector>

#include "Gender.hpp"
#include "Animal.hpp"

class AnimalLibrary
{
private:
  std::vector<std::shared_ptr<Animal>> animals;

public:
  AnimalLibrary();

  std::vector<Animal> GetAnimals();
};

#endif
