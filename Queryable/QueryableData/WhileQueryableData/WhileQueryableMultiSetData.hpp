#ifndef CPPQUERYABLE_QUERYABLE_WHILEQUERYABLEMULTISETDATA_H
#define CPPQUERYABLE_QUERYABLE_WHILEQUERYABLEMULTISETDATA_H

#include <iostream>
#include <set>

#include "../../Utilities/Condition.hpp"
#include "WhileQueryableData.hpp"

template<
  typename TObj,
  typename TCompare = std::less<TObj>,
  typename TAllocator = std::allocator<TObj>>
class WhileQueryableMultiSetData : public WhileQueryableData<TObj, std::multiset, TCompare, TAllocator>
{
public:
  WhileQueryableMultiSetData(
    std::shared_ptr<IQueryableData<TObj>> data,
    std::shared_ptr<IWhileCondition<TObj>> && condition)
    : WhileQueryableData<TObj, std::multiset, TCompare, TAllocator>(std::move(data), std::move(condition))
  {
  }
  WhileQueryableMultiSetData(
    std::shared_ptr<QueryableData<TObj, std::multiset, TCompare, TAllocator>> && data,
    std::shared_ptr<IWhileCondition<TObj>> && condition)
    : WhileQueryableData<TObj, std::multiset, TCompare, TAllocator>(std::move(data), std::move(condition))
  {
  }
  WhileQueryableMultiSetData(const WhileQueryableMultiSetData<TObj, TCompare, TAllocator> & other)
    : WhileQueryableData<TObj, std::multiset, TCompare, TAllocator>(other)
  {
  }

  virtual ~WhileQueryableMultiSetData() { }

  virtual std::shared_ptr<IQueryableData<TObj>> Clone() override
  {
    return std::make_shared<WhileQueryableMultiSetData<TObj, TCompare, TAllocator>>(*this);
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
