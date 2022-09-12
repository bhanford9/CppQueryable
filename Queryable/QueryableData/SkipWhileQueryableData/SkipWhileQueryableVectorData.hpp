#ifndef CPPQUERYABLE_QUERYABLE_SKIPWHILEQUERYABLEDATA_SKIPWHILEQUERYABLEVECTORDATA_H
#define CPPQUERYABLE_QUERYABLE_SKIPWHILEQUERYABLEDATA_SKIPWHILEQUERYABLEVECTORDATA_H

#include <iostream>
#include <vector>

#include "../../QueryableType.hpp"
#include "../../Utilities/Condition.hpp"
#include "../../Sorters/VectorSorter.hpp"
#include "SkipWhileQueryableData.hpp"

template<typename TObj, typename TAllocator = std::allocator<TObj>>
class SkipWhileQueryableVectorData : public SkipWhileQueryableData<TObj, std::vector, TAllocator>
{
public:
  SkipWhileQueryableVectorData(
    std::shared_ptr<IQueryableData<TObj>> && data,
    std::shared_ptr<IWhileCondition<TObj>> && condition)
    : SkipWhileQueryableData<TObj, std::vector, TAllocator>(std::move(data), std::move(condition))
  {
    // std::cout << "SkipWhileQueryable Vector Data Constructor 0" << std::endl;
  }
  SkipWhileQueryableVectorData(
    std::shared_ptr<QueryableData<TObj, std::vector, TAllocator>> && data,
    std::shared_ptr<IWhileCondition<TObj>> && condition)
    : SkipWhileQueryableData<TObj, std::vector, TAllocator>(std::move(data), std::move(condition))
  {
    // std::cout << "SkipWhileQueryable Vector Data Constructor 1" << std::endl;
  }
  SkipWhileQueryableVectorData(
    const std::shared_ptr<QueryableData<TObj, std::vector, TAllocator>> & data,
    std::shared_ptr<IWhileCondition<TObj>> && condition)
    : SkipWhileQueryableData<TObj, std::vector, TAllocator>(data, std::move(condition))
  {
    // std::cout << "SkipWhileQueryable Vector Data Constructor 3" << std::endl;
  }
  SkipWhileQueryableVectorData(const SkipWhileQueryableVectorData<TObj, TAllocator> & other)
    : SkipWhileQueryableData<TObj, std::vector, TAllocator>(other)
  {
    // std::cout << "SkipWhileQueryable Vector Data Constructor 2" << std::endl;
  }

  virtual ~SkipWhileQueryableVectorData() { }

  virtual std::shared_ptr<IQueryableData<TObj>> Clone() override
  {
    return std::make_shared<SkipWhileQueryableVectorData<TObj, TAllocator>>(*this);
  }

  virtual void InternalAdd(TObj item) override
  {
    this->items->push_back(item);
  }

  virtual std::shared_ptr<IQueryableData<TObj>> GetRealizedQueryableData() override
  {
    // If all QueryableData's have a constructor that skips begin, end, Args... then this method can be a one liner
    std::vector<TObj, TAllocator> data(this->items->get_allocator());

    for (const TObj & value : *this)
    {
        data.push_back(value);
    }
    
    return std::make_shared<QueryableVectorData<TObj, TAllocator>>(std::move(data));
  }
};

#endif
