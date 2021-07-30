#ifndef CPPQUERYABLE_DATASTRUCTURES_PERSONANDPETLIBRARY_H
#define CPPQUERYABLE_DATASTRUCTURES_PERSONANDPETLIBRARY_H

#include <memory>
#include <vector>

#include "Gender.h"
#include "Person.h"
#include "Animal.h"
#include "PersonAndPet.h"

class PersonAndPetLibrary
{
private:
  std::vector<std::unique_ptr<PersonAndPet>> petOwners;

public:
  PersonAndPetLibrary();

  std::vector<PersonAndPet> GetPetOwners();
};

#endif
