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
  QueryableList()
  {
    std::list<T> local;
    this->items = std::make_unique<QueryableListData<T>>(local);
    this->type = QueryableType::List;
  }

  QueryableList(std::list<T> items)
  {
    this->items = std::make_unique<QueryableListData<T>>(items);
    this->type = QueryableType::List;
  }
};

#endif
