#ifndef CPPQUERYABLE_DATASTRUCTURES_PERSONANDPETLIBRARY_H
#define CPPQUERYABLE_DATASTRUCTURES_PERSONANDPETLIBRARY_H

#include <memory>
#include <vector>

#include "Person.hpp"
#include "PersonAndPet.hpp"

class PersonAndPetLibrary
{
private:
  std::vector<std::shared_ptr<PersonAndPet>> petOwners;

public:
  PersonAndPetLibrary();

  std::vector<PersonAndPet> GetPetOwners() const;
};

#endif
