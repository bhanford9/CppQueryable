#ifndef CPPQUERYABLE_QUERYABLE_QUERYBLEALIASES_H
#define CPPQUERYABLE_QUERYABLE_QUERYBLEALIASES_H

#include <deque>
#include <list>
#include <memory>
#include <set>
#include <vector>

#include "Queryable.hpp"

template<
  typename TObj,
  typename TAllocator = std::allocator<TObj>>
using QueryableDeque = Queryable<TObj, std::deque, TAllocator>;

template<
  typename TObj,
  typename TAllocator = std::allocator<TObj>>
using QueryableList = Queryable<TObj, std::list, TAllocator>;

template<
  typename TObj,
  typename TLessThan = std::less<TObj>,
  typename TAllocator = std::allocator<TObj>>
using QueryableMultiSet = Queryable<TObj, std::multiset, TLessThan, TAllocator>;

template<
  typename TObj,
  typename TLessThan = std::less<TObj>,
  typename TAllocator = std::allocator<TObj>>
using QueryableSet = Queryable<TObj, std::set, TLessThan, TAllocator>;

template<
  typename TObj,
  typename TAllocator = std::allocator<TObj>>
using QueryableVector = Queryable<TObj, std::vector, TAllocator>;

// template<
//   typename TObj,
//   typename ...TArgs>
// using QueryableDeque = Queryable<TObj, std::deque, TArgs...>;
//
// template<
//   typename TObj,
//   typename ...TArgs>
// using QueryableList = Queryable<TObj, std::list, TArgs...>;
//
// template<
//   typename TObj,
//   typename ...TArgs>
// using QueryableMultiSet = Queryable<TObj, std::multiset, TArgs...>;
//
// template<
//   typename TObj,
//   typename ...TArgs>
// using QueryableSet = Queryable<TObj, std::set, TArgs...>;
//
// template<
//   typename TObj,
//   typename ...TArgs>
// using QueryableVector = Queryable<TObj, std::vector, TArgs...>;

#endif
