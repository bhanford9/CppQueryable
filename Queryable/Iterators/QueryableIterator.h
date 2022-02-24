#ifndef CPPQUERYABLE_QUERYABLE_ITERATORS_QUERYABLEITERATOR_H
#define CPPQUERYABLE_QUERYABLE_ITERATORS_QUERYABLEITERATOR_H

#include <iostream>
#include <memory>

#include "IteratorType.h"
#include "IIterable.h"
#include "../QueryableData/IQueryableIteratorData.h"

template<typename T>
class IIterable;

template <typename T>
class QueryableIterator// : public IIterable<T>
{
private:
  IQueryableIteratorData<T> * queryableData;
  // std::shared_ptr<IQueryableIteratorData<T>> queryableData;
public:
  uint64_t index;
  // these seem to be needed by the std library
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef T value_type;
  typedef int difference_type;
  typedef T* pointer;
  typedef T& reference;

  QueryableIterator() : index(0) {}

  QueryableIterator(IQueryableIteratorData<T> * queryableData) : QueryableIterator()
  {
    this->queryableData = queryableData;
  }

  QueryableIterator(IQueryableIteratorData<T> * queryableData, int startingIndex)
  {
    this->queryableData = queryableData;
    this->index = startingIndex;
  }

  inline QueryableIterator<T> & operator=(IQueryableIteratorData<T> * queryableData)
  {
    this->queryableData = queryableData;
    return *this;
  }

  inline virtual bool operator==(const QueryableIterator<T>& comparison) const
  {
    return this->index == comparison.index;
  }

  inline virtual bool operator!=(const QueryableIterator<T>& comparison) const
  {
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
    return *this;
  }

  inline virtual QueryableIterator<T>& operator++()
  {
    this->queryableData->Next();
    this->index++;
    return *this;
  }

  inline virtual QueryableIterator<T>& operator--()
  {
    this->queryableData->Prev();
    this->index--;
    return *this;
  }


  inline virtual T& operator*()
  {
    return this->queryableData->Get();
  }

  inline virtual const T& operator*() const
  {
    return this->queryableData->ConstGet();
  }

  inline virtual QueryableIterator<T> operator+(int addend)
  {
    this->queryableData->Add(addend);
    this->index += addend;
    return *this;
  }

  inline virtual QueryableIterator<T>& operator+=(int addend)
  {
    this->queryableData->Add(addend);
    this->index += addend;
    return *this;
  }

  inline virtual QueryableIterator<T> operator-(int subtrahend)
  {
    this->queryableData->Subtract(subtrahend);
    this->index -= subtrahend;
    return *this;
  }

  inline virtual QueryableIterator<T>& operator-=(int subtrahend)
  {
    this->queryableData->Subtract(subtrahend);
    this->index -= subtrahend;
    return *this;
  }
};

#endif
