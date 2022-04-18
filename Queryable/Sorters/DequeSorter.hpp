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
    void,//SortOutput<TObj, std::deque, TAllocator>,
    TLessThan>
{
public:
  virtual void Sort(
    QueryableIterator<TObj> beginIterator,
    QueryableIterator<TObj> endIterator,
    TLessThan lessThan = {}) const override
  {
    std::sort(beginIterator, endIterator, lessThan);
  }
};

#endif
