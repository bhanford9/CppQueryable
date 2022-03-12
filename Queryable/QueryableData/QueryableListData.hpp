#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLELISTDATA_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLELISTDATA_H

#include <iostream>
#include <list>

#include "QueryableData.hpp"

template<
  typename T,
  typename TAllocator = std::allocator<T>>
class QueryableListData : public QueryableData<T, std::list, TAllocator>
{
protected:

  inline virtual void Add(std::list<T, TAllocator> items, T item) const
  {
    items.push_back(item);
  }
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
};

#endif
