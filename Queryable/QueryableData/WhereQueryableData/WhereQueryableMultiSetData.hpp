#ifndef CPPQUERYABLE_QUERYABLE_WHEREQUERYABLEMULTISETDATA_H
#define CPPQUERYABLE_QUERYABLE_WHEREQUERYABLEMULTISETDATA_H

#include <iostream>
#include <set>

#include "../../Utilities/Condition.hpp"
#include "WhereQueryableData.hpp"

template<
  typename TObj,
  typename TCompare = std::less<TObj>,
  typename TAllocator = std::allocator<TObj>>
class WhereQueryableMultiSetData : public WhereQueryableData<TObj, std::multiset, TCompare, TAllocator>
{
public:
  WhereQueryableMultiSetData(
    std::shared_ptr<IQueryableData<TObj, TObj>> data,
    std::function<bool(TObj)> condition)
    : WhereQueryableData<TObj, std::multiset, TCompare, TAllocator>(std::move(data), std::move(condition))
  {
  }
  WhereQueryableMultiSetData(
    std::shared_ptr<QueryableData<TObj, std::multiset, TCompare, TAllocator>> && data,
    std::function<bool(TObj)> condition)
    : WhereQueryableData<TObj, std::multiset, TCompare, TAllocator>(std::move(data), std::move(condition))
  {
  }
  WhereQueryableMultiSetData(const WhereQueryableMultiSetData<TObj, TCompare, TAllocator> & other)
    : WhereQueryableData<TObj, std::multiset, TCompare, TAllocator>(other)
  {
  }

  virtual ~WhereQueryableMultiSetData() { }

  void Add(TObj item) override
  {
    // this wont easily or quickly work... might want to nix it
    this->items.insert(item);
    this->size++;
  }
};

#endif
