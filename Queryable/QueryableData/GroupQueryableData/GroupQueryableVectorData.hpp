#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLEDATA_GROUPQUERYABLEVECTORDATA_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLEDATA_GROUPQUERYABLEVECTORDATA_H

#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <vector>

#include "../../QueryableType.hpp"
#include "RandomAccessGroupQueryableData.hpp"

template<
  typename TKey,
  typename TData,
  typename ...TArgs>
class GroupQueryableVectorData : public RandomAccessGroupQueryableData<TKey, TData, std::vector, TArgs...>
{
public:
  GroupQueryableVectorData(
    TKey key,
    QueryableType type,
    std::function<bool(TKey, TKey)> keyCompare = [](TKey a, TKey b) { return a < b; })
    : RandomAccessGroupQueryableData<TKey, TData, std::vector, TArgs...>(key, type, keyCompare)
  {
  }

  GroupQueryableVectorData(
    TKey key,
    std::shared_ptr<IQueryableData<TData>> data,
    QueryableType type,
    std::function<bool(TKey, TKey)> keyCompare = [](TKey a, TKey b) { return a < b; })
    : RandomAccessGroupQueryableData<TKey, TData, std::vector, TArgs...>(key, std::move(data), type, keyCompare)
  {
  }

  GroupQueryableVectorData(const GroupQueryableVectorData<TData, TKey, TArgs...> & data)
    : RandomAccessGroupQueryableData<TKey, TData, std::vector, TArgs...>(data)
  {
  }

  virtual ~GroupQueryableVectorData() { }
};

#endif
