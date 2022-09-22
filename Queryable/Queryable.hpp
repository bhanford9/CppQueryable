#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLE_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLE_H

#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <type_traits>
#include <utility>

#include "InternalQueryable.hpp"
#include "IQueryable.hpp"
#include "ISortedQueryable.hpp"
#include "SelectBuilders/SelectBuilder.hpp"
#include "SelectBuilders/DequeSelectBuilder.hpp"
#include "SelectBuilders/ListSelectBuilder.hpp"
#include "SelectBuilders/MultiSetSelectBuilder.hpp"
#include "SelectBuilders/SetSelectBuilder.hpp"
#include "SelectBuilders/VectorSelectBuilder.hpp"
#include "Utilities/Casting.hpp"
#include "Utilities/StaticBuilders/QueryableStaticBuilder.hpp"

template<
  typename T, 
  template<typename, typename ...> typename TIterable,
  typename ...TArgs>
class IQueryable;
template<
  typename T, 
  template<typename, typename ...> typename TIterable,
  typename ...TArgs>
class ISortedQueryable;

template<
  typename TObj,
  template<typename, typename ...> typename TIterable,
  typename ...TArgs>
class Queryable
{
protected:
  std::shared_ptr<InternalQueryable<TObj, TIterable, TArgs...>> queryable;
  Queryable() { }

public:
  virtual ~Queryable() { }

  Queryable(const IQueryable<TObj, TIterable, TArgs...> & other)
  {
    queryable = other.template AsExtendedQueryable<TIterable>().queryable;
  }

  Queryable(const ISortedQueryable<TObj, TIterable, TArgs...> & other)
  {
    queryable = other.template AsExtendedQueryable<TIterable>().queryable;
  }

  Queryable(Queryable<TObj, TIterable, TArgs...> && other)
    : queryable(std::move(other.queryable))
  {
  }
  Queryable(const Queryable<TObj, TIterable, TArgs...> & other)
    : queryable(other.queryable)
  {
  }

  Queryable<TObj, TIterable, TArgs...> & operator=(const Queryable<TObj, TIterable, TArgs...> & other)
  {
    this->queryable = other.queryable;
    return *this;
  }

  // I think these should be protected
  Queryable(std::shared_ptr<InternalQueryable<TObj, TIterable, TArgs...>> && other)
    : queryable(std::move(other))
  {
  }
  Queryable(InternalQueryable<TObj, TIterable, TArgs...> * other)
  {
    this->queryable.reset(other);
  }

  template<typename TAllocator>
  TAllocator GetAllocator()
  {
    return this->queryable->template GetAllocator<TAllocator>();
  }

  template<typename TLessThan>
  TLessThan GetValueCompare()
  {
    return this->queryable->GetValueCompare();
  }

  template<typename TAllocator = std::allocator<TObj>>
  inline std::deque<TObj, TAllocator> ToDeque(TAllocator allocator = {}) const
  {
    return this->queryable->ToDeque(allocator);
  }

  inline std::deque<TObj> ToDeque() const
  {
    return this->queryable->ToDeque();
  }

  template<typename TAllocator = std::allocator<TObj>>
  inline std::list<TObj, TAllocator> ToList(TAllocator allocator = {}) const
  {
    return this->queryable->ToList(allocator);
  }

  inline std::list<TObj> ToList() const
  {
    return this->queryable->ToList();
  }

  template<
    typename TKey,
    typename TValue = TObj,
    typename TLessThan = std::less<TKey>,
    typename TAllocator = std::allocator<std::pair<const TKey, TValue>>>
  inline std::map<const TKey, TValue, TLessThan, TAllocator> ToMap(
    std::function<TKey(TObj)> getKey,
    std::function<TValue(TObj)> getValue,
    TLessThan keyCompare = {},
    TAllocator pairAllocator = {})
  {
    return this->queryable->ToMap(getKey, getValue, keyCompare, pairAllocator);
  }

  template<typename TLessThan = std::less<TObj>, typename TAllocator = std::allocator<TObj>>
  inline std::multiset<TObj, TLessThan, TAllocator> ToMultiSet(TLessThan lessThan = {}, TAllocator allocator = {}) const
  {
    return this->queryable->ToMultiSet(lessThan, allocator);
  }

