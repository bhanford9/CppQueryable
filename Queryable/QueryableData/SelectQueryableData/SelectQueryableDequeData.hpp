#ifndef CPPQUERYABLE_QUERYABLE_SELECTQUERYABLEDEQUEDATA_H
#define CPPQUERYABLE_QUERYABLE_SELECTQUERYABLEDEQUEDATA_H

#include <iostream>
#include <deque>

#include "SelectQueryableData.hpp"

template<
  typename TOriginal,
  typename TCurrent,
  typename TAllocator = std::allocator<TCurrent>>
class SelectQueryableDequeData : public SelectQueryableData<TOriginal, TCurrent, std::deque, TAllocator>
{
public:
  SelectQueryableDequeData(
    std::shared_ptr<QueryableData<TOriginal, std::deque, TAllocator>> && data,
    std::function<TCurrent(TOriginal)> selector)
    : SelectQueryableData<TOriginal, TCurrent, std::deque, TAllocator>(std::move(data), selector)
  {
  }

  virtual ~SelectQueryableDequeData() { }

  virtual std::shared_ptr<IQueryableData<TCurrent>> Clone() override
  {
    return std::make_shared<SelectQueryableDequeData<TOriginal, TCurrent, TAllocator>>(*this);
  }

  void Add(TCurrent item) override
  {
    // this wont easily or quickly work... might want to nix it
    this->items->push_back(item);
    this->size++;
  }
};

#endif
