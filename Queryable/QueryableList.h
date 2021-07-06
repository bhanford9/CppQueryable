#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLELIST_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLELIST_H

#include <list>

#include "Queryable.h"

template<typename T>
class QueryableList : public Queryable<T, std::list>
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
  QueryableList() : Queryable<T, std::list>() { }
  QueryableList(std::list<T> items) : Queryable<T, std::list>(items) { }
};

#endif
