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
  typename TAllocator,
  typename TObjOut>
class SortedQueryable : public Queryable<TObj, TIterable, TObjOut, TLessThan, TAllocator>
{
public:
  SortedQueryable(TLessThan lessThan = {}, TAllocator allocator = {}) :
    Queryable<TObj, TIterable, TObjOut, TLessThan, TAllocator>(QueryableType::Set)
  {
  }

  virtual Queryable<TObj, TIterable, TObjOut, TLessThan, TAllocator> & Sort(std::function<bool(TObj, TObj)> lessThan = [](TObj a, TObj b) { return a < b; }) override
  {
    throw std::runtime_error("Sorted Containers cannot be sorted normally. Use ReOrderby or ReSort instead.");
  }
};

#endif
