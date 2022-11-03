#ifndef CPPQUERYABLE_QUERYABLE_TAKEWHILEQUERYABLEDATA_TAKEWHILEQUERYABLEVECTORDATA_H
#define CPPQUERYABLE_QUERYABLE_TAKEWHILEQUERYABLEDATA_TAKEWHILEQUERYABLEVECTORDATA_H

#include <vector>

#include "TakeWhileQueryableData.hpp"

template<typename TObj, typename TAllocator = std::allocator<TObj>>
class TakeWhileQueryableVectorData : public TakeWhileQueryableData<TObj, std::vector, TObj, TAllocator>
{
public:
  TakeWhileQueryableVectorData(const TakeWhileQueryableVectorData & other)
    : TakeWhileQueryableData<TObj, std::vector, TObj, TAllocator>(other)
  {
  }

  TakeWhileQueryableVectorData(TakeWhileQueryableVectorData && other) noexcept
    : TakeWhileQueryableData<TObj, std::vector, TObj, TAllocator>(std::move(other))
  {
  }

  TakeWhileQueryableVectorData(
    std::shared_ptr<IQueryableData<TObj>> && data,
    std::shared_ptr<IWhileCondition<TObj>> && condition)
    : TakeWhileQueryableData<TObj, std::vector, TObj, TAllocator>(std::move(data), std::move(condition))
  {
    // std::cout << "TakeWhileQueryable Vector Data Constructor 0" << std::endl;
  }
  TakeWhileQueryableVectorData(
    std::shared_ptr<QueryableData<TObj, std::vector, TObj, TAllocator>> && data,
    std::shared_ptr<IWhileCondition<TObj>> && condition)
    : TakeWhileQueryableData<TObj, std::vector, TObj, TAllocator>(std::move(data), std::move(condition))
  {
    // std::cout << "TakeWhileQueryable Vector Data Constructor 1" << std::endl;
  }
  TakeWhileQueryableVectorData(
    const std::shared_ptr<QueryableData<TObj, std::vector, TObj, TAllocator>> & data,
    std::shared_ptr<IWhileCondition<TObj>> && condition)
    : TakeWhileQueryableData<TObj, std::vector, TObj, TAllocator>(data, std::move(condition))
  {
    // std::cout << "TakeWhileQueryable Vector Data Constructor 3" << std::endl;
  }

  TakeWhileQueryableVectorData & operator=(const TakeWhileQueryableVectorData & other)
  {
    if (this == &other) return *this;
    TakeWhileQueryableData<TObj, std::vector, TObj, TAllocator>::operator =(other);
    return *this;
  }

  TakeWhileQueryableVectorData & operator=(TakeWhileQueryableVectorData && other) noexcept
  {
    if (this == &other) return *this;
    TakeWhileQueryableData<TObj, std::vector, TObj, TAllocator>::operator =(std::move(other));
    return *this;
  }

  virtual ~TakeWhileQueryableVectorData() override = default;

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
