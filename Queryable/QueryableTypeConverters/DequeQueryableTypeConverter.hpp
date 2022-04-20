#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLETYPECONVERTERS_DEQUEQUERYABLETYPECONVERTER_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLETYPECONVERTERS_DEQUEQUERYABLETYPECONVERTER_H

#include "QueryableTypeConverter.hpp"
#include "../InternalQueryable.hpp"
#include "../InternalQueryables/DequeInternalQueryable.hpp"

template<
  typename TSourceObj,
  typename TDestObj,
  typename TDestAllocator = std::allocator<TDestObj>>
class DequeQueryableTypeConverter :
  public QueryableTypeConverter<TSourceObj, TDestObj, std::deque, TDestAllocator>
{
public:
  virtual std::shared_ptr<InternalQueryable<TDestObj, std::deque, TDestAllocator>> Convert(
    QueryableIterator<TSourceObj> first,
    QueryableIterator<TSourceObj> last,
    TDestAllocator allocator = {}) const override
  {
    DequeInternalQueryable<TDestObj, TDestAllocator> dequeQueryable(first, last, allocator);
    return std::make_shared<DequeInternalQueryable<TDestObj, TDestAllocator>>(dequeQueryable);
  }
};

#endif
