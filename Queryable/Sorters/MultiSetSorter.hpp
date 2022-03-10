#ifndef CPPQUERYABLE_SORTERS_MULTISETSORTER_H
#define CPPQUERYABLE_SORTERS_MULTISETSORTER_H

#include <algorithm>
#include <set>

#include "Sorter.hpp"

template<
  typename TObj,
  typename TLessThan = std::less<TObj>,
  typename TAllocator = std::allocator<TObj>>
class MultiSetSorter :
  public Sorter<
    TObj,
    std::multiset,
    SortOutput<TObj, std::multiset, std::function<bool(TObj, TObj)>>>
{
public:
  virtual SortOutput<TObj, std::multiset, std::function<bool(TObj, TObj)>> Sort(
    std::multiset<TObj, TLessThan, TAllocator> & iterable,
    std::function<bool(TObj, TObj)> lessThan = [](TObj a, TObj b) { return a < b; }) const override
  {
    std::multiset<TObj, std::function<bool(TObj, TObj)>, TAllocator> newMultiSet(iterable.begin(), iterable.end(), lessThan);
    SortOutput<TObj, std::multiset, std::function<bool(TObj, TObj)>> newlySorted(newMultiSet);
    return newlySorted;
  }
};

#endif
