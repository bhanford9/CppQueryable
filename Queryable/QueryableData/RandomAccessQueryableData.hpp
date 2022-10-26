#ifndef CPPQUERYABLE_QUERYABLE_RANDOMACCESSQUERYABLEDATA_H
#define CPPQUERYABLE_QUERYABLE_RANDOMACCESSQUERYABLEDATA_H

#include <algorithm>
#include <iostream>
#include <memory>

#include "QueryableData.hpp"

template<
  typename T,
  template<typename, typename ...> typename TIterable,
  typename TAllocator = std::allocator<T>,
  typename ...TArgs>
class RandomAccessQueryableData : public QueryableData<T, TIterable, T, TAllocator, TArgs...>
{
public:
  RandomAccessQueryableData() :
    QueryableData<T, TIterable, T, TAllocator, TArgs...>()
  {
  }

  RandomAccessQueryableData(
    const TIterable<T, TAllocator, TArgs...> & items) :
    QueryableData<T, TIterable, T, TAllocator, TArgs...>(items)
  {
  }

  RandomAccessQueryableData(
    TIterable<T, TAllocator, TArgs...> && items) :
    QueryableData<T, TIterable, T, TAllocator, TArgs...>(std::move(items))
  {
  }

  RandomAccessQueryableData(
    const RandomAccessQueryableData<T, TIterable, TAllocator, TArgs...> & data) :
    QueryableData<T, TIterable, T, TAllocator, TArgs...>(data)
  {
  }

  RandomAccessQueryableData(RandomAccessQueryableData<T, TIterable, TAllocator, TArgs...> && data)
    : QueryableData<T, TIterable, T, TAllocator, TArgs...>(std::move(data))
  {
  }

  virtual ~RandomAccessQueryableData()
  {
  }

  virtual IQueryableData<T> & Add(int addend, IteratorType type) override
  {
    std::cout << "Random Access + Operator, adding: " << addend << std::endl;
    switch (type)
    {
      case IteratorType::BeginForward: this->beginIterator += addend; break;
      case IteratorType::EndForward: this->endIterator += addend; break;
      case IteratorType::BeginReverse: this->rbeginIterator += addend; break;
      case IteratorType::EndReverse: this->rendIterator += addend; break;
    }

    // std::cout << "Random Access add result: " << *this->beginIterator << std::endl;

    return *this;
  }

  virtual IQueryableData<T> & Subtract(int subtrahend, IteratorType type) override
  {
    // std::cout << "Random Access - Operator, adding: " << subtrahend << std::endl;
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
    std::cout << "RAQ Get" << std::endl;
    switch (type)
    {
      case IteratorType::BeginForward: { this->value = &(*this->beginIterator); return *this->value; }
      case IteratorType::EndForward: { this->value = &(*this->endIterator); return *this->value; }
      case IteratorType::BeginReverse: { this->value = &(*this->rbeginIterator); return *this->value; }
      case IteratorType::EndReverse: default: { this->value = &(*this->rendIterator); return *this->value; }
      // case IteratorType::BeginForward: { *this->value = *this->beginIterator; return *this->value; }
      // case IteratorType::EndForward: { *this->value = *this->endIterator; return *this->value; }
      // case IteratorType::BeginReverse: { *this->value = *this->rbeginIterator; return *this->value; }
      // case IteratorType::EndReverse: default: { *this->value = *this->rendIterator; return *this->value; }
    }

    return *this->value;
    // std::cout << "Get: " << *this->value << std::endl;
  }

  virtual const T & ConstGet(IteratorType type) override
  {
    std::cout << "RAQ Const Get" << std::endl;
    switch (type)
    {
      case IteratorType::BeginForward: { this->value = &(*this->beginIterator); return *this->value; }
      case IteratorType::EndForward: { this->value = &(*this->endIterator); return *this->value; }
      case IteratorType::BeginReverse: { this->value = &(*this->rbeginIterator); return *this->value; }
      case IteratorType::EndReverse: default: { this->value = &(*this->rendIterator); return *this->value; }
      // case IteratorType::BeginForward: { *this->value = *this->beginIterator; return *this->value; }
      // case IteratorType::EndForward: { *this->value = *this->endIterator; return *this->value; }
      // case IteratorType::BeginReverse: { *this->value = *this->rbeginIterator; return *this->value; }
      // case IteratorType::EndReverse: default: { *this->value = *this->rendIterator; return *this->value; }
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
