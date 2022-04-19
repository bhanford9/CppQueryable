#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLE_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLE_H

#include <iostream>
#include <memory>
#include <type_traits>
#include <utility>

#include "InternalQueryable.hpp"

#include "SelectBuilders/SelectBuilder.hpp"
#include "SelectBuilders/DequeSelectBuilder.hpp"
#include "SelectBuilders/ListSelectBuilder.hpp"
#include "SelectBuilders/MultiSetSelectBuilder.hpp"
#include "SelectBuilders/SetSelectBuilder.hpp"
#include "SelectBuilders/VectorSelectBuilder.hpp"
#include "Sorters/Sorter.hpp"
#include "Sorters/DequeSorter.hpp"
#include "Sorters/ListSorter.hpp"
#include "Sorters/MultiSetSorter.hpp"
#include "Sorters/SetSorter.hpp"
#include "Sorters/VectorSorter.hpp"
#include "Utilities/Casting.hpp"

template<
  typename TObj,
  template<typename, typename ...> typename TIterable,
  typename ...TArgs>
class Queryable
{
protected:
  std::shared_ptr<InternalQueryable<TObj, TIterable, TArgs...>> queryable;
  Queryable() {}

public:

  virtual ~Queryable() { }

  Queryable(Queryable<TObj, TIterable, TArgs...> && other)
    : queryable(std::move(other.queryable))
  {
  }
  Queryable(const Queryable<TObj, TIterable, TArgs...> & other)
    : queryable(other.queryable)
  {
  }
  Queryable(std::shared_ptr<InternalQueryable<TObj, TIterable, TArgs...>> && other)
    : queryable(std::move(other))
  {
  }
  Queryable(InternalQueryable<TObj, TIterable, TArgs...> * other)
  {
    queryable.reset(other);
  }
  Queryable(const TIterable<TObj, TArgs...> & items);
  Queryable(TIterable<TObj, TArgs...> && items);

  // All these reinterpret_casts should not be necessary. Need to figure out why the inheritance
  // is not implemented properly
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
  static Queryable<TObj, std::deque, TAllocator> FromDeque(const std::deque<TObj, TAllocator> & iterable)
  {
    Queryable<TObj, std::deque, TAllocator> queryable(
      FutureStd::reinterpret_pointer_cast<InternalQueryable<TObj, std::deque, TAllocator>>(
        std::make_shared<DequeInternalQueryable<TObj, TAllocator>>(iterable)));
    return queryable;
  }

  template<typename TAllocator = std::allocator<TObj>>
  static Queryable<TObj, std::list, TAllocator> FromList(const std::list<TObj, TAllocator> & iterable)
  {
    Queryable<TObj, std::list, TAllocator> queryable(
      FutureStd::reinterpret_pointer_cast<InternalQueryable<TObj, std::list, TAllocator>>(
        std::make_shared<ListInternalQueryable<TObj, TAllocator>>(iterable)));
    return queryable;
  }

  template<typename TLessThan = std::less<TObj>, typename TAllocator = std::allocator<TObj>>
  static Queryable<TObj, std::multiset, TLessThan, TAllocator> FromMultiSet(const std::multiset<TObj, TLessThan, TAllocator> & iterable)
  {
    Queryable<TObj, std::multiset, TLessThan, TAllocator> queryable(
      FutureStd::reinterpret_pointer_cast<InternalQueryable<TObj, std::multiset, TLessThan, TAllocator>>(
        std::make_shared<MultiSetInternalQueryable<TObj, TLessThan, TAllocator>>(iterable)));
    return queryable;
  }

  template<typename TLessThan = std::less<TObj>, typename TAllocator = std::allocator<TObj>>
  static Queryable<TObj, std::set, TLessThan, TAllocator> FromSet(const std::set<TObj, TLessThan, TAllocator> & iterable)
  {
    Queryable<TObj, std::set, TLessThan, TAllocator> queryable(
      FutureStd::reinterpret_pointer_cast<InternalQueryable<TObj, std::set, TLessThan, TAllocator>>(
        std::make_shared<SetInternalQueryable<TObj, TLessThan, TAllocator>>(iterable)));
    return queryable;
  }

