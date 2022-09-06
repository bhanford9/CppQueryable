#ifndef CPPQUERYABLE_QUERYABLE_TAKEWHILEQUERYABLEDATA_TAKEWHILEQUERYABLEDEQUEDATA_H
#define CPPQUERYABLE_QUERYABLE_TAKEWHILEQUERYABLEDATA_TAKEWHILEQUERYABLEDEQUEDATA_H

#include <iostream>
#include <deque>

#include "../../QueryableType.hpp"
#include "../../Utilities/Condition.hpp"
#include "../../Sorters/DequeSorter.hpp"
#include "TakeWhileQueryableData.hpp"

template<typename TObj, typename TAllocator = std::allocator<TObj>>
class TakeWhileQueryableDequeData : public TakeWhileQueryableData<TObj, std::deque, TAllocator>
{
public:
  TakeWhileQueryableDequeData(
    std::shared_ptr<IQueryableData<TObj>> && data,
    std::shared_ptr<IWhileCondition<TObj>> && condition)
    : TakeWhileQueryableData<TObj, std::deque, TAllocator>(std::move(data), std::move(condition))
  {
    // std::cout << "TakeWhileQueryable Deque Data Constructor 0" << std::endl;
  }
  TakeWhileQueryableDequeData(
    std::shared_ptr<QueryableData<TObj, std::deque, TAllocator>> && data,
    std::shared_ptr<IWhileCondition<TObj>> && condition)
    : TakeWhileQueryableData<TObj, std::deque, TAllocator>(std::move(data), std::move(condition))
  {
    // std::cout << "TakeWhileQueryable Deque Data Constructor 1" << std::endl;
  }
  TakeWhileQueryableDequeData(
    const std::shared_ptr<QueryableData<TObj, std::deque, TAllocator>> & data,
    std::shared_ptr<IWhileCondition<TObj>> && condition)
    : TakeWhileQueryableData<TObj, std::deque, TAllocator>(data, std::move(condition))
  {
    // std::cout << "TakeWhileQueryable Deque Data Constructor 3" << std::endl;
  }
  TakeWhileQueryableDequeData(const TakeWhileQueryableDequeData<TObj, TAllocator> & other)
    : TakeWhileQueryableData<TObj, std::deque, TAllocator>(other)
  {
    // std::cout << "TakeWhileQueryable Deque Data Constructor 2" << std::endl;
  }

  virtual ~TakeWhileQueryableDequeData() { }

  virtual std::shared_ptr<IQueryableData<TObj>> Clone() override
  {
    return std::make_shared<TakeWhileQueryableDequeData<TObj, TAllocator>>(*this);
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