#ifndef CPPQUERYABLE_QUERYABLE_INTERNALQUERYABLES_LISTINTERNALQUERYABLE_H
#define CPPQUERYABLE_QUERYABLE_INTERNALQUERYABLES_LISTINTERNALQUERYABLE_H

#include <iostream>
#include <list>
#include "QueryableForwardDeclare.hpp"
#include "../InternalQueryable.hpp"
#include "../QueryableType.hpp"
#include "../QueryableData/QueryableListData.hpp"

template<
  typename TObj,
  typename TAllocator>
class ListInternalQueryable : public InternalQueryable<TObj, std::list, TAllocator>
{
public:
  ListInternalQueryable(TAllocator allocator = {}) :
    InternalQueryable<TObj, std::list, TAllocator>(QueryableType::List)
  {
    std::list<TObj> localList(allocator);
    this->items = std::make_shared<QueryableListData<TObj, TAllocator>>(localList);
  }

  ListInternalQueryable(const std::list<TObj, TAllocator> & list)
  {
    this->type = QueryableType::List;
    this->items = std::move(std::make_shared<QueryableListData<TObj, TAllocator>>(list));
  }

  ListInternalQueryable(const ListInternalQueryable<TObj, TAllocator> & other)
  {
    this->type = QueryableType::List;
    this->items = other.items;
  }

  ListInternalQueryable(const InternalQueryable<TObj, std::list, TAllocator> & other)
    : InternalQueryable<TObj, std::list, TAllocator>(other)
  {
    this->type = QueryableType::Deque;
  }
  ListInternalQueryable(
    std::shared_ptr<QueryableData<TObj, std::list, TAllocator>> && queryableData,
    QueryableType type)
      : InternalQueryable<TObj, std::list, TAllocator>(std::move(queryableData), type)
  {
  }

  virtual InternalQueryable<TObj, std::list, TAllocator> & Where(std::function<bool(const TObj &)> condition) override
  {
    this->items = std::move(std::make_shared<WhereQueryableListData<TObj, TAllocator>>(std::move(this->items), std::move(condition)));
    return *this;
  }

  virtual InternalQueryable<TObj, std::list, TAllocator> & Sort(std::function<bool(TObj, TObj)> lessThan = [](TObj a, TObj b) { return a < b; }) override
  {
    // don't think anything special needs done other than just calling sort
    ListSorter<TObj, TAllocator> sorter;
    this->items->Sort(sorter, lessThan);
    return *this;
  }
};

#endif
