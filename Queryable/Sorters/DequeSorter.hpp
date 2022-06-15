#ifndef CPPQUERYABLE_SORTERS_DEQUESORTER_H
#define CPPQUERYABLE_SORTERS_DEQUESORTER_H

#include <algorithm>
#include <deque>

#include "Sorter.hpp"

template<
  typename TObj,
  typename TLessThan = std::less<TObj>,
  typename TAllocator = std::allocator<TObj>>
class DequeSorter :
  public Sorter<
    TObj,
    std::deque,
    TLessThan,
    TAllocator>
{
public:
  DequeSorter(TLessThan lessThan = {}) :
    Sorter<TObj, std::deque, TLessThan, TAllocator>(lessThan)
  {
  }
  virtual ~DequeSorter() { }

  virtual void Sort(std::deque<TObj, TAllocator> & container) const override
  {
    std::sort(container.begin(), container.end(), this->lessThan);
  }
};

#endif
