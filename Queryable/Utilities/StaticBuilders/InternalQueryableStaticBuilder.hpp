#ifndef CPPQUERYABLE_QUERYABLE_UTILITIES_STATICBUILDERS_INTERNALQUERYABLESTATICBUILDER_H
#define CPPQUERYABLE_QUERYABLE_UTILITIES_STATICBUILDERS_INTERNALQUERYABLESTATICBUILDER_H

#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <set>
#include <vector>

#include "../Casting.hpp"
#include "../../Queryable.hpp"

namespace InternalBuilders
{
  

  // COPYING FACTORY

  template<typename TStoring, typename TAllocator = std::allocator<TStoring>>
  static std::shared_ptr<InternalQueryable<TStoring, std::deque, TStoring, TAllocator>> FromDeque(const std::deque<TStoring, TAllocator> & deque)
  {
    return FutureStd::reinterpret_pointer_cast<InternalQueryable<TStoring, std::deque, TStoring, TAllocator>>(
      std::make_shared<DequeInternalQueryable<TStoring, TAllocator>>(deque));
  }
  template<typename TStoring>
  static std::shared_ptr<InternalQueryable<TStoring, std::deque, TStoring>> FromDeque(const std::deque<TStoring> & deque)
  {
    return FutureStd::reinterpret_pointer_cast<InternalQueryable<TStoring, std::deque, TStoring>>(
      std::make_shared<DequeInternalQueryable<TStoring>>(deque));
  }
  
  template<typename TStoring, typename TAllocator = std::allocator<TStoring>>
  static std::shared_ptr<InternalQueryable<TStoring, std::list, TStoring, TAllocator>> FromList(const std::list<TStoring, TAllocator> & list)
  {
    return FutureStd::reinterpret_pointer_cast<InternalQueryable<TStoring, std::list, TStoring, TAllocator>>(
      std::make_shared<ListInternalQueryable<TStoring, TAllocator>>(list));
  }  
  template<typename TStoring>
  static std::shared_ptr<InternalQueryable<TStoring, std::list, TStoring>> FromList(const std::list<TStoring> & list)
  {
    return FutureStd::reinterpret_pointer_cast<InternalQueryable<TStoring, std::list, TStoring>>(
      std::make_shared<ListInternalQueryable<TStoring>>(list));
  }

  template<
    typename TKey,
    typename TValue,
    typename TKeyCompare = std::less<TKey>,
    typename TAllocator = std::allocator<std::pair<const TKey, TValue>>>
  static std::shared_ptr<InternalQueryable<TKey, std::map, std::pair<const TKey, TValue>, TValue, TKeyCompare, TAllocator>> FromMap(
    const std::map<TKey, TValue, TKeyCompare, TAllocator> & map)
  {
    return FutureStd::reinterpret_pointer_cast<InternalQueryable<TKey, std::map, std::pair<const TKey, TValue>, TValue, TKeyCompare, TAllocator>>(
      std::make_shared<MapInternalQueryable<TKey, TValue, TKeyCompare, TAllocator>>(map));
  }
  template<typename TKey, typename TValue>
  static std::shared_ptr<InternalQueryable<TKey, std::map, std::pair<const TKey, TValue>, TValue>> FromMap(
    const std::map<TKey, TValue> & map)
  {
    return FutureStd::reinterpret_pointer_cast<InternalQueryable<TKey, std::map, std::pair<const TKey, TValue>, TValue>>(
      std::make_shared<MapInternalQueryable<TKey, TValue>>(map));
  }

  template<typename TStoring, typename TLessThan = std::less<TStoring>, typename TAllocator = std::allocator<TStoring>>
  static std::shared_ptr<InternalQueryable<TStoring, std::multiset, TStoring, TLessThan, TAllocator>> FromMultiSet(
    const std::multiset<TStoring, TLessThan, TAllocator> & multiset)
  {
    return FutureStd::reinterpret_pointer_cast<InternalQueryable<TStoring, std::multiset, TStoring, TLessThan, TAllocator>>(
      std::make_shared<MultiSetInternalQueryable<TStoring, TLessThan, TAllocator>>(multiset));
  }
  template<typename TStoring>
  static std::shared_ptr<InternalQueryable<TStoring, std::multiset, TStoring>> FromMultiSet(
    const std::multiset<TStoring> & multiset)
  {
    return FutureStd::reinterpret_pointer_cast<InternalQueryable<TStoring, std::multiset, TStoring>>(
      std::make_shared<MultiSetInternalQueryable<TStoring>>(multiset));
  }

