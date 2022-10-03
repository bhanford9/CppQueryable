#ifndef CPPQUERYABLE_QUERYABLE_SKIPWHILEQUERYABLEDATA_SKIPWHILEQUERYABLEDEQUEDATA_H
#define CPPQUERYABLE_QUERYABLE_SKIPWHILEQUERYABLEDATA_SKIPWHILEQUERYABLEDEQUEDATA_H

#include <iostream>
#include <deque>

#include "../../QueryableType.hpp"
#include "../../Utilities/Condition.hpp"
#include "../../Sorters/DequeSorter.hpp"
#include "SkipWhileQueryableData.hpp"

template<typename TObj, typename TAllocator = std::allocator<TObj>>
class SkipWhileQueryableDequeData : public SkipWhileQueryableData<TObj, std::deque, TObj, TAllocator>
{
public:
  SkipWhileQueryableDequeData(
    std::shared_ptr<IQueryableData<TObj>> && data,
    std::shared_ptr<IWhileCondition<TObj>> && condition)
    : SkipWhileQueryableData<TObj, std::deque, TObj, TAllocator>(std::move(data), std::move(condition))
  {
    // std::cout << "SkipWhileQueryable Deque Data Constructor 0" << std::endl;
  }
  SkipWhileQueryableDequeData(
    std::shared_ptr<QueryableData<TObj, std::deque, TObj, TAllocator>> && data,
    std::shared_ptr<IWhileCondition<TObj>> && condition)
    : SkipWhileQueryableData<TObj, std::deque, TObj, TAllocator>(std::move(data), std::move(condition))
  {
    // std::cout << "SkipWhileQueryable Deque Data Constructor 1" << std::endl;
  }
  SkipWhileQueryableDequeData(
    const std::shared_ptr<QueryableData<TObj, std::deque, TObj, TAllocator>> & data,
    std::shared_ptr<IWhileCondition<TObj>> && condition)
    : SkipWhileQueryableData<TObj, std::deque, TObj, TAllocator>(data, std::move(condition))
  {
    // std::cout << "SkipWhileQueryable Deque Data Constructor 3" << std::endl;
  }
  SkipWhileQueryableDequeData(const SkipWhileQueryableDequeData<TObj, TAllocator> & other)
    : SkipWhileQueryableData<TObj, std::deque, TObj, TAllocator>(other)
  {
    // std::cout << "SkipWhileQueryable Deque Data Constructor 2" << std::endl;
  }

  virtual ~SkipWhileQueryableDequeData() { }

  virtual std::shared_ptr<IQueryableData<TObj>> Clone() override
  {
    return std::make_shared<SkipWhileQueryableDequeData<TObj, TAllocator>>(*this);
  }

  virtual void InternalAdd(TObj item) override
  {
    this->items->push_back(item);
  }

  virtual std::shared_ptr<IQueryableData<TObj>> GetRealizedQueryableData() override
  {
    // If all QueryableData's have a constructor that skips begin, end, Args... then this method can be a one liner
    std::deque<TObj, TAllocator> data(this->items->get_allocator());

    for (const TObj & value : *this)
    {
        data.push_back(value);
    }
    
    return std::make_shared<QueryableDequeData<TObj, TAllocator>>(std::move(data));
  }
};

#endif
