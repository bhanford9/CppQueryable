#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLEDEQUE_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLEDEQUE_H

#include <deque>

#include "Queryable.h"

template<typename T>
class QueryableDeque : public Queryable<T, std::deque>
{
protected:
  int CountInternal() override
  {
    return this->items.size();
  }

  void AddItem(T item) override
  {
    this->items.push_back(item);
  }
public:
  QueryableDeque() : Queryable<T, std::deque>() { }
  QueryableDeque(std::deque<T> items) : Queryable<T, std::deque>(items) { }
};

#endif
