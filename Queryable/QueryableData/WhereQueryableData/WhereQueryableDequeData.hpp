#ifndef CPPQUERYABLE_QUERYABLE_WHEREQUERYABLEDEQUEDATA_H
#define CPPQUERYABLE_QUERYABLE_WHEREQUERYABLEDEQUEDATA_H

#include <iostream>
#include <deque>

#include "../../QueryableType.hpp"
#include "../../Utilities/Condition.hpp"
#include "../../Sorters/DequeSorter.hpp"
#include "WhereQueryableData.hpp"

template<typename TObj, typename TAllocator = std::allocator<TObj>>
class WhereQueryableDequeData : public WhereQueryableData<TObj, std::deque, TAllocator>
{
public:
  WhereQueryableDequeData(
    std::shared_ptr<IQueryableData<TObj>> data,
    std::function<bool(TObj)> condition)
    : WhereQueryableData<TObj, std::deque, TAllocator>(std::move(data), std::move(condition))
  {
  }
  WhereQueryableDequeData(
    std::shared_ptr<QueryableData<TObj, std::deque, TAllocator>> && data,
    std::function<bool(TObj)> condition)
    : WhereQueryableData<TObj, std::deque, TAllocator>(std::move(data), std::move(condition))
  {
  }
  WhereQueryableDequeData(const WhereQueryableDequeData<TObj, TAllocator> & other)
    : WhereQueryableData<TObj, std::deque, TAllocator>(other)
  {
  }

  virtual ~WhereQueryableDequeData() { }

  virtual std::shared_ptr<IQueryableData<TObj>> Clone() override
  {
    return std::make_shared<WhereQueryableDequeData<TObj, TAllocator>>(*this);
  }

  virtual void InternalAdd(TObj item) override
  {
    this->items->push_back(item);
  }

  virtual std::shared_ptr<IQueryableData<TObj>> GetRealizedQueryableData() override
  {
    // If all QueryableData's have a constructor that takes begin, end, Args... then this method can be a one liner
    std::deque<TObj, TAllocator> data(this->items->get_allocator());

    for (const TObj & value : *this)
    {
        data.push_back(value);
    }

    return std::make_shared<QueryableDequeData<TObj, TAllocator>>(std::move(data));
  }
};

#endif
