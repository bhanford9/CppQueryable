#ifndef CPPQUERYABLE_SORTERS_ISORTER_H
#define CPPQUERYABLE_SORTERS_ISORTER_H

#include <functional>
#include <iostream>
#include <memory>

#include "../Iterators/QueryableIterator.hpp"

template<
  typename TObj,
  template<typename, typename ...> typename TIterable,
  typename ...TArgs>
class ISorter
{
public:
  virtual ~ISorter() { }
  virtual void Sort(TIterable<TObj, TArgs...> & container) const = 0;
};

#endif
