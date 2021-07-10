#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLEDEQUE_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLEDEQUE_H

#include <memory>
#include <deque>

#include "Queryable.h"
#include "QueryableData/QueryableDequeData.h"

template<typename T>
class QueryableDeque : public Queryable<T>
{
public:
  QueryableDeque() : Queryable<T>() { }
  QueryableDeque(std::deque<T> items)
  {
    this->items = std::make_unique<QueryableDequeData<T>>(items);
  }
};

#endif
