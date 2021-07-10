#ifndef CPPQUERYABLE_QUERYABLE_CONSTITERATOR_H
#define CPPQUERYABLE_QUERYABLE_CONSTITERATOR_H

#include <iostream>
#include <functional>
#include <iterator>

#include "Iterator.h"

template <typename T>
class ConstIterator : public Iterator<T>
{
public:

  typedef std::bidirectional_iterator_tag iterator_category;
  typedef T value_type;
  typedef std::ptrdiff_t difference_type;
  typedef const T* pointer;
  typedef const T& reference;

  typedef ConstIterator<T> self;

  ConstIterator()
  {
    std::cout << "const assignment 0" << std::endl;
  }
  ConstIterator(const ConstIterator<T>& iterator)
  {
    std::cout << "const assignment 1" << std::endl;
    *this = iterator;
  }
  ConstIterator(ConstIterator<T>& iterator)
  {
    std::cout << "const assignment 2" << std::endl;
    *this = iterator;
  }
  ConstIterator(const Iterator<T>& iterator)
  {
    std::cout << "const assignment 1" << std::endl;
    *this = iterator;
  }
  ConstIterator(Iterator<T>& iterator)
  {
    std::cout << "const assignment 2" << std::endl;
    *this = iterator;
  }

  std::function<void*()> Get;
  std::function<void()> Increment;
  std::function<void()> Decrement;
  std::function<bool(const ConstIterator<T>&)> Equal;
  std::function<T&()> Dereference;
  std::function<const T&()> ConstDereference;


  ConstIterator<T>& operator++()
  {
    this->Increment();
    return *this;
  }

  ConstIterator<T> operator++(int)
  {
    ConstIterator<T> copy = *this;
    this->Increment();
    return copy;
  }

  virtual ConstIterator<T>& operator--()
  {
    this->Decrement();
    return *this;
  }

  ConstIterator<T> operator--(int)
  {
    ConstIterator<T> copy = *this;
    this->Decrement();
    return copy;
  }

  virtual T& operator*()
  {
    return this->Dereference();
  }

  virtual const T& operator*() const
  {
    return this->ConstDereference();
  }

  virtual bool operator==(const ConstIterator<T>& comparison) const
  {
    return this->Equal(comparison);
  }

  virtual bool operator!=(const ConstIterator<T>& comparison) const
  {
    return !this->Equal(comparison);
  }
};

#endif
