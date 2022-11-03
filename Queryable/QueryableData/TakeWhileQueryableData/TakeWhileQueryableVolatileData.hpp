#ifndef CPPQUERYABLE_QUERYABLE_TAKEWHILEQUERYABLEDATA_TAKEWHILEQUERYABLEVOLATILEDATA_H
#define CPPQUERYABLE_QUERYABLE_TAKEWHILEQUERYABLEDATA_TAKEWHILEQUERYABLEVOLATILEDATA_H

#include <vector>

#include "TakeWhileQueryableData.hpp"
#include "../VolatileQueryableData.hpp"

template<typename TObj, typename TAllocator = std::allocator<TObj>>
class TakeWhileQueryableVolatileData : public TakeWhileQueryableData<TObj, std::vector, TObj, TAllocator>
{
public:
  TakeWhileQueryableVolatileData(const TakeWhileQueryableVolatileData & other)
    : TakeWhileQueryableData<TObj, std::vector, TObj, TAllocator>(other)
  {
  }

  TakeWhileQueryableVolatileData(TakeWhileQueryableVolatileData && other) noexcept
    : TakeWhileQueryableData<TObj, std::vector, TObj, TAllocator>(std::move(other))
  {
  }

  TakeWhileQueryableVolatileData(
    std::shared_ptr<IQueryableData<TObj>> && data,
    std::shared_ptr<IWhileCondition<TObj>> && condition)
    : TakeWhileQueryableData<TObj, std::vector, TObj, TAllocator>(std::move(data), std::move(condition))
  {
    // std::cout << "TakeWhileQueryable Volatile Data Constructor 0" << std::endl;
  }
  TakeWhileQueryableVolatileData(
    std::shared_ptr<QueryableData<TObj, std::vector, TObj, TAllocator>> && data,
    std::shared_ptr<IWhileCondition<TObj>> && condition)
    : TakeWhileQueryableData<TObj, std::vector, TObj, TAllocator>(std::move(data), std::move(condition))
  {
    // std::cout << "TakeWhileQueryable Volatile Data Constructor 1" << std::endl;
  }
  TakeWhileQueryableVolatileData(
    const std::shared_ptr<QueryableData<TObj, std::vector, TObj, TAllocator>> & data,
    std::shared_ptr<IWhileCondition<TObj>> && condition)
    : TakeWhileQueryableData<TObj, std::vector, TObj, TAllocator>(data, std::move(condition))
  {
    // std::cout << "TakeWhileQueryable Volatile Data Constructor 3" << std::endl;
  }

  TakeWhileQueryableVolatileData & operator=(const TakeWhileQueryableVolatileData & other)
  {
    if (this == &other) return *this;
    TakeWhileQueryableData<TObj, std::vector, TObj, TAllocator>::operator =(other);
    return *this;
  }

  TakeWhileQueryableVolatileData & operator=(TakeWhileQueryableVolatileData && other) noexcept
  {
    if (this == &other) return *this;
    TakeWhileQueryableData<TObj, std::vector, TObj, TAllocator>::operator =(std::move(other));
    return *this;
  }

  virtual ~TakeWhileQueryableVolatileData() override = default;

  virtual std::shared_ptr<IQueryableData<TObj>> Clone() override
  {
    return std::make_shared<TakeWhileQueryableVolatileData<TObj, TAllocator>>(*this);
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
    
    return std::make_shared<VolatileQueryableData<TObj, std::vector, TObj, TAllocator>>(std::move(data));
  }
};

#endif
