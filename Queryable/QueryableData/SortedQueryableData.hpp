#ifndef CPPQUERYABLE_QUERYABLE_SORTEDQUERYABLEDATA_H
#define CPPQUERYABLE_QUERYABLE_SORTEDQUERYABLEDATA_H

#include <iostream>
#include <memory>

#include "QueryableData.hpp"

template<
  typename T,
  template<typename, typename ...> typename TIterable,
  typename TCompare = std::less<T>,
  typename TAllocator = std::allocator<T>,
  typename ...TArgs>
class SortedQueryableData : public QueryableData<T, TIterable, TCompare, TAllocator, TArgs...>
{
protected:
  TCompare comparator; // TODO --> I don't think this is actually necessary

  typedef typename std::vector<T>::iterator TVectorIterator;
public:
  SortedQueryableData(TCompare comparator = {})
    : QueryableData<T, TIterable, TCompare, TAllocator, TArgs...>()
  {
    this->comparator = comparator;
    this->items = TIterable<T, TCompare, TAllocator, TArgs...>(comparator);
  }

  // SortedQueryableData(
  //   TIterable<T, TCompare, TAllocator, TArgs...> items,
  //   TCompare comparator = {})
  //   : QueryableData<T, TIterable, TCompare, TAllocator, TArgs...>(items)
  // {
  //   this->comparator = comparator;
  // }

  SortedQueryableData(
    const TIterable<T, TCompare, TAllocator, TArgs...> & items,
    TCompare comparator = {})
    : QueryableData<T, TIterable, TCompare, TAllocator, TArgs...>(items)
  {
    this->comparator = comparator;
  }

  SortedQueryableData(
    TIterable<T, TCompare, TAllocator, TArgs...> && items,
    TCompare comparator = {})
    : QueryableData<T, TIterable, TCompare, TAllocator, TArgs...>(std::move(items))
  {
    this->comparator = comparator;
  }

  SortedQueryableData(const SortedQueryableData<T, TIterable, TCompare, TAllocator, TArgs...> & data)
    : QueryableData<T, TIterable, TCompare, TAllocator, TArgs...>(data)
  {
    this->comparator = data.comparator;
  }

  SortedQueryableData(
    TVectorIterator first,
    TVectorIterator last,
    TCompare comparator = {})
  {
    // TODO SFINAE require this constructor
    this->comparator = comparator;
    this->items = TIterable<T, TCompare, TAllocator, TArgs...>(first, last, this->comparator);
    this->size = this->items.size();
  }

  virtual ~SortedQueryableData() { }
};

#endif
