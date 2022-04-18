#ifndef CPPQUERYABLE_QUERYABLE_ITERATORS_IITERABLE_H
#define CPPQUERYABLE_QUERYABLE_ITERATORS_IITERABLE_H

#include "QueryableIterator.hpp"

template<typename T>
class QueryableIterator;

template<typename T>
class IIterable
{
public:
  // being lazy and leaving this public
  uint64_t index;

  IIterable() : index(0) { }

  // virtual bool operator==(const QueryableIterator<T>& comparison) const
  // {
  //   std::cout << "[==] My Index: " << this->index << ", compare index: " << comparison.index << std::endl;
  //   return this->index == comparison.index;
  // }
  //
  // virtual bool operator!=(const QueryableIterator<T>& comparison) const
  // {
  //   std::cout << "[!=] My Index: " << this->index << ", compare index: " << comparison.index << std::endl;
  //   return this->index != comparison.index;
  // }
  //
  // virtual int operator-(const QueryableIterator<T>& subtrahend) const
  // {
  //   std::cout << "[-] My Index: " << this->index << ", compare index: " << subtrahend.index << std::endl;
  //   return this->index - subtrahend.index;
  // }

  virtual bool operator==(const QueryableIterator<T>& comparison) const
  {
    // std::cout << "[==] My Index: " << this->index << ", compare index: " << comparison.index << std::endl;
    return this->index == comparison.index;
  }

  virtual bool operator!=(const QueryableIterator<T>& comparison) const
  {
    // std::cout << "[!=] My Index: " << this->index << ", compare index: " << comparison.index << std::endl;
    return this->index != comparison.index;
  }

  virtual int operator-(const QueryableIterator<T>& subtrahend) const
  {
    // std::cout << "[-] My Index: " << this->index << ", compare index: " << subtrahend.index << std::endl;
    return this->index - subtrahend.index;
  }

  // virtual bool operator==(const QueryableIterator<T>& comparison) const = 0;
  // virtual bool operator!=(const QueryableIterator<T>& comparison) const = 0;
  // virtual int operator-(const QueryableIterator<T>& subtrahend) const = 0;
  virtual QueryableIterator<T>& operator++() = 0;
  virtual QueryableIterator<T>& operator--() = 0;
  virtual T& operator*() = 0;
  virtual const T& operator*() const = 0;
  virtual QueryableIterator<T>& operator+(int addend) = 0;
  virtual QueryableIterator<T>& operator+=(int addend) = 0;
  virtual QueryableIterator<T>& operator-(int subtrahend) = 0;
  virtual QueryableIterator<T>& operator-=(int subtrahend) = 0;
  // virtual QueryableIterator<T>& operator=(const QueryableIterator<T>& value) = 0;
};

#endif
