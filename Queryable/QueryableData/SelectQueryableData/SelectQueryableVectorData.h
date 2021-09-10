#ifndef CPPQUERYABLE_QUERYABLE_SELECTQUERYABLEVECTORDATA_H
#define CPPQUERYABLE_QUERYABLE_SELECTQUERYABLEVECTORDATA_H

#include <iostream>
#include <vector>

#include "SelectQueryableData.h"

template<typename TOriginal, typename TCurrent>
class SelectQueryableVectorData : public SelectQueryableData<TOriginal, TCurrent, std::vector>
{
public:
  SelectQueryableVectorData(
    IQueryableData<TOriginal> * data,
    std::function<TCurrent(TOriginal)> selector)
    : SelectQueryableData<TOriginal, TCurrent, std::vector>(data, selector)
  {
  }

  virtual ~SelectQueryableVectorData() { }

  void Add(TCurrent item) override
  {
    // this wont easily or quickly work... might want to nix it
    this->items.push_back(item);
    this->size++;
  }

  void Sort(std::function<bool(TCurrent, TCurrent)> compare) override
  {
    // std::sort(this->begin(), this->end(), compare);
  }
};

#endif
