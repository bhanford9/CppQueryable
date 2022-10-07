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
// #include "SelectBuilders/SelectBuilder.hpp"
// #include "SelectBuilders/DequeSelectBuilder.hpp"
// #include "SelectBuilders/ListSelectBuilder.hpp"
// #include "SelectBuilders/MultiSetSelectBuilder.hpp"
// #include "SelectBuilders/SetSelectBuilder.hpp"
// #include "SelectBuilders/VectorSelectBuilder.hpp"
#include "Utilities/Casting.hpp"
#include "Utilities/StaticBuilders/QueryableStaticBuilder.hpp"

template<
  typename TStoring, 
  template<typename, typename ...> typename TIterable,
  typename TIterating,
  typename ...TArgs>
class IQueryable;
template<
  typename TStoring, 
  template<typename, typename ...> typename TIterable,
  typename TIterating,
  typename ...TArgs>
class ISortedQueryable;

template<
  typename TStoring, 
  template<typename, typename ...> typename TIterable,
  typename TIterating,
  typename ...TArgs>
class Queryable
{
protected:
  std::shared_ptr<InternalQueryable<TStoring, TIterable, TIterating, TArgs...>> queryable;
  Queryable() { }

public:
  virtual ~Queryable() { }

  Queryable(const IQueryable<TStoring, TIterable, TIterating, TArgs...> & other)
  {
    queryable = other.template AsExtendedQueryable<TIterable>().queryable;
  }

  Queryable(const ISortedQueryable<TStoring, TIterable, TIterating, TArgs...> & other)
  {
    queryable = other.template AsExtendedQueryable<TIterable>().queryable;
  }

  Queryable(Queryable<TStoring, TIterable, TIterating, TArgs...> && other)
    : queryable(std::move(other.queryable))
  {
  }
  Queryable(const Queryable<TStoring, TIterable, TIterating, TArgs...> & other)
    : queryable(other.queryable)
  {
  }

  Queryable<TStoring, TIterable, TIterating, TArgs...> & operator=(const Queryable<TStoring, TIterable, TIterating, TArgs...> & other)
  {
    this->queryable = other.queryable;
    return *this;
  }

  // I think these should be protected
  Queryable(std::shared_ptr<InternalQueryable<TStoring, TIterable, TIterating, TArgs...>> && other)
    : queryable(std::move(other))
  {
  }
  Queryable(InternalQueryable<TStoring, TIterable, TIterating, TArgs...> * other)
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

  template<typename TAllocator = std::allocator<TStoring>>
  inline std::deque<TStoring, TAllocator> ToDeque(TAllocator allocator = {}) const
  {
    return this->queryable->ToDeque(allocator);
  }

  inline std::deque<TStoring> ToDeque() const
  {
    return this->queryable->ToDeque();
  }

  template<typename TAllocator = std::allocator<TStoring>>
  inline std::list<TStoring, TAllocator> ToList(TAllocator allocator = {}) const
  {
    return this->queryable->ToList(allocator);
  }

