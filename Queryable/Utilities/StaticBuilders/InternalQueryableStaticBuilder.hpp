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

  template<typename T, typename TAllocator = std::allocator<T>>
  static std::shared_ptr<InternalQueryable<T, std::deque, TAllocator>> FromDeque(const std::deque<T, TAllocator> & deque)
  {
    return FutureStd::reinterpret_pointer_cast<InternalQueryable<T, std::deque, TAllocator>>(
      std::make_shared<DequeInternalQueryable<T, TAllocator>>(deque));
  }
  template<typename T>
  static std::shared_ptr<InternalQueryable<T, std::deque>> FromDeque(const std::deque<T> & deque)
  {
    return FutureStd::reinterpret_pointer_cast<InternalQueryable<T, std::deque>>(
      std::make_shared<DequeInternalQueryable<T>>(deque));
  }
  
  template<typename T, typename TAllocator = std::allocator<T>>
  static std::shared_ptr<InternalQueryable<T, std::list, TAllocator>> FromList(const std::list<T, TAllocator> & list)
  {
    return FutureStd::reinterpret_pointer_cast<InternalQueryable<T, std::list, TAllocator>>(
      std::make_shared<ListInternalQueryable<T, TAllocator>>(list));
  }  
  template<typename T>
  static std::shared_ptr<InternalQueryable<T, std::list>> FromList(const std::list<T> & list)
  {
    return FutureStd::reinterpret_pointer_cast<InternalQueryable<T, std::list>>(
      std::make_shared<ListInternalQueryable<T>>(list));
  }

  template<typename T, typename TLessThan = std::less<T>, typename TAllocator = std::allocator<T>>
  static std::shared_ptr<InternalQueryable<T, std::multiset, TLessThan, TAllocator>> FromMultiSet(
    const std::multiset<T, TLessThan, TAllocator> & multiset)
  {
    return FutureStd::reinterpret_pointer_cast<InternalQueryable<T, std::multiset, TLessThan, TAllocator>>(
      std::make_shared<MultiSetInternalQueryable<T, TLessThan, TAllocator>>(multiset));
  }
  template<typename T>
  static std::shared_ptr<InternalQueryable<T, std::multiset>> FromMultiSet(
    const std::multiset<T> & multiset)
  {
    return FutureStd::reinterpret_pointer_cast<InternalQueryable<T, std::multiset>>(
      std::make_shared<MultiSetInternalQueryable<T>>(multiset));
  }

  template<typename T, typename TLessThan = std::less<T>, typename TAllocator = std::allocator<T>>
  static std::shared_ptr<InternalQueryable<T, std::set, TLessThan, TAllocator>> FromSet(
    const std::set<T, TLessThan, TAllocator> & set)
  {
    return FutureStd::reinterpret_pointer_cast<InternalQueryable<T, std::set, TLessThan, TAllocator>>(
      std::make_shared<SetInternalQueryable<T, TLessThan, TAllocator>>(set));
  }
  template<typename T>
  static std::shared_ptr<InternalQueryable<T, std::set>> FromSet(
    const std::set<T> & set)
  {
    return FutureStd::reinterpret_pointer_cast<InternalQueryable<T, std::set>>(
      std::make_shared<SetInternalQueryable<T>>(set));
  }

  template<typename T, typename TAllocator = std::allocator<T>>
  static std::shared_ptr<InternalQueryable<T, std::vector, TAllocator>> FromVector(const std::vector<T, TAllocator> & vector)
  {
    return FutureStd::reinterpret_pointer_cast<InternalQueryable<T, std::vector, TAllocator>>(
      std::make_shared<VectorInternalQueryable<T, TAllocator>>(vector));
  }
  template<typename T>
  static std::shared_ptr<InternalQueryable<T, std::vector>> FromVector(const std::vector<T> & vector)
  {
    return FutureStd::reinterpret_pointer_cast<InternalQueryable<T, std::vector>>(
      std::make_shared<VectorInternalQueryable<T>>(vector));
  }



  // MOVING FACTORY

  template<typename T, typename TAllocator = std::allocator<T>>
  static std::shared_ptr<InternalQueryable<T, std::deque, TAllocator>> FromDeque(std::deque<T, TAllocator> && deque)
  {
    return FutureStd::reinterpret_pointer_cast<InternalQueryable<T, std::deque, TAllocator>>(
      std::make_shared<DequeInternalQueryable<T, TAllocator>>(deque));
  }
  template<typename T>
  static std::shared_ptr<InternalQueryable<T, std::deque>> FromDeque(std::deque<T> && deque)
  {
    return FutureStd::reinterpret_pointer_cast<InternalQueryable<T, std::deque>>(
      std::make_shared<DequeInternalQueryable<T>>(deque));
  }
  
  template<typename T, typename TAllocator = std::allocator<T>>
  static std::shared_ptr<InternalQueryable<T, std::list, TAllocator>> FromList(std::list<T, TAllocator> && list)
  {
    return FutureStd::reinterpret_pointer_cast<InternalQueryable<T, std::list, TAllocator>>(
      std::make_shared<ListInternalQueryable<T, TAllocator>>(list));
  }  
  template<typename T>
  static std::shared_ptr<InternalQueryable<T, std::list>> FromList(std::list<T> && list)
  {
    return FutureStd::reinterpret_pointer_cast<InternalQueryable<T, std::list>>(
      std::make_shared<ListInternalQueryable<T>>(list));
  }

  template<typename T, typename TLessThan = std::less<T>, typename TAllocator = std::allocator<T>>
  static std::shared_ptr<InternalQueryable<T, std::multiset, TLessThan, TAllocator>> FromMultiSet(
    std::multiset<T, TLessThan, TAllocator> && multiset)
  {
    return FutureStd::reinterpret_pointer_cast<InternalQueryable<T, std::multiset, TLessThan, TAllocator>>(
      std::make_shared<MultiSetInternalQueryable<T, TLessThan, TAllocator>>(multiset));
  }
  template<typename T>
  static std::shared_ptr<InternalQueryable<T, std::multiset>> FromMultiSet(
    std::multiset<T> && multiset)
  {
    return FutureStd::reinterpret_pointer_cast<InternalQueryable<T, std::multiset>>(
      std::make_shared<MultiSetInternalQueryable<T>>(multiset));
  }

  template<typename T, typename TLessThan = std::less<T>, typename TAllocator = std::allocator<T>>
  static std::shared_ptr<InternalQueryable<T, std::set, TLessThan, TAllocator>> FromSet(
    std::set<T, TLessThan, TAllocator> && set)
  {
    return FutureStd::reinterpret_pointer_cast<InternalQueryable<T, std::set, TLessThan, TAllocator>>(
      std::make_shared<SetInternalQueryable<T, TLessThan, TAllocator>>(set));
  }
  template<typename T>
  static std::shared_ptr<InternalQueryable<T, std::set>> FromSet(
    std::set<T> && set)
  {
    return FutureStd::reinterpret_pointer_cast<InternalQueryable<T, std::set>>(
      std::make_shared<SetInternalQueryable<T>>(set));
  }

  template<typename T, typename TAllocator = std::allocator<T>>
  static std::shared_ptr<InternalQueryable<T, std::vector, TAllocator>> FromVector(std::vector<T, TAllocator> && vector)
  {
    return FutureStd::reinterpret_pointer_cast<InternalQueryable<T, std::vector, TAllocator>>(
      std::make_shared<VectorInternalQueryable<T, TAllocator>>(vector));
  }
  template<typename T>
  static std::shared_ptr<InternalQueryable<T, std::vector>> FromVector(std::vector<T> && vector)
  {
    return FutureStd::reinterpret_pointer_cast<InternalQueryable<T, std::vector>>(
      std::make_shared<VectorInternalQueryable<T>>(vector));
  }
}

#endif