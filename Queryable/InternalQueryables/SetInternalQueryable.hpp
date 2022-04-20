#ifndef CPPQUERYABLE_QUERYABLE_INTERNALQUERYABLES_SETINTERNALQUERYABLE_H
#define CPPQUERYABLE_QUERYABLE_INTERNALQUERYABLES_SETINTERNALQUERYABLE_H

#include <iostream>
#include <set>
#include "QueryableForwardDeclare.hpp"
#include "SortedInternalQueryable.hpp"
#include "../InternalQueryable.hpp"
#include "../QueryableType.hpp"
#include "../QueryableData/QueryableSetData.hpp"

template<
  typename TObj,
  typename TLessThan,
  typename TAllocator>
class SetInternalQueryable : public SortedInternalQueryable<TObj, std::set, TLessThan, TAllocator>
{
public:
  SetInternalQueryable(TLessThan lessThan = {}, TAllocator allocator = {}) :
    SortedInternalQueryable<TObj, std::set, TLessThan, TAllocator>(QueryableType::Set, lessThan, allocator)
  {
    std::set<TObj, TLessThan, TAllocator> localSet(lessThan, allocator);
    this->items = std::make_shared<QueryableSetData<TObj, TLessThan, TAllocator>>(localSet);
  }

  SetInternalQueryable(const std::set<TObj, TLessThan, TAllocator> & set)
  {
    this->type = QueryableType::Set;
    this->items = std::move(std::make_shared<QueryableSetData<TObj, TLessThan, TAllocator>>(set));
  }

  // SetInternalQueryable(const std::set<TObj, TLessThan, TAllocator> & set, TLessThan lessThan = {}, TAllocator allocator = {})
  // {
  //   this->type = QueryableType::Set;
  //   std::set<TObj, TLessThan, TAllocator> localSet(set.begin(), set.end(), lessThan, allocator);
  //   this->items = std::move(std::make_shared<QueryableSetData<TObj, TLessThan, TAllocator>>(localSet));
  // }

  SetInternalQueryable(const SetInternalQueryable<TObj, TLessThan, TAllocator> & other)
  {
    this->type = QueryableType::Set;
    this->items = other.items;
  }

  SetInternalQueryable(const InternalQueryable<TObj, std::set, TLessThan, TAllocator> & other)
    : SortedInternalQueryable<TObj, std::set, TLessThan, TAllocator>(other, QueryableType::Set)
  {
  }
  SetInternalQueryable(
    std::shared_ptr<QueryableData<TObj, std::set, TLessThan, TAllocator>> && queryableData,
    QueryableType type)
      : SortedInternalQueryable<TObj, std::set, TLessThan, TAllocator>(std::move(queryableData), type)
  {
  }

  SetInternalQueryable(
    const QueryableIterator<TObj> & first,
    const QueryableIterator<TObj> & last,
    TLessThan lessThan = {},
    TAllocator allocator = {})
  {
    this->items = std::make_shared<QueryableSetData<TObj, TLessThan, TAllocator>>(
      std::set<TObj, TLessThan, TAllocator>(first, last, lessThan, allocator));
    this->type = QueryableType::Set;
  }

  virtual InternalQueryable<TObj, std::set, TLessThan, TAllocator> & Where(std::function<bool(const TObj &)> condition) override
  {
    this->items = std::move(std::make_shared<WhereQueryableSetData<TObj, TLessThan, TAllocator>>(std::move(this->items), std::move(condition)));
    return *this;
  }
};

#endif
