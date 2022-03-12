#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLEVECTORDATA_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLEVECTORDATA_H

#include <iostream>
#include <vector>

#include "RandomAccessQueryableData.hpp"

template<
  typename T,
  typename TAllocator = std::allocator<T>>
class QueryableVectorData : public RandomAccessQueryableData<T, std::vector, TAllocator>
{
public:
  QueryableVectorData() : RandomAccessQueryableData<T, std::vector, TAllocator>() { }

  QueryableVectorData(std::vector<T, TAllocator> items)
    : RandomAccessQueryableData<T, std::vector, TAllocator>(items) { }

  QueryableVectorData(const QueryableVectorData & data)
    : RandomAccessQueryableData<T, std::vector, TAllocator>(data) { }

  QueryableVectorData(QueryableVectorData && data)
    : RandomAccessQueryableData<T, std::vector, TAllocator>(data) { }

  virtual ~QueryableVectorData() { }
};

#endif
