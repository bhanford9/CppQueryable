#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLESETDATA_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLESETDATA_H

#include <iostream>
#include <memory>
#include <set>

#include "QueryableData.h"

template<typename T>
class QueryableSetData : public QueryableData<T, std::set, std::function<bool(T, T)>>
{
public:
  QueryableSetData(std::function<bool(T, T)> compare = [](T a, T b) { return a < b; })
    : QueryableData<T, std::set, std::function<bool(T, T)>>()
  {
    this->items = std::set<T, std::function<bool(T, T)>>(compare);
    this->InitForwardBegin();
    this->InitForwardEnd();
    this->InitReverseBegin();
    this->InitReverseEnd();
  }
  QueryableSetData(std::set<T, std::function<bool(T, T)>> items)
    : QueryableData<T, std::set, std::function<bool(T, T)>>(items)
  {
  }
  QueryableSetData(const QueryableSetData& data)
    : QueryableData<T, std::set, std::function<bool(T, T)>>(data)
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

  void Sort(std::function<bool(T, T)> compare = [](T a, T b) { return a < b; }) override
  {
    // already sorted
  }

  virtual void Update(Iterator<T> first, Iterator<T> last, std::function<bool(T, T)> compare) override
  {
    this->items = std::set<T, std::function<bool(T, T)>>(this->items.begin(), this->items.end(), compare);
    this->size = this->items.size();
  }
};

#endif
