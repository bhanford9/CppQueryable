#ifndef CPPQUERYABLE_QUERYABLE_SELECTQUERYABLEMULTISETDATA_H
#define CPPQUERYABLE_QUERYABLE_SELECTQUERYABLEMULTISETDATA_H

#include <iostream>
#include <set>

#include "SelectQueryableData.hpp"

// TODO --> think [multi]sets will need two compare templates
template<
  typename TOriginal,
  typename TCurrent,
  typename TCompare = std::less<TCurrent>,
  typename TAllocator = std::allocator<TOriginal>>
class SelectQueryableMultiSetData : public SelectQueryableData<TOriginal, TCurrent, std::multiset, TCompare, TAllocator>
{
public:
  SelectQueryableMultiSetData(
    std::shared_ptr<QueryableData<TOriginal, std::multiset, TCompare, TAllocator>> && data,
    std::function<TCurrent(TOriginal)> selector,
    TCompare comparator = {})
    : SelectQueryableData<TOriginal, TCurrent, std::multiset, TCompare, TAllocator>(std::move(data), selector)
  {
  }

  virtual ~SelectQueryableMultiSetData() { }

  virtual std::shared_ptr<IQueryableData<TCurrent>> Clone() override
  {
    return std::make_shared<SelectQueryableMultiSetData<TOriginal, TCurrent, TCompare, TAllocator>>(*this);
  }

  void Add(TCurrent item) override
  {
    // this wont easily or quickly work... might want to nix it
    this->items->insert(item);
    this->size++;
  }
};

#endif
