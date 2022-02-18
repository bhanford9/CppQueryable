#ifndef CPPQUERYABLE_QUERYABLE_SELECTQUERYABLELISTDATA_H
#define CPPQUERYABLE_QUERYABLE_SELECTQUERYABLELISTDATA_H

#include <iostream>
#include <list>

#include "SelectQueryableData.h"

template<typename TOriginal, typename TCurrent>
class SelectQueryableListData : public SelectQueryableData<TOriginal, TCurrent, std::list>
{
public:
  SelectQueryableListData(
    std::shared_ptr<IQueryableData<TOriginal, TCurrent>> data,
    std::function<TCurrent(TOriginal)> selector)
    : SelectQueryableData<TOriginal, TCurrent, std::list>(std::move(data), selector)
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
