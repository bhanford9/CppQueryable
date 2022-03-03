#ifndef CPPQUERYABLE_QUERYABLE_SELECTQUERYABLEVECTORDATA_H
#define CPPQUERYABLE_QUERYABLE_SELECTQUERYABLEVECTORDATA_H

#include <iostream>
#include <vector>

#include "SelectQueryableData.hpp"

template<
  typename TOriginal,
  typename TCurrent,
  typename TCompare = std::less<TCurrent>,
  typename TAllocator = std::allocator<TOriginal>>
class SelectQueryableVectorData : public SelectQueryableData<TOriginal, TCurrent, std::vector, TCompare, TAllocator>
{
private:

public:
  SelectQueryableVectorData(
    std::shared_ptr<IQueryableData<TOriginal, TCurrent>> data,
    std::function<TCurrent(TOriginal)> selector)
    : SelectQueryableData<TOriginal, TCurrent, std::vector, TCompare, TAllocator>(std::move(data), selector)
  {
    this->InitRandomAccessProperties();
  }
  virtual ~SelectQueryableVectorData() { }

  void Add(TCurrent item) override
  {
    // this wont easily or quickly work... might want to nix it
    this->items.push_back(item);
    this->size++;
  }
};

#endif
