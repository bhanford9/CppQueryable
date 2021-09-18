#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLEDATA_GROUPQUERYABLEMULTISETDATA_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLEDATA_GROUPQUERYABLEMULTISETDATA_H

#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <set>

#include "SortedGroupQueryableData.h"

template<
  typename TKey,
  typename TData,
  typename ...TArgs>
class GroupQueryableMultiSetData : public SortedGroupQueryableData<TKey, TData, std::multiset, TArgs...>
{
protected:
  typedef typename std::vector<TData>::iterator TVectorIterator;

public:

  GroupQueryableMultiSetData(
    TKey key,
    QueryableType type,
    std::function<bool(TKey, TKey)> keyCompare = [](TKey a, TKey b) { return a < b; },
    std::function<bool(TData, TData)> compare = [](TData a, TData b) { return a < b; })
    : SortedGroupQueryableData<TKey, TData, std::multiset, TArgs...>(key, type, keyCompare, compare)
  {
  }

  GroupQueryableMultiSetData(
    TKey key,
    std::shared_ptr<IQueryableData<TData>> data,
    QueryableType type,
    std::function<bool(TKey, TKey)> keyCompare = [](TKey a, TKey b) { return a < b; },
    std::function<bool(TData, TData)> compare = [](TData a, TData b) { return a < b; })
    : SortedGroupQueryableData<TKey, TData, std::multiset, TArgs...>(key, std::move(data), type, keyCompare, compare)
  {
  }

  GroupQueryableMultiSetData(const GroupQueryableMultiSetData<TData, TKey, TArgs...> & data)
    : SortedGroupQueryableData<TKey, TData, std::multiset, TArgs...>(data)
  {
  }

  GroupQueryableMultiSetData(
    TKey key,
    TVectorIterator first,
    TVectorIterator last,
    QueryableType type,
    std::function<bool(TKey, TKey)> keyCompare = [](TKey a, TKey b) { return a < b; },
    std::function<bool(TData, TData)> compare = [](TData a, TData b) { return a < b; })
    : SortedGroupQueryableData<TKey, TData, std::set, TArgs...>(key, first, last, type, keyCompare, compare)
  {
  }

  virtual ~GroupQueryableMultiSetData() { }
};

#endif
