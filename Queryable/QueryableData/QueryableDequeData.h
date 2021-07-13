#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLEDEQUEDATA_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLEDEQUEDATA_H

#include <deque>
#include <iostream>
#include <memory>

#include "QueryableData.h"
#include "../Iterators/Iterator.h"

template<typename T>
class QueryableDequeData : public QueryableData<T, std::deque>
{
public:
  QueryableDequeData() : QueryableData<T, std::deque>() { }
  QueryableDequeData(std::deque<T> items)
    : QueryableData<T, std::deque>(items)
  {
  }

  void Add(T item) override
  {
    this->items.push_back(item);
  }

  int Count() override
  {
    return this->items.size();
  }

  void RemoveLast() override
  {
    this->items.pop_back();
  }

  void RemoveFirst() override
  {

  }
};

#endif
