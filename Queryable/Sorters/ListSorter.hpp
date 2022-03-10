#ifndef CPPQUERYABLE_SORTERS_LISTSORTER_H
#define CPPQUERYABLE_SORTERS_LISTSORTER_H

#include <algorithm>
#include <list>

#include "Sorter.hpp"

template<
  typename TObj,
  typename TAllocator = std::allocator<TObj>>
class ListSorter :
  public Sorter<
    TObj,
    std::list,
    SortOutput<TObj, std::list, TAllocator>,
    TAllocator>
{
public:
  virtual SortOutput<TObj, std::list, TAllocator> Sort(
    std::list<TObj, TAllocator> & iterable,
    std::function<bool(TObj, TObj)> lessThan = [](TObj a, TObj b) { return a < b; }) const override
  {
    iterable.sort(lessThan);
    return iterable;
  }
};

#endif
