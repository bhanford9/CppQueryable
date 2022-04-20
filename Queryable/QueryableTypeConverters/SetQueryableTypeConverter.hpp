#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLETYPECONVERTERS_SETQUERYABLETYPECONVERTER_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLETYPECONVERTERS_SETQUERYABLETYPECONVERTER_H

#include "QueryableTypeConverter.hpp"
#include "../InternalQueryable.hpp"
#include "../InternalQueryables/SetInternalQueryable.hpp"

template<
  typename TSourceObj,
  typename TDestObj,
  typename TDestLessThan = std::less<TDestObj>,
  typename TDestAllocator = std::allocator<TDestObj>>
class SetQueryableTypeConverter :
  public QueryableTypeConverter<TSourceObj, TDestObj, std::set, TDestLessThan, TDestAllocator>
{
public:
  virtual std::shared_ptr<InternalQueryable<TDestObj, std::set, TDestLessThan, TDestAllocator>> Convert(
    QueryableIterator<TSourceObj> first,
    QueryableIterator<TSourceObj> last,
    TDestLessThan lessThan = {},
    TDestAllocator allocator = {}) const override
  {
    SetInternalQueryable<TDestObj, TDestLessThan, TDestAllocator> setQueryable(first, last, lessThan, allocator);
    return std::make_shared<SetInternalQueryable<TDestObj, TDestLessThan, TDestAllocator>>(setQueryable);
  }
};

#endif
