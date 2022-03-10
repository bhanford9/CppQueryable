#ifndef CPPQUERYABLE_QUERYABLE_MULTISETQUERYABLE_H
#define CPPQUERYABLE_QUERYABLE_MULTISETQUERYABLE_H

#include <iostream>
#include <set>
#include "QueryableForwardDeclare.hpp"
#include "SortedQueryable.hpp"
#include "../Queryable.hpp"
#include "../QueryableType.hpp"
#include "../QueryableData/QueryableMultiSetData.hpp"

template<
  typename TObj,
  typename TLessThan,
  typename TAllocator,
  typename TObjOut>
class MultiSetQueryable : public SortedQueryable<TObj, std::multiset, TObjOut, TLessThan, TAllocator>
{
public:
  MultiSetQueryable(TLessThan lessThan = {}, TAllocator allocator = {}) :
    SortedQueryable<TObj, std::multiset, TObjOut, TLessThan, TAllocator>(QueryableType::MultiSet)
  {
    std::multiset<TObj, TLessThan, TAllocator> localMultiSet(lessThan, allocator);
    this->items = std::make_shared<QueryableMultiSetData<TObj, TLessThan, TAllocator>>(localMultiSet);
  }

  MultiSetQueryable(const std::multiset<TObj, TLessThan, TAllocator> & multiset)
  {
    this->type = QueryableType::MultiSet;
    this->items = std::move(std::make_shared<QueryableMultiSetData<TObj, TLessThan, TAllocator>>(multiset));
  }

  MultiSetQueryable(const MultiSetQueryable<TObj, TLessThan, TAllocator, TObjOut> & other)
  {
    this->type = QueryableType::MultiSet;
    this->items = other.items;
  }

  virtual Queryable<TObj, std::multiset, TObjOut, TLessThan, TAllocator> & Where(std::function<bool(const TObj &)> condition) override
  {
    this->items = std::move(std::make_shared<WhereQueryableMultiSetData<TObj, TLessThan, TAllocator>>(std::move(this->items), std::move(condition)));
    return *this;
  }
};

#endif
