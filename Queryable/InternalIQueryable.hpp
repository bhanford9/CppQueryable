#ifndef CPPQUERYABLE_QUERYABLE_INTERNALIQUERYABLE_H
#define CPPQUERYABLE_QUERYABLE_INTERNALIQUERYABLE_H

#include <deque>
#include <functional>
#include <list>
#include <set>
#include <vector>

#include "Queryable.hpp"
#include "QueryableAliases.hpp"
#include "QueryableType.hpp"

// TODO --> Test if using template parameters is faster than std::function parameters

template<
  typename TObj,
  template<typename, typename ...> typename TIterable,
  typename ...TArgs>
class Queryable;

template<typename T, typename ...TArgs>
class InternalIQueryable
{
protected:

public:
  inline virtual QueryableType GetType() const = 0;

  inline QueryableDeque<T, TArgs...> & AsQueryableDeque() const
  {
    if (this->GetType() != QueryableType::Deque)
    {
      throw std::invalid_argument("Queryable type of TODO cannot be treated as a QueryableDeque.");
    }

    return *const_cast<QueryableDeque<T, TArgs...>*>(dynamic_cast<const QueryableDeque<T, TArgs...>*>(this));
  }

  inline QueryableDeque<T, TArgs...> ToQueryableDeque() const
  {
    // Investiage speed of doing it this way and whether iterators would be simpler
    return QueryableDeque<T, TArgs...>::FromDeque(this->ToDeque());
  }

  inline QueryableList<T, TArgs...> & AsQueryableList() const
  {
    if (this->GetType() != QueryableType::List)
    {
      throw std::invalid_argument("Queryable type of TODO cannot be treated as a QueryableList.");
    }

    return *const_cast<QueryableList<T, TArgs...>*>(dynamic_cast<const QueryableList<T, TArgs...>*>(this));
  }

  inline QueryableList<T, TArgs...> ToQueryableList() const
  {
    // Investiage speed of doing it this way and whether iterators would be simpler
    return QueryableList<T, TArgs...>::FromList(this->ToList());
  }

  inline QueryableMultiSet<T, TArgs...> & AsQueryableMultiSet() const
  {
    if (this->GetType() != QueryableType::MultiSet)
    {
      throw std::invalid_argument("Queryable type of TODO cannot be treated as a QueryableMultiSet.");
    }

    return *const_cast<QueryableMultiSet<T, TArgs...>*>(dynamic_cast<const QueryableMultiSet<T, TArgs...>*>(this));
  }

  inline QueryableMultiSet<T, TArgs...> ToQueryableMultiSet() const
  {
    // Investiage speed of doing it this way and whether iterators would be simpler
    return QueryableMultiSet<T, TArgs...>::FromMultiSet(this->ToMultiSet());
  }

  inline QueryableSet<T, TArgs...> & AsQueryableSet() const
  {
    if (this->GetType() != QueryableType::Set)
    {
      throw std::invalid_argument("Queryable type of TODO cannot be treated as a QueryableSet.");
    }

    return *const_cast<QueryableSet<T, TArgs...>*>(dynamic_cast<const QueryableSet<T, TArgs...>*>(this));
  }

  inline QueryableSet<T, TArgs...> ToQueryableSet() const
  {
    // Investiage speed of doing it this way and whether iterators would be simpler
    return QueryableSet<T, TArgs...>::FromSet(this->ToSet());
  }

  inline QueryableVector<T, TArgs...> & AsQueryableVector() const
  {
    if (this->GetType() != QueryableType::Vector)
    {
      throw std::invalid_argument("Queryable type of TODO cannot be treated as a QueryableVector.");
    }

    return *const_cast<QueryableVector<T, TArgs...>*>(dynamic_cast<const QueryableVector<T, TArgs...>*>(this));
  }

  inline QueryableVector<T, TArgs...> ToQueryableVector() const
  {
    // Investiage speed of doing it this way and whether iterators would be simpler
    return QueryableVector<T, TArgs...>::FromVector(this->ToVector());
  }

