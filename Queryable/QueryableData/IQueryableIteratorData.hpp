#ifndef CPPQUERYABLE_QUERYABLE_IQUERYABLEDATAITERATOR_H
#define CPPQUERYABLE_QUERYABLE_IQUERYABLEDATAITERATOR_H

#include "../Iterators/IteratorType.hpp"
#include "../Iterators/QueryableIterator.hpp"

template<typename T>
class IQueryableIteratorData// : public IIterable<T>
{
public:
  virtual QueryableIterator<T> begin() = 0;
  virtual QueryableIterator<T> end() = 0;
  virtual QueryableIterator<T> rbegin() = 0;
  virtual QueryableIterator<T> rend() = 0;

  virtual IQueryableIteratorData<T>& Next(IteratorType type, size_t & iterated) = 0;
  virtual IQueryableIteratorData<T>& Prev(IteratorType type, size_t & iterated) = 0;
  virtual T Get(IteratorType type) = 0;
  virtual const T& ConstGet(IteratorType type) = 0;
  // virtual IQueryableIteratorData<T>& operator+(int addend) = 0;
  virtual IQueryableIteratorData<T>& Add(int addend, IteratorType type) = 0;
  // virtual IQueryableIteratorData<T>& operator-(int subtrahend) = 0;
  virtual IQueryableIteratorData<T>& Subtract(int subtrahend, IteratorType type) = 0;
};

#endif
