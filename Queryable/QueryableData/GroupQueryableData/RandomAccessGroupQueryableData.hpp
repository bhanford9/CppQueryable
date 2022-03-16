#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLEDATA_RANDOMACCESSGROUPQUERYABLEDATA_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLEDATA_RANDOMACCESSGROUPQUERYABLEDATA_H

#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>

#include "../../QueryableType.hpp"
#include "GroupQueryableData.hpp"

template<
  typename TKey,
  typename TData,
  template<typename, typename ...> typename TIterable,
  typename ...TArgs>
class RandomAccessGroupQueryableData : public GroupQueryableData<TKey, TData, TIterable, TArgs...>
{
private:
  void InitRandomAccessProperties()
  {
    this->beginning.Add = [&](int addend, int64_t & index) { this->beginIterator += addend; index += addend; };
    this->beginning.Subtract = [&](int subtrahend, int64_t & index) { this->beginIterator -= subtrahend; index -= subtrahend; };

    this->ending.Add = [&](int addend, int64_t & index) { this->endIterator += addend; index += addend; };
    this->ending.Subtract = [&](int subtrahend, int64_t & index) { this->endIterator -= subtrahend; index -= subtrahend; };

    this->rbeginning.Add = [&](int addend, int64_t & index) { this->rbeginIterator += addend; index += addend; };
    this->rbeginning.Subtract = [&](int subtrahend, int64_t & index) { this->rbeginIterator -= subtrahend; index -= subtrahend; };

    this->rending.Add = [&](int addend, int64_t & index) { this->rendIterator += addend; index += addend; };
    this->rending.Subtract = [&](int subtrahend, int64_t & index) { this->rendIterator -= subtrahend; index -= subtrahend; };
  }

public:
  RandomAccessGroupQueryableData(
    TKey key,
    QueryableType type,
    std::function<bool(TKey, TKey)> keyCompare = [](TKey a, TKey b) { return a < b; })
    : GroupQueryableData<TKey, TData, TIterable, TArgs...>(key, type, keyCompare)
  {
    this->InitRandomAccessProperties();
  }

  RandomAccessGroupQueryableData(
    TKey key,
    std::shared_ptr<IQueryableData<TData>> data,
    QueryableType type,
    std::function<bool(TKey, TKey)> keyCompare = [](TKey a, TKey b) { return a < b; })
    : GroupQueryableData<TKey, TData, TIterable, TArgs...>(key, std::move(data), type, keyCompare)
  {
    this->InitRandomAccessProperties();
  }

  RandomAccessGroupQueryableData(const RandomAccessGroupQueryableData<TData, TKey, TIterable, TArgs...> & data)
    : GroupQueryableData<TKey, TData, TIterable, TArgs...>(data)
  {
    this->InitRandomAccessProperties();
  }

  virtual ~RandomAccessGroupQueryableData() { }

  void Add(TData item) override
  {
    this->items.push_back(item);
    this->size++;
  }

  void Sort(std::function<bool(TData, TData)> compare = [](TData a, TData b) { return a < b; }) override
  {
    // todo figure out how to get this to work with this->begin instead o this->items.begin()
    std::sort(this->items.begin(), this->items.end(), compare);
  }
};

#endif
