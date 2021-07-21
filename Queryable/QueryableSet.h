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
  QueryableSet()
  {
    std::set<T> local;
    this->items = std::make_unique<QueryableSetData<T>>(local);
    this->type = QueryableType::Set;
  }

  QueryableSet(std::set<T> items)
  {
    this->items = std::make_unique<QueryableSetData<T>>(items);
    this->type = QueryableType::Set;
  }
};

#endif
