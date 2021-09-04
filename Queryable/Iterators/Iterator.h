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
  uint64_t index = 0;

public:

  typedef std::bidirectional_iterator_tag iterator_category;
  typedef T value_type;
  typedef int difference_type;
  typedef T* pointer;
  typedef T& reference;

  Iterator() {}

  std::function<void*()> Get;
  std::function<void(uint64_t & index)> Increment;
  std::function<void(uint64_t & index)> Decrement;
  std::function<T&()> Dereference;
  std::function<const T&()> ConstDereference;
  std::function<void(const Iterator<T>&)> Assign;

  uint64_t & GetIndex() { return this->index; }
  void SetIndex(uint64_t index) { this->index = index; }
  void IncrementIndex() { this->index++; }
  void DecrementIndex() { this->index--; }

  Iterator<T>& operator++()
  {
    this->index++;

    this->Increment(this->index);
    return *this;
  }

  Iterator<T> operator++(int)
  {
    this->index++;

    Iterator<T> copy = *this;
    this->Increment(this->index);
    return copy;
  }

  Iterator<T>& operator--()
  {
    this->index--;

    this->Decrement(this->index);
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
    return this->index == comparison.index;
  }

  bool operator!=(const Iterator<T>& comparison) const
  {
    return this->index != comparison.index;
  }

  Iterator<T>& operator=(const Iterator<T>& value)
  {
    this->Assign(value);
    this->index = value.index;
    return *this;
  }
};

#endif