  template<template<typename, typename ...> typename TIterable>
  inline Queryable<T, TIterable, TArgs...> & AsExtendedQueryable() const
  {
    switch (this->GetType())
    {
      case QueryableType::Deque:
        if (!std::is_same<TIterable<T, TArgs...>, std::deque<T, TArgs...>>::value)
        {
          throw std::invalid_argument("Invalid template argument. Underlying container for Queryable is a Deque.");
        }
        break;
      case QueryableType::List:
        if (!std::is_same<TIterable<T, TArgs...>, std::list<T, TArgs...>>::value)
        {
          throw std::invalid_argument("Invalid template argument. Underlying container for Queryable is a List.");
        }
        break;
      case QueryableType::MultiSet:
        if (!std::is_same<TIterable<T, TArgs...>, std::multiset<T, TArgs...>>::value)
        {
          throw std::invalid_argument("Invalid template argument. Underlying container for Queryable is a MultiSet.");
        }
        break;
      case QueryableType::Set:
        if (!std::is_same<TIterable<T, TArgs...>, std::set<T, TArgs...>>::value)
        {
          throw std::invalid_argument("Invalid template argument. Underlying container for Queryable is a Set.");
        }
        break;
      case QueryableType::Vector:
        if (!std::is_same<TIterable<T, TArgs...>, std::vector<T, TArgs...>>::value)
        {
          throw std::invalid_argument("Invalid template argument. Underlying container for Queryable is a Vector.");
        }
        break;
      default:
        throw std::invalid_argument("Invalid container type.");
        break;
    }

    return *const_cast<Queryable<T, TIterable, TArgs...>*>(dynamic_cast<const Queryable<T, TIterable, TArgs...>*>(this));
  }

  template<
    template<typename, typename ...> typename TIterable,
    typename TAllocator>
  TAllocator GetAllocator()
  {
    return this->AsExtendedQueryable<TIterable>().template GetAllocator<TAllocator>();
  }

  template<
    template<typename, typename ...> typename TIterable,
    typename TLessThan>
  TLessThan GetValueCompare()
  {
    return this->AsExtendedQueryable<TIterable>().GetValueCompare();
  }

  template<typename TAllocator = std::allocator<T>>
  inline std::deque<T, TAllocator> ToDeque(TAllocator allocator = {}) const
  {
    std::deque<T, TAllocator> newDeque(allocator);
    this->ForEach([&](const T & value) { newDeque.push_back(value); });
    return newDeque;
  }

  template<typename TAllocator = std::allocator<T>>
  inline std::list<T, TAllocator> ToList(TAllocator allocator = {}) const
  {
    std::list<T, TAllocator> newList(allocator);
    this->ForEach([&](const T & value) { newList.push_back(value); });
    return newList;
  }

  template<typename TLessThan = std::less<T>, typename TAllocator = std::allocator<T>>
  inline std::multiset<T, TLessThan, TAllocator> ToMultiSet(TLessThan lessThan = {}, TAllocator allocator = {}) const
  {
    std::multiset<T, TLessThan, TAllocator> newMultiSet(lessThan, allocator);
    this->ForEach([&](const T & value) { newMultiSet.insert(value); });
    return newMultiSet;
  }

  template<typename TLessThan = std::less<T>, typename TAllocator = std::allocator<T>>
  inline std::set<T, TLessThan, TAllocator> ToSet(TLessThan lessThan = {}, TAllocator allocator = {}) const
  {
    std::set<T, TLessThan, TAllocator> newSet(lessThan, allocator);
    this->ForEach([&](const T & value) { newSet.insert(value); });
    return newSet;
  }

  template<typename TAllocator = std::allocator<T>>
  inline std::vector<T, TAllocator> ToVector(TAllocator allocator = {}) const
  {
    std::vector<T, TAllocator> newVector(allocator);
    this->ForEach([&](const T & value) { newVector.push_back(value); });
    return newVector;
  }

  template<
    template<typename, typename ...> typename TIterable,
    typename TOut = T>
  inline TOut Aggregate(const std::function<TOut(TOut, T)> & accumulate, TOut * seed = NULL)
  {
    return this->AsExtendedQueryable<TIterable>().Aggregate(accumulate, seed);
  }

  template<
    template<typename, typename ...> typename TIterable,
    typename TFinalized,
    typename TOut = T>
  inline TFinalized Aggregate(
    const std::function<TOut(TOut, T)> & accumulate,
    const std::function<TFinalized(TOut)> & finalizer,
    TOut * seed = NULL)
  {
    return this->AsExtendedQueryable<TIterable>().Aggregate(accumulate, finalizer, seed);
  }

