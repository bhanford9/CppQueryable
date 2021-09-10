#ifndef CPPQUERYABLE_QUERYABLE_WHEREQUERYABLEVECTORDATA_H
#define CPPQUERYABLE_QUERYABLE_WHEREQUERYABLEVECTORDATA_H

#include <iostream>
#include <vector>

#include "../../Utilities/Condition.h"
#include "WhereQueryableData.h"

template<typename TOriginal>
class WhereQueryableVectorData : public WhereQueryableData<TOriginal, std::vector>
{
public:
  WhereQueryableVectorData(
    IQueryableData<TOriginal> * data,
    std::function<bool(TOriginal)> condition)
    : WhereQueryableData<TOriginal, std::vector>(data, condition)
  {
  }

  virtual ~WhereQueryableVectorData() { }

  void Add(TOriginal item) override
  {
    // this wont easily or quickly work... might want to nix it
    this->items.push_back(item);
    this->size++;
  }

  void Sort(std::function<bool(TOriginal, TOriginal)> compare) override
  {
    // std::sort(this->begin(), this->end(), compare);
  }

};

#endif
