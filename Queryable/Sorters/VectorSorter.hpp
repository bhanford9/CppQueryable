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
    TAllocator>
{
public:
  virtual void Sort(
    std::vector<TObj, TAllocator> & container,
    std::function<bool(const TObj &, const TObj &)> lessThan = std::less<TObj>()) const override
  {
    std::sort(container.begin(), container.end(), lessThan);
  }
};

#endif
