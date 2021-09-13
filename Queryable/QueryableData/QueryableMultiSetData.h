#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLEMULTISETDATA_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLEMULTISETDATA_H

#include <iostream>
#include <memory>
#include <set>

#include "QueryableData.h"

template<typename T>
class QueryableMultiSetData : public QueryableData<T, std::multiset, std::function<bool(T, T)>>
{
  typedef typename std::multiset<T, std::function<bool(T, T)>>::iterator t_forwardIterator;
public:
  QueryableMultiSetData(std::function<bool(T, T)> compare = [](T a, T b) { return a < b; })
    : QueryableData<T, std::multiset, std::function<bool(T, T)>>()
  {
    this->items = std::multiset<T, std::function<bool(T, T)>>(compare);
    this->InitForwardBegin();
    this->InitForwardEnd();
    this->InitReverseBegin();
    this->InitReverseEnd();
  }
  QueryableMultiSetData(std::multiset<T, std::function<bool(T, T)>> items)
    : QueryableData<T, std::multiset, std::function<bool(T, T)>>(items)
  {
  }
  QueryableMultiSetData(const QueryableMultiSetData& data)
    : QueryableData<T, std::multiset, std::function<bool(T, T)>>(data)
  {
  }

  virtual ~QueryableMultiSetData() { }

  void Add(T item) override
  {
    this->items.insert(item);
    this->size++;
  }

  void Sort(std::function<bool(T, T)> compare = [](T a, T b) { return a < b; }) override
  {
    // already sorted
  }

  virtual void Update(Iterator<T> first, Iterator<T> last, std::function<bool(T, T)> compare) override
  {
    this->items = std::multiset<T, std::function<bool(T, T)>>(this->items.begin(), this->items.end(), compare);
  }
};

#endif
