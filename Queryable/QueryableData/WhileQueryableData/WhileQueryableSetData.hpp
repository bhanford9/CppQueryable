#ifndef CPPQUERYABLE_QUERYABLE_WHILEQUERYABLESETDATA_H
#define CPPQUERYABLE_QUERYABLE_WHILEQUERYABLESETDATA_H

#include <iostream>
#include <set>

#include "../../Utilities/Condition.hpp"
#include "WhileQueryableData.hpp"

template<
  typename TObj,
  typename TCompare = std::less<TObj>,
  typename TAllocator = std::allocator<TObj>>
class WhileQueryableSetData : public WhileQueryableData<TObj, std::set, TCompare, TAllocator>
{
public:
  WhileQueryableSetData(
    std::shared_ptr<IQueryableData<TObj>> data,
    std::shared_ptr<IWhileCondition<TObj>> && condition)
    : WhileQueryableData<TObj, std::set, TCompare, TAllocator>(std::move(data), std::move(condition))
  {
  }
  WhileQueryableSetData(
    std::shared_ptr<QueryableData<TObj, std::set, TCompare, TAllocator>> && data,
    std::shared_ptr<IWhileCondition<TObj>> && condition)
    : WhileQueryableData<TObj, std::set, TCompare, TAllocator>(std::move(data), std::move(condition))
  {
  }
  WhileQueryableSetData(const WhileQueryableSetData<TObj, TCompare, TAllocator> & other)
    : WhileQueryableData<TObj, std::set, TCompare, TAllocator>(other)
  {
  }

  virtual ~WhileQueryableSetData() { }

  virtual std::shared_ptr<IQueryableData<TObj>> Clone() override
  {
    return std::make_shared<WhileQueryableSetData<TObj, TCompare, TAllocator>>(*this);
  }

  virtual void InternalAdd(TObj item) override
  {
    this->items->insert(item);
  }

  virtual std::shared_ptr<IQueryableData<TObj>> GetRealizedQueryableData() override
  {
    // If all QueryableData's have a constructor that takes begin, end, Args... then this method can be a one liner

    std::set<TObj, TCompare, TAllocator> data(this->items->value_comp(), this->items->get_allocator());

    for (const TObj & value : *this)
    {
        data.insert(value);
    }

    return std::make_shared<QueryableSetData<TObj, TCompare, TAllocator>>(std::move(data));
  }
};

#endif
