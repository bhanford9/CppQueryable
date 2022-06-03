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
    TAllocator>
{
public:
  virtual void Sort(
    std::list<TObj, TAllocator> & container,
    std::function<bool(const TObj &, const TObj &)> lessThan = std::less<TObj>()) const override
  {
    container.sort(lessThan);
  }
};

#endif
