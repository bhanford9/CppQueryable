#ifndef CPPQUERYABLE_SORTERS_SETSORTER_H
#define CPPQUERYABLE_SORTERS_SETSORTER_H

#include <algorithm>
#include <set>

#include "Sorter.hpp"

template<
  typename TObj,
  typename TOutLessThan = std::less<TObj>,
  typename TLessThan = std::less<TObj>,
  typename TAllocator = std::allocator<TObj>>
class SetSorter :
  public Sorter<
    TObj,
    SortOutput<TObj, std::set, TOutLessThan>,
    TOutLessThan>
{
public:
  virtual SortOutput<TObj, std::set, TOutLessThan> Sort(
    QueryableIterator<TObj> beginIterator,
    QueryableIterator<TObj> endIterator,
    TOutLessThan lessThan = {}) const override
  {
    std::set<TObj, TOutLessThan, TAllocator> newSet(beginIterator, endIterator, lessThan);
    SortOutput<TObj, std::set, TOutLessThan> newlySorted(newSet);
    return newlySorted;
  }
};

#endif
