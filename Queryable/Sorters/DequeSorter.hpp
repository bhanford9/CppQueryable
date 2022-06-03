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
    TAllocator>
{
public:
  virtual void Sort(
    std::deque<TObj, TAllocator> & container,
    std::function<bool(const TObj &, const TObj &)> lessThan = std::less<TObj>()) const override
  {
    std::sort(container.begin(), container.end(), lessThan);
  }
};

#endif
