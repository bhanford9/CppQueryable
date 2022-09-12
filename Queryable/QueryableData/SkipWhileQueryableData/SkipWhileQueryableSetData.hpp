#ifndef CPPQUERYABLE_QUERYABLE_SKIPWHILEQUERYABLEDATA_SKIPWHILEQUERYABLESETDATA_H
#define CPPQUERYABLE_QUERYABLE_SKIPWHILEQUERYABLEDATA_SKIPWHILEQUERYABLESETDATA_H

#include <iostream>
#include <set>

#include "../../Utilities/Condition.hpp"
#include "SkipWhileQueryableData.hpp"

template<
  typename TObj,
  typename TCompare = std::less<TObj>,
  typename TAllocator = std::allocator<TObj>>
class SkipWhileQueryableSetData : public SkipWhileQueryableData<TObj, std::set, TCompare, TAllocator>
{
public:
  SkipWhileQueryableSetData(
    std::shared_ptr<IQueryableData<TObj>> data,
    std::shared_ptr<IWhileCondition<TObj>> && condition)
    : SkipWhileQueryableData<TObj, std::set, TCompare, TAllocator>(std::move(data), std::move(condition))
  {
  }
  SkipWhileQueryableSetData(
    std::shared_ptr<QueryableData<TObj, std::set, TCompare, TAllocator>> && data,
    std::shared_ptr<IWhileCondition<TObj>> && condition)
    : SkipWhileQueryableData<TObj, std::set, TCompare, TAllocator>(std::move(data), std::move(condition))
  {
  }
  SkipWhileQueryableSetData(const SkipWhileQueryableSetData<TObj, TCompare, TAllocator> & other)
    : SkipWhileQueryableData<TObj, std::set, TCompare, TAllocator>(other)
  {
  }

  virtual ~SkipWhileQueryableSetData() { }

  virtual std::shared_ptr<IQueryableData<TObj>> Clone() override
  {
    return std::make_shared<SkipWhileQueryableSetData<TObj, TCompare, TAllocator>>(*this);
  }

  virtual void InternalAdd(TObj item) override
  {
    this->items->insert(item);
  }

  virtual std::shared_ptr<IQueryableData<TObj>> GetRealizedQueryableData() override
  {
    // If all QueryableData's have a constructor that skips begin, end, Args... then this method can be a one liner

    std::set<TObj, TCompare, TAllocator> data(this->items->value_comp(), this->items->get_allocator());

    for (const TObj & value : *this)
    {
        data.insert(value);
    }

    return std::make_shared<QueryableSetData<TObj, TCompare, TAllocator>>(std::move(data));
  }
};

#endif
