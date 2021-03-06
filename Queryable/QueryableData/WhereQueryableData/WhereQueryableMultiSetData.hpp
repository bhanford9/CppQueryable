#ifndef CPPQUERYABLE_QUERYABLE_WHEREQUERYABLEMULTISETDATA_H
#define CPPQUERYABLE_QUERYABLE_WHEREQUERYABLEMULTISETDATA_H

#include <iostream>
#include <set>

#include "../../Utilities/Condition.hpp"
#include "WhereQueryableData.hpp"

template<
  typename TObj,
  typename TCompare = std::less<TObj>,
  typename TAllocator = std::allocator<TObj>>
class WhereQueryableMultiSetData : public WhereQueryableData<TObj, std::multiset, TCompare, TAllocator>
{
public:
  WhereQueryableMultiSetData(
    std::shared_ptr<IQueryableData<TObj>> data,
    std::function<bool(TObj)> condition)
    : WhereQueryableData<TObj, std::multiset, TCompare, TAllocator>(std::move(data), std::move(condition))
  {
  }
  WhereQueryableMultiSetData(
    std::shared_ptr<QueryableData<TObj, std::multiset, TCompare, TAllocator>> && data,
    std::function<bool(TObj)> condition)
    : WhereQueryableData<TObj, std::multiset, TCompare, TAllocator>(std::move(data), std::move(condition))
  {
  }
  WhereQueryableMultiSetData(const WhereQueryableMultiSetData<TObj, TCompare, TAllocator> & other)
    : WhereQueryableData<TObj, std::multiset, TCompare, TAllocator>(other)
  {
  }

  virtual ~WhereQueryableMultiSetData() { }

  virtual std::shared_ptr<IQueryableData<TObj>> Clone() override
  {
    return std::make_shared<WhereQueryableMultiSetData<TObj, TCompare, TAllocator>>(*this);
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
