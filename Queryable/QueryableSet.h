#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLESET_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLESET_H

#include <set>

#include "Queryable.h"

template<typename T>
class QueryableSet : public Queryable<T, std::set>
{
protected:
  int CountInternal() override
  {
    return this->items.size();
  }

  void AddItem(T item) override
  {
    this->items.insert(item);
  }
public:
  QueryableSet() : Queryable<T, std::set>() { }
  QueryableSet(std::set<T> items) : Queryable<T, std::set>(items) { }
};

#endif
