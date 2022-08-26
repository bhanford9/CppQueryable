#ifndef CPPQUERYABLE_QUERYABLE_WHILEQUERYABLEVECTORDATA_H
#define CPPQUERYABLE_QUERYABLE_WHILEQUERYABLEVECTORDATA_H

#include <iostream>
#include <vector>

#include "../../QueryableType.hpp"
#include "../../Utilities/Condition.hpp"
#include "../../Sorters/VectorSorter.hpp"
#include "WhileQueryableData.hpp"

template<typename TObj, typename TAllocator = std::allocator<TObj>>
class WhileQueryableVectorData : public WhileQueryableData<TObj, std::vector, TAllocator>
{
public:
  WhileQueryableVectorData(
    std::shared_ptr<IQueryableData<TObj>> && data,
    std::shared_ptr<IWhileCondition<TObj>> && condition)
    : WhileQueryableData<TObj, std::vector, TAllocator>(std::move(data), std::move(condition))
  {
    // std::cout << "WhileQueryable Vector Data Constructor 0" << std::endl;
  }
  WhileQueryableVectorData(
    std::shared_ptr<QueryableData<TObj, std::vector, TAllocator>> && data,
    std::shared_ptr<IWhileCondition<TObj>> && condition)
    : WhileQueryableData<TObj, std::vector, TAllocator>(std::move(data), std::move(condition))
  {
    // std::cout << "WhileQueryable Vector Data Constructor 1" << std::endl;
  }
  WhileQueryableVectorData(
    const std::shared_ptr<QueryableData<TObj, std::vector, TAllocator>> & data,
    std::shared_ptr<IWhileCondition<TObj>> && condition)
    : WhileQueryableData<TObj, std::vector, TAllocator>(data, std::move(condition))
  {
    // std::cout << "WhileQueryable Vector Data Constructor 3" << std::endl;
  }
  WhileQueryableVectorData(const WhileQueryableVectorData<TObj, TAllocator> & other)
    : WhileQueryableData<TObj, std::vector, TAllocator>(other)
  {
    // std::cout << "WhileQueryable Vector Data Constructor 2" << std::endl;
  }

  virtual ~WhileQueryableVectorData() { }

  virtual std::shared_ptr<IQueryableData<TObj>> Clone() override
  {
    return std::make_shared<WhileQueryableVectorData<TObj, TAllocator>>(*this);
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
