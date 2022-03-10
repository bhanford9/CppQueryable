#ifndef CPPQUERYABLE_SORTERS_SETSORTER_H
#define CPPQUERYABLE_SORTERS_SETSORTER_H

#include <algorithm>
#include <set>

#include "Sorter.hpp"

template<
  typename TObj,
  typename ...TArgs>
  // typename TLessThan = std::less<TObj>,
  // typename TAllocator = std::allocator<TObj>,
  // typename TOriginalLessThan = std::less<TObj>>
class SetSorter :
  public Sorter<
    TObj,
    std::set,
    SortOutput<TObj, std::set, std::function<bool(TObj, TObj)>>>
    // TLessThan,
    // TOriginalLessThan,  // First TArgs... used by sort input parameter
    // TAllocator>         // Second TArgs... used by sort input parameter
{
public:
  virtual SortOutput<TObj, std::set, std::function<bool(TObj, TObj)>> Sort(
    std::set<TObj, TArgs...> & iterable,
    std::function<bool(TObj, TObj)> lessThan = [](TObj a, TObj b) { return a < b; }) const override
  {
    SortOutput<TObj, std::set, std::function<bool(TObj, TObj)>> newlySorted(iterable.begin(), iterable.end(), lessThan);

    // SortOutput move constructor will be used by default
    return newlySorted;
  }
};

#endif
