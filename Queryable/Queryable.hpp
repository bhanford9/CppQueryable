#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLE_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLE_H

#include <iostream>
#include <memory>
#include <type_traits>
#include <utility>

#include "InternalIQueryable.hpp"
#include "InternalQueryable.hpp"
#include "IQueryable.hpp"
#include "ISortedQueryable.hpp"
// #include "QueryableTypeConverters/DequeQueryableTypeConverter.hpp"
// #include "QueryableTypeConverters/ListQueryableTypeConverter.hpp"
// #include "QueryableTypeConverters/MultiSetQueryableTypeConverter.hpp"
// #include "QueryableTypeConverters/SetQueryableTypeConverter.hpp"
// #include "QueryableTypeConverters/VectorQueryableTypeConverter.hpp"
#include "SelectBuilders/SelectBuilder.hpp"
#include "SelectBuilders/DequeSelectBuilder.hpp"
#include "SelectBuilders/ListSelectBuilder.hpp"
#include "SelectBuilders/MultiSetSelectBuilder.hpp"
#include "SelectBuilders/SetSelectBuilder.hpp"
#include "SelectBuilders/VectorSelectBuilder.hpp"
#include "Utilities/Casting.hpp"

template<typename T, typename ...TArgs>
class IQueryable;
template<typename T, typename ...TArgs>
class ISortedQueryable;
template<typename T, typename ...TArgs>
class InternalIQueryable;

template<
  typename TObj,
  template<typename, typename ...> typename TIterable,
  typename ...TArgs>
class Queryable : public InternalIQueryable<TObj, TArgs...>
{
protected:
  std::shared_ptr<InternalQueryable<TObj, TIterable, TArgs...>> queryable;
  Queryable() { }

public:
  virtual ~Queryable() { }

  Queryable(const IQueryable<TObj, TArgs...> & other)
  {
    queryable = other.template AsExtendedQueryable<TIterable>().queryable;
  }

  Queryable(const ISortedQueryable<TObj, TArgs...> & other)
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

  // These can't actually be implemented here
  // Queryable(const TIterable<TObj, TArgs...> & items);
  // Queryable(TIterable<TObj, TArgs...> && items);

  // All these reinterpret_casts should not be necessary. Need to figure out why the inheritance
  // is not allowing the shared_ptr<child> to be used as shared_ptr<parent>
  //
  // I don't think I like all these being in here either.
  //   - FrontInternal* should not be accessible to anyone outside the library and can be put in its own location
  //   - FromIterable* is basically what QueryBuilder is doing, so it can probably be moved there
  template<typename TAllocator = std::allocator<TObj>>
  static Queryable<TObj, std::deque, TAllocator> FromInternalDeque(DequeInternalQueryable<TObj, TAllocator> && other)
  {
    Queryable<TObj, std::deque, TAllocator> queryable(
      std::move(
        FutureStd::reinterpret_pointer_cast<InternalQueryable<TObj, std::deque, TAllocator>>(
          std::make_shared<DequeInternalQueryable<TObj, TAllocator>>(other))));
    return queryable;
  }

  template<typename TAllocator = std::allocator<TObj>>
  static Queryable<TObj, std::list, TAllocator> FromInternalList(ListInternalQueryable<TObj, TAllocator> && other)
  {
    Queryable<TObj, std::list, TAllocator> queryable(
      std::move(
        FutureStd::reinterpret_pointer_cast<InternalQueryable<TObj, std::list, TAllocator>>(
          std::make_shared<ListInternalQueryable<TObj, TAllocator>>(other))));
    return queryable;
  }

  template<typename TLessThan = std::less<TObj>, typename TAllocator = std::allocator<TObj>>
  static Queryable<TObj, std::multiset, TLessThan, TAllocator> FromInternalMultiSet (MultiSetInternalQueryable<TObj, TLessThan, TAllocator> && other)
  {
    Queryable<TObj, std::multiset, TLessThan, TAllocator> queryable(
      std::move(
        FutureStd::reinterpret_pointer_cast<InternalQueryable<TObj, std::multiset, TLessThan, TAllocator>>(
          std::make_shared<MultiSetInternalQueryable<TObj, TLessThan, TAllocator>>(other))));
  }

  template<typename TLessThan = std::less<TObj>, typename TAllocator = std::allocator<TObj>>
  static Queryable<TObj, std::set, TLessThan, TAllocator> FromInternalSet (SetInternalQueryable<TObj, TLessThan, TAllocator> && other)
  {
    Queryable<TObj, std::set, TLessThan, TAllocator> queryable(
      std::move(
        FutureStd::reinterpret_pointer_cast<InternalQueryable<TObj, std::set, TLessThan, TAllocator>>(
          std::make_shared<SetInternalQueryable<TObj, TLessThan, TAllocator>>(other))));
  }

