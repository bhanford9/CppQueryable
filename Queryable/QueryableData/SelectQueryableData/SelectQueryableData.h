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
    IQueryableData<TOriginal> * data,
    std::function<TCurrent(TOriginal)> selector)
    : LinkedQueryableData<TOriginal, TCurrent, TIterable, TArgs...>(data)
  {
    this->selector = selector;
  }

  virtual ~SelectQueryableData() { }

  virtual TCurrent ToCurrent(TOriginal original) override
  {
    return this->selector(original);
  }

  virtual bool DoSkip(TCurrent value) override
  {
    return false;
  }

  virtual bool CanSkip() override
  {
    return false;
  }
};

#endif
