#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLELISTDATA_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLELISTDATA_H

#include <iostream>
#include <list>

#include "../Sorters/ListSorter.hpp"
#include "QueryableData.hpp"

template<
  typename T,
  typename TAllocator = std::allocator<T>>
class QueryableListData : public QueryableData<T, std::list, T, TAllocator>
{
protected:

  virtual void Add(std::list<T, TAllocator> items, T item) const
  {
    items.push_back(item);
  }
public:
  QueryableListData() : QueryableData<T, std::list, T, TAllocator>() { }

  // QueryableListData(std::list<T, TAllocator> items)
  //   : QueryableData<T, std::list, TAllocator>(items) { }

  QueryableListData(const std::list<T, TAllocator> & items)
    : QueryableData<T, std::list, T, TAllocator>(items) { }

  QueryableListData(std::list<T, TAllocator> && items)
    : QueryableData<T, std::list, T, TAllocator>(std::move(items)) { }

  QueryableListData(const QueryableListData& data)
    : QueryableData<T, std::list, T, TAllocator>(data) { }

  virtual ~QueryableListData() { }

  virtual std::shared_ptr<IQueryableData<T>> Clone() override
  {
    return std::make_shared<QueryableListData<T, TAllocator>>(*this);
  }

  void Add(T item) override
  {
    this->items->push_back(item);
    this->size++;
  }

  virtual T & Get(IteratorType type) override
  {
      // std::cout << "Get" << std::endl;
    switch (type)
    {
      
      // case IteratorType::BeginForward: { this->value = &(*this->beginIterator); return *this->value; }
      // case IteratorType::EndForward: { this->value = &(*this->endIterator); return *this->value; }
      // case IteratorType::BeginReverse: { this->value = &(*this->rbeginIterator); return *this->value; }
      // case IteratorType::EndReverse: default: { this->value = &(*this->rendIterator); return *this->value; }
      case IteratorType::BeginForward: { this->value = *this->beginIterator; return this->value; }
      case IteratorType::EndForward: { this->value = *this->endIterator; return this->value; }
      case IteratorType::BeginReverse: { this->value = *this->rbeginIterator; return this->value; }
      case IteratorType::EndReverse: default: { this->value = *this->rendIterator; return this->value; }
    }

    return this->value;
    // std::cout << "Get: " << *this->value << std::endl;
  }

  virtual const T & ConstGet(IteratorType type) override
  {
    switch (type)
    {
      // case IteratorType::BeginForward: { this->value = &(*this->beginIterator); return *this->value; }
      // case IteratorType::EndForward: { this->value = &(*this->endIterator); return *this->value; }
      // case IteratorType::BeginReverse: { this->value = &(*this->rbeginIterator); return *this->value; }
      // case IteratorType::EndReverse: default: { this->value = &(*this->rendIterator); return *this->value; }
      case IteratorType::BeginForward: { this->value = *this->beginIterator; return this->value; }
      case IteratorType::EndForward: { this->value = *this->endIterator; return this->value; }
      case IteratorType::BeginReverse: { this->value = *this->rbeginIterator; return this->value; }
      case IteratorType::EndReverse: default: { this->value = *this->rendIterator; return this->value; }
    }

    return this->value;
  }
};

#endif
