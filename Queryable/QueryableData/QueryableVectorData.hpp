#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLEVECTORDATA_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLEVECTORDATA_H

#include <iostream>
#include <vector>

#include "RandomAccessQueryableData.hpp"

template<
  typename T,
  typename TAllocator = std::allocator<T>,
  typename TOut = T>
class QueryableVectorData : public RandomAccessQueryableData<T, std::vector, TAllocator, TOut>
{
public:
  QueryableVectorData() : RandomAccessQueryableData<T, std::vector, TAllocator, TOut>() { }

  QueryableVectorData(std::vector<T, TAllocator> items)
    : RandomAccessQueryableData<T, std::vector, TAllocator, TOut>(items) { }

  QueryableVectorData(const QueryableVectorData & data)
    : RandomAccessQueryableData<T, std::vector, TAllocator, TOut>(data) { }

  QueryableVectorData(QueryableVectorData && data)
    : RandomAccessQueryableData<T, std::vector, TAllocator, TOut>(data) { }

  virtual ~QueryableVectorData() { }
};

#endif
