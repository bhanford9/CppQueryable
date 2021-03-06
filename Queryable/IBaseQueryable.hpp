#ifndef CPPQUERYABLE_QUERYABLE_IBASEQUERYABLE_H
#define CPPQUERYABLE_QUERYABLE_IBASEQUERYABLE_H

#include <deque>
#include <functional>
#include <list>
#include <memory>
#include <set>
#include <vector>

#include "InternalIQueryable.hpp"
#include "Queryable.hpp"
#include "QueryableType.hpp"

template<
  typename TObj,
  template<typename, typename ...> typename TIterable,
  typename ...TArgs>
class Queryable;

template<typename T, typename ...TArgs>
class IBaseQueryable
{
protected:
  std::shared_ptr<InternalIQueryable<T, TArgs...>> queryable;

public:
  IBaseQueryable() { }
  IBaseQueryable(const std::shared_ptr<InternalIQueryable<T, TArgs...>> & other) :
    queryable(other)
  {
  }
  IBaseQueryable(std::shared_ptr<InternalIQueryable<T, TArgs...>> && other) :
    queryable(std::move(other))
  {
  }
  // probably unsafe enough that it shouldn't be a thing
  IBaseQueryable(InternalIQueryable<T, TArgs...> * other)
  {
    this->queryable.reset(other);
  }
  IBaseQueryable(const IBaseQueryable<T, TArgs...> & other) :
    queryable(other.queryable)
  {
  }
  IBaseQueryable(IBaseQueryable<T, TArgs...> && other) :
    queryable(std::move(other.queryable))
  {
  }

  void operator=(const IBaseQueryable<T, TArgs...> & other)
  {
    this->queryable = other.queryable;
  }

  void operator=(IBaseQueryable<T, TArgs...> && other)
  {
    this->queryable = std::move(other.queryable);
  }

  inline Queryable<T, std::deque, TArgs...> & AsQueryableDeque() const
  {
    return this->queryable->template AsQueryableDeque();
  }

  inline Queryable<T, std::deque, TArgs...> ToQueryableDeque() const
  {
    // Investiage speed of doing it this way and whether iterators would be simpler
    return Queryable<T, std::deque, TArgs...>::FromDeque(this->queryable->ToDeque());
  }

  inline Queryable<T, std::list, TArgs...> & AsQueryableList() const
  {
    return this->queryable->template AsQueryableList();
  }

  inline Queryable<T, std::list, TArgs...> ToQueryableList() const
  {
    // Investiage speed of doing it this way and whether iterators would be simpler
    return Queryable<T, std::list, TArgs...>::FromList(this->queryable->ToList());
  }

  inline Queryable<T, std::multiset, TArgs...> & AsQueryableMultiSet() const
  {
    return this->queryable->template AsQueryableMultiSet();
  }

  inline Queryable<T, std::multiset, TArgs...> ToQueryableMultiSet() const
  {
    // Investiage speed of doing it this way and whether iterators would be simpler
    return Queryable<T, std::multiset, TArgs...>::FromMultiSet(this->queryable->ToMultiSet());
  }

  inline Queryable<T, std::set, TArgs...> & AsQueryableSet() const
  {
    return this->queryable->template AsQueryableSet();
  }

  inline Queryable<T, std::set, TArgs...> ToQueryableSet() const
  {
    // Investiage speed of doing it this way and whether iterators would be simpler
    return Queryable<T, std::set, TArgs...>::FromSet(this->queryable->ToSet());
  }

  inline Queryable<T, std::vector, TArgs...> & AsQueryableVector() const
  {
    return this->queryable->template AsQueryableVector();
  }

  inline Queryable<T, std::vector, TArgs...> ToQueryableVector() const
  {
    // Investiage speed of doing it this way and whether iterators would be simpler
    return Queryable<T, std::vector, TArgs...>::FromVector(this->queryable->ToVector());
  }

  template<template<typename, typename ...> typename TContainer>
  inline Queryable<T, TContainer, TArgs...> & AsExtendedQueryable() const
  {
    return this->queryable->template AsExtendedQueryable<TContainer>();
  }

  template<typename TAllocator = std::allocator<T>>
  inline std::deque<T, TAllocator> ToDeque(TAllocator allocator = {}) const
  {
    return this->queryable->ToDeque(allocator);
  }

  template<typename TAllocator = std::allocator<T>>
  inline std::list<T, TAllocator> ToList(TAllocator allocator = {}) const
  {
    return this->queryable->ToList(allocator);
  }

  template<typename TLessThan = std::less<T>, typename TAllocator = std::allocator<T>>
  inline std::multiset<T, TLessThan, TAllocator> ToMultiSet(TLessThan lessThan = {}, TAllocator allocator = {}) const
  {
    return this->queryable->ToMultiSet(lessThan, allocator);
  }

