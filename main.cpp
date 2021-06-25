#include <iostream>
#include <vector>

#include "DataStructures/Animal.h"
#include "DataStructures/AnimalLibrary.h"
#include "DataStructures/Gender.h"
#include "DataStructures/NumberNameName.h"
#include "DataStructures/People.h"
#include "DataStructures/Person.h"
#include "DataStructures/PersonLibrary.h"
#include "Queryable/Queryable.h"

int main()
{
  std::vector<Person> people = PersonLibrary().GetPeople();
  std::vector<Animal> animals = AnimalLibrary().GetAnimals();

  Queryable<Person, std::vector> queryablePeople(people);

  std::vector<Person> males = queryablePeople
    .Where([](Person person){ return person.IsMale(); })
    .ToVector();

  std::vector<Person> females = queryablePeople
    .Where([](Person person){ return person.IsFemale(); })
    .ToVector();

  std::vector<Person> young = queryablePeople
    .Where([](Person person){ return person.GetAge() < 50; })
    .ToVector();

  std::vector<Person> old = queryablePeople
    .Where([](Person person){ return person.GetAge() >= 50; })
    .ToVector();

  double averageAge = queryablePeople.Average<double>([](Person person){ return person.GetAge(); });

  double averageMaleHeight = queryablePeople
    .Where([](Person person){ return person.IsMale(); })
    .Average<int>([](Person person){ return person.GetHeight(); });

  std::vector<Person> aged = queryablePeople
    .OnEach([](Person person){ person.SetAge(person.GetAge() + 100); return person; })
    .ToVector();

  std::vector<Person> heightOrdered = queryablePeople
    .OrderBy<int>([](Person person){ return person.GetHeight(); })
    .ToVector();

  Queryable<NumberNameName, std::vector> keyValues =
    queryablePeople
      .Join<Animal, double, NumberNameName>(
        animals,
        [](Person p) { return p.GetAge(); },
        [](Animal a) { return a.GetAge(); },
        [](Person p, Animal a) { return NumberNameName(p.GetAge(), p.GetName(), a.GetName()); });\

  Queryable<Person, std::vector>(aged)
    .Concat(heightOrdered, [](std::vector<Person> * collection, Person person) { collection->push_back(person); })
    .ForEach([](Person person) { std::cout << person.ToString() << std::endl; });

  std::string emptyString = "";
  std::string csv = queryablePeople
    .Aggregate<std::string, std::string>(
      &emptyString,
      [](std::string accumulated, Person person) { return accumulated + ", " + person.GetName(); },
      [](std::string output) { return output.erase(0, 2); });

  std::cout << csv << std::endl;

  std::cout << "max age: " << queryablePeople.Max<double>([](Person person) { return person.GetAge(); }) << std::endl;
  std::cout << "first alphebetically: " << queryablePeople.Min<std::string>([](Person person) { return person.GetName(); }) << std::endl;

  People childQueryable(people);
  childQueryable
    .Where([](Person person) { return person.IsMale(); })
    .OrderBy<std::string>([](Person person) { return person.GetName(); })
    .Select<std::string>([](Person person) { return person.GetName(); })
    .ForEach([](std::string name) { std::cout << name << std::endl; });

  return averageAge + averageMaleHeight;
}
