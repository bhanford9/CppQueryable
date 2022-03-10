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

#include "../../TypeConstraintUtil.hpp"
#include "../../Utilities/Condition.hpp"
#include "../IQueryableData.hpp"
#include "../QueryableData.hpp"

template<
  typename TOriginal,
  typename TCurrent,
  template<typename, typename ...> typename TIterable,
  typename TCompare = std::less<TCurrent>, // TODO: can be used for sort (might need to pass this into parent, not sure how this works)
  typename ...TArgs>
class SelectQueryableData : public QueryableData<TOriginal, TCurrent, TIterable, TArgs...>
{
  // static_assert(can_iterate<TIterable<TOriginal, TArgs...>>::value, "Class must be able to be iterated over");
protected:
  std::function<TCurrent&(TOriginal) const> selector;
public:

  SelectQueryableData(
    std::shared_ptr<IQueryableData<TOriginal, TCurrent>> data,
    std::function<TCurrent&(TOriginal) const> selector)
    : QueryableData<TOriginal, TCurrent, TIterable, TArgs...>(std::move(data))
  {
    this->selector = selector;
  }

  SelectQueryableData(const SelectQueryableData<TOriginal, TCurrent, TIterable, TArgs...> & data)
    : QueryableData<TOriginal, TCurrent, TIterable, TArgs...>(data)
  {
  }

  virtual ~SelectQueryableData() { }

  inline virtual TCurrent & ToOutput(const TOriginal & original) const
  {
    return this->selector(original);
  }

  inline virtual const TCurrent & ToOutputConst(const TOriginal & original) const override
  {
    return this->selector(original);
  }

  inline virtual TCurrent & Get(IteratorType type) override
  {
    switch (type)
    {
      case IteratorType::BeginForward: return this->selector(*this->beginIterator);
      case IteratorType::EndForward: return this->selector(*this->endIterator);
      case IteratorType::BeginReverse: return this->selector(*this->rbeginIterator);
      case IteratorType::EndReverse: default: return this->selector(*this->rendIterator);
    }
  }

  inline virtual const TCurrent & ConstGet(IteratorType type) override
  {
    switch (type)
    {
      case IteratorType::BeginForward: return this->selector(*this->beginIterator);
      case IteratorType::EndForward: return this->selector(*this->endIterator);
      case IteratorType::BeginReverse: return this->selector(*this->rbeginIterator);
      case IteratorType::EndReverse: default: return this->selector(*this->rendIterator);
    }
  }

  // if we ever want to return true here, will need to change signature to take
  // a TCurrent instead of a TOriginal. Its faster in the iterator incrementing
  // if we do not have to convert from TOriginal to TCurrent though
  // virtual bool DoSkip(const TOriginal & value) override
  // {
  //   return false;
  // }
  //
  // virtual bool CanSkip() override
  // {
  //   return false;
  // }
};

#endif
