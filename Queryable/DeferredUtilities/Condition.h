#ifndef CPPQUERYABLE_QUERYABLE_DEFERREDUTILITIES_LISTITERATOR_H
#define CPPQUERYABLE_QUERYABLE_DEFERREDUTILITIES_LISTITERATOR_H

#include <functional>
#include <iostream>

template<typename T>
class Condition
{
private:
  bool applied = false;
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

    this->applied = false;
  }

  bool Passes(T obj)
  {
    return !this->condition || this->applied || this->condition(obj);
  }

  void MarkApplied(bool applied = true)
  {
    this->applied = applied;
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
