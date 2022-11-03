#ifndef CPPQUERYABLE_QUERYABLE_UTILITIES_STATICBUILDERS_INTERNALQUERYABLESTATICBUILDER_H
#define CPPQUERYABLE_QUERYABLE_UTILITIES_STATICBUILDERS_INTERNALQUERYABLESTATICBUILDER_H

#include <deque>
#include <list>
#include <map>
#include <memory>
#include <set>
#include <vector>

#include "../Casting.hpp"

namespace InternalBuilders
{  

  // COPYING FACTORY

  template<typename TStoring, typename TAllocator = std::allocator<TStoring>>
  static std::shared_ptr<InternalQueryable<TStoring, std::deque, TStoring, TAllocator>> FromDeque(const std::deque<TStoring, TAllocator> & deque)
  {
    return FutureStd::reinterpret_pointer_cast<InternalQueryable<TStoring, std::deque, TStoring, TAllocator>>(
      std::make_shared<DequeInternalQueryable<TStoring, TAllocator>>(deque));
  }
  
  template<typename TStoring, typename TAllocator = std::allocator<TStoring>>
  static std::shared_ptr<InternalQueryable<TStoring, std::list, TStoring, TAllocator>> FromList(const std::list<TStoring, TAllocator> & list)
  {
    return FutureStd::reinterpret_pointer_cast<InternalQueryable<TStoring, std::list, TStoring, TAllocator>>(
      std::make_shared<ListInternalQueryable<TStoring, TAllocator>>(list));
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

  template<typename TStoring, typename TLessThan = std::less<TStoring>, typename TAllocator = std::allocator<TStoring>>
  static std::shared_ptr<InternalQueryable<TStoring, std::multiset, TStoring, TLessThan, TAllocator>> FromMultiSet(
    const std::multiset<TStoring, TLessThan, TAllocator> & multiset)
  {
    return FutureStd::reinterpret_pointer_cast<InternalQueryable<TStoring, std::multiset, TStoring, TLessThan, TAllocator>>(
      std::make_shared<MultiSetInternalQueryable<TStoring, TLessThan, TAllocator>>(multiset));
  }

  template<typename TStoring, typename TLessThan = std::less<TStoring>, typename TAllocator = std::allocator<TStoring>>
  static std::shared_ptr<InternalQueryable<TStoring, std::set, TStoring, TLessThan, TAllocator>> FromSet(
    const std::set<TStoring, TLessThan, TAllocator> & set)
  {
    return FutureStd::reinterpret_pointer_cast<InternalQueryable<TStoring, std::set, TStoring, TLessThan, TAllocator>>(
      std::make_shared<SetInternalQueryable<TStoring, TLessThan, TAllocator>>(set));
  }

  template<typename TStoring, typename TAllocator = std::allocator<TStoring>>
  static std::shared_ptr<InternalQueryable<TStoring, std::vector, TStoring, TAllocator>> FromVector(const std::vector<TStoring, TAllocator> & vector)
  {
    return FutureStd::reinterpret_pointer_cast<InternalQueryable<TStoring, std::vector, TStoring, TAllocator>>(
      std::move(std::make_shared<VectorInternalQueryable<TStoring, TAllocator>>(
        std::move(FutureStd::reinterpret_pointer_cast<QueryableData<TStoring, std::vector, TStoring, TAllocator>>(
          std::make_shared<QueryableVectorData<TStoring, TAllocator>>(vector))), QueryableType::Vector)));
  }


  // MOVING FACTORY

  template<typename TStoring, typename TAllocator = std::allocator<TStoring>>
  static std::shared_ptr<InternalQueryable<TStoring, std::deque, TStoring, TAllocator>> FromDeque(std::deque<TStoring, TAllocator> && deque)
  {
    return FutureStd::reinterpret_pointer_cast<InternalQueryable<TStoring, std::deque, TStoring, TAllocator>>(
      std::make_shared<DequeInternalQueryable<TStoring, TAllocator>>(std::move(deque)));
  }
  
  template<typename TStoring, typename TAllocator = std::allocator<TStoring>>
  static std::shared_ptr<InternalQueryable<TStoring, std::list, TStoring, TAllocator>> FromList(std::list<TStoring, TAllocator> && list)
  {
    return FutureStd::reinterpret_pointer_cast<InternalQueryable<TStoring, std::list, TStoring, TAllocator>>(
      std::make_shared<ListInternalQueryable<TStoring, TAllocator>>(std::move(list)));
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

  template<typename TStoring, typename TLessThan = std::less<TStoring>, typename TAllocator = std::allocator<TStoring>>
  static std::shared_ptr<InternalQueryable<TStoring, std::multiset, TStoring, TLessThan, TAllocator>> FromMultiSet(
    std::multiset<TStoring, TLessThan, TAllocator> && multiset)
  {
    return FutureStd::reinterpret_pointer_cast<InternalQueryable<TStoring, std::multiset, TStoring, TLessThan, TAllocator>>(
      std::make_shared<MultiSetInternalQueryable<TStoring, TLessThan, TAllocator>>(std::move(multiset)));
  }

  template<typename TStoring, typename TLessThan = std::less<TStoring>, typename TAllocator = std::allocator<TStoring>>
  static std::shared_ptr<InternalQueryable<TStoring, std::set, TStoring, TLessThan, TAllocator>> FromSet(
    std::set<TStoring, TLessThan, TAllocator> && set)
  {
    return FutureStd::reinterpret_pointer_cast<InternalQueryable<TStoring, std::set, TStoring, TLessThan, TAllocator>>(
      std::make_shared<SetInternalQueryable<TStoring, TLessThan, TAllocator>>(std::move(set)));
  }

  template<typename TStoring, typename TAllocator = std::allocator<TStoring>>
  static std::shared_ptr<InternalQueryable<TStoring, std::vector, TStoring, TAllocator>> FromVector(std::vector<TStoring, TAllocator> && vector)
  {
    return FutureStd::reinterpret_pointer_cast<InternalQueryable<TStoring, std::vector, TStoring, TAllocator>>(
      std::move(std::make_shared<VectorInternalQueryable<TStoring, TAllocator>>(
        std::move(FutureStd::reinterpret_pointer_cast<QueryableData<TStoring, std::vector, TStoring, TAllocator>>(
          std::make_shared<QueryableVectorData<TStoring, TAllocator>>(
            std::move(vector)))), QueryableType::Vector)));
  }
}

#endif