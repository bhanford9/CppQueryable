#ifndef CPPQUERYABLE_QUERYABLE_SETQUERYABLE_H
#define CPPQUERYABLE_QUERYABLE_SETQUERYABLE_H

#include <iostream>
#include <set>
#include "QueryableForwardDeclare.hpp"
#include "../Queryable.hpp"
#include "../QueryableType.hpp"
#include "../QueryableData/QueryableSetData.hpp"

template<
  typename TObj,
  typename TLessThan,
  typename TAllocator>
class SetQueryable : public Queryable<TObj, std::set, TAllocator, TLessThan>
{
public:
  SetQueryable(TLessThan lessThan = {}, TAllocator allocator = {}) :
    Queryable<TObj, std::set, TAllocator, TLessThan>(QueryableType::Set)
  {
    std::set<TObj, TLessThan, TAllocator> localSet(lessThan, allocator);
    this->items = std::make_shared<QueryableSetData<TObj, TLessThan, TAllocator>>(localSet);
  }

  SetQueryable(const std::set<TObj, TLessThan, TAllocator> & set)
  {
    this->type = QueryableType::Set;
    this->items = std::move(std::make_shared<QueryableSetData<TObj, TLessThan, TAllocator>>(set));
  }

  SetQueryable(const SetQueryable<TObj, TAllocator, TLessThan> & other)
  {
    this->type = QueryableType::Set;
    this->items = other.items;
  }
};

#endif
