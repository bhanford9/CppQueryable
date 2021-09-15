#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLESETDATA_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLESETDATA_H

#include <iostream>
#include <memory>
#include <set>

#include "SortedQueryableData.h"

template<typename T>
class QueryableSetData : public SortedQueryableData<T, std::set>
{
  typedef typename std::vector<T>::iterator TVectorIterator;
public:
  QueryableSetData(std::function<bool(T, T)> compare = [](T a, T b) { return a < b; })
    : SortedQueryableData<T, std::set>()
  {
  }
  QueryableSetData(std::set<T, std::function<bool(T, T)>> items)
    : SortedQueryableData<T, std::set>(items)
  {
  }
  QueryableSetData(const QueryableSetData& data)
    : SortedQueryableData<T, std::set>(data)
  {
  }
  QueryableSetData(
    TVectorIterator first,
    TVectorIterator last,
    std::function<bool(T, T)> compare = [](T a, T b) { return a < b; })
    : SortedQueryableData<T, std::set>(first, last, compare)
  {
  }

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
