#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLESETDATA_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLESETDATA_H

#include <iostream>
#include <memory>
#include <set>

#include "QueryableData.h"

template<
  typename T,
  typename TCompare = std::less<T>,
  typename TAllocator = std::allocator<T>>
class QueryableSetData : public QueryableData<T, std::set, TCompare, TAllocator>
{
public:
  QueryableSetData(TCompare compare = TCompare())
    : QueryableData<T, std::set, TCompare, TAllocator>()
  {
    this->items = std::set<T, TCompare>(compare);
    this->InitForwardBegin();
    this->InitForwardEnd();
    this->InitReverseBegin();
    this->InitReverseEnd();
  }
  QueryableSetData(std::set<T, TCompare, TAllocator> items)
    : QueryableData<T, std::set, TCompare, TAllocator>(items)
  {
  }
  QueryableSetData(const QueryableSetData& data)
    : QueryableData<T, std::set, TCompare, TAllocator>(data)
  {
  }

  virtual ~QueryableSetData() { }

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
