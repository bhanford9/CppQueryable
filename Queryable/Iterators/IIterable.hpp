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

  // inline virtual bool operator==(const QueryableIterator<T>& comparison) const
  // {
  //   std::cout << "[==] My Index: " << this->index << ", compare index: " << comparison.index << std::endl;
  //   return this->index == comparison.index;
  // }
  //
  // inline virtual bool operator!=(const QueryableIterator<T>& comparison) const
  // {
  //   std::cout << "[!=] My Index: " << this->index << ", compare index: " << comparison.index << std::endl;
  //   return this->index != comparison.index;
  // }
  //
  // inline virtual int operator-(const QueryableIterator<T>& subtrahend) const
  // {
  //   std::cout << "[-] My Index: " << this->index << ", compare index: " << subtrahend.index << std::endl;
  //   return this->index - subtrahend.index;
  // }

  inline virtual bool operator==(const QueryableIterator<T>& comparison) const
  {
    // std::cout << "[==] My Index: " << this->index << ", compare index: " << comparison.index << std::endl;
    return this->index == comparison.index;
  }

  inline virtual bool operator!=(const QueryableIterator<T>& comparison) const
  {
    // std::cout << "[!=] My Index: " << this->index << ", compare index: " << comparison.index << std::endl;
    return this->index != comparison.index;
  }

  inline virtual int operator-(const QueryableIterator<T>& subtrahend) const
  {
    // std::cout << "[-] My Index: " << this->index << ", compare index: " << subtrahend.index << std::endl;
    return this->index - subtrahend.index;
  }

  // inline virtual bool operator==(const QueryableIterator<T>& comparison) const = 0;
  // inline virtual bool operator!=(const QueryableIterator<T>& comparison) const = 0;
  // inline virtual int operator-(const QueryableIterator<T>& subtrahend) const = 0;
  inline virtual QueryableIterator<T>& operator++() = 0;
  inline virtual QueryableIterator<T>& operator--() = 0;
  inline virtual T& operator*() = 0;
  inline virtual const T& operator*() const = 0;
  inline virtual QueryableIterator<T>& operator+(int addend) = 0;
  inline virtual QueryableIterator<T>& operator+=(int addend) = 0;
  inline virtual QueryableIterator<T>& operator-(int subtrahend) = 0;
  inline virtual QueryableIterator<T>& operator-=(int subtrahend) = 0;
  // inline virtual QueryableIterator<T>& operator=(const QueryableIterator<T>& value) = 0;
};

#endif
