#ifndef CPPQUERYABLE_QUERYABLE_INTERNALQUERYABLES_SORTEDINTERNALQUERYABLE_H
#define CPPQUERYABLE_QUERYABLE_INTERNALQUERYABLES_SORTEDINTERNALQUERYABLE_H

#include <iostream>
#include <set>
#include "QueryableForwardDeclare.hpp"
#include "../InternalQueryable.hpp"
#include "../QueryableType.hpp"
#include "../QueryableData/QueryableSetData.hpp"

template<
  typename TObj,
  template<typename, typename ...> typename TIterable,
  typename TLessThan,
  typename TAllocator>
class SortedInternalQueryable : public InternalQueryable<TObj, TIterable, TObj, TLessThan, TAllocator>
{
protected:
  SortedInternalQueryable() { }

public:
  SortedInternalQueryable(QueryableType type, TLessThan lessThan = {}, TAllocator allocator = {}) :
    InternalQueryable<TObj, TIterable, TObj, TLessThan, TAllocator>(type)
  {
  }

  SortedInternalQueryable(
    const InternalQueryable<TObj, TIterable, TObj, TLessThan, TAllocator> & other,
    QueryableType type)
    : InternalQueryable<TObj, TIterable, TObj, TLessThan, TAllocator>(other)
  {
    this->type = type;
  }
  SortedInternalQueryable(
    std::shared_ptr<QueryableData<TObj, TIterable, TObj, TLessThan, TAllocator>> && queryableData,
    QueryableType type)
      : InternalQueryable<TObj, TIterable, TObj, TLessThan, TAllocator>(std::move(queryableData), type)
  {
  }
  SortedInternalQueryable(
    std::shared_ptr<QueryableSetData<TObj, TLessThan, TAllocator>> && queryableData,
    QueryableType type)
      : InternalQueryable<TObj, TIterable, TObj, TLessThan, TAllocator>(std::move(queryableData), type)
  {
    std::cout << "Sorted Move Constructor" << std::endl;
  }
};

#endif
