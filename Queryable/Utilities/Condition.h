#ifndef CPPQUERYABLE_QUERYABLE_UTILITIES_CONDITION_H
#define CPPQUERYABLE_QUERYABLE_UTILITIES_CONDITION_H

#include <functional>
#include <iostream>

template<typename T>
class Condition
{
private:
  bool applied = false;
  std::function<bool(const T &)> condition;

public:
  Condition() { }

  void Add(std::function<bool(const T &)> condition)
  {
    if (this->condition)
    {
      std::function<bool(T)> copy = this->condition;
      this->condition = [&](T obj) { return copy(obj) && condition(obj); };
    }
    else
    {
      this->condition = condition;
    }

    this->applied = false;
  }

  bool Passes(const T & obj) const
  {
    return !this->condition || this->applied || this->condition(obj);
  }

  void MarkApplied(bool applied = true)
  {
    this->applied = applied;
  }

  Condition & operator+=(std::function<bool(const T &)> condition)
  {
    this->Add(condition);
    return *this;
  }

  bool operator()(const T & obj) const
  {
    return this->Passes(obj);
  }

  operator bool() const
  {
    return this->condition ? true : false;
  }
};

#endif
