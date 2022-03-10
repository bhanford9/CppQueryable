#ifndef CPPQUERYABLE_SORTERS_VECTORSORTER_H
#define CPPQUERYABLE_SORTERS_VECTORSORTER_H

#include <algorithm>
#include <vector>

#include "Sorter.hpp"

template<
  typename TObj,
  typename TAllocator = std::allocator<TObj>>
class VectorSorter :
  public Sorter<
    TObj,
    std::vector,
    SortOutput<TObj, std::vector, TAllocator>,
    TAllocator>
{
public:
  virtual SortOutput<TObj, std::vector, TAllocator> Sort(
    std::vector<TObj, TAllocator> & iterable,
    std::function<bool(TObj, TObj)> lessThan = [](TObj a, TObj b) { return a < b; }) const override
  {
    std::sort(iterable.begin(), iterable.end(), lessThan);
    return iterable;
  }
};

#endif
