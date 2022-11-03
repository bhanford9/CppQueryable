#ifndef CPPQUERYABLE_SORTERS_SORTER_H
#define CPPQUERYABLE_SORTERS_SORTER_H

#include <functional>

#include "ISorter.hpp"

template<
  typename TObj,
  template<typename, typename ...> class TIterable,
  typename TLessThan = std::less<TObj>,
  typename ...TArgs>
class Sorter : public ISorter<TObj, TIterable, TArgs...>
{
protected:
  TLessThan lessThan;

public:
  Sorter(TLessThan lessThan = {}) :
    lessThan(lessThan)
  {
  }
  virtual ~Sorter() { }

  virtual void Sort(TIterable<TObj, TArgs...> & container) const = 0;
};

#endif
