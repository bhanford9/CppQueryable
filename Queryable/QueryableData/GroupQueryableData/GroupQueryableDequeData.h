#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLEDATA_GROUPQUERYABLEDEQUEDATA_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLEDATA_GROUPQUERYABLEDEQUEDATA_H

#include <algorithm>
#include <deque>
#include <functional>
#include <iostream>
#include <memory>

#include "RandomAccessGroupQueryableData.h"

template<
  typename TKey,
  typename TData,
  typename ...TArgs>
class GroupQueryableDequeData : public RandomAccessGroupQueryableData<TKey, TData, std::deque, TArgs...>
{
public:
  GroupQueryableDequeData(
    TKey key,
    QueryableType type,
    std::function<bool(TKey, TKey)> keyCompare = [](TKey a, TKey b) { return a < b; })
    : RandomAccessGroupQueryableData<TKey, TData, std::deque, TArgs...>(key, type, keyCompare)
  {
  }

  GroupQueryableDequeData(
    TKey key,
    std::shared_ptr<IQueryableData<TData>> data,
    QueryableType type,
    std::function<bool(TKey, TKey)> keyCompare = [](TKey a, TKey b) { return a < b; })
    : RandomAccessGroupQueryableData<TKey, TData, std::deque, TArgs...>(key, std::move(data), type, keyCompare)
  {
  }

  GroupQueryableDequeData(const GroupQueryableDequeData<TData, TKey, TArgs...> & data)
    : RandomAccessGroupQueryableData<TKey, TData, std::deque, TArgs...>(data)
  {
  }

  virtual ~GroupQueryableDequeData() { }
};

#endif
