#ifndef CPPQUERYABLE_SORTERS_SORTER_H
#define CPPQUERYABLE_SORTERS_SORTER_H

#include <functional>
#include <iostream>

#include "Outputs/SortOutput.hpp"

template<
  typename TObj,
  template<typename, typename ...> typename TIterable,
  typename TOutput,
  // typename TLessThan = std::less<TObj>,
  typename ...TArgs>
class Sorter
{
public:
  virtual TOutput Sort(
    TIterable<TObj, TArgs...> & iterable,
    std::function<bool(TObj, TObj)> lessThan = [](TObj a, TObj b) { return a < b; }) const = 0;
};

#endif
