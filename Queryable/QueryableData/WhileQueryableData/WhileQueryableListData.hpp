#ifndef CPPQUERYABLE_QUERYABLE_WHILEQUERYABLELISTDATA_H
#define CPPQUERYABLE_QUERYABLE_WHILEQUERYABLELISTDATA_H

#include <iostream>
#include <list>

#include "../../QueryableType.hpp"
#include "../../Utilities/Condition.hpp"
#include "../../Sorters/ListSorter.hpp"
#include "WhileQueryableData.hpp"

template<typename TObj, typename TAllocator = std::allocator<TObj>>
class WhileQueryableListData : public WhileQueryableData<TObj, std::list, TAllocator>
{
public:
  WhileQueryableListData(
    std::shared_ptr<IQueryableData<TObj>> && data,
    std::shared_ptr<IWhileCondition<TObj>> && condition)
    : WhileQueryableData<TObj, std::list, TAllocator>(std::move(data), std::move(condition))
  {
    // std::cout << "WhileQueryable List Data Constructor 0" << std::endl;
  }
  WhileQueryableListData(
    std::shared_ptr<QueryableData<TObj, std::list, TAllocator>> && data,
    std::shared_ptr<IWhileCondition<TObj>> && condition)
    : WhileQueryableData<TObj, std::list, TAllocator>(std::move(data), std::move(condition))
  {
    // std::cout << "WhileQueryable List Data Constructor 1" << std::endl;
  }
  WhileQueryableListData(
    const std::shared_ptr<QueryableData<TObj, std::list, TAllocator>> & data,
    std::shared_ptr<IWhileCondition<TObj>> && condition)
    : WhileQueryableData<TObj, std::list, TAllocator>(data, std::move(condition))
  {
    // std::cout << "WhileQueryable List Data Constructor 3" << std::endl;
  }
  WhileQueryableListData(const WhileQueryableListData<TObj, TAllocator> & other)
    : WhileQueryableData<TObj, std::list, TAllocator>(other)
  {
    // std::cout << "WhileQueryable List Data Constructor 2" << std::endl;
  }

  virtual ~WhileQueryableListData() { }

  virtual std::shared_ptr<IQueryableData<TObj>> Clone() override
  {
    return std::make_shared<WhileQueryableListData<TObj, TAllocator>>(*this);
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
