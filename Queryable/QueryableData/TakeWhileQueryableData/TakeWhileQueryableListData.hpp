#ifndef CPPQUERYABLE_QUERYABLE_TAKEWHILEQUERYABLELISTDATA_H
#define CPPQUERYABLE_QUERYABLE_TAKEWHILEQUERYABLELISTDATA_H

#include <iostream>
#include <list>

#include "../../QueryableType.hpp"
#include "../../Utilities/Condition.hpp"
#include "../../Sorters/ListSorter.hpp"
#include "TakeWhileQueryableData.hpp"

template<typename TObj, typename TAllocator = std::allocator<TObj>>
class TakeWhileQueryableListData : public TakeWhileQueryableData<TObj, std::list, TAllocator>
{
public:
  TakeWhileQueryableListData(
    std::shared_ptr<IQueryableData<TObj>> && data,
    std::shared_ptr<IWhileCondition<TObj>> && condition)
    : TakeWhileQueryableData<TObj, std::list, TAllocator>(std::move(data), std::move(condition))
  {
    // std::cout << "TakeWhileQueryable List Data Constructor 0" << std::endl;
  }
  TakeWhileQueryableListData(
    std::shared_ptr<QueryableData<TObj, std::list, TAllocator>> && data,
    std::shared_ptr<IWhileCondition<TObj>> && condition)
    : TakeWhileQueryableData<TObj, std::list, TAllocator>(std::move(data), std::move(condition))
  {
    // std::cout << "TakeWhileQueryable List Data Constructor 1" << std::endl;
  }
  TakeWhileQueryableListData(
    const std::shared_ptr<QueryableData<TObj, std::list, TAllocator>> & data,
    std::shared_ptr<IWhileCondition<TObj>> && condition)
    : TakeWhileQueryableData<TObj, std::list, TAllocator>(data, std::move(condition))
  {
    // std::cout << "TakeWhileQueryable List Data Constructor 3" << std::endl;
  }
  TakeWhileQueryableListData(const TakeWhileQueryableListData<TObj, TAllocator> & other)
    : TakeWhileQueryableData<TObj, std::list, TAllocator>(other)
  {
    // std::cout << "TakeWhileQueryable List Data Constructor 2" << std::endl;
  }

  virtual ~TakeWhileQueryableListData() { }

  virtual std::shared_ptr<IQueryableData<TObj>> Clone() override
  {
    return std::make_shared<TakeWhileQueryableListData<TObj, TAllocator>>(*this);
  }

  virtual void InternalAdd(TObj item) override
  {
    this->items->push_back(item);
  }

  virtual std::shared_ptr<IQueryableData<TObj>> GetRealizedQueryableData() override
  {
    // If all QueryableData's have a constructor that takes begin, end, Args... then this method can be a one liner
    std::list<TObj, TAllocator> data(this->items->get_allocator());

    for (const TObj & value : *this)
    {
        data.push_back(value);
    }
    
    return std::make_shared<QueryableListData<TObj, TAllocator>>(std::move(data));
  }
};

#endif
