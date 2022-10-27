#ifndef CPPQUERYABLE_QUERYABLE_CONSTRANDOMACCESSQUERYABLEDATA_H
#define CPPQUERYABLE_QUERYABLE_CONSTRANDOMACCESSQUERYABLEDATA_H

#include <algorithm>
#include <iostream>
#include <memory>

#include "QueryableData.hpp"

template<
  typename T,
  template<typename, typename ...> typename TIterable,
  typename TAllocator = std::allocator<T>,
  typename ...TArgs>
class ConstRandomAccessQueryableData : public QueryableData<T, TIterable, T, TAllocator, TArgs...>
{
public:
  ConstRandomAccessQueryableData() :
    QueryableData<T, TIterable, T, TAllocator, TArgs...>()
  {
  }

  ConstRandomAccessQueryableData(
    const TIterable<T, TAllocator, TArgs...> & items) :
    QueryableData<T, TIterable, T, TAllocator, TArgs...>(items)
  {
  }

  ConstRandomAccessQueryableData(
    TIterable<T, TAllocator, TArgs...> && items) :
    QueryableData<T, TIterable, T, TAllocator, TArgs...>(std::move(items))
  {
  }

  ConstRandomAccessQueryableData(
    const ConstRandomAccessQueryableData<T, TIterable, TAllocator, TArgs...> & data) :
    QueryableData<T, TIterable, T, TAllocator, TArgs...>(data)
  {
  }

  ConstRandomAccessQueryableData(ConstRandomAccessQueryableData<T, TIterable, TAllocator, TArgs...> && data)
    : QueryableData<T, TIterable, T, TAllocator, TArgs...>(std::move(data))
  {
  }

  virtual ~ConstRandomAccessQueryableData()
  {
  }

  virtual IQueryableData<T> & Add(int addend, IteratorType type) override
  {
    // std::cout << "ConstRandom Access + Operator, adding: " << addend << std::endl;
    switch (type)
    {
      case IteratorType::BeginForward: this->cbeginIterator += addend; break;
      case IteratorType::EndForward: this->cendIterator += addend; break;
      case IteratorType::BeginReverse: this->crbeginIterator += addend; break;
      case IteratorType::EndReverse: this->crendIterator += addend; break;
    }

    // std::cout << "ConstRandom Access add result: " << *this->beginIterator << std::endl;

    return *this;
  }

  virtual IQueryableData<T> & Subtract(int subtrahend, IteratorType type) override
  {
    // std::cout << "ConstRandom Access - Operator, adding: " << subtrahend << std::endl;
    switch (type)
    {
      case IteratorType::BeginForward: this->cbeginIterator -= subtrahend; break;
      case IteratorType::EndForward: this->cendIterator -= subtrahend; break;
      case IteratorType::BeginReverse: this->crbeginIterator -= subtrahend; break;
      case IteratorType::EndReverse: this->crendIterator -= subtrahend; break;
    }

    return *this;
  }

  virtual T & Get(IteratorType type) override
  {
      // std::cout << "Get" << std::endl;
    switch (type)
    {
      case IteratorType::BeginForward: { return (T&)*this->cbeginIterator; }
      case IteratorType::EndForward: { return (T&)*this->cendIterator; }
      case IteratorType::BeginReverse: { return (T&)*this->crbeginIterator; }
      case IteratorType::EndReverse: default: { return (T&)*this->crendIterator; }
    }

    return *this->value;
    // std::cout << "Get: " << *this->value << std::endl;
  }

  virtual const T & ConstGet(IteratorType type) override
  {
    switch (type)
    {
      case IteratorType::BeginForward: { return *this->cbeginIterator; }
      case IteratorType::EndForward: { return *this->cendIterator; }
      case IteratorType::BeginReverse: { return *this->crbeginIterator; }
      case IteratorType::EndReverse: default: { return *this->crendIterator; }
    }

    return *this->value;
  }

  void Add(T item) override
  {
    this->items->push_back(item);
    this->size++;
  }
};

#endif
