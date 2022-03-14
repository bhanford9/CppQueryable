#ifndef CPPQUERYABLE_QUERYABLE_SORTEDQUERYABLE_H
#define CPPQUERYABLE_QUERYABLE_SORTEDQUERYABLE_H

#include <iostream>
#include <set>
#include "QueryableForwardDeclare.hpp"
#include "../Queryable.hpp"
#include "../QueryableType.hpp"
#include "../QueryableData/QueryableSetData.hpp"

template<
  typename TObj,
  template<typename, typename ...> typename TIterable,
  typename TLessThan,
  typename TAllocator>
class SortedInternalQueryable : public InternalQueryable<TObj, TIterable, TLessThan, TAllocator>
{
public:
  SortedInternalQueryable(TLessThan lessThan = {}, TAllocator allocator = {}) :
    InternalQueryable<TObj, TIterable, TLessThan, TAllocator>(QueryableType::Set)
  {
  }

  SortedInternalQueryable(const InternalQueryable<TObj, std::set, TLessThan, TAllocator> & other)
    : InternalQueryable<TObj, std::set, TLessThan, TAllocator>(other)
  {
    this->type = QueryableType::Set;
  }
  SortedInternalQueryable(
    std::shared_ptr<QueryableData<TObj, std::set, TLessThan, TAllocator>> && queryableData,
    QueryableType type)
      : InternalQueryable<TObj, std::set, TLessThan, TAllocator>(std::move(queryableData), type)
  {
  }

  virtual InternalQueryable<TObj, TIterable, TLessThan, TAllocator> & Sort(std::function<bool(TObj, TObj)> lessThan = [](TObj a, TObj b) { return a < b; }) override
  {
    throw std::runtime_error("Sorted Containers cannot be sorted normally. Use ReOrderby or ReSort instead.");
  }
};

#endif
