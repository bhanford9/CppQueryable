#ifndef CPPQUERYABLE_QUERYABLE_SELECTQUERYABLESETDATA_H
#define CPPQUERYABLE_QUERYABLE_SELECTQUERYABLESETDATA_H

#include <iostream>
#include <set>

#include "SelectQueryableData.hpp"

template<
  typename TOriginal,
  typename TCurrent,
  typename TCompare = std::less<TCurrent>,
  typename TAllocator = std::allocator<TOriginal>>
class SelectQueryableSetData : public SelectQueryableData<TOriginal, TCurrent, std::set, TCompare, TAllocator>
{
public:
  SelectQueryableSetData(
    std::shared_ptr<QueryableData<TOriginal, std::set, TCompare, TAllocator>> && data,
    std::function<TCurrent(TOriginal)> selector,
    TCompare comparator = {})
    : SelectQueryableData<TOriginal, TCurrent, std::set, TCompare, TAllocator>(std::move(data), selector)
  {
  }
  SelectQueryableSetData(
    const std::shared_ptr<QueryableData<TOriginal, std::set, TCompare, TAllocator>> & data,
    std::function<TCurrent(TOriginal)> selector,
    TCompare comparator = {})
    : SelectQueryableData<TOriginal, TCurrent, std::set, TCompare, TAllocator>(data, selector)
  {
  }

  virtual ~SelectQueryableSetData() { }

  virtual std::shared_ptr<IQueryableData<TCurrent>> Clone() override
  {
    return std::make_shared<SelectQueryableSetData<TOriginal, TCurrent, TCompare, TAllocator>>(*this);
  }

  void Add(TCurrent item) override
  {
    // this wont easily or quickly work... might want to nix it
    this->items->insert(item);
    this->size++;
  }
};

#endif
