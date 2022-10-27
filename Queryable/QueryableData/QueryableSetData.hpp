#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLESETDATA_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLESETDATA_H

#include <iostream>
#include <memory>
#include <set>

#include "SortedQueryableData.hpp"

template<
  typename T,
  typename TCompare = std::less<T>,
  typename TAllocator = std::allocator<T>>
class QueryableSetData : public SortedQueryableData<T, std::set, TCompare, TAllocator>
{
  typedef typename std::vector<T>::iterator TVectorIterator;
public:
  QueryableSetData(TCompare comparator = {})
    : SortedQueryableData<T, std::set, TCompare, TAllocator>() { }

  QueryableSetData(const std::set<T, TCompare, TAllocator> & items)
    : SortedQueryableData<T, std::set, TCompare, TAllocator>(items)
    {
    }

  QueryableSetData(std::set<T, TCompare, TAllocator> && items)
    : SortedQueryableData<T, std::set, TCompare, TAllocator>(std::move(items))
    {
    }

  QueryableSetData(const QueryableSetData<T, TCompare, TAllocator> & data)
    : SortedQueryableData<T, std::set, TCompare, TAllocator>(data) { }

  QueryableSetData(
    TVectorIterator first,
    TVectorIterator last,
    TCompare comparator = {})
    : SortedQueryableData<T, std::set, TCompare, TAllocator>(first, last, comparator) { }

  virtual ~QueryableSetData() { }

  virtual std::shared_ptr<IQueryableData<T>> Clone() override
  {
    return std::make_shared<QueryableSetData<T, TCompare, TAllocator>>(*this);
  }

  void Add(T item) override
  {
    this->items->insert(item);

    // because its a set, the item may not have actually been added. Insert
    // returns true/false whether the item was added, but the size method is
    // also a constant time action, so its cleaner to use it
    this->size = this->items->size();
  }
  virtual T & Get(IteratorType type) override
  {
    std::cout << "queryable set data" << std::endl;
    switch (type)
    {
      // case IteratorType::BeginForward: { return *this->beginIterator; }
      // case IteratorType::EndForward: { return *this->endIterator; }
      // case IteratorType::BeginReverse: { return *this->rbeginIterator; }
      // case IteratorType::EndReverse: default: { return *this->rendIterator; }
      case IteratorType::BeginForward: { *this->value = *this->beginIterator; return *this->value; }
      case IteratorType::EndForward: { *this->value = *this->endIterator; return *this->value; }
      case IteratorType::BeginReverse: { *this->value = *this->rbeginIterator; return *this->value; }
      case IteratorType::EndReverse: default: { *this->value = *this->rendIterator; return *this->value; }
    }

    return *this->value;
  }
};

#endif
