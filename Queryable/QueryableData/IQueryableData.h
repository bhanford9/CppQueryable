#ifndef CPPQUERYABLE_QUERYABLE_IQUERYABLEDATA_H
#define CPPQUERYABLE_QUERYABLE_IQUERYABLEDATA_H

#include <functional>
#include <vector>

#include "../Iterators/Iterator.h"

template<typename T>
class IQueryableData
{
public:
  virtual ~IQueryableData() { }

  virtual Iterator<T> begin() = 0;
  virtual Iterator<T> end() = 0;
  virtual Iterator<T> rbegin() = 0;
  virtual Iterator<T> rend() = 0;

  virtual void Clear() = 0;
  virtual void Add(T obj) = 0;
  virtual int Count() = 0;
  virtual void RemoveLast() = 0;
  virtual void RemoveFirst() = 0;
  virtual std::vector<T> ToVector() = 0;
  virtual void Sort(std::function<bool(T, T)> compare) = 0;

  virtual void AddCondition(std::function<bool(T)> condition) = 0;
};

#endif
