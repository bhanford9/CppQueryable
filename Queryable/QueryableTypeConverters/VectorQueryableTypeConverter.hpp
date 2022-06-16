#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLETYPECONVERTERS_VECTORQUERYABLETYPECONVERTER_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLETYPECONVERTERS_VECTORQUERYABLETYPECONVERTER_H

#include "QueryableTypeConverter.hpp"
#include "../InternalQueryable.hpp"
#include "../InternalQueryables/VectorInternalQueryable.hpp"

template<
  typename TSourceObj,
  typename TDestObj,
  typename TDestAllocator = std::allocator<TDestObj>>
class VectorQueryableTypeConverter :
  public QueryableTypeConverter<TSourceObj, TDestObj, std::vector, TDesTAllocator>
{
public:
  virtual std::shared_ptr<InternalQueryable<TDestObj, std::vector, TDesTAllocator>> Convert(
    QueryableIterator<TSourceObj> first,
    QueryableIterator<TSourceObj> last,
    TDestAllocator allocator = {}) const override
  {
    VectorInternalQueryable<TDestObj, TDesTAllocator> vectorQueryable(first, last, allocator);
    return std::make_shared<VectorInternalQueryable<TDestObj, TDesTAllocator>>(vectorQueryable);
  }
};

#endif
