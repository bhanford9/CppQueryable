#ifndef CPPQUERYABLE_QUERYABLE_WHEREQUERYABLEMAPDATA_H
#define CPPQUERYABLE_QUERYABLE_WHEREQUERYABLEMAPDATA_H

#include <iostream>
#include <map>

#include "../../Utilities/Condition.hpp"
#include "../QueryableMapData.hpp"

template<
  typename TKey,
  typename TValue,
  typename TCompare = std::less<TKey>,
  typename TAllocator = std::allocator<std::pair<const TKey, TValue>>>
class WhereQueryableMapData : public WhereQueryableData<TKey, std::map, std::pair<const TKey, TValue>, TValue, TCompare, TAllocator>
{
public:
  WhereQueryableMapData(
    std::shared_ptr<IQueryableData<std::pair<const TKey, TValue>>> data,
    std::function<bool(std::pair<const TKey, TValue>)> condition)
    : WhereQueryableData<TKey, std::map, std::pair<const TKey, TValue>, TValue, TCompare, TAllocator>(std::move(data), std::move(condition))
  {
  }
  WhereQueryableMapData(
    std::shared_ptr<QueryableData<TKey, std::map, std::pair<const TKey, TValue>, TValue, TCompare, TAllocator>> && data,
    std::function<bool(std::pair<const TKey, TValue>)> condition)
    : WhereQueryableData<TKey, std::map, std::pair<const TKey, TValue>, TValue, TCompare, TAllocator>(std::move(data), std::move(condition))
  {
  }
  WhereQueryableMapData(const WhereQueryableMapData<TKey, TValue, TCompare, TAllocator> & other)
    : WhereQueryableData<TKey, std::map, std::pair<const TKey, TValue>, TValue, TCompare, TAllocator>(other)
  {
  }

  virtual ~WhereQueryableMapData() { }

  virtual std::shared_ptr<IQueryableData<std::pair<const TKey, TValue>>> Clone() override
  {
    return std::make_shared<WhereQueryableMapData<TKey, TValue, TCompare, TAllocator>>(*this);
  }

  virtual void InternalAdd(std::pair<const TKey, TValue> item) override
  {
    this->items->insert(item);
  }

  virtual std::shared_ptr<IQueryableData<std::pair<const TKey, TValue>>> GetRealizedQueryableData() override
  {
    // If all QueryableData's have a constructor that takes begin, end, Args... then this method can be a one liner
    std::map<TKey, TValue, TCompare, TAllocator> data(this->items->key_comp(), this->items->get_allocator());

    for (const std::pair<const TKey, TValue> & value : *this)
    {
        data[value.first] = value.second;
    }

    return std::make_shared<QueryableMapData<TKey, TValue, TCompare, TAllocator>>(std::move(data));
  }
};

#endif
