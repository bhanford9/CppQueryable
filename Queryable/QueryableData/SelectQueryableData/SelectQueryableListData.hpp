#ifndef CPPQUERYABLE_QUERYABLE_SELECTQUERYABLELISTDATA_H
#define CPPQUERYABLE_QUERYABLE_SELECTQUERYABLELISTDATA_H

#include <iostream>
#include <list>

#include "SelectQueryableData.hpp"

template<
  typename TOriginal,
  typename TCurrent,
  typename TCompare = std::less<TCurrent>,
  typename TAllocator = std::allocator<TOriginal>>
class SelectQueryableListData : public SelectQueryableData<TOriginal, TCurrent, std::list, TCompare, TAllocator>
{
public:
  SelectQueryableListData(
    std::shared_ptr<IQueryableData<TOriginal, TCurrent>> data,
    std::function<TCurrent(TOriginal)> selector)
    : SelectQueryableData<TOriginal, TCurrent, std::list, TCompare, TAllocator>(std::move(data), selector)
  {
  }

  virtual ~SelectQueryableListData() { }

  void Add(TCurrent item) override
  {
    // this wont easily or quickly work... might want to nix it
    this->items.push_back(item);
    this->size++;
  }
};

#endif