  inline std::multiset<TObj> ToMultiSet() const
  {
    return this->queryable->ToMultiSet();
  }

  template<typename TLessThan = std::less<TObj>, typename TAllocator = std::allocator<TObj>>
  inline std::set<TObj, TLessThan, TAllocator> ToSet(TLessThan lessThan = {}, TAllocator allocator = {}) const
  {
    return this->queryable->ToSet(lessThan, allocator);
  }

  inline std::set<TObj> ToSet() const
  {
    return this->queryable->ToSet();
  }

  template<typename TAllocator = std::allocator<TObj>>
  inline std::vector<TObj, TAllocator> ToVector(TAllocator allocator = {}) const
  {
    return this->queryable->ToVector(allocator);
  }

  inline std::vector<TObj> ToVector() const
  {
    return this->queryable->ToVector();
  }

  inline Queryable<TObj, TIterable, TArgs...> ToQueryable()
  {
    this->queryable->GetRealized();
    return *this;
  }

  template<typename T = TObj>
  inline T Aggregate(const std::function<T(T, TObj)> & accumulate, T * seed = NULL)
  {
    return this->queryable->Aggregate(accumulate, seed);
  }

  template<typename TFinalized, typename T = TObj>
  inline TFinalized Aggregate(
    const std::function<T(T, TObj)> & accumulate,
    const std::function<TFinalized(T)> & finalizer,
    T * seed = NULL)
  {
    return this->queryable->Aggregate(accumulate, finalizer, seed);
  }

  inline bool All(std::function<bool(TObj)> condition) const
  {
    return this->queryable->All(condition);
  }

  inline bool Any(std::function<bool(TObj)> condition) const
  {
    return this->queryable->Any(condition);
  }

  inline TObj & At(int index) const
  {
    return this->queryable->At(index);
  }

  inline double Average(std::function<double(TObj)> retrieveValue = [](TObj value) { return value; }) const
  {
    return this->queryable->Average(retrieveValue);
  }

  inline double Average(
    std::function<double(double, size_t)> divisor,
    std::function<double(TObj)> retrieveValue = [](TObj value) { return value; }) const
  {
    return this->queryable->Average(divisor, retrieveValue);
  }

  inline bool Contains(const TObj & item) const
  {
    return this->queryable->Contains(item);
  }

  inline size_t Count()
  {
    return this->queryable->Count();
  }

  inline size_t CountIf(std::function<bool(TObj)> condition) const
  {
    return this->queryable->CountIf(condition);
  }

  // inline bool Equal(const TIterable<TObj, TArgs...> & collection) const
  // {
  //   return this->queryable->Equal(collection);
  // }
  //
  // inline bool Equal(
  //   const TIterable<TObj, TArgs...> & collection,
  //   const std::function<bool(TObj, TObj)> & areEqual) const
  // {
  //   return this->queryable->Equal(collection, areEqual);
  // }
  //
  // inline bool Equal(const TIterable<TObj, TArgs...> & collection, size_t collectionSize) const
  // {
  //   return this->queryable->Equal(collection, collectionSize);
  // }
  //
  // inline bool Equal(
  //   const TIterable<TObj, TArgs...> & collection,
  //   size_t collectionSize,
  //   const std::function<bool(TObj, TObj)> & areEqual) const
  // {
  //   return this->queryable->Equal(collection, collectionSize, areEqual);
  // }

  template<
    template<typename, typename ...> typename TExceptions,
    typename TLessThan = std::less<TObj>,
    typename TAllocator = std::allocator<TObj>,
    typename ...TExceptionArgs>
  Queryable<TObj, TIterable, TArgs...> & Except(
    const TExceptions<TObj, TExceptionArgs...> & exceptions,
    TLessThan lessThan = {},
    TAllocator allocator = {})
  {
    this->queryable->Except(exceptions, lessThan, allocator);
    // TODO --> make sure no slicing or other memory corruption happens with this
    return *this;
  }

  inline TObj First(std::function<bool(TObj)> condition)
  {
    return this->queryable->First(condition);
  }

  inline TObj First()
  {
    return this->queryable->First();
  }

  inline void ForEach(std::function<void(TObj)> action) const
  {
    this->queryable->ForEach(action);
  }

  inline QueryableType GetType() const
  {
    return this->queryable->GetType();
  }

