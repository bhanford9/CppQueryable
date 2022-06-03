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
class WhereQueryableSetData : public WhereQueryableData<TObj, std::set, TCompare, TAllocator>
{
public:
  WhereQueryableSetData(
    std::shared_ptr<IQueryableData<TObj>> data,
    std::function<bool(TObj)> condition)
    : WhereQueryableData<TObj, std::set, TCompare, TAllocator>(std::move(data), std::move(condition))
  {
  }
  WhereQueryableSetData(
    std::shared_ptr<QueryableData<TObj, std::set, TCompare, TAllocator>> && data,
    std::function<bool(TObj)> condition)
    : WhereQueryableData<TObj, std::set, TCompare, TAllocator>(std::move(data), std::move(condition))
  {
  }
  WhereQueryableSetData(const WhereQueryableSetData<TObj, TCompare, TAllocator> & other)
    : WhereQueryableData<TObj, std::set, TCompare, TAllocator>(other)
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
};

#endif
