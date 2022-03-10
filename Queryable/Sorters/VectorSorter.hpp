#ifndef CPPQUERYABLE_SORTERS_VECTORSORTER_H
#define CPPQUERYABLE_SORTERS_VECTORSORTER_H

#include <algorithm>
#include <vector>

#include "Sorter.hpp"

template<
  typename TObj,
  // typename TLessThan = std::less<TObj>,
  typename ...TArgs>
  // typename TAllocator = std::allocator<TObj>>
class VectorSorter :
  public Sorter<
    TObj,
    std::vector,
    SortOutput<TObj, std::vector, TArgs...>,
    // TLessThan,
    TArgs...>  // First TArgs... used by sort input parameter
{
public:
  virtual SortOutput<TObj, std::vector, TArgs...> Sort(
    std::vector<TObj, TArgs...> & iterable,
    std::function<bool(TObj, TObj)> lessThan = [](TObj a, TObj b) { return a < b; }) const override
  {
    std::sort(iterable.begin(), iterable.end(), lessThan);

    // vector move constructor will be used by default, so it costs little extra to return it
    return iterable;
  }
};

#endif
