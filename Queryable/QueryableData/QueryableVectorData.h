#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLEVECTORDATA_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLEVECTORDATA_H

#include <iostream>
#include <vector>

#include "QueryableData.h"

template<typename T, typename TAllocator = std::allocator<T>>
class QueryableVectorData : public QueryableData<T, std::vector, TAllocator>
{
public:
  QueryableVectorData() : QueryableData<T, std::vector, TAllocator>() { }
  QueryableVectorData(std::vector<T, TAllocator> items)
    : QueryableData<T, std::vector, TAllocator>(items)
  {
  }
  QueryableVectorData(const QueryableVectorData& data)
    : QueryableData<T, std::vector, TAllocator>(data)
  {
  }

  virtual ~QueryableVectorData() { }

  void Add(T item) override
  {
    this->items.push_back(item);
    this->size++;
  }

  int Count() override
  {
    return this->items.size();
  }

  void RemoveLast() override
  {
    this->items.pop_back();
    this->size--;
  }

  void RemoveFirst() override
  {

  }

  void Sort(std::function<bool(T, T)> compare) override
  {
    std::sort(this->items.begin(), this->items.end(), compare);
  }
};

#endif
