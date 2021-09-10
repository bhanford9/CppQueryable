#ifndef CPPQUERYABLE_QUERYABLE_WHEREQUERYABLEDEQUEDATA_H
#define CPPQUERYABLE_QUERYABLE_WHEREQUERYABLEDEQUEDATA_H

#include <iostream>
#include <deque>

#include "../../Utilities/Condition.h"
#include "WhereQueryableData.h"

template<typename TOriginal>
class WhereQueryableDequeData : public WhereQueryableData<TOriginal, std::deque>
{
public:
  WhereQueryableDequeData(
    std::shared_ptr<IQueryableData<TOriginal>> data,
    std::function<bool(TOriginal)> condition)
    : WhereQueryableData<TOriginal, std::deque>(std::move(data), condition)
  {
  }

  virtual ~WhereQueryableDequeData() { }

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
