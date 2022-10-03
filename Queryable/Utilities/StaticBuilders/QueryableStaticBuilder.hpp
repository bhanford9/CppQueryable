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
  typename TStoring,
  template<typename, typename ...> typename TIterable,
  typename TIterating,
  typename ...TArgs>
class Queryable;

namespace Builders
{
  template<typename TStoring, typename TAllocator = std::allocator<TStoring>>
  static Queryable<TStoring, std::deque, TAllocator> FromInternalDeque(
    DequeInternalQueryable<TStoring, TAllocator> && other)
  {
    Queryable<TStoring, std::deque, TAllocator> queryable(
      std::move(
        FutureStd::reinterpret_pointer_cast<InternalQueryable<TStoring, std::deque, TAllocator>>(
          std::make_shared<DequeInternalQueryable<TStoring, TAllocator>>(other))));
    return queryable;
  }

  template<typename TStoring, typename TAllocator = std::allocator<TStoring>>
  static Queryable<TStoring, std::list, TAllocator> FromInternalList(
    ListInternalQueryable<TStoring, TAllocator> && other)
  {
    Queryable<TStoring, std::list, TAllocator> queryable(
      std::move(
        FutureStd::reinterpret_pointer_cast<InternalQueryable<TStoring, std::list, TAllocator>>(
          std::make_shared<ListInternalQueryable<TStoring, TAllocator>>(other))));
    return queryable;
  }

  template<typename TStoring, typename TLessThan = std::less<TStoring>, typename TAllocator = std::allocator<TStoring>>
  static Queryable<TStoring, std::multiset, TLessThan, TAllocator> FromInternalMultiSet(
    MultiSetInternalQueryable<TStoring, TLessThan, TAllocator> && other)
  {
    Queryable<TStoring, std::multiset, TLessThan, TAllocator> queryable(
      std::move(
        FutureStd::reinterpret_pointer_cast<InternalQueryable<TStoring, std::multiset, TLessThan, TAllocator>>(
          std::make_shared<MultiSetInternalQueryable<TStoring, TLessThan, TAllocator>>(other))));
  }

  template<typename TStoring, typename TLessThan = std::less<TStoring>, typename TAllocator = std::allocator<TStoring>>
  static Queryable<TStoring, std::set, TLessThan, TAllocator> FromInternalSet(
    SetInternalQueryable<TStoring, TLessThan, TAllocator> && other)
  {
    Queryable<TStoring, std::set, TLessThan, TAllocator> queryable(
      std::move(
        FutureStd::reinterpret_pointer_cast<InternalQueryable<TStoring, std::set, TLessThan, TAllocator>>(
          std::make_shared<SetInternalQueryable<TStoring, TLessThan, TAllocator>>(other))));
    return queryable;
  }

  template<typename TStoring, typename TAllocator = std::allocator<TStoring>>
  static Queryable<TStoring, std::vector, TAllocator> FromInternalVector(
    VectorInternalQueryable<TStoring, TAllocator> && other)
  {
    Queryable<TStoring, std::vector, TAllocator> queryable(
      std::move(
        FutureStd::reinterpret_pointer_cast<InternalQueryable<TStoring, std::vector, TAllocator>>(
          std::make_shared<VectorInternalQueryable<TStoring, TAllocator>>(other))));
    return queryable;
  }

  template<typename TStoring, typename TAllocator = std::allocator<TStoring>>
  static Queryable<TStoring, std::deque, TAllocator> FromInternalDeque(
    const DequeInternalQueryable<TStoring, TAllocator> & other)
  {
    Queryable<TStoring, std::deque, TAllocator> queryable(
      FutureStd::reinterpret_pointer_cast<InternalQueryable<TStoring, std::deque, TAllocator>>(
        std::make_shared<DequeInternalQueryable<TStoring, TAllocator>>(other)));
    return queryable;
  }

  template<typename TStoring, typename TAllocator = std::allocator<TStoring>>
  static Queryable<TStoring, std::list, TAllocator> FromInternalList(
    const ListInternalQueryable<TStoring, TAllocator> & other)
  {
    Queryable<TStoring, std::list, TAllocator> queryable(
      FutureStd::reinterpret_pointer_cast<InternalQueryable<TStoring, std::list, TAllocator>>(
        std::make_shared<ListInternalQueryable<TStoring, TAllocator>>(other)));
    return queryable;
  }

  template<typename TStoring, typename TLessThan = std::less<TStoring>, typename TAllocator = std::allocator<TStoring>>
  static Queryable<TStoring, std::multiset, TLessThan, TAllocator> FromInternalMultiSet(
    const MultiSetInternalQueryable<TStoring, TLessThan, TAllocator> & other)
  {
    Queryable<TStoring, std::multiset, TLessThan, TAllocator> queryable(
      FutureStd::reinterpret_pointer_cast<InternalQueryable<TStoring, std::multiset, TLessThan, TAllocator>>(
        std::make_shared<MultiSetInternalQueryable<TStoring, TLessThan, TAllocator>>(other)));
    return queryable;
  }

