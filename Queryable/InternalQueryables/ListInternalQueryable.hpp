#ifndef CPPQUERYABLE_QUERYABLE_INTERNALQUERYABLES_LISTINTERNALQUERYABLE_H
#define CPPQUERYABLE_QUERYABLE_INTERNALQUERYABLES_LISTINTERNALQUERYABLE_H

#include <list>
#include "QueryableForwardDeclare.hpp"
#include "../QueryableType.hpp"
#include "../QueryableData/QueryableListData.hpp"
#include "../QueryableData/SkipWhileQueryableData/SkipWhileQueryableListData.hpp"
#include "../QueryableData/TakeWhileQueryableData/TakeWhileQueryableListData.hpp"
#include "../QueryableData/WhereQueryableData/WhereQueryableListData.hpp"
#include "../Utilities/IWhileCondition.hpp"

template<
  typename TObj,
  typename TAllocator>
class ListInternalQueryable final : public InternalQueryable<TObj, std::list, TObj, TAllocator>
{
public:
  virtual ~ListInternalQueryable() = default;

  ListInternalQueryable(const ListInternalQueryable & other)
    : InternalQueryable<TObj, std::list, TObj, TAllocator>(other)
  {
  }

  ListInternalQueryable(ListInternalQueryable && other) noexcept
    : InternalQueryable<TObj, std::list, TObj, TAllocator>(std::move(other))
  {
  }

  explicit ListInternalQueryable(TAllocator allocator = {}) :
    InternalQueryable<TObj, std::list, TObj, TAllocator>(QueryableType::List)
  {
    std::list<TObj> localList(allocator);
    this->items = std::make_shared<QueryableListData<TObj, TAllocator>>(localList);
  }

  explicit ListInternalQueryable(const std::list<TObj, TAllocator> & list)
  {
    this->type = QueryableType::List;
    this->items = std::move(std::make_shared<QueryableListData<TObj, TAllocator>>(list));
  }

  explicit ListInternalQueryable(const InternalQueryable<TObj, std::list, TObj, TAllocator> & other)
    : InternalQueryable<TObj, std::list, TObj, TAllocator>(other)
  {
    this->type = QueryableType::List;
  }
  ListInternalQueryable(
    std::shared_ptr<QueryableData<TObj, std::list, TObj, TAllocator>> && queryableData,
    QueryableType type)
    : InternalQueryable<TObj, std::list, TObj, TAllocator>(std::move(queryableData), type)
  {
  }

  ListInternalQueryable(const QueryableIterator<TObj> & first, const QueryableIterator<TObj> & last, TAllocator allocator = {})
  {
    this->items = std::make_shared<QueryableListData<TObj, TAllocator>>(std::list<TObj, TAllocator>(first, last, allocator));
    this->type = QueryableType::List;
  }

  ListInternalQueryable & operator=(const ListInternalQueryable & other)
  {
    if (this == &other) return *this;
    InternalQueryable<TObj, std::list, TObj, TAllocator>::operator =(other);
    return *this;
  }

  ListInternalQueryable & operator=(ListInternalQueryable && other) noexcept
  {
    if (this == &other) return *this;
    InternalQueryable<TObj, std::list, TObj, TAllocator>::operator =(std::move(other));
    return *this;
  }

  virtual void Where(std::function<bool(const TObj &)> condition) override
  {
    this->items = std::move(std::make_shared<WhereQueryableListData<TObj, TAllocator>>(std::move(this->items), std::move(condition)));
  }

  virtual void InternalSkipWhile(std::shared_ptr<IWhileCondition<TObj>> && condition) override
  {
    this->items = std::move(std::make_shared<SkipWhileQueryableListData<TObj, TAllocator>>(
      std::move(this->items),
      std::move(condition)));
  }

  virtual void InternalTakeWhile(std::shared_ptr<IWhileCondition<TObj>> && condition) override
  {
    this->items = std::move(std::make_shared<TakeWhileQueryableListData<TObj, TAllocator>>(
      std::move(this->items),
      std::move(condition)));
  }
};

#endif
