#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLEDATA_GROUPQUERYABLESETDATA_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLEDATA_GROUPQUERYABLESETDATA_H

#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <set>

#include "../../QueryableType.hpp"
#include "SortedGroupQueryableData.hpp"

template<
  typename TKey,
  typename TData,
  typename ...TArgs>
class GroupQueryableSetData : public SortedGroupQueryableData<TKey, TData, std::set, TArgs...>
{
protected:
  typedef typename std::vector<TData>::iterator TVectorIterator;

public:

  GroupQueryableSetData(
    TKey key,
    QueryableType type,
    std::function<bool(TKey, TKey)> keyCompare = [](TKey a, TKey b) { return a < b; },
    std::function<bool(TData, TData)> compare = [](TData a, TData b) { return a < b; })
    : SortedGroupQueryableData<TKey, TData, std::set, TArgs...>(key, type, keyCompare, compare)
  {
  }

  GroupQueryableSetData(
    TKey key,
    std::shared_ptr<IQueryableData<TData>> data,
    QueryableType type,
    std::function<bool(TKey, TKey)> keyCompare = [](TKey a, TKey b) { return a < b; },
    std::function<bool(TData, TData)> compare = [](TData a, TData b) { return a < b; })
    : SortedGroupQueryableData<TKey, TData, std::set, TArgs...>(key, std::move(data), type, keyCompare, compare)
  {
  }

  GroupQueryableSetData(const GroupQueryableSetData<TData, TKey, TArgs...> & data)
    : SortedGroupQueryableData<TKey, TData, std::set, TArgs...>(data)
  {
  }

  GroupQueryableSetData(
    TKey key,
    TVectorIterator first,
    TVectorIterator last,
    QueryableType type,
    std::function<bool(TKey, TKey)> keyCompare = [](TKey a, TKey b) { return a < b; },
    std::function<bool(TData, TData)> compare = [](TData a, TData b) { return a < b; })
    : SortedGroupQueryableData<TKey, TData, std::set, TArgs...>(key, first, last, type, keyCompare, compare)
  {
  }

  virtual ~GroupQueryableSetData() { }
};

#endif
