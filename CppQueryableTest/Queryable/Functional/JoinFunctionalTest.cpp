#include <gtest/gtest.h>

#include <array>
#include <deque>
#include <iostream>
#include <list>
#include <set>
#include <string>
#include <vector>

#include "../../../DataStructures/Animal.h"
#include "../../../DataStructures/AnimalLibrary.h"
#include "../../../DataStructures/Gender.h"
#include "../../../DataStructures/Person.h"
#include "../../../DataStructures/PersonAndPet.h"
#include "../../../DataStructures/PersonLibrary.h"

#include "../../../Queryable/QueryBuilder.h"

using namespace QueryBuilder;

class JoinFunctionalTest : public ::testing::Test
{
protected:
  QueryableVector<Person> people;
  //QueryableVector<Animal> animals;

  void SetUp() override
  {
    this->people = QueryableVector<Person>(PersonLibrary().GetPeople());
    //this->animals = QueryableVector<Animal>(AnimalLibrary().GetAnimals());
  }

  void TearDown() override {}
};

TEST_F(JoinFunctionalTest, JoinUninitializedTest)
{
}