  template<
    typename TKey,
    typename TAllocator = std::allocator<TObj>>
  inline Queryable<
      Grouping<TKey, TObj, TAllocator>,
      std::set,
      std::less<Grouping<TKey, TObj, TAllocator>>,
      std::allocator<Grouping<TKey, TObj, TAllocator>>> GroupBy(
    const std::function<TKey(TObj)> & getKey,
    std::function<bool(TKey, TKey)> lessThan = [](TKey a, TKey b) { return a < b; },
    TAllocator allocator = {})
  {
    using TGrouping = Grouping<TKey, TObj, TAllocator>;
    using TSetIter = typename std::set<TGrouping>::iterator;

    std::set<TGrouping> groups;
    
    this->ForEach([&](TObj value)
    {
      std::pair<TSetIter, bool> result = 
        groups.insert(TGrouping(
          getKey(value),
          value,
          lessThan,
          allocator));

      if (!result.second)
      {
        TGrouping group = *result.first;
        group.Add(value);
      }
    });

    // TODO --> Grouping should maybe be an unordered_set instead
    SetInternalQueryable<TGrouping> setGroupedQueryable(std::move(groups));

    Queryable<TGrouping, std::set, std::less<TGrouping>, std::allocator<TGrouping>> queryable =
      Builders::FromInternalSet(std::move(setGroupedQueryable));

    return queryable;
  }

  // Join

  inline TObj Last(std::function<bool(TObj)> condition)
  {
    return this->queryable->Last(condition);
  }

  inline TObj Last()
  {
    return this->queryable->Last();
  }

  template<typename T>
  inline TObj MaxItem(std::function<T(TObj)> retrieveValue) const
  {
    return this->queryable->MaxItem(retrieveValue);
  }

  template<typename T>
  inline T Max(std::function<T(TObj)> retrieveValue) const
  {
    return this->queryable->Max(retrieveValue);
  }

  inline TObj Max() const
  {
    return this->queryable->Max();
  }

  template<typename T>
  inline T Max(std::function<T(TObj)> retrieveValue, T startSeed) const
  {
    return this->queryable->Max(retrieveValue, startSeed);
  }

  inline TObj Max(TObj startSeed) const
  {
    return this->queryable->Max(startSeed);
  }

  template<typename T>
  inline TObj MinItem(std::function<T(TObj)> retrieveValue) const
  {
    return this->queryable->MinItem(retrieveValue);
  }

  template<typename T>
  inline T Min(std::function<T(TObj)> retrieveValue) const
  {
    return this->queryable->Min(retrieveValue);
  }

  inline TObj Min() const
  {
    return this->queryable->Min();
  }

  template<typename T>
  inline T Min(std::function<T(TObj)> retrieveValue, T startSeed) const
  {
    return this->queryable->Min(retrieveValue, startSeed);
  }

  inline TObj Min(TObj startSeed) const
  {
    return this->queryable->Min(startSeed);
  }

  template<typename T>
  inline T Range(std::function<T(TObj)> retrieveValue) const
  {
    return this->queryable->Range(retrieveValue);
  }

  inline double Range(std::function<double(TObj)> retrieveValue = [](TObj value) { return value; }) const
  {
    return this->queryable->Range(retrieveValue);
  }

