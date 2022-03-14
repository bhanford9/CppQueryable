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
  typename TAllocator>
class SetQueryable : public SortedQueryable<TObj, std::set, TLessThan, TAllocator>
{
public:
  SetQueryable(TLessThan lessThan = {}, TAllocator allocator = {}) :
    SortedQueryable<TObj, std::set, TLessThan, TAllocator>(QueryableType::Set)
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

  SetQueryable(const SetQueryable<TObj, TLessThan, TAllocator> & other)
  {
    this->type = QueryableType::Set;
    this->items = other.items;
  }

  SetQueryable(const Queryable<TObj, std::set, TLessThan, TAllocator> & other)
    : SortedQueryable<TObj, std::set, TLessThan, TAllocator>(other)
  {
    this->type = QueryableType::Set;
  }
  SetQueryable(
    std::shared_ptr<QueryableData<TObj, std::set, TLessThan, TAllocator>> && queryableData,
    QueryableType type)
      : SortedQueryable<TObj, std::set, TLessThan, TAllocator>(std::move(queryableData), type)
  {
  }

  virtual Queryable<TObj, std::set, TLessThan, TAllocator> & Where(std::function<bool(const TObj &)> condition) override
  {
    this->items = std::move(std::make_shared<WhereQueryableSetData<TObj, TLessThan, TAllocator>>(std::move(this->items), std::move(condition)));
    return *this;
  }
};

#endif