  template<typename TStoring, typename TLessThan = std::less<TStoring>, typename TAllocator = std::allocator<TStoring>>
  static std::shared_ptr<InternalQueryable<TStoring, std::set, TStoring, TLessThan, TAllocator>> FromSet(
    const std::set<TStoring, TLessThan, TAllocator> & set)
  {
    return FutureStd::reinterpret_pointer_cast<InternalQueryable<TStoring, std::set, TStoring, TLessThan, TAllocator>>(
      std::make_shared<SetInternalQueryable<TStoring, TLessThan, TAllocator>>(set));
  }
  template<typename TStoring>
  static std::shared_ptr<InternalQueryable<TStoring, std::set, TStoring>> FromSet(
    const std::set<TStoring> & set)
  {
    return FutureStd::reinterpret_pointer_cast<InternalQueryable<TStoring, std::set, TStoring>>(
      std::make_shared<SetInternalQueryable<TStoring>>(set));
  }

  template<typename TStoring, typename TAllocator = std::allocator<TStoring>>
  static std::shared_ptr<InternalQueryable<TStoring, std::vector, TStoring, TAllocator>> FromVector(const std::vector<TStoring, TAllocator> & vector)
  {
    return FutureStd::reinterpret_pointer_cast<InternalQueryable<TStoring, std::vector, TStoring, TAllocator>>(
      std::make_shared<VectorInternalQueryable<TStoring, TAllocator>>(vector));
  }
  template<typename TStoring>
  static std::shared_ptr<InternalQueryable<TStoring, std::vector, TStoring>> FromVector(const std::vector<TStoring> & vector)
  {
    return FutureStd::reinterpret_pointer_cast<InternalQueryable<TStoring, std::vector, TStoring>>(
      std::make_shared<VectorInternalQueryable<TStoring>>(vector));
  }



  // MOVING FACTORY

  template<typename TStoring, typename TAllocator = std::allocator<TStoring>>
  static std::shared_ptr<InternalQueryable<TStoring, std::deque, TStoring, TAllocator>> FromDeque(std::deque<TStoring, TAllocator> && deque)
  {
    return FutureStd::reinterpret_pointer_cast<InternalQueryable<TStoring, std::deque, TStoring, TAllocator>>(
      std::make_shared<DequeInternalQueryable<TStoring, TAllocator>>(std::move(deque)));
  }
  template<typename TStoring>
  static std::shared_ptr<InternalQueryable<TStoring, std::deque, TStoring>> FromDeque(std::deque<TStoring> && deque)
  {
    return FutureStd::reinterpret_pointer_cast<InternalQueryable<TStoring, std::deque, TStoring>>(
      std::make_shared<DequeInternalQueryable<TStoring>>(std::move(deque)));
  }
  
  template<typename TStoring, typename TAllocator = std::allocator<TStoring>>
  static std::shared_ptr<InternalQueryable<TStoring, std::list, TStoring, TAllocator>> FromList(std::list<TStoring, TAllocator> && list)
  {
    return FutureStd::reinterpret_pointer_cast<InternalQueryable<TStoring, std::list, TStoring, TAllocator>>(
      std::make_shared<ListInternalQueryable<TStoring, TAllocator>>(std::move(list)));
  }  
  template<typename TStoring>
  static std::shared_ptr<InternalQueryable<TStoring, std::list, TStoring>> FromList(std::list<TStoring> && list)
  {
    return FutureStd::reinterpret_pointer_cast<InternalQueryable<TStoring, std::list, TStoring>>(
      std::make_shared<ListInternalQueryable<TStoring>>(std::move(list)));
  }

