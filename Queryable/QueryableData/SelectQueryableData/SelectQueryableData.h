#ifndef CPPQUERYABLE_QUERYABLE_SELECTQUERYABLEDATA_H
#define CPPQUERYABLE_QUERYABLE_SELECTQUERYABLEDATA_H

#include <algorithm>
#include <deque>
#include <exception>
#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <set>
#include <vector>

#include "../../TypeConstraintUtil.h"
#include "../../Utilities/Condition.h"
#include "../IQueryableData.h"
#include "../QueryableData.h"
#include "../LinkedQueryableData.h"

template<typename TOriginal, typename TCurrent, template<typename, typename ...> typename TIterable, typename ...TArgs>
class SelectQueryableData : public LinkedQueryableData<TOriginal, TCurrent, TIterable, TArgs...>
{
  static_assert(can_iterate<TIterable<TCurrent, TArgs...>>::value, "Class must be able to be iterated over");
protected:
  std::function<TCurrent(TOriginal)> selector;
public:

  SelectQueryableData(
    std::shared_ptr<IQueryableData<TOriginal>> data,
    std::function<TCurrent(TOriginal)> selector)
    : LinkedQueryableData<TOriginal, TCurrent, TIterable, TArgs...>(std::move(data))
  {
    this->selector = selector;
  }

  SelectQueryableData(const SelectQueryableData<TOriginal, TCurrent, TIterable, TArgs...> & data)
    : LinkedQueryableData<TOriginal, TCurrent, TIterable, TArgs...>(data)
  {
  }

  virtual ~SelectQueryableData() { }

  virtual int Count() override
  {
    return this->original.get()->Count();
  }

  virtual TCurrent ToCurrent(const TOriginal & original) override
  {
    return this->selector(original);
  }

  // if we ever want to return true here, will need to change signature to take
  // a TCurrent instead of a TOriginal. Its faster in the iterator incrementing
  // if we do not have to convert from TOriginal to TCurrent though
  virtual bool DoSkip(const TOriginal & value) override
  {
    return false;
  }

  virtual bool CanSkip() override
  {
    return false;
  }
};

#endif
