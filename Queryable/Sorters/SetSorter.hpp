#ifndef CPPQUERYABLE_SORTERS_SETSORTER_H
#define CPPQUERYABLE_SORTERS_SETSORTER_H

#include <algorithm>
#include <set>

#include "Sorter.hpp"

template<
  typename TObj,
  typename TLessThan = std::less<TObj>,
  typename TAllocator = std::allocator<TObj>>
class SetSorter :
  public Sorter<
    TObj,
    std::set,
    SortOutput<TObj, std::set, std::function<bool(TObj, TObj)>>>
{
public:
  virtual SortOutput<TObj, std::set, std::function<bool(TObj, TObj)>> Sort(
    std::set<TObj, TLessThan, TAllocator> & iterable,
    std::function<bool(TObj, TObj)> lessThan = [](TObj a, TObj b) { return a < b; }) const override
  {
    std::set<TObj, std::function<bool(TObj, TObj)>, TAllocator> newSet(iterable.begin(), iterable.end(), lessThan);
    SortOutput<TObj, std::set, std::function<bool(TObj, TObj)>> newlySorted(newSet);
    return newlySorted;
  }
};

#endif
