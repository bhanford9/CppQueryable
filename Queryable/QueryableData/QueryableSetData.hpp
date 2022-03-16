#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLESETDATA_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLESETDATA_H

#include <iostream>
#include <memory>
#include <set>

#include "SortedQueryableData.hpp"

template<
  typename T,
  typename TCompare = std::less<T>,
  typename TAllocator = std::allocator<T>>
class QueryableSetData : public SortedQueryableData<T, std::set, TCompare, TAllocator>
{
  typedef typename std::vector<T>::iterator TVectorIterator;
public:
  QueryableSetData(TCompare comparator = {})
    : SortedQueryableData<T, std::set, TCompare, TAllocator>() { }

  // QueryableSetData(std::set<T, TCompare, TAllocator> items)
  //   : SortedQueryableData<T, std::set, TCompare, TAllocator>(items) { }

  QueryableSetData(const std::set<T, TCompare, TAllocator> & items)
    : SortedQueryableData<T, std::set, TCompare, TAllocator>(items) { }

  QueryableSetData(std::set<T, TCompare, TAllocator> && items)
    : SortedQueryableData<T, std::set, TCompare, TAllocator>(std::move(items)) { }

  QueryableSetData(const QueryableSetData<T, TCompare, TAllocator> & data)
    : SortedQueryableData<T, std::set, TCompare, TAllocator>(data) { }

  QueryableSetData(
    TVectorIterator first,
    TVectorIterator last,
    TCompare comparator = {})
    : SortedQueryableData<T, std::set, TCompare, TAllocator>(first, last, comparator) { }

  virtual ~QueryableSetData() { }

  void Add(T item) override
  {
    this->items.insert(item);

    // because its a set, the tiem may not have actually been added. Insert
    // returns true/false whether the item was added, but the size method is
    // also a constant time action, so its cleaner to use it
    this->size = this->items.size();
  }
};

#endif
