#ifndef CPPQUERYABLE_QUERYABLE_WHEREQUERYABLESETDATA_H
#define CPPQUERYABLE_QUERYABLE_WHEREQUERYABLESETDATA_H

#include <iostream>
#include <set>

#include "../../Utilities/Condition.hpp"
#include "WhereQueryableData.hpp"

template<
  typename TObj,
  typename TCompare = std::less<TObj>,
  typename TAllocator = std::allocator<TObj>>
class WhereQueryableSetData : public WhereQueryableData<TObj, std::set, TObj, TCompare, TAllocator>
{
public:
  WhereQueryableSetData(
    std::shared_ptr<IQueryableData<TObj>> data,
    std::function<bool(TObj)> condition)
    : WhereQueryableData<TObj, std::set, TObj, TCompare, TAllocator>(std::move(data), std::move(condition))
  {
  }
  WhereQueryableSetData(
    std::shared_ptr<QueryableData<TObj, std::set, TObj, TCompare, TAllocator>> && data,
    std::function<bool(TObj)> condition)
    : WhereQueryableData<TObj, std::set, TObj, TCompare, TAllocator>(std::move(data), std::move(condition))
  {
  }
  WhereQueryableSetData(const WhereQueryableSetData<TObj, TCompare, TAllocator> & other)
    : WhereQueryableData<TObj, std::set, TObj, TCompare, TAllocator>(other)
  {
  }

  virtual ~WhereQueryableSetData() { }

  virtual std::shared_ptr<IQueryableData<TObj>> Clone() override
  {
    return std::make_shared<WhereQueryableSetData<TObj, TCompare, TAllocator>>(*this);
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
