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

  Iterator() : Index(0) {}

  std::function<void*()> Get;
  std::function<void(uint64_t & index)> Increment;
  std::function<void(uint64_t & index)> Decrement;
  std::function<T&()> Dereference;
  std::function<const T&()> ConstDereference;
  std::function<void(const Iterator<T>&)> Assign;

  // intentionally public
  uint64_t Index = 0;

  Iterator<T>& operator++()
  {
    this->Index++;

    this->Increment(this->Index);
    return *this;
  }

  // Iterator<T> operator++(int)
  // {
  //   this->Index++;
  //
  //   Iterator<T> copy = *this;
  //   this->Increment(this->Index);
  //   return copy;
  // }

  Iterator<T>& operator--()
  {
    this->Index--;

    this->Decrement(this->Index);
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
    return this->Index == comparison.Index;
  }

  bool operator!=(const Iterator<T>& comparison) const
  {
    return this->Index != comparison.Index;
  }

  Iterator<T>& operator=(const Iterator<T>& value)
  {
    this->Get = value.Get;
    this->Increment = value.Increment;
    this->Decrement = value.Decrement;
    this->Dereference = value.Dereference;
    this->ConstDereference = value.ConstDereference;
    this->Assign = value.Assign;
    this->Index = value.Index;
    this->Assign(value);
    return *this;
  }
};

#endif
