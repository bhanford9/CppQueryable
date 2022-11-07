#ifndef CPPQUERYABLE_QUERYABLE_IBASEQUERYABLE_H
#define CPPQUERYABLE_QUERYABLE_IBASEQUERYABLE_H

#include <deque>
#include <functional>
#include <list>
#include <memory>
#include <set>
#include <vector>

template<
  typename TStoring,
  template<typename, typename ...> class TIterable,
  typename TIterating,
  typename ...TArgs>
class Queryable;

template<
  typename TStoring,
  template<typename, typename ...> class TIterable,
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

  template<template<typename, typename ...> class TContainer>
  Queryable<TStoring, TContainer, TIterating, TArgs...> & AsExtendedQueryable() const
  {
    return *this->queryable;
  }

  template<typename TAllocator = std::allocator<TStoring>>
  std::deque<TStoring, TAllocator> ToDeque(TAllocator allocator = {}) const
  {
    return this->queryable->ToDeque(allocator);
  }

  template<typename TAllocator = std::allocator<TStoring>>
  std::list<TStoring, TAllocator> ToList(TAllocator allocator = {}) const
  {
    return this->queryable->ToList(allocator);
  }

  template<
    typename TKey,
    typename TValue = TStoring,
    typename TLessThan = std::less<TKey>,
    typename TAllocator = std::allocator<std::pair<const TKey, TValue>>>
  std::map<TKey, TValue, TLessThan, TAllocator> ToMap(
    std::function<TKey(TIterating)> getKey,
    std::function<TValue(TIterating)> getValue,
    TLessThan keyCompare = {},
    TAllocator pairAllocator = {})
  {
    return this->queryable->ToMap(getKey, getValue, keyCompare, pairAllocator);
  }

  template<typename TLessThan = std::less<TStoring>, typename TAllocator = std::allocator<TStoring>>
  std::multiset<TStoring, TLessThan, TAllocator> ToMultiSet(TLessThan lessThan = {}, TAllocator allocator = {}) const
  {
    return this->queryable->ToMultiSet(lessThan, allocator);
  }

  template<typename TLessThan = std::less<TStoring>, typename TAllocator = std::allocator<TStoring>>
  std::set<TStoring, TLessThan, TAllocator> ToSet(TLessThan lessThan = {}, TAllocator allocator = {}) const
  {
    return this->queryable->ToSet(lessThan, allocator);
  }

  template<typename TAllocator = std::allocator<TStoring>>
  std::vector<TStoring, TAllocator> ToVector(TAllocator allocator = {}) const
  {
    return this->queryable->ToVector(allocator);
  }

  template<typename TOut = TIterating>
  TOut Aggregate(const std::function<TOut(TOut, TIterating)> & accumulate, TOut * seed = nullptr)
  {
    return this->queryable->template Aggregate<TOut>(accumulate, seed);
  }

  template<typename TFinalized, typename TOut = TIterating>
  TFinalized Aggregate(
    const std::function<TOut(TOut, TIterating)> & accumulate,
    const std::function<TFinalized(TOut)> & finalizer,
    TOut * seed = nullptr)
  {
    return this->queryable->template Aggregate<TFinalized, TOut>(accumulate, finalizer, seed);
  }

  bool All(std::function<bool(TIterating)> condition) const
  {
    return this->queryable->All(condition);
  }

  bool Any(std::function<bool(TIterating)> condition) const
  {
    return this->queryable->Any(condition);
  }

  TIterating & At(size_t index)
  {
    return this->queryable->At(index);
  }

  double Average(std::function<double(TIterating)> retrieveValue = [](TIterating value) { return value; }) const
  {
    return this->queryable->Average(retrieveValue);
  }

  double Average(
    std::function<double(double, size_t)> divisor,
    std::function<double(TIterating)> retrieveValue = [](TIterating value) { return value; }) const
  {
    return this->queryable->Average(divisor, retrieveValue);
  }

  bool Contains(const TStoring & item) const
  {
    return this->queryable->Contains(item);
  }

  size_t Count() const
  {
    return this->queryable->Count();
  }

  size_t CountIf(const std::function<bool(const TIterating &)> & condition) const
  {
    return this->queryable->CountIf(condition);
  }

  TIterating First(std::function<bool(TIterating)> condition)
  {
    return this->queryable->First(condition);
  }

  TIterating First()
  {
    return this->queryable->First();
  }

  void ForEach(std::function<void(TIterating)> action) const
  {
    return this->queryable->ForEach(action);
  }

  TIterating Last(std::function<bool(TIterating)> condition)
  {
    return this->queryable->Last(condition);
  }

  TIterating Last()
  {
    return this->queryable->Last();
  }

  TIterating Max() const
  {
    return this->queryable->Max();
  }

  TIterating Max(TIterating startSeed) const
  {
    return this->queryable->Max(startSeed);
  }

  template<typename TOut>
  TOut Max(std::function<TOut(TIterating)> retrieveValue) const
  {
    return this->queryable->template Max<TIterable, TOut>(retrieveValue);
  }

  template<typename TOut>
  TOut Max(std::function<TOut(TIterating)> retrieveValue, TOut startSeed) const
  {
    return this->queryable->template Max<TIterable, TOut>(retrieveValue, startSeed);
  }

  template<typename TOut>
  TIterating MaxItem(std::function<TOut(TIterating)> retrieveValue) const
  {
    return this->queryable->template MaxItem<TIterable, TOut>(retrieveValue);
  }

  TIterating Min() const
  {
    return this->queryable->Min();
  }

  TIterating Min(TIterating startSeed) const
  {
    return this->queryable->Min(startSeed);
  }

  template<typename TOut>
  TOut Min(std::function<TOut(TIterating)> retrieveValue) const
  {
    return this->queryable->template Min<TIterable, TOut>(retrieveValue);
  }

  template<typename TOut>
  TOut Min(std::function<TOut(TIterating)> retrieveValue, TOut startSeed) const
  {
    return this->queryable->template Min<TIterable, TOut>(retrieveValue, startSeed);
  }

  template<typename TOut>
  TIterating MinItem(std::function<TOut(TIterating)> retrieveValue) const
  {
    return this->queryable->template MinItem<TIterable, TOut>(retrieveValue);
  }

  double Range(std::function<double(TIterating)> retrieveValue = [](TIterating value) { return value; }) const
  {
    return this->queryable->Range(retrieveValue);
  }

  template<typename TOut>
  TOut Range(std::function<TOut(TIterating)> retrieveValue)
  {
    return this->queryable->template Range<TIterable, TOut>(retrieveValue);
  }

  IBaseQueryable<TStoring, TIterable, TIterating, TArgs...> & Skip(int count)
  {
    this->queryable->Skip(count);
    return *this;
  }

  IBaseQueryable<TStoring, TIterable, TIterating, TArgs...> & SkipWhile(std::function<bool(TIterating)> && doSkip)
  {
    this->queryable->SkipWhile(std::move(doSkip));
    return *this;
  }

  double Sum(std::function<double(TIterating)> retrieveValue = [](TIterating value) { return value; }) const
  {
    return this->queryable->Sum(retrieveValue);
  }

  IBaseQueryable<TStoring, TIterable, TIterating, TArgs...> & Take(int count)
  {
    this->queryable->Take(count);
    return *this;
  }

  IBaseQueryable<TStoring, TIterable, TIterating, TArgs...> & TakeWhile(std::function<bool(TIterating)> && doTake)
  {
    this->queryable->TakeWhile(std::move(doTake));
    return *this;
  }
};

#endif
