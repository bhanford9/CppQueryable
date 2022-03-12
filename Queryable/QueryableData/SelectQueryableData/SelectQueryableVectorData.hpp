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
    std::cout << "\n\nin SelectQueryableVectorData" << std::endl;
    for (TOriginal orig : *this->original) std::cout << "orig: " << orig << std::endl;
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
