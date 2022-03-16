#ifndef CPPQUERYABLE_QUERYABLE_WHEREQUERYABLEDEQUEDATA_H
#define CPPQUERYABLE_QUERYABLE_WHEREQUERYABLEDEQUEDATA_H

#include <iostream>
#include <deque>

#include "../../QueryableType.hpp"
#include "../../Utilities/Condition.hpp"
#include "WhereQueryableData.hpp"

template<typename TObj, typename TAllocator = std::allocator<TObj>>
class WhereQueryableDequeData : public WhereQueryableData<TObj, std::deque, TAllocator>
{
public:
  WhereQueryableDequeData(
    std::shared_ptr<IQueryableData<TObj>> data,
    std::function<bool(TObj)> condition)
    : WhereQueryableData<TObj, std::deque, TAllocator>(std::move(data), std::move(condition))
  {
  }
  WhereQueryableDequeData(
    std::shared_ptr<QueryableData<TObj, std::deque, TAllocator>> && data,
    std::function<bool(TObj)> condition)
    : WhereQueryableData<TObj, std::deque, TAllocator>(std::move(data), std::move(condition))
  {
  }
  WhereQueryableDequeData(const WhereQueryableDequeData<TObj, TAllocator> & other)
    : WhereQueryableData<TObj, std::deque, TAllocator>(other)
  {
  }

  virtual ~WhereQueryableDequeData() { }

  void Add(TObj item) override
  {
    // this wont easily or quickly work... might want to nix it
    this->items.push_back(item);
    this->size++;
  }
};

#endif
