#ifndef CPPQUERYABLE_QUERYABLE_WHEREQUERYABLESETDATA_H
#define CPPQUERYABLE_QUERYABLE_WHEREQUERYABLESETDATA_H

#include <iostream>
#include <set>

#include "../../Utilities/Condition.hpp"
#include "WhereQueryableData.hpp"

template<
  typename TObj,
  typename TCompare = std::less<TObj>,
  typename TAllocator = std::allocator<TObj>>
class WhereQueryableSetData : public WhereQueryableData<TObj, std::set, TCompare, TAllocator>
{
public:
  WhereQueryableSetData(
    std::shared_ptr<IQueryableData<TObj, TObj>> data,
    std::function<bool(TObj)> condition)
    : WhereQueryableData<TObj, std::set, TCompare, TAllocator>(std::move(data), std::move(condition))
  {
  }
  WhereQueryableSetData(const WhereQueryableSetData<TObj, TCompare, TAllocator> & other)
    : WhereQueryableData<TObj, std::set, TCompare, TAllocator>(other)
  {
  }

  virtual ~WhereQueryableSetData() { }

  void Add(TObj item) override
  {
    // this wont easily or quickly work... might want to nix it
    this->items.insert(item);
    this->size++;
  }

  // virtual void Update(QueryableIterator<TObj> first, QueryableIterator<TObj> last, std::function<bool(TObj, TObj)> compare) override
  // {
  //   this->original.get()->Update(first, last, compare);
  // }
};

#endif
