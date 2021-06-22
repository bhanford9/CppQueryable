#ifndef QUERYPLAGROUND_DATASTRUCTURES_NUMBERNAMENAME_H
#define QUERYPLAGROUND_DATASTRUCTURES_NUMBERNAMENAME_H

#include <string>

class NumberNameName
{
public:
  double Number;
  std::string Name1;
  std::string Name2;

  NumberNameName(double number, std::string name1, std::string name2)
  {
    this->Number = number;
    this->Name1 = name1;
    this->Name2 = name2;
  }
};

#endif
