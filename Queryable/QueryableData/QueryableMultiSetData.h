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
  typedef typename std::multiset<T>::iterator t_forwardIterator;
public:
  QueryableMultiSetData(TCompare compare = TCompare())
    : QueryableData<T, std::multiset, TCompare, TAllocator>()
  {
    this->items = std::multiset<T, TCompare>(compare);
    this->InitForwardBegin();
    this->InitForwardEnd();
    this->InitReverseBegin();
    this->InitReverseEnd();
  }
  QueryableMultiSetData(std::multiset<T, TCompare, TAllocator> items)
    : QueryableData<T, std::multiset, TCompare, TAllocator>(items)
  {
  }
  QueryableMultiSetData(const QueryableMultiSetData& data)
    : QueryableData<T, std::multiset, TCompare, TAllocator>(data)
  {
  }

  virtual ~QueryableMultiSetData() { }

  void Add(T item) override
  {
    this->items.insert(item);
    this->size++;
  }

  void Sort(std::function<bool(T, T)> compare) override
  {
    // already sorted
  }
};

#endif
