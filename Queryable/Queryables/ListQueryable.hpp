#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLERS_LISTQUERYABLE_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLERS_LISTQUERYABLE_H

#include <iostream>
#include <list>

#include "../Queryable.hpp"
#include "../QueryableType.hpp"
#include "../QueryableData/QueryableListData.hpp"

template<
  typename TObj,
  typename TAllocator = std::allocator<TObj>>
class ListQueryable : public Queryable<TObj, std::list, TAllocator>
{
public:
  ListQueryable()
  {
    this->queryable = std::make_shared<ListInternalQueryable<TObj, TAllocator>>();
  }
  virtual ~ListQueryable() { }

  ListQueryable(const ListInternalQueryable<TObj, TAllocator> && other)
    : Queryable<TObj, std::list, TAllocator>(std::move(other))
  {
  }

  ListQueryable(const std::list<TObj, TAllocator> & iterable)
  {
    this->queryable = std::make_shared<ListInternalQueryable<TObj, TAllocator>>(iterable);
  }

  ListQueryable(const std::list<TObj, TAllocator> && iterable)
  {
    this->queryable = std::make_shared<ListInternalQueryable<TObj, TAllocator>>(std::move(iterable));
  }
};

#endif
