#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLEMULTISET_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLEMULTISET_H

#include <set>

#include "Queryable.h"

template<typename T>
class QueryableMultiSet : public Queryable<T, std::multiset>
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
  QueryableMultiSet() : Queryable<T, std::multiset>() { }
  QueryableMultiSet(std::multiset<T> items) : Queryable<T, std::multiset>(items) { }
};

#endif
