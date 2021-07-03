#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLEVECTOR_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLEVECTOR_H

#include <vector>

#include "Queryable.h"

template<typename T>
class QueryableVector : public Queryable<T, std::vector>
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
  QueryableVector() : Queryable<T, std::vector>() { }
  QueryableVector(std::vector<T> items) : Queryable<T, std::vector>(items) { }
};

#endif
