#ifndef CPPQUERYABLE_QUERYABLE_SKIPWHILEQUERYABLEDATA_SKIPWHILEQUERYABLEVECTORDATA_H
#define CPPQUERYABLE_QUERYABLE_SKIPWHILEQUERYABLEDATA_SKIPWHILEQUERYABLEVECTORDATA_H

#include <vector>

#include "SkipWhileQueryableData.hpp"

template<typename TObj, typename TAllocator = std::allocator<TObj>>
class SkipWhileQueryableVectorData final : public SkipWhileQueryableData<TObj, std::vector, TObj, TAllocator>
{
public:
  SkipWhileQueryableVectorData(const SkipWhileQueryableVectorData & other)
    : SkipWhileQueryableData<TObj, std::vector, TObj, TAllocator>(other)
  {
  }

  SkipWhileQueryableVectorData(SkipWhileQueryableVectorData && other) noexcept
    : SkipWhileQueryableData<TObj, std::vector, TObj, TAllocator>(std::move(other))
  {
  }

  SkipWhileQueryableVectorData(
    std::shared_ptr<IQueryableData<TObj>> && data,
    std::shared_ptr<IWhileCondition<TObj>> && condition)
    : SkipWhileQueryableData<TObj, std::vector, TObj, TAllocator>(std::move(data), std::move(condition))
  {
    // std::cout << "SkipWhileQueryable Vector Data Constructor 0" << std::endl;
  }
  SkipWhileQueryableVectorData(
    std::shared_ptr<QueryableData<TObj, std::vector, TObj, TAllocator>> && data,
    std::shared_ptr<IWhileCondition<TObj>> && condition)
    : SkipWhileQueryableData<TObj, std::vector, TObj, TAllocator>(std::move(data), std::move(condition))
  {
    // std::cout << "SkipWhileQueryable Vector Data Constructor 1" << std::endl;
  }
  SkipWhileQueryableVectorData(
    const std::shared_ptr<QueryableData<TObj, std::vector, TObj, TAllocator>> & data,
    std::shared_ptr<IWhileCondition<TObj>> && condition)
    : SkipWhileQueryableData<TObj, std::vector, TObj, TAllocator>(data, std::move(condition))
  {
    // std::cout << "SkipWhileQueryable Vector Data Constructor 3" << std::endl;
  }

  SkipWhileQueryableVectorData & operator=(const SkipWhileQueryableVectorData & other)
  {
    if (this == &other) return *this;
    SkipWhileQueryableData<TObj, std::vector, TObj, TAllocator>::operator =(other);
    return *this;
  }

  SkipWhileQueryableVectorData & operator=(SkipWhileQueryableVectorData && other) noexcept
  {
    if (this == &other) return *this;
    SkipWhileQueryableData<TObj, std::vector, TObj, TAllocator>::operator =(std::move(other));
    return *this;
  }

  virtual ~SkipWhileQueryableVectorData() override = default;

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
