#ifndef CPPQUERYABLE_QUERYABLE_MULTISETQUERYABLE_H
#define CPPQUERYABLE_QUERYABLE_MULTISETQUERYABLE_H

#include <iostream>
#include <set>
#include "QueryableForwardDeclare.hpp"
#include "../Queryable.hpp"
#include "../QueryableType.hpp"
#include "../QueryableData/QueryableMultiSetData.hpp"

template<
  typename TObj,
  typename TLessThan,
  typename TAllocator>
class MultiSetQueryable : public Queryable<TObj, std::multiset, TAllocator, TLessThan>
{
public:
  MultiSetQueryable(TLessThan lessThan = {}, TAllocator allocator = {}) :
    Queryable<TObj, std::multiset, TAllocator, TLessThan>(QueryableType::MultiSet)
  {
    std::multiset<TObj, TLessThan, TAllocator> localMultiSet(lessThan, allocator);
    this->items = std::make_shared<QueryableMultiSetData<TObj, TLessThan, TAllocator>>(localMultiSet);
  }

  MultiSetQueryable(const std::multiset<TObj, TLessThan, TAllocator> & multiset)
  {
    this->type = QueryableType::MultiSet;
    this->items = std::move(std::make_shared<QueryableMultiSetData<TObj, TLessThan, TAllocator>>(multiset));
  }

  MultiSetQueryable(const MultiSetQueryable<TObj, TAllocator, TLessThan> & other)
  {
    this->type = QueryableType::MultiSet;
    this->items = other.items;
  }
};

#endif
