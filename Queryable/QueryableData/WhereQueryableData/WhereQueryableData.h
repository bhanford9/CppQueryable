#ifndef CPPQUERYABLE_QUERYABLE_WHEREQUERYABLEDATA_H
#define CPPQUERYABLE_QUERYABLE_WHEREQUERYABLEDATA_H

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
#include "../LinkedQueryableData.h"

template<typename TOriginal, template<typename, typename ...> typename TIterable, typename ...TArgs>
class WhereQueryableData : public LinkedQueryableData<TOriginal, TOriginal, TIterable, TArgs...>
{
  static_assert(can_iterate<TIterable<TOriginal, TArgs...>>::value, "Class must be able to be iterated over");
protected:
  Condition<TOriginal> condition;
public:

  WhereQueryableData(
    IQueryableData<TOriginal> * data,
    std::function<bool(TOriginal)> condition)
    : LinkedQueryableData<TOriginal, TOriginal, TIterable, TArgs...>(data)
  {
    this->condition += condition;
  }

  virtual ~WhereQueryableData() { }

  virtual int Count() override
  {
    int count = 0;

    for (TOriginal item : *this->original)
    {
      if (this->condition(item))
      {
        count++;
      }
    }

    return count;
  }

  virtual std::vector<TOriginal> ToVector() override
  {
    std::vector<TOriginal> objs;

    for (TOriginal item : *this->original)
    {
      if (this->condition(item))
      {
        objs.push_back(item);
      }
    }

    return objs;
  }

  virtual TOriginal ToCurrent(TOriginal original) override
  {
    return original;
  }

  virtual bool DoSkip(TOriginal value) override
  {
    return this->CanSkip() && !condition(value);
  }

  virtual bool CanSkip() override
  {
    return this->condition;
  }
};

#endif
