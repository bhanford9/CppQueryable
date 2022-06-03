#ifndef CPPQUERYABLE_QUERYABLE_WHEREQUERYABLELISTDATA_H
#define CPPQUERYABLE_QUERYABLE_WHEREQUERYABLELISTDATA_H

#include <iostream>
#include <list>

#include "../../Utilities/Condition.hpp"
#include "../../Sorters/ListSorter.hpp"
#include "WhereQueryableData.hpp"

template<
  typename TObj,
  typename TAllocator = std::allocator<TObj>>
class WhereQueryableListData : public WhereQueryableData<TObj, std::list, TAllocator>
{
protected:

  virtual void Add(std::list<TObj, TAllocator> items, TObj item) const
  {
    items.push_back(item);
  }
public:
  WhereQueryableListData(
    std::shared_ptr<IQueryableData<TObj>> data,
    std::function<bool(TObj)> condition)
    : WhereQueryableData<TObj, std::list, TAllocator>(std::move(data), std::move(condition))
  {
  }
  WhereQueryableListData(
    std::shared_ptr<QueryableData<TObj, std::list, TAllocator>> && data,
    std::function<bool(TObj)> && condition)
    : WhereQueryableData<TObj, std::list, TAllocator>(std::move(data), std::move(condition))
  {
  }
  WhereQueryableListData(const WhereQueryableListData<TObj, TAllocator> & other)
    : WhereQueryableData<TObj, std::list, TAllocator>(other)
  {
  }

  virtual ~WhereQueryableListData() { }

  virtual std::shared_ptr<IQueryableData<TObj>> Clone() override
  {
    return std::make_shared<WhereQueryableListData<TObj, TAllocator>>(*this);
  }

  virtual void InternalAdd(TObj item) override
  {
    this->items->push_back(item);
  }

  virtual std::shared_ptr<Sorter<TObj, std::list, TAllocator>> GetSorter() override
  {
    return std::make_shared<ListSorter<TObj, TAllocator>>();
  }
};

#endif
