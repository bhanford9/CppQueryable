#ifndef CPPQUERYABLE_QUERYABLE_IQUERYABLEDATA_H
#define CPPQUERYABLE_QUERYABLE_IQUERYABLEDATA_H

#include <functional>
#include <vector>

#include "../Iterators/Iterator.h"
#include "../Iterators/QueryableIterator.h"

template<typename T>
class IQueryableData
{
protected:
  typedef typename std::vector<T>::iterator TVectorIterator;

public:
  virtual ~IQueryableData() { }

  virtual Iterator<T> begin() = 0;
  virtual Iterator<T> end() = 0;
  virtual Iterator<T> rbegin() = 0;
  virtual Iterator<T> rend() = 0;

  virtual void Clear() = 0;
  virtual void Add(T obj) = 0;
  virtual int Count() = 0;
  virtual int StorageSize() = 0;
  virtual std::vector<T> ToVector() = 0;
  virtual void Sort(std::function<bool(T, T)> compare = [](T a, T b) { return a < b; }) = 0;
  virtual void Update(Iterator<T> first, Iterator<T> last, std::function<bool(T, T)> compare = [](T a, T b) { return a < b; }) = 0;
  virtual void Update(TVectorIterator first, TVectorIterator last) = 0;

  // virtual void AddCondition(std::function<bool(const T &)> condition) = 0;
  // virtual bool PassesCondition(const T & obj) const = 0;
};

#endif
