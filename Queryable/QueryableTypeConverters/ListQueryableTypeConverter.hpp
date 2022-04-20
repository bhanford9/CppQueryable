#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLETYPECONVERTERS_LISTQUERYABLETYPECONVERTER_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLETYPECONVERTERS_LISTQUERYABLETYPECONVERTER_H

#include "QueryableTypeConverter.hpp"
#include "../InternalQueryable.hpp"
#include "../InternalQueryables/ListInternalQueryable.hpp"

template<
  typename TSourceObj,
  typename TDestObj,
  typename TDestAllocator = std::allocator<TDestObj>>
class ListQueryableTypeConverter :
  public QueryableTypeConverter<TSourceObj, TDestObj, std::list, TDestAllocator>
{
public:
  virtual std::shared_ptr<InternalQueryable<TDestObj, std::list, TDestAllocator>> Convert(
    QueryableIterator<TSourceObj> first,
    QueryableIterator<TSourceObj> last,
    TDestAllocator allocator = {}) const override
  {
    ListInternalQueryable<TDestObj, TDestAllocator> listQueryable(first, last, allocator);
    return std::make_shared<ListInternalQueryable<TDestObj, TDestAllocator>>(listQueryable);
  }
};

#endif
