#ifndef CPPQUERYABLE_QUERYABLE_UTILITIES_STATICBUILDERS_QUERYABLESTATICBUILDER_H
#define CPPQUERYABLE_QUERYABLE_UTILITIES_STATICBUILDERS_QUERYABLESTATICBUILDER_H

#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <vector>

#include "InternalQueryableStaticBuilder.hpp"
#include "../Casting.hpp"
#include "../../Queryable.hpp"

template<
  typename TObj,
  template<typename, typename ...> typename TIterable,
  typename ...TArgs>
class Queryable;

namespace Builders
{
  template<typename T, typename TAllocator = std::allocator<T>>
  static Queryable<T, std::deque, TAllocator> FromInternalDeque(DequeInternalQueryable<T, TAllocator> && other)
  {
    Queryable<T, std::deque, TAllocator> queryable(
      std::move(
        FutureStd::reinterpret_pointer_cast<InternalQueryable<T, std::deque, TAllocator>>(
          std::make_shared<DequeInternalQueryable<T, TAllocator>>(other))));
    return queryable;
  }

  template<typename T, typename TAllocator = std::allocator<T>>
  static Queryable<T, std::list, TAllocator> FromInternalList(ListInternalQueryable<T, TAllocator> && other)
  {
    Queryable<T, std::list, TAllocator> queryable(
      std::move(
        FutureStd::reinterpret_pointer_cast<InternalQueryable<T, std::list, TAllocator>>(
          std::make_shared<ListInternalQueryable<T, TAllocator>>(other))));
    return queryable;
  }

  template<typename T, typename TLessThan = std::less<T>, typename TAllocator = std::allocator<T>>
  static Queryable<T, std::multiset, TLessThan, TAllocator> FromInternalMultiSet(MultiSetInternalQueryable<T, TLessThan, TAllocator> && other)
  {
    Queryable<T, std::multiset, TLessThan, TAllocator> queryable(
      std::move(
        FutureStd::reinterpret_pointer_cast<InternalQueryable<T, std::multiset, TLessThan, TAllocator>>(
          std::make_shared<MultiSetInternalQueryable<T, TLessThan, TAllocator>>(other))));
  }

  template<typename T, typename TLessThan = std::less<T>, typename TAllocator = std::allocator<T>>
  static Queryable<T, std::set, TLessThan, TAllocator> FromInternalSet(SetInternalQueryable<T, TLessThan, TAllocator> && other)
  {
    Queryable<T, std::set, TLessThan, TAllocator> queryable(
      std::move(
        FutureStd::reinterpret_pointer_cast<InternalQueryable<T, std::set, TLessThan, TAllocator>>(
          std::make_shared<SetInternalQueryable<T, TLessThan, TAllocator>>(other))));
    return queryable;
  }

  template<typename T, typename TAllocator = std::allocator<T>>
  static Queryable<T, std::vector, TAllocator> FromInternalVector(VectorInternalQueryable<T, TAllocator> && other)
  {
    Queryable<T, std::vector, TAllocator> queryable(
      std::move(
        FutureStd::reinterpret_pointer_cast<InternalQueryable<T, std::vector, TAllocator>>(
          std::make_shared<VectorInternalQueryable<T, TAllocator>>(other))));
    return queryable;
  }

  template<typename T, typename TAllocator = std::allocator<T>>
  static Queryable<T, std::deque, TAllocator> FromInternalDeque(const DequeInternalQueryable<T, TAllocator> & other)
  {
    Queryable<T, std::deque, TAllocator> queryable(
      FutureStd::reinterpret_pointer_cast<InternalQueryable<T, std::deque, TAllocator>>(
        std::make_shared<DequeInternalQueryable<T, TAllocator>>(other)));
    return queryable;
  }

  template<typename T, typename TAllocator = std::allocator<T>>
  static Queryable<T, std::list, TAllocator> FromInternalList(const ListInternalQueryable<T, TAllocator> & other)
  {
    Queryable<T, std::list, TAllocator> queryable(
      FutureStd::reinterpret_pointer_cast<InternalQueryable<T, std::list, TAllocator>>(
        std::make_shared<ListInternalQueryable<T, TAllocator>>(other)));
    return queryable;
  }

  template<typename T, typename TLessThan = std::less<T>, typename TAllocator = std::allocator<T>>
  static Queryable<T, std::multiset, TLessThan, TAllocator> FromInternalMultiSet(const MultiSetInternalQueryable<T, TLessThan, TAllocator> & other)
  {
    Queryable<T, std::multiset, TLessThan, TAllocator> queryable(
      FutureStd::reinterpret_pointer_cast<InternalQueryable<T, std::multiset, TLessThan, TAllocator>>(
        std::make_shared<MultiSetInternalQueryable<T, TLessThan, TAllocator>>(other)));
    return queryable;
  }

