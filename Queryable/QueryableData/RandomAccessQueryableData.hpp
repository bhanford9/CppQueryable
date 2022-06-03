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
class RandomAccessQueryableData : public QueryableData<T, TIterable, TAllocator, TArgs...>
{
public:
  RandomAccessQueryableData() : QueryableData<T, TIterable, TAllocator, TArgs...>()
  {
  }

  // RandomAccessQueryableData(TIterable<T, TAllocator, TArgs...> items)
  //   : QueryableData<T, TIterable, TAllocator, TArgs...>(items)
  // {
  // }

  RandomAccessQueryableData(const TIterable<T, TAllocator, TArgs...> & items)
    : QueryableData<T, TIterable, TAllocator, TArgs...>(items)
  {
  }

  RandomAccessQueryableData(TIterable<T, TAllocator, TArgs...> && items)
    : QueryableData<T, TIterable, TAllocator, TArgs...>(std::move(items))
  {
  }

  RandomAccessQueryableData(const RandomAccessQueryableData<T, TIterable, TAllocator, TArgs...> & data)
    : QueryableData<T, TIterable, TAllocator, TArgs...>(data)
  {
  }

  RandomAccessQueryableData(RandomAccessQueryableData<T, TIterable, TAllocator, TArgs...> && data)
    : QueryableData<T, TIterable, TAllocator, TArgs...>(std::move(data))
  {
  }

  virtual ~RandomAccessQueryableData() { }

  virtual IQueryableData<T> & Add(int addend, IteratorType type) override
  {
    std::cout << "Random Access + Operator, adding: " << addend << ", value: " << *this->beginIterator << std::endl;
    switch (type)
    {
      case IteratorType::BeginForward: this->beginIterator += addend; break;
      case IteratorType::EndForward: this->endIterator += addend; break;
      case IteratorType::BeginReverse: this->rbeginIterator += addend; break;
      case IteratorType::EndReverse: this->rendIterator += addend; break;
    }

    return *this;
  }

  virtual IQueryableData<T> & Subtract(int subtrahend, IteratorType type) override
  {
    std::cout << "Random Access - Operator, adding: " << subtrahend << std::endl;
    switch (type)
    {
      case IteratorType::BeginForward: this->beginIterator -= subtrahend; break;
      case IteratorType::EndForward: this->endIterator -= subtrahend; break;
      case IteratorType::BeginReverse: this->rbeginIterator -= subtrahend; break;
      case IteratorType::EndReverse: this->rendIterator -= subtrahend; break;
    }

    return *this;
  }

  void Add(T item) override
  {
    this->items->push_back(item);
    this->size++;
  }

  virtual T & Get(IteratorType type) override
  {
    switch (type)
    {
        case IteratorType::BeginForward: { this->value = *this->beginIterator; return *this->beginIterator; }
        case IteratorType::EndForward: { this->value = *this->endIterator; return *this->endIterator; }
        case IteratorType::BeginReverse: { this->value = *this->rbeginIterator; return *this->rbeginIterator; }
        case IteratorType::EndReverse: default: { this->value = *this->rendIterator; return *this->rendIterator; }
    }
  }
};

#endif
