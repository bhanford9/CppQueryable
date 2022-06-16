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
  public QueryableTypeConverter<TSourceObj, TDestObj, std::set, TDesTLessThan, TDesTAllocator>
{
public:
  virtual std::shared_ptr<InternalQueryable<TDestObj, std::set, TDesTLessThan, TDesTAllocator>> Convert(
    QueryableIterator<TSourceObj> first,
    QueryableIterator<TSourceObj> last,
    const TDestLessThan & lessThan = {},
    const TDestAllocator & allocator = {}) const override
  {
    SetInternalQueryable<TDestObj, TDesTLessThan, TDesTAllocator> setQueryable(first, last, lessThan, allocator);
    return std::make_shared<SetInternalQueryable<TDestObj, TDesTLessThan, TDesTAllocator>>(setQueryable);
  }
};

#endif
