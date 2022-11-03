#ifndef CPPQUERYABLE_QUERYABLE_SKIPWHILEQUERYABLEDATA_SKIPWHILEQUERYABLEVOLATILEDATA_H
#define CPPQUERYABLE_QUERYABLE_SKIPWHILEQUERYABLEDATA_SKIPWHILEQUERYABLEVOLATILEDATA_H

#include <vector>

#include "SkipWhileQueryableData.hpp"
#include "../VolatileQueryableData.hpp"

template<typename TObj, typename TAllocator = std::allocator<TObj>>
class SkipWhileQueryableVolatileData final : public SkipWhileQueryableData<TObj, std::vector, TObj, TAllocator>
{
public:
  SkipWhileQueryableVolatileData(const SkipWhileQueryableVolatileData & other)
    : SkipWhileQueryableData<TObj, std::vector, TObj, TAllocator>(other)
  {
  }

  SkipWhileQueryableVolatileData(SkipWhileQueryableVolatileData && other) noexcept
    : SkipWhileQueryableData<TObj, std::vector, TObj, TAllocator>(std::move(other))
  {
  }

  SkipWhileQueryableVolatileData(
    std::shared_ptr<IQueryableData<TObj>> && data,
    std::shared_ptr<IWhileCondition<TObj>> && condition)
    : SkipWhileQueryableData<TObj, std::vector, TObj, TAllocator>(std::move(data), std::move(condition))
  {
    // std::cout << "SkipWhileQueryable Volatile Data Constructor 0" << std::endl;
  }
  SkipWhileQueryableVolatileData(
    std::shared_ptr<QueryableData<TObj, std::vector, TObj, TAllocator>> && data,
    std::shared_ptr<IWhileCondition<TObj>> && condition)
    : SkipWhileQueryableData<TObj, std::vector, TObj, TAllocator>(std::move(data), std::move(condition))
  {
    // std::cout << "SkipWhileQueryable Volatile Data Constructor 1" << std::endl;
  }
  SkipWhileQueryableVolatileData(
    const std::shared_ptr<QueryableData<TObj, std::vector, TObj, TAllocator>> & data,
    std::shared_ptr<IWhileCondition<TObj>> && condition)
    : SkipWhileQueryableData<TObj, std::vector, TObj, TAllocator>(data, std::move(condition))
  {
    // std::cout << "SkipWhileQueryable Volatile Data Constructor 3" << std::endl;
  }

  SkipWhileQueryableVolatileData & operator=(const SkipWhileQueryableVolatileData & other)
  {
    if (this == &other) return *this;
    SkipWhileQueryableData<TObj, std::vector, TObj, TAllocator>::operator =(other);
    return *this;
  }

  SkipWhileQueryableVolatileData & operator=(SkipWhileQueryableVolatileData && other) noexcept
  {
    if (this == &other) return *this;
    SkipWhileQueryableData<TObj, std::vector, TObj, TAllocator>::operator =(std::move(other));
    return *this;
  }

  virtual ~SkipWhileQueryableVolatileData() override = default;

  virtual std::shared_ptr<IQueryableData<TObj>> Clone() override
  {
    return std::make_shared<SkipWhileQueryableVolatileData<TObj, TAllocator>>(*this);
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
    
    return std::make_shared<VolatileQueryableData<TObj, std::vector, TObj, TAllocator>>(std::move(data));
  }
};

#endif
