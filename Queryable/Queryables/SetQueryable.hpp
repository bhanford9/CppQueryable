#ifndef CPPQUERYABLE_QUERYABLE_SETQUERYABLE_H
#define CPPQUERYABLE_QUERYABLE_SETQUERYABLE_H

#include <iostream>
#include <set>
#include "QueryableForwardDeclare.hpp"
#include "SortedQueryable.hpp"
#include "../Queryable.hpp"
#include "../QueryableType.hpp"
#include "../QueryableData/QueryableSetData.hpp"

template<
  typename TObj,
  typename TLessThan,
  typename TAllocator,
  typename TObjOut>
class SetQueryable : public SortedQueryable<TObj, std::set, TLessThan, TAllocator, TObjOut>
{
public:
  SetQueryable(TLessThan lessThan = {}, TAllocator allocator = {}) :
    SortedQueryable<TObj, std::set, TObjOut, TLessThan, TAllocator>(QueryableType::Set)
  {
    std::set<TObj, TLessThan, TAllocator> localSet(lessThan, allocator);
    this->items = std::make_shared<QueryableSetData<TObj, TLessThan, TAllocator>>(localSet);
  }

  SetQueryable(const std::set<TObj, TLessThan, TAllocator> & set)
  {
    this->type = QueryableType::Set;
    this->items = std::move(std::make_shared<QueryableSetData<TObj, TLessThan, TAllocator>>(set));
  }

  // SetQueryable(const std::set<TObj, TLessThan, TAllocator> & set, TLessThan lessThan = {}, TAllocator allocator = {})
  // {
  //   this->type = QueryableType::Set;
  //   std::set<TObj, TLessThan, TAllocator> localSet(set.begin(), set.end(), lessThan, allocator);
  //   this->items = std::move(std::make_shared<QueryableSetData<TObj, TLessThan, TAllocator>>(localSet));
  // }

  SetQueryable(const SetQueryable<TObj, TLessThan, TAllocator, TObjOut> & other)
  {
    this->type = QueryableType::Set;
    this->items = other.items;
  }

  virtual Queryable<TObj, std::set, TObjOut, TLessThan, TAllocator> & Where(std::function<bool(const TObj &)> condition) override
  {
    this->items = std::move(std::make_shared<WhereQueryableSetData<TObj, TLessThan, TAllocator>>(std::move(this->items), std::move(condition)));
    return *this;
  }
};

#endif
