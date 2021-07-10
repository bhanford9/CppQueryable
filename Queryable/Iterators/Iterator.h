#ifndef CPPQUERYABLE_QUERYABLE_LISTITERATOR_H
#define CPPQUERYABLE_QUERYABLE_LISTITERATOR_H

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
  typedef std::ptrdiff_t difference_type;
  typedef T* pointer;
  typedef T& reference;

  Iterator() { }
  Iterator(const Iterator<T>& iterator)
  {
    *this = iterator;
  }
  Iterator(
    std::function<void*()> get,
    std::function<void()> increment,
    std::function<void()> decrement,
    std::function<bool(const Iterator<T>&)> equal,
    std::function<T&()> dereference,
    std::function<const T&()> constDereference
  )
  {
    this->Get = get;
    this->Increment = increment;
    this->Decrement = decrement;
    this->Equal = equal;
    this->Dereference = dereference;
    this->ConstDereference = constDereference;
  }

  std::function<void*()> Get;
  std::function<void()> Increment;
  std::function<void()> Decrement;
  std::function<bool(const Iterator<T>&)> Equal;
  std::function<T&()> Dereference;
  std::function<const T&()> ConstDereference;


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

  virtual Iterator<T>& operator--()
  {
    this->Decrement();
    return *this;
  }

  virtual T& operator*()
  {
    return this->Dereference();
  }

  virtual const T& operator*() const
  {
    return this->ConstDereference();
  }

  virtual bool operator==(const Iterator<T>& comparison) const
  {
    return this->Equal(comparison);
  }

  virtual bool operator!=(const Iterator<T>& comparison) const
  {
    return !this->Equal(comparison);
  }
};

#endif
