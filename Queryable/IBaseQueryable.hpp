#ifndef CPPQUERYABLE_QUERYABLE_IBASEQUERYABLE_H
#define CPPQUERYABLE_QUERYABLE_IBASEQUERYABLE_H

#include <deque>
#include <functional>
#include <list>
#include <memory>
#include <set>
#include <vector>

#include "Queryable.hpp"
#include "QueryableType.hpp"
#include "Utilities/Grouping.hpp"

template<
  typename TStoring,
  template<typename, typename ...> typename TIterable,
  typename TIterating,
  typename ...TArgs>
class Queryable;

template<
  typename TStoring,
  template<typename, typename ...> typename TIterable,
  typename TIterating,
  typename ...TArgs>
class IBaseQueryable
{
protected:
  std::shared_ptr<Queryable<TStoring, TIterable, TIterating, TArgs...>> queryable;

public:
  IBaseQueryable() { }
  IBaseQueryable(const std::shared_ptr<Queryable<TStoring, TIterable, TIterating, TArgs...>> & other) :
    queryable(other)
  {
  }
  IBaseQueryable(std::shared_ptr<Queryable<TStoring, TIterable, TIterating, TArgs...>> && other) :
    queryable(std::move(other))
  {
  }
  // probably unsafe enough that it shouldn't be a thing
  IBaseQueryable(Queryable<TStoring, TIterable, TIterating, TArgs...> * other)
  {
    this->queryable.reset(other);
  }
  IBaseQueryable(const IBaseQueryable<TStoring, TIterable, TIterating, TArgs...> & other) :
    queryable(other.queryable)
  {
  }
  IBaseQueryable(IBaseQueryable<TStoring, TIterable, TIterating, TArgs...> && other) :
    queryable(std::move(other.queryable))
  {
  }

  void operator=(const IBaseQueryable<TStoring, TIterable, TIterating, TArgs...> & other)
  {
    this->queryable = other.queryable;
  }

  void operator=(IBaseQueryable<TStoring, TIterable, TIterating, TArgs...> && other)
  {
    this->queryable = std::move(other.queryable);
  }

  template<template<typename, typename ...> typename TContainer>
  inline Queryable<TStoring, TContainer, TIterating, TArgs...> & AsExtendedQueryable() const
  {
    return *this->queryable;
  }

  template<typename TAllocator = std::allocator<TStoring>>
  inline std::deque<TStoring, TAllocator> ToDeque(TAllocator allocator = {}) const
  {
    return this->queryable->ToDeque(allocator);
  }

  template<typename TAllocator = std::allocator<TStoring>>
  inline std::list<TStoring, TAllocator> ToList(TAllocator allocator = {}) const
  {
    return this->queryable->ToList(allocator);
  }

  template<
    typename TKey,
    typename TValue = TStoring,
    typename TLessThan = std::less<TKey>,
    typename TAllocator = std::allocator<std::pair<const TKey, TValue>>>
  inline std::map<TKey, TValue, TLessThan, TAllocator> ToMap(
    std::function<TKey(TIterating)> getKey,
    std::function<TValue(TIterating)> getValue,
    TLessThan keyCompare = {},
    TAllocator pairAllocator = {})
  {
    return this->queryable->ToMap(getKey, getValue, keyCompare, pairAllocator);
  }

  template<typename TLessThan = std::less<TStoring>, typename TAllocator = std::allocator<TStoring>>
  inline std::multiset<TStoring, TLessThan, TAllocator> ToMultiSet(TLessThan lessThan = {}, TAllocator allocator = {}) const
  {
    return this->queryable->ToMultiSet(lessThan, allocator);
  }

  template<typename TLessThan = std::less<TStoring>, typename TAllocator = std::allocator<TStoring>>
  inline std::set<TStoring, TLessThan, TAllocator> ToSet(TLessThan lessThan = {}, TAllocator allocator = {}) const
  {
    return this->queryable->ToSet(lessThan, allocator);
  }

  template<typename TAllocator = std::allocator<TStoring>>
  inline std::vector<TStoring, TAllocator> ToVector(TAllocator allocator = {}) const
  {
    return this->queryable->ToVector(allocator);
  }

  template<typename TOut = TIterating>
  inline TOut Aggregate(const std::function<TOut(TOut, TIterating)> & accumulate, TOut * seed = NULL)
  {
    return this->queryable->template Aggregate<TOut>(accumulate, seed);
  }

  template<typename TFinalized, typename TOut = TIterating>
  inline TFinalized Aggregate(
    const std::function<TOut(TOut, TIterating)> & accumulate,
    const std::function<TFinalized(TOut)> & finalizer,
    TOut * seed = NULL)
  {
    return this->queryable->template Aggregate<TFinalized, TOut>(accumulate, finalizer, seed);
  }

