#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLEVECTORDATA_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLEVECTORDATA_H

#include <iostream>
#include <vector>

#include "QueryableData.h"
#include "../Iterators/Iterator.h"

template<typename T>
class QueryableVectorData : public QueryableData<T, std::vector>
{
public:
  QueryableVectorData() : QueryableData<T, std::vector>() { }
  QueryableVectorData(std::vector<T> items)
    : QueryableData<T, std::vector>(items)
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
