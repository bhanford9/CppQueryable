#ifndef CPPQUERYABLE_SORTERS_LISTSORTER_H
#define CPPQUERYABLE_SORTERS_LISTSORTER_H

#include <algorithm>
#include <list>

#include "Sorter.hpp"

template<
  typename TObj,
  // typename TLessThan = std::less<TObj>,
  typename ...TArgs>
  // typename TAllocator = std::allocator<TObj>>
class ListSorter :
  public Sorter<
    TObj,
    std::list,
    SortOutput<TObj, std::list, TArgs...>,
    // TLessThan,
    TArgs...>  // First TArgs... used by sort input parameter
{
public:
  virtual SortOutput<TObj, std::list, TArgs...> Sort(
    std::list<TObj, TArgs...> & iterable,
    std::function<bool(TObj, TObj)> lessThan = [](TObj a, TObj b) { return a < b; }) const override
  {
    iterable.sort(lessThan);

    // list move constructor will be used by default, so it costs little extra to return it
    return iterable;
  }
};

#endif
