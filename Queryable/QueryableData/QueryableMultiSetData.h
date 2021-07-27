#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLEMULTISETDATA_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLEMULTISETDATA_H

#include <iostream>
#include <memory>
#include <set>

#include "QueryableData.h"

template<
  typename T,
  typename TCompare = std::less<T>,
  typename TAllocator = std::allocator<T>>
class QueryableMultiSetData : public QueryableData<T, std::multiset, TCompare, TAllocator>
{
public:
  QueryableMultiSetData() : QueryableData<T, std::multiset, TCompare, TAllocator>() { }
  QueryableMultiSetData(std::multiset<T, TCompare, TAllocator> items)
    : QueryableData<T, std::multiset, TCompare, TAllocator>(items)
  {
    this->InitForwardBegin();
    this->InitForwardEnd();
    this->InitReverseBegin();
    this->InitReverseEnd();
  }
  QueryableMultiSetData(const QueryableMultiSetData& data)
    : QueryableData<T, std::multiset, TCompare, TAllocator>(data)
  {
  }

  virtual ~QueryableMultiSetData() { }

  void Add(T item) override
  {
    this->items.insert(item);
  }

  int Count() override
  {
    return this->items.size();
  }

  void RemoveLast() override
  {
    if (this->Count() > 0)
    {
      this->items.erase(--this->items.end());
    }
  }

  void RemoveFirst() override
  {

  }

  void Sort(std::function<bool(T, T)> compare) override
  {
    // already sorted
  }
};

#endif
