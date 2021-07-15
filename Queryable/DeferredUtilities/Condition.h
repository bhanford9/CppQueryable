#ifndef CPPQUERYABLE_QUERYABLE_DEFERREDUTILITIES_LISTITERATOR_H
#define CPPQUERYABLE_QUERYABLE_DEFERREDUTILITIES_LISTITERATOR_H

#include <functional>
#include <iostream>

template<typename T>
class Condition
{
private:
  std::function<bool(T)> condition;

public:
  Condition() { }

  void Add(std::function<bool(T)> condition)
  {
    if (this->condition)
    {
      std::function<bool(T)> copy = this->condition;
      this->condition = [&](T obj) -> bool { return copy(obj) && condition(obj); };
    }
    else
    {
      this->condition = condition;
    }
  }

  bool Passes(T obj)
  {
    return !this->condition || this->condition(obj);
  }

  Condition & operator+=(std::function<bool(T)> condition)
  {
    this->Add(condition);
    return *this;
  }

  bool operator()(T obj)
  {
    return this->Passes(obj);
  }

  operator bool() const
  {
    return this->condition;
  }
};

#endif
