#ifndef DERIVED_DATA
#define DERIVED_DATA

#include "Base.hpp"

template<typename T1, typename T2>
class Derived : public Base<T1>
{
private:
  T2 notData;

public:
  T2 GetNotData() { return this->notData; }
  void SetNotData(T2 notData) { this->notData = notData; }
};

#endif
