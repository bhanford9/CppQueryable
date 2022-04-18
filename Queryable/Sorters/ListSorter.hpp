#ifndef CPPQUERYABLE_SORTERS_LISTSORTER_H
#define CPPQUERYABLE_SORTERS_LISTSORTER_H

#include <algorithm>
#include <list>

#include "Sorter.hpp"

template<
  typename TObj,
  typename TAllocator = std::allocator<TObj>,
  typename TLessThan = std::less<TObj>>
class ListSorter :
  public Sorter<
    TObj,
    SortOutput<TObj, std::list, TAllocator>,
    TLessThan>
{
public:
  virtual SortOutput<TObj, std::list, TAllocator> Sort(
    QueryableIterator<TObj> beginIterator,
    QueryableIterator<TObj> endIterator,
    TLessThan lessThan = {}) const override
  {
    std::list<TObj, TAllocator> copy(beginIterator, endIterator);
    copy.sort(lessThan);
    SortOutput<TObj, std::list, TAllocator> output(copy);
    return output;
  }
};

#endif
