#ifndef CPPQUERYABLE_QUERYABLE_SELECTQUERYABLELISTDATA_H
#define CPPQUERYABLE_QUERYABLE_SELECTQUERYABLELISTDATA_H

#include <iostream>
#include <list>

#include "SelectQueryableData.hpp"

template<
  typename TOriginal,
  typename TCurrent,
  typename TAllocator = std::allocator<TCurrent>>
class SelectQueryableListData : public SelectQueryableData<TOriginal, TCurrent, std::list, TAllocator>
{
public:
  SelectQueryableListData(
    std::shared_ptr<QueryableData<TOriginal, std::list, TAllocator>> && data,
    std::function<TCurrent(TOriginal)> selector)
    : SelectQueryableData<TOriginal, TCurrent, std::list, TAllocator>(std::move(data), selector)
  {
  }

  virtual ~SelectQueryableListData() { }

  virtual std::shared_ptr<IQueryableData<TCurrent>> Clone() override
  {
    return std::make_shared<SelectQueryableListData<TOriginal, TCurrent, TAllocator>>(*this);
  }

  void Add(TCurrent item) override
  {
    // this wont easily or quickly work... might want to nix it
    this->items->push_back(item);
    this->size++;
  }
};

#endif
