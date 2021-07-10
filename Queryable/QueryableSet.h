#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLESET_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLESET_H

#include <memory>
#include <set>

#include "Queryable.h"
#include "QueryableData/QueryableSetData.h"

template<typename T>
class QueryableSet : public Queryable<T>
{
public:
  QueryableSet() : Queryable<T>() { }
  QueryableSet(std::set<T> items)
  {
    this->items = std::make_unique<QueryableSetData<T>>(items);
  }
};

#endif
