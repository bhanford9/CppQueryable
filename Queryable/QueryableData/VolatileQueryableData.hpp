#ifndef CPPQUERYABLE_QUERYABLE_VOLATILEQUERYABLEDATA_H
#define CPPQUERYABLE_QUERYABLE_VOLATILEQUERYABLEDATA_H

#include <algorithm>
#include <memory>

#include "QueryableData.hpp"

template<
  typename T,
  template<typename, typename ...> typename TIterable,
  typename TAllocator = std::allocator<T>,
  typename ...TArgs>
class VolatileQueryableData : public QueryableData<T, TIterable, T, TAllocator, TArgs...>
{
public:
  VolatileQueryableData() :
    QueryableData<T, TIterable, T, TAllocator, TArgs...>()
  {
  }

  VolatileQueryableData(
    const TIterable<T, TAllocator, TArgs...> & items) :
    QueryableData<T, TIterable, T, TAllocator, TArgs...>(items)
  {
  }

  VolatileQueryableData(
    TIterable<T, TAllocator, TArgs...> && items) :
    QueryableData<T, TIterable, T, TAllocator, TArgs...>(std::move(items))
  {
  }

  VolatileQueryableData(
    const VolatileQueryableData<T, TIterable, TAllocator, TArgs...> & data) :
    QueryableData<T, TIterable, T, TAllocator, TArgs...>(data)
  {
  }

  VolatileQueryableData(VolatileQueryableData<T, TIterable, TAllocator, TArgs...> && data)
    : QueryableData<T, TIterable, T, TAllocator, TArgs...>(std::move(data))
  {
  }

  virtual ~VolatileQueryableData()
  {
  }

  virtual IQueryableData<T> & Add(int addend, IteratorType type) override
  {
    // std::cout << "ConstRandom Access + Operator, adding: " << addend << std::endl;
    switch (type)
    {
      case IteratorType::BeginForward: this->beginIterator += addend; break;
      case IteratorType::EndForward: this->endIterator += addend; break;
      case IteratorType::BeginReverse: this->rbeginIterator += addend; break;
      case IteratorType::EndReverse: this->rendIterator += addend; break;
    }

    // std::cout << "ConstRandom Access add result: " << *this->beginIterator << std::endl;

    return *this;
  }

  virtual IQueryableData<T> & Subtract(int subtrahend, IteratorType type) override
  {
    // std::cout << "ConstRandom Access - Operator, adding: " << subtrahend << std::endl;
    switch (type)
    {
      case IteratorType::BeginForward: this->beginIterator -= subtrahend; break;
      case IteratorType::EndForward: this->endIterator -= subtrahend; break;
      case IteratorType::BeginReverse: this->rbeginIterator -= subtrahend; break;
      case IteratorType::EndReverse: this->rendIterator -= subtrahend; break;
    }

    return *this;
  }

  virtual T & Get(IteratorType type) override
  {
      // std::cout << "Get" << std::endl;
    switch (type)
    {
      case IteratorType::BeginForward: { return (T&)*this->beginIterator; }
      case IteratorType::EndForward: { return (T&)*this->endIterator; }
      case IteratorType::BeginReverse: { return (T&)*this->rbeginIterator; }
      case IteratorType::EndReverse: default: { return (T&)*this->rendIterator; }
    }

    return *this->value;
    // std::cout << "Get: " << *this->value << std::endl;
  }

  virtual const T & ConstGet(IteratorType type) override
  {
    switch (type)
    {
      case IteratorType::BeginForward: { return *this->beginIterator; }
      case IteratorType::EndForward: { return *this->endIterator; }
      case IteratorType::BeginReverse: { return *this->rbeginIterator; }
      case IteratorType::EndReverse: default: { return *this->rendIterator; }
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
