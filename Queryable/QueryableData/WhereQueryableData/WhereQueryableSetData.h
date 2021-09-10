#ifndef CPPQUERYABLE_QUERYABLE_WHEREQUERYABLESETDATA_H
#define CPPQUERYABLE_QUERYABLE_WHEREQUERYABLESETDATA_H

#include <iostream>
#include <set>

#include "../../Utilities/Condition.h"
#include "WhereQueryableData.h"

template<typename TOriginal>
class WhereQueryableSetData : public WhereQueryableData<TOriginal, std::set>
{
public:
  WhereQueryableSetData(
    std::shared_ptr<IQueryableData<TOriginal>> data,
    std::function<bool(TOriginal)> condition)
    : WhereQueryableData<TOriginal, std::set>(std::move(data), condition)
  {
  }

  virtual ~WhereQueryableSetData() { }

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
