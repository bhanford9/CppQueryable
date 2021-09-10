#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLELISTDATA_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLELISTDATA_H

#include <iostream>
#include <list>

#include "QueryableData.h"

template<typename T, typename TAllocator = std::allocator<T>>
class QueryableListData : public QueryableData<T, std::list, TAllocator>
{
public:
  QueryableListData() : QueryableData<T, std::list, TAllocator>() { }
  QueryableListData(std::list<T, TAllocator> items)
    : QueryableData<T, std::list, TAllocator>(items)
  {
  }
  QueryableListData(const QueryableListData& data)
    : QueryableData<T, std::list, TAllocator>(data)
  {
  }

  virtual ~QueryableListData() { }

  void Add(T item) override
  {
    this->items.push_back(item);
    this->size++;
  }

  void Sort(std::function<bool(T, T)> compare) override
  {
    this->items.sort(compare);
  }
};

#endif
