#ifndef CPPQUERYABLE_SORTERS_VECTORSORTER_H
#define CPPQUERYABLE_SORTERS_VECTORSORTER_H

#include <algorithm>
#include <vector>

#include "Sorter.hpp"

template<
  typename TObj,
  typename TLessThan = std::less<TObj>,
  typename TAllocator = std::allocator<TObj>>
class VectorSorter :
  public Sorter<
    TObj,
    void, //SortOutput<TObj, std::vector, TAllocator>,
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
