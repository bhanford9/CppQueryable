#ifndef CPPQUERYABLE_QUERYABLE_ITERATORS_QUERYABLEITERATOR_H
#define CPPQUERYABLE_QUERYABLE_ITERATORS_QUERYABLEITERATOR_H

#include <iostream>
#include <memory>

#include "IteratorType.hpp"
#include "../QueryableData/IQueryableData.hpp"

template<typename T>
class IQueryableData;

template <typename T>
class QueryableIterator
{
private:
  std::shared_ptr<IQueryableData<T>> queryableData;
public:
  // TODO --> make private add an accessor
  // TODO --> this should probably be size_t
  uint64_t index;
  IteratorType type;
  // these seem to be needed by the std library
  typedef std::random_access_iterator_tag iterator_category;
  typedef T value_type;
  typedef int difference_type;
  typedef T* pointer;
  typedef T& reference;

  QueryableIterator() : index(0)
  {
    // std::cout << "QueryableIterator constructor 0" << std::endl;
  }

  QueryableIterator(std::shared_ptr<IQueryableData<T>> queryableData, IteratorType type) : QueryableIterator()
  {
    // std::cout << "QueryableIterator constructor 1" << std::endl;
    this->queryableData = queryableData->Clone();
    this->type = type;
  }

  QueryableIterator(std::shared_ptr<IQueryableData<T>> queryableData, int startingIndex, IteratorType type)
  {
    // std::cout << "QueryableIterator constructor 2, starting index: " << startingIndex << std::endl;
    this->queryableData = queryableData->Clone();
    this->index = startingIndex;
    this->type = type;
  }

  QueryableIterator(const QueryableIterator<T> & other)
  {
    // std::cout << "QueryableIterator constructor 3, index: " << other.index << std::endl;
    this->queryableData = other.queryableData->Clone();
    this->index = other.index;
    this->type = other.type;
  }

  QueryableIterator(QueryableIterator<T> && other) :
    queryableData(other.queryableData->Clone()),
    index(other.index),
    type(other.type)
  {
    // std::cout << "QueryableIterator constructor 4" << std::endl;
    // std::cout << "Iterator move constructor" << std::endl;
  }

// start std::sort requirements
  inline bool operator<(const QueryableIterator<T> & other) const
  {
    // std::cout << "iterator less than comparison. self: " << this->index << ", other: " << other.index << std::endl;
    return this->index < other.index;
  }

  inline bool operator>(const QueryableIterator<T> & other) const
  {
    // std::cout << "iterator greater than comparison. self: " << this->index << ", other: " << other.index << std::endl;
    return this->index > other.index;
  }

  inline bool operator<=(const QueryableIterator<T> & other) const
  {
    // std::cout << "iterator less than or equal to comparison. self: " << this->index << ", other: " << other.index << std::endl;
    return this->index <= other.index;
  }

  inline bool operator>=(const QueryableIterator<T> & other) const
  {
    // std::cout << "iterator greater than or equal to comparison. self: " << this->index << ", other: " << other.index << std::endl;
    return this->index >= other.index;
  }

  inline T & operator[](int index) const
  {
    // std::cout << "[] self: " << this->index << ", incoming index: " << index << std::endl;
    QueryableIterator<T> copy = *this;
    return *(copy + index);
  }
// end std::sort requirements

  inline T * operator->() const
  {
    // std::cout << "-> operator" << std::endl;
    return &this->queryableData->Get(this->type);
  }

  inline QueryableIterator<T> & operator=(IQueryableData<T> * queryableData)
  {
    // std::cout << "\n\nthis is probably bad\n\n" << std::endl;
    this->queryableData = queryableData;
    return *this;
  }

  virtual bool operator==(const QueryableIterator<T>& comparison) const
  {
    // std::cout << "[==] " << this->index  << " vs " << comparison.index << std::endl;
    return this->index == comparison.index;
  }

  virtual bool operator!=(const QueryableIterator<T>& comparison) const
  {
    // std::cout << "[!=] " << this->index  << " vs " << comparison.index << std::endl;
    return this->index != comparison.index;
  }

  virtual int operator-(const QueryableIterator<T>& subtrahend) const
  {
    // std::cout << "iterator subtraction (1). self: " << this->index << ", other: " << subtrahend.index << std::endl;
    // std::cout << "\tsubtraction result: " << (this->index - subtrahend.index) << std::endl;;
    return this->index - subtrahend.index;
  }

