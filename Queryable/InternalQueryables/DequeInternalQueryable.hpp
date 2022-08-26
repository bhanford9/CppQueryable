#ifndef CPPQUERYABLE_QUERYABLE_INTERNALQUERYABLES_DEQUEINTERNALQUERYABLE_H
#define CPPQUERYABLE_QUERYABLE_INTERNALQUERYABLES_DEQUEINTERNALQUERYABLE_H

#include <iostream>
#include <deque>
#include "QueryableForwardDeclare.hpp"
#include "../InternalQueryable.hpp"
#include "../QueryableType.hpp"
#include "../QueryableData/QueryableDequeData.hpp"
#include "../Utilities/IWhileCondition.hpp"

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

  DequeInternalQueryable(std::deque<TObj, TAllocator> && deque)
  {
    this->type = QueryableType::Deque;
    this->items = std::move(std::make_shared<QueryableDequeData<TObj, TAllocator>>(std::move(deque)));
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

  DequeInternalQueryable(const QueryableIterator<TObj> & first, const QueryableIterator<TObj> & last, TAllocator allocator = {})
  {
    this->items = std::make_shared<QueryableDequeData<TObj, TAllocator>>(std::deque<TObj, TAllocator>(first, last, allocator));
    this->type = QueryableType::Deque;
  }

  virtual void Where(std::function<bool(const TObj &)> condition) override
  {
    this->items = std::move(std::make_shared<WhereQueryableDequeData<TObj, TAllocator>>(std::move(this->items), std::move(condition)));
  }

  virtual void While(std::shared_ptr<IWhileCondition<TObj>> && condition) override
  {
    // this->items = std::make_shared<WhileQueryableDequeData<TObj, TAllocator>>(std::move(this->items), std::move(condition));
  }
};

#endif