  template<typename T, typename ...TNewArgs>
    Queryable<T, TIterable, TNewArgs...> Select(
    std::function<T(TObj)> retrieveValue,
    TNewArgs... iterableParameters)
  {
    // TODO --> this is terribly ugly, find a better way to handle it
    switch (this->queryable->GetType())
    {
      case QueryableType::Deque:
      {
        DequeSelectBuilder<TObj, T, TNewArgs...> selectBuilder;
        this->queryable->Select(
          retrieveValue,
          reinterpret_cast<SelectBuilder<TObj, T, TIterable, TNewArgs...>*>(&selectBuilder),
          iterableParameters...);

        std::shared_ptr<InternalQueryable<T, TIterable, TNewArgs...>> newInternalQueryable(
          FutureStd::reinterpret_pointer_cast<InternalQueryable<T, TIterable, TNewArgs...>>(selectBuilder.Get()));

        Queryable<T, TIterable, TNewArgs...> newQueryable(std::move(newInternalQueryable));
        return newQueryable;
        break;
      }
      case QueryableType::List:
      {
        ListSelectBuilder<TObj, T, TNewArgs...> selectBuilder;
        this->queryable->Select(
          retrieveValue,
          reinterpret_cast<SelectBuilder<TObj, T, TIterable, TNewArgs...>*>(&selectBuilder),
          iterableParameters...);

        std::shared_ptr<InternalQueryable<T, TIterable, TNewArgs...>> newInternalQueryable(
          FutureStd::reinterpret_pointer_cast<InternalQueryable<T, TIterable, TNewArgs...>>(selectBuilder.Get()));

        Queryable<T, TIterable, TNewArgs...> newQueryable(std::move(newInternalQueryable));
        return newQueryable;
        break;
      }
      case QueryableType::MultiSet:
      {
        MultiSetSelectBuilder<TObj, T, TNewArgs...> selectBuilder;
        this->queryable->Select(
          retrieveValue,
          reinterpret_cast<SelectBuilder<TObj, T, TIterable, TNewArgs...>*>(&selectBuilder),
          iterableParameters...);

        std::shared_ptr<InternalQueryable<T, TIterable, TNewArgs...>> newInternalQueryable(
          FutureStd::reinterpret_pointer_cast<InternalQueryable<T, TIterable, TNewArgs...>>(selectBuilder.Get()));

        Queryable<T, TIterable, TNewArgs...> newQueryable(std::move(newInternalQueryable));
        return newQueryable;
        break;
      }
      case QueryableType::Set:
      {
        SetSelectBuilder<TObj, T, TNewArgs...> selectBuilder;
        this->queryable->Select(
          retrieveValue,
          reinterpret_cast<SelectBuilder<TObj, T, TIterable, TNewArgs...>*>(&selectBuilder),
          iterableParameters...);

        std::shared_ptr<InternalQueryable<T, TIterable, TNewArgs...>> newInternalQueryable(
          FutureStd::reinterpret_pointer_cast<InternalQueryable<T, TIterable, TNewArgs...>>(selectBuilder.Get()));

        Queryable<T, TIterable, TNewArgs...> newQueryable(std::move(newInternalQueryable));
        return newQueryable;
        break;
      }
      case QueryableType::Vector:
      {
        VectorSelectBuilder<TObj, T, TNewArgs...> selectBuilder;
        this->queryable->Select(
          retrieveValue,
          reinterpret_cast<SelectBuilder<TObj, T, TIterable, TNewArgs...>*>(&selectBuilder),
          iterableParameters...);

        std::shared_ptr<InternalQueryable<T, TIterable, TNewArgs...>> newInternalQueryable(
          FutureStd::reinterpret_pointer_cast<InternalQueryable<T, TIterable, TNewArgs...>>(selectBuilder.Get()));

        Queryable<T, TIterable, TNewArgs...> newQueryable(std::move(newInternalQueryable));
        return newQueryable;
        break;
      }
      default: throw std::runtime_error("should not reach here");
    }
  }

  inline void Skip(int count)
  {
    this->queryable->Skip(count);
  }

  inline void SkipWhile(std::function<bool(TObj)> && doSkip)
  {    
    this->queryable->SkipWhile(std::move(doSkip));
  }

  template<typename TLessThan = std::less<TObj>>
  void Sort(TLessThan lessThan = {})
  {
    this->queryable->Sort(lessThan);
  }

  inline double Sum(std::function<double(TObj)> retrieveValue = [](TObj value) { return value; }) const
  {
    return this->queryable->Sum(retrieveValue);
  }

  // inline size_t Sum(std::function<size_t(TObj)> retrieveValue = [](TObj value) { return value; }) const
  // {
  //   return this->queryable->Sum(retrieveValue);
  // }

  // inline TObj Sum() const
  // {
  //   return this->queryable->Sum();
  // }

  inline void Take(int count)
  {
    this->queryable->Take(count);
  }

  inline void TakeWhile(std::function<bool(TObj)> && doTake)
  {    
    this->queryable->TakeWhile(std::move(doTake));
  }

  inline Queryable<TObj, TIterable, TArgs...> & Where(std::function<bool(const TObj &)> condition)
  {
    this->queryable->Where(condition);
    return *this;
  }
};

#endif
