#ifndef CPPQUERYABLE_QUERYABLE_IQUERYABLEDATA_H
#define CPPQUERYABLE_QUERYABLE_IQUERYABLEDATA_H

#include <functional>
#include <vector>

#include "../Iterators/QueryableIterator.hpp"
#include "../Iterators/IIterable.hpp"
#include "../Sorters/Sorter.hpp"

template<typename TObj>
class QueryableIterator;

template<typename TObj>
class IQueryableData
{
public:
  virtual ~IQueryableData() { }

  virtual void Clear() = 0;
  virtual void Add(TObj obj) = 0;
  virtual int Count() = 0;
  virtual int StorageSize() = 0;

  virtual QueryableIterator<TObj> begin() = 0;
  virtual QueryableIterator<TObj> end() = 0;
  virtual QueryableIterator<TObj> rbegin() = 0;
  virtual QueryableIterator<TObj> rend() = 0;

  inline virtual IQueryableData<TObj>& Next(IteratorType type, uint64_t & iterated) = 0;
  inline virtual IQueryableData<TObj>& Prev(IteratorType type, uint64_t & iterated) = 0;
  inline virtual TObj& Get(IteratorType type) = 0;
  inline virtual const TObj& ConstGet(IteratorType type) = 0;
  inline virtual IQueryableData<TObj>& Add(int addend, IteratorType type) = 0;
  inline virtual IQueryableData<TObj>& Subtract(int subtrahend, IteratorType type) = 0;
};

#endif