  template<typename T, typename TLessThan = std::less<T>, typename TAllocator = std::allocator<T>>
  static Queryable<T, std::set, TLessThan, TAllocator> FromInternalSet(const SetInternalQueryable<T, TLessThan, TAllocator> & other)
  {
    Queryable<T, std::set, TLessThan, TAllocator> queryable(
      FutureStd::reinterpret_pointer_cast<InternalQueryable<T, std::set, TLessThan, TAllocator>>(
        std::make_shared<SetInternalQueryable<T, TLessThan, TAllocator>>(other)));
    return queryable;
  }

  template<typename T, typename TAllocator = std::allocator<T>>
  static Queryable<T, std::vector, TAllocator> FromInternalVector(const VectorInternalQueryable<T, TAllocator> & other)
  {
    Queryable<T, std::vector, TAllocator> queryable(
      FutureStd::reinterpret_pointer_cast<InternalQueryable<T, std::vector, TAllocator>>(
        std::make_shared<VectorInternalQueryable<T, TAllocator>>(other)));
    return queryable;
  }

  template<typename T, typename TAllocator = std::allocator<T>>
  static Queryable<T, std::deque, TAllocator> FromDeque(const std::deque<T, TAllocator> & iterable)
  {
    return Queryable<T, std::deque, TAllocator>(InternalBuilders::FromDeque(iterable));
  }
  template<typename T>
  static Queryable<T, std::deque> FromDeque(const std::deque<T> & iterable)
  {
    return Queryable<T, std::deque>(InternalBuilders::FromDeque(iterable));
  }

  template<typename T, typename TAllocator = std::allocator<T>>
  static Queryable<T, std::list, TAllocator> FromList(const std::list<T, TAllocator> & iterable)
  {
    return Queryable<T, std::list, TAllocator>(InternalBuilders::FromList(iterable));
  }
  template<typename T>
  static Queryable<T, std::list> FromList(const std::list<T> & iterable)
  {
    return Queryable<T, std::list>(InternalBuilders::FromList(iterable));
  }

  template<typename TKey, typename TValue>
  static Queryable<std::pair<TKey, TValue>, std::map> FromMap(const std::map<TKey, TValue> & iterable)
  {
    return Queryable<std::pair<TKey, TValue>, std::map>(InternalBuilders::FromMap(iterable));
  }

  template<
    typename TKey,
    typename TValue,
    typename TLessThan = std::less<TKey>,
    typename TAllocator = std::allocator<std::pair<const TKey, TValue>>>
  static Queryable<std::pair<TKey, TValue>, std::map, TLessThan, TAllocator> FromMap(const std::map<TKey, TValue, TLessThan, TAllocator> & iterable)
  {
    return Queryable<std::pair<TKey, TValue>, std::map, TLessThan, TAllocator>(InternalBuilders::FromMap(iterable));
  }

  template<typename T, typename TLessThan = std::less<T>, typename TAllocator = std::allocator<T>>
  static Queryable<T, std::multiset, TLessThan, TAllocator> FromMultiSet(const std::multiset<T, TLessThan, TAllocator> & iterable)
  {
    return Queryable<T, std::multiset, TLessThan, TAllocator>(InternalBuilders::FromMultiSet(iterable));
  }

  template<typename T>
  static Queryable<T, std::multiset> FromMultiSet(const std::multiset<T> & iterable)
  {
    return Queryable<T, std::multiset>(InternalBuilders::FromMultiSet(iterable));
  }

  template<typename T, typename TLessThan = std::less<T>, typename TAllocator = std::allocator<T>>
  static Queryable<T, std::set, TLessThan, TAllocator> FromSet(const std::set<T, TLessThan, TAllocator> & iterable)
  {
    return Queryable<T, std::set, TLessThan, TAllocator>(InternalBuilders::FromSet(iterable));
  }

  template<typename T>
  static Queryable<T, std::set> FromSet(const std::set<T> & iterable)
  {
    return Queryable<T, std::set>(InternalBuilders::FromSet(iterable));
  }

  template<typename T, typename TAllocator = std::allocator<T>>
  static Queryable<T, std::vector, TAllocator> FromVector(const std::vector<T, TAllocator> & iterable)
  {
    return Queryable<T, std::vector, TAllocator>(InternalBuilders::FromVector(iterable));
  }
  template<typename T>
  static Queryable<T, std::vector> FromVector(const std::vector<T> & iterable)
  {
    return Queryable<T, std::vector>(InternalBuilders::FromVector(iterable));
  }
}

#endif