  template<typename TAllocator = std::allocator<TObj>>
  static Queryable<TObj, std::vector, TAllocator> FromVector(const std::vector<TObj, TAllocator> & iterable)
  {
    Queryable<TObj, std::vector, TAllocator> queryable(
      FutureStd::reinterpret_pointer_cast<InternalQueryable<TObj, std::vector, TAllocator>>(
        std::make_shared<VectorInternalQueryable<TObj, TAllocator>>(iterable)));
    return queryable;
  }

  template<typename TAllocator = std::allocator<TObj>>
  inline std::deque<TObj, TAllocator> ToDeque(TAllocator allocator = {}) const
  {
    return this->queryable->ToDeque(allocator);
  }

  template<typename TAllocator = std::allocator<TObj>>
  inline std::list<TObj, TAllocator> ToList(TAllocator allocator = {}) const
  {
    return this->queryable->ToList(allocator);
  }

  template<typename TLessThan = std::less<TObj>, typename TAllocator = std::allocator<TObj>>
  inline std::multiset<TObj, TLessThan, TAllocator> ToMultiSet(TLessThan lessThan = {}, TAllocator allocator = {}) const
  {
    return this->queryable->ToMultiSet(lessThan, allocator);
  }

  template<typename TLessThan = std::less<TObj>, typename TAllocator = std::allocator<TObj>>
  inline std::set<TObj, TLessThan, TAllocator> ToSet(TLessThan lessThan = {}, TAllocator allocator = {}) const
  {
    return this->queryable->ToSet(lessThan, allocator);
  }

  template<typename TAllocator = std::allocator<TObj>>
  inline std::vector<TObj, TAllocator> ToVector(TAllocator allocator = {}) const
  {
    return this->queryable->ToVector(allocator);
  }

  inline bool Any(std::function<bool(TObj)> condition) const
  {
    return this->queryable->Any(condition);
  }

  inline bool All(std::function<bool(TObj)> condition) const
  {
    return this->queryable->All(condition);
  }

  inline TObj & At(int index)
  {
    return this->queryable->At(index);
  }

  template<typename T>
  inline double Average(std::function<T(TObj)> retrieveValue) const
  {
    return this->queryable->Average(retrieveValue);
  }

  inline TObj Average(std::function<TObj(const TObj &, size_t)> divisor) const
  {
    return this->queryable->Average(divisor);
  }

