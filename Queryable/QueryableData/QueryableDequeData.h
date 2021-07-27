#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLEDEQUEDATA_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLEDEQUEDATA_H

#include <algorithm>
#include <deque>
#include <iostream>
#include <memory>

#include "QueryableData.h"

template<typename T, typename TAllocator = std::allocator<T>>
class QueryableDequeData : public QueryableData<T, std::deque, TAllocator>
{
public:
  QueryableDequeData() : QueryableData<T, std::deque, TAllocator>() { }
  QueryableDequeData(std::deque<T, TAllocator> items)
    : QueryableData<T, std::deque, TAllocator>(items)
  {
  }
  QueryableDequeData(const QueryableDequeData& data)
    : QueryableData<T, std::deque, TAllocator>(data)
  {
  }

  virtual ~QueryableDequeData() { }

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

  void Sort(std::function<bool(T, T)> compare) override
  {
    std::sort(this->items.begin(), this->items.end(), compare);
  }
};

#endif
