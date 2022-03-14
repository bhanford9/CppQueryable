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
class SortedQueryable : public Queryable<TObj, TIterable, TLessThan, TAllocator>
{
public:
  SortedQueryable(TLessThan lessThan = {}, TAllocator allocator = {}) :
    Queryable<TObj, TIterable, TLessThan, TAllocator>(QueryableType::Set)
  {
  }

  SortedQueryable(const Queryable<TObj, std::set, TLessThan, TAllocator> & other)
    : Queryable<TObj, std::set, TLessThan, TAllocator>(other)
  {
    this->type = QueryableType::Set;
  }
  SortedQueryable(
    std::shared_ptr<QueryableData<TObj, std::set, TLessThan, TAllocator>> && queryableData,
    QueryableType type)
      : Queryable<TObj, std::set, TLessThan, TAllocator>(std::move(queryableData), type)
  {
  }

  virtual Queryable<TObj, TIterable, TLessThan, TAllocator> & Sort(std::function<bool(TObj, TObj)> lessThan = [](TObj a, TObj b) { return a < b; }) override
  {
    throw std::runtime_error("Sorted Containers cannot be sorted normally. Use ReOrderby or ReSort instead.");
  }
};

#endif
