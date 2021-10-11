#ifndef CPPQUERYABLE_QUERYABLE_WHEREQUERYABLEDEQUEDATA_H
#define CPPQUERYABLE_QUERYABLE_WHEREQUERYABLEDEQUEDATA_H

#include <iostream>
#include <deque>

#include "../../Utilities/Condition.h"
#include "WhereQueryableData.h"

template<typename TOriginal>
class WhereQueryableDequeData : public WhereQueryableData<TOriginal, std::deque>
{
private:
  void InitWhereRandomAccessProperties()
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
  WhereQueryableDequeData(
    std::shared_ptr<IQueryableData<TOriginal>> data,
    std::function<bool(TOriginal)> condition)
    : WhereQueryableData<TOriginal, std::deque>(std::move(data), std::move(condition))
  {
    this->InitWhereRandomAccessProperties();
  }
  WhereQueryableDequeData(const WhereQueryableDequeData & other)
    : WhereQueryableData<TOriginal, std::deque>(other)
  {
  }

  virtual ~WhereQueryableDequeData() { }

  void Add(TOriginal item) override
  {
    // this wont easily or quickly work... might want to nix it
    this->items.push_back(item);
    this->size++;
  }
};

#endif
