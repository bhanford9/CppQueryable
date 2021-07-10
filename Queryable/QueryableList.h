#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLELIST_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLELIST_H

#include <memory>
#include <list>

#include "Queryable.h"
#include "QueryableData/QueryableListData.h"

template<typename T>
class QueryableList : public Queryable<T>
{
public:
  QueryableList() : Queryable<T>() { }
  QueryableList(std::list<T> items)
  {
    this->items = std::make_unique<QueryableListData<T>>(items);
  }
};

#endif