  template<typename TAllocator = std::allocator<TObj>>
  static Queryable<TObj, std::vector, TAllocator> FromInternalVector(VectorInternalQueryable<TObj, TAllocator> && other)
  {
    Queryable<TObj, std::vector, TAllocator> queryable(
      std::move(
        FutureStd::reinterpret_pointer_cast<InternalQueryable<TObj, std::vector, TAllocator>>(
          std::make_shared<VectorInternalQueryable<TObj, TAllocator>>(other))));
    return queryable;
  }

  template<typename TAllocator = std::allocator<TObj>>
  static Queryable<TObj, std::deque, TAllocator> FromInternalDeque(const DequeInternalQueryable<TObj, TAllocator> & other)
  {
    Queryable<TObj, std::deque, TAllocator> queryable(
      FutureStd::reinterpret_pointer_cast<InternalQueryable<TObj, std::deque, TAllocator>>(
        std::make_shared<DequeInternalQueryable<TObj, TAllocator>>(other)));
    return queryable;
  }

  template<typename TAllocator = std::allocator<TObj>>
  static Queryable<TObj, std::list, TAllocator> FromInternalList(const ListInternalQueryable<TObj, TAllocator> & other)
  {
    Queryable<TObj, std::list, TAllocator> queryable(
      FutureStd::reinterpret_pointer_cast<InternalQueryable<TObj, std::list, TAllocator>>(
        std::make_shared<ListInternalQueryable<TObj, TAllocator>>(other)));
    return queryable;
  }

  template<typename TLessThan = std::less<TObj>, typename TAllocator = std::allocator<TObj>>
  static Queryable<TObj, std::multiset, TLessThan, TAllocator> FromInternalMultiSet (const MultiSetInternalQueryable<TObj, TLessThan, TAllocator> & other)
  {
    Queryable<TObj, std::multiset, TLessThan, TAllocator> queryable(
      FutureStd::reinterpret_pointer_cast<InternalQueryable<TObj, std::multiset, TLessThan, TAllocator>>(
        std::make_shared<MultiSetInternalQueryable<TObj, TLessThan, TAllocator>>(other)));
    return queryable;
  }

  template<typename TLessThan = std::less<TObj>, typename TAllocator = std::allocator<TObj>>
  static Queryable<TObj, std::set, TLessThan, TAllocator> FromInternalSet (const SetInternalQueryable<TObj, TLessThan, TAllocator> & other)
  {
    Queryable<TObj, std::set, TLessThan, TAllocator> queryable(
      FutureStd::reinterpret_pointer_cast<InternalQueryable<TObj, std::set, TLessThan, TAllocator>>(
        std::make_shared<SetInternalQueryable<TObj, TLessThan, TAllocator>>(other)));
    return queryable;
  }

  template<typename TAllocator = std::allocator<TObj>>
  static Queryable<TObj, std::vector, TAllocator> FromInternalVector(const VectorInternalQueryable<TObj, TAllocator> & other)
  {
    Queryable<TObj, std::vector, TAllocator> queryable(
      FutureStd::reinterpret_pointer_cast<InternalQueryable<TObj, std::vector, TAllocator>>(
        std::make_shared<VectorInternalQueryable<TObj, TAllocator>>(other)));
    return queryable;
  }

  template<typename TAllocator = std::allocator<TObj>>
  static Queryable<TObj, std::deque, TAllocator> FromDeque2(const std::deque<TObj, TAllocator> & iterable)
  {
    Queryable<TObj, std::deque, TAllocator> queryable(
      FutureStd::reinterpret_pointer_cast<InternalQueryable<TObj, std::deque, TAllocator>>(
        std::make_shared<DequeInternalQueryable<TObj, TAllocator>>(iterable)));
    return queryable;
  }
  static Queryable<TObj, std::deque> FromDeque(const std::deque<TObj> & iterable)
  {
    Queryable<TObj, std::deque> queryable(
      FutureStd::reinterpret_pointer_cast<InternalQueryable<TObj, std::deque>>(
        std::make_shared<DequeInternalQueryable<TObj>>(iterable)));
    return queryable;
  }

  template<typename TAllocator = std::allocator<TObj>>
  static Queryable<TObj, std::list, TAllocator> FromList2(const std::list<TObj, TAllocator> & iterable)
  {
    Queryable<TObj, std::list, TAllocator> queryable(
      FutureStd::reinterpret_pointer_cast<InternalQueryable<TObj, std::list, TAllocator>>(
        std::make_shared<ListInternalQueryable<TObj, TAllocator>>(iterable)));
    return queryable;
  }
  static Queryable<TObj, std::list> FromList(const std::list<TObj> & iterable)
  {
    Queryable<TObj, std::list> queryable(
      FutureStd::reinterpret_pointer_cast<InternalQueryable<TObj, std::list>>(
        std::make_shared<ListInternalQueryable<TObj>>(iterable)));
    return queryable;
  }

