#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLEMULTISET_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLEMULTISET_H

#include <memory>
#include <set>

#include "Queryable.h"
#include "QueryableData/QueryableMultiSetData.h"

template<typename T>
class QueryableMultiSet : public Queryable<T>
{
public:
  QueryableMultiSet() : Queryable<T>() { }
  QueryableMultiSet(std::multiset<T> items)
  {
    this->items = std::make_unique<QueryableMultiSetData<T>>(items);
  }
};

#endif
