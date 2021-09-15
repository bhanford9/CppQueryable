#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLEMULTISETDATA_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLEMULTISETDATA_H

#include <iostream>
#include <memory>
#include <set>

#include "SortedQueryableData.h"

template<typename T>
class QueryableMultiSetData : public SortedQueryableData<T, std::multiset>
{
  typedef typename std::vector<T>::iterator TVectorIterator;
public:
  QueryableMultiSetData(std::function<bool(T, T)> compare = [](T a, T b) { return a < b; })
    : SortedQueryableData<T, std::multiset>()
  {
  }
  QueryableMultiSetData(std::multiset<T, std::function<bool(T, T)>> items)
    : SortedQueryableData<T, std::multiset>(items)
  {
  }
  QueryableMultiSetData(const QueryableMultiSetData& data)
    : SortedQueryableData<T, std::multiset>(data)
  {
  }
  QueryableMultiSetData(
    TVectorIterator first,
    TVectorIterator last,
    std::function<bool(T, T)> compare = [](T a, T b) { return a < b; })
    : SortedQueryableData<T, std::multiset>(first, last, compare)
  {
  }

  virtual ~QueryableMultiSetData() { }

  void Add(T item) override
  {
    this->items.insert(item);
    this->size++;
  }
};

#endif
