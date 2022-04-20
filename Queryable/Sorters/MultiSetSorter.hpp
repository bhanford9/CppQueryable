#ifndef CPPQUERYABLE_SORTERS_MULTISETSORTER_H
#define CPPQUERYABLE_SORTERS_MULTISETSORTER_H

#include <algorithm>
#include <set>

#include "Sorter.hpp"

template<
  typename TObj,
  typename TOutLessThan = std::less<TObj>,
  typename TLessThan = std::less<TObj>,
  typename TAllocator = std::allocator<TObj>>
class MultiSetSorter :
  public Sorter<
    TObj,
    SortOutput<TObj, std::multiset, TOutLessThan>,
    TOutLessThan>
{
public:
  virtual SortOutput<TObj, std::multiset, TOutLessThan, TAllocator> Sort(
    QueryableIterator<TObj> beginIterator,
    QueryableIterator<TObj> endIterator,
    TOutLessThan lessThan = {}) const override
  {
    std::cout << "multiset sorter sort 1" << std::endl;
    std::multiset<TObj, TOutLessThan, TAllocator> newMultiSet(beginIterator, endIterator, lessThan);
    std::cout << "multiset sorter sort 2" << std::endl;
    SortOutput<TObj, std::multiset, TOutLessThan, TAllocator> newlySorted(newMultiSet);
    std::cout << "multiset sorter sort 3" << std::endl;
    return newlySorted;
  }
};

#endif
