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
  typedef typename std::vector<TOriginal>::iterator TVectorIterator;

  Condition<TOriginal> condition;
public:

  WhereQueryableData(
    std::shared_ptr<IQueryableData<TOriginal>> data,
    std::function<bool(TOriginal)> condition)
    : LinkedQueryableData<TOriginal, TOriginal, TIterable, TArgs...>(std::move(data))
  {
    this->condition += condition;
  }
  WhereQueryableData(const WhereQueryableData & other)
    : LinkedQueryableData<TOriginal, TOriginal, TIterable, TArgs...>(other)
  {
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

  virtual void Update(
    Iterator<TOriginal> first,
    Iterator<TOriginal> last,
    std::function<bool(TOriginal, TOriginal)> compare = [](TOriginal a, TOriginal b) { return a < b; }) override
  {
    // TODO SFINAE require this constructor
    this->original.get()->Update(this->original.get()->begin(), this->original.get()->end(), compare);
    this->size = this->original.get()->Count();
  }

  virtual void Update(TVectorIterator first, TVectorIterator last) override
  {
    // TODO SFINAE require this constructor
    this->original.get()->Update(first, last);
    this->size = this->original.get()->Count();
  }
};

#endif
