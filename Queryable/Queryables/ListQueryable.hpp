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
  typename TAllocator>
class ListQueryable : public Queryable<TObj, std::list, TAllocator>
{
public:
  ListQueryable(TAllocator allocator = {}) :
    Queryable<TObj, std::list, TAllocator>(QueryableType::List)
  {
    std::list<TObj> localList(allocator);
    this->items = std::make_shared<QueryableListData<TObj, TAllocator>>(localList);
  }

  ListQueryable(const std::list<TObj, TAllocator> & list)
  {
    this->type = QueryableType::List;
    this->items = std::move(std::make_shared<QueryableListData<TObj, TAllocator>>(list));
  }

  ListQueryable(const ListQueryable<TObj, TAllocator> & other)
  {
    this->type = QueryableType::List;
    this->items = other.items;
  }
};

#endif
