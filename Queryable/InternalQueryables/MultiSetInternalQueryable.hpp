#ifndef CPPQUERYABLE_QUERYABLE_INTERNALQUERYABLES_MULTISETINTERNALQUERYABLE_H
#define CPPQUERYABLE_QUERYABLE_INTERNALQUERYABLES_MULTISETINTERNALQUERYABLE_H

#include <iostream>
#include <set>
#include "QueryableForwardDeclare.hpp"
#include "SortedInternalQueryable.hpp"
#include "../InternalQueryable.hpp"
#include "../QueryableType.hpp"
#include "../QueryableData/QueryableMultiSetData.hpp"

template<
  typename TObj,
  typename TLessThan,
  typename TAllocator>
class MultiSetInternalQueryable : public SortedInternalQueryable<TObj, std::multiset, TLessThan, TAllocator>
{
public:
  MultiSetInternalQueryable(TLessThan lessThan = {}, TAllocator allocator = {}) :
    SortedInternalQueryable<TObj, std::multiset, TLessThan, TAllocator>(QueryableType::MultiSet)
  {
    std::multiset<TObj, TLessThan, TAllocator> localMultiSet(lessThan, allocator);
    this->items = std::make_shared<QueryableMultiSetData<TObj, TLessThan, TAllocator>>(localMultiSet);
  }

  MultiSetInternalQueryable(const std::multiset<TObj, TLessThan, TAllocator> & multiset)
  {
    this->type = QueryableType::MultiSet;
    this->items = std::move(std::make_shared<QueryableMultiSetData<TObj, TLessThan, TAllocator>>(multiset));
  }

  MultiSetInternalQueryable(const MultiSetInternalQueryable<TObj, TLessThan, TAllocator> & other)
  {
    this->type = QueryableType::MultiSet;
    this->items = other.items;
  }

  MultiSetInternalQueryable(const InternalQueryable<TObj, std::multiset, TLessThan, TAllocator> & other)
    : SortedInternalQueryable<TObj, std::multiset, TLessThan, TAllocator>(other, QueryableType::MultiSet)
  {
  }
  MultiSetInternalQueryable(
    std::shared_ptr<QueryableData<TObj, std::multiset, TLessThan, TAllocator>> && queryableData,
    QueryableType type)
      : SortedInternalQueryable<TObj, std::multiset, TLessThan, TAllocator>(std::move(queryableData), type)
  {
  }

  virtual InternalQueryable<TObj, std::multiset, TLessThan, TAllocator> & Where(std::function<bool(const TObj &)> condition) override
  {
    this->items = std::move(std::make_shared<WhereQueryableMultiSetData<TObj, TLessThan, TAllocator>>(std::move(this->items), std::move(condition)));
    return *this;
  }
};

#endif
