#ifndef CPPQUERYABLE_QUERYABLE_IQUERYABLEDATA_H
#define CPPQUERYABLE_QUERYABLE_IQUERYABLEDATA_H

#include <iostream>
#include <vector>

#include "../Iterators/ConstIterator.h"
#include "../Iterators/Iterator.h"

template<typename T>
class IQueryableData
{
public:
  virtual Iterator<T> begin() = 0;
  virtual Iterator<T> end() = 0;
  virtual Iterator<T> rbegin() = 0;
  virtual Iterator<T> rend() = 0;
  // virtual ConstIterator<T> begin() const = 0;
  // virtual ConstIterator<T> end() const = 0;
  // virtual ConstIterator<T> rbegin() const = 0;
  // virtual ConstIterator<T> rend() const = 0;

  virtual void Clear() = 0;
  virtual void Add(T obj) = 0;
  virtual int Count() = 0;
  virtual void RemoveLast() = 0;
  virtual void RemoveFirst() = 0;
  virtual std::vector<T> ToVector() = 0;
};

#endif
