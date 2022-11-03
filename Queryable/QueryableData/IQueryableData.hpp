#ifndef CPPQUERYABLE_QUERYABLE_IQUERYABLEDATA_H
#define CPPQUERYABLE_QUERYABLE_IQUERYABLEDATA_H

#include <memory>

#include "../Iterators/QueryableIterator.hpp"

template<typename TIterating>
class QueryableIterator;

template<typename TIterating>
class IQueryableData
{
public:
  virtual ~IQueryableData() { }

  virtual void Clear() = 0;
  virtual void Add(TIterating obj) = 0;
  virtual size_t Count() = 0;
  virtual size_t StorageSize() const = 0;

  virtual QueryableIterator<TIterating> begin() = 0;
  virtual QueryableIterator<TIterating> end() = 0;
  virtual QueryableIterator<TIterating> rbegin() = 0;
  virtual QueryableIterator<TIterating> rend() = 0;
  virtual void ForceBegin(IteratorType type) = 0;
  virtual void ForceEnd(IteratorType type) = 0;

  virtual std::shared_ptr<IQueryableData<TIterating>> Clone() = 0;
  virtual std::shared_ptr<IQueryableData<TIterating>> GetRealizedQueryableData() = 0;

  virtual bool CanIncrement(IteratorType type) = 0;
  virtual bool CanDecrement(IteratorType type) = 0;
  virtual IQueryableData<TIterating>& Next(IteratorType type, size_t & iterated, bool & isForcingToEnd) = 0;
  virtual IQueryableData<TIterating>& Prev(IteratorType type, size_t & iterated) = 0;
  virtual TIterating& Get(IteratorType type) = 0;
  virtual const TIterating& ConstGet(IteratorType type) = 0;
  virtual IQueryableData<TIterating>& Add(int addend, IteratorType type) = 0;
  virtual IQueryableData<TIterating>& Subtract(int subtrahend, IteratorType type) = 0;
};

#endif
