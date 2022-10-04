#ifndef CPPQUERYABLE_QUERYABLE_INTERNALQUERYABLES_MAPINTERNALQUERYABLE_H
#define CPPQUERYABLE_QUERYABLE_INTERNALQUERYABLES_MAPINTERNALQUERYABLE_H

#include <iostream>
#include <map>
#include "QueryableForwardDeclare.hpp"
#include "../InternalQueryable.hpp"
#include "../QueryableType.hpp"
#include "../QueryableData/QueryableMapData.hpp"
#include "../QueryableData/WhereQueryableData/WhereQueryableMapData.hpp"
#include "../QueryableData/SkipWhileQueryableData/SkipWhileQueryableMapData.hpp"
// #include "../QueryableData/TakeWhileQueryableData/TakeWhileQueryableMapData.hpp"
#include "../Utilities/IWhileCondition.hpp"

template<
  typename TKey,
  typename TValue,
  typename TLessThan,
  typename TAllocator>
class MapInternalQueryable : public InternalQueryable<TKey, std::map, std::pair<const TKey, TValue>, TValue, TLessThan, TAllocator>
{
public:
  MapInternalQueryable(TLessThan lessThan = {}, TAllocator allocator = {}) :
    InternalQueryable<TKey, std::map, std::pair<const TKey, TValue>, TValue, TLessThan, TAllocator>(
      QueryableType::Map,
      lessThan,
      allocator)
  {
    std::map<TKey, TValue, TLessThan, TAllocator> localMap(lessThan, allocator);
    this->items = std::make_shared<QueryableMapData<TKey, TValue, TLessThan, TAllocator>>(localMap);
  }

  MapInternalQueryable(const std::map<TKey, TValue, TLessThan, TAllocator> & map)
  {
    this->type = QueryableType::Map;
    this->items = std::make_shared<QueryableMapData<TKey, TValue, TLessThan, TAllocator>>(map);
  }

  MapInternalQueryable(std::map<TKey, TValue, TLessThan, TAllocator> && map)
  {
    this->type = QueryableType::Map;
    this->items = std::make_shared<QueryableMapData<TKey, TValue, TLessThan, TAllocator>>(std::move(map));
  }

  MapInternalQueryable(const MapInternalQueryable<TKey, TValue, TLessThan, TAllocator> & other)
  {
    this->type = QueryableType::Map;
    this->items = other.items;
  }

  MapInternalQueryable(
    const InternalQueryable<TKey, std::map, std::pair<const TKey, TValue>, TValue, TLessThan, TAllocator> & other)
      : InternalQueryable<TKey, std::map, std::pair<const TKey, TValue>, TValue, TLessThan, TAllocator>(other, QueryableType::Map)
  {
  }
  MapInternalQueryable(
    std::shared_ptr<QueryableData<TKey, std::map, std::pair<const TKey, TValue>, TValue, TLessThan, TAllocator>> && queryableData,
    QueryableType type)
      : InternalQueryable<TKey, std::map, std::pair<const TKey, TValue>, TValue, TLessThan, TAllocator>(std::move(queryableData), type)
  {
  }

  MapInternalQueryable(
    const QueryableIterator<TValue> & first,
    const QueryableIterator<TValue> & last,
    TLessThan lessThan = {},
    TAllocator allocator = {})
  {
    this->items = std::make_shared<QueryableMapData<TKey, TValue, TLessThan, TAllocator>>(
      std::map<TKey, TValue, TLessThan, TAllocator>(first, last, lessThan, allocator));
    this->type = QueryableType::Map;
  }

  virtual void Where(std::function<bool(const std::pair<const TKey, TValue> &)> condition) override
  {
    this->items = std::move(
      std::make_shared<WhereQueryableMapData<TKey, TValue, TLessThan, TAllocator>>(
        std::move(this->items),
        std::move(condition)));
  }
  
  virtual void InternalSkipWhile(std::shared_ptr<IWhileCondition<std::pair<const TKey, TValue>>> && condition) override
  {
    this->items = std::move(std::make_shared<SkipWhileQueryableMapData<TKey, TValue, TLessThan, TAllocator>>(
      std::move(this->items),
      std::move(condition)));
  }
  
  virtual void InternalTakeWhile(std::shared_ptr<IWhileCondition<std::pair<const TKey, TValue>>> && condition) override
  {
    // this->items = std::move(std::make_shared<TakeWhileQueryableMapData<TKey, TValue, TLessThan, TAllocator>>(
    //   std::move(this->items),
    //   std::move(condition)));
  }
};

#endif
