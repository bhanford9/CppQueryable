#ifndef CPPQUERYABLE_SORTERS_DEQUESORTER_H
#define CPPQUERYABLE_SORTERS_DEQUESORTER_H

#include <algorithm>
#include <deque>

#include "Sorter.hpp"

template<
  typename TObj,
  typename TAllocator = std::allocator<TObj>>
class DequeSorter :
  public Sorter<
    TObj,
    std::deque,
    SortOutput<TObj, std::deque, TAllocator>,
    TAllocator>
{
public:
  virtual SortOutput<TObj, std::deque, TAllocator> Sort(
    std::deque<TObj, TAllocator> & iterable,
    std::function<bool(TObj, TObj)> lessThan = [](TObj a, TObj b) { return a < b; }) const override
  {
    std::sort(iterable.begin(), iterable.end(), lessThan);
    return iterable;
  }
};

#endif
