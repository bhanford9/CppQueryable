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
  QueryableDeque()
  {
    std::deque<T> local;
    this->items = std::make_unique<QueryableDequeData<T>>(local);
    this->type = QueryableType::Deque;
  }

  QueryableDeque(std::deque<T> items)
  {
    this->items = std::make_unique<QueryableDequeData<T>>(items);
    this->type = QueryableType::Deque;
  }
};

#endif