  template<typename TStoring, typename TLessThan = std::less<TStoring>, typename TAllocator = std::allocator<TStoring>>
  static Queryable<TStoring, std::set, TLessThan, TAllocator> FromInternalSet(
    const SetInternalQueryable<TStoring, TLessThan, TAllocator> & other)
  {
    Queryable<TStoring, std::set, TLessThan, TAllocator> queryable(
      FutureStd::reinterpret_pointer_cast<InternalQueryable<TStoring, std::set, TLessThan, TAllocator>>(
        std::make_shared<SetInternalQueryable<TStoring, TLessThan, TAllocator>>(other)));
    return queryable;
  }

  template<typename TStoring, typename TAllocator = std::allocator<TStoring>>
  static Queryable<TStoring, std::vector, TAllocator> FromInternalVector(
    const VectorInternalQueryable<TStoring, TAllocator> & other)
  {
    Queryable<TStoring, std::vector, TAllocator> queryable(
      FutureStd::reinterpret_pointer_cast<InternalQueryable<TStoring, std::vector, TAllocator>>(
        std::make_shared<VectorInternalQueryable<TStoring, TAllocator>>(other)));
    return queryable;
  }

  template<typename TStoring, typename TAllocator = std::allocator<TStoring>>
  static Queryable<TStoring, std::deque, TStoring, TAllocator> FromDeque(const std::deque<TStoring, TAllocator> & iterable)
  {
    return Queryable<TStoring, std::deque, TStoring, TAllocator>(InternalBuilders::FromDeque(iterable));
  }
  template<typename TStoring>
  static Queryable<TStoring, std::deque, TStoring> FromDeque(const std::deque<TStoring> & iterable)
  {
    return Queryable<TStoring, std::deque, TStoring>(InternalBuilders::FromDeque(iterable));
  }

  template<typename TStoring, typename TAllocator = std::allocator<TStoring>>
  static Queryable<TStoring, std::list, TStoring, TAllocator> FromList(const std::list<TStoring, TAllocator> & iterable)
  {
    return Queryable<TStoring, std::list, TStoring, TAllocator>(InternalBuilders::FromList(iterable));
  }
  template<typename TStoring>
  static Queryable<TStoring, std::list, TStoring> FromList(const std::list<TStoring> & iterable)
  {
    return Queryable<TStoring, std::list, TStoring>(InternalBuilders::FromList(iterable));
  }

  template<typename TKey, typename TValue>
  static Queryable<TKey, std::map, std::pair<const TKey, TValue>, TValue> FromMap(const std::map<TKey, TValue> & iterable)
  {
    return Queryable<TKey, std::map, std::pair<const TKey, TValue>, TValue>(InternalBuilders::FromMap(iterable));
  }

  template<
    typename TKey,
    typename TValue,
    typename TLessThan = std::less<TKey>,
    typename TAllocator = std::allocator<std::pair<const TKey, TValue>>>
  static Queryable<TKey, std::map, std::pair<const TKey, TValue>, TValue, TLessThan, TAllocator> FromMap(
    const std::map<TKey, TValue, TLessThan, TAllocator> & iterable)
  {
    return Queryable<TKey, std::map, std::pair<const TKey, TValue>, TValue, TLessThan, TAllocator>(
      InternalBuilders::FromMap(iterable));
  }

  template<typename TStoring, typename TLessThan = std::less<TStoring>, typename TAllocator = std::allocator<TStoring>>
  static Queryable<TStoring, std::multiset, TStoring, TLessThan, TAllocator> FromMultiSet(
    const std::multiset<TStoring, TLessThan, TAllocator> & iterable)
  {
    return Queryable<TStoring, std::multiset, TStoring, TLessThan, TAllocator>(InternalBuilders::FromMultiSet(iterable));
  }

  template<typename TStoring>
  static Queryable<TStoring, std::multiset, TStoring> FromMultiSet(const std::multiset<TStoring> & iterable)
  {
    return Queryable<TStoring, std::multiset, TStoring>(InternalBuilders::FromMultiSet(iterable));
  }

  template<typename TStoring, typename TLessThan = std::less<TStoring>, typename TAllocator = std::allocator<TStoring>>
  static Queryable<TStoring, std::set, TStoring, TLessThan, TAllocator> FromSet(
    const std::set<TStoring, TLessThan, TAllocator> & iterable)
  {
    return Queryable<TStoring, std::set, TStoring, TLessThan, TAllocator>(InternalBuilders::FromSet(iterable));
  }

  template<typename TStoring>
  static Queryable<TStoring, std::set, TStoring> FromSet(const std::set<TStoring> & iterable)
  {
    return Queryable<TStoring, std::set, TStoring>(InternalBuilders::FromSet(iterable));
  }

  template<typename TStoring, typename TAllocator = std::allocator<TStoring>>
  static Queryable<TStoring, std::vector, TStoring, TAllocator> FromVector(
    const std::vector<TStoring, TAllocator> & iterable)
  {
    return Queryable<TStoring, std::vector, TStoring, TAllocator>(InternalBuilders::FromVector(iterable));
  }
  template<typename TStoring>
  static Queryable<TStoring, std::vector, TStoring> FromVector(const std::vector<TStoring> & iterable)
  {
    return Queryable<TStoring, std::vector, TStoring>(InternalBuilders::FromVector(iterable));
  }
}

#endif