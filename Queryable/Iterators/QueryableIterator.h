#ifndef CPPQUERYABLE_QUERYABLE_ITERATORS_QUERYABLEITERATOR_H
#define CPPQUERYABLE_QUERYABLE_ITERATORS_QUERYABLEITERATOR_H

#include <iostream>
#include <memory>

#include "IteratorType.h"

template <typename T>
class QueryableIterator
{
public:
  IteratorType type;

  // only way to compare two iterators is going to be by their index
  uint64_t index;

  // these seem to be needed by the std library
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef T value_type;
  typedef int difference_type;
  typedef T* pointer;
  typedef T& reference;

  QueryableIterator() :
    type(IteratorType::BeginForward)
  {
  }


  // These methods are all intended to be overriden, but be inilned for speed optimization
  // Making them pure virtual would make the class abstract and would not work with the begin/end methods
  // I am hoping that I can inherit from CppQueryableData and cast itself to return a copy
  //   if this does not work, then the begin/end methods will have to be pushed all the way down to the lowest children
  inline virtual QueryableIterator<T> begin()
  {
    return *this;
  }

  inline virtual QueryableIterator<T> end()
  {
    return *this;
  }

  inline virtual QueryableIterator<T> rbegin()
  {
    return *this;
  }

  inline virtual QueryableIterator<T> rend()
  {
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

  // inline virtual bool operator<(const QueryableIterator<T>& other) const
  // {
  //   return false;
  // }

  inline virtual QueryableIterator<T>& operator++()
  {
    return *this;
  }

  inline virtual QueryableIterator<T>& operator--()
  {
    return *this;
  }


  inline virtual const T& operator*()
  {
    std::cout << "within fake deref 1" << std::endl;
    std::shared_ptr<T> fake;
    return *fake;
  }

  inline virtual const T& operator*() const
  {
    std::cout << "within fake deref 2" << std::endl;
    std::shared_ptr<T> fake;
    return *fake;
  }

  inline virtual QueryableIterator<T>& operator+(int addend)
  {
    return *this;
  }

  inline virtual QueryableIterator<T>& operator+=(int addend)
  {
    return *this;
  }

  inline virtual QueryableIterator<T>& operator-(int subtrahend)
  {
    return *this;
  }

  inline virtual QueryableIterator<T>& operator-=(int subtrahend)
  {
    return *this;
  }

  inline virtual QueryableIterator<T>& operator=(const QueryableIterator<T>& value)
  {
    return *this;
  }
};

#endif
