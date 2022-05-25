#ifndef CPPQUERYABLE_QUERYABLE_SELECTQUERYABLEVECTORDATA_H
#define CPPQUERYABLE_QUERYABLE_SELECTQUERYABLEVECTORDATA_H

#include <iostream>
#include <vector>

#include "SelectQueryableData.hpp"

template<
  typename TOriginal,
  typename TCurrent,
  typename TAllocator = std::allocator<TCurrent>>
class SelectQueryableVectorData : public SelectQueryableData<TOriginal, TCurrent, std::vector, TAllocator>
{
private:

public:
  SelectQueryableVectorData(
    std::shared_ptr<QueryableData<TOriginal, std::vector, TAllocator>> && data,
    std::function<TCurrent(TOriginal)> selector)
    : SelectQueryableData<TOriginal, TCurrent, std::vector, TAllocator>(std::move(data), selector)
  {
  }
  SelectQueryableVectorData(
    const std::shared_ptr<QueryableData<TOriginal, std::vector, TAllocator>> & data,
    std::function<TCurrent(TOriginal)> selector)
    : SelectQueryableData<TOriginal, TCurrent, std::vector, TAllocator>(data, selector)
  {
  }
  virtual ~SelectQueryableVectorData() { }

  virtual std::shared_ptr<IQueryableData<TCurrent>> Clone() override
  {
    return std::make_shared<SelectQueryableVectorData<TOriginal, TCurrent, TAllocator>>(*this);
  }

  void Add(TCurrent item) override
  {
    // this wont easily or quickly work... might want to nix it
    this->items->push_back(item);
    this->size++;
  }
};

#endif
