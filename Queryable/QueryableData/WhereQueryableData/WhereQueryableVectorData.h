#ifndef CPPQUERYABLE_QUERYABLE_WHEREQUERYABLEVECTORDATA_H
#define CPPQUERYABLE_QUERYABLE_WHEREQUERYABLEVECTORDATA_H

#include <iostream>
#include <vector>

#include "../../Utilities/Condition.h"
#include "WhereQueryableData.h"

template<typename TOriginal>
class WhereQueryableVectorData : public WhereQueryableData<TOriginal, std::vector>
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
  WhereQueryableVectorData(
    std::shared_ptr<IQueryableData<TOriginal>> data,
    std::function<bool(TOriginal)> condition)
    : WhereQueryableData<TOriginal, std::vector>(std::move(data), condition)
  {
    this->InitWhereRandomAccessProperties();
  }

  virtual ~WhereQueryableVectorData() { }

  void Add(TOriginal item) override
  {
    // this wont easily or quickly work... might want to nix it
    this->items.push_back(item);
    this->size++;
  }
};

#endif
