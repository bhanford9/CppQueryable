#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLELISTDATA_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLELISTDATA_H

#include <iostream>
#include <list>

#include "QueryableData.h"
// #include "../Iterators/Iterator.h"

template<typename T>
class QueryableListData : public QueryableData<T, std::list>
{
public:
  QueryableListData() : QueryableData<T, std::list>() { }
  QueryableListData(std::list<T> items)
    : QueryableData<T, std::list>(items)
  {
  }
  QueryableListData(const QueryableListData& data)
    : QueryableData<T, std::list>(data)
  {
  }

  virtual ~QueryableListData() { }

  void Add(T item) override
  {
    this->items.push_back(item);
  }

  int Count() override
  {
    return this->items.size();
  }

  void RemoveLast() override
  {
    this->items.pop_back();
  }

  void RemoveFirst() override
  {

  }
};

#endif
