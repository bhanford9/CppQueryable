#ifndef CPPQUERYABLE_SORTERS_LISTSORTER_H
#define CPPQUERYABLE_SORTERS_LISTSORTER_H

#include <algorithm>
#include <list>

#include "Sorter.hpp"

template<
  typename TObj,
  typename TLessThan = std::less<TObj>,
  typename TAllocator = std::allocator<TObj>>
class ListSorter :
  public Sorter<
    TObj,
    std::list,
    TLessThan,
    TAllocator>
{
public:
  ListSorter(TLessThan lessThan = {}) :
    Sorter<TObj, std::list, TLessThan, TAllocator>(lessThan)
  {
  }
  virtual ~ListSorter() { }

  virtual void Sort(std::list<TObj, TAllocator> & container) const override
  {
    container.sort(this->lessThan);
  }
};

#endif
