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
// protected:
//   TAllocator allocator;

public:
  RandomAccessQueryableData() :
    QueryableData<T, TIterable, TAllocator, TArgs...>()
  {
  }

  // RandomAccessQueryableData(TIterable<T, TAllocator, TArgs...> items)
  //   : QueryableData<T, TIterable, TAllocator, TArgs...>(items)
  // {
  // }

  RandomAccessQueryableData(
    const TIterable<T, TAllocator, TArgs...> & items) :
    QueryableData<T, TIterable, TAllocator, TArgs...>(items)
  {
  }

  RandomAccessQueryableData(
    TIterable<T, TAllocator, TArgs...> && items) :
    QueryableData<T, TIterable, TAllocator, TArgs...>(std::move(items))
  {
  }

  RandomAccessQueryableData(
    const RandomAccessQueryableData<T, TIterable, TAllocator, TArgs...> & data) :
    QueryableData<T, TIterable, TAllocator, TArgs...>(data)
  {
  }

  RandomAccessQueryableData(RandomAccessQueryableData<T, TIterable, TAllocator, TArgs...> && data)
    : QueryableData<T, TIterable, TAllocator, TArgs...>(std::move(data))
  {
  }

//   RandomAccessQueryableData(
//     const TIterable<T, TAllocator, TArgs...> & items,
//     TAllocator allocator = {}) :
//     QueryableData<T, TIterable, TAllocator, TArgs...>(items),
//     allocator(allocator)
//   {
//     this->value = this->allocator.allocate(1);
//   }

//   RandomAccessQueryableData(
//     TIterable<T, TAllocator, TArgs...> && items,
//     TAllocator allocator = {}) :
//     QueryableData<T, TIterable, TAllocator, TArgs...>(std::move(items)),
//     allocator(allocator)
//   {
//     this->value = this->allocator.allocate(1);
//   }

//   RandomAccessQueryableData(
//     const RandomAccessQueryableData<T, TIterable, TAllocator, TArgs...> & data,
//     TAllocator allocator = {}) :
//     QueryableData<T, TIterable, TAllocator, TArgs...>(data)
//   {
//     this->value = this->allocator.allocate(1);
//   }

//   RandomAccessQueryableData(RandomAccessQueryableData<T, TIterable, TAllocator, TArgs...> && data)
//     : QueryableData<T, TIterable, TAllocator, TArgs...>(std::move(data)),
//     allocator(allocator)
//   {
//     this->value = this->allocator.allocate(1);
//   }

  virtual ~RandomAccessQueryableData()
  {
    // this->value only gets assigned by this->allocator.allocate which either returns a non-null
    //   value or it throws an exception
    // all other instances of this->value are copy returns or assignements to the value at its address
    // therefore, this check shouldn't be necessary
    // if (this->value != NULL)
    // {
    //   this->allocator.deallocate(this->value, 1);
    // }
  }

  virtual IQueryableData<T> & Add(int addend, IteratorType type) override
  {
    // std::cout << "Random Access + Operator, adding: " << addend << std::endl;
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

  void Add(T item) override
  {
    this->items->push_back(item);
    this->size++;
  }

  // TODO --> don't think this actually needs overriden
//   virtual T & Get(IteratorType type) override
//   {
//     switch (type)
//     {
//         case IteratorType::BeginForward: { *this->value = *this->beginIterator; return *this->beginIterator; }
//         case IteratorType::EndForward: { *this->value = *this->endIterator; return *this->endIterator; }
//         case IteratorType::BeginReverse: { *this->value = *this->rbeginIterator; return *this->rbeginIterator; }
//         case IteratorType::EndReverse: default: { *this->value = *this->rendIterator; return *this->rendIterator; }
//     }
//   }
};

#endif
