#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLELISTDATA_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLELISTDATA_H

#include <iostream>
#include <list>

#include "QueryableData.h"

template<typename T, typename TAllocator = std::allocator<T>>
class QueryableListData : public QueryableData<T, T, std::list, TAllocator>
{
protected:

  inline virtual void Add(std::list<T, TAllocator> items, T item) const
  {
    items.push_back(item);
  }
public:
  QueryableListData() : QueryableData<T, T, std::list, TAllocator>() { }
  QueryableListData(std::list<T, TAllocator> items)
    : QueryableData<T, T, std::list, TAllocator>(items)
  {
  }
  QueryableListData(const QueryableListData& data)
    : QueryableData<T, T, std::list, TAllocator>(data)
  {
  }

  virtual ~QueryableListData() { }

  void Add(T item) override
  {
    this->items.push_back(item);
    this->size++;
  }

  void Sort(std::function<bool(T, T)> compare = [](T a, T b) { return a < b; }) override
  {
    this->items.sort(compare);
  }
};

#endif