  virtual QueryableIterator<T>& operator=(const QueryableIterator<T>& value)
  {
    //   std::cout << "start assignment" << std::endl;
    // std::cout << "within assignment operator"
    //   << "\n\tindex: " << value.index
    //   << "\n\tvalue: " << value.queryableData->Get(value.type)
    //   << std::endl;
    this->queryableData = value.queryableData->Clone();
    this->index = value.index;
    this->type = value.type;
    return *this;
  }

  virtual QueryableIterator<T>& operator=(QueryableIterator<T> && value)
  {
    // std::cout << "within move operator" << std::endl;
    this->queryableData = std::move(value.queryableData->Clone());
    this->index = value.index;
    this->type = value.type;
    return *this;
  }

  virtual QueryableIterator<T>& operator++()
  {
    //   std::cout << "start ++" << std::endl;
    // std::cout << "in operator++"
    //   << "\n\tCurrent Index: " << this->index
    //   << "\n\tId: " << this->queryableData->myId
    //   << "\n\tCurrent Value: " << this->queryableData->Get(this->type)
    //   << std::endl;
    uint64_t iterated = 1;
    bool isForcingToEnd = false;
    this->queryableData->Next(this->type, iterated, isForcingToEnd);

    if (isForcingToEnd)
    {
      // size was sent back within iterated
      this->index = iterated;
    }
    else
    {
      this->index += iterated;
    }

    // std::cout << "out operator++"
    //   << "\n\tCurrent Index: " << this->index
    //   << "\n\tId: " << this->queryableData->myId
    //   << "\n\tCurrent Value: " << this->queryableData->Get(this->type)
    //   << std::endl;
    return *this;
  }

  virtual QueryableIterator<T>& operator--()
  {
    //   std::cout << "start --" << std::endl;
    // std::cout << "in operator--"
    //   << "\n\tCurrent Index: " << this->index
    //   << "\n\tId: " << this->queryableData->myId
    //   << "\n\tCurrent Value: " << this->queryableData->Get(this->type)
    //   << std::endl;
    uint64_t iterated = 1;
    this->queryableData->Prev(this->type, iterated);

    this->index -= iterated;

    // std::cout << "out operator--"
    //   << "\n\tCurrent Index: " << this->index
    //   << "\n\tId: " << this->queryableData->myId
    //   << "\n\tCurrent Value: " << this->queryableData->Get(this->type)
    //   << std::endl;
    return *this;
  }

  virtual QueryableIterator<T> operator++(int)
  {
    // std::cout << "++(int)" << std::endl;
    QueryableIterator<T> copy(*this);
    (*this)++;
    return copy;
  }

  virtual QueryableIterator<T> operator--(int)
  {
    // std::cout << "--(int)" << std::endl;
    QueryableIterator<T> copy(*this);
    (*this)--;
    return copy;
  }

  virtual T& operator*()
  {
    //   std::cout << "starting *" << std::endl;
    // std::cout << "deref, addr: " << this << ", index: " << this->index << ", value: " << this->queryableData->Get(this->type) << std::endl;
    T& value = this->queryableData->Get(this->type);
    // std::cout << "back from get" << std::endl;
    return value;
  }

  virtual const T& operator*() const
  {
    //   std::cout << "starting const *" << std::endl;
    // std::cout << "const deref, index: " << this->index << ", value: " << this->queryableData->Get(this->type) << std::endl;
    return this->queryableData->ConstGet(this->type);
  }

  virtual QueryableIterator<T> operator+(int addend)
  {
    // std::cout << "+(int) copy" << std::endl;
    QueryableIterator<T> copy(this->queryableData, this->index, this->type);
    (*this) += addend;
    return copy;
  }

  virtual QueryableIterator<T>& operator+=(int addend)
  {
    // std::cout << "operator +=" << std::endl;
    this->queryableData->Add(addend, this->type);
    this->index += addend;
    return *this;
  }

  virtual QueryableIterator<T> operator-(int subtrahend)
  {
    // std::cout << "-(int) copy" << std::endl;
    QueryableIterator<T> copy(this->queryableData, this->index, this->type);
    (*this) -= subtrahend;
    return copy;
  }

  virtual QueryableIterator<T>& operator-=(int subtrahend)
  {
    // std::cout << "operator -=" << std::endl;
    this->queryableData->Subtract(subtrahend, this->type);
    this->index -= subtrahend;
    return *this;
  }
};

#endif