  inline double Average() const
  {
    return this->queryable->Average();
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

  inline bool Equal(const TIterable<TObj, TArgs...> & collection) const
  {
    return this->queryable->Equal(collection);
  }

  inline bool Equal(
    const TIterable<TObj, TArgs...> & collection,
    const std::function<bool(TObj, TObj)> & areEqual) const
  {
    return this->queryable->Equal(collection, areEqual);
  }

  inline bool Equal(const TIterable<TObj, TArgs...> & collection, size_t collectionSize) const
  {
    return this->queryable->Equal(collection, collectionSize);
  }

  inline bool Equal(
    const TIterable<TObj, TArgs...> & collection,
    size_t collectionSize,
    const std::function<bool(TObj, TObj)> & areEqual) const
  {
    return this->queryable->Equal(collection, collectionSize, areEqual);
  }

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

  TObj First(std::function<bool(TObj)> condition)
  {
    return this->queryable->First(condition);
  }

  TObj First()
  {
    return this->queryable->First();
  }

  inline void ForEach(std::function<void(TObj)> action)
  {
    this->queryable->ForEach(action);
  }

  inline QueryableType GetType()
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
        // move constructor so no new memory is created
        Queryable<T, TIterable, TNewArgs...> newQueryable(std::move(newInternalQueryable));

        // TODO --> determine if reseting is undesireable
        this->queryable.reset();

        // return uses move constructor so no new memory is created
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
        // move constructor so no new memory is created
        Queryable<T, TIterable, TNewArgs...> newQueryable(std::move(newInternalQueryable));

        // TODO --> determine if reseting is undesireable
        this->queryable.reset();

        // return uses move constructor so no new memory is created
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
        // move constructor so no new memory is created
        Queryable<T, TIterable, TNewArgs...> newQueryable(std::move(newInternalQueryable));

        // TODO --> determine if reseting is undesireable
        this->queryable.reset();

        // return uses move constructor so no new memory is created
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
        // move constructor so no new memory is created
        Queryable<T, TIterable, TNewArgs...> newQueryable(std::move(newInternalQueryable));

        // TODO --> determine if reseting is undesireable
        this->queryable.reset();

        // return uses move constructor so no new memory is created
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
        // move constructor so no new memory is created
        Queryable<T, TIterable, TNewArgs...> newQueryable(std::move(newInternalQueryable));

        // TODO --> determine if reseting is undesireable
        this->queryable.reset();

        // return uses move constructor so no new memory is created
        return newQueryable;
        break;
      }
      default:
        break;
    }

    return {};
  }

  inline Queryable<TObj, TIterable, TArgs...> & Where(std::function<bool(const TObj &)> condition)
  {
    this->queryable->Where(condition);
    return *this;
  }


  template<
    typename TLessThan = std::less<TObj>,
    typename ...TNewArgs>
  Queryable<TObj, TIterable, TNewArgs...> Sort(TLessThan lessThan = {}, TNewArgs... args)
  {
    switch (this->queryable->GetType())
    {
      case QueryableType::Deque:
      {
        // this is only safe if TNewArgs is the same as TArgs (which should probably be enforced anyway)
        std::shared_ptr<InternalQueryable<TObj, TIterable, TNewArgs...>> newInternalQueryable(
          FutureStd::reinterpret_pointer_cast<InternalQueryable<TObj, TIterable, TNewArgs...>>(this->queryable));

        DequeSorter<TObj, TLessThan, TNewArgs...> sorter;
        newInternalQueryable->Sort(reinterpret_cast<Sorter<TObj, void, TLessThan>*>(&sorter), lessThan);

        Queryable<TObj, TIterable, TNewArgs...> newQueryable(std::move(newInternalQueryable));
        return newQueryable;
        break;
      }
      // case QueryableType::List:
      // {
      //   ListSorter<TObj, TArgs...> sorter;
      //   Queryable<TObj, TIterable, TNewArgs...> newQueryable(this->queryable->OrderBy(sorter, retrieveValue, lessThan));
      //   return newQueryable;
      //   break;
      // }
      // case QueryableType::MultiSet:
      // {
      //   MultiSetSorter<TObj, TArgs...> sorter;
      //   Queryable<TObj, TIterable, TNewArgs...> newQueryable(this->queryable->OrderBy(sorter, retrieveValue, lessThan));
      //   return newQueryable;
      //   break;
      // }
      // case QueryableType::Set:
      // {
      //   SetSorter<TObj, TArgs...> sorter;
      //   Queryable<TObj, TIterable, TNewArgs...> newQueryable(this->queryable->OrderBy(sorter, retrieveValue, lessThan));
      //   return newQueryable;
      //   break;
      // }
        case QueryableType::Vector:
        {
          // this is only safe if TNewArgs is the same as TArgs (which should probably be enforced anyway)
          std::shared_ptr<InternalQueryable<TObj, TIterable, TNewArgs...>> newInternalQueryable(
            FutureStd::reinterpret_pointer_cast<InternalQueryable<TObj, TIterable, TNewArgs...>>(this->queryable));

          VectorSorter<TObj, TLessThan, TNewArgs...> sorter;
          newInternalQueryable->Sort(reinterpret_cast<Sorter<TObj, void, TLessThan>*>(&sorter), lessThan);

          Queryable<TObj, TIterable, TNewArgs...> newQueryable(std::move(newInternalQueryable));
          return newQueryable;
          break;
        }
      default: throw std::runtime_error("should not reach here");
    }
  }

  template<
    typename T = TObj,
    typename TLessThan = std::less<T>>
  Queryable<TObj, TIterable, TArgs...> OrderBy(
    std::function<T(TObj)> retrieveValue = [](TObj o) { return o; },
    TLessThan lessThan = {})
  {
    // TODO --> this is terribly ugly, find a better way to handle it
    switch (this->queryable->GetType())
    {
      case QueryableType::Deque:
      {
        DequeSorter<TObj, TArgs...> sorter;
        Queryable<TObj, TIterable, TArgs...> newQueryable(this->queryable->OrderBy(sorter, retrieveValue, lessThan));
        return newQueryable;
        break;
      }
      case QueryableType::List:
      {
        ListSorter<TObj, TArgs...> sorter;
        Queryable<TObj, TIterable, TArgs...> newQueryable(this->queryable->OrderBy(sorter, retrieveValue, lessThan));
        return newQueryable;
        break;
      }
      case QueryableType::MultiSet:
      {
        MultiSetSorter<TObj, TArgs...> sorter;
        Queryable<TObj, TIterable, TArgs...> newQueryable(this->queryable->OrderBy(sorter, retrieveValue, lessThan));
        return newQueryable;
        break;
      }
      case QueryableType::Set:
      {
        SetSorter<TObj, TArgs...> sorter;
        Queryable<TObj, TIterable, TArgs...> newQueryable(this->queryable->OrderBy(sorter, retrieveValue, lessThan));
        return newQueryable;
        break;
      }
      case QueryableType::Vector:
      {
        VectorSorter<TObj, TArgs...> sorter;
        Queryable<TObj, TIterable, TArgs...> newQueryable(this->queryable->OrderBy(sorter, retrieveValue, lessThan));
        return newQueryable;
        break;
      }
      default: break;
    }
  }

  template<
    typename T = TObj,
    typename TLessThan = std::less<T>>
  Queryable<TObj, TIterable, TArgs...> & OrderByDescending(
    std::function<T(TObj)> retrieveValue = [](TObj o) { return o; },
    TLessThan lessThan = {})
  {
    // TODO
    return *this;//this->OrderByDescending<T, TLessThan, TArgs...>(retrieveValue, lessThan);
  }

  template<
    typename TOutLessThan = std::less<TObj>,
    typename T = TObj,
    typename TLessThan = std::less<T>,
    typename TOutAllocator = std::allocator<TObj>>
  Queryable<TObj, TIterable, TLessThan, TOutAllocator> OrderByDescending(
    TOutLessThan outLessThan,
    std::function<T(TObj)> retrieveValue = [](TObj o) { return o; },
    TLessThan lessThan = {},
    TOutAllocator outAllocator = {})
  {
    // need to take the is_invocable_r implementation from gcc++14
    // static_assert(std::is_invocable_r<bool, TOutLessThan, TObj, TObj>::value, "TOutLessThan must be an invocable type that takes two parameters of type TObj and returns a bool.");
    // static_assert(std::is_invocable_r<TObj, TOutAllocator>::value, "TOutAllocator must be an invocable type that takes no parameters and returns a TObj.");


  // }
  //
  // template<
  //   typename T = TObj,
  //   typename TLessThan = std::less<T>,
  //   typename ...TNewArgs>
  // Queryable<TObj, TIterable, TNewArgs...> OrderByDescending(
  //   std::function<T(TObj)> retrieveValue = [](TObj o) { return o; },
  //   TLessThan lessThan = {},
  //   TNewArgs... newArgs)
  // {
    // TODO --> this is terribly ugly, find a better way to handle it
    switch (this->queryable->GetType())
    {
      // case QueryableType::Deque:
      // {
      //   DequeSorter<TObj, TArgs...> sorter;
      //   Queryable<TObj, TIterable, TArgs...> newQueryable(this->queryable->OrderByDescending(
      //     *reinterpret_cast<Sorter<TObj, TIterable, SortOutput<TObj, TIterable, TArgs...>, TArgs...>*>(&sorter),
      //     retrieveValue,
      //     lessThan));
      //   return newQueryable;
      //   break;
      // }
      // case QueryableType::List:
      // {
      //   ListSorter<TObj, TArgs...> sorter;
      //   Queryable<TObj, TIterable, TArgs...> newQueryable(this->queryable->OrderByDescending(
      //     *reinterpret_cast<Sorter<TObj, TIterable, SortOutput<TObj, TIterable, TArgs...>, TArgs...>*>(&sorter),
      //     retrieveValue,
      //     lessThan));
      //   return newQueryable;
      //   break;
      // }
      case QueryableType::MultiSet:
      {
        MultiSetSorter<TObj, TOutLessThan, TArgs...> sorter;
        std::cout << "outer orderby descending" << std::endl;




        // TODO --> pass the resulting shared_ptr<InternalQueryable<TNewArgs...>> into the internal order by and get it back. Then you can create a new instance of self and return



        // std::shared_ptr<InternalQueryable<TObj, TIterable, TNewArgs...>> result(
        //   // FutureStd::reinterpret_pointer_cast<InternalQueryable<T, TIterable, TNewArgs...>>(
        //   //   std::make_shared<MultiSetInternalQueryable<TObj, TNewArgs...>>(
        //       this->queryable->OrderByDescending(
        //         *reinterpret_cast<Sorter<TObj, std::multiset, SortOutput<TObj, std::multiset, std::function<bool(TObj, TObj)>>, TArgs...>*>(&sorter),
        //         retrieveValue,
        //         lessThan)
        //       .Get());//));

        // this type always has to be std::function<bool(TObj, TObj)> for output of multi/sets there is no way around it
        // I think I need to NIX the Orderbys and just do Sorting

        // SortOutput<TObj, std::multiset, TOutLessThan, TOutAllocator> sortOutput = this->queryable->OrderByDescending(
        //   *reinterpret_cast<Sorter<TObj, std::multiset, SortOutput<TObj, std::multiset, TOutLessThan, TOutAllocator>, TArgs...>*>(&sorter),
        //   retrieveValue,
        //   lessThan);
        // std::multiset<TObj, TOutLessThan, TOutAllocator> resorted = sortOutput.Get();

        Queryable<TObj, std::multiset, TOutLessThan, TOutAllocator> queryableResult;

        std::cout << "returning self as sorted multiset" << std::endl;
        return queryableResult;
        break;
      }
      // case QueryableType::Set:
      // {
      //   SetSorter<TObj, TArgs...> sorter;
      //   Queryable<TObj, TIterable, TArgs...> newQueryable(this->queryable->OrderByDescending(
      //     *reinterpret_cast<Sorter<TObj, TIterable, SortOutput<TObj, TIterable, TArgs...>, TArgs...>*>(&sorter),
      //     retrieveValue,
      //     lessThan));
      //   return newQueryable;
      //   break;
      // }
      // case QueryableType::Vector:
      // {
      //   VectorSorter<TObj, TArgs...> sorter;
      //   Queryable<TObj, TIterable, TArgs...> newQueryable(this->queryable->OrderByDescending(
      //     *reinterpret_cast<Sorter<TObj, TIterable, SortOutput<TObj, TIterable, TArgs...>, TArgs...>*>(&sorter),
      //     retrieveValue,
      //     lessThan));
      //   return newQueryable;
      //   break;
      // }
      default: break;
    }

    throw std::runtime_error("should not reach here");
  }
};

#endif
