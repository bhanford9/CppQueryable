#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLETYPECONVERTERS_MULTISETQUERYABLETYPECONVERTER_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLETYPECONVERTERS_MULTISETQUERYABLETYPECONVERTER_H

#include "QueryableTypeConverter.hpp"
#include "../InternalQueryable.hpp"
#include "../InternalQueryables/MultiSetInternalQueryable.hpp"

template<
  typename TSourceObj,
  typename TDestObj,
  typename TDestLessThan = std::less<TDestObj>,
  typename TDestAllocator = std::allocator<TDestObj>>
class MultiSetQueryableTypeConverter :
  public QueryableTypeConverter<TSourceObj, TDestObj, std::multiset, TDestLessThan, TDestAllocator>
{
public:
  virtual std::shared_ptr<InternalQueryable<TDestObj, std::multiset, TDestLessThan, TDestAllocator>> Convert(
    QueryableIterator<TSourceObj> first,
    QueryableIterator<TSourceObj> last,
    TDestLessThan lessThan = {},
    TDestAllocator allocator = {}) const override
  {
    MultiSetInternalQueryable<TDestObj, TDestLessThan, TDestAllocator> multisetQueryable(first, last, lessThan, allocator);
    return std::make_shared<MultiSetInternalQueryable<TDestObj, TDestLessThan, TDestAllocator>>(multisetQueryable);
  }
};

#endif