  inline virtual bool All(std::function<bool(T)> condition) const = 0;
  inline virtual bool Any(std::function<bool(T)> condition) const = 0;
  inline virtual T & At(int index) const = 0;
  inline virtual double Average(std::function<double(T)> retrieveValue = [](T value) { return value; }) const = 0;
  inline virtual double Average(
    std::function<double(double, size_t)> divisor,
    std::function<double(T)> retrieveValue = [](T value) { return value; }) const = 0;
  inline virtual bool Contains(const T & item) const = 0;
  inline virtual size_t Count() = 0;
  inline virtual size_t CountIf(std::function<bool(T)> condition) const = 0;


  template<
    template<typename, typename ...> typename TIterable,
    template<typename, typename ...> typename TExceptions,
    typename TLessThan = std::less<T>,
    typename TAllocator = std::allocator<T>,
    typename ...TExceptionArgs>
  InternalIQueryable<T, TArgs...> & Except(
    const TExceptions<T, TExceptionArgs...> & exceptions,
    TLessThan lessThan = {},
    TAllocator allocator = {})
  {
    return this->AsExtendedQueryable<TIterable>().Except(exceptions, lessThan, allocator);
  }

  inline virtual T First(std::function<bool(T)> condition) = 0;
  inline virtual T First() = 0;
  inline virtual void ForEach(std::function<void(T)> action) const = 0;

  inline virtual T Last(std::function<bool(T)> condition) = 0;
  inline virtual T Last() = 0;
  inline virtual T Max() const = 0;
  inline virtual T Max(T startSeed) const = 0;

  template<template<typename, typename ...> typename TIterable, typename TOut>
  inline TOut Max(std::function<TOut(T)> retrieveValue) const
  {
    return this->AsExtendedQueryable<TIterable>().Max(retrieveValue);
  }

  template<template<typename, typename ...> typename TIterable, typename TOut>
  inline TOut Max(std::function<TOut(T)> retrieveValue, TOut startSeed) const
  {
    return this->AsExtendedQueryable<TIterable>().Max(retrieveValue, startSeed);
  }

  template<template<typename, typename ...> typename TIterable, typename TOut>
  inline T MaxItem(std::function<TOut(T)> retrieveValue) const
  {
    return this->AsExtendedQueryable<TIterable>().MaxItem(retrieveValue);
  }

  inline virtual T Min() const = 0;
  inline virtual T Min(T startSeed) const = 0;

  template<template<typename, typename ...> typename TIterable, typename TOut>
  inline TOut Min(std::function<TOut(T)> retrieveValue)
  {
    return this->AsExtendedQueryable<TIterable>().Min(retrieveValue);
  }

  template<template<typename, typename ...> typename TIterable, typename TOut>
  TOut Min(std::function<TOut(T)> retrieveValue, TOut startSeed) const
  {
    return this->AsExtendedQueryable<TIterable>().Min(retrieveValue, startSeed);
  }

  template<template<typename, typename ...> typename TIterable, typename TOut>
  inline T MinItem(std::function<TOut(T)> retrieveValue) const
  {
    return this->AsExtendedQueryable<TIterable>().MinItem(retrieveValue);
  }

  inline virtual double Range(std::function<double(T)> retrieveValue = [](T value) { return value; }) const = 0;

  template<template<typename, typename ...> typename TIterable, typename TOut>
  inline TOut Range(std::function<TOut(T)> retrieveValue)
  {
    return this->AsExtendedQueryable<TIterable>().Range(retrieveValue);
  }

  template<
    template<typename, typename ...> typename TIterable,
    typename TOut,
    typename ...TNewArgs>
  inline Queryable<TOut, TIterable, TNewArgs...> Select(
    std::function<TOut(T)> retrieveValue,
    TNewArgs... iterableParameters)
  {
    return this->AsExtendedQueryable<TIterable>().Select(retrieveValue, iterableParameters...);
  }

  template<
    template<typename, typename ...> typename TIterable,
    typename TLessThan = std::less<T>>
  inline void Sort(TLessThan lessThan = {})
  {
    this->AsExtendedQueryable<TIterable>().Sort(lessThan);
  }

  inline virtual void Take(int count) = 0;

  inline virtual double Sum(std::function<double(T)> retrieveValue = [](T value) { return value; }) const = 0;
//   inline virtual size_t Sum(std::function<size_t(T)> retrieveValue = [](T value) { return value; }) const = 0;
  inline virtual InternalIQueryable<T, TArgs...> & Where(std::function<bool(const T &)> condition) = 0;
};

#endif
