#ifndef CPPQUERYABLE_QUERYABLE_IQUERYABLEDATA_H
#define CPPQUERYABLE_QUERYABLE_IQUERYABLEDATA_H

#include <functional>
#include <memory>
#include <vector>

#include "../Iterators/QueryableIterator.hpp"

template<typename TObj>
class QueryableIterator;

template<typename TObj>
class IQueryableData
{
public:
  int myId = 0;
  virtual ~IQueryableData() { }

  virtual void Clear() = 0;
  virtual void Add(TObj obj) = 0;
  virtual size_t Count() = 0;
  virtual size_t StorageSize() const = 0;

  virtual QueryableIterator<TObj> begin() = 0;
  virtual QueryableIterator<TObj> end() = 0;
  virtual QueryableIterator<TObj> rbegin() = 0;
  virtual QueryableIterator<TObj> rend() = 0;

  virtual std::shared_ptr<IQueryableData<TObj>> Clone() = 0;
  virtual std::shared_ptr<IQueryableData<TObj>> GetRealizedQueryableData() = 0;

  virtual bool CanIncrement(IteratorType type) = 0;
  virtual bool CanDecrement(IteratorType type) = 0;
  virtual IQueryableData<TObj>& Next(IteratorType type, uint64_t & iterated) = 0;
  virtual IQueryableData<TObj>& Prev(IteratorType type, uint64_t & iterated) = 0;
  virtual TObj& Get(IteratorType type) = 0;
  virtual const TObj& ConstGet(IteratorType type) = 0;
  virtual IQueryableData<TObj>& Add(int addend, IteratorType type) = 0;
  virtual IQueryableData<TObj>& Subtract(int subtrahend, IteratorType type) = 0;
};

#endif
