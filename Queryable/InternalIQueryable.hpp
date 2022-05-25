#ifndef CPPQUERYABLE_QUERYABLE_INTERNALIQUERYABLE_H
#define CPPQUERYABLE_QUERYABLE_INTERNALIQUERYABLE_H

#include <deque>
#include <functional>
#include <list>
#include <set>
#include <vector>

#include "IQueryable.hpp"
#include "Queryable.hpp"
#include "QueryableAliases.hpp"
#include "QueryableType.hpp"

template<
  typename TObj,
  template<typename, typename ...> typename TIterable,
  typename ...TArgs>
class Queryable;

template<typename T, typename ...TArgs>
class IQueryable;

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

  inline QueryableList<T, TArgs...> & AsQueryableList() const
  {
    if (this->GetType() != QueryableType::List)
    {
      throw std::invalid_argument("Queryable type of TODO cannot be treated as a QueryableList.");
    }

    return *const_cast<QueryableList<T, TArgs...>*>(dynamic_cast<const QueryableList<T, TArgs...>*>(this));
  }

  inline QueryableMultiSet<T, TArgs...> & AsQueryableMultiSet() const
  {
    if (this->GetType() != QueryableType::MultiSet)
    {
      throw std::invalid_argument("Queryable type of TODO cannot be treated as a QueryableMultiSet.");
    }

    return *const_cast<QueryableMultiSet<T, TArgs...>*>(dynamic_cast<const QueryableMultiSet<T, TArgs...>*>(this));
  }

  inline QueryableSet<T, TArgs...> & AsQueryableSet() const
  {
    if (this->GetType() != QueryableType::Set)
    {
      throw std::invalid_argument("Queryable type of TODO cannot be treated as a QueryableSet.");
    }

    return *const_cast<QueryableSet<T, TArgs...>*>(dynamic_cast<const QueryableSet<T, TArgs...>*>(this));
  }

  inline QueryableVector<T, TArgs...> & AsQueryableVector() const
  {
    if (this->GetType() != QueryableType::Vector)
    {
      throw std::invalid_argument("Queryable type of TODO cannot be treated as a QueryableVector.");
    }

    return *const_cast<QueryableVector<T, TArgs...>*>(dynamic_cast<const QueryableVector<T, TArgs...>*>(this));
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


  // inline virtual std::deque<T, TArgs...> ToDeque() const = 0;
  // inline virtual std::list<T, TArgs...> ToList() const = 0;
  // inline virtual std::multiset<T, TArgs...> ToMultiSet() const = 0;
  // inline virtual std::set<T, TArgs...> ToSet() const = 0;
  // inline virtual std::vector<T, TArgs...> ToVector() const = 0;

  inline virtual bool All(std::function<bool(T)> condition) const = 0;
  inline virtual bool Any(std::function<bool(T)> condition) const = 0;
  inline virtual T & At(int index) const = 0;
  inline virtual double Average(std::function<double(T)> retrieveValue) const = 0;
  inline virtual double Average(
    std::function<double(double, size_t)> divisor,
    std::function<double(T)> retrieveValue = [](T value) { return value; }) const = 0;
  inline virtual double Average() const = 0;
  template<template<typename, typename ...> typename TIterable>
  inline T Average(std::function<T(const T &, size_t)> divisor) const
  {
    return this->AsExtendedQueryable<TIterable>().Average(divisor);
  }
  inline virtual bool Contains(const T & item) const = 0;
  inline virtual size_t Count() = 0;
  inline virtual size_t CountIf(std::function<bool(T)> condition) const = 0;

  // virtual TODO
  // virtual all the equal methods will need to have overloads for each container type

  inline virtual T First(std::function<bool(T)> condition) = 0;
  inline virtual T First() = 0;
  inline virtual void ForEach(std::function<void(T)> action) const = 0;

  inline virtual T Last(std::function<bool(T)> condition) = 0;
  inline virtual T Last() = 0;
  inline virtual T Max() const = 0;
  inline virtual T Max(T startSeed) const = 0;
  inline virtual T Min() const = 0;
  inline virtual T Min(T startSeed) const = 0;
  inline virtual double Range(std::function<double(T)> retrieveValue) const = 0;

  template<
    typename TOut,
    template<typename, typename ...> typename TIterable,
    typename ...TNewArgs>
  inline InternalIQueryable<TOut, TNewArgs...> & Select(
    std::function<TOut(T)> retrieveValue,
    TNewArgs... iterableParameters)
  {
    return this->AsExtendedQueryable<TIterable>().Select(retrieveValue, iterableParameters...);
  }

  inline virtual double Sum(std::function<double(T)> retrieveValue = [](T value) { return value; }) const = 0;
  inline virtual size_t Sum(std::function<size_t(T)> retrieveValue = [](T value) { return value; }) const = 0;
  inline virtual InternalIQueryable<T, TArgs...> & Where(std::function<bool(const T &)> condition) = 0;
};

#endif
