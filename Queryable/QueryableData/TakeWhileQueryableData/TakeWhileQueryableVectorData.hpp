#ifndef CPPQUERYABLE_QUERYABLE_TAKEWHILEQUERYABLEVECTORDATA_H
#define CPPQUERYABLE_QUERYABLE_TAKEWHILEQUERYABLEVECTORDATA_H

#include <iostream>
#include <vector>

#include "../../QueryableType.hpp"
#include "../../Utilities/Condition.hpp"
#include "../../Sorters/VectorSorter.hpp"
#include "TakeWhileQueryableData.hpp"

template<typename TObj, typename TAllocator = std::allocator<TObj>>
class TakeWhileQueryableVectorData : public TakeWhileQueryableData<TObj, std::vector, TAllocator>
{
public:
  TakeWhileQueryableVectorData(
    std::shared_ptr<IQueryableData<TObj>> && data,
    std::shared_ptr<IWhileCondition<TObj>> && condition)
    : TakeWhileQueryableData<TObj, std::vector, TAllocator>(std::move(data), std::move(condition))
  {
    // std::cout << "TakeWhileQueryable Vector Data Constructor 0" << std::endl;
  }
  TakeWhileQueryableVectorData(
    std::shared_ptr<QueryableData<TObj, std::vector, TAllocator>> && data,
    std::shared_ptr<IWhileCondition<TObj>> && condition)
    : TakeWhileQueryableData<TObj, std::vector, TAllocator>(std::move(data), std::move(condition))
  {
    // std::cout << "TakeWhileQueryable Vector Data Constructor 1" << std::endl;
  }
  TakeWhileQueryableVectorData(
    const std::shared_ptr<QueryableData<TObj, std::vector, TAllocator>> & data,
    std::shared_ptr<IWhileCondition<TObj>> && condition)
    : TakeWhileQueryableData<TObj, std::vector, TAllocator>(data, std::move(condition))
  {
    // std::cout << "TakeWhileQueryable Vector Data Constructor 3" << std::endl;
  }
  TakeWhileQueryableVectorData(const TakeWhileQueryableVectorData<TObj, TAllocator> & other)
    : TakeWhileQueryableData<TObj, std::vector, TAllocator>(other)
  {
    // std::cout << "TakeWhileQueryable Vector Data Constructor 2" << std::endl;
  }

  virtual ~TakeWhileQueryableVectorData() { }

  virtual std::shared_ptr<IQueryableData<TObj>> Clone() override
  {
    return std::make_shared<TakeWhileQueryableVectorData<TObj, TAllocator>>(*this);
  }

  virtual void InternalAdd(TObj item) override
  {
    this->items->push_back(item);
  }

  virtual std::shared_ptr<IQueryableData<TObj>> GetRealizedQueryableData() override
  {
    // If all QueryableData's have a constructor that takes begin, end, Args... then this method can be a one liner
    std::vector<TObj, TAllocator> data(this->items->get_allocator());

    for (const TObj & value : *this)
    {
        data.push_back(value);
    }
    
    return std::make_shared<QueryableVectorData<TObj, TAllocator>>(std::move(data));
  }
};

#endif
