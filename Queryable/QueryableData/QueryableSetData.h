#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLESETDATA_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLESETDATA_H

#include <iostream>
#include <memory>
#include <set>

#include "QueryableData.h"

#include "../Iterators/Iterator.h"

template<typename T>
class QueryableSetData : public QueryableData<T, std::set>
{
public:
  QueryableSetData() : QueryableData<T, std::set>() { }
  QueryableSetData(std::set<T> items)
    : QueryableData<T, std::set>(items)
  {
    this->InitForwardBegin();
    this->InitForwardEnd();
    this->InitReverseBegin();
    this->InitReverseEnd();
  }
  QueryableSetData(const QueryableSetData& data)
    : QueryableData<T, std::deque>(data)
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
};

#endif
