#ifndef CPPQUERYABLE_SORTERS_SORTER_H
#define CPPQUERYABLE_SORTERS_SORTER_H

#include <functional>
#include <iostream>
#include <memory>

#include "../Iterators/QueryableIterator.hpp"

template<
  typename TObj,
  template<typename, typename ...> typename TIterable,
  typename TAllocator = std::allocator<TObj>,
  typename ...TArgs>
class Sorter
{
public:
  virtual void Sort(
    TIterable<TObj, TAllocator, TArgs...> & container,
    std::function<bool(const TObj &, const TObj &)> lessThan = std::less<TObj>()) const = 0;
};

#endif
