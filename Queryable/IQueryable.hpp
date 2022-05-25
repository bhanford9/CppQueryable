#ifndef CPPQUERYABLE_QUERYABLE_IQUERYABLE_H
#define CPPQUERYABLE_QUERYABLE_IQUERYABLE_H

#include <deque>
#include <functional>
#include <list>
#include <memory>
#include <set>
#include <vector>

#include "InternalIQueryable.hpp"
#include "Queryable.hpp"
#include "QueryableType.hpp"

// TODO --> I don't think this class is actually necessary
//   could just pass around the interface and use BuildQueryable for constructing it
//   I guess it depends if it is seen as a hassle to necessarily pass something as
//   a pointer/reference.


template<
  typename TObj,
  template<typename, typename ...> typename TIterable,
  typename ...TArgs>
class Queryable;

template<typename T, typename ...TArgs>
class InternalIQueryable;

template<typename T, typename ...TArgs>
class IQueryable
{
private:
  std::shared_ptr<InternalIQueryable<T, TArgs...>> queryable;

public:
  IQueryable() { }
  IQueryable(const std::shared_ptr<InternalIQueryable<T, TArgs...>> & other) :
    queryable(other)
  {
  }
  IQueryable(std::shared_ptr<InternalIQueryable<T, TArgs...>> && other) :
    queryable(std::move(other))
  {
  }
  IQueryable(const IQueryable<T, TArgs...> & other) :
    queryable(other.queryable)
  {
  }
  IQueryable(IQueryable<T, TArgs...> && other) :
    queryable(std::move(other.queryable))
  {
  }

  inline QueryableDeque<T, TArgs...> & AsQueryableDeque() const
  {
    return this->queryable->template AsQueryableDeque();
  }

  inline QueryableList<T, TArgs...> & AsQueryableList() const
  {
    return this->queryable->template AsQueryableList();
  }

  inline QueryableMultiSet<T, TArgs...> & AsQueryableMultiSet() const
  {
    return this->queryable->template AsQueryableMultiSet();
  }

  inline QueryableSet<T, TArgs...> & AsQueryableSet() const
  {
    return this->queryable->template AsQueryableSet();
  }

  inline QueryableVector<T, TArgs...> & AsQueryableVector() const
  {
    return this->queryable->template AsQueryableVector();
  }

  template<template<typename, typename ...> typename TContainer>
  inline Queryable<T, TContainer, TArgs...> & AsExtendedQueryable() const
  {
    return this->queryable->template AsExtendedQueryable<TContainer>();
  }

  template<
    typename TOut,
    template<typename, typename ...> typename TIterable,
    typename ...TNewArgs>
  InternalIQueryable<TOut, TNewArgs...> & Select(
    std::function<TOut(T)> retrieveValue,
    TNewArgs... iterableParameters)
  {
    return this->queryable->Select(retrieveValue, iterableParameters...);
  }

  template<typename TAllocator = std::allocator<T>>
  inline std::deque<T, TAllocator> ToDeque(TAllocator allocator = {}) const
  {
    std::deque<T, TAllocator> newDeque(allocator);
    this->queryable->ForEach([&](const T & value) { newDeque.push_back(value); });
    return newDeque;
  }

  template<typename TAllocator = std::allocator<T>>
  inline std::list<T, TAllocator> ToList(TAllocator allocator = {}) const
  {
    std::list<T, TAllocator> newList(allocator);
    this->queryable->ForEach([&](const T & value) { newList.push_back(value); });
    return newList;
  }

  template<typename TLessThan = std::less<T>, typename TAllocator = std::allocator<T>>
  inline std::multiset<T, TLessThan, TAllocator> ToMultiSet(TLessThan lessThan = {}, TAllocator allocator = {}) const
  {
    std::multiset<T, TLessThan, TAllocator> newMultiSet(lessThan, allocator);
    this->queryable->ForEach([&](const T & value) { newMultiSet.insert(value); });
    return newMultiSet;
  }

  template<typename TLessThan = std::less<T>, typename TAllocator = std::allocator<T>>
  inline std::set<T, TLessThan, TAllocator> ToSet(TLessThan lessThan = {}, TAllocator allocator = {}) const
  {
    std::set<T, TLessThan, TAllocator> newSet(lessThan, allocator);
    this->queryable->ForEach([&](const T & value) { newSet.insert(value); });
    return newSet;
  }

  template<typename TAllocator = std::allocator<T>>
  inline std::vector<T, TAllocator> ToVector(TAllocator allocator = {}) const
  {
    std::vector<T, TAllocator> newVector(allocator);
    this->queryable->ForEach([&](const T & value) { newVector.push_back(value); });
    return newVector;
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

  inline double Average(std::function<double(T)> retrieveValue) const
  {
    return this->queryable->Average(retrieveValue);
  }

  inline double Average(
    std::function<double(double, size_t)> divisor,
    std::function<double(T)> retrieveValue = [](T value) { return value; }) const
  {
    return this->queryable->Average(divisor, retrieveValue);
  }

  template<template<typename, typename ...> typename TIterable>
  inline T Average(std::function<T(const T &, size_t)> divisor) const
  {
    return this->queryable->template Average<TIterable>(divisor);
  }

  inline double Average() const
  {
    return this->queryable->Average();
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

  inline T Min() const
  {
    return this->queryable->Min();
  }

  inline T Min(T startSeed) const
  {
    return this->queryable->Min(startSeed);
  }

  inline double Range(std::function<double(T)> retrieveValue) const
  {
    return this->queryable->Range(retrieveValue);
  }

  inline double Sum(std::function<double(T)> retrieveValue = [](T value) { return value; }) const
  {
    return this->queryable->Sum();
  }

  inline size_t Sum(std::function<size_t(T)> retrieveValue = [](T value) { return value; }) const
  {
    return this->queryable->Sum();
  }

  inline IQueryable<T, TArgs...> Where(std::function<bool(const T &)> condition)
  {
    this->queryable->Where(condition);
    return *this;
  }
};

#endif
