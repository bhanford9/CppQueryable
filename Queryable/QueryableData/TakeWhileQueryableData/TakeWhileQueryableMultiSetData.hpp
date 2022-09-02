#ifndef CPPQUERYABLE_QUERYABLE_TAKEWHILEQUERYABLEMULTISETDATA_H
#define CPPQUERYABLE_QUERYABLE_TAKEWHILEQUERYABLEMULTISETDATA_H

#include <iostream>
#include <set>

#include "../../Utilities/Condition.hpp"
#include "TakeWhileQueryableData.hpp"

template<
  typename TObj,
  typename TCompare = std::less<TObj>,
  typename TAllocator = std::allocator<TObj>>
class TakeWhileQueryableMultiSetData : public TakeWhileQueryableData<TObj, std::multiset, TCompare, TAllocator>
{
public:
  TakeWhileQueryableMultiSetData(
    std::shared_ptr<IQueryableData<TObj>> data,
    std::shared_ptr<IWhileCondition<TObj>> && condition)
    : TakeWhileQueryableData<TObj, std::multiset, TCompare, TAllocator>(std::move(data), std::move(condition))
  {
  }
  TakeWhileQueryableMultiSetData(
    std::shared_ptr<QueryableData<TObj, std::multiset, TCompare, TAllocator>> && data,
    std::shared_ptr<IWhileCondition<TObj>> && condition)
    : TakeWhileQueryableData<TObj, std::multiset, TCompare, TAllocator>(std::move(data), std::move(condition))
  {
  }
  TakeWhileQueryableMultiSetData(const TakeWhileQueryableMultiSetData<TObj, TCompare, TAllocator> & other)
    : TakeWhileQueryableData<TObj, std::multiset, TCompare, TAllocator>(other)
  {
  }

  virtual ~TakeWhileQueryableMultiSetData() { }

  virtual std::shared_ptr<IQueryableData<TObj>> Clone() override
  {
    return std::make_shared<TakeWhileQueryableMultiSetData<TObj, TCompare, TAllocator>>(*this);
  }

  virtual void InternalAdd(TObj item) override
  {
    this->items->insert(item);
  }

  virtual std::shared_ptr<IQueryableData<TObj>> GetRealizedQueryableData() override
  {
    // If all QueryableData's have a constructor that takes begin, end, Args... then this method can be a one liner

    std::multiset<TObj, TCompare, TAllocator> data(this->items->value_comp(), this->items->get_allocator());

    for (const TObj & value : *this)
    {
        data.insert(value);
    }

    return std::make_shared<QueryableMultiSetData<TObj, TCompare, TAllocator>>(std::move(data));
  }
};

#endif