  template<
    typename TKey,
    typename TValue,
    typename TKeyCompare = std::less<TKey>,
    typename TAllocator = std::allocator<std::pair<const TKey, TValue>>>
  static std::shared_ptr<InternalQueryable<TKey, std::map, std::pair<const TKey, TValue>, TValue, TKeyCompare, TAllocator>> FromMap(
    std::map<TKey, TValue, TKeyCompare, TAllocator> && map)
  {
    return FutureStd::reinterpret_pointer_cast<InternalQueryable<TKey, std::map, std::pair<const TKey, TValue>, TValue, TKeyCompare, TAllocator>>(
      std::make_shared<MapInternalQueryable<TKey, TValue, TKeyCompare, TAllocator>>(std::move(map)));
  }
  template<typename TKey, typename TValue>
  static std::shared_ptr<InternalQueryable<TKey, std::map, std::pair<const TKey, TValue>, TValue>> FromMap(
    std::map<TKey, TValue> && map)
  {
    return FutureStd::reinterpret_pointer_cast<InternalQueryable<TKey, std::map, std::pair<const TKey, TValue>, TValue>>(
      std::make_shared<MapInternalQueryable<TKey, TValue>>(std::move(map)));
  }

  template<typename TStoring, typename TLessThan = std::less<TStoring>, typename TAllocator = std::allocator<TStoring>>
  static std::shared_ptr<InternalQueryable<TStoring, std::multiset, TStoring, TLessThan, TAllocator>> FromMultiSet(
    std::multiset<TStoring, TLessThan, TAllocator> && multiset)
  {
    return FutureStd::reinterpret_pointer_cast<InternalQueryable<TStoring, std::multiset, TStoring, TLessThan, TAllocator>>(
      std::make_shared<MultiSetInternalQueryable<TStoring, TLessThan, TAllocator>>(std::move(multiset)));
  }
  template<typename TStoring>
  static std::shared_ptr<InternalQueryable<TStoring, std::multiset, TStoring>> FromMultiSet(
    std::multiset<TStoring> && multiset)
  {
    return FutureStd::reinterpret_pointer_cast<InternalQueryable<TStoring, std::multiset, TStoring>>(
      std::make_shared<MultiSetInternalQueryable<TStoring>>(std::move(multiset)));
  }

  template<typename TStoring, typename TLessThan = std::less<TStoring>, typename TAllocator = std::allocator<TStoring>>
  static std::shared_ptr<InternalQueryable<TStoring, std::set, TStoring, TLessThan, TAllocator>> FromSet(
    std::set<TStoring, TLessThan, TAllocator> && set)
  {
    return FutureStd::reinterpret_pointer_cast<InternalQueryable<TStoring, std::set, TStoring, TLessThan, TAllocator>>(
      std::make_shared<SetInternalQueryable<TStoring, TLessThan, TAllocator>>(std::move(set)));
  }
  template<typename TStoring>
  static std::shared_ptr<InternalQueryable<TStoring, std::set, TStoring>> FromSet(
    std::set<TStoring> && set)
  {
    return FutureStd::reinterpret_pointer_cast<InternalQueryable<TStoring, std::set, TStoring>>(
      std::make_shared<SetInternalQueryable<TStoring>>(std::move(set)));
  }

  template<typename TStoring, typename TAllocator = std::allocator<TStoring>>
  static std::shared_ptr<InternalQueryable<TStoring, std::vector, TStoring, TAllocator>> FromVector(std::vector<TStoring, TAllocator> && vector)
  {
    return FutureStd::reinterpret_pointer_cast<InternalQueryable<TStoring, std::vector, TStoring, TAllocator>>(
      std::make_shared<VectorInternalQueryable<TStoring, TAllocator>>(std::move(vector)));
  }
  template<typename TStoring>
  static std::shared_ptr<InternalQueryable<TStoring, std::vector, TStoring>> FromVector(std::vector<TStoring> && vector)
  {
    return FutureStd::reinterpret_pointer_cast<InternalQueryable<TStoring, std::vector, TStoring>>(
      std::make_shared<VectorInternalQueryable<TStoring>>(std::move(vector)));
  }
}

#endif