#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLEDEQUEDATA_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLEDEQUEDATA_H

#include <algorithm>
#include <deque>
#include <iostream>
#include <memory>

#include "RandomAccessQueryableData.h"

template<typename T, typename TAllocator = std::allocator<T>>
class QueryableDequeData : public RandomAccessQueryableData<T, std::deque, TAllocator>
{
public:
  QueryableDequeData() : RandomAccessQueryableData<T, std::deque, TAllocator>() { }
  QueryableDequeData(std::deque<T, TAllocator> items)
    : RandomAccessQueryableData<T, std::deque, TAllocator>(items) { }
  QueryableDequeData(const QueryableDequeData& data)
    : RandomAccessQueryableData<T, std::deque, TAllocator>(data) { }
  QueryableDequeData(QueryableDequeData && data)
    : RandomAccessQueryableData<T, std::deque, TAllocator>(data) { }

  virtual ~QueryableDequeData() { }
};

#endif
