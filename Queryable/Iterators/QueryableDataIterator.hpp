#ifndef CPPQUERYABLE_QUERYABLE_ITERATORS_QUERYABLEDATAITERATOR_H
#define CPPQUERYABLE_QUERYABLE_ITERATORS_QUERYABLEDATAITERATOR_H

#include "QueryableIterator.hpp"

template <typename T, template<typename, typename ...> typename TIterable, typename ...TArgs>
class QueryableDataIterator : virtual public QueryableIterator<T>
{
public:
  using TForwardIterator = typename TIterable<T, TArgs...>::iterator;
  using TReverseIterator = typename TIterable<T, TArgs...>::reverse_iterator;

  TIterable<T, TArgs...> items;

  TForwardIterator beginIterator;
  TForwardIterator endIterator;
  TReverseIterator rbeginIterator;
  TReverseIterator rendIterator;
};

#endif
