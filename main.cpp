#include <iostream>
#include <vector>

#include "DataStructures/Animal.h"
#include "DataStructures/Gender.h"
#include "DataStructures/NumberNameName.h"
#include "DataStructures/Person.h"
#include "Queryable/Queryable.h"

int main()
{
  std::cout << "Hello World!\n" << std::endl;

  Person brian("Donald Duck", 26.5, 73, Gender::Male);
  Person person1("Person 1", 26.5, 73, Gender::Male);
  Person person5("Person 5", 26.5, 71, Gender::Male);
  Person hannah("Mickey Mouse", 26.9, 62, Gender::Female);
  Person person2("Person 2", 26.9, 62, Gender::Female);
  Person person6("Person 6", 26.9, 61, Gender::Female);
  Person jennylu("Jennylu Farmer", 51, 55, Gender::Female);
  Person person4("Person 4", 51, 55, Gender::Female);
  Person person8("Person 8", 51, 55, Gender::Female);
  Person person3("Person 3", 52, 68, Gender::Male);
  Person person7("Person 7", 52, 60, Gender::Male);
  Person joebob("Joebob Farmer", 61, 68, Gender::Male);

  Animal brianA("Donald Duck", 26.5, Gender::Male);
  Animal animal5("Animal 5", 26.5, Gender::Male);
  Animal hannahA("Mickey Mouse", 26.9, Gender::Female);
  Animal animal2("Animal 2", 26.9, Gender::Female);
  Animal animal6("Animal 6", 27, Gender::Female);
  Animal animal1("Animal 1", 27.5, Gender::Male);
  Animal joebobA("Joebob Farmer", 49, Gender::Male);
  Animal jennyluA("Jennylu Farmer", 51, Gender::Female);
  Animal animal8("Animal 8", 51, Gender::Female);
  Animal animal3("Animal 3", 52, Gender::Male);
  Animal animal7("Animal 7", 52, Gender::Male);
  Animal animal4("Animal 4", 61, Gender::Female);

  std::vector<Person> people
  {
    brian,
    hannah,
    joebob,
    jennylu,
    person1,
    person2,
    person3,
    person4,
    person5,
    person6,
    person7,
    person8
  };
  std::vector<Animal> animals
  {
    brianA,
    hannahA,
    joebobA,
    jennyluA,
    animal1,
    animal2,
    animal3,
    animal4,
    animal5,
    animal6,
    animal7,
    animal8,
  };

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

  std::cout << "old people found: " << old.size() << std::endl;

  double averageAge = queryablePeople.Average<double>([](Person person){ return person.GetAge(); });

  std::cout << "average age: " << averageAge << std::endl;

  double averageMaleHeight = queryablePeople
    .Where([](Person person){ return person.IsMale(); })
    .Average<int>([](Person person){ return person.GetHeight(); });

  std::cout << "average male height: " << averageMaleHeight << std::endl;

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
        [](Person p, Animal a) { return NumberNameName(p.GetAge(), p.GetName(), a.GetName()); });


  return averageAge + averageMaleHeight;
}
