#ifndef CPPQUERYABLE_QUERYABLE_LISTQUERYABLE_H
#define CPPQUERYABLE_QUERYABLE_LISTQUERYABLE_H

#include <iostream>
#include <list>
#include "QueryableForwardDeclare.hpp"
#include "../Queryable.hpp"
#include "../QueryableType.hpp"
#include "../QueryableData/QueryableListData.hpp"

template<
  typename TObj,
  typename TAllocator,
  typename TObjOut>
class ListQueryable : public Queryable<TObj, std::list, TObjOut, TAllocator>
{
public:
  ListQueryable(TAllocator allocator = {}) :
    Queryable<TObj, std::list, TObjOut, TAllocator>(QueryableType::List)
  {
    std::list<TObj> localList(allocator);
    this->items = std::make_shared<QueryableListData<TObj, TAllocator>>(localList);
  }

  ListQueryable(const std::list<TObj, TAllocator> & list)
  {
    this->type = QueryableType::List;
    this->items = std::move(std::make_shared<QueryableListData<TObj, TAllocator>>(list));
  }

  ListQueryable(const ListQueryable<TObj, TAllocator, TObjOut> & other)
  {
    this->type = QueryableType::List;
    this->items = other.items;
  }

  virtual Queryable<TObj, std::list, TObjOut, TAllocator> & Where(std::function<bool(const TObj &)> condition) override
  {
    this->items = std::move(std::make_shared<WhereQueryableListData<TObj, TAllocator>>(std::move(this->items), std::move(condition)));
    return *this;
  }

  virtual Queryable<TObj, std::list, TObjOut, TAllocator> & Sort(std::function<bool(TObj, TObj)> lessThan = [](TObj a, TObj b) { return a < b; }) override
  {
    // don't think anything special needs done other than just calling sort
    ListSorter<TObj, TAllocator> sorter;
    this->items->Sort(sorter, lessThan);
    return *this;
  }
};

#endif
