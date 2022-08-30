#ifndef CPPQUERYABLE_QUERYABLE_INTERNALQUERYABLES_LISTINTERNALQUERYABLE_H
#define CPPQUERYABLE_QUERYABLE_INTERNALQUERYABLES_LISTINTERNALQUERYABLE_H

#include <iostream>
#include <list>
#include "QueryableForwardDeclare.hpp"
#include "../InternalQueryable.hpp"
#include "../QueryableType.hpp"
#include "../QueryableData/QueryableListData.hpp"
#include "../QueryableData/WhileQueryableData/WhileQueryableListData.hpp"
#include "../Utilities/IWhileCondition.hpp"

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
    this->type = QueryableType::List;
  }
  ListInternalQueryable(
    std::shared_ptr<QueryableData<TObj, std::list, TAllocator>> && queryableData,
    QueryableType type)
      : InternalQueryable<TObj, std::list, TAllocator>(std::move(queryableData), type)
  {
  }

  ListInternalQueryable(const QueryableIterator<TObj> & first, const QueryableIterator<TObj> & last, TAllocator allocator = {})
  {
    this->items = std::make_shared<QueryableListData<TObj, TAllocator>>(std::list<TObj, TAllocator>(first, last, allocator));
    this->type = QueryableType::List;
  }

  virtual void Where(std::function<bool(const TObj &)> condition) override
  {
    this->items = std::move(std::make_shared<WhereQueryableListData<TObj, TAllocator>>(std::move(this->items), std::move(condition)));
  }

  virtual void While(std::shared_ptr<IWhileCondition<TObj>> && condition) override
  {
    this->items = std::move(std::make_shared<WhileQueryableListData<TObj, TAllocator>>(
      std::move(this->items),
      std::move(condition)));
  }
};

#endif
