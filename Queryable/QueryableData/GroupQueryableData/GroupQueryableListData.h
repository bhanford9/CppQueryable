#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLEDATA_GROUPQUERYABLELISTDATA_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLEDATA_GROUPQUERYABLELISTDATA_H

#include <functional>
#include <iostream>
#include <list>
#include <memory>

#include "../../QueryableType.h"
#include "GroupQueryableData.h"

template<
  typename TKey,
  typename TData,
  typename ...TArgs>
class GroupQueryableListData : public GroupQueryableData<TKey, TData, std::list, TArgs...>
{
public:
  GroupQueryableListData(
    TKey key,
    QueryableType type,
    std::function<bool(TKey, TKey)> keyCompare = [](TKey a, TKey b) { return a < b; })
    : GroupQueryableData<TKey, TData, std::list, TArgs...>(key, type, keyCompare)
  {
  }

  GroupQueryableListData(
    TKey key,
    std::shared_ptr<IQueryableData<TData, TData>> data,
    QueryableType type,
    std::function<bool(TKey, TKey)> keyCompare = [](TKey a, TKey b) { return a < b; })
    : GroupQueryableData<TKey, TData, std::list, TArgs...>(key, std::move(data), type, keyCompare)
  {
  }

  GroupQueryableListData(const GroupQueryableListData<TData, TKey, TArgs...> & data)
    : GroupQueryableData<TKey, TData, std::list, TArgs...>(data)
  {
  }

  virtual ~GroupQueryableListData() { }

  void Add(TData item) override
  {
    this->items.push_back(item);
    this->size++;
  }

  void Sort(std::function<bool(TData, TData)> compare = [](TData a, TData b) { return a < b; }) override
  {
    this->items.sort(compare);
  }
};

#endif
