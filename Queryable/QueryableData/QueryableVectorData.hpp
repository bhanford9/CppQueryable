#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLEVECTORDATA_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLEVECTORDATA_H

#include <vector>

#include "RandomAccessQueryableData.hpp"

template<
  typename T,
  typename TAllocator = std::allocator<T>>
class QueryableVectorData : public RandomAccessQueryableData<T, std::vector, TAllocator>
{
public:
  QueryableVectorData() : RandomAccessQueryableData<T, std::vector, TAllocator>() { }

  // QueryableVectorData(std::vector<T, TAllocator> items)
  //   : RandomAccessQueryableData<T, std::vector, TAllocator>(items) { }

  QueryableVectorData(const std::vector<T, TAllocator> & items)
    : RandomAccessQueryableData<T, std::vector, TAllocator>(items) { }

  QueryableVectorData(std::vector<T, TAllocator> && items)
    : RandomAccessQueryableData<T, std::vector, TAllocator>(std::move(items)) { }

  QueryableVectorData(const QueryableVectorData & data)
    : RandomAccessQueryableData<T, std::vector, TAllocator>(data) { }

  QueryableVectorData(QueryableVectorData && data)
    : RandomAccessQueryableData<T, std::vector, TAllocator>(data) { }

  virtual ~QueryableVectorData() { }

  virtual std::shared_ptr<IQueryableData<T>> Clone() override
  {
    return std::make_shared<QueryableVectorData<T, TAllocator>>(*this);
  }
};

#endif
