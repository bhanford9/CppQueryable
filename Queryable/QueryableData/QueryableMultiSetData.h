#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLEMULTISETDATA_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLEMULTISETDATA_H

#include <iostream>
#include <memory>
#include <set>

#include "SortedQueryableData.h"

template<typename T>
class QueryableMultiSetData : public SortedQueryableData<T, std::multiset>
{
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

  virtual ~QueryableMultiSetData() { }

  void Add(T item) override
  {
    this->items.insert(item);
    this->size++;
  }

  // virtual void Update(Iterator<T> first, Iterator<T> last, std::function<bool(T, T)> compare) override
  // {
  //   this->items = std::multiset<T, std::function<bool(T, T)>>(this->items.begin(), this->items.end(), compare);
  // }
  //
  // virtual void Update(TVectorIterator first, TVectorIterator last)
  // {
  //   // TODO SFINAE require this constructor
  //   this->items = std::multiset<T, std::function<bool(T, T)>>(first, last, this->comparator);
  //   this->size = this->items.size();
  // }
};

#endif
