#ifndef CPPQUERYABLE_QUERYABLE_SELECTQUERYABLELISTDATA_H
#define CPPQUERYABLE_QUERYABLE_SELECTQUERYABLELISTDATA_H

#include <iostream>
#include <list>

#include "SelectQueryableData.hpp"
#include "../../Sorters/ListSorter.hpp"

template<
  typename TOriginal,
  typename TCurrent,
  typename TAllocator = std::allocator<TCurrent>>
class SelectQueryableListData : public SelectQueryableData<TOriginal, TCurrent, std::list, TAllocator>
{
public:
  SelectQueryableListData(
    std::shared_ptr<QueryableData<TOriginal, std::list, TAllocator>> && data,
    std::function<TCurrent(TOriginal)> selector)
    : SelectQueryableData<TOriginal, TCurrent, std::list, TAllocator>(std::move(data), selector)
  {
  }
  SelectQueryableListData(
    const std::shared_ptr<QueryableData<TOriginal, std::list, TAllocator>> & data,
    std::function<TCurrent(TOriginal)> selector)
    : SelectQueryableData<TOriginal, TCurrent, std::list, TAllocator>(data, selector)
  {
  }

  virtual ~SelectQueryableListData() { }

  virtual std::shared_ptr<IQueryableData<TCurrent>> Clone() override
  {
    return std::make_shared<SelectQueryableListData<TOriginal, TCurrent, TAllocator>>(*this);
  }

  void Add(TCurrent item) override
  {
    // this wont easily or quickly work... might want to nix it
    this->items->push_back(item);
    this->size++;
  }

  virtual std::shared_ptr<IQueryableData<TCurrent>> GetRealizedQueryableData() override
  {
    // If all QueryableData's have a constructor that takes begin, end, Args... then this method can be a one liner
    std::list<TCurrent, TAllocator> data(this->items->get_allocator());

    for (const TCurrent & value : *this)
    {
        data.push_back(value);
    }

    return std::make_shared<QueryableListData<TCurrent, TAllocator>>(std::move(data));
  }
};

#endif
