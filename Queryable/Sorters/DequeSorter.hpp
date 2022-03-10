#ifndef CPPQUERYABLE_SORTERS_DEQUESORTER_H
#define CPPQUERYABLE_SORTERS_DEQUESORTER_H

#include <algorithm>
#include <deque>

#include "Sorter.hpp"

template<
  typename TObj,
  // typename TLessThan = std::less<TObj>,
  typename ...TArgs>
  // typename TAllocator = std::allocator<TObj>>
class DequeSorter :
  public Sorter<
    TObj,
    std::deque,
    SortOutput<TObj, std::deque, TArgs...>,
    // TLessThan,
    TArgs...>  // First TArgs... used by sort input parameter
{
public:
  virtual SortOutput<TObj, std::deque, TArgs...> Sort(
    std::deque<TObj, TArgs...> & iterable,
    std::function<bool(TObj, TObj)> lessThan = [](TObj a, TObj b) { return a < b; }) const override
  {
    std::sort(iterable.begin(), iterable.end(), lessThan);

    // deque move constructor will be used by default, so it costs little extra to return it
    SortOutput<TObj, std::deque, TArgs...> retValue(iterable);
    return retValue;
  }
};

#endif
