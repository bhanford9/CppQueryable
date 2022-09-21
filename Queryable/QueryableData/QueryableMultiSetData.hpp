#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLEMULTISETDATA_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLEMULTISETDATA_H

#include <iostream>
#include <memory>
#include <set>

#include "SortedQueryableData.hpp"

template<
  typename T,
  typename TCompare = std::less<T>,
  typename TAllocator = std::allocator<T>>
class QueryableMultiSetData : public SortedQueryableData<T, std::multiset, TCompare, TAllocator>
{
  typedef typename std::vector<T>::iterator TVectorIterator;
public:
  QueryableMultiSetData(TCompare comparator = {})
    : SortedQueryableData<T, std::multiset, TCompare, TAllocator>() { }

  QueryableMultiSetData(const std::multiset<T, TCompare, TAllocator> & items)
    : SortedQueryableData<T, std::multiset, TCompare, TAllocator>(items) { }

  QueryableMultiSetData(std::multiset<T, TCompare, TAllocator> && items)
    : SortedQueryableData<T, std::multiset, TCompare, TAllocator>(std::move(items)) { }

  QueryableMultiSetData(const QueryableMultiSetData<T, TCompare, TAllocator> & data)
    : SortedQueryableData<T, std::multiset, TCompare, TAllocator>(data) { }

  QueryableMultiSetData(
    TVectorIterator first,
    TVectorIterator last,
    TCompare comparator = {})
    : SortedQueryableData<T, std::multiset, TCompare, TAllocator>(first, last, comparator)
  {
  }

  virtual ~QueryableMultiSetData() { }

  virtual std::shared_ptr<IQueryableData<T>> Clone() override
  {
    return std::make_shared<QueryableMultiSetData<T, TCompare, TAllocator>>(*this);
  }

  void Add(T item) override
  {
    this->items->insert(item);
    this->size++;
  }
};

#endif
