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
  typename TOut = T,
  typename ...TArgs>
class SortedQueryableData : public QueryableData<T, TOut, TIterable, TCompare, TAllocator, TArgs...>
{
protected:
  TCompare comparator;

  typedef typename std::vector<T>::iterator TVectorIterator;
public:
  SortedQueryableData(TCompare comparator = {})
    : QueryableData<T, TOut, TIterable, TCompare, TAllocator, TArgs...>()
  {
    this->comparator = comparator;
    this->items = TIterable<T, TCompare, TAllocator, TArgs...>(comparator);
  }

  SortedQueryableData(
    TIterable<T, TCompare, TAllocator, TArgs...> items,
    TCompare comparator = {})
    : QueryableData<T, TOut, TIterable, TCompare, TAllocator, TArgs...>(items)
  {
    this->comparator = comparator;
  }

  SortedQueryableData(const SortedQueryableData<T, TIterable, TCompare, TAllocator, TArgs...> & data)
    : QueryableData<T, TOut, TIterable, TCompare, TAllocator, TArgs...>(data)
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

  // void Sort(std::function<bool(T, T)> compare = [](T a, T b) { return a < b; }) override
  // {
  //   // this->Update(this->begin(), this->end(), compare);
  // }

  // virtual void Update(QueryableIterator<T> first, QueryableIterator<T> last, std::function<bool(T, T)> compare) override
  // {
  //   // TODO SFINAE require this constructor
  //   this->comparator = compare;
  //   this->items = TIterable<T, std::function<bool(T, T)>>(first, last, compare);
  //   this->size = this->items.size();
  // }
  //
  // virtual void Update(TVectorIterator first, TVectorIterator last) override
  // {
  //   // TODO SFINAE require this constructor
  //   this->items = TIterable<T, std::function<bool(T, T)>>(first, last, this->comparator);
  //   this->size = this->items.size();
  // }
};

#endif