  inline std::list<TStoring> ToList() const
  {
    return this->queryable->ToList();
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

  inline std::multiset<TStoring> ToMultiSet() const
  {
    return this->queryable->ToMultiSet();
  }

  template<typename TLessThan = std::less<TStoring>, typename TAllocator = std::allocator<TStoring>>
  inline std::set<TStoring, TLessThan, TAllocator> ToSet(TLessThan lessThan = {}, TAllocator allocator = {}) const
  {
    return this->queryable->ToSet(lessThan, allocator);
  }

  inline std::set<TStoring> ToSet() const
  {
    return this->queryable->ToSet();
  }

  template<typename TAllocator = std::allocator<TStoring>>
  inline std::vector<TStoring, TAllocator> ToVector(TAllocator allocator = {}) const
  {
    return this->queryable->ToVector(allocator);
  }

  inline std::vector<TStoring> ToVector() const
  {
    return this->queryable->ToVector();
  }

  inline Queryable<TStoring, TIterable, TIterating, TArgs...> ToQueryable()
  {
    this->queryable->GetRealized();
    return *this;
  }

  template<typename T = TIterating>
  inline T Aggregate(const std::function<T(T, TIterating)> & accumulate, T * seed = NULL)
  {
    return this->queryable->Aggregate(accumulate, seed);
  }

  template<typename TFinalized, typename T = TIterating>
  inline TFinalized Aggregate(
    const std::function<T(T, TIterating)> & accumulate,
    const std::function<TFinalized(T)> & finalizer,
    T * seed = NULL)
  {
    return this->queryable->Aggregate(accumulate, finalizer, seed);
  }

  inline bool All(std::function<bool(TIterating)> condition) const
  {
    return this->queryable->All(condition);
  }

  inline bool Any(std::function<bool(TIterating)> condition) const
  {
    return this->queryable->Any(condition);
  }

  inline TIterating & At(int index) const
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

  inline size_t Count()
  {
    return this->queryable->Count();
  }

  inline size_t CountIf(std::function<bool(TIterating)> condition) const
  {
    return this->queryable->CountIf(condition);
  }

  // inline bool Equal(const TIterable<TIterating, TArgs...> & collection) const
  // {
  //   return this->queryable->Equal(collection);
  // }
  //
  // inline bool Equal(
  //   const TIterable<TIterating, TArgs...> & collection,
  //   const std::function<bool(TIterating, TIterating)> & areEqual) const
  // {
  //   return this->queryable->Equal(collection, areEqual);
  // }
  //
  // inline bool Equal(const TIterable<TIterating, TArgs...> & collection, size_t collectionSize) const
  // {
  //   return this->queryable->Equal(collection, collectionSize);
  // }
  //
  // inline bool Equal(
  //   const TIterable<TIterating, TArgs...> & collection,
  //   size_t collectionSize,
  //   const std::function<bool(TIterating, TIterating)> & areEqual) const
  // {
  //   return this->queryable->Equal(collection, collectionSize, areEqual);
  // }

  template<
    template<typename, typename ...> typename TExceptions,
    typename TLessThan = std::less<TStoring>,
    typename TAllocator = std::allocator<TStoring>,
    typename ...TExceptionArgs>
  Queryable<TStoring, TIterable, TIterating, TArgs...> & Except(
    const TExceptions<TStoring, TExceptionArgs...> & exceptions,
    TLessThan lessThan = {},
    TAllocator allocator = {})
  {
    this->queryable->Except(exceptions, lessThan, allocator);
    // TODO --> make sure no slicing or other memory corruption happens with this
    return *this;
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
    this->queryable->ForEach(action);
  }

  inline QueryableType GetType() const
  {
    return this->queryable->GetType();
  }

  template<
    typename TKey,
    typename TAllocator = std::allocator<TStoring>>
  inline Queryable<
      Grouping<TKey, TStoring, TAllocator>,
      std::set,
      TIterating,
      std::less<Grouping<TKey, TStoring, TAllocator>>,
      std::allocator<Grouping<TKey, TStoring, TAllocator>>> GroupBy(
    const std::function<TKey(TIterating)> & getKey,
    std::function<bool(TKey, TKey)> lessThan = [](TKey a, TKey b) { return a < b; },
    TAllocator allocator = {})
  {
    using TGrouping = Grouping<TKey, TStoring, TAllocator>;
    using TSetIter = typename std::set<TGrouping>::iterator;

    std::set<TGrouping> groups;
    
    this->ForEach([&](TStoring value)
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

    Queryable<TGrouping, std::set, TIterating, std::less<TGrouping>, std::allocator<TGrouping>> queryable =
      Builders::FromInternalSet(std::move(setGroupedQueryable));

    return queryable;
  }

  // Join

  inline TIterating Last(std::function<bool(TIterating)> condition)
  {
    return this->queryable->Last(condition);
  }

  inline TIterating Last()
  {
    return this->queryable->Last();
  }

  template<typename T>
  inline TIterating MaxItem(std::function<T(TIterating)> retrieveValue) const
  {
    return this->queryable->MaxItem(retrieveValue);
  }

  template<typename T>
  inline T Max(std::function<T(TIterating)> retrieveValue) const
  {
    return this->queryable->Max(retrieveValue);
  }

  inline TIterating Max() const
  {
    return this->queryable->Max();
  }

  template<typename T>
  inline T Max(std::function<T(TIterating)> retrieveValue, T startSeed) const
  {
    return this->queryable->Max(retrieveValue, startSeed);
  }

  inline TIterating Max(TIterating startSeed) const
  {
    return this->queryable->Max(startSeed);
  }

  template<typename T>
  inline TIterating MinItem(std::function<T(TIterating)> retrieveValue) const
  {
    return this->queryable->MinItem(retrieveValue);
  }

  template<typename T>
  inline T Min(std::function<T(TIterating)> retrieveValue) const
  {
    return this->queryable->Min(retrieveValue);
  }

  inline TIterating Min() const
  {
    return this->queryable->Min();
  }

  template<typename T>
  inline T Min(std::function<T(TIterating)> retrieveValue, T startSeed) const
  {
    return this->queryable->Min(retrieveValue, startSeed);
  }

  inline TIterating Min(TIterating startSeed) const
  {
    return this->queryable->Min(startSeed);
  }

  template<typename T>
  inline T Range(std::function<T(TIterating)> retrieveValue) const
  {
    return this->queryable->Range(retrieveValue);
  }

  inline double Range(std::function<double(TIterating)> retrieveValue = [](TIterating value) { return value; }) const
  {
    return this->queryable->Range(retrieveValue);
  }

  template<typename TDestination, typename TDestinationAllocator = std::allocator<TDestination>>
    Queryable<TDestination, std::vector, TDestination, TDestinationAllocator> Select(
    std::function<TDestination(TIterating)> retrieveValue,
    TDestinationAllocator allocator = {})
  {
    Queryable<TDestination, std::vector, TDestination, TDestinationAllocator> mapQueryable(
      this->queryable->template Select<TDestination, TDestinationAllocator>(retrieveValue));

    return mapQueryable;
    // switch (this->queryable->GetType())
    // {
    //   // case QueryableType::Deque:
    //   //   Queryable<TDestination, std::vector, TDestination, TDestinationAllocator> dequeQueryable(
    //   //     this->queryable->DequeSelect(retrieveValue));
    //   //   return dequeQueryable;
    //   // break;
    //   // case QueryableType::List:
    //   //   Queryable<TDestination, std::vector, TDestination, TDestinationAllocator> listQueryable(
    //   //     this->queryable->ListSelect(retrieveValue));
    //   //   return listQueryable;
    //   // break;
    //   case QueryableType::Map:
    //   {
    //     Queryable<TDestination, std::vector, TDestination, TDestinationAllocator> mapQueryable(
    //       this->queryable->template MapSelect<TDestination, TDestinationAllocator>(retrieveValue));

    //     return mapQueryable;
    //   }
    //   break;
    //   // case QueryableType::MultiSet:
    //   //   Queryable<TDestination, std::vector, TDestination, TDestinationAllocator> multisetQueryable(
    //   //     this->queryable->MultiSetSelect(retrieveValue));
    //   //   return multisetQueryable;
    //   // break;
    //   // case QueryableType::Set:
    //   //   Queryable<TDestination, std::vector, TDestination, TDestinationAllocator> setQueryable(
    //   //     this->queryable->SetSelect(retrieveValue));
    //   //   return setQueryable;
    //   // break;
    //   // case QueryableType::Vector:
    //   //   Queryable<TDestination, std::vector, TDestination, TDestinationAllocator> vectorQueryable(
    //   //     this->queryable->VectorSelect(retrieveValue));
    //   //   return vectorQueryable;
    //   // break;
    //   // case QueryableType::Deque:
    //   // {
    //   //   DequeSelectBuilder<TStoring, T, TNewArgs...> selectBuilder;
    //   //   this->queryable->Select(
    //   //     retrieveValue,
    //   //     reinterpret_cast<SelectBuilder<TStoring, T, TIterable, TIterating, TNewArgs...>*>(&selectBuilder),
    //   //     iterableParameters...);

    //   //   std::shared_ptr<InternalQueryable<T, TIterable, TIterating, TNewArgs...>> newInternalQueryable(
    //   //     FutureStd::reinterpret_pointer_cast<InternalQueryable<T, TIterable, TIterating, TNewArgs...>>(selectBuilder.Get()));

    //   //   Queryable<T, TIterable, TIterating, TNewArgs...> newQueryable(std::move(newInternalQueryable));
    //   //   return newQueryable;
    //   //   break;
    //   // }
    //   // case QueryableType::List:
    //   // {
    //   //   ListSelectBuilder<TStoring, T, TNewArgs...> selectBuilder;
    //   //   this->queryable->Select(
    //   //     retrieveValue,
    //   //     reinterpret_cast<SelectBuilder<TStoring, T, TIterable, TIterating, TNewArgs...>*>(&selectBuilder),
    //   //     iterableParameters...);

    //   //   std::shared_ptr<InternalQueryable<T, TIterable, TIterating, TNewArgs...>> newInternalQueryable(
    //   //     FutureStd::reinterpret_pointer_cast<InternalQueryable<T, TIterable, TIterating, TNewArgs...>>(selectBuilder.Get()));

    //   //   Queryable<T, TIterable, TIterating, TNewArgs...> newQueryable(std::move(newInternalQueryable));
    //   //   return newQueryable;
    //   //   break;
    //   // }
    //   // case QueryableType::MultiSet:
    //   // {
    //   //   MultiSetSelectBuilder<TStoring, T, TNewArgs...> selectBuilder;
    //   //   this->queryable->Select(
    //   //     retrieveValue,
    //   //     reinterpret_cast<SelectBuilder<TStoring, T, TIterable, TIterating, TNewArgs...>*>(&selectBuilder),
    //   //     iterableParameters...);

    //   //   std::shared_ptr<InternalQueryable<T, TIterable, TIterating, TNewArgs...>> newInternalQueryable(
    //   //     FutureStd::reinterpret_pointer_cast<InternalQueryable<T, TIterable, TIterating, TNewArgs...>>(selectBuilder.Get()));

    //   //   Queryable<T, TIterable, TIterating, TNewArgs...> newQueryable(std::move(newInternalQueryable));
    //   //   return newQueryable;
    //   //   break;
    //   // }
    //   // case QueryableType::Set:
    //   // {
    //   //   SetSelectBuilder<TStoring, T, TNewArgs...> selectBuilder;
    //   //   this->queryable->Select(
    //   //     retrieveValue,
    //   //     reinterpret_cast<SelectBuilder<TStoring, T, TIterable, TIterating, TNewArgs...>*>(&selectBuilder),
    //   //     iterableParameters...);

    //   //   std::shared_ptr<InternalQueryable<T, TIterable, TIterating, TNewArgs...>> newInternalQueryable(
    //   //     FutureStd::reinterpret_pointer_cast<InternalQueryable<T, TIterable, TIterating, TNewArgs...>>(selectBuilder.Get()));

    //   //   Queryable<T, TIterable, TIterating, TNewArgs...> newQueryable(std::move(newInternalQueryable));
    //   //   return newQueryable;
    //   //   break;
    //   // }
    //   // case QueryableType::Vector:
    //   // {
    //   //   VectorSelectBuilder<TStoring, T, TNewArgs...> selectBuilder;
    //   //   this->queryable->Select(
    //   //     retrieveValue,
    //   //     reinterpret_cast<SelectBuilder<TStoring, T, TIterable, TIterating, TNewArgs...>*>(&selectBuilder),
    //   //     iterableParameters...);

    //   //   std::shared_ptr<InternalQueryable<T, TIterable, TIterating, TNewArgs...>> newInternalQueryable(
    //   //     FutureStd::reinterpret_pointer_cast<InternalQueryable<T, TIterable, TIterating, TNewArgs...>>(selectBuilder.Get()));

    //   //   Queryable<T, TIterable, TIterating, TNewArgs...> newQueryable(std::move(newInternalQueryable));
    //   //   return newQueryable;
    //   //   break;
    //   // }
    //   case QueryableType::Deque:
    //   case QueryableType::List:
    //   case QueryableType::MultiSet:
    //   case QueryableType::Set:
    //   case QueryableType::Vector:
    //   default: throw std::runtime_error("should not reach here");
    // }
  }

  inline Queryable<TStoring, TIterable, TIterating, TArgs...> & Skip(int count)
  {
    this->queryable->Skip(count);
    return *this;
  }

  inline Queryable<TStoring, TIterable, TIterating, TArgs...> & SkipWhile(std::function<bool(TIterating)> && doSkip)
  {    
    this->queryable->SkipWhile(std::move(doSkip));
    return *this;
  }

  template<typename TLessThan = std::less<TStoring>>
  void Sort(TLessThan lessThan = {})
  {
    this->queryable->Sort(lessThan);
  }

  inline double Sum(std::function<double(TIterating)> retrieveValue = [](TIterating value) { return value; }) const
  {
    return this->queryable->Sum(retrieveValue);
  }

  // inline size_t Sum(std::function<size_t(TIterating)> retrieveValue = [](TIterating value) { return value; }) const
  // {
  //   return this->queryable->Sum(retrieveValue);
  // }

  // inline TIterating Sum() const
  // {
  //   return this->queryable->Sum();
  // }

  inline Queryable<TStoring, TIterable, TIterating, TArgs...> & Take(int count)
  {
    this->queryable->Take(count);
    return *this;
  }

  inline Queryable<TStoring, TIterable, TIterating, TArgs...> & TakeWhile(std::function<bool(TIterating)> && doTake)
  {    
    this->queryable->TakeWhile(std::move(doTake));
    return *this;
  }

  inline Queryable<TStoring, TIterable, TIterating, TArgs...> & Where(std::function<bool(const TIterating &)> condition)
  {
    this->queryable->Where(condition);
    return *this;
  }
};

#endif