  inline bool All(std::function<bool(TIterating)> condition) const
  {
    return this->queryable->All(condition);
  }

  inline bool Any(std::function<bool(TIterating)> condition) const
  {
    return this->queryable->Any(condition);
  }

  inline TIterating & At(int index)
  {
    return this->queryable->At(index);
  }

  inline double Average(std::function<double(TIterating)> retrieveValue = [](TIterating value) { return value; }) const
  {
    return this->queryable->Average(retrieveValue);
  }

  inline double Average(
    std::function<double(double, size_t)> divisor,
    std::function<double(TIterating)> retrieveValue = [](TIterating value) { return value; }) const
  {
    return this->queryable->Average(divisor, retrieveValue);
  }

  inline bool Contains(const TStoring & item) const
  {
    return this->queryable->Contains(item);
  }

  inline size_t Count() const
  {
    return this->queryable->Count();
  }

  inline size_t CountIf(std::function<bool(TIterating)> condition) const
  {
    return this->queryable->CountIf(condition);
  }

  inline TIterating First(std::function<bool(TIterating)> condition)
  {
    return this->queryable->First(condition);
  }

  inline TIterating First()
  {
    return this->queryable->First();
  }

  inline void ForEach(std::function<void(TIterating)> action) const
  {
    return this->queryable->ForEach(action);
  }

  inline TIterating Last(std::function<bool(TIterating)> condition)
  {
    return this->queryable->Last(condition);
  }

  inline TIterating Last()
  {
    return this->queryable->Last();
  }

  inline TIterating Max() const
  {
    return this->queryable->Max();
  }

  inline TIterating Max(TIterating startSeed) const
  {
    return this->queryable->Max(startSeed);
  }

  template<typename TOut>
  inline TOut Max(std::function<TOut(TIterating)> retrieveValue) const
  {
    return this->queryable->template Max<TIterable, TOut>(retrieveValue);
  }

  template<typename TOut>
  inline TOut Max(std::function<TOut(TIterating)> retrieveValue, TOut startSeed) const
  {
    return this->queryable->template Max<TIterable, TOut>(retrieveValue, startSeed);
  }

  template<typename TOut>
  inline TIterating MaxItem(std::function<TOut(TIterating)> retrieveValue) const
  {
    return this->queryable->template MaxItem<TIterable, TOut>(retrieveValue);
  }

  inline TIterating Min() const
  {
    return this->queryable->Min();
  }

  inline TIterating Min(TIterating startSeed) const
  {
    return this->queryable->Min(startSeed);
  }

  template<typename TOut>
  inline TOut Min(std::function<TOut(TIterating)> retrieveValue) const
  {
    return this->queryable->template Min<TIterable, TOut>(retrieveValue);
  }

  template<typename TOut>
  TOut Min(std::function<TOut(TIterating)> retrieveValue, TOut startSeed) const
  {
    return this->queryable->template Min<TIterable, TOut>(retrieveValue, startSeed);
  }

  template<typename TOut>
  inline TIterating MinItem(std::function<TOut(TIterating)> retrieveValue) const
  {
    return this->queryable->template MinItem<TIterable, TOut>(retrieveValue);
  }

  inline double Range(std::function<double(TIterating)> retrieveValue = [](TIterating value) { return value; }) const
  {
    return this->queryable->Range(retrieveValue);
  }

  template<typename TOut>
  inline TOut Range(std::function<TOut(TIterating)> retrieveValue)
  {
    return this->queryable->template Range<TIterable, TOut>(retrieveValue);
  }

  inline IBaseQueryable<TStoring, TIterable, TIterating, TArgs...> & Skip(int count)
  {
    this->queryable->Skip(count);
    return *this;
  }

  inline IBaseQueryable<TStoring, TIterable, TIterating, TArgs...> & SkipWhile(std::function<bool(TIterating)> && doSkip)
  {
    this->queryable->SkipWhile(std::move(doSkip));
    return *this;
  }

  inline double Sum(std::function<double(TIterating)> retrieveValue = [](TIterating value) { return value; }) const
  {
    return this->queryable->Sum(retrieveValue);
  }

  inline IBaseQueryable<TStoring, TIterable, TIterating, TArgs...> & Take(int count)
  {
    this->queryable->Take(count);
    return *this;
  }

  inline IBaseQueryable<TStoring, TIterable, TIterating, TArgs...> & TakeWhile(std::function<bool(TIterating)> && doTake)
  {
    this->queryable->TakeWhile(std::move(doTake));
    return *this;
  }
};

#endif
