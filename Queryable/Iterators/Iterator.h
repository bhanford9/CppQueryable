#ifndef CPPQUERYABLE_QUERYABLE_ITERATORS_LISTITERATOR_H
#define CPPQUERYABLE_QUERYABLE_ITERATORS_LISTITERATOR_H

#include <chrono>
#include <functional>
#include <iostream>
#include <iterator>

template <typename T>
class Iterator
{
private:

public:

  typedef std::bidirectional_iterator_tag iterator_category;
  typedef T value_type;
  typedef int difference_type;
  typedef T* pointer;
  typedef T& reference;


  typedef std::chrono::high_resolution_clock THighRes;
  typedef std::chrono::time_point<THighRes> TTime;

  Iterator()
  {
  }

  std::function<void*()> Get;
  std::function<void()> Increment;
  std::function<void()> Decrement;
  std::function<bool(const Iterator<T>&)> Equal;
  std::function<T&()> Dereference;
  std::function<const T&()> ConstDereference;
  std::function<void(const Iterator<T>&)> Assign;

  virtual Iterator<T>& operator++()
  {
    this->Increment();
    return *this;
  }

  Iterator<T> operator++(int)
  {
    Iterator<T> copy = *this;
    this->Increment();
    return copy;
  }

  Iterator<T>& operator--()
  {
    this->Decrement();
    return *this;
  }

  T& operator*()
  {
    return this->Dereference();
  }

  const T& operator*() const
  {
    return this->ConstDereference();
  }

  bool operator==(const Iterator<T>& comparison) const
  {
    return this->Equal(comparison);
  }

  bool operator!=(const Iterator<T>& comparison) const
  {
    bool notEqual = !this->Equal(comparison);
    return notEqual;
  }

  Iterator<T>& operator=(const Iterator<T>& value)
  {
    this->Assign(value);
    return *this;
  }
};

#endif