  template<typename TLessThan = std::less<TObj>, typename TAllocator = std::allocator<TObj>>
  static Queryable<TObj, std::multiset, TLessThan, TAllocator> FromMultiSet2(const std::multiset<TObj, TLessThan, TAllocator> & iterable)
  {
    Queryable<TObj, std::multiset, TLessThan, TAllocator> queryable(
      FutureStd::reinterpret_pointer_cast<InternalQueryable<TObj, std::multiset, TLessThan, TAllocator>>(
        std::make_shared<MultiSetInternalQueryable<TObj, TLessThan, TAllocator>>(iterable)));
    return queryable;
  }
  // template<typename TLessThan = std::less<TObj>>
  // static Queryable<TObj, std::multiset, TLessThan> FromMultiSet(const std::multiset<TObj, TLessThan> & iterable)
  // {
  //   Queryable<TObj, std::multiset, TLessThan> queryable(
  //     FutureStd::reinterpret_pointer_cast<InternalQueryable<TObj, std::multiset, TLessThan>>(
  //       std::make_shared<MultiSetInternalQueryable<TObj, TLessThan>>(iterable)));
  //   return queryable;
  // }
  static Queryable<TObj, std::multiset> FromMultiSet(const std::multiset<TObj> & iterable)
  {
    Queryable<TObj, std::multiset> queryable(
      FutureStd::reinterpret_pointer_cast<InternalQueryable<TObj, std::multiset>>(
        std::make_shared<MultiSetInternalQueryable<TObj>>(iterable)));
    return queryable;
  }

  template<typename TLessThan = std::less<TObj>, typename TAllocator = std::allocator<TObj>>
  static Queryable<TObj, std::set, TLessThan, TAllocator> FromSet2(const std::set<TObj, TLessThan, TAllocator> & iterable)
  {
    Queryable<TObj, std::set, TLessThan, TAllocator> queryable(
      FutureStd::reinterpret_pointer_cast<InternalQueryable<TObj, std::set, TLessThan, TAllocator>>(
        std::make_shared<SetInternalQueryable<TObj, TLessThan, TAllocator>>(iterable)));
    return queryable;
  }
  // template<typename TLessThan = std::less<TObj>>
  // static Queryable<TObj, std::set, TLessThan> FromSet(const std::set<TObj, TLessThan> & iterable)
  // {
  //   Queryable<TObj, std::set, TLessThan> queryable(
  //     FutureStd::reinterpret_pointer_cast<InternalQueryable<TObj, std::set, TLessThan>>(
  //       std::make_shared<SetInternalQueryable<TObj, TLessThan>>(iterable)));
  //   return queryable;
  // }
  static Queryable<TObj, std::set> FromSet(const std::set<TObj> & iterable)
  {
    Queryable<TObj, std::set> queryable(
      FutureStd::reinterpret_pointer_cast<InternalQueryable<TObj, std::set>>(
        std::make_shared<SetInternalQueryable<TObj>>(iterable)));
    return queryable;
  }

  template<typename TAllocator = std::allocator<TObj>>
  static Queryable<TObj, std::vector, TAllocator> FromVector2(const std::vector<TObj, TAllocator> & iterable)
  {
    Queryable<TObj, std::vector, TAllocator> queryable(
      FutureStd::reinterpret_pointer_cast<InternalQueryable<TObj, std::vector, TAllocator>>(
        std::make_shared<VectorInternalQueryable<TObj, TAllocator>>(iterable)));
    return queryable;
  }
  static Queryable<TObj, std::vector> FromVector(const std::vector<TObj> & iterable)
  {
    Queryable<TObj, std::vector> queryable(
      FutureStd::reinterpret_pointer_cast<InternalQueryable<TObj, std::vector>>(
        std::make_shared<VectorInternalQueryable<TObj>>(iterable)));
    return queryable;
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
  InternalIQueryable<TObj, TArgs...> & Except(
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

  // GroupBy
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

  inline size_t Sum(std::function<size_t(TObj)> retrieveValue = [](TObj value) { return value; }) const
  {
    return this->queryable->Sum(retrieveValue);
  }

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

  inline InternalIQueryable<TObj, TArgs...> & Where(std::function<bool(const TObj &)> condition)
  {
    this->queryable->Where(condition);
    return *this;
  }
};

#endif
