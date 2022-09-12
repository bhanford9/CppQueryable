#ifndef CPPQUERYABLE_QUERYABLE_SKIPWHILEQUERYABLEDATA_SKIPWHILEQUERYABLELISTDATA_H
#define CPPQUERYABLE_QUERYABLE_SKIPWHILEQUERYABLEDATA_SKIPWHILEQUERYABLELISTDATA_H

#include <iostream>
#include <list>

#include "../../QueryableType.hpp"
#include "../../Utilities/Condition.hpp"
#include "../../Sorters/ListSorter.hpp"
#include "SkipWhileQueryableData.hpp"

template<typename TObj, typename TAllocator = std::allocator<TObj>>
class SkipWhileQueryableListData : public SkipWhileQueryableData<TObj, std::list, TAllocator>
{
public:
  SkipWhileQueryableListData(
    std::shared_ptr<IQueryableData<TObj>> && data,
    std::shared_ptr<IWhileCondition<TObj>> && condition)
    : SkipWhileQueryableData<TObj, std::list, TAllocator>(std::move(data), std::move(condition))
  {
    // std::cout << "SkipWhileQueryable List Data Constructor 0" << std::endl;
  }
  SkipWhileQueryableListData(
    std::shared_ptr<QueryableData<TObj, std::list, TAllocator>> && data,
    std::shared_ptr<IWhileCondition<TObj>> && condition)
    : SkipWhileQueryableData<TObj, std::list, TAllocator>(std::move(data), std::move(condition))
  {
    // std::cout << "SkipWhileQueryable List Data Constructor 1" << std::endl;
  }
  SkipWhileQueryableListData(
    const std::shared_ptr<QueryableData<TObj, std::list, TAllocator>> & data,
    std::shared_ptr<IWhileCondition<TObj>> && condition)
    : SkipWhileQueryableData<TObj, std::list, TAllocator>(data, std::move(condition))
  {
    // std::cout << "SkipWhileQueryable List Data Constructor 3" << std::endl;
  }
  SkipWhileQueryableListData(const SkipWhileQueryableListData<TObj, TAllocator> & other)
    : SkipWhileQueryableData<TObj, std::list, TAllocator>(other)
  {
    // std::cout << "SkipWhileQueryable List Data Constructor 2" << std::endl;
  }

  virtual ~SkipWhileQueryableListData() { }

  virtual std::shared_ptr<IQueryableData<TObj>> Clone() override
  {
    return std::make_shared<SkipWhileQueryableListData<TObj, TAllocator>>(*this);
  }

  virtual void InternalAdd(TObj item) override
  {
    this->items->push_back(item);
  }

  virtual std::shared_ptr<IQueryableData<TObj>> GetRealizedQueryableData() override
  {
    // If all QueryableData's have a constructor that skips begin, end, Args... then this method can be a one liner
    std::list<TObj, TAllocator> data(this->items->get_allocator());

    for (const TObj & value : *this)
    {
        data.push_back(value);
    }
    
    return std::make_shared<QueryableListData<TObj, TAllocator>>(std::move(data));
  }
};

#endif
