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
    std::vector,
    TLessThan,
    TAllocator>
{
public:
  VectorSorter(TLessThan lessThan = {}) :
    Sorter<TObj, std::vector, TLessThan, TAllocator>(lessThan)
  {
  }
  virtual ~VectorSorter() { }

  virtual void Sort(std::vector<TObj, TAllocator> & container) const override
  {
    std::sort(container.begin(), container.end(), this->lessThan);
  }
};

#endif
