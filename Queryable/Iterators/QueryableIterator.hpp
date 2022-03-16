#ifndef CPPQUERYABLE_QUERYABLE_ITERATORS_QUERYABLEITERATOR_H
#define CPPQUERYABLE_QUERYABLE_ITERATORS_QUERYABLEITERATOR_H

#include <iostream>
#include <memory>

#include "IteratorType.hpp"
#include "IIterable.hpp"
#include "../QueryableData/IQueryableData.hpp"

template<typename T>
class IQueryableData;

template <typename T>
class QueryableIterator
{
private:
  IQueryableData<T> * queryableData;
public:
  uint64_t index;
  IteratorType type;
  // these seem to be needed by the std library
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef T value_type;
  typedef int difference_type;
  typedef T* pointer;
  typedef T& reference;

  QueryableIterator() : index(0) {}

  QueryableIterator(IQueryableData<T> * queryableData, IteratorType type) : QueryableIterator()
  {
    this->queryableData = queryableData;
    this->type = type;
  }

  QueryableIterator(IQueryableData<T> * queryableData, int startingIndex, IteratorType type)
  {
    this->queryableData = queryableData;
    this->index = startingIndex;
    this->type = type;
  }

  QueryableIterator(const QueryableIterator<T> & other)
  {
    this->queryableData = other.queryableData;
    this->index = other.index;
    this->type = other.type;
  }

  inline QueryableIterator<T> & operator=(IQueryableData<T> * queryableData)
  {
    this->queryableData = queryableData;
    return *this;
  }

  inline virtual bool operator==(const QueryableIterator<T>& comparison) const
  {
    // std::cout << "[==] " << this->index  << " vs " << comparison.index << std::endl;
    return this->index == comparison.index;
  }

  inline virtual bool operator!=(const QueryableIterator<T>& comparison) const
  {
    // std::cout << "[!=] " << this->index  << " vs " << comparison.index << std::endl;
    return this->index != comparison.index;
  }

  inline virtual int operator-(const QueryableIterator<T>& subtrahend) const
  {
    return this->index - subtrahend.index;
  }

  inline virtual QueryableIterator<T>& operator=(const QueryableIterator<T>& value)
  {
    this->queryableData = value.queryableData;
    this->index = value.index;
    this->type = value.type;
    return *this;
  }

  inline virtual QueryableIterator<T>& operator++()
  {
    uint64_t iterated = 1;
    this->queryableData->Next(this->type, iterated);
    this->index += iterated;
    return *this;
  }

  inline virtual QueryableIterator<T>& operator--()
  {
    uint64_t iterated = 1;
    this->queryableData->Prev(this->type, iterated);
    this->index -= iterated;
    return *this;
  }

  inline virtual QueryableIterator<T> operator++(int)
  {
    uint64_t iterated = 1;
    this->queryableData->Next(this->type, iterated);
    this->index += iterated;
    return *this;
  }

  inline virtual QueryableIterator<T> operator--(int)
  {
    uint64_t iterated = 1;
    this->queryableData->Prev(this->type, iterated);
    this->index -= iterated;
    return *this;
  }


  inline virtual T& operator*()
  {
    return this->queryableData->Get(this->type);
  }

  inline virtual const T& operator*() const
  {
    return this->queryableData->ConstGet(this->type);
  }

  inline virtual QueryableIterator<T> operator+(int addend)
  {
    this->queryableData->Add(addend, this->type);
    this->index += addend;
    return *this;
  }

  inline virtual QueryableIterator<T>& operator+=(int addend)
  {
    this->queryableData->Add(addend, this->type);
    this->index += addend;
    return *this;
  }

  inline virtual QueryableIterator<T> operator-(int subtrahend)
  {
    this->queryableData->Subtract(subtrahend, this->type);
    this->index -= subtrahend;
    return *this;
  }

  inline virtual QueryableIterator<T>& operator-=(int subtrahend)
  {
    this->queryableData->Subtract(subtrahend, this->type);
    this->index -= subtrahend;
    return *this;
  }
};

#endif
