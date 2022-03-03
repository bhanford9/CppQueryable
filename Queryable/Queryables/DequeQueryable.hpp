#ifndef CPPQUERYABLE_QUERYABLE_DEQUEQUERYABLE_H
#define CPPQUERYABLE_QUERYABLE_DEQUEQUERYABLE_H

#include <iostream>
#include <deque>
#include "QueryableForwardDeclare.hpp"
#include "../Queryable.hpp"
#include "../QueryableType.hpp"
#include "../QueryableData/QueryableDequeData.hpp"

template<
  typename TObj,
  typename TAllocator>
class DequeQueryable : public Queryable<TObj, std::deque, TAllocator>
{
public:
  DequeQueryable(TAllocator allocator = {}) :
    Queryable<TObj, std::deque, TAllocator>(QueryableType::Deque)
  {
    std::deque<TObj> localDeque(allocator);
    this->items = std::make_shared<QueryableDequeData<TObj, TAllocator>>(localDeque);
  }

  DequeQueryable(const std::deque<TObj, TAllocator> & deque)
  {
    this->type = QueryableType::Deque;
    this->items = std::move(std::make_shared<QueryableDequeData<TObj, TAllocator>>(deque));
  }

  DequeQueryable(const DequeQueryable<TObj, TAllocator> & other)
  {
    this->type = QueryableType::Deque;
    this->items = other.items;
  }
};

#endif
