#ifndef CPPQUERYABLE_QUERYABLE_ITERATORS_LISTITERATOR_H
#define CPPQUERYABLE_QUERYABLE_ITERATORS_LISTITERATOR_H

#include <chrono>
#include <stdexcept>
#include <functional>
#include <iostream>
#include <iterator>

#include "../Utilities/Backtrace.h"

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

  Iterator()
  {
    // std::cout << "iterator deault constructor" << std::endl;
  }

  Iterator(const Iterator<T> && other)
  {
    // std::cout << "\t\t\titerator move constructor" << std::endl;
    this->Get = std::move(other.Get);
    this->Increment = std::move(other.Increment);
    this->Decrement = std::move(other.Decrement);
    this->Dereference = std::move(other.Dereference);
    this->ConstDereference = std::move(other.ConstDereference);
    this->Assign = std::move(other.Assign);
    this->Add = std::move(other.Add);
    this->Subtract = std::move(other.Subtract);
    this->Index = std::move(other.Index);
  }

  Iterator(const Iterator<T> & other)
  {
    // std::cout << "\t\t\titerator copy constructor" << std::endl;
    this->Get = other.Get;
    this->Increment = other.Increment;
    this->Decrement = other.Decrement;
    this->Dereference = other.Dereference;
    this->ConstDereference = other.ConstDereference;
    this->Assign = other.Assign;
    this->Add = other.Add;
    this->Subtract = other.Subtract;
    this->Index = other.Index;
  }

  std::function<void*()> Get;
  std::function<void(int64_t & index)> Increment;
  std::function<void(int64_t & index)> Decrement;
  std::function<T&()> Dereference;
  std::function<const T&()> ConstDereference;
  std::function<void(const Iterator<T>&)> Assign;

  // random access iterators only
  std::function<void(int addend, int64_t & index)> Add;
  std::function<void(int subtrahend, int64_t & index)> Subtract;

  // intentionally public
  int64_t Index = 0;

  Iterator<T>& operator++()
  {
    this->Index++;

    // std::cout << "++ index; " << this->Index << std::endl;

    this->Increment(this->Index);
    return *this;
  }

  Iterator<T>& operator--()
  {
    this->Index--;
      // std::cout << "-- index; " << this->Index << std::endl;


    // std::cout << "calling Dereference: " << std::endl;
    this->Dereference();
    this->Decrement(this->Index);
    return *this;
  }

  T& operator*()
  {
    // if (this->Index > 15)
    // {
    //   throw std::exception();
    // }
    // std::cout << "* index; " << this->Index << std::endl;
    return this->Dereference();
  }

  const T& operator*() const
  {
    // std::cout << "c* index; " << this->Index << std::endl;
    return this->ConstDereference();
  }

  bool operator==(const Iterator<T>& comparison) const
  {
    // std::cout << "== index; " << this->Index << std::endl;
    return this->Index == comparison.Index;
  }

  bool operator!=(const Iterator<T>& comparison) const
  {
    // std::cout << "!= index; " << this->Index << std::endl;
    return this->Index != comparison.Index;
  }

  int operator-(const Iterator<T>& subtrahend) const
  {
    // std::cout << "-o index; " << this->Index << std::endl;
    return this->Index - subtrahend.Index;
  }

  Iterator<T>& operator+(int addend)
  {
    // std::cout << "+i index; " << this->Index << std::endl;
    this->Add(addend, this->Index);
    return *this;
  }

  Iterator<T>& operator+=(int addend)
  {
    // std::cout << "in +=" << std::endl;

    this->Add(addend, this->Index);
    // std::cout << "add complete" << std::endl;
    return *this;
  }

  Iterator<T>& operator-(int subtrahend)
  {
    // std::cout << "-i index; " << this->Index << std::endl;
    this->Subtract(subtrahend, this->Index);
    return *this;
  }

  Iterator<T>& operator-=(int subtrahend)
  {
    // std::cout << "-= index; " << this->Index << std::endl;
    this->Subtract(subtrahend, this->Index);
    return *this;
  }

  bool operator<(const Iterator<T>& other) const
  {
    // std::cout << "< index; " << this->Index << std::endl;
    return this->Index < other.Index;
  }

  Iterator<T>& operator=(const Iterator<T>& value)
  {
    // std::cout << "\t\t\titerator assignment.  index; " << this->Index << std::endl;
    this->Get = value.Get;
    this->Increment = value.Increment;
    this->Decrement = value.Decrement;
    this->Dereference = value.Dereference;
    this->ConstDereference = value.ConstDereference;
    this->Assign = value.Assign;
    this->Add = value.Add;
    this->Subtract = value.Subtract;
    this->Index = value.Index;
    this->Assign(value);
    return *this;
  }
};

#endif
