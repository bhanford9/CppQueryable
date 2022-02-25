#ifndef CPPQUERYABLE_QUERYABLE_IQUERYABLEDATAITERATOR_H
#define CPPQUERYABLE_QUERYABLE_IQUERYABLEDATAITERATOR_H

#include <vector>

#include "../Iterators/IteratorType.h"
#include "../Iterators/QueryableIterator.h"

template<typename T>
class IQueryableIteratorData// : public IIterable<T>
{
public:
  virtual QueryableIterator<T> begin() = 0;
  virtual QueryableIterator<T> end() = 0;
  virtual QueryableIterator<T> rbegin() = 0;
  virtual QueryableIterator<T> rend() = 0;
  virtual std::vector<T> ToVector() = 0;

  inline virtual IQueryableIteratorData<T>& Next(IteratorType type, uint64_t & iterated) = 0;
  inline virtual IQueryableIteratorData<T>& Prev(IteratorType type, uint64_t & iterated) = 0;
  inline virtual T& Get(IteratorType type) = 0;
  inline virtual const T& ConstGet(IteratorType type) = 0;
  // inline virtual IQueryableIteratorData<T>& operator+(int addend) = 0;
  inline virtual IQueryableIteratorData<T>& Add(int addend, IteratorType type) = 0;
  // inline virtual IQueryableIteratorData<T>& operator-(int subtrahend) = 0;
  inline virtual IQueryableIteratorData<T>& Subtract(int subtrahend, IteratorType type) = 0;
};

#endif
