#ifndef CPPQUERYABLE_SORTERS_SORTER_H
#define CPPQUERYABLE_SORTERS_SORTER_H

#include <functional>
#include <iostream>
#include <memory>

#include "Outputs/SortOutput.hpp"
#include "../InternalQueryable.hpp"

template<
  typename TObj,
  typename TOutput,
  typename TLessThan = std::less<TObj>>
class Sorter
{
public:
  virtual TOutput Sort(
    QueryableIterator<TObj> beginIterator,
    QueryableIterator<TObj> endIterator,
    TLessThan lessThan = {}) const = 0;
};

#endif
