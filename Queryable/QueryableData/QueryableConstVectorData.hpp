#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLECONSTVECTORDATA_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLECONSTVECTORDATA_H

#include <iostream>
#include <vector>

#include "../Sorters/VectorSorter.hpp"
#include "ConstRandomAccessQueryableData.hpp"

template<
  typename T,
  typename TAllocator = std::allocator<T>>
class QueryableConstVectorData : public ConstRandomAccessQueryableData<T, std::vector, TAllocator>
{
public:
  QueryableConstVectorData() : ConstRandomAccessQueryableData<T, std::vector, TAllocator>() { }

  // QueryableConstVectorData(std::vector<T, TAllocator> items)
  //   : ConstRandomAccessQueryableData<T, std::vector, TAllocator>(items) { }

  QueryableConstVectorData(const std::vector<T, TAllocator> & items)
    : ConstRandomAccessQueryableData<T, std::vector, TAllocator>(items) { }

  QueryableConstVectorData(std::vector<T, TAllocator> && items)
    : ConstRandomAccessQueryableData<T, std::vector, TAllocator>(std::move(items)) { }

  QueryableConstVectorData(const QueryableConstVectorData & data)
    : ConstRandomAccessQueryableData<T, std::vector, TAllocator>(data) { }

  QueryableConstVectorData(QueryableConstVectorData && data)
    : ConstRandomAccessQueryableData<T, std::vector, TAllocator>(data) { }

  virtual ~QueryableConstVectorData() { }

  virtual std::shared_ptr<IQueryableData<T>> Clone() override
  {
    return std::make_shared<QueryableConstVectorData<T, TAllocator>>(*this);
  }
};

#endif
