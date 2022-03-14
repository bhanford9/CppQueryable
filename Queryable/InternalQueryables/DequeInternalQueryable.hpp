#ifndef CPPQUERYABLE_QUERYABLE_INTERNALQUERYABLES_DEQUEINTERNALQUERYABLE_H
#define CPPQUERYABLE_QUERYABLE_INTERNALQUERYABLES_DEQUEINTERNALQUERYABLE_H

#include <iostream>
#include <deque>
#include "QueryableForwardDeclare.hpp"
#include "../InternalQueryable.hpp"
#include "../QueryableType.hpp"
#include "../QueryableData/QueryableDequeData.hpp"

template<
  typename TObj,
  typename TAllocator>
class DequeInternalQueryable : public InternalQueryable<TObj, std::deque, TAllocator>
{
public:
  DequeInternalQueryable(TAllocator allocator = {}) :
    InternalQueryable<TObj, std::deque, TAllocator>(QueryableType::Deque)
  {
    std::deque<TObj> localDeque(allocator);
    this->items = std::make_shared<QueryableDequeData<TObj, TAllocator>>(localDeque);
  }

  DequeInternalQueryable(const std::deque<TObj, TAllocator> & deque)
  {
    this->type = QueryableType::Deque;
    this->items = std::move(std::make_shared<QueryableDequeData<TObj, TAllocator>>(deque));
  }

  DequeInternalQueryable(const DequeInternalQueryable<TObj, TAllocator> & other)
  {
    this->type = QueryableType::Deque;
    this->items = other.items;
  }

  DequeInternalQueryable(const InternalQueryable<TObj, std::deque, TAllocator> & other)
    : InternalQueryable<TObj, std::deque, TAllocator>(other)
  {
    this->type = QueryableType::Deque;
  }
  DequeInternalQueryable(
    std::shared_ptr<QueryableData<TObj, std::deque, TAllocator>> && queryableData,
    QueryableType type)
      : InternalQueryable<TObj, std::deque, TAllocator>(std::move(queryableData), type)
  {
  }

  virtual InternalQueryable<TObj, std::deque, TAllocator> & Where(std::function<bool(const TObj &)> condition) override
  {
    this->items = std::move(std::make_shared<WhereQueryableDequeData<TObj, TAllocator>>(std::move(this->items), std::move(condition)));
    return *this;
  }

  virtual InternalQueryable<TObj, std::deque, TAllocator> & Sort(std::function<bool(TObj, TObj)> lessThan = [](TObj a, TObj b) { return a < b; }) override
  {
    // don't think anything special needs done other than just calling sort
    DequeSorter<TObj, TAllocator> sorter;
    this->items->Sort(sorter, lessThan);
    return *this;
  }
};

#endif
