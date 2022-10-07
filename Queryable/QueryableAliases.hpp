#ifndef CPPQUERYABLE_QUERYABLE_QUERYBLEALIASES_H
#define CPPQUERYABLE_QUERYABLE_QUERYBLEALIASES_H

#include <deque>
#include <list>
#include <map>
#include <memory>
#include <set>
#include <vector>

#include "Queryable.hpp"

template<
  typename TObj,
  typename TAllocator = std::allocator<TObj>>
using QueryableDeque = Queryable<TObj, std::deque, TObj, TAllocator>;

template<
  typename TObj,
  typename TAllocator = std::allocator<TObj>>
using QueryableList = Queryable<TObj, std::list, TObj,TAllocator>;

template<
  typename TKey,
  typename TValue,
  typename TKeyLessThan = std::less<TKey>,
  typename TAllocator = std::allocator<std::pair<const TKey, TValue>>>
using QueryableMap = Queryable<TKey, std::map, std::pair<const TKey, TValue>, TValue, TKeyLessThan, TAllocator>;

template<
  typename TObj,
  typename TLessThan = std::less<TObj>,
  typename TAllocator = std::allocator<TObj>>
using QueryableMultiSet = Queryable<TObj, std::multiset, TObj, TLessThan, TAllocator>;

template<
  typename TObj,
  typename TLessThan = std::less<TObj>,
  typename TAllocator = std::allocator<TObj>>
using QueryableSet = Queryable<TObj, std::set, TObj, TLessThan, TAllocator>;

template<
  typename TObj,
  typename TAllocator = std::allocator<TObj>>
using QueryableVector = Queryable<TObj, std::vector, TObj, TAllocator>;

#endif
