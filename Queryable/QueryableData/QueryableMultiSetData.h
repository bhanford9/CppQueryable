#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLEMULTISETDATA_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLEMULTISETDATA_H

#include <iostream>
#include <memory>
#include <set>

#include "QueryableData.h"
#include "../Iterators/Iterator.h"

template<typename T>
class QueryableMultiSetData : public QueryableData<T, std::multiset>
{
public:
  QueryableMultiSetData() : QueryableData<T, std::multiset>() { }
  QueryableMultiSetData(std::multiset<T> items)
    : QueryableData<T, std::multiset>(items)
  {
    this->InitForwardBegin();
    this->InitForwardEnd();
    this->InitReverseBegin();
    this->InitReverseEnd();
  }
  QueryableMultiSetData(const QueryableMultiSetData& data)
    : QueryableData<T, std::deque>(data)
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
};

#endif
