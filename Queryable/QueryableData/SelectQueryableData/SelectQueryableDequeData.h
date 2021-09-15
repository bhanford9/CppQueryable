#ifndef CPPQUERYABLE_QUERYABLE_SELECTQUERYABLEDEQUEDATA_H
#define CPPQUERYABLE_QUERYABLE_SELECTQUERYABLEDEQUEDATA_H

#include <iostream>
#include <deque>

#include "SelectQueryableData.h"

template<typename TOriginal, typename TCurrent>
class SelectQueryableDequeData : public SelectQueryableData<TOriginal, TCurrent, std::deque>
{
private:
  void InitRandomAccessProperties()
  {
    this->beginning.Add = [&](int addend, int64_t & index) { this->originalBeginning += addend; index += addend; };
    this->beginning.Subtract = [&](int subtrahend, int64_t & index) { this->originalBeginning -= subtrahend; index -= subtrahend; };

    this->ending.Add = [&](int addend, int64_t & index) { this->originalEnding += addend; index += addend; };
    this->ending.Subtract = [&](int subtrahend, int64_t & index) { this->originalEnding -= subtrahend; index -= subtrahend; };

    this->rbeginning.Add = [&](int addend, int64_t & index) { this->originalBeginning += addend; index += addend; };
    this->rbeginning.Subtract = [&](int subtrahend, int64_t & index) { this->originalBeginning -= subtrahend; index -= subtrahend; };

    this->rending.Add = [&](int addend, int64_t & index) { this->originalREnding += addend; index += addend; };
    this->rending.Subtract = [&](int subtrahend, int64_t & index) { this->originalREnding -= subtrahend; index -= subtrahend; };
  }

public:
  SelectQueryableDequeData(
    std::shared_ptr<IQueryableData<TOriginal>> data,
    std::function<TCurrent(TOriginal)> selector)
    : SelectQueryableData<TOriginal, TCurrent, std::deque>(std::move(data), selector)
  {
    this->InitRandomAccessProperties();
  }

  virtual ~SelectQueryableDequeData() { }

  void Add(TCurrent item) override
  {
    // this wont easily or quickly work... might want to nix it
    this->items.push_back(item);
    this->size++;
  }
};

#endif
