#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLEDEQUEDATA_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLEDEQUEDATA_H

#include <algorithm>
#include <deque>
#include <iostream>
#include <memory>

#include "QueryableData.h"

template<typename T, typename TAllocator = std::allocator<T>>
class QueryableDequeData : public QueryableData<T, std::deque, TAllocator>
{
private:
  void InitRandomAccessProperties()
  {
    this->beginning.Add = [&](int addend, uint64_t & index) { this->beginIterator += addend; index += addend; };
    this->beginning.Subtract = [&](int subtrahend, uint64_t & index) { this->beginIterator -= subtrahend; index -= subtrahend; };

    this->ending.Add = [&](int addend, uint64_t & index) { this->endIterator += addend; index += addend; };
    this->ending.Subtract = [&](int subtrahend, uint64_t & index) { this->endIterator -= subtrahend; index -= subtrahend; };

    this->rbeginning.Add = [&](int addend, uint64_t & index) { this->rbeginIterator += addend; index += addend; };
    this->rbeginning.Subtract = [&](int subtrahend, uint64_t & index) { this->rbeginIterator -= subtrahend; index -= subtrahend; };

    this->rending.Add = [&](int addend, uint64_t & index) { this->rendIterator += addend; index += addend; };
    this->rending.Subtract = [&](int subtrahend, uint64_t & index) { this->rendIterator -= subtrahend; index -= subtrahend; };
  }

public:
  QueryableDequeData() : QueryableData<T, std::deque, TAllocator>() { }
  QueryableDequeData(std::deque<T, TAllocator> items)
    : QueryableData<T, std::deque, TAllocator>(items)
  {
  }
  QueryableDequeData(const QueryableDequeData& data)
    : QueryableData<T, std::deque, TAllocator>(data)
  {
  }

  virtual ~QueryableDequeData() { }

  void Add(T item) override
  {
    this->items.push_back(item);
    this->size++;
  }

  void Sort(std::function<bool(T, T)> compare = [](T a, T b) { return a < b; }) override
  {
    // todo figure out how to get this to work with this->begin instead o this->items.begin()
    std::sort(this->items.begin(), this->items.end(), compare);
  }
};

#endif