  template<typename TLessThan = std::less<T>, typename TAllocator = std::allocator<T>>
  inline std::set<T, TLessThan, TAllocator> ToSet(TLessThan lessThan = {}, TAllocator allocator = {}) const
  {
    return this->queryable->ToSet(lessThan, allocator);
  }

  template<typename TAllocator = std::allocator<T>>
  inline std::vector<T, TAllocator> ToVector(TAllocator allocator = {}) const
  {
    return this->queryable->ToVector(allocator);
  }

  template<template<typename, typename ...> typename TIterable, typename TOut = T>
  inline TOut Aggregate(const std::function<TOut(TOut, T)> & accumulate, TOut * seed = NULL)
  {
    return this->queryable->template Aggregate<TIterable, TOut>(accumulate, seed);
  }

  template<template<typename, typename ...> typename TIterable, typename TFinalized, typename TOut = T>
  inline TFinalized Aggregate(
    const std::function<TOut(TOut, T)> & accumulate,
    const std::function<TFinalized(TOut)> & finalizer,
    TOut * seed = NULL)
  {
    return this->queryable->template Aggregate<TIterable, TFinalized, TOut>(accumulate, finalizer, seed);
  }

  inline bool All(std::function<bool(T)> condition) const
  {
    return this->queryable->All(condition);
  }

  inline bool Any(std::function<bool(T)> condition) const
  {
    return this->queryable->Any(condition);
  }

  inline T & At(int index)
  {
    return this->queryable->At(index);
  }

  inline double Average(std::function<double(T)> retrieveValue = [](T value) { return value; }) const
  {
    return this->queryable->Average(retrieveValue);
  }

  inline double Average(
    std::function<double(double, size_t)> divisor,
    std::function<double(T)> retrieveValue = [](T value) { return value; }) const
  {
    return this->queryable->Average(divisor, retrieveValue);
  }

  inline bool Contains(const T & item) const
  {
    return this->queryable->Contains(item);
  }

  inline size_t Count() const
  {
    return this->queryable->Count();
  }

  inline size_t CountIf(std::function<bool(T)> condition) const
  {
    return this->queryable->CountIf(condition);
  }

  inline T First(std::function<bool(T)> condition)
  {
    return this->queryable->First(condition);
  }

  inline T First()
  {
    return this->queryable->First();
  }

  inline void ForEach(std::function<void(T)> action) const
  {
    return this->queryable->ForEach(action);
  }

  inline T Last(std::function<bool(T)> condition)
  {
    return this->queryable->Last(condition);
  }

  inline T Last()
  {
    return this->queryable->Last();
  }

  inline T Max() const
  {
    return this->queryable->Max();
  }

  inline T Max(T startSeed) const
  {
    return this->queryable->Max(startSeed);
  }

  template<template<typename, typename ...> typename TIterable, typename TOut>
  inline TOut Max(std::function<TOut(T)> retrieveValue) const
  {
    return this->queryable->template Max<TIterable, TOut>(retrieveValue);
  }

  template<template<typename, typename ...> typename TIterable, typename TOut>
  inline TOut Max(std::function<TOut(T)> retrieveValue, TOut startSeed) const
  {
    return this->queryable->template Max<TIterable, TOut>(retrieveValue, startSeed);
  }

  template<template<typename, typename ...> typename TIterable, typename TOut>
  inline T MaxItem(std::function<TOut(T)> retrieveValue) const
  {
    return this->queryable->template MaxItem<TIterable, TOut>(retrieveValue);
  }

  inline T Min() const
  {
    return this->queryable->Min();
  }

  inline T Min(T startSeed) const
  {
    return this->queryable->Min(startSeed);
  }

  template<template<typename, typename ...> typename TIterable, typename TOut>
  inline TOut Min(std::function<TOut(T)> retrieveValue) const
  {
    return this->queryable->template Min<TIterable, TOut>(retrieveValue);
  }

  template<template<typename, typename ...> typename TIterable, typename TOut>
  TOut Min(std::function<TOut(T)> retrieveValue, TOut startSeed) const
  {
    return this->queryable->template Min<TIterable, TOut>(retrieveValue, startSeed);
  }

  template<template<typename, typename ...> typename TIterable, typename TOut>
  inline T MinItem(std::function<TOut(T)> retrieveValue) const
  {
    return this->queryable->template MinItem<TIterable, TOut>(retrieveValue);
  }

  inline double Range(std::function<double(T)> retrieveValue = [](T value) { return value; }) const
  {
    return this->queryable->Range(retrieveValue);
  }

  template<template<typename, typename ...> typename TIterable, typename TOut>
  inline TOut Range(std::function<TOut(T)> retrieveValue)
  {
    return this->queryable->template Range<TIterable, TOut>(retrieveValue);
  }

  inline double Sum(std::function<double(T)> retrieveValue = [](T value) { return value; }) const
  {
    return this->queryable->Sum(retrieveValue);
  }
};

#endif